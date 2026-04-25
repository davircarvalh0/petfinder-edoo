//implementa as funçoes de avistamento.h e os comentario com o que cada funçao faz foi feito apenas na .h para poupar tempo
#include <iostream>
#include "Avistamento.h"
using namespace std;

Avistamento::Avistamento(int id, string data, string descricao, Usuario* usuario, Ocorrencia* ocorrencia, Localizacao* loc) {
    this->id = id;
    this->data = data;
    this->descricao = descricao;
    this->usuario = usuario;
    this->ocorrencia = ocorrencia;
    this->localizacao = loc;
}
int Avistamento::getId() { return id; } //to tentando deixar em uma linha diferente de como deixei em Ocorrencia e Localização
string Avistamento::getData() { return data; }
string Avistamento::getDescricao() { return descricao; }
Usuario* Avistamento::getUsuario() { return usuario; }
Ocorrencia* Avistamento::getOcorrencia() { return ocorrencia; }
Localizacao* Avistamento::getLocalizacao() { return localizacao; }

void Avistamento::exibir() {
    cout << "Avistamento ID : " << id << endl;
    cout << "Data           : " << data << endl;
    cout << "Descricao      : " << descricao << endl;
    cout << "Localizacao    : " << endl;
    localizacao->exibir();
    cout << "Ocorrencia ID  : " << ocorrencia->getId() << endl;
}