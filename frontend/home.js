let todosAnimais = []; // guarda todos os animais para filtrar localmente

//INICIALIZACAO

document.addEventListener("DOMContentLoaded", () => {
    carregarAnimais();
    configurarPreviewFoto();
    configurarFormularioPublicar();

    // filtra em tempo real enquanto digita
    const filtro = document.getElementById("filtro-busca");
    if (filtro) filtro.addEventListener("input", filtrarAnimais);
});

//ABAS

window.mudarAba = function(aba) {
    // esconde todas as secoes
    document.querySelectorAll(".secao").forEach(s => s.classList.remove("ativa"));
    document.querySelectorAll(".aba-btn").forEach(b => b.classList.remove("ativa"));

    // mostra a secao escolhida
    document.getElementById(`secao-${aba}`).classList.add("ativa");

    // marca o botao como ativo
    const botoes = document.querySelectorAll(".aba-btn");
    const mapa = { feed: 0, publicar: 1, minhas: 2, perfil: 3 };
    botoes[mapa[aba]].classList.add("ativa");

    // carrega dados especificos de cada aba
    if (aba === "minhas") carregarMinhasOcorrencias();
    if (aba === "perfil") carregarPerfil();
};

// FEED 

async function carregarAnimais() {
    try {
        const response = await fetch('/api/animais');
        todosAnimais = await response.json();
        renderizarAnimais(todosAnimais);
    } catch (erro) {
        console.error("Erro ao carregar o feed:", erro);
    }
}

// filtra por nome do pet ou nome do dono
window.filtrarAnimais = function() {
    const termo = document.getElementById("filtro-busca").value.toLowerCase().trim();
    if (!termo) { renderizarAnimais(todosAnimais); return; }
    const filtrados = todosAnimais.filter(a =>
        (a.nome && a.nome.toLowerCase().includes(termo)) ||
        (a.dono_nome && a.dono_nome.toLowerCase().includes(termo))
    );
    renderizarAnimais(filtrados);
};

window.limparFiltro = function() {
    document.getElementById("filtro-busca").value = "";
    renderizarAnimais(todosAnimais);
};

function renderizarAnimais(animais) {
    const lista = document.getElementById('lista-animais');
    if (!lista) return;
    lista.innerHTML = '';

    if (animais.length === 0) {
        lista.innerHTML = '<p style="text-align:center; color:#888; padding:30px 0;">Nenhuma ocorrência encontrada.</p>';
        return;
    }

    animais.forEach(animal => {
        const card = document.createElement('div');
        card.className = "pet-card";

        const coleiraTexto = animal.usa_coleira === "1" ? "Sim" : "Não";
        const castradoTexto = animal.eh_castrado === "1" ? "Sim" : "Não";

        const fotoHtml = animal.foto
            ? `<img src="${animal.foto}" alt="Foto do pet" style="width:100%; height:200px; object-fit:cover; border-radius:8px 8px 0 0; margin-bottom:10px;">`
            : `<div style="width:100%; height:150px; background:#eee; display:flex; align-items:center; justify-content:center; border-radius:8px 8px 0 0; color:#888; margin-bottom:10px;">Sem foto</div>`;

        const statusCor = animal.status === "ENCONTRADO" ? "#28a745" : "#dc3545";
        const statusTexto = animal.status === "ENCONTRADO" ? "✅ Encontrado" : "⚠️ Desaparecido";

        card.innerHTML = `
            ${fotoHtml}
            <div class="pet-card-header">
                <h3>🐾 ${animal.nome}</h3>
                <span class="status-badge" style="background:${statusCor};">${statusTexto}</span>
            </div>
            <div class="pet-card-body">
                <div class="pet-badges">
                    <span class="badge" style="background:#e9ecef;">${animal.tipo.toUpperCase()}</span>
                    <span class="badge">Raça: ${animal.raca}</span>
                    <span class="badge">Cor: ${animal.cor}</span>
                </div>
                <div class="pet-details">
                    <div><span>Porte:</span> <strong>${animal.porte}</strong></div>
                    <div><span>Pelagem:</span> <strong>${animal.pelagem}</strong></div>
                    <div><span>Idade:</span> <strong>${animal.idade} anos</strong></div>
                    <div><span>Peso:</span> <strong>${animal.peso} kg</strong></div>
                    <div><span>Coleira:</span> <strong>${coleiraTexto}</strong></div>
                    <div><span>Castrado:</span> <strong>${castradoTexto}</strong></div>
                </div>
                <div class="pet-extra">
                    <p><strong>📍 Visto por último:</strong> ${animal.localizacao || "Não informada"}</p>
                    <p><strong>📝 Descrição:</strong> ${animal.descricao || "Nenhuma descrição."}</p>
                </div>
            </div>
            <div class="pet-card-footer">
                <p>👤 <strong>Dono:</strong> ${animal.dono_nome || "Desconhecido"}</p>
                <p>📞 <strong>Contato:</strong> ${animal.dono_telefone || "Sem contato"}</p>
            </div>
            <div class="comentarios-section">
                <h4 class="comentarios-titulo">👁️ Avistamentos / Pistas</h4>
                <div class="lista-comentarios" id="avistamentos-${animal.id}">
                    <p style="color:#888; font-size:0.9em;">Carregando...</p>
                </div>
                <div class="novo-comentario">
                    <input type="text" id="input-avistamento-${animal.id}" placeholder="Viu o ${animal.nome}? Deixe um relato...">
                    <button onclick="window.enviarAvistamento('${animal.id}')">Enviar</button>
                </div>
            </div>
        `;
        lista.appendChild(card);
        window.carregarAvistamentos(animal.id);
    });
}

