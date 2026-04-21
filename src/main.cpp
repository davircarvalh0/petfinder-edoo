#include "httplib.h"
#include <iostream>
#include <string>

int main() {
    httplib::Server servidor;
    auto resultado = servidor.set_mount_point("/", "./frontend");
    if (!resultado) {
        std::cerr << "Erro: A pasta 'frontend' nao foi encontrada." << std::endl;
        return 1;
    }
    servidor.Post("/api/login", [](const httplib::Request& req, httplib::Response& res) {
        std::string usuario = req.get_param_value("usuario");
        std::string senha = req.get_param_value("senha");

        if (usuario == "admin" && senha == "1234") {
            res.set_content(R"({"sucesso": true})", "application/json");
            std::cout << "[LOG] Login efetuado com sucesso: " << usuario << std::endl;
        } else {
            res.set_content(R"({"sucesso": false, "erro": "Usuario ou senha incorretos."})", "application/json");
            std::cout << "[LOG] Tentativa de login falha: " << usuario << std::endl;
        }
    });

    std::cout << "Servidor PetFinder rodando em http://localhost:8080..." << std::endl;
    std::cout << "Pressione Ctrl+C no terminal para encerrar." << std::endl;
    
    servidor.listen("localhost", 8080);

    return 0;
}