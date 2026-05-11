#include "CRUDOcorrencia.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

//constructor
CRUDOcorrencia::CRUDOcorrencia(Database* banco) : db(banco) {} // referencia ao banco de dados 
//Create
bool CRUDOcorrencia::CriarOcorrencia(Ocorrencia* ocorrencia, int animalId, int localizacaoId) {
    if (!ocorrencia) return false;

    string statusEnvio = ocorrencia->getStatus();

    // 1. Criamos os parâmetros básicos (os que sempre existem)
    vector<string> params = {
        to_string(animalId),
        ocorrencia->getData()
    };

    string sql;

    if (localizacaoId > 0) {
        params.push_back(to_string(localizacaoId));
        params.push_back(statusEnvio);
        sql = "INSERT INTO ocorrencias (animal_id, data_desaparecimento, ultima_localizacao_id, status) VALUES (?, ?, ?, ?)";
    } else {
        params.push_back(statusEnvio);
        sql = "INSERT INTO ocorrencias (animal_id, data_desaparecimento, status) VALUES (?, ?, ?)";
    }

    // DEBUG para você ter certeza no terminal
    cout << "--- DEBUG PARAMETROS ---" << endl;
    cout << "Itens no vetor: " << params.size() << endl;
    cout << "SQL: " << sql << endl;

    bool sucesso = db->executarPreparado(sql, params);

    if (sucesso) {
        cout << "Ocorrencia registrada no PetFinder com sucesso!" << endl;
    } else {
        cout << "Erro ao registrar ocorrencia: " << db->getMensagemErro() << endl;
    }

    return sucesso;
}
//Read especifica
bool CRUDOcorrencia::LerOcorrencia(int id) {
    bool encontrou = false;
    db->consultar(
        "SELECT * FROM ocorrencias WHERE id = ?", 
        {to_string(id)}, 
        [&](const Database::Linha& linha) {
            encontrou = true;
            cout << "=== Ocorrencia Detalhada ===" << endl;
            cout << "ID: "     << linha.at("id") << endl;
            cout << "Status: " << linha.at("status") << endl;
            cout << "Data: "   << linha.at("data_desaparecimento") << endl;
            cout << "Animal ID: " << linha.at("animal_id") << endl;
        }
    );

    if (!encontrou) cout << "Ocorrencia " << id << " nao encontrada." << endl;
    return encontrou;
}
//Read Geral
bool CRUDOcorrencia::LerTodasOcorrencias() {
    int contador = 0;
    db->consultar(
        "SELECT * FROM ocorrencias ORDER BY id DESC", 
        {}, 
        [&](const Database::Linha& linha) {
            contador++;
            cout << "[" << linha.at("status") << "] Ocorrencia ID: " << linha.at("id") 
                 << " | Data: " << linha.at("data_desaparecimento") << endl;
        }
    );

    if (contador == 0) cout << "Nenhuma ocorrencia registrada no sistema." << endl;
    return contador > 0;
}
//Update
bool CRUDOcorrencia::AtualizarOcorrencia(int id, const string& novoStatus) {
    bool sucesso = db->executarPreparado(
        "UPDATE ocorrencias SET status = ? WHERE id = ?",
        {novoStatus, to_string(id)}
    );

    if (sucesso) cout << "Status da ocorrencia " << id << " atualizado para " << novoStatus << endl;
    return sucesso;
}
//Delete
bool CRUDOcorrencia::DeletarOcorrencia(int id) {
    bool sucesso = db->executarPreparado(
        "DELETE FROM ocorrencias WHERE id = ?",
        {to_string(id)}
    );

    if (sucesso) cout << "Ocorrencia " << id << " removida do banco de dados." << endl;
    return sucesso;
}