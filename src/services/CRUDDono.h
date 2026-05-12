#ifndef CRUDDONO_H
#define CRUDDONO_H
#include "../models/Dono.h"
#include "../database/Database.h"
#include <string>
class CRUDDono {
    private:
    Database* db;
    public:
//construtor
    CRUDDono(Database* database);
//C : cadastra um novo dono no banco
    bool cadastrar(Dono* dono, const std::string& usuario, const std::string& senha);
    string realizarLogin(const std::string& usuario, const std::string& senha);
    bool buscarPorId(int id); //R: busca um dono especifico pelo id
    bool listarTodos(); //R: lista todos os donos cadastrados
    bool atualizar(int id, const std::string& novoTelefone,const std::string& novoEndereco); //U: atualiza telefone e endereco do dono pelo id
    bool deletar(int id); //D: remove um dono do banco pelo id
    string buscarPerfil(int id); //R: busca dados do perfil do usuario para exibir na tela
    bool atualizarPerfil(int id, const string& email, const string& telefone, const string& senha); //U: atualiza dados sensiveis (so altera o que nao for vazio)
};
#endif