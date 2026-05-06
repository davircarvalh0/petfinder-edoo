#pragma once
#include "Pessoa.h"
#include <string>

class Avistamento;

class Usuario : public Pessoa {

private:
    std::string dataCadastro;

public:
    Usuario(std::string n, std::string c, std::string t, std::string e, std::string data);

    ~Usuario() {}

    void reportarAvistamento(Avistamento* av);

    void exibirInfo() override;

    void buscarAnimais();
};