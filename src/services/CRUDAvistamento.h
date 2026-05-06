#ifndef CRUDAVISTAMENO_H
#define CRUDAVISTAMENTO_H
#include "../models/Avistamento.h"
#include "../database/Database.h"
#include <string>
using namespace std;
//vai ser mais um CRD do que um CRUD
class CRUDAvistamento {
    private:
    Database& db; 
    public:
    CRUDAvistamento(Database& database);//construtor
    bool criar(int usuarioId, int ocorrenciaId, int localizacaoId, const string& descricao); //C:registra um novo avistamento de um pet perdido
    bool listarPorOcorrencia(int ocorrenciaId); //R: lista todos os avistamentos de uma ocorrencia especifica
    bool deletar(int id); //D: remove um avistamento pelo id e nao tem Update pois reporte nao se edita,ou seja, deleta e cria outro
};
#endif