//implementa os void set e getters do arquivo localizaçao.h
#include <cmath>
#include <iostream>
#include "Localizacao.h"
using namespace std;
Localizacao::Localizacao(){ //contrutor padrao, mantem as variaveis iguais a 0 ou "nada"
    latitude = 0;
    longitude = 0;
    bairro = "Não informado";
    referencia = "Nenhuma";
}   
Localizacao::Localizacao(double lat, double longi, string b, string ref) { //construtor completo, recebe os valores das variaveis e atribui a elas
    latitude   = lat;
    longitude  = longi;
    bairro     = b;
    referencia = ref;
}
//get
double Localizacao::getLatitude() const { //retornam os valorres dos atributos privados
    return latitude;
}
double Localizacao::getLongitude() const {
    return longitude;
}
string Localizacao::getBairro() const {
    return bairro;
}
string Localizacao::getReferencia() const {
    return referencia;
}
//set
void Localizacao::setLatitude(double lat){ // alteram os valores dos atributos privados
    latitude = lat;
}
void Localizacao::setLongitude(double longi){
    longitude = longi;
}
void Localizacao::setBairro(string b){
    bairro = b;
}
void Localizacao::setReferencia(string ref){
    referencia = ref;
}

//print
void Localizacao::exibir() const {
    cout << "Bairro: " << bairro     << endl;
    cout << "Referencia: " << referencia << endl;
    cout << "Latitude: " << latitude   << endl;
    cout << "Longitude: " << longitude  << endl;
}