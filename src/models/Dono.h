#pragma once
#include "Pessoa.h"
#include <string>

class Animal;
class Avistamento;

class Dono : public Pessoa {

private:
    std::string endereco;

public:
    Dono(std::string n, std::string c, std::string t, std::string e, std::string end);

    ~Dono() {}

    void cadastrarAnimal(Animal* a);
    void listarAnimais();
    void exibirInfo() override;
    void notificarAvistamento(Avistamento* av);
};