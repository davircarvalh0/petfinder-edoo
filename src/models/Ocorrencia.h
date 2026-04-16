#include <string>
#include "Localizacao.h"
#include "Animal.h" //ainda nao foi criada (remover dps)
using namespace std;
class Ocorrencia{
    private:
    int Id; //id da ocorrenncia
    string dataDesaparecimento, status; //data do ocorrido e se ta ja achou ou ainda nn //RAPAZIADA, PFVR SEMPRE USAR COMO PERDIDO/ENCONTRADO PRARA QUEM FOR MEXER NO MEU CODIGO
    Animal* animal; //ainda vai ser criada (vou remover esse comentario dps)
    Localizacao* localizacao; //proprio nome ja diz
    public:
    Ocorrencia(int id, string data, string stats, Animal* bicho, Localizacao* loc ); //contructor, ele tbm vai servir como settter
    int getId();
    string getData();
    string getStatus();
    Animal* getAnimal();
    Localizacao* getLocalizacao();
    void exibir(); 
    void marcarEncontrado();
};