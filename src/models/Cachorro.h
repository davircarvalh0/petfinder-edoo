Cachorro.h 

#ifndef CACHORRO_H
#define CACHORRO_H

#include "Animal.h"
#include <string>

class Cachorro : public Animal {
private:
    std::string raca;
    std::string porte;   // "pequeno", "medio" ou "grande"
    bool usaColeira;

public:
    // Construtor
    Cachorro(const std::string& nome,
             const std::string& cor,
             float peso,
             int idade,
             const std::string& raca,
             const std::string& porte,
             bool usaColeira);

    // Getters
    std::string getRaca() const;
    std::string getPorte() const;
    bool getUsaColeira() const;

    // Setters
    void setRaca(const std::string& raca);
    void setPorte(const std::string& porte);
    void setUsaColeira(bool usaColeira);

    // Retorna uma descricao textual das caracteristicas visuais do animal
    std::string identificar() const;

    // Implementacao do metodo abstrato da classe Animal
    void exibir() const override;
};

#endif // CACHORRO_H