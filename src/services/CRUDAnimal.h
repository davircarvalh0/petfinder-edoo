#ifndef CRUDOANIMAL_H
#define CRUDANIMAL_H
#include "../models/Animal.h"
#include "../database/Database.h"
#include <string>
using namespace std;
class CRUDAnimal {
private:
    Database& db; //referência do banco de dados
public:
//construtor
    CRUDAnimal(Database& database);
//C:insere um animal no banco vinculado a um dono
    bool cadastrar(int donoId, const string& tipo, const string& nome,float peso, int idade, const string& cor,const string& raca, const string& foto,const string& porte, bool usaColeira,const string& pelagem, bool ehCastrado);
    bool buscarPorId(int id); //R: busca um animal especifico pelo id
    bool listarTodos(); //R: lista todos os animais cadastrados
    bool listarPorDono(int donoId);//R: lista todos os animais de um dono especifico
    bool atualizar(int id, const string& novaFoto, float novoPeso); //U: atualiza a foto e o peso do animal
    bool deletar(int id); //D: remove um animal do banco
};
#endif