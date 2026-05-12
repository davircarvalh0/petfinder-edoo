#include "Dono.h"
#include "Avistamento.h"  //para chamar av->exibir()
#include <iostream>

Dono::Dono(string n, string c, string t, string e, string end)
    : Pessoa(n, c, t, e), 
    endereco(end) {}
   


void Dono::cadastrarAnimal(Animal* a) {
    (void)a;
    cout << "Animal cadastrado!" << endl;
}

void Dono::listarAnimais() {
    cout << "Listando animais pelo banco de dados..." << endl;
}

void Dono::exibirInfo() {
    cout << "Dono: " << getNome() << " | Endereco: " << endereco << endl;
}

void Dono::notificarAvistamento(Avistamento* av) {
    cout << "Novo avistamento do seu pet!" << endl;
    av->exibir();
}