#pragma once
#include <string>

class Pessoa {
private:
    std::string nome;
    std::string cpf;
    std::string telefone;
    std::string email;

public:
    Pessoa(std::string n, std::string c, std::string t, std::string e);
    
    std::string getNome();
    std::string getCpf();
    
    virtual void exibirInfo() = 0; 
};