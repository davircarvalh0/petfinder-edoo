//implementacao dos metodos da classe Gato
#include "Gato.h"
#include <iostream>
using namespace std;
//construtor
Gato::Gato(const string& nome, const string& cor, float peso, int idade,const string& raca, const string& pelagem, bool ehCastrado): Animal(nome, cor, peso, idade, ""), raca(raca),pelagem(pelagem),ehCastrado(ehCastrado){}
//getters
string Gato::getRaca()       const { return raca;       }
string Gato::getPelagem()    const { return pelagem;    }
bool   Gato::getEhCastrado() const { return ehCastrado; }
//setters
void Gato::setRaca(const string& r)    { raca       = r; }
void Gato::setPelagem(const string& p) { pelagem    = p; }
void Gato::setEhCastrado(bool c)       { ehCastrado = c; }
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