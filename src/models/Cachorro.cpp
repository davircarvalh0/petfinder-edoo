#include "Cachorro.h"
#include <iostream>
using namespace std;
//implementacao dos metodos da classe Cachorro
// chama o construtor da classe mae e obrigatorio para inicializar os atributos herdados de Animal
Cachorro::Cachorro(const std::string& n, const std::string& c, float p, int i, 
                   const std::string& rc, const std::string& pt, const std::string& pel, 
                   bool col, bool cast, const std::string& f) 
    : Animal() // inicializa a base
{
    nome = n;
    cor = c;
    peso = p;
    idade = i;
    raca = rc;
    porte = pt;
    pelagem = pel;
    usaColeira = col;
    ehCastrado = cast;
    foto = f;
}
//getters
string Cachorro::getRaca() const { return raca; }
string Cachorro::getPorte() const { return porte; }
bool Cachorro::getUsaColeira() const { return usaColeira; }
string Cachorro::getPelagem() const { return pelagem; }
bool Cachorro::getEhCastrado() const { return ehCastrado; }
//setters
void Cachorro::setRaca(const std::string& r) { raca = r; }
void Cachorro::setPorte(const std::string& p) { porte = p; }
void Cachorro::setUsaColeira(bool c) { usaColeira = c; }
std::string Cachorro::identificar() const { //retorna uma descricao textual rapida do cachorro
    std::string desc = "Cachorro " + raca + ", porte " + porte +
                       ", pelagem " + getCor();
    if (usaColeira)
        desc += ", usa coleira";
    else
        desc += ", sem coleira";
    return desc;
}
void Cachorro::exibir() const {
    std::cout << "=== Perfil do Cachorro ===" << std::endl;
    std::cout << "Nome    : " << getNome()   << std::endl;
    std::cout << "Raca    : " << raca         << std::endl;
    std::cout << "Porte   : " << porte        << std::endl;
    std::cout << "Cor     : " << getCor()     << std::endl;
    std::cout << "Peso    : " << getPeso()    << " kg" << std::endl;
    std::cout << "Idade   : " << getIdade()   << " ano(s)" << std::endl;
    std::cout << "Coleira : " << (usaColeira ? "Sim" : "Nao") << std::endl;
    std::cout << "Descricao: " << identificar() << std::endl;
}