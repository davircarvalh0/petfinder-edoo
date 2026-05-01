#ifndef ANIMAL_H
#define ANIMAL_H

#include <string>

using namespace std;

class Animal {
private:
    string nome;
    string cor;
    float peso;
    int idade;

public:
    Animal(const string& nome,
           const string& cor,
           float peso,
           int idade);

    // Getters
    string getNome() const;
    string getCor() const;
    float getPeso() const;
    int getIdade() const;

    // Setters
    void setNome(const string& nome);
    void setCor(const string& cor);
    void setPeso(float peso);
    void setIdade(int idade);

    // Metodo abstrato — cada animal implementa o seu
    virtual void exibir() const = 0;

    // Destrutor virtual (boa pratica com heranca)
    virtual ~Animal() {}
};

#endif // ANIMAL_H