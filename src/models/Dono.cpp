#include "Dono.h"
#include "Avistamento.h"  //para chamar av->exibir()
#include <iostream>

Dono::Dono(std::string n, std::string c, std::string t, std::string e, std::string end)
    : Pessoa(n, c, t, e) {
    endereco = end;
}

void Dono::cadastrarAnimal(Animal* a) {
    std::cout << "Animal cadastrado!" << std::endl;
}

void Dono::listarAnimais() {
    std::cout << "Listando animais pelo banco de dados..." << std::endl;
}

void Dono::exibirInfo() {
    std::cout << "Dono: " << getNome() << " | Endereco: " << endereco << std::endl;
}

void Dono::notificarAvistamento(Avistamento* av) {
    std::cout << "Novo avistamento do seu pet!" << std::endl;
    av->exibir();
}