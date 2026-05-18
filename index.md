<div align="center">
  <h1>🐾 PetFinder Recife</h1>
  <p><strong>Gabriel Godoy &bull; Davi Rosendo &bull; João Felipe Costa &bull; Davi Pedrosa &bull; João Antonio Lins</strong></p>
  <p><em>Projeto desenvolvido para a disciplina de Estrutura de Dados e Orientação a Objetos (CIN-UFPE 2026.1)</em></p>
  <br>
  <a href="https://docs.google.com/document/d/1VwX5ofNbjtOzzGhpuue7LXBqGyys31T4ps2Xtrb9pik/edit?usp=sharing">
    <img src="https://img.shields.io/badge/📄_Relatório_Técnico-0052CC?style=for-the-badge" alt="Relatório Técnico">
  </a>
  <a href="https://github.com/davircarvalh0/petfinder-edoo">
    <img src="https://img.shields.io/badge/💻_Código_no_GitHub-181717?style=for-the-badge" alt="Código Fonte">
  </a>
  <a href="https://www.youtube.com/watch?v=8shw4VffJTE">
    <img src="https://img.shields.io/badge/🎥_Vídeo_Demonstrativo-FF0000?style=for-the-badge" alt="Vídeo no YouTube">
  </a>
</div>

---

## Sobre o Projeto

O **PetFinder Recife** é um sistema web dedicado a ajudar donos de animais a reencontrarem seus pets desaparecidos. Nossa plataforma centraliza os registros de ocorrências e avistamentos, criando uma rede de solidariedade rápida e acessível. O sistema gerencia toda a lógica em um backend robusto em C++, conectado a um banco de dados relacional e consumido por uma interface web intuitiva.

---

## O que o sistema faz

* **Gestão de Usuários:** Cadastro, login unificado e gerenciamento de perfil.
* **Mural de Ocorrências:** Publicação de pets perdidos incluindo fotos, descrições detalhadas (porte, raça, coleira) e localização do desaparecimento.
* **Filtros de Busca:** Localização rápida de ocorrências ativas filtrando pelo nome do animal ou do próprio dono.
* **Rede de Avistamentos:** Qualquer usuário logado pode reportar pistas diretamente na página da ocorrência do animal desaparecido.
* **Resolução:** O dono tem autonomia para alterar o status do pet para "Encontrado" e remover a ocorrência do feed principal.

---

## Demonstração do Sistema

Abaixo estão as telas com as principais funcionalidades do nosso sistema operando no navegador:

### Login e Acesso
<div align="center">
  <img src="docs/screenshots/login.png" alt="Tela de Login" width="80%">
</div>

### Feed de Ocorrências
<div align="center">
  <img src="docs/screenshots/feed.png" alt="Feed de Ocorrências" width="80%">
  <p><em>Mural principal com as ocorrências de animais desaparecidos.</em></p>
</div>

### Publicar Pet Perdido
<div align="center">
  <img src="docs/screenshots/publicar.png" alt="Publicar Pet Perdido" width="80%">
  <p><em>Formulário para registro de uma nova ocorrência.</em></p>
</div>

### Minhas Ocorrências
<div align="center">
  <img src="docs/screenshots/minhas-ocorrencias.png" alt="Minhas Ocorrências" width="80%">
  <p><em>Área de gestão onde o dono pode atualizar o status do pet.</em></p>
</div>

### Meu Perfil
<div align="center">
  <img src="docs/screenshots/perfil.png" alt="Perfil do Usuário" width="80%">
</div>

---

## Tecnologias

* **Backend:** C++17 com servidor HTTP (`httplib`)
* **Banco de Dados:** SQLite3
* **Frontend:** HTML, CSS e JavaScript puro
