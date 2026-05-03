
//subclasse de Animal que representa um gato
//herda os atributos comuns de Animal e adiciona os especificos
#ifndef GATO_H
#define GATO_H
#include "Animal.h"
#include <string>
using namespace std;
//herda tudo de Animal
class Gato : public Animal {
private:
    string raca;      // ex: "Persa", "Siames", "SRD"
    string pelagem;   // ex: "curta", "longa", "semi-longa"
    bool ehCastrado;  // true = castrado, false = nao castrado
public:
//recebe os dados de Animal + os especificos de Gato
    Gato(const string& nome, const string& cor, float peso, int idade,
         const string& raca, const string& pelagem, bool ehCastrado);
//getters especificos de Gato
    string getRaca()       const;
    string getPelagem()    const;
    bool   getEhCastrado() const;
//setters especificos de Gato
    void setRaca(const string& raca);
    void setPelagem(const string& pelagem);
    void setEhCastrado(bool ehCastrado);
//retorna uma string descritiva das caracteristicas visuais do gato
//pode ser util para exibir num mapa ou em listagens rapidas
    string identificar() const;
    void exibir() const override;
};
#endif