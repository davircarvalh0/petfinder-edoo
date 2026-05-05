#include "httplib.h"
#include "database/Database.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
    Database banco;
    const string caminhoBanco = "petfinder.db";
    const string caminhoSchema = "src/database/schema.sql";

    if (!banco.abrir(caminhoBanco)) {
        return 1;
    }

    if (!banco.criarTabelas(caminhoSchema)) {
        cerr << "Erro ao criar tabelas: " << banco.getMensagemErro() << endl;
        return 1;
    }

    cout << "Tabelas do SQLite prontas para uso." << endl;

    httplib::Server servidor;

    auto resultado = servidor.set_mount_point("/", "./frontend");

    if (!resultado) {
        cerr << "Erro: A pasta 'frontend' nao foi encontrada." << endl;
        return 1;
    }

    servidor.Post("/api/login", [](const httplib::Request& req, httplib::Response& res) {
        string usuario = req.get_param_value("usuario");
        string senha = req.get_param_value("senha");

        if (usuario == "admin" && senha == "1234") {
            res.set_content(R"({"sucesso": true})", "application/json");
            cout << "[LOG] Login efetuado com sucesso: " << usuario << endl;
        } else {
            res.set_content(R"({"sucesso": false, "erro": "Usuario ou senha incorretos."})", "application/json");
            cout << "[LOG] Tentativa de login falha: " << usuario << endl;
        }
    });

    cout << "Servidor PetFinder rodando em http://localhost:8080..." << endl;
    cout << "Pressione Ctrl+C no terminal para encerrar." << endl;

    servidor.listen("localhost", 8080);

    return 0;
}
