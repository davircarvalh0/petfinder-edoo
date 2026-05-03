//declaração das classes de ocorrencia
#ifndef OCORRENCIA.H
#define OCORRENCIA.H
#include <string>
#include "Localizacao.h"
#include "Animal.h" //ainda nao foi criada (remover dps)
using namespace std;
class Ocorrencia{
    private:
    int Id; //id da ocorrenncia
    string dataDesaparecimento, status; //data do ocorrido e se ta ja achou ou ainda nn //RAPAZIADA, PFVR SEMPRE USAR COMO PERDIDO/ENCONTRADO PRARA QUEM FOR MEXER NO MEU CODIGO
    Animal* animal; //ainda vai ser criada (vou remover esse comentario dps)
    Localizacao* localizacao; //ponteiro pra area que o dono acha que o bicho ta
    public:
    Ocorrencia(int id, string data, string stats, Animal* bicho, Localizacao* loc ); //contructor, ele tbm vai servir como settter
    int getId(); //chama o id
    string getData(); //chama a data
    string getStatus(); //chama o status de perdido ou encontrado
    Animal* getAnimal(); //mostra o animal perdido
    Localizacao* getLocalizacao(); //mostra a localização informada pelo dono do pet
    void exibir(); 
    void marcarEncontrado(); //update do status
};
#endif