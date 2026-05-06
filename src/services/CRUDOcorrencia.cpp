#include "CRUDOcorrencia.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

//constructor
CRUDOcorrencia::CRUDOcorrencia(Database& b) : banco(b) {}; // referencia ao banco de dados // o & aponta, nao clona
//Create
bool CRUDOcorrencia::CriarOcorrencia(int animalId, string data, int localizacaoId) {
    string L_id = to_string(localizacaoId);
    string A_id = to_string(animalId);
    bool sucesso = banco.executarPreparado("INSERT INTO ocorrencias (animal_id, data_desaparecimento, ultima_localizacao_id) VALUES (?, ?, ?)", {A_id, data, L_id});
    if (sucesso) {
        cout << "Ocorrencia criada com sucesso!" << endl;
    } else {
        cout << "Erro ao criar ocorrencia: " << banco.getMensagemErro() << endl;
    }
    return sucesso;
}
//Read especifica
bool CRUDOcorrencia::LerOcorrencia(int id) {
    string str_id = to_string(id);
    bool encontrou = false;
    banco.consultar("SELECT * FROM ocorrencias WHERE id = ?", {str_id}, [&](const Database::Linha& linha) {
        encontrou = true;
        cout << "ID: " << linha.at("id") << endl;
        cout << "Status: " << linha.at("status") << endl;
        cout << "Data Desaparecimento: " << linha.at("data_desaparecimento") << endl;});
    if (!encontrou) {
        cout << "Nenhuma ocorrencia encontrada com ID: " << id << endl;
    }
    return encontrou;
}
//Read Geral
bool CRUDOcorrencia::LerTodasOcorrencias() {
    int contador = 0;
    banco.consultar("SELECT * FROM ocorrencias", {}, [&](const Database::Linha& linha) {
        contador++;
        cout << "--- Ocorrencia " << contador << " ---" << endl;
        cout << "ID: " << linha.at("id") << endl; //acessa cada coluna pelo nome
        cout << "Status: " << linha.at("status") << endl;
        cout << "Data Desaparecimento: " << linha.at("data_desaparecimento") << endl;});
    if (contador == 0) {
        cout << "Nenhuma ocorrencia cadastrada." << endl;
    }
    return contador > 0;
}
//Update
bool CRUDOcorrencia::AtualizarOcorrencia(int id, string novoStatus) {
    string str_id = to_string(id);
    bool sucesso = banco.executarPreparado("UPDATE ocorrencias SET status = ? WHERE id = ?",{novoStatus, str_id});
    if (sucesso) {
        cout << "Ocorrencia Atualizada com sucesso!" << endl;
    } else {
        cout << "Erro ao atualizar ocorrencia: " << banco.getMensagemErro() << endl;
    }
    return sucesso;
}
//Delete
bool CRUDOcorrencia::DeletarOcorrencia(int id) {
    string str_id = to_string(id);
    bool sucesso = banco.executarPreparado("DELETE FROM ocorrencias WHERE id = ?",{str_id});
    if (sucesso) {
        cout << "Ocorrencia Deletada com sucesso!" << endl;
    } else {
        cout << "Erro ao deletar ocorrencia: " << banco.getMensagemErro() << endl;
    }
    return sucesso;
}