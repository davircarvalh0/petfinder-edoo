#include "Usuario.h"
#include <iostream>

Usuario::Usuario(std::string n, std::string c, std::string t, std::string e, std::string data)
    : Pessoa(n, c, t, e) {
    dataCadastro = data;
}

void Usuario::reportarAvistamento(Avistamento* av) {
    std::cout << "Avistamento registrado!" << std::endl;
}

void Usuario::exibirInfo() {
    std::cout << "Usuario: " << getNome() << " | Data de cadastro: " << dataCadastro << std::endl;
}

void Usuario::buscarAnimais() {
    std::cout << "Buscando animais perdidos na sua area..." << std::endl;
}