#include <string>
#include "Localizacao.h"
#include "Ocorrencia.h"
#include "Usuario.h"
using namespace std;
class Avistamento {
private:
    int id; //id do avistamento 
    string data; //data de quando o pet perdido foi avistado
    string descricao; //observaçoes feitas pelos usuarios sobre onde viram o pet
    Usuario* usuario; //ponteiro pro usuario que fez o reportw
    Ocorrencia* ocorrencia; 
    Localizacao* localizacao;
public:
    Avistamento(int id, string data, string descricao, Usuario* usuario, Ocorrencia* ocorrencia, Localizacao* loc); //construtor completo
    int getId() const; //retorna o id de avistamento
    string getData() const; //retorna a data do reporte  
    string getDescricao() const; //retorna as observaçoes feitas pelo usuario
    Usuario* getUsuario() const; //retorna o ponteiro do usuario que reportou
    Ocorrencia* getOcorrencia() const; //rettorna o ponteiro da ocrrencia relacionada ao animal
    Localizacao* getLocalizacao() const; //retona a possivel localizaçao do pet 

    void exibir() const; //print
};