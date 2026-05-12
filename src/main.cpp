#include <sqlite3.h>
#include "httplib.h"
#include "database/Database.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "models/Cachorro.h"
#include "models/Gato.h"
#include "models/Dono.h"
#include "models/Usuario.h"
#include "models/Ocorrencia.h"
#include "models/Localizacao.h"
#include "services/CRUDAnimal.h"
#include "services/CRUDDono.h"
#include "services/CRUDOcorrencia.h"
#include "services/CRUDLocalizacao.h"
#include "services/CRUDAvistamento.h"

using namespace std;
using namespace httplib;

// código mais complexo da main, função que retira dados do .js e diferencia foto de str normal
// código mais complexo da main, função que retira dados do .js e diferencia foto de str normal
string extrairValorJson(const string& json, const string& chave) {
    string busca = "\"" + chave + "\"";
    size_t posChave = json.find(busca);
    if (posChave == string::npos) return "";
    
    size_t posDoisPontos = json.find(":", posChave); // encontra os dois pontos após a chave
    if (posDoisPontos == string::npos) return "";

    size_t posAtual = posDoisPontos + 1; // pula os espaços em branco após os dois pontos
    while (posAtual < json.length() && isspace(json[posAtual])) {
        posAtual++;
    }
    if (posAtual >= json.length()) return "";
    
    // verifica se o valor é uma string 
    if (json[posAtual] == '"') {
        size_t inicio = posAtual + 1; // pula a aspa de abertura
        size_t fim = json.find('"', inicio); // procura a aspa de fechamento
        
        if (fim != string::npos) {
            return json.substr(inicio, fim - inicio); // retorna tudo
        }
    } else {
        // se for um número ou bool
        size_t inicio = posAtual;
        size_t fim = json.find_first_of(",}", inicio); // para na vírgula ou fim do json
        
        if (fim != string::npos) {
            string valor = json.substr(inicio, fim - inicio);
            // remove espaços extras no final
            while (!valor.empty() && isspace(valor.back())) valor.pop_back();
            return valor;
        }
    }
    
    return "";
}

