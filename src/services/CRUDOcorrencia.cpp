#include <iostream>
#include <string>
#include "CRUDOcorrencia.h"
#include <vector>
using namespace std;
//constructor
CRUDOcorrencia::CRUDocorrencia(Database& b) : banco(b) {}; //referencia ao banco de dados //o & aponta, não clona
//Create
void CRUDOcorrencia::CriarOcorrencia(int animalId, string data, int localizacaoId){
    string L_id = to_string(localizacaoId);
    string A_id = to_string(animalId);  
    banco.executarPreparado("INSERT INTO ocorrencias (animal_id, data_desaparecimento, ultima_localizacao_id) VALUES (?, ?, ?)",{A_id,data,L_id});
};
//Read especifica
void CRUDOcorrencia::LerOcorrencia(int id){
    string str_id = to_string(id);
    banco.consultar("SELECT * FROM ocorrencias WHERE id = ?", {str_id}, [](const Database::Linha& linha){
    cout << linha.at("id") << endl;
    cout << linha.at("status") << endl;
    cout << linha.at("data_desaparecimento") << endl;});
};
//Read Geral
void CRUDOcorrencia::LerTodasOcorrencia(){
    banco.consultar("SELECT * FROM ocorrencias", {}, [](const Database::Linha& linha) {
    cout << linha.at("id") << endl; //acessa cada coluna pelo nome
    cout << linha.at("status") << endl;
    cout << linha.at("data_desaparecimento") << endl;});
};
//Update
void CRUDOcorrencia::AtualizarOcorrencia(int id, string novoStatus){};
//Delete
void CRUDOcorrencia::DeletarOcorrencia(int id){};
