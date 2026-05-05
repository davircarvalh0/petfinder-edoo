#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <functional>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

class Database {
private:
    sqlite3* db;
    string mensagemErro;

    bool vincularParametros(sqlite3_stmt* stmt, const vector<string>& parametros);
    bool tabelaTemColuna(const string& tabela, const string& coluna);
    bool migrarSchemaAntigo();
    bool garantirColunasNovas();

public:
    using Linha = unordered_map<string, string>;
    using CallbackConsulta = function<void(const Linha&)>;

    Database();
    ~Database();

    bool abrir(const string& nomeArquivo);
    void fechar();
    bool estaAberto() const;

    bool executar(const string& sql);
    bool executarPreparado(const string& sql, const vector<string>& parametros = {});
    bool consultar(const string& sql, const vector<string>& parametros, CallbackConsulta callback);
    bool criarTabelas(const string& caminhoSchema);

    bool iniciarTransacao();
    bool confirmarTransacao();
    bool cancelarTransacao();

    sqlite3* getConexao();
    long long ultimoIdInserido() const;
    string getMensagemErro() const;
};

#endif
