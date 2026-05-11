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
    string pelagem;    // "curta", "media" ou "grande"
    bool usaColeira;   // true = usa coleira, false = nao usa
    bool ehCastrado;  
public:
//construtor completo, recebe os dados de Animal + os especificos de Cachorro
//": Animal(...)" no .cpp repassa os dados comuns para a classe mae    
    Cachorro(const std::string& n, const std::string& c, float p, int i,
             const std::string& rc, const std::string& pt, const std::string& pel, bool col, 
             bool cast, const std::string& f);
//getters especificos de Cachorro
    string getRaca() const;
    string getPorte() const;
    string getPelagem() const; 
    bool getUsaColeira() const;
    bool getEhCastrado() const;
//setters especificos de Cachorro
    void setRaca(const std::string& r);
    void setPorte(const std::string& p);
    void setPelagem(const string& p);
    void setUsaColeira(bool u);
    void setEhCastrado(bool e);
//retorna uma string descritiva das caracteristicas visuais do cachorro
//util para exibir no mapaa ou em listagens rapidas
    string identificar() const;
    void exibir() const override;
};
#endif