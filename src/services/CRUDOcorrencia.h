#ifndef CRUDOCORRENCIA_H
#define CRUDOCORRENCIA_H
#include "../models/Ocorrencia.h"
#include "../database/Database.h"
#include <string>
using namespace std;

class CRUDOcorrencia {
private:
    Database* db; 
public:
    CRUDOcorrencia(Database* banco); //constructor
    bool CriarOcorrencia(Ocorrencia* ocorrencia, int animalId, int localizacaoId); //C
    bool LerOcorrencia(int id); //R -> read so de uma em especifico
    bool LerTodasOcorrencias(); //R -> read de todas as ocorrencias
    bool AtualizarOcorrencia(int id, const string& novoStatus); //U
    bool DeletarOcorrencia(int id); //D
};
#endif