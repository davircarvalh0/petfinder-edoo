#ifndef ANIMAL_H
#define ANIMAL_H
#include <string>
using namespace std;
//classe abstrata base para todos os animais do sistema
class Animal {
private:
    string nome;
    string cor;
    float peso;
    int idade;
public:
//inicializa todos os atributos
//o "const string&" recebe a string sem copiar, mais eficiente
    Animal(const string& nome,
           const string& cor,
           float peso,
           int idade);
    //getters
    string getNome() const;
    string getCor() const;
    float getPeso() const;
    int getIdade() const;
    //setters
    void setNome(const string& nome);
    void setCor(const string& cor);
    void setPeso(float peso);
    void setIdade(int idade);
    //metodo abstrato, cada animal implementa o seu
    virtual void exibir() const = 0;
    //destrutor virtual 
    virtual ~Animal() {}
};
#endif 