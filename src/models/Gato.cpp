//implementacao dos metodos da classe Gato
#include "Gato.h"
#include <iostream>
using namespace std;
//construtor
Gato::Gato(const std::string& n, const std::string& c, float p, int i,
           const std::string& rc, const std::string& pel, bool col, bool cast, 
           const std::string& f) 
    : Animal() // chama o construtor padrão da base
{
    // atribui os valores às variáveis da classe base 
    nome = n;
    cor = c;
    peso = p;
    idade = i;
    foto = f;
    // atribui os valores às variáveis da subclasse
    raca = rc;
    pelagem = pel;
    usaColeira = col;
    ehCastrado = cast;
}
//getters
string Gato::getRaca()       const { return raca;       }
string Gato::getPelagem()    const { return pelagem;    }
bool   Gato::getEhCastrado() const { return ehCastrado; }
bool Gato::getUsaColeira() const { return usaColeira; }
//setters
void Gato::setRaca(const string& r)    { raca       = r; }
void Gato::setPelagem(const string& p) { pelagem    = p; }
void Gato::setEhCastrado(bool c)       { ehCastrado = c; }
void Gato::setUsaColeira(bool u) { usaColeira = u; }
//retorna uma descricao textual rapida do gato
string Gato::identificar() const {
    string desc = "Gato " + raca + ", pelagem " + pelagem + " e " + getCor();
    desc += (ehCastrado ? ", castrado" : ", nao castrado");
    return desc;
}
void Gato::exibir() const { //famoso print
    cout << "=== Perfil do Gato ===" << endl;
    cout << "Nome     : " << getNome()                          << endl;
    cout << "Raca     : " << raca                               << endl;
    cout << "Pelagem  : " << pelagem                            << endl;
    cout << "Cor      : " << getCor()                           << endl;
    cout << "Peso     : " << getPeso()  << " kg"                << endl;
    cout << "Idade    : " << getIdade() << " ano(s)"            << endl;
    cout << "Castrado : " << (ehCastrado ? "Sim" : "Nao")      << endl;
    cout << "Descricao: " << identificar()                      << endl;
}