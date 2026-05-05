#include "Database.h"
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

Database::Database() {
    db = nullptr;
}

Database::~Database() {
    fechar();
}

bool Database::abrir(const string& nomeArquivo) {
    fechar();

    if (sqlite3_open(nomeArquivo.c_str(), &db) != SQLITE_OK) {
        mensagemErro = sqlite3_errmsg(db);
        cout << "Erro ao abrir banco: " << mensagemErro << endl;
        fechar();
        return false;
    }

    if (!executar("PRAGMA foreign_keys = ON;")) {
        fechar();
        return false;
    }

    cout << "Banco conectado com sucesso: " << nomeArquivo << endl;
    return true;
}

void Database::fechar() {
    if (db) {
        sqlite3_close(db);
        db = nullptr;
    }
}

bool Database::estaAberto() const {
    return db != nullptr;
}

bool Database::executar(const string& sql) {
    if (!db) {
        mensagemErro = "Banco de dados nao esta aberto.";
        cout << "Erro SQL: " << mensagemErro << endl;
        return false;
    }

    char* erro = nullptr;

    if (sqlite3_exec(db, sql.c_str(), 0, 0, &erro) != SQLITE_OK) {
        mensagemErro = erro ? erro : sqlite3_errmsg(db);
        cout << "Erro SQL: " << mensagemErro << endl;
        sqlite3_free(erro);
        return false;
    }

    return true;
}

bool Database::vincularParametros(sqlite3_stmt* stmt, const vector<string>& parametros) {
    for (size_t i = 0; i < parametros.size(); i++) {
        int indice = static_cast<int>(i + 1);
        int resultado = sqlite3_bind_text(stmt, indice, parametros[i].c_str(), -1, SQLITE_TRANSIENT);

        if (resultado != SQLITE_OK) {
            mensagemErro = sqlite3_errmsg(db);
            cout << "Erro ao vincular parametro " << indice << ": " << mensagemErro << endl;
            return false;
        }
    }

    return true;
}

bool Database::executarPreparado(const string& sql, const vector<string>& parametros) {
    if (!db) {
        mensagemErro = "Banco de dados nao esta aberto.";
        cout << "Erro SQL: " << mensagemErro << endl;
        return false;
    }

    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        mensagemErro = sqlite3_errmsg(db);
        cout << "Erro ao preparar SQL: " << mensagemErro << endl;
        return false;
    }

    if (!vincularParametros(stmt, parametros)) {
        sqlite3_finalize(stmt);
        return false;
    }

    int resultado = sqlite3_step(stmt);

    if (resultado != SQLITE_DONE) {
        mensagemErro = sqlite3_errmsg(db);
        cout << "Erro ao executar SQL preparado: " << mensagemErro << endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

bool Database::consultar(const string& sql, const vector<string>& parametros, CallbackConsulta callback) {
    if (!db) {
        mensagemErro = "Banco de dados nao esta aberto.";
        cout << "Erro SQL: " << mensagemErro << endl;
        return false;
    }

    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        mensagemErro = sqlite3_errmsg(db);
        cout << "Erro ao preparar consulta: " << mensagemErro << endl;
        return false;
    }

    if (!vincularParametros(stmt, parametros)) {
        sqlite3_finalize(stmt);
        return false;
    }

    int resultado;

    while ((resultado = sqlite3_step(stmt)) == SQLITE_ROW) {
        Linha linha;
        int quantidadeColunas = sqlite3_column_count(stmt);

        for (int i = 0; i < quantidadeColunas; i++) {
            const char* nomeColuna = sqlite3_column_name(stmt, i);
            const unsigned char* valor = sqlite3_column_text(stmt, i);
            linha[nomeColuna ? nomeColuna : ""] = valor ? reinterpret_cast<const char*>(valor) : "";
        }

        callback(linha);
    }

    if (resultado != SQLITE_DONE) {
        mensagemErro = sqlite3_errmsg(db);
        cout << "Erro ao consultar dados: " << mensagemErro << endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

bool Database::tabelaTemColuna(const string& tabela, const string& coluna) {
    bool encontrou = false;

    consultar("PRAGMA table_info(" + tabela + ");", {}, [&](const Linha& linha) {
        auto item = linha.find("name");

        if (item != linha.end() && item->second == coluna) {
            encontrou = true;
        }
    });

    return encontrou;
}

bool Database::migrarSchemaAntigo() {
    bool temAnimais = tabelaTemColuna("animais", "id");
    bool animaisAntigo = temAnimais && !tabelaTemColuna("animais", "dono_id");
    bool temUsuariosAntigo = tabelaTemColuna("usuarios", "id");
    bool ocorrenciasAntigo = tabelaTemColuna("ocorrencias", "data") && !tabelaTemColuna("ocorrencias", "data_desaparecimento");

    if (!animaisAntigo && !temUsuariosAntigo && !ocorrenciasAntigo) {
        return true;
    }

    string sufixo = "_legado_" + to_string(time(nullptr));
    cout << "Schema antigo encontrado. Guardando tabelas antigas com sufixo " << sufixo << endl;

    if (animaisAntigo && !executar("ALTER TABLE animais RENAME TO animais" + sufixo + ";")) {
        return false;
    }

    if (temUsuariosAntigo && !executar("ALTER TABLE usuarios RENAME TO usuarios" + sufixo + ";")) {
        return false;
    }

    if (ocorrenciasAntigo && !executar("ALTER TABLE ocorrencias RENAME TO ocorrencias" + sufixo + ";")) {
        return false;
    }

    return true;
}

bool Database::garantirColunasNovas() {
    if (!tabelaTemColuna("animais", "foto")) {
        return executar("ALTER TABLE animais ADD COLUMN foto TEXT DEFAULT '';");
    }

    return true;
}

bool Database::criarTabelas(const string& caminhoSchema) {
    ifstream arquivo(caminhoSchema);

    if (!arquivo.is_open()) {
        mensagemErro = "Nao foi possivel abrir o arquivo " + caminhoSchema;
        cout << "Erro ao abrir schema: " << mensagemErro << endl;
        return false;
    }

    stringstream buffer;
    buffer << arquivo.rdbuf();

    if (!iniciarTransacao()) {
        return false;
    }

    if (!migrarSchemaAntigo() || !executar(buffer.str()) || !garantirColunasNovas()) {
        cancelarTransacao();
        return false;
    }

    return confirmarTransacao();
}

bool Database::iniciarTransacao() {
    return executar("BEGIN TRANSACTION;");
}

bool Database::confirmarTransacao() {
    return executar("COMMIT;");
}

bool Database::cancelarTransacao() {
    return executar("ROLLBACK;");
}

sqlite3* Database::getConexao() {
    return db;
}

long long Database::ultimoIdInserido() const {
    if (!db) {
        return 0;
    }

    return sqlite3_last_insert_rowid(db);
}

string Database::getMensagemErro() const {
    return mensagemErro;
}