//MINHAS OCORRENCIAS 

async function carregarMinhasOcorrencias() {
    const donoId = localStorage.getItem("usuarioLogadoId");
    const lista = document.getElementById("lista-minhas-ocorrencias");
    if (!donoId) {
        lista.innerHTML = '<p style="text-align:center; color:#888;">Faça login para ver suas ocorrências.</p>';
        return;
    }
    lista.innerHTML = '<p style="text-align:center; color:#888; padding:20px;">Carregando...</p>';

    try {
        const response = await fetch(`/api/animais/meus?dono_id=${donoId}`);
        const animais = await response.json();

        if (animais.length === 0) {
            lista.innerHTML = '<p style="text-align:center; color:#888; padding:30px 0;">Você ainda não publicou nenhuma ocorrência.</p>';
            return;
        }

        lista.innerHTML = '';
        animais.forEach(animal => {
            const statusTexto = animal.status === "ENCONTRADO" ? "✅ Encontrado" : "⚠️ Desaparecido";
            const statusCor = animal.status === "ENCONTRADO" ? "#28a745" : "#e74c3c";

            const card = document.createElement('div');
            card.className = "minha-ocorrencia-card";
            card.innerHTML = `
                <div style="display:flex; justify-content:space-between; align-items:center;">
                    <h4>🐾 ${animal.nome}</h4>
                    <span style="background:${statusCor}; color:white; padding:4px 12px; border-radius:20px; font-size:0.85rem; font-weight:bold;">${statusTexto}</span>
                </div>
                <p style="color:#555; margin:4px 0; font-size:0.9rem;">Tipo: ${animal.tipo} | Raça: ${animal.raca} | Cor: ${animal.cor}</p>
                <p style="color:#555; margin:4px 0; font-size:0.9rem;">📍 ${animal.localizacao || "Local não informado"}</p>
                <p style="color:#555; margin:4px 0; font-size:0.9rem;">📝 ${animal.descricao || "Sem descrição"}</p>
                <div class="minha-ocorrencia-acoes">
                    <button onclick="abrirModalEdicao(${JSON.stringify(animal).replace(/"/g, '&quot;')})"
                        style="background:#0d6efd; color:white;">✏️ Editar</button>
                    <button onclick="marcarEncontrado('${animal.id}')"
                        style="background:#28a745; color:white;" ${animal.status === "ENCONTRADO" ? "disabled" : ""}>✅ Marcar Encontrado</button>
                    <button onclick="removerAnimal('${animal.id}')"
                        style="background:#dc3545; color:white;">🗑️ Remover</button>
                </div>
            `;
            lista.appendChild(card);
        });
    } catch (erro) {
        lista.innerHTML = '<p style="text-align:center; color:#dc3545;">Erro ao carregar ocorrências.</p>';
        console.error(erro);
    }
}

//EDITAR OCORRENCIA 

window.abrirModalEdicao = function(animal) {
    document.getElementById("edit-animal-id").value  = animal.id;
    document.getElementById("edit-nome").value        = animal.nome || "";
    document.getElementById("edit-raca").value        = animal.raca || "";
    document.getElementById("edit-cor").value         = animal.cor || "";
    document.getElementById("edit-porte").value       = animal.porte || "";
    document.getElementById("edit-pelagem").value     = animal.pelagem || "";
    document.getElementById("edit-peso").value        = animal.peso || "";
    document.getElementById("edit-idade").value       = animal.idade || "";
    document.getElementById("edit-localizacao").value = animal.localizacao || "";
    document.getElementById("edit-descricao").value   = animal.descricao || "";
    document.getElementById("modal-editar-ocorrencia").classList.add("aberto");
};

window.salvarEdicaoOcorrencia = async function() {
    const id = document.getElementById("edit-animal-id").value;
    const dados = {
        nome:        document.getElementById("edit-nome").value,
        raca:        document.getElementById("edit-raca").value,
        cor:         document.getElementById("edit-cor").value,
        porte:       document.getElementById("edit-porte").value,
        pelagem:     document.getElementById("edit-pelagem").value,
        peso:        document.getElementById("edit-peso").value,
        idade:       document.getElementById("edit-idade").value,
        localizacao: document.getElementById("edit-localizacao").value,
        descricao:   document.getElementById("edit-descricao").value,
    };

    try {
        const response = await fetch(`/api/animais/${id}`, {
            method: 'PUT',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify(dados)
        });
        const resultado = await response.json();
        if (resultado.sucesso) {
            alert("Ocorrência atualizada com sucesso!");
            fecharModal("modal-editar-ocorrencia");
            carregarMinhasOcorrencias();
            carregarAnimais();
        } else {
            alert("Erro ao salvar: " + (resultado.erro || "Falha no servidor."));
        }
    } catch (erro) {
        alert("Erro de conexão com o servidor.");
    }
};

//PERFIL 

async function carregarPerfil() {
    const donoId = localStorage.getItem("usuarioLogadoId");
    if (!donoId) return;
    try {
        const response = await fetch(`/api/perfil?id=${donoId}`);
        const dados = await response.json();
        document.getElementById("perfil-nome").textContent     = dados.nome     || "—";
        document.getElementById("perfil-email").textContent    = dados.email    || "—";
        document.getElementById("perfil-telefone").textContent = dados.telefone || "—";
        document.getElementById("perfil-cpf").textContent      = dados.cpf      || "—";
    } catch (erro) {
        console.error("Erro ao carregar perfil:", erro);
    }
}

window.abrirModalPerfil = function() {
    // limpa os campos antes de abrir
    document.getElementById("edit-perfil-email").value            = "";
    document.getElementById("edit-perfil-telefone").value         = "";
    document.getElementById("edit-perfil-senha").value            = "";
    document.getElementById("edit-perfil-senha-confirmar").value  = "";
    document.getElementById("modal-editar-perfil").classList.add("aberto");
};

window.salvarEdicaoPerfil = async function() {
    const donoId  = localStorage.getItem("usuarioLogadoId");
    const email   = document.getElementById("edit-perfil-email").value.trim();
    const tel     = document.getElementById("edit-perfil-telefone").value.trim();
    const senha   = document.getElementById("edit-perfil-senha").value;
    const confirmar = document.getElementById("edit-perfil-senha-confirmar").value;

    // valida senhas se preenchidas
    if (senha && senha !== confirmar) {
        alert("As senhas não coincidem!");
        return;
    }
    if (!email && !tel && !senha) {
        alert("Preencha pelo menos um campo para atualizar.");
        return;
    }

    const payload = { id: donoId };
    if (email) payload.email     = email;
    if (tel)   payload.telefone  = tel;
    if (senha) payload.senha     = senha;

    try {
        const response = await fetch('/api/perfil', {
            method: 'PUT',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify(payload)
        });
        const resultado = await response.json();
        if (resultado.sucesso) {
            alert("Perfil atualizado com sucesso!");
            fecharModal("modal-editar-perfil");
            carregarPerfil();
        } else {
            alert("Erro ao atualizar: " + (resultado.erro || "Falha no servidor."));
        }
    } catch (erro) {
        alert("Erro de conexão com o servidor.");
    }
};

window.fecharModal = function(id) {
    document.getElementById(id).classList.remove("aberto");
};

// fecha modal clicando fora
document.addEventListener("click", (e) => {
    if (e.target.classList.contains("modal-overlay")) {
        e.target.classList.remove("aberto");
    }
});

// ACOES DO DONO (FEED) 

window.marcarEncontrado = async function(animalId) {
    if (!confirm("Confirmar que o pet foi encontrado?")) return;
    try {
        const response = await fetch(`/api/animais/${animalId}/encontrado`, { method: 'PUT' });
        const resultado = await response.json();
        if (resultado.sucesso) {
            alert("Status atualizado! Que ótima notícia! 🎉");
            carregarAnimais();
            carregarMinhasOcorrencias();
        } else {
            alert("Erro: " + (resultado.erro || "Falha no servidor."));
        }
    } catch (erro) { alert("Erro de conexão."); }
};

window.removerAnimal = async function(animalId) {
    if (!confirm("Remover esta ocorrência? Esta ação não pode ser desfeita.")) return;
    try {
        const response = await fetch(`/api/animais/${animalId}`, { method: 'DELETE' });
        const resultado = await response.json();
        if (resultado.sucesso) {
            alert("Ocorrência removida.");
            carregarAnimais();
            carregarMinhasOcorrencias();
        } else {
            alert("Erro: " + (resultado.erro || "Falha no servidor."));
        }
    } catch (erro) { alert("Erro de conexão."); }
};

