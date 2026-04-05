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
