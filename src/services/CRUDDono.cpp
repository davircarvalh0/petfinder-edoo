#include "CRUDDono.h"
#include <iostream>
using namespace std;
//construtor, inicializa a referencia ao banco
CRUDDono::CRUDDono(Database* database) : db(database) {}
//C: insere um dono na tabela pessoas com fixo "dono"
bool CRUDDono::cadastrar(Dono* dono, const string& usuario, const string& senha) {
    vector<string> params = {
        "dono", usuario, senha, dono->getNome(), 
        dono->getCpf(), dono->getTelefone(), dono->getEmail(), dono->getEndereco() // Se o getter não existir, crie-o!
    };

    bool sucesso = db->executarPreparado(
        "INSERT INTO pessoas (tipo, usuario, senha, nome, cpf, telefone, email, endereco) VALUES (?, ?, ?, ?, ?, ?, ?, ?)", 
        params
    );
    
    if (sucesso) cout << "Dono cadastrado com sucesso no banco!" << endl;
    else cout << "Erro ao cadastrar dono: " << db->getMensagemErro() << endl;
    
    return sucesso;
}
// método de login
string CRUDDono::realizarLogin(const string& usuario, const string& senha) {
    string usuario_id = "";
    db->consultar(
        "SELECT id FROM pessoas WHERE usuario = ? AND senha = ? AND tipo = 'dono';", 
        {usuario, senha}, 
        [&](const Database::Linha& linha) {
            usuario_id = linha.at("id");
        }
    );
    return usuario_id;
}

//R:busca um dono especifico pelo id e imprime suas informacoes
bool CRUDDono::buscarPorId(int id) {
    bool encontrou = false;
    db->consultar(
        "SELECT id, nome, cpf, telefone, email, endereco FROM pessoas WHERE id = ? AND tipo = 'dono'", 
        {to_string(id)}, 
        [&](const Database::Linha& linha) {
            encontrou = true;
            cout << "=== Dono Encontrado ===" << endl;
            cout << "ID: "  << linha.at("id") << endl;
            cout << "Nome: " << linha.at("nome") << endl;
            cout << "CPF: " << linha.at("cpf") << endl;
            cout << "Telefone: " << linha.at("telefone") << endl;
            cout << "Email: "  << linha.at("email") << endl;
            cout << "Endereço: " << linha.at("endereco") << endl;
        }
    );
    if (!encontrou) cout << "Nenhum dono encontrado com ID: " << id << endl;
    return encontrou;
}
//R: lista todos os donos cadastrados ordenados por nome
bool CRUDDono::listarTodos() {
    int contador = 0;
    db->consultar(
        "SELECT id, nome, cpf, telefone, email, endereco FROM pessoas WHERE tipo = 'dono' ORDER BY nome", 
        {}, 
        [&](const Database::Linha& linha) {
            contador++;
            cout << "\nDono " << contador << " (ID: " << linha.at("id") << ")" << endl;
            cout << "Nome: " << linha.at("nome") << " | Tel: " << linha.at("telefone") << endl;
        }
    );
    if (contador == 0) cout << "Nenhum dono cadastrado." << endl;
    return contador > 0;
}
//U: atualiza telefone e endereco do dono pelo id e atualiza tambem o campo atualizado_em automaticamente
bool CRUDDono::atualizar(int id, const string& novoTelefone, const string& novoEndereco) {
    bool sucesso = db->executarPreparado(
        "UPDATE pessoas SET telefone = ?, endereco = ?, atualizado_em = datetime('now', 'localtime') WHERE id = ? AND tipo = 'dono';", 
        {novoTelefone, novoEndereco, to_string(id)}
    );
    if (sucesso) cout << "Dono atualizado com sucesso!" << endl;
    else cout << "Erro ao atualizar dono: " << db->getMensagemErro() << endl;
    return sucesso;
}
//D: remove um dono do banco pelo id e por cascade no schema, remove tambem os animais desse dono
bool CRUDDono::deletar(int id) {
    bool sucesso = db->executarPreparado(
        "DELETE FROM pessoas WHERE id = ? AND tipo = 'dono'", 
        {to_string(id)}
    );
    if (sucesso) cout << "Dono removido com sucesso!" << endl;
    else cout << "Erro ao remover dono: " << db->getMensagemErro() << endl;
    return sucesso;
}
//read do fltro
string CRUDDono::buscarPerfil(int id) {
    string json = "{}";
    db->consultar("SELECT nome, email, telefone, cpf FROM pessoas WHERE id=?", {to_string(id)},
        [&](const Database::Linha& linha) {
            json =  "{""\"nome\":\"" + linha.at("nome") + "\",""\"email\":\"" + linha.at("email")+ "\",""\"telefone\":\"" + linha.at("telefone") + "\",""\"cpf\":\""+ linha.at("cpf")+ "\"""}";});
    return json;
}
//update do perfil
bool CRUDDono::atualizarPerfil(int id, const string& email, const string& telefone, const string& senha) {
    string sql = "UPDATE pessoas SET ";
    vector<string> params;
    bool algum = false;
    if (!email.empty()) { if (algum) sql += ", "; sql += "email=?"; params.push_back(email); algum = true; }
    if (!telefone.empty()) { if (algum) sql += ", "; sql += "telefone=?"; params.push_back(telefone); algum = true; }
    if (!senha.empty()) { if (algum) sql += ", "; sql += "senha=?"; params.push_back(senha); algum = true; }
    if (!algum) return false;
    sql += " WHERE id=?";
    params.push_back(to_string(id));
    return db->executarPreparado(sql, params);
}