//main
int main() {
    Database db;
    const string caminhoBanco = "petfinder.db";
    const string caminhoSchema = "src/database/schema.sql";

    if (!db.abrir(caminhoBanco)) return 1; // abre o banco
    if (!db.criarTabelas(caminhoSchema)) { // cria as tabelas se nao existirem
        cerr << "Erro ao criar tabelas: " << db.getMensagemErro() << endl;
        return 1;
    }
    cout << "Tabelas do SQLite prontas para uso." << endl;

    CRUDDono crudDono(&db);
    CRUDAnimal crudAnimal(&db);
    CRUDOcorrencia crudOcorrencia(&db);
    CRUDLocalizacao crudLocalizacao(&db);
    CRUDAvistamento crudAvistamento(&db);

    Server servidor;
    auto resultado = servidor.set_mount_point("/", "./frontend"); // serve os arquivos do frontend
    if (!resultado) {
        cerr << "Erro: A pasta 'frontend' nao foi encontrada." << endl;
        return 1;
    }
    // rota de cadastro de usuario
    servidor.Post("/api/register", [&](const Request& req, Response& res) {
        string user = extrairValorJson(req.body, "usuario");
        string nome = extrairValorJson(req.body, "nome");
        string cpf = extrairValorJson(req.body, "cpf");
        string telefone = extrairValorJson(req.body, "telefone");
        string email = extrairValorJson(req.body, "email");
        string senha = extrairValorJson(req.body, "senha");
        // se vier vazio, tenta ler do json
        if (nome.empty() || email.empty() || senha.empty()) {
            res.set_content(R"({"sucesso": false, "erro": "Dados incompletos"})", "application/json");
            return;
        }

        Dono novoDono(nome, cpf, telefone, email, "");
        // conexão com o crud do dono
        if (crudDono.cadastrar(&novoDono, user, senha)) {
            res.set_content(R"({"sucesso": true})", "application/json");
        } else {
            res.set_content(R"({"sucesso": false, "erro": "Usuário, CPF ou E-mail já existe"})", "application/json");
        }
    });
    // rota de login
    servidor.Post("/api/login", [&](const Request& req, Response& res) {
        string usuario = extrairValorJson(req.body, "usuario");
        string senha = extrairValorJson(req.body, "senha");

        // o CRUDDono assume a lógica de verificação
        string usuario_id = crudDono.realizarLogin(usuario, senha);

        if (!usuario_id.empty()) {
            res.set_content("{\"sucesso\": true, \"id\": \"" + usuario_id + "\"}", "application/json");
            cout << "Login realizado com sucesso: " << usuario << " (ID: " << usuario_id << ")" << endl;
        } else {
            res.set_content(R"({"sucesso": false, "erro": "E-mail ou senha incorretos."})", "application/json");
            cout << "Falha de login para o usuário: " << usuario << endl;
        }
    });

    // rota para cadastrar animais no banco de dados
    servidor.Post("/api/animais", [&](const Request& req, Response& res) {
        string corpo = req.body;
        string dono_id = extrairValorJson(corpo, "dono_id");
        string tipo = extrairValorJson(corpo, "tipo");

        if(dono_id.empty()) {
            res.status = 401;
            res.set_content(R"({"sucesso": false, "erro": "Sessão expirada."})", "application/json");
            return;
        }

        // extração dos dados do json
        string nome = extrairValorJson(corpo, "nome");
        string cor = extrairValorJson(corpo, "cor");
        string foto = extrairValorJson(corpo, "foto");
        string localizacao = extrairValorJson(corpo, "localizacao");
        string descricao = extrairValorJson(corpo, "descricao");
        string raca = extrairValorJson(corpo, "raca");
        string porte = extrairValorJson(corpo, "porte");
        string pelagem = extrairValorJson(corpo, "pelagem");

        string sPeso = extrairValorJson(corpo, "peso");
        float peso = sPeso.empty() ? 0.0f : stof(sPeso);

        string sIdade = extrairValorJson(corpo, "idade");
        int idade = sIdade.empty() ? 0 : stoi(sIdade);

        string sColeira = extrairValorJson(corpo, "usa_coleira");
        bool usaColeira = (sColeira == "1" || sColeira == "true");

        string sCastrado = extrairValorJson(corpo, "eh_castrado");
        bool ehCastrado = (sCastrado == "1" || sCastrado == "true");

        // 2. Instanciação Polimórfica passando os dados para os construtores
        Animal* pet = nullptr;
        if (tipo == "gato") {
            pet = new Gato(nome, cor, peso, idade, raca, pelagem, usaColeira, ehCastrado, foto);
        } else {
            pet = new Cachorro(nome, cor, peso, idade, raca, porte, pelagem, usaColeira, ehCastrado, foto);
        }

        string enderecoDoFront = extrairValorJson(req.body, "localizacao");
        string descricaoDoFront = extrairValorJson(req.body, "descricao");

        // preenchendo dados auxiliares
        pet->setLocalizacao(enderecoDoFront);
        pet->setDescricao(descricaoDoFront);

        if (crudAnimal.cadastrar(pet, dono_id, tipo)) {
            
            // pega o id do animal criado
            int novoAnimalId = 0;
            db.consultar("SELECT last_insert_rowid();", {}, [&](const Database::Linha& l) {
                novoAnimalId = stoi(l.begin()->second);
            });

            if (novoAnimalId > 0) {
                // cria a localização com os dados do usuário
                string bairroFinal = enderecoDoFront.empty() ? "Desconhecido" : enderecoDoFront;
                Localizacao novaLoc(0.0, 0.0, bairroFinal, descricaoDoFront);
                
                int localId = crudLocalizacao.CriarLocalizacao(&novaLoc);

                // cria a ocorrência
                Ocorrencia novaOco(0, "Recente", "PERDIDO", nullptr, nullptr);  
                
                // amarra no banco
                crudOcorrencia.CriarOcorrencia(&novaOco, novoAnimalId, localId);
            }

            res.set_content(R"({"sucesso": true})", "application/json");
        } else {
            res.set_content(R"({"sucesso": false})", "application/json");
        }
        
        delete pet;
    }); 

    // rota para listar animais do feed
    servidor.Get("/api/animais", [&](const Request&, Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");

        res.set_content(crudAnimal.listarFeed(), "application/json");
    });

    // rota de ocorrências
    servidor.Post("/api/ocorrencias", [&](const Request& req, Response& res) {
        int animalId = stoi(extrairValorJson(req.body, "animal_id"));
        int localId = stoi(extrairValorJson(req.body, "localizacao_id"));
        string data = extrairValorJson(req.body, "data");
        string status = "PERDIDO"; // status inicial

        // criamos o objeto ocorrência
        Ocorrencia novaOcorrencia(0, data, status, nullptr, nullptr);

        if (crudOcorrencia.CriarOcorrencia(&novaOcorrencia, animalId, localId)) {
            res.set_content(R"({"sucesso": true})", "application/json");
        } else {
            res.set_content(R"({"sucesso": false})", "application/json");
        }
    });

    servidor.Get("/api/ocorrencias", [&](const Request&, Response& res) {
        crudOcorrencia.LerTodasOcorrencias();
        res.set_content(R"({"mensagem": "Lista impressa no terminal do servidor"})", "application/json");
    });

    servidor.Put("/api/ocorrencias/encontrado", [&](const Request& req, Response& res) {
        int id = stoi(extrairValorJson(req.body, "id"));
        if (crudOcorrencia.AtualizarOcorrencia(id, "ENCONTRADO")) {
            res.set_content(R"({"sucesso": true})", "application/json");
        } else {
            res.set_content(R"({"sucesso": false})", "application/json");
        }
    });
    
    // rota para cadastar comentário
    servidor.Post("/api/avistamentos", [&](const Request& req, Response& res) {
        try {
            string animalIdStr = extrairValorJson(req.body, "animal_id");
            string usuarioIdStr = extrairValorJson(req.body, "usuario_id");
            string descricao = extrairValorJson(req.body, "descricao");
            string data = extrairValorJson(req.body, "data");

            cout << "Animal: [" << animalIdStr << "] | Usuario: [" << usuarioIdStr << "]" << endl;

            if (animalIdStr.empty() || usuarioIdStr.empty()) {
                res.status = 400;
                res.set_content(R"({"sucesso": false, "erro": "ID ausente"})", "application/json");
                return;
            }
            int ocorrenciaId = stoi(animalIdStr);
            int usuarioId = stoi(usuarioIdStr);

            if (crudAvistamento.criar(usuarioId, ocorrenciaId, descricao, data)) {
                res.set_content(R"({"sucesso": true})", "application/json");
            } else {
                res.set_content(R"({"sucesso": false, "erro": "Falha ao salvar no banco"})", "application/json");
            }
        } catch (const exception& e) {
            cout << "CRASH EVITADO: Erro ao processar JSON de avistamento -> " << e.what() << endl;
            res.status = 500;
            res.set_content(R"({"sucesso": false, "erro": "Erro interno no servidor"})", "application/json");
        }
    });

    //rota para buscar os comentários de um animal no feed
    servidor.Get("/api/avistamentos", [&](const Request& req, Response& res) {
        //verifica se o js enviou o id
        if (req.has_param("animal_id")) {
            int id = stoi(req.get_param_value("animal_id"));
            res.set_content(crudAvistamento.listarPorOcorrencia(id), "application/json");
        } else {
            res.status = 400; 
            res.set_content("[]", "application/json");
        }
    });

    cout << "Servidor PetFinder rodando em http://localhost:8080..." << endl;
    cout << "Pressione Ctrl+C para encerrar." << endl;
    servidor.listen("localhost", 8080); // inicia o servidor

    return 0;
}