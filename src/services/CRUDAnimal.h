#ifndef CRUDANIMAL_H
#define CRUDANIMAL_H
#include "../models/Animal.h"
#include "../database/Database.h"
#include <string>
using namespace std;
class CRUDAnimal {
private:
    Database* db; //referência do banco de dados
public:
//construtor
    CRUDAnimal(Database* database);
//C:insere um animal no banco vinculado a um dono
    bool cadastrar(Animal* pet, const string& donoId, const string& tipo);
    bool buscarPorId(int id);
    string listarFeed();
    bool listarTodos(); //R: lista todos os animais cadastrados
    bool listarPorDono(int donoId);//R: lista todos os animais de um dono especifico
    bool atualizar(int id, const string& novaFoto, float novoPeso); //U: atualiza a foto e o peso do animal
    bool deletar(int id); //D: remove um animal do banco
};
#endif