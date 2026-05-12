#pragma once
#include "Pessoa.h"
#include <string>
using namespace std;

class Avistamento;  //avisa que a classe existe sem precisar incluir o arquivo

class Usuario : public Pessoa {     //Usuario herda os atributos e metodos de Pessoa

private:
    string dataCadastro;    //data em que o usuario se cadastrou no sistema

public:
    Usuario(string n, string c, string t, string e, string data);   //construtor

    ~Usuario() {}   //destrutor

    void reportarAvistamento(Avistamento* av);      //recebe ponteiro para Avistamento e registra no sistema

    void exibirInfo() override;     //override q implementa a propria do metodo virtual puro de Pessoa

    void buscarAnimais();       //busca animais perdidos na area do usuario
};