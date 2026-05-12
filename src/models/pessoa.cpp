#include "Pessoa.h"

Pessoa::Pessoa(string n, string c, string t, string e) //construtor
    : nome(n), cpf(c), telefone(t), email(e) {}

//retornam o valor de cada atributo protegido
string Pessoa::getNome() const { return nome; }
string Pessoa::getCpf() const { return cpf; }
string Pessoa::getTelefone() const { return telefone; }
string Pessoa::getEmail() const { return email; }