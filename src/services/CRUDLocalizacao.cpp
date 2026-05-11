#include "CRUDLocalizacao.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

int CRUDLocalizacao::CriarLocalizacao(Localizacao* loc) {
    if (!loc) return 0;

    vector<string> params = {
        to_string(loc->getLatitude()),
        to_string(loc->getLongitude()),
        loc->getBairro(),
        loc->getReferencia()
    };

    bool sucesso = db->executarPreparado(
        "INSERT INTO localizacoes (latitude, longitude, bairro, referencia) VALUES (?, ?, ?, ?)", 
        params
    );

    if (sucesso) {
        int idGerado = 0;
        // pega o id da localização que acabou de ser criada
        db->consultar("SELECT last_insert_rowid();", {}, [&](const Database::Linha& l) {
            idGerado = stoi(l.begin()->second);
        });
        return idGerado;
    }

    cout << "Erro ao salvar localização: " << db->getMensagemErro() << endl;
    return 0; 
}