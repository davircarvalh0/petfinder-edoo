// Aguarda a página carregar completamente
document.addEventListener("DOMContentLoaded", () => {
    carregarAnimais();

    // lógica para publicar nova ocorrência
    const formOcorrencia = document.getElementById("form-ocorrencia");

    if (formOcorrencia) {
        formOcorrencia.addEventListener("submit", async (e) => {
            e.preventDefault(); // impede a página de recarregar
            const donoId = localStorage.getItem("usuarioLogadoId"); //verifica se o usuário fez login pegando o ID que o C++ enviou
            
            if (!donoId) {
                alert("Você precisa fazer login primeiro para publicar!");
                window.location.href = 'index.html'; // manda de volta pra tela de login
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
                // Checkbox: se estiver marcado envia "1", senão "0"
                usa_coleira: document.getElementById("usa_coleira").checked ? "1" : "0",
                eh_castrado: document.getElementById("eh_castrado").checked ? "1" : "0",
                localizacao: document.getElementById("localizacao").value,
                descricao: document.getElementById("descricao").value
            };

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

        lista.innerHTML = ''; // Limpa a lista antes de carregar

        animais.forEach(animal => {
            const card = document.createElement('div');
            // A classe 'pet-card' é o que vai puxar o design bonito do CSS!
            card.className = "pet-card"; 

            const coleiraTexto = animal.usa_coleira === "1" ? "Sim" : "Não";
            const castradoTexto = animal.eh_castrado === "1" ? "Sim" : "Não";

            // Monta a estrutura HTML do Card
            card.innerHTML = `
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
            `;
            lista.appendChild(card);
        });
    } catch (erro) {
        console.error("Erro ao carregar o feed:", erro);
    }
}