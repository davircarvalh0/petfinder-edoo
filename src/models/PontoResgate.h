//declaracao da classe PontoResgate
//representa locais de apoio como clinicas, ONGs e castradores que podem ajudar a encontrar ou cuidar de animais perdido
#pragma once
#include <string>
#include "Localizacao.h"
using namespace std;
class PontoResgate {
private:
    string nome;              // nome do local ex: "Clinica Vet Recife"
    string tipo;              // tipo do local ex: "Clinica", "ONG", "Castrador"
    string telefone;          // telefone de contato ex: "(81) 99999-9999"
    Localizacao* localizacao; // ponteiro para a localizacao do ponto de resgate
public:
//cria o ponto de resgate com todas as informacoes
    PontoResgate(string nome, string tipo, string telefone, Localizacao* loc);
//getters
    string getNome();
    string getTipo();
    string getTelefone();
    Localizacao* getLocalizacao(); 
//setters
    void setNome(string nome);
    void setTipo(string tipo);
    void setTelefone(string telefone);
    void setLocalizacao(Localizacao* loc);
    void exibir(); //print
};