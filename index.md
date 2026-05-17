<div align="center">

# 🐾 PetFinder Recife

**Gabriel Godoy &bull; Davi Rosendo &bull; João Felipe Costa &bull; Davi Pedrosa &bull; João Antonio Lins**

*Projeto desenvolvido para a disciplina de Estrutura de Dados e Orientação a Objetos (CIN-UFPE 2026.1)*

<br>

[![Relatório Técnico](https://img.shields.io/badge/📄_Relatório_Técnico-0052CC?style=for-the-badge)](https://docs.google.com/document/d/1VwX5ofNbjtOzzGhpuue7LXBqGyys31T4ps2Xtrb9pik/edit?usp=sharing)
[![Código Fonte](https://img.shields.io/badge/💻_Código_no_GitHub-181717?style=for-the-badge)](https://github.com/davircarvalh0/petfinder-edoo)
[![Vídeo no YouTube](https://img.shields.io/badge/🎥_Vídeo_Demonstrativo-FF0000?style=for-the-badge)](#)

</div>

---

## 📋 Sobre o Projeto (Abstract)

O **PetFinder Recife** é um sistema web dedicado a ajudar donos de animais a reencontrarem seus pets desaparecidos. Nossa plataforma centraliza os registros de ocorrências e avistamentos, criando uma rede de solidariedade rápida e acessível. O sistema gerencia toda a lógica em um backend robusto em C++, conectado a um banco de dados relacional e consumido por uma interface web intuitiva.

---

## ✅ O que o sistema faz

* **Gestão de Usuários:** Cadastro, login unificado e gerenciamento de perfil.
* **Mural de Ocorrências:** Publicação de pets perdidos incluindo fotos, descrições detalhadas (porte, raça, coleira) e localização do desaparecimento.
* **Filtros de Busca:** Localização rápida de ocorrências ativas filtrando pelo nome do animal ou do próprio dono.
* **Rede de Avistamentos:** Qualquer usuário logado pode reportar pistas diretamente na página da ocorrência do animal desaparecido.
* **Resolução:** O dono tem autonomia para alterar o status do pet para "Encontrado" e remover a ocorrência do feed principal.

---

## 📸 Demonstração do Sistema

Abaixo estão algumas telas das principais funcionalidades do nosso sistema operando no navegador:

<div align="center">
  <img src="docs/screenshots/feed.png" alt="Feed de Ocorrências" width="80%">
  <p><em>Mural principal com as ocorrências de animais desaparecidos.</em></p>
</div>

<div align="center">
  <img src="docs/screenshots/publicar.png" alt="Publicar Pet Perdido" width="80%">
  <p><em>Formulário para registro de uma nova ocorrência.</em></p>
</div>

*(Para conferir as demais telas como Login, Perfil e Histórico, consulte o [repositório do projeto](https://github.com/davircarvalh0/petfinder-edoo)).*

---

## 🛠️ Tecnologias

* **Backend:** C++17 com servidor HTTP (`httplib`)
* **Banco de Dados:** SQLite3
* **Frontend:** HTML, CSS e JavaScript puro
