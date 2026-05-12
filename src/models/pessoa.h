#pragma once
#include <string>
using namespace std;

class Pessoa {
protected:     //protected faz com q outras subclasses acessem tambem
                // private (oq estava antes) apenas csse pessoa acessava
    string nome;        //nome completo da pessoa
    string cpf;         //cpf usado como identificador unico
    string telefone;    //telefone para contato
    string email;       //email para contato

public:
    Pessoa(string n, string c, string t, string e);   //construtor

    string getNome() const;      //retorna o nome
    string getCpf() const;       //retorna o cpf
    string getTelefone() const;  //retorna o telefone
    string getEmail() const;     //retorna o email
    
    virtual ~Pessoa() {}    //destrutor virtual faz que o destrutor correto seja chamado nas subclasses

    
    
    virtual void exibirInfo() = 0;      //metodo virtual puro obriga Dono e Usuario a terem sua propria versao
};