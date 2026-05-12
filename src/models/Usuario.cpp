#include "Usuario.h"
#include <iostream>
using namespace std;

Usuario::Usuario(string n, string c, string t, string e, string data)   //construtor
    : Pessoa(n, c, t, e), dataCadastro(data) {}

void Usuario::reportarAvistamento(Avistamento* av) {
    std::cout << "Avistamento registrado!" << std::endl;       //persistencia real feita pelo CRUDUsuario
}

void Usuario::exibirInfo() {
    std::cout << "Usuario: " << getNome() << " | Data de cadastro: " << dataCadastro << std::endl;  //getNome() herdado de Pessoa
}

void Usuario::buscarAnimais() {
    std::cout << "Buscando animais perdidos na sua area..." << std::endl;
}