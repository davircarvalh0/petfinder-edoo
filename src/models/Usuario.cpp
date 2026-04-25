#include "Usuario.h"
#include <iostream>

Usuario::Usuario(std::string n, std::string c, std::string t, std::string e, std::string data) : Pessoa(n, c, t, e) {
    dataCadastro = data;
}

void Usuario::reportarAvistamento() {
    std::cout << "Avistamento reportado...\n";
}

void Usuario::exibirInfo() {
    std::cout << "Usuario: " << getNome() << " | Data de cadastro: " << dataCadastro << "\n";
}

void Usuario::buscarAnimais() {
    std::cout << "Buscando animais...\n";
}