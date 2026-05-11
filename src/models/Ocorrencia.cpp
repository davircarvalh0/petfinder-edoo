//implementa as funçoes de ocorrencia.h e os comentario com o que cada funçao faz foi feito apenas na .h para poupar tempo
#include <string>
#include <iostream>
#include <algorithm>
#include <cctype>
#include "Ocorrencia.h"
using namespace std;
Ocorrencia::Ocorrencia(int id, string data, string stats, Animal* bicho, Localizacao* loc)
    : id(id), dataDesaparecimento(data), status(stats), animal(bicho), localizacao(loc) {} //constructor completo, que recebe as infos e as coloca nas respectivas variaveis

int Ocorrencia::getId() const { //retorna os valores do devido atributo 
    return id;
}
string Ocorrencia::getData() const {
    return dataDesaparecimento;
}
string Ocorrencia::getStatus() const {
    return status;
}
Animal* Ocorrencia::getAnimal() const {
    return animal;
}
Localizacao* Ocorrencia::getLocalizacao() const{
    return localizacao;
}

void Ocorrencia::marcarEncontrado() {
    status = "ENCONTRADO";
}

void Ocorrencia::exibir() const {
    cout << "Informacoes da Ocorrencia:" << endl;
    cout << "Id: " << getId() << endl; 
    cout << "Data do Desaparecimento: " << getData() << endl;
    cout << "Status da Ocorrencia: " << getStatus() << endl;
    cout << "Informacoes do animal: " << endl;
    animal-> exibir();
    cout << "Area | Local: " << endl;
    localizacao-> exibir();
}