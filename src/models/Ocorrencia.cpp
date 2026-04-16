#include <string>
#include <iostream>
#include "Ocorrencia.h"
using namespace std;
Ocorrencia::Ocorrencia(int id, string data, string stats, Animal* bicho, Localizacao* loc){ //contructor completo, que recebe as infos e as coloca nas respectivas variaveis
    Id = id;
    dataDesaparecimento = data;
    status = stats;
    animal = bicho;
    localizacao = loc;
}

int Ocorrencia::getId(){ //retorna os valores do devido atributo 
    return Id;
}
string Ocorrencia::getData(){
    return dataDesaparecimento;
}
string Ocorrencia::getStatus(){
    return status;
}
Animal* Ocorrencia::getAnimal(){
    return animal;
}
Localizacao* Ocorrencia::getLocalizacao(){
    return localizacao;
}

void Ocorrencia::marcarEncontrado(){
    status = "ENCONTRADO";
}

void Ocorrencia::exibir(){
    cout << "Informacoes da Ocorrencia:" << endl;
    cout << "Id: " << getId() << endl; 
    cout << "Data do Desaparecimento: " << getData() << endl;
    cout << "Status da Ocorrencia: " << getStatus() << endl;
    cout << "Informacoes do animal: " << endl;
    animal-> exibir();
    cout << "Area | Local: " << endl;
    localizacao-> exibir();
}