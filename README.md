
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
│   │   ├── CRUDAvistamento.h / CRUDAvistamento.cpp
│   │   └── CRUDLocalizacao.h / CRUDLocalizacao.cpp
│   ├── ui/
│   │   ├── Menu.h / Menu.cpp
│   │   └── Relatorios.h / Relatorios.cpp
│   └── main.cpp
├── frontend/
│   ├── index.html
│   ├── home.html
│   ├── script.js
│   ├── home.js
│   └── style.css
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
# 🐾 PetFinder Recife

Sistema web para reportar e localizar animais domésticos desaparecidos na cidade do Recife.

---

## 📋 Descrição

O PetFinder Recife é uma plataforma onde donos de animais podem registrar ocorrências de pets desaparecidos e outros usuários podem reportar avistamentos, ajudando a reunir o animal com seu dono.

---

## ✅ O que o sistema faz

- Cadastro e login de usuários
- Publicar ocorrência de pet perdido com foto, descrição e localização
- Feed de ocorrências com todos os pets desaparecidos
- Filtrar ocorrências por **nome do pet** ou **nome do dono**
- Reportar avistamentos/pistas em cada ocorrência
- Dono pode **marcar o pet como encontrado**
- Dono pode **remover a ocorrência** do feed

---

## 🛠️ Tecnologias

- **Backend:** C++17 com servidor HTTP (`httplib`)
- **Banco de dados:** SQLite3
- **Frontend:** HTML, CSS e JavaScript puro

---

## 🚀 Como rodar

### Windows (MSYS2)

1. Baixe e instale o **MSYS2** em [msys2.org](https://www.msys2.org)
2. Abra o terminal **MSYS2 MINGW64** pelo menu iniciar
3. Instale as dependências (apenas uma vez):

```bash
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-make mingw-w64-x86_64-sqlite3
```

4. Entre na pasta do projeto e compile:

```bash
cd /c/Users/SEU_NOME/caminho/petfinder-edoo-main
mingw32-make
mingw32-make run
```

Após rodar, acesse no navegador: **http://localhost:8080**

Para encerrar o servidor: `Ctrl + C`

### Outros comandos

```bash
make clean      # remove o executavel compilado
make db-reset   # apaga e recria o banco do zero
make db-schema  # cria as tabelas sem apagar dados
```

---

## 🔗 Links

| Item | Link |
|------|------|
| 📁 Código fonte | _em breve_ |
| 📄 Relatório | _em breve_ |
| 🎥 Vídeo no YouTube | _em breve_ |

---

## 👥 Equipe

Projeto desenvolvido para a disciplina de Estrutura de Dados e Orientação a Objetos (CIN-UFPE 2026.1)
