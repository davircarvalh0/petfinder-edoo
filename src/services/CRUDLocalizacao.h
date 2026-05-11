#ifndef CRUDLOCALIZACAO_H
#define CRUDLOCALIZACAO_H
#include "../database/Database.h"
#include "../models/Localizacao.h"

class CRUDLocalizacao {
    private:
        Database* db;
    public:
        CRUDLocalizacao(Database* banco) : db(banco) {}
        int CriarLocalizacao(Localizacao* loc);  // retorna o id da nova localização em vez de bool
};
#endif