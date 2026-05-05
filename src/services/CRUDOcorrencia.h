#ifndef CRUDOCORRENCIA_H
#define CRUDOCORRENCIA_H
#include <iostream>
#include <string>
#include "Ocorrencia.h"
#include <vector>
#include "Database.h" 
using namespace std;
class CRUDocorrencia{
    private:
    Database& banco; //referencia ao banco de dados //o & aponta, não clona
    public:
    CRUDocorrencia(Database& banco); //constructor
    void CriarOcorrencia(int animalId, string data, int localizacaoId); //C
    void LerOcorrencia(int id); //R - read so de uma em especifico
    void LerTodasOcorrencias(); //R - read de todas as ocorrencias
    void AtualizarOcorrencia(int id, string novoStatus); //U
    void DeletarOcorrencia(int id); //D
};
#endif