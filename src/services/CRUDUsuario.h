#ifndef CRUDUSUARIO_H
#define CRUDUSUARIO_H

#include "../database/Database.h"
#include <string>
//CRUDUsuario gerencia todas as operacoes de banco de dados relacionadas ao Usuario
class CRUDUsuario {
private:
    Database& db;   ////referencia ao banco compartilhado com o resto do sistema

public:
    CRUDUsuario(Database& database);    //construtor recebe o banco ja aberto
    
    bool cadastrar(const std::string& nome, const std::string& cpf, const std::string& telefone, const std::string& email, const std::string& dataCadastro); //insere um novo Usuario no banco
    bool buscarPorId(int id);   //busca um Usuario pelo id
    bool listarTodos();     //lista todos os Usuarios cadastrados
    bool atualizar(int id, const std::string& novoTelefone, const std::string& novoEmail);     //atualiza telefone e email pelo id
    bool deletar(int id);   //remove um Usuario pelo id
};

#endif