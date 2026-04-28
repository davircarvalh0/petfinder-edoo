#include "httplib.h"
#include <iostream>
#include <string>
#include <vector>

struct Comentario {
    std::string autor;
    std::string texto;
};

struct Postagem {
    int id;
    std::string autor;
    std::string conteudo;
    std::vector<Comentario> comentarios;
};

std::vector<Postagem> banco_de_postagens = {
    {1, "Admin", "Cachorro perdido hoje? Ele estava com uma coleira azul.", {}}
};
int proximo_id_post = 2; 

std::string gerarJsonDasPostagens() {
    std::string json = "[";
    for(size_t i = 0; i < banco_de_postagens.size(); i++) {
        json += "{\"id\":" + std::to_string(banco_de_postagens[i].id) + ",";
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

int main() {
    httplib::Server servidor;

    servidor.set_mount_point("/", "./frontend");

    servidor.Post("/api/login", [](const httplib::Request& req, httplib::Response& res) {
        std::string usuario = req.get_param_value("usuario");
        std::string senha = req.get_param_value("senha");

        if (usuario == "admin" && senha == "1234") {
            res.set_content(R"({"sucesso": true})", "application/json");
        } else {
            res.set_content(R"({"sucesso": false, "erro": "Incorreto."})", "application/json");
        }
    });

    servidor.Get("/api/posts", [](const httplib::Request& req, httplib::Response& res) {
        std::string respostaJson = gerarJsonDasPostagens();
        res.set_content(respostaJson, "application/json");
    });

    servidor.Post("/api/posts", [](const httplib::Request& req, httplib::Response& res) {
        std::string conteudo = req.get_param_value("conteudo");
        
        Postagem novoPost;
        novoPost.id = proximo_id_post++;
        novoPost.autor = "Admin"; 
        novoPost.conteudo = conteudo;
        
        banco_de_postagens.push_back(novoPost);
        res.set_content("{\"sucesso\": true}", "application/json");
    });

    servidor.Post("/api/comments", [](const httplib::Request& req, httplib::Response& res) {
        int postId = std::stoi(req.get_param_value("postId"));
        std::string texto = req.get_param_value("texto");

        for(auto& post : banco_de_postagens) {
            if(post.id == postId) {
                Comentario novoComentario = {"Admin", texto};
                post.comentarios.push_back(novoComentario);
                break;
            }
        }
        res.set_content("{\"sucesso\": true}", "application/json");
    });

    std::cout << "Servidor PetFinder rodando em http://localhost:8080..." << std::endl;
    servidor.listen("localhost", 8080);

    return 0;
}