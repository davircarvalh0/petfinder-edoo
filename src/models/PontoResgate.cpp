//implementacao dos metodos da classe PontoResgate
#include "PontoResgate.h"
#include <iostream>
using namespace std;
//recebe todas as informacoes e atribui aos respectivos atributos de localizacao e um ponteiro que aponta para um objeto ja existentena memoria, nao faz uma copia
PontoResgate::PontoResgate(string n, string t, string tel, Localizacao* loc){   
    nome = n; 
    tipo = t; 
    telefone = tel; 
    localizacao = loc;
}
//getters
string       PontoResgate::getNome()        { return nome;        }
string       PontoResgate::getTipo()        { return tipo;        }
string       PontoResgate::getTelefone()    { return telefone;    }
Localizacao* PontoResgate::getLocalizacao() { return localizacao; }
//setters
void PontoResgate::setNome(string n)       { nome        = n;   }
void PontoResgate::setTipo(string t)       { tipo        = t;   }
void PontoResgate::setTelefone(string tel) { telefone    = tel; }
void PontoResgate::setLocalizacao(Localizacao* loc) { localizacao = loc; }
void PontoResgate::exibir() {
    cout << "Ponto de Resgate"             << endl;
    cout << "Nome: " << nome          << endl;
    cout << "Tipo: " << tipo          << endl;
    cout << "Telefone: " << telefone      << endl;
    cout << "Localizacao:"                 << endl;
    localizacao->exibir(); //chama localizacao->exibir() via ponteiro para mostrar o endereco completo do local
}