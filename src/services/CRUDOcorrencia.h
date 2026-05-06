#ifndef CRUDOCORRENCIA_H
#define CRUDOCORRENCIA_H
#include "../models/Ocorrencia.h"
#include "../database/Database.h"
#include <string>
using namespace std;
class CRUDOcorrencia {
private:
    Database& banco; // referencia ao banco de dados // o & aponta, nao clona
public:
    CRUDOcorrencia(Database& banco); // constructor
    bool CriarOcorrencia(int animalId, string data, int localizacaoId); // C
    bool LerOcorrencia(int id); // R -> read so de uma em especifico
    bool LerTodasOcorrencias(); // R -> read de todas as ocorrencias
    bool AtualizarOcorrencia(int id, string novoStatus); // U
    bool DeletarOcorrencia(int id); // D
};
#endif