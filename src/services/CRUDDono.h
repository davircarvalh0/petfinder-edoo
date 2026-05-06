#ifndef CRUDDONO_H
#define CRUDDONO_H
#include "../models/Dono.h"
#include "../database/Database.h"
#include <string>
using namespace std;
class CRUDDono {
    private:
    Database& db;
    public:
//construtor
    CRUDDono(Database& database);
//C : cadastra um novo dono no banco
    bool cadastrar(const string& nome, const string& cpf,const string& telefone, const string& email,const string& endereco);
    bool buscarPorId(int id); //R: busca um dono especifico pelo id
    bool listarTodos(); //R: lista todos os donos cadastrados
    bool atualizar(int id, const string& novoTelefone,const string& novoEndereco); //U: atualiza telefone e endereco do dono pelo id
    bool deletar(int id); //D: remove um dono do banco pelo id
};
#endif