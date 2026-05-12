#pragma once
#include "pessoa.h"
#include <string>
using namespace std;

class Avistamento; 

class Usuario : public Pessoa {

private:
    string dataCadastro;

public:
    Usuario(string n, string c, string t, string e, string data);

    ~Usuario() {}

    void reportarAvistamento(Avistamento* av);

    void exibirInfo() override;

    void buscarAnimais();
};