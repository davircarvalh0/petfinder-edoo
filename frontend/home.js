document.addEventListener("DOMContentLoaded", () => {
    // Recupera o nome do usuário salvo no login
    const nomeUsuario = localStorage.getItem('usuarioAtivo');
    
    // Atualiza a saudação no cabeçalho
    if (nomeUsuario) {
        const saudacaoEl = document.getElementById('saudacaoUsuario');
        if (saudacaoEl) saudacaoEl.textContent = `Olá, ${nomeUsuario}`;
    }

    // Carrega as postagens assim que a página abrir
    carregarPostagens();

    const formPublicacao = document.getElementById('form-publicacao');
    const mensagemRetorno = document.getElementById('mensagem-retorno');

    if (formPublicacao) {
        formPublicacao.addEventListener('submit', async (evento) => {
            evento.preventDefault(); // Impede a página de recarregar
            
            const formData = new FormData(formPublicacao);
            
            // Você pode adicionar o autor (dono) no FormData para o backend em C++ saber quem postou
            formData.append('autor', nomeUsuario || 'Anônimo');

            try {
                // Ajuste a rota '/api/ocorrencias' conforme estiver no seu main.cpp do servidor
                const resposta = await fetch('/api/ocorrencias', {
                    method: 'POST',
                    body: formData // Não envie 'Content-Type', o navegador gera o boundary do multipart automaticamente
                });

                if (resposta.ok) {
                    mensagemRetorno.style.color = 'green';
                    mensagemRetorno.innerText = 'Cachorro registrado com sucesso!';
                    formPublicacao.reset(); // Limpa os campos
                    carregarPostagens();    // Recarrega o feed para mostrar a nova ocorrência
                } else {
                    const erroInfo = await resposta.text();
                    mensagemRetorno.style.color = 'red';
                    mensagemRetorno.innerText = `Erro ao salvar: ${erroInfo}`;
                }
            } catch (erro) {
                console.error('Erro de comunicação com o servidor:', erro);
                mensagemRetorno.style.color = 'red';
                mensagemRetorno.innerText = 'Servidor indisponível. Tente novamente.';
            }
        });
    }
});

const btnSair = document.getElementById('btnSair');
if (btnSair) {
    btnSair.addEventListener('click', () => {
        localStorage.removeItem('usuarioAtivo'); 
    });
}

async function carregarPostagens() {
    try {
        const resposta = await fetch('/api/posts', { cache: 'no-store' });
        const postagens = await resposta.json();
        const container = document.getElementById('listaPostagens');
        
        container.innerHTML = ''; 

        postagens.reverse().forEach(post => {
            const postElement = document.createElement('div');
            postElement.className = 'post';
            
            let comentariosHTML = '';
            // Valida se comments existe antes de iterar
            if (post.comments && Array.isArray(post.comments)) {
                post.comments.forEach(comentario => {
                    comentariosHTML += `<div class="comment"><strong>${comentario.autor}:</strong> ${comentario.texto}</div>`;
                });
            }

            postElement.innerHTML = `
                <div class="post-author">${post.autor}</div>
                <!-- Se no futuro o backend retornar o caminho da foto, você pode adicionar uma <img> aqui -->
                <div class="post-content">${post.conteudo}</div>
                <div class="comments-section">
                    ${comentariosHTML}
                    <div class="add-comment">
                        <input type="text" id="input-comentario-${post.id}" placeholder="Escreva um comentário...">
                        <button onclick="adicionarComentario(${post.id})">Comentar</button>
                    </div>
                </div>
            `;
            container.appendChild(postElement);
        });
    } catch (erro) {
        console.error("Erro ao carregar postagens:", erro);
    }
}

async function adicionarComentario(postId) {
    const input = document.getElementById(`input-comentario-${postId}`);
    const texto = input.value;
    if (!texto.trim()) return;

    const textoLimpo = texto.replace(/"/g, "'").replace(/\n/g, " - ");
    const autor = localStorage.getItem('usuarioAtivo') || 'Anônimo';

    try {
        await fetch('/api/comments', {
            method: 'POST',
            headers: { 'Content-Type': 'application/x-www-form-urlencoded' },
            body: `postId=${postId}&texto=${encodeURIComponent(textoLimpo)}&autor=${encodeURIComponent(autor)}`
        });

        input.value = ''; // Limpa o campo
        carregarPostagens(); 
    } catch (erro) {
        console.error("Erro ao comentar:", erro);
    }
}