#pragma once
#include "../models/Usuario.h"
#include "../database/Database.h"
#include <string>

class CRUDUsuario {
private:
    Database& db;

public:
    CRUDUsuario(Database& database);

    bool cadastrar(const std::string& nome, const std::string& cpf,
                   const std::string& telefone, const std::string& email,
                   const std::string& dataCadastro);

    bool buscarPorId(int id);

    bool listarTodos();

    bool atualizar(int id, const std::string& novoTelefone,
                   const std::string& novoEmail);

    bool deletar(int id);
};