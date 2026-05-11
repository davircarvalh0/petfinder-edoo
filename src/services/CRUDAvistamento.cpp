#include "CRUDAvistamento.h"
#include <iostream>
using namespace std;
//construtor 
CRUDAvistamento::CRUDAvistamento(Database* database) : db(database) {}
//C, insere um avistamento na tabela avistamentos e vincula o usuario que reportou, a ocorrencia do pet e a localizacao onde viu
bool CRUDAvistamento::criar(int usuarioId, int ocorrenciaId, const string& descricao, const string& data) {
    bool sucesso = db->executarPreparado(
        "INSERT INTO avistamentos (usuario_id, ocorrencia_id, descricao, data_avistamento) VALUES (?, ?, ?, ?)",
        {to_string(usuarioId), to_string(ocorrenciaId), descricao, data}
    );
    if (sucesso) {
        cout << "Avistamento registrado com sucesso!" << endl;
    } else {
        cout << "Erro ao registrar avistamento: " << db->getMensagemErro() << endl;
    }
    return sucesso;
}
//read, lista todos os avistamentos de uma ocorrencia especifica, vai ser util para o dono ver onde o pet foi visto
string CRUDAvistamento::listarPorOcorrencia(int ocorrenciaId) {
    string json = "[";
    
    // busca os comentários e monta a json
    db->consultar(
        "SELECT * FROM avistamentos WHERE ocorrencia_id = ? ORDER BY id DESC", 
        {to_string(ocorrenciaId)}, 
        [&](const Database::Linha& linha) {
            if (json.length() > 1) json += ",";
            json += "{\"id\":" + linha.at("id") + ","
                 + "\"descricao\":\"" + linha.at("descricao") + "\","
                 + "\"data\":\"" + linha.at("data_avistamento") + "\"}";
        }
    );
    
    json += "]";
    return json;
}
//delete, remove um avistamento pelo id, vai ser usado quando o usuario errou o reporte
bool CRUDAvistamento::deletar(int id) {
    bool sucesso = db->executarPreparado("DELETE FROM avistamentos WHERE id = ?", {to_string(id)});
    if (sucesso) cout << "Avistamento removido com sucesso!" << endl;
    else cout << "Erro ao remover avistamento: " << db->getMensagemErro() << endl;
    return sucesso;
}
