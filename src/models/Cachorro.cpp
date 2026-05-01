Cachorro.cpp 

#include "Cachorro.h"
#include <iostream>

Cachorro::Cachorro(const std::string& nome,
                   const std::string& cor,
                   float peso,
                   int idade,
                   const std::string& raca,
                   const std::string& porte,
                   bool usaColeira)
    : Animal(nome, cor, peso, idade),
      raca(raca),
      porte(porte),
      usaColeira(usaColeira)
{}

// Getters
std::string Cachorro::getRaca() const { return raca; }
std::string Cachorro::getPorte() const { return porte; }
bool Cachorro::getUsaColeira() const { return usaColeira; }

// Setters
void Cachorro::setRaca(const std::string& r) { raca = r; }
void Cachorro::setPorte(const std::string& p) { porte = p; }
void Cachorro::setUsaColeira(bool c) { usaColeira = c; }

std::string Cachorro::identificar() const {
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