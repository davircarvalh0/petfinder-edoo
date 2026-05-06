#include "CRUDAvistamento.h"
#include <iostream>
using namespace std;
//construtor 
CRUDAvistamento::CRUDAvistamento(Database& database) : db(database) {}
//C, insere um avistamento na tabela avistamentos e vincula o usuario que reportou, a ocorrencia do pet e a localizacao onde viu
bool CRUDAvistamento::criar(int usuarioId, int ocorrenciaId, int localizacaoId, const string& descricao) {
    bool sucesso = db.executarPreparado("INSERT INTO avistamentos (usuario_id, ocorrencia_id, localizacao_id, descricao)VALUES (?, ?, ?, ?)"
, {to_string(usuarioId),to_string(ocorrenciaId), to_string(localizacaoId), descricao});
    if (sucesso) {
        cout << "Avistamento registrado com sucesso!" << endl;
    } else {
        cout << "Erro ao registrar avistamento: " << db.getMensagemErro() << endl;
    }
    return sucesso;
}
//read, lista todos os avistamentos de uma ocorrencia especifica, vai ser util para o dono ver onde o pet foi visto
bool CRUDAvistamento::listarPorOcorrencia(int ocorrenciaId) {
    int contador = 0;
    db.consultar("SELECT * FROM avistamentos WHERE ocorrencia_id = ? ORDER BY data_avistamento DESC", {to_string(ocorrenciaId)}, [&](const Database::Linha& linha) {
        contador++;
        cout << "Avistamento " << contador << endl;
        cout << "ID: " << linha.at("id")<< endl;
        cout << "Data: " << linha.at("data_avistamento") << endl;
        cout << "Descricao: " << linha.at("descricao") << endl;
        cout << "Usuario ID: " << linha.at("usuario_id") << endl;
        cout << "Localizacao ID: " << linha.at("localizacao_id") << endl;
    });
    if (contador == 0) {
        cout << "Nenhum avistamento encontrado para esta ocorrencia." << endl;
    }
    return contador > 0;
}
//delete, remove um avistamento pelo id, vai ser usado quando o usuario errou o reporte
bool CRUDAvistamento::deletar(int id) {
    bool sucesso = db.executarPreparado("DELETE FROM avistamentos WHERE id = ?", {to_string(id)});
    if (sucesso) {
        cout << "Avistamento removido com sucesso!" << endl;
    } else {
        cout << "Erro ao remover avistamento: " << db.getMensagemErro() << endl;
    }
    return sucesso;
}