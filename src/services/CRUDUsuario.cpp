#include "CRUDUsuario.h"
#include <iostream>
using namespace std;
CRUDUsuario::CRUDUsuario(Database& database) : db(database) {}
bool CRUDUsuario::cadastrar(const string& nome, const string& cpf, const string& telefone, const string& email,const string& dataCadastro) {
    bool sucesso = db.executarPreparado("INSERT INTO pessoas (tipo, nome, cpf, telefone, email, data_cadastro) VALUES ('usuario', ?, ?, ?, ?, ?)", {nome, cpf, telefone, email, dataCadastro});
    if (sucesso) {
        cout << "Usuario cadastrado com sucesso!" << endl;
    } else {
        cout << "Erro ao cadastrar usuario: " << db.getMensagemErro() << endl;
    }
    return sucesso;
}
bool CRUDUsuario::buscarPorId(int id) {
    bool encontrou = false;
    db.consultar("SELECT id, nome, cpf, telefone, email, data_cadastro FROM pessoas WHERE id = ? AND tipo = 'usuario'", {to_string(id)}, [&](const Database::Linha& linha) {
        encontrou = true;
        cout << "Usuario Encontrado"  << endl;
        cout << "ID: " << linha.at("id") << endl;
        cout << "Nome: " << linha.at("nome")  << endl;
        cout << "CPF: " << linha.at("cpf")  << endl;
        cout << "Telefone: " << linha.at("telefone") << endl;
        cout << "Emai: " << linha.at("email") << endl;
        cout << "Data Cadastro: " << linha.at("data_cadastro") << endl;});
    if (!encontrou) {
        cout << "Nenhum usuario encontrado com ID: " << id << endl;
    }
    return encontrou;
}
bool CRUDUsuario::listarTodos() {
    int contador = 0;
    db.consultar("SELECT id, nome, cpf, telefone, email, data_cadastro FROM pessoas WHERE tipo = 'usuario' ORDER BY nome", {}, [&](const Database::Linha& linha) {
        contador++;
        cout << "Usuario " << contador  << endl;
        cout << "ID: " << linha.at("id") << endl;
        cout << "Nome: " << linha.at("nome")  << endl;
        cout << "CPF: " << linha.at("cpf") << endl;
        cout << "Telefone: " << linha.at("telefone") << endl;
        cout << "Email: " << linha.at("email") << endl;
        cout << "Data Cadastro: " << linha.at("data_cadastro") << endl;
    });
    if (contador == 0) {
        cout << "Nenhum usuario cadastrado." << endl;
    }
    return contador > 0;
}
bool CRUDUsuario::atualizar(int id, const string& novoTelefone, const string& novoEmail) {
    bool sucesso = db.executarPreparado("UPDATE pessoas SET telefone = ?, email = ?,atualizado_em = datetime('now', 'localtime') WHERE id = ? AND tipo = 'usuario'", {novoTelefone, novoEmail, to_string(id)});
    if (sucesso) {
        cout << "Usuario atualizado com sucesso!" << endl;
    } else {
        cout << "Erro ao atualizar usuario: " << db.getMensagemErro() << endl;
    }
    return sucesso;
}
bool CRUDUsuario::deletar(int id) {
    bool sucesso = db.executarPreparado("DELETE FROM pessoas WHERE id = ? AND tipo = 'usuario'", {to_string(id)});
    if (sucesso) {
        cout << "Usuario removido com sucesso!" << endl;
    } else {
        cout << "Erro ao remover usuario: " << db.getMensagemErro() << endl;
    }
    return sucesso;
}