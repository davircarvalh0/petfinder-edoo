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
    int getId(); //retorna o id de avistamento
    string getData(); //retorna a data do reporte  
    string getDescricao(); //retorna as observaçoes feitas pelo usuario
    Usuario* getUsuario(); //retorna o ponteiro do usuario que reportou
    Ocorrencia* getOcorrencia(); //rettorna o ponteiro da ocrrencia relacionada ao animal
    Localizacao* getLocalizacao(); //retona a possivel localizaçao do pet 
    void exibir(); //print
};