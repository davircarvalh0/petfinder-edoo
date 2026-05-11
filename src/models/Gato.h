
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
    bool usaColeira; // true = usa, false = nao usa
    bool ehCastrado;  // true = castrado, false = nao castrado
public:
//recebe os dados de Animal + os especificos de Gato
    Gato(const std::string& n, const std::string& c, float p, int i,
         const std::string& rc, const std::string& pel, bool col, bool cast, 
         const std::string& f);
//getters especificos de Gato
    string getRaca() const;
    string getPelagem() const;
    bool getUsaColeira() const;
    bool getEhCastrado() const;
//setters especificos de Gato
    void setRaca(const std::string& r);
    void setPelagem(const std::string& p);
    void setUsaColeira(bool u);
    void setEhCastrado(bool e);
//retorna uma string descritiva das caracteristicas visuais do gato
//pode ser util para exibir num mapa ou em listagens rapidas
    string identificar() const;
    void exibir() const override;
};
#endif