// declaração das classes de localização
#ifndef LOCALIZACAO_H
#define LOCALIZACAO_H
#include <string>
#include <iostream>
using namespace std;
class Localizacao{
    private: // variaveis privadas da class localização
    double latitude, longitude;
    string bairro, referencia;
    public:
    Localizacao(); // contrutor
    Localizacao(double lat, double longi, string bairro, string referencia);
    double getLatitude() const; // os get lem os valores fora da classe
    double getLongitude() const;
    string getBairro() const;
    string getReferencia() const;
    void setLatitude(double lat); // os set permite alterar os valores fora da classe
    void setLongitude(double longi);
    void setBairro(string bairro);
    void setReferencia(string referenia);
    void exibir() const; //exibe as informaçoes no terminal
};
#endif 
