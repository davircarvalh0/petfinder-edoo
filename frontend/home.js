let fotoBase64 = "";

// aguarda a página carregar completamente
document.addEventListener("DOMContentLoaded", () => {
    carregarAnimais();

    const fotoInput = document.getElementById("fotoAnimal");
    if (fotoInput) {
        fotoInput.addEventListener("change", function(event) {
            const file = event.target.files[0];
            if (file) {
                // limite de 2MB
                if (file.size > 2 * 1024 * 1024) {
                    alert("A imagem é muito grande. Escolha uma foto com menos de 2MB.");
                    this.value = ""; 
                    return;
                }
                const reader = new FileReader();
                reader.onload = function(e) {
                    fotoBase64 = e.target.result;
                    const preview = document.getElementById("previewFoto");
                    preview.src = fotoBase64;
                    preview.style.display = "block";
                };
                reader.readAsDataURL(file);
            }
        });
    }

    // lógica para publicar nova ocorrência
    const formOcorrencia = document.getElementById("form-ocorrencia");

    if (formOcorrencia) {
        formOcorrencia.addEventListener("submit", async (e) => {
            e.preventDefault(); // impede a página de recarregar
            const donoId = localStorage.getItem("usuarioLogadoId"); 
            
            if (!donoId) {
                alert("Você precisa fazer login primeiro para publicar!");
                window.location.href = 'index.html'; 
                return;
            }

            // pega os campos do HTML de forma segura
            const racaInput = document.getElementById("raca");
            const localizacaoInput = document.getElementById("localizacao");
            const descricaoInput = document.getElementById("descricao");

            // trava de segurança
            if (!racaInput || !localizacaoInput || !descricaoInput) {
                alert("Erro no código: Faltam os IDs corretos no HTML.");
                return;
            }

            // monta os dados
            let fotoParaEnviar = "";
            const preview = document.getElementById("previewFoto");
            if (preview && preview.src && preview.src.startsWith("data:image")) {
                fotoParaEnviar = preview.src;
            }

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

            console.log("DADOS QUE SERÃO ENVIADOS:", dadosPet);
            if (!fotoParaEnviar) {
                alert("Atenção: A foto se perdeu ou não foi selecionada! Tente selecionar novamente.");
                return; // bloqueia o envio
            }

            try {
                const resposta = await fetch('/api/animais', {
                    method: 'POST',
                    headers: { 'Content-Type': 'application/json' },
                    body: JSON.stringify(dadosPet)
                });

                const resultado = await resposta.json();

                if (resultado.sucesso) {
                    alert("Ocorrência publicada com sucesso!");
                    formOcorrencia.reset(); // limpa os campos
                    carregarAnimais();      // atualiza o Feed imediatamente
                } else {
                    alert("Erro ao publicar: " + resultado.erro);
                }
            } catch (erro) {
                console.error("Erro na requisição:", erro);
                alert("Erro de conexão com o servidor C++.");
            }
        });
    }
});

async function carregarAnimais() {
    try {
        const response = await fetch('/api/animais');
        const animais = await response.json();

        const lista = document.getElementById('lista-animais');
        if (!lista) return;

        lista.innerHTML = ''; // limpa a lista antes de carregar

        animais.forEach(animal => {
            const card = document.createElement('div');
            card.className = "pet-card"; 

            const coleiraTexto = animal.usa_coleira === "1" ? "Sim" : "Não";
            const castradoTexto = animal.eh_castrado === "1" ? "Sim" : "Não";

            const fotoHtml = animal.foto 
                ? `<img src="${animal.foto}" alt="Foto do pet" style="width: 100%; height: 200px; object-fit: cover; border-radius: 8px 8px 0 0; margin-bottom: 10px;">` 
                : `<div style="width: 100%; height: 150px; background: #eee; display: flex; align-items: center; justify-content: center; border-radius: 8px 8px 0 0; color: #888; margin-bottom: 10px;">Sem foto</div>`;
            
            card.innerHTML = `
                ${fotoHtml}
                <div class="pet-card-header">
                    <h3>🐾 ${animal.nome}</h3>
                    <span class="status-badge">Desaparecido</span>
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
                        <p><strong>📝 Descrição:</strong> ${animal.descricao || "Nenhuma descrição adicional."}</p>
                    </div>
                </div>

                <div class="pet-card-footer">
                    <p>👤 <strong>Dono:</strong> ${animal.dono_nome || "Desconhecido"}</p>
                    <p>📞 <strong>Contato:</strong> ${animal.dono_telefone || "Sem contato"}</p>
                </div>
                
                <div class="comentarios-section">
                    <h4 class="comentarios-titulo">👁️ Avistamentos / Pistas</h4>
                    
                    <div class="lista-comentarios" id="avistamentos-${animal.id}">
                        <p style="color: #888; font-size: 0.9em; text-align: center;">Carregando avistamentos...</p>
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
    } catch (erro) {
        console.error("Erro ao carregar o feed:", erro);
    }
}

window.carregarAvistamentos = async function(animalId) {
    const container = document.getElementById(`avistamentos-${animalId}`);
    if (!container) return;

    try {
        const response = await fetch(`/api/avistamentos?animal_id=${animalId}`);
        if (!response.ok) {
            container.innerHTML = `<p style="color: #888; font-size: 0.85em; text-align: center;">Seja o primeiro a reportar uma pista.</p>`;
            return;
        }

        const avistamentos = await response.json();
        
        if (avistamentos.length === 0) {
            container.innerHTML = `<p style="color: #888; font-size: 0.85em; text-align: center;">Nenhuma pista registrada ainda.</p>`;
            return;
        }

        container.innerHTML = ''; 
        avistamentos.forEach(av => {
            container.innerHTML += `
                <div class="comentario-item">
                    <p class="comentario-texto"><strong>Relato:</strong> ${av.descricao}</p>
                    <span class="comentario-data">${av.data}</span>
                </div>
            `;
        });
    } catch (erro) {
        console.error(`Erro ao carregar avistamentos do pet ${animalId}:`, erro);
        container.innerHTML = `<p style="color: #dc3545; font-size: 0.85em;">Erro ao carregar avistamentos.</p>`;
    }
};

window.enviarAvistamento = async function(animalId) {
    const input = document.getElementById(`input-avistamento-${animalId}`);
    const descricao = input.value;
    
    if (!descricao.trim()) {
        alert("O relato não pode estar vazio.");
        return;
    }

    const usuarioId = localStorage.getItem("usuarioLogadoId");
    if (!usuarioId) {
        alert("Você precisa estar logado para reportar uma pista.");
        return;
    }

    const dataAtual = new Date().toLocaleDateString('pt-BR');

    const payload = {
        animal_id: animalId.toString(),
        usuario_id: usuarioId.toString(),
        descricao: descricao,
        data: dataAtual
    };

    console.log("Enviando avistamento:", payload);

    try {
        const response = await fetch('/api/avistamentos', {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify(payload)
        });

        const resultado = await response.json();

        if (resultado.sucesso) {
            input.value = ''; 
            window.carregarAvistamentos(animalId); 
        } else {
            alert("Erro ao enviar: " + (resultado.erro || "Falha no servidor."));
        }
    } catch (erro) {
        console.error("Erro ao enviar avistamento:", erro);
        alert("Erro de conexão. O servidor backend está rodando?");
    }
};