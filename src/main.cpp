#include <sqlite3.h>
#include "httplib.h"
#include "database/Database.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;
using namespace httplib;

string extrairValorJson(const string& json, const string& chave) {
    string busca = "\"" + chave + "\":\"";
    size_t inicio = json.find(busca);
    if (inicio == string::npos) return ""; // Retorna vazio se não achar a chave
    inicio += busca.length();
    size_t fim = json.find("\"", inicio);
    return json.substr(inicio, fim - inicio);
}
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
    Database db;
    const string caminhoBanco = "petfinder.db";
    const string caminhoSchema = "src/database/schema.sql";
    if (!db.abrir(caminhoBanco)) return 1; // abre o banco
    if (!db.criarTabelas(caminhoSchema)) { // cria as tabelas se nao existirem
        cerr << "Erro ao criar tabelas: " << db.getMensagemErro() << endl;
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

        vector<string> params = {"dono", user, senha, nome, cpf, telefone, email};

        bool sucesso = db.executarPreparado(
            "INSERT INTO pessoas (tipo, usuario, senha, nome, cpf, telefone, email) VALUES (?, ?, ?, ?, ?, ?, ?)", 
            params
        );

        if (sucesso) res.set_content(R"({"sucesso": true})", "application/json");
        else res.set_content(R"({"sucesso": false, "erro": "Usuário, CPF ou E-mail já existe"})", "application/json");
    });
    // rota de login
    servidor.Post("/api/login", [&](const Request& req, Response& res) {
        string usuario = extrairValorJson(req.body, "usuario");
        string senha = extrairValorJson(req.body, "senha");

        sqlite3* db_local;
        sqlite3_open("petfinder.db", &db_local);
        
        string sql = "SELECT id FROM pessoas WHERE usuario='" + usuario + "' AND senha='" + senha + "';";
        string usuario_id = "";
        
        auto callback = [](void* data, int argc, char** argv, char**) -> int {
            string* id_ptr = static_cast<string*>(data);
            if (argc > 0 && argv[0]) {
                *id_ptr = argv[0]; // salva o id retornado pelo banco
            }
            return 0;
        };

        sqlite3_exec(db_local, sql.c_str(), callback, &usuario_id, nullptr);
        sqlite3_close(db_local);

        if (!usuario_id.empty()) {
            // se achou o ID, devolve pro JavaScript
            res.set_content("{\"sucesso\": true, \"id\": \"" + usuario_id + "\"}", "application/json");
            cout << "Login realizado com sucesso: " << usuario << " (ID: " << usuario_id << ")" << endl;
        } else {
            res.set_content(R"({"sucesso": false, "erro": "E-mail ou senha incorretos."})", "application/json");
            cout << "Falha de login para o usuário: " << usuario << endl;
        }
    });
    // rota para listar postagens
    servidor.Get("/api/posts", [](const Request& /*req*/, Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_content(gerarJsonDasPostagens(), "application/json");
    });
    // rota para cadastrar animais no banco de dados
    servidor.Post("/api/animais", [&](const Request& req, Response& res) {
        string corpo = req.body;
        string dono_id = extrairValorJson(corpo, "dono_id");
        if(dono_id.empty()) {
            res.status = 401;
            res.set_content(R"({"sucesso": false, "erro": "Sessão expirada. Faça login."})", "application/json");
            return;
        }

        string tipo = extrairValorJson(corpo, "tipo");
        string nome = extrairValorJson(corpo, "nome");
        string raca = extrairValorJson(corpo, "raca");
        string cor = extrairValorJson(corpo, "cor");
        string porte = extrairValorJson(corpo, "porte");
        string pelagem = extrairValorJson(corpo, "pelagem");
        string idade = extrairValorJson(corpo, "idade");
        string peso = extrairValorJson(corpo, "peso");
        string usa_coleira = extrairValorJson(corpo, "usa_coleira");
        string eh_castrado = extrairValorJson(corpo, "eh_castrado");
        string localizacao = extrairValorJson(corpo, "localizacao"); 
        string descricao = extrairValorJson(corpo, "descricao");     

        vector<string> parametros = {dono_id, tipo, nome, peso, idade, cor, raca, porte, usa_coleira, pelagem, eh_castrado, localizacao, descricao};
        
        bool sucesso = db.executarPreparado(
            "INSERT INTO animais (dono_id, tipo, nome, peso, idade, cor, raca, porte, usa_coleira, pelagem, eh_castrado, localizacao, descricao) "
            "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)", 
            parametros
        );

        if (sucesso) res.set_content(R"({"sucesso": true})", "application/json");
        else res.set_content(R"({"sucesso": false, "erro": "Erro ao salvar no banco"})", "application/json");
    });

    // rota para listar animais do feed
    servidor.Get("/api/animais", [](const Request&, Response& res) {
        sqlite3* db_ptr;
        if (sqlite3_open("petfinder.db", &db_ptr) != SQLITE_OK) {
            res.status = 500; res.set_content("[]", "application/json"); return;
        }

        string json = "[";
        auto cb = [](void* data, int, char** argv, char**) -> int {
            string* s = static_cast<string*>(data);
            if (s->length() > 1) *s += ",";
            
            *s += string("{") 
                + "\"nome\":\"" + (argv[0] ? argv[0] : "") + "\","
                + "\"tipo\":\"" + (argv[1] ? argv[1] : "") + "\","
                + "\"raca\":\"" + (argv[2] ? argv[2] : "") + "\","
                + "\"cor\":\"" + (argv[3] ? argv[3] : "") + "\","
                + "\"porte\":\"" + (argv[4] ? argv[4] : "") + "\","
                + "\"pelagem\":\"" + (argv[5] ? argv[5] : "") + "\","
                + "\"idade\":\"" + (argv[6] ? argv[6] : "0") + "\","
                + "\"peso\":\"" + (argv[7] ? argv[7] : "0") + "\","
                + "\"usa_coleira\":\"" + (argv[8] ? argv[8] : "0") + "\","
                + "\"eh_castrado\":\"" + (argv[9] ? argv[9] : "0") + "\","
                + "\"localizacao\":\"" + (argv[10] ? argv[10] : "") + "\","
                + "\"descricao\":\"" + (argv[11] ? argv[11] : "") + "\","
                + "\"dono_nome\":\"" + (argv[12] ? argv[12] : "") + "\","
                + "\"dono_telefone\":\"" + (argv[13] ? argv[13] : "") + "\""
                + "}";
            return 0;
        };

        string query = 
            "SELECT a.nome, a.tipo, a.raca, a.cor, a.porte, a.pelagem, a.idade, a.peso, a.usa_coleira, a.eh_castrado, a.localizacao, a.descricao, "
            "p.nome AS dono_nome, p.telefone AS dono_telefone "
            "FROM animais a "
            "JOIN pessoas p ON a.dono_id = p.id "
            "ORDER BY a.id DESC;";
        
        sqlite3_exec(db_ptr, query.c_str(), cb, &json, nullptr);
        sqlite3_close(db_ptr);
        json += "]";
        
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_content(json, "application/json");
    });


    // rota para criar postagem
    servidor.Post("/api/posts", [](const Request& req, Response& res) {
        string conteudo = extrairValorJson(req.body, "conteudo");
        string autor = extrairValorJson(req.body, "autor");
        if (autor.empty()) autor = "Anonimo";

        Postagem novoPost;
        novoPost.id = proximo_id_post++;
        novoPost.autor = autor;
        novoPost.conteudo = conteudo;
        banco_de_postagens.push_back(novoPost); // adiciona na lista

        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_content("{\"sucesso\": true}", "application/json");
    });
    // rota para adicionar comentario em uma postagem
    servidor.Post("/api/comments", [](const Request& req, Response& res) {
        string postIdStr = extrairValorJson(req.body, "postId");
        int postId = postIdStr.empty() ? 0 : stoi(postIdStr);
        string texto = extrairValorJson(req.body, "texto");
        string autor = extrairValorJson(req.body, "autor");
        if (autor.empty()) autor = "Anonimo";
        
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