#pragma once
#include "pessoa.h"
#include <string>
using namespace std;

class Animal;
class Avistamento;

class Dono : public Pessoa {

private:
    std::string endereco;

public:
    Dono(std::string n, std::string c, std::string t, std::string e, std::string end);

    ~Dono() {}

    string getEndereco() const { return endereco; }
    void setEndereco(const std::string& end) { endereco = end; }
    void cadastrarAnimal(Animal* a);
    void listarAnimais();
    void exibirInfo() override;
    void notificarAvistamento(Avistamento* av);
};