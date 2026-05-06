#include "CRUDAnimal.h"
#include <iostream>
using namespace std;
//construtor
CRUDAnimal::CRUDAnimal(Database& database) : db(database) {}
//create
bool CRUDAnimal::cadastrar(int donoId, const string& tipo, const string& nome,float peso, int idade, const string& cor,const string& raca, const string& foto,const string& porte, bool usaColeira,const string& pelagem, bool ehCastrado) {
    bool sucesso = db.executarPreparado("INSERT INTO animais (dono_id, tipo, nome, peso, idade, cor, raca, foto, porte, usa_coleira, pelagem, eh_castrado) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);", {to_string(donoId), tipo, nome,to_string(peso), to_string(idade), cor, raca, foto,porte, to_string(usaColeira), pelagem, to_string(ehCastrado)});
    if (sucesso) {
        cout << "Animal cadastrado com sucesso!" << endl;
    } else {
        cout << "Erro ao cadastrar animal: " << db.getMensagemErro() << endl;
    }
    return sucesso;
}
//read por id
bool CRUDAnimal::buscarPorId(int id) {
    bool encontrou = false;
    db.consultar("SELECT * FROM animais WHERE id = ?;", {to_string(id)}, [&](const Database::Linha& linha) {
        encontrou = true;
        cout << "Animal Encontrado" << endl;
        cout << "ID: " << linha.at("id") << endl;
        cout << "Nome: " << linha.at("nome") << endl;
        cout << "Tipo : " << linha.at("tipo") << endl;
        cout << "Raca: " << linha.at("raca") << endl;
        cout << "Cor: " << linha.at("cor") << endl;
        cout << "Peso: " << linha.at("peso") << " kg" << endl;
        cout << "Idade: " << linha.at("idade")  << " ano(s)" << endl;
        cout << "Foto: " << linha.at("foto") << endl;
    });
    if (!encontrou) {
        cout << "Nenhum animal encontrado com ID: " << id << endl;
    }
    return encontrou;
}
//read geral
bool CRUDAnimal::listarTodos() {
    int contador = 0;
    db.consultar("SELECT * FROM animais ORDER BY nome;", {}, [&](const Database::Linha& linha) {
        contador++;
        cout << "Animal " << contador << endl;
        cout << "ID: " << linha.at("id") << endl;
        cout << "Nome: " << linha.at("nome") << endl;
        cout << "Tipo: " << linha.at("tipo") << endl;
        cout << "Raca: " << linha.at("raca") << endl;
        cout << "Cor: " << linha.at("cor") << endl;
        cout << "Dono ID: " << linha.at("dono_id") << endl;
    });
    if (contador == 0) {
        cout << "Nenhum animal cadastrado." << endl;
    }
    return contador > 0;
}
//read por dono
bool CRUDAnimal::listarPorDono(int donoId) {
    int contador = 0;
    db.consultar("SELECT * FROM animais WHERE dono_id = ? ORDER BY nome;", {to_string(donoId)}, [&](const Database::Linha& linha) {
        contador++;
        cout << "Animal " << contador << endl;
        cout << "ID: " << linha.at("id") << endl;
        cout << "Nome: " << linha.at("nome") << endl;
        cout << "Tipo: " << linha.at("tipo") << endl;
        cout << "Raca: " << linha.at("raca") << endl;
        cout << "Cor: " << linha.at("cor") << endl;
    });
    if (contador == 0) {
        cout << "Nenhum animal encontrado para o dono ID: " << donoId << endl;
    }
    return contador > 0;
}
//update
bool CRUDAnimal::atualizar(int id, const string& novaFoto, float novoPeso) {
    bool sucesso = db.executarPreparado("UPDATE animais SET foto = ?, peso = ?, atualizado_em = datetime('now', 'localtime') WHERE id = ?;", {novaFoto, to_string(novoPeso), to_string(id)});
    if (sucesso) {
        cout << "Animal atualizado com sucesso!" << endl;
    } else {
        cout << "Erro ao atualizar animal: " << db.getMensagemErro() << endl;
    }
    return sucesso;
}
//delete
bool CRUDAnimal::deletar(int id) {
    bool sucesso = db.executarPreparado("DELETE FROM animais WHERE id = ?", {to_string(id)});
    if (sucesso) {
        cout << "Animal removido com sucesso!" << endl;
    } else {
        cout << "Erro ao remover animal: " << db.getMensagemErro() << endl;
    }
    return sucesso;
}