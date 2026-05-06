#include "Pessoa.h"

Pessoa::Pessoa(std::string n, std::string c, std::string t, std::string e) {
    nome = n;
    cpf = c;
    telefone = t;
    email = e;
}

std::string Pessoa::getNome() { return nome; }
std::string Pessoa::getCpf() { return cpf; }    
std::string Pessoa::getTelefone() { return telefone; }
std::string Pessoa::getEmail()    { return email;    }
