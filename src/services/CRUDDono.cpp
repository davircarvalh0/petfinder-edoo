#include "CRUDDono.h"
#include <iostream>

using namespace std;

CRUDDono::CRUDDono(Database& database) : db(database) {}

bool CRUDDono::cadastrar(const string& nome, const string& cpf,
                          const string& telefone, const string& email,
                          const string& endereco) {

    string sql = "INSERT INTO pessoas (tipo, nome, cpf, telefone, email, endereco) "
                 "VALUES ('dono', ?, ?, ?, ?, ?);";

    bool sucesso = db.executarPreparado(sql, {nome, cpf, telefone, email, endereco});

    if (sucesso) {
        cout << "Dono cadastrado com sucesso!" << endl;
    } else {
        cout << "Erro ao cadastrar dono: " << db.getMensagemErro() << endl;
    }

    return sucesso;
}

bool CRUDDono::buscarPorCpf(const string& cpf) {
    string sql = "SELECT id, nome, cpf, telefone, email, endereco "
                 "FROM pessoas WHERE cpf = ? AND tipo = 'dono';";

    bool encontrou = false;

    db.consultar(sql, {cpf}, [&](const Database::Linha& linha) {
        encontrou = true;
        cout << "--- Dono Encontrado ---" << endl;
        cout << "ID       : " << linha.at("id")       << endl;
        cout << "Nome     : " << linha.at("nome")     << endl;
        cout << "CPF      : " << linha.at("cpf")      << endl;
        cout << "Telefone : " << linha.at("telefone") << endl;
        cout << "Email    : " << linha.at("email")    << endl;
        cout << "Endereço : " << linha.at("endereco") << endl;
    });

    if (!encontrou) {
        cout << "Nenhum dono encontrado com CPF: " << cpf << endl;
    }

    return encontrou;
}

bool CRUDDono::listarTodos() {
    string sql = "SELECT id, nome, cpf, telefone, email, endereco "
                 "FROM pessoas WHERE tipo = 'dono' ORDER BY nome;";

    int contador = 0;

    db.consultar(sql, {}, [&](const Database::Linha& linha) {
        contador++;
        cout << "--- Dono " << contador << " ---" << endl;
        cout << "ID       : " << linha.at("id")       << endl;
        cout << "Nome     : " << linha.at("nome")     << endl;
        cout << "CPF      : " << linha.at("cpf")      << endl;
        cout << "Telefone : " << linha.at("telefone") << endl;
        cout << "Email    : " << linha.at("email")    << endl;
        cout << "Endereço : " << linha.at("endereco") << endl;
    });

    if (contador == 0) {
        cout << "Nenhum dono cadastrado." << endl;
    }

    return contador > 0;
}

bool CRUDDono::atualizar(const string& cpf, const string& novoTelefone,
                          const string& novoEmail) {

    string sql = "UPDATE pessoas SET telefone = ?, email = ?, "
                 "atualizado_em = datetime('now', 'localtime') "
                 "WHERE cpf = ? AND tipo = 'dono';";


    bool sucesso = db.executarPreparado(sql, {novoTelefone, novoEmail, cpf});

    if (sucesso) {
        cout << "Dono atualizado com sucesso!" << endl;
    } else {
        cout << "Erro ao atualizar dono: " << db.getMensagemErro() << endl;
    }

    return sucesso;
}

bool CRUDDono::deletar(const string& cpf) {
    string sql = "DELETE FROM pessoas WHERE cpf = ? AND tipo = 'dono';";

    bool sucesso = db.executarPreparado(sql, {cpf});

    if (sucesso) {
        cout << "Dono removido com sucesso!" << endl;
    } else {
        cout << "Erro ao remover dono: " << db.getMensagemErro() << endl;
    }

    return sucesso;
}