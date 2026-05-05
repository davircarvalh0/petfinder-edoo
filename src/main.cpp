#include "httplib.h"
#include "database/Database.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;
using namespace httplib;
// estrutura de um comentario de postagem
struct Comentario {
    string autor;
    string texto;
};
// estrutura de uma postagem
struct Postagem {
    int id;
    string autor;
    string conteudo;
    vector<Comentario> comentarios;
};
// lista de postagens em memoria
vector<Postagem> banco_de_postagens = {
    {1, "Admin", "Cachorro perdido hoje? Ele estava com uma coleira azul.", {}}
};
int proximo_id_post = 2; // contador de id das postagens
// dicionario de usuarios em memoria
map<string, string> usuarios_db = {
    {"admin", "1234"} // usuario padrao para testes
};
// gera um json com todas as postagens e seus comentarios
string gerarJsonDasPostagens() {
    string json = "[";
    for(size_t i = 0; i < banco_de_postagens.size(); i++) {
        json += "{\"id\":" + to_string(banco_de_postagens[i].id) + ",";
        json += "\"autor\":\"" + banco_de_postagens[i].autor + "\",";
        json += "\"conteudo\":\"" + banco_de_postagens[i].conteudo + "\",";
        json += "\"comments\":[";
        for(size_t j = 0; j < banco_de_postagens[i].comentarios.size(); j++) {
            json += "{\"autor\":\"" + banco_de_postagens[i].comentarios[j].autor + "\",";
            json += "\"texto\":\"" + banco_de_postagens[i].comentarios[j].texto + "\"}";
            if(j < banco_de_postagens[i].comentarios.size() - 1) json += ",";
        }
        json += "]}";
        if(i < banco_de_postagens.size() - 1) json += ",";
    }
    json += "]";
    return json;
}
//main
int main() {
    Database banco;
    const string caminhoBanco = "petfinder.db";
    const string caminhoSchema = "src/database/schema.sql";
    if (!banco.abrir(caminhoBanco)) return 1; // abre o banco
    if (!banco.criarTabelas(caminhoSchema)) { // cria as tabelas se nao existirem
        cerr << "Erro ao criar tabelas: " << banco.getMensagemErro() << endl;
        return 1;
    }
    cout << "Tabelas do SQLite prontas para uso." << endl;
    httplib::Server servidor;
    auto resultado = servidor.set_mount_point("/", "./frontend"); // serve os arquivos do frontend
    if (!resultado) {
        cerr << "Erro: A pasta 'frontend' nao foi encontrada." << endl;
        return 1;
    }
    // rota de cadastro de usuario
    servidor.Post("/api/register", [](const Request& req, Response& res) {
        string usuario = req.get_param_value("usuario");
        string senha = req.get_param_value("senha");
        if (usuarios_db.find(usuario) == usuarios_db.end()) {
            usuarios_db[usuario] = senha; // salva o usuario
            res.set_content(R"({"sucesso": true})", "application/json");
        } else {
            res.set_content(R"({"sucesso": false, "erro": "usuario ja existe."})", "application/json");
        }
    });
    // rota de login
    servidor.Post("/api/login", [](const Request& req, Response& res) {
        string usuario = req.get_param_value("usuario");
        string senha = req.get_param_value("senha");

        if (usuarios_db.find(usuario) != usuarios_db.end() && usuarios_db[usuario] == senha) {
            res.set_content(R"({"sucesso": true})", "application/json");
            cout << "[LOG] login ok: " << usuario << endl;
        } else {
            res.set_content(R"({"sucesso": false, "erro": "usuario ou senha incorretos."})", "application/json");
            cout << "[LOG] login falhou: " << usuario << endl;
        }
    });
    // rota para listar postagens
    servidor.Get("/api/posts", [](const Request& req, Response& res) {
        res.set_content(gerarJsonDasPostagens(), "application/json");
    });
    // rota para criar postagem
    servidor.Post("/api/posts", [](const Request& req, Response& res) {
        string conteudo = req.get_param_value("conteudo");
        string autor = req.has_param("autor") ? req.get_param_value("autor") : "Anonimo";
        Postagem novoPost;
        novoPost.id = proximo_id_post++;
        novoPost.autor = autor;
        novoPost.conteudo = conteudo;
        banco_de_postagens.push_back(novoPost); // adiciona na lista
        res.set_content("{\"sucesso\": true}", "application/json");
    });
    // rota para adicionar comentario em uma postagem
    servidor.Post("/api/comments", [](const Request& req, Response& res) {
        int postId = stoi(req.get_param_value("postId"));
        string texto = req.get_param_value("texto");
        string autor = req.has_param("autor") ? req.get_param_value("autor") : "Anonimo";
        for(auto& post : banco_de_postagens) {
            if(post.id == postId) {
                post.comentarios.push_back({autor, texto}); // adiciona o comentario
                break;
            }
        }
        res.set_content("{\"sucesso\": true}", "application/json");
    });
    cout << "Servidor PetFinder rodando em http://localhost:8080..." << endl;
    cout << "Pressione Ctrl+C para encerrar." << endl;
    servidor.listen("localhost", 8080); // inicia o servidor

    return 0;
}