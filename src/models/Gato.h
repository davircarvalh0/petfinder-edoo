Gato.h

#ifndef GATO_H
#define GATO_H

#include "Animal.h"
#include <string>

class Gato : public Animal {
private:
    std::string raca;
    std::string pelagem;   // ex: "curta", "longa", "semi-longa"
    bool ehCastrado;

public:
    // Construtor
    Gato(const std::string& nome,
         const std::string& cor,
         float peso,
         int idade,
         const std::string& raca,
         const std::string& pelagem,
         bool ehCastrado);

    // Getters
    std::string getRaca() const;
    std::string getPelagem() const;
    bool getEhCastrado() const;

    // Setters
    void setRaca(const std::string& raca);
    void setPelagem(const std::string& pelagem);
    void setEhCastrado(bool ehCastrado);

    // Retorna uma descricao textual das caracteristicas visuais do animal
    std::string identificar() const;

    // Implementacao do metodo abstrato da classe Animal
    void exibir() const override;
};

#endif // GATO_H