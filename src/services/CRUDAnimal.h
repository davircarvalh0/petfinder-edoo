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
    string listarPorDonoId(const string& donoId); //R: lista animais vinculados a um dono (feed do dono)
    //U: atualiza os dados textuais de um animal/ocorrencia
    bool atualizarInfo(int id, const string& nome, const string& raca,const string& cor, const string& porte,const string& pelagem, const string& peso,const string& idade, const string& localizacao,const string& descricao);
    bool marcarEncontrado(int id); //U: altera o status para 'encontrado' na tabela de ocorrencias
};
#endif