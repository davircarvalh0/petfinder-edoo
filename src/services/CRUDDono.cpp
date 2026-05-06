#include "CRUDDono.h"
#include <iostream>
using namespace std;
//construtor, inicializa a referencia ao banco
CRUDDono::CRUDDono(Database& database) : db(database) {}
//C: insere um dono na tabela pessoas com fixo "dono"
bool CRUDDono::cadastrar(const string& nome, const string& cpf,const string& telefone, const string& email, const string& endereco) {
    bool sucesso = db.executarPreparado("INSERT INTO pessoas (tipo, nome, cpf, telefone, email, endereco) VALUES ('dono', ?, ?, ?, ?, ?)", {nome, cpf, telefone, email, endereco});
    if (sucesso) {
        cout << "Dono cadastrado com sucesso!" << endl;
    } else {
        cout << "Erro ao cadastrar dono: " << db.getMensagemErro() << endl;
    }
    return sucesso;
}
//R:busca um dono especifico pelo id e imprime suas informacoes
bool CRUDDono::buscarPorId(int id) {
    bool encontrou = false;
    db.consultar("SELECT id, nome, cpf, telefone, email, endereco FROM pessoas WHERE id = ? AND tipo = 'dono'", {to_string(id)}, [&](const Database::Linha& linha) {
        encontrou = true;
        cout << "Dono Encontrado" << endl;
        cout << "ID: " << linha.at("id") << endl;
        cout << "Nome: " << linha.at("nome") << endl;
        cout << "CPF: " << linha.at("cpf") << endl;
        cout << "Telefone: " << linha.at("telefone") << endl;
        cout << "Email: " << linha.at("email") << endl;
        cout << "Endereco: " << linha.at("endereco") << endl;
    });
    if (!encontrou) {
        cout << "Nenhum dono encontrado com ID: " << id << endl;
    }
    return encontrou;
}
//R: lista todos os donos cadastrados ordenados por nome
bool CRUDDono::listarTodos() {
    int contador = 0;
    db.consultar("SELECT id, nome, cpf, telefone, email, endereco FROM pessoas WHERE tipo = 'dono' ORDER BY nome", {}, [&](const Database::Linha& linha) {
        contador++;
        cout << "Dono " << contador << endl;
        cout << "ID: " << linha.at("id") << endl;
        cout << "Nome: " << linha.at("nome") << endl;
        cout << "CPF: " << linha.at("cpf") << endl;
        cout << "Telefone: " << linha.at("telefone") << endl;
        cout << "Email: " << linha.at("email") << endl;
        cout << "Endereco: " << linha.at("endereco") << endl;
    });
    if (contador == 0) {
        cout << "Nenhum dono cadastrado." << endl;
    }
    return contador > 0;
}
//U: atualiza telefone e endereco do dono pelo id e atualiza tambem o campo atualizado_em automaticamente
bool CRUDDono::atualizar(int id, const string& novoTelefone,const string& novoEndereco) {
    bool sucesso = db.executarPreparado("UPDATE pessoas SET telefone = ?, endereco = ?, atualizado_em = datetime('now', 'localtime')WHERE id = ? AND tipo = 'dono';", {novoTelefone, novoEndereco, to_string(id)});
    if (sucesso) {
        cout << "Dono atualizado com sucesso!" << endl;
    } else {
        cout << "Erro ao atualizar dono: " << db.getMensagemErro() << endl;
    }
    return sucesso;
}
//D: remove um dono do banco pelo id e por cascade no schema, remove tambem os animais desse dono
bool CRUDDono::deletar(int id) {
    bool sucesso = db.executarPreparado("DELETE FROM pessoas WHERE id = ? AND tipo = 'dono'", {to_string(id)});
    if (sucesso) {
        cout << "Dono removido com sucesso!" << endl;
    } else {
        cout << "Erro ao remover dono: " << db.getMensagemErro() << endl;
    }
    return sucesso;
}