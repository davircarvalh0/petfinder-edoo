# pethealth-edoo
Projeto da disciplina de Estrutura de Dados Orientadas a Objetos

# Sobre o projeto
O **PetFinder Recife** é um sistema de informação que conecta donos de animais perdidos com usuários que possam ter avistado o pet. O sistema permite o cadastro de animais, donos, ocorrências de desaparecimento e avistamentos, além de exibir pontos de resgate próximos na cidade.

Desenvolvido como projeto acadêmico da disciplina de **Estruturas de Dados / POO em C++**, com foco em:

- Programação Orientada a Objetos (classes, herança, polimorfismo, encapsulamento)
- CRUD completo conectado a banco de dados
- Interface com o usuário via interface gráfica
- Documentação técnica e Diagrama de Classes UML

# 🗂️ Estrutura de Pastas

```
petfinder-recife/
├── src/
│   ├── models/
│   │   ├── Pessoa.h / Pessoa.cpp
│   │   ├── Dono.h / Dono.cpp
│   │   ├── Usuario.h / Usuario.cpp
│   │   ├── Animal.h / Animal.cpp
│   │   ├── Cachorro.h / Cachorro.cpp
│   │   ├── Gato.h / Gato.cpp
│   │   ├── Ocorrencia.h / Ocorrencia.cpp
│   │   ├── Avistamento.h / Avistamento.cpp
│   │   ├── Localizacao.h / Localizacao.cpp
│   │   └── PontoResgate.h / PontoResgate.cpp
│   ├── database/
│   │   ├── Database.h / Database.cpp
│   │   └── schema.sql
│   ├── services/
│   │   ├── CRUDAnimal.h / CRUDAnimal.cpp
│   │   ├── CRUDDono.h / CRUDDono.cpp
│   │   ├── CRUDOcorrencia.h / CRUDOcorrencia.cpp
│   │   └── CRUDAvisamento.h / CRUDAvistamento.cpp
│   ├── ui/
│   │   ├── Menu.h / Menu.cpp
│   │   └── Relatorios.h / Relatorios.cpp
│   └── main.cpp
├── docs/
│   ├── diagrama_classes_uml.png
│   ├── relatorio_tecnico.pdf
│   └── documentacao_sprint.md
├── tests/
│   └── test_main.cpp
├── .gitignore
├── Makefile
└── README.md
```
## Como rodar o codigo
# WIndows:
**O Compilador:** MinGW-w64

**O que baixar:** MSYS2

**Após instalar o MSYS2, ele deve abrir o terminal do MSYS2 (UCRT64) e rodar:**
pacman -S mingw-w64-ucrt-x86_64-gcc

**Precisa adicionar a pasta bin do MinGW (geralmente C:\msys64\ucrt64\bin) ao PATH das Variáveis de Ambiente do Windows para que o comando g++ funcione no terminal do VS Code.**

**Instalação do sqlite:**
pacman -S mingw-w64-ucrt-x86_64-sqlite3

**ferramenta de automação:**
pacman -S make

**dentro do Vscode:**
*crie um novo terminal (control + ') e rode* mingw32-make
*depois rode* mingw32-make run

**localhost**
apos isso, no seu terminal, vai aparecer o link do site web local, agora é so copiar e colar e ultilizar a ferramenta!
```
# Banco de dados SQLite

O projeto usa SQLite, entao o banco fica em um arquivo local chamado `petfinder.db`.
As tabelas sao criadas pelo arquivo `src/database/schema.sql` quando o programa inicia.

## Como compilar e rodar

```bash
make
make run
```

Se quiser recriar o banco do zero:

```bash
make db-reset
```

Para abrir o banco pelo terminal:

```bash
sqlite3 petfinder.db
.tables
.schema animais
```

## Como conectar no C++

```cpp
#include "database/Database.h"

Database banco;

if (!banco.abrir("petfinder.db")) {
    return 1;
}

banco.criarTabelas("src/database/schema.sql");
```

## Exemplo para os CRUDs

Use `executarPreparado` para `INSERT`, `UPDATE` e `DELETE`:

```cpp
banco.executarPreparado(
    "INSERT INTO animais (dono_id, tipo, nome, peso, idade, cor, raca, foto) VALUES (?, ?, ?, ?, ?, ?, ?, ?);",
    {"1", "cachorro", "Rex", "12.5", "3", "caramelo", "vira-lata", "uploads/rex.jpg"}
);
```

Use `consultar` para `SELECT`:

```cpp
banco.consultar(
    "SELECT id, nome, telefone FROM pessoas WHERE tipo = ?;",
    {"dono"},
    [](const Database::Linha& linha) {
        std::cout << linha.at("id") << " - " << linha.at("nome") << std::endl;
    }
);
```

Principais tabelas:

- `pessoas`: guarda `dono` e `usuario`
- `animais`: cachorro/gato ligado a um dono, incluindo o campo `foto`
- `localizacoes`: latitude, longitude, bairro e referencia
- `ocorrencias`: desaparecimento de um animal
- `avistamentos`: relato de um usuario sobre uma ocorrencia
- `pontos_resgate`: locais uteis para resgate