// AVISTAMENTOS 

window.carregarAvistamentos = async function(animalId) {
    const container = document.getElementById(`avistamentos-${animalId}`);
    if (!container) return;
    try {
        const response = await fetch(`/api/avistamentos?animal_id=${animalId}`);
        if (!response.ok) { container.innerHTML = `<p style="color:#888; font-size:0.85em;">Seja o primeiro a reportar.</p>`; return; }
        const avistamentos = await response.json();
        if (avistamentos.length === 0) { container.innerHTML = `<p style="color:#888; font-size:0.85em;">Nenhuma pista ainda.</p>`; return; }
        container.innerHTML = '';
        avistamentos.forEach(av => {
            container.innerHTML += `<div class="comentario-item"><p class="comentario-texto"><strong>Relato:</strong> ${av.descricao}</p><span class="comentario-data">${av.data}</span></div>`;
        });
    } catch (e) { container.innerHTML = `<p style="color:#dc3545; font-size:0.85em;">Erro ao carregar.</p>`; }
};

window.enviarAvistamento = async function(animalId) {
    const input = document.getElementById(`input-avistamento-${animalId}`);
    if (!input.value.trim()) { alert("O relato não pode estar vazio."); return; }
    const usuarioId = localStorage.getItem("usuarioLogadoId");
    if (!usuarioId) { alert("Você precisa estar logado."); return; }
    try {
        const response = await fetch('/api/avistamentos', {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify({ animal_id: animalId.toString(), usuario_id: usuarioId, descricao: input.value, data: new Date().toLocaleDateString('pt-BR') })
        });
        const resultado = await response.json();
        if (resultado.sucesso) { input.value = ''; window.carregarAvistamentos(animalId); }
        else alert("Erro: " + (resultado.erro || "Falha."));
    } catch (e) { alert("Erro de conexão."); }
};
//PUBLICAR FORMUlARIO

function configurarPreviewFoto() {
    const fotoInput = document.getElementById("fotoAnimal");
    if (!fotoInput) return;
    fotoInput.addEventListener("change", function(event) {
        const file = event.target.files[0];
        if (!file) return;
        if (file.size > 2 * 1024 * 1024) { alert("Foto maior que 2MB. Escolha outra."); this.value = ""; return; }
        const reader = new FileReader();
        reader.onload = function(e) {
            const preview = document.getElementById("previewFoto");
            preview.src = e.target.result;
            preview.style.display = "block";
        };
        reader.readAsDataURL(file);
    });
}

function configurarFormularioPublicar() {
    const form = document.getElementById("form-ocorrencia");
    if (!form) return;
    form.addEventListener("submit", async (e) => {
        e.preventDefault();
        const donoId = localStorage.getItem("usuarioLogadoId");
        if (!donoId) { alert("Faça login primeiro!"); window.location.href = 'index.html'; return; }

        const preview = document.getElementById("previewFoto");
        const fotoParaEnviar = (preview && preview.src && preview.src.startsWith("data:image")) ? preview.src : "";
        if (!fotoParaEnviar) { alert("Selecione uma foto antes de publicar."); return; }

        const dadosPet = {
            dono_id: donoId,
            nome: document.getElementById("nome").value || "Desconhecido",
            tipo: document.getElementById("tipo").value || "cachorro",
            raca: document.getElementById("raca").value || "Desconhecida",
            cor: document.getElementById("cor").value || "Não informada",
            porte: document.getElementById("porte").value || "Não informado",
            pelagem: document.getElementById("pelagem").value || "Não informada",
            peso: document.getElementById("peso").value || "0",
            idade: document.getElementById("idade").value || "0",
            usa_coleira: document.getElementById("usa_coleira").checked ? "1" : "0",
            eh_castrado: document.getElementById("eh_castrado").checked ? "1" : "0",
            localizacao: document.getElementById("localizacao").value,
            descricao: document.getElementById("descricao").value,
            foto: fotoParaEnviar
        };

        try {
            const resposta = await fetch('/api/animais', { method: 'POST', headers: { 'Content-Type': 'application/json' }, body: JSON.stringify(dadosPet) });
            const resultado = await resposta.json();
            if (resultado.sucesso) {
                alert("Ocorrência publicada!");
                form.reset();
                preview.style.display = "none";
                mudarAba('feed');
                carregarAnimais();
            } else alert("Erro: " + resultado.erro);
        } catch (e) { alert("Erro de conexão."); }
    });
}