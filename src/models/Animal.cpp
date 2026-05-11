#include "Animal.h"
#include <iostream>
using namespace std;
//implementacao dos metodos da classe Animal
Animal::Animal(const string& nome, const string& cor, float peso, int idade, const string& foto) 
: nome(nome), cor(cor), peso(peso), idade(idade), foto(foto), localizacao(""), descricao("") {}


//getters
string Animal::getNome() const { return nome; }
string Animal::getCor()  const { return cor;  }
float Animal::getPeso()  const { return peso; }
int Animal::getIdade()   const { return idade; }
string Animal::getFoto() const { return foto; }
string Animal::getLocalizacao() const { return localizacao; }
string Animal::getDescricao() const { return descricao; }
//setters
void Animal::setNome(const string& n) { nome = n; }
void Animal::setCor(const string& c)  { cor = c;  }
void Animal::setPeso(float p)         { peso = p; }
void Animal::setIdade(int i)          { idade = i; }
void Animal::setFoto(const string& f) { foto = f; }
void Animal::setLocalizacao(const string& l) { localizacao = l; }
void Animal::setDescricao(const string& d) { descricao = d; }