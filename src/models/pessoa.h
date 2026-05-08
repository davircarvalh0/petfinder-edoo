#pragma once
#include <string>

class Pessoa {
protected:     //protected faz com q outras subclasses acessem tambem
                // private (oq estava antes) apenas csse pessoa acessava
    std::string nome;
    std::string cpf;
    std::string telefone;
    std::string email;

public:
    Pessoa(std::string n, std::string c, std::string t, std::string e);
    
    virtual ~Pessoa() {}

    std::string getNome();
    std::string getCpf();
    std::string getTelefone();
    std::string getEmail();
    
    
    virtual void exibirInfo() = 0; 
};