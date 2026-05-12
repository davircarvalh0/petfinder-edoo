#include "Usuario.h"
#include <iostream>
using namespace std;

Usuario::Usuario(string n, string c, string t, string e, string data)
    : Pessoa(n, c, t, e), dataCadastro(data) {}

void Usuario::reportarAvistamento(Avistamento* av) {
    (void)av;
    std::cout << "Avistamento registrado!" << std::endl;
}

void Usuario::exibirInfo() {
    std::cout << "Usuario: " << getNome() << " | Data de cadastro: " << dataCadastro << std::endl;
}

void Usuario::buscarAnimais() {
    std::cout << "Buscando animais perdidos na sua area..." << std::endl;
}