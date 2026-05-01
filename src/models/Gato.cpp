Gato.cpp 

#include "Gato.h"
#include <iostream>

Gato::Gato(const std::string& nome,
           const std::string& cor,
           float peso,
           int idade,
           const std::string& raca,
           const std::string& pelagem,
           bool ehCastrado)
    : Animal(nome, cor, peso, idade),
      raca(raca),
      pelagem(pelagem),
      ehCastrado(ehCastrado)
{}

// Getters
std::string Gato::getRaca() const { return raca; }
std::string Gato::getPelagem() const { return pelagem; }
bool Gato::getEhCastrado() const { return ehCastrado; }

// Setters
void Gato::setRaca(const std::string& r) { raca = r; }
void Gato::setPelagem(const std::string& p) { pelagem = p; }
void Gato::setEhCastrado(bool c) { ehCastrado = c; }

std::string Gato::identificar() const {
    std::string desc = "Gato " + raca + ", pelagem " + pelagem +
                       " e " + getCor();
    if (ehCastrado)
        desc += ", castrado";
    else
        desc += ", nao castrado";
    return desc;
}

void Gato::exibir() const {
    std::cout << "=== Perfil do Gato ===" << std::endl;
    std::cout << "Nome     : " << getNome()      << std::endl;
    std::cout << "Raca     : " << raca            << std::endl;
    std::cout << "Pelagem  : " << pelagem         << std::endl;
    std::cout << "Cor      : " << getCor()        << std::endl;
    std::cout << "Peso     : " << getPeso()       << " kg" << std::endl;
    std::cout << "Idade    : " << getIdade()      << " ano(s)" << std::endl;
    std::cout << "Castrado : " << (ehCastrado ? "Sim" : "Nao") << std::endl;
    std::cout << "Descricao: " << identificar()   << std::endl;
}