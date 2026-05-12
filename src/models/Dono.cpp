#include "Dono.h"
#include "Avistamento.h"  //para chamar av->exibir()
#include <iostream>

Dono::Dono(string n, string c, string t, string e, string end)     //construtor
    : Pessoa(n, c, t, e), 
    endereco(end) {}
   


void Dono::cadastrarAnimal(Animal* a) {
    cout << "Animal cadastrado!" << endl;   //persistencia real feita pelo CRUDDono
}

void Dono::listarAnimais() {
    cout << "Listando animais pelo banco de dados..." << endl;  //busca real feita pelo CRUDDono
}

void Dono::exibirInfo() {
    cout << "Dono: " << getNome() << " | Endereco: " << endereco << endl; //getNome() herdado de Pessoa
}

void Dono::notificarAvistamento(Avistamento* av) {
    cout << "Novo avistamento do seu pet!" << endl;
    av->exibir();       //"->" acessa metodo de um ponteiro
}