#ifndef ANIMAL_H
#define ANIMAL_H
#include <string>
using namespace std;
//classe abstrata base para todos os animais do sistema
class Animal {
protected:
    string nome;
    string cor;
    float peso;
    int idade;
    string foto;
    string localizacao;
    string descricao;
public:
//inicializa todos os atributos
    Animal() : nome(""), cor(""), peso(0.0f), idade(0), foto("") {}
    Animal(const std::string& nome, const std::string& cor, float peso, int idade, const std::string& foto); // construtor padrão
    
    virtual ~Animal() {} // destrutor virtual 
    //getters
    string getNome() const;
    string getCor() const;
    float getPeso() const;
    int getIdade() const;
    string getLocalizacao() const;
    string getDescricao() const;
    string getFoto() const;
    //setters
    void setNome(const string& n);
    void setCor(const string& c);
    void setPeso(float p);
    void setIdade(int i);
    void setFoto(const string& f);
    void setLocalizacao(const string& l);
    void setDescricao(const string& d);
    //metodo abstrato, cada animal implementa o seu
    virtual void exibir() const = 0;
};
#endif 