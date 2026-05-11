#pragma once
#include <string>
using namespace std;

class Pessoa {
protected:     //protected faz com q outras subclasses acessem tambem
                // private (oq estava antes) apenas csse pessoa acessava
    string nome;
    string cpf;
    string telefone;
    string email;

public:
    Pessoa(string n, string c, string t, string e) 
        : nome(n), cpf(c), telefone(t), email(e) {}

    string getNome() const;
    string getCpf() const;
    string getTelefone() const;
    string getEmail() const;
    
    virtual ~Pessoa() {}

    
    
    virtual void exibirInfo() = 0; 
};