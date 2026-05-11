#include "CRUDAnimal.h"
#include <iostream>
#include "../models/Cachorro.h" 
#include "../models/Gato.h"
#include <vector>

using namespace std;
//construtor
CRUDAnimal::CRUDAnimal(Database* database) : db(database) {}
//create
bool CRUDAnimal::cadastrar(Animal* pet, const string& donoId, const string& tipo) {
    vector<string> parametros;
    parametros.push_back(donoId);
    parametros.push_back(tipo);
    parametros.push_back(pet->getNome());
    parametros.push_back(to_string(pet->getPeso()));
    parametros.push_back(to_string(pet->getIdade()));
    parametros.push_back(pet->getCor());

    if (tipo == "cachorro") {
        Cachorro* dog = static_cast<Cachorro*>(pet);
        parametros.push_back(dog->getRaca());
        parametros.push_back(dog->getPorte());
        parametros.push_back(dog->getUsaColeira() ? "1" : "0");
        parametros.push_back(dog->getPelagem());
        parametros.push_back(dog->getEhCastrado() ? "1" : "0");
    } else {
        Gato* cat = static_cast<Gato*>(pet);
        parametros.push_back(cat->getRaca());
        parametros.push_back(""); // Gato não tem porte no BD
        parametros.push_back(cat->getUsaColeira() ? "1" : "0");
        parametros.push_back(cat->getPelagem());
        parametros.push_back(cat->getEhCastrado() ? "1" : "0");
    }

    parametros.push_back(pet->getLocalizacao());
    parametros.push_back(pet->getDescricao());
    parametros.push_back(pet->getFoto());

    bool sucesso = db->executarPreparado(
        "INSERT INTO animais (dono_id, tipo, nome, peso, idade, cor, raca, porte, usa_coleira, pelagem, eh_castrado, localizacao, descricao, foto) "
        "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)",
        parametros
    );

    if (sucesso) cout << "Animal cadastrado com sucesso!" << endl;
    else cout << "Erro ao cadastrar animal: " << db->getMensagemErro() << endl;
    return sucesso;
}
// método para a api
string CRUDAnimal::listarFeed() {
    string json = "[";
    
    // 1. GARANTA que o id está aqui no SELECT!
    string sql = "SELECT id, nome, tipo, raca, cor, porte, pelagem, idade, peso, usa_coleira, eh_castrado, localizacao, descricao, foto FROM animais";

    try {
        db->consultar(sql, {}, [&](const Database::Linha& linha) {
            if (json.length() > 1) json += ",";
            
            json += "{";
            // Usamos um pequeno truque para evitar o erro 500:
            // Verificamos se a coluna existe antes de dar o .at()
            auto pegarDado = [&](string coluna) {
                return (linha.find(coluna) != linha.end()) ? linha.at(coluna) : "ERRO_COLUNA_FALTANDO";
            };

            json += "\"id\":\"" + pegarDado("id") + "\",";
            json += "\"nome\":\"" + pegarDado("nome") + "\",";
            json += "\"tipo\":\"" + pegarDado("tipo") + "\",";
            json += "\"raca\":\"" + pegarDado("raca") + "\",";
            json += "\"cor\":\"" + pegarDado("cor") + "\",";
            json += "\"porte\":\"" + pegarDado("porte") + "\",";
            json += "\"pelagem\":\"" + pegarDado("pelagem") + "\",";
            json += "\"idade\":\"" + pegarDado("idade") + "\",";
            json += "\"peso\":\"" + pegarDado("peso") + "\",";
            json += "\"usa_coleira\":\"" + pegarDado("usa_coleira") + "\",";
            json += "\"eh_castrado\":\"" + pegarDado("eh_castrado") + "\",";
            json += "\"localizacao\":\"" + pegarDado("localizacao") + "\",";
            json += "\"descricao\":\"" + pegarDado("descricao") + "\",";
            json += "\"foto\":\"" + pegarDado("foto") + "\"";
            json += "}";
        });
    } catch (const std::exception& e) {
        std::cout << "CRITICAL ERROR no listarFeed: " << e.what() << std::endl;
    }

    json += "]";
    return json;
}


//read por id
bool CRUDAnimal::buscarPorId(int id) {
    bool encontrou = false;
    db->consultar(
        "SELECT * FROM animais WHERE id = ?;", 
        {to_string(id)}, 
        [&](const Database::Linha& linha) {
            encontrou = true;
            cout << "=== Animal Encontrado ===" << endl;
            cout << "ID: "   << linha.at("id") << endl;
            cout << "Nome: " << linha.at("nome") << " (" << linha.at("tipo") << ")" << endl;
            cout << "Raça: " << linha.at("raca") << endl;
            cout << "Peso: " << linha.at("peso") << " kg | Idade: " << linha.at("idade") << " anos" << endl;
        }
    );
    if (!encontrou) cout << "Nenhum animal encontrado com ID: " << id << endl;
    return encontrou;
}
//read geral
bool CRUDAnimal::listarTodos() {
    int contador = 0;
    db->consultar(
        "SELECT * FROM animais ORDER BY nome;", 
        {}, 
        [&](const Database::Linha& linha) {
            contador++;
            cout << "Animal " << contador << " (ID: " << linha.at("id") << ") - " << linha.at("nome") << endl;
        }
    );
    if (contador == 0) cout << "Nenhum animal cadastrado." << endl;
    return contador > 0;
}

//read por dono
bool CRUDAnimal::listarPorDono(int donoId) {
    int contador = 0;
    db->consultar(
        "SELECT * FROM animais WHERE dono_id = ? ORDER BY nome;", 
        {to_string(donoId)}, 
        [&](const Database::Linha& linha) {
            contador++;
            cout << "Pet do Dono: " << linha.at("nome") << " (" << linha.at("tipo") << ")" << endl;
        }
    );
    if (contador == 0) cout << "Nenhum animal para o dono ID: " << donoId << endl;
    return contador > 0;
}

//update
bool CRUDAnimal::atualizar(int id, const string& novaFoto, float novoPeso) {
    bool sucesso = db->executarPreparado(
        "UPDATE animais SET foto = ?, peso = ?, atualizado_em = datetime('now', 'localtime') WHERE id = ?;", 
        {novaFoto, to_string(novoPeso), to_string(id)}
    );
    if (sucesso) cout << "Animal atualizado com sucesso!" << endl;
    else cout << "Erro ao atualizar animal: " << db->getMensagemErro() << endl;
    return sucesso;
}
//delete
bool CRUDAnimal::deletar(int id) {
    bool sucesso = db->executarPreparado("DELETE FROM animais WHERE id = ?", {to_string(id)});
    if (sucesso) cout << "Animal removido com sucesso!" << endl;
    else cout << "Erro ao remover animal: " << db->getMensagemErro() << endl;
    return sucesso;
}