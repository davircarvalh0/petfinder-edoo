#pragma once
#include "Pessoa.h"
#include <vector>
#include <string>

class Animal;

class Dono : public Pessoa {
private:
    std::string endereco;
    std::vector<Animal*> animais;

public:
    Dono(std::string n, std::string c, std::string t, std::string e, std::string end);
    
    void cadastrarAnimal();
    void listarAnimais();
    void exibirInfo(); 
    void notificarAvistamento();
};