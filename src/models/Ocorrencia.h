//declaração das classes de ocorrencia
#ifndef OCORRENCIA_H
#define OCORRENCIA_H
#include <string>
#include "Localizacao.h"
#include "Animal.h" //ainda nao foi criada (remover dps)

class Animal;
class Localizacao;

class Ocorrencia{
    private:
    int id; //id da ocorrenncia
    std::string dataDesaparecimento, status; //data do ocorrido e se ta ja achou ou ainda nn //RAPAZIADA, PFVR SEMPRE USAR COMO PERDIDO/ENCONTRADO PRARA QUEM FOR MEXER NO MEU CODIGO
    Animal* animal; //ainda vai ser criada (vou remover esse comentario dps)
    Localizacao* localizacao; //ponteiro pra area que o dono acha que o bicho ta
    public:
    Ocorrencia(int id, std::string data, std::string stats, Animal* bicho, Localizacao* loc); //contructor, ele tbm vai servir como settter
    ~Ocorrencia() {}

    int getId() const; //chama o id
    std::string getData() const; //chama a data
    std::string getStatus() const; //chama o status de perdido ou encontrado
    Animal* getAnimal() const; //mostra o animal perdido
    Localizacao* getLocalizacao() const; //mostra a localização informada pelo dono do pet
    void exibir() const; 
    void marcarEncontrado(); //update do status
};
#endif
