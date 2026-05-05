
//subclasse de Animal que representa um cachorro
//herda os atributos comuns de Animal e adiciona os especificos
#ifndef CACHORRO_H
#define CACHORRO_H
#include "Animal.h"
#include <string>
using namespace std;
// "public Animal" significa que Cachorro herda tudo de Animal
class Cachorro : public Animal{
private:
    string raca;       // ex: "Labrador", "Vira-lata"
    string porte;      // "pequeno", "medio" ou "grande"
    bool usaColeira;   // true = usa coleira, false = nao usa
public:
//construtor completo, recebe os dados de Animal + os especificos de Cachorro
//": Animal(...)" no .cpp repassa os dados comuns para a classe mae
    Cachorro(const string& nome, const string& cor, float peso, int idade,
             const string& raca, const string& porte, bool usaColeira);
//getters especificos de Cachorro
    string getRaca()       const;
    string getPorte()      const;
    bool   getUsaColeira() const;
//setters especificos de Cachorro
    void setRaca(const string& raca);
    void setPorte(const string& porte);
    void setUsaColeira(bool usaColeira);
//retorna uma string descritiva das caracteristicas visuais do cachorro
//util para exibir no mapa ou em listagens rapidas
    string identificar() const;
    void exibir() const override;
};
#endif