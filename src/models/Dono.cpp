#include "Dono.h"
#include <iostream>

Dono::Dono(std::string n, std::string c, std::string t, std::string e, std::string end) : Pessoa(n, c, t, e) {
    endereco = end;
}

void Dono::cadastrarAnimal() {
    std::cout << "Cadastrando animal...\n";
}

void Dono::listarAnimais() {
    std::cout << "Listando animais...\n";
}

void Dono::exibirInfo() {
    std::cout << "Dono: " << getNome() << " | Endereco: " << endereco << "\n";
}

void Dono::notificarAvistamento() {
    std::cout << "Avistamento notificado!\n";
}