#pragma once
#include "Pessoa.h"
#include <string>
using namespace std;

class Animal;       //avisa que a classe existe sem precisar incluir o arquivo
class Avistamento;  //evita dependencia circular entre os headers

class Dono : public Pessoa {    //Dono herda os atributos e metodos de Pessoa

private:
    std::string endereco;   //endereco residencial do dono

public:
    Dono(std::string n, std::string c, std::string t, std::string e, std::string end);  //construtor completo

    ~Dono() {}  //destrutor

    string getEndereco() const { return endereco; }
    void setEndereco(const std::string& end) { endereco = end; }
    void cadastrarAnimal(Animal* a);    //recebe ponteiro para Animal e registra no sistema
    void listarAnimais();           //exibe os animais do dono via banco de dados
    void exibirInfo() override;     //override implementa propria do metodo virtual puro de Pessoa
    void notificarAvistamento(Avistamento* av);     //recebe ponteiro para Avistamento e notifica o dono
};