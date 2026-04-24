#pragma once
#include "Pessoa.h"
#include <vector>
#include <string>

class Avistamento;

class Usuario : public Pessoa {
private:
    std::string dataCadastro;
    std::vector<Avistamento*> avistamentos;

public:
    Usuario(std::string n, std::string c, std::string t, std::string e, std::string data);
    
    void reportarAvistamento();
    void exibirInfo();
    void buscarAnimais();
};