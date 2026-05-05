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
});

// Ação do botão de sair
const btnSair = document.getElementById('btnSair');
if (btnSair) {
    btnSair.addEventListener('click', () => {
        localStorage.removeItem('usuarioAtivo'); 
    });
}

// Função para buscar e renderizar as postagens
async function carregarPostagens() {
    try {
        // NOVO: { cache: 'no-store' } obriga o navegador a pegar os dados frescos do C++!
        const resposta = await fetch('/api/posts', { cache: 'no-store' });
        const postagens = await resposta.json();
        const container = document.getElementById('listaPostagens');
        
        container.innerHTML = ''; 

        postagens.reverse().forEach(post => {
            const postElement = document.createElement('div');
            postElement.className = 'post';
            
            let comentariosHTML = '';
            post.comments.forEach(comentario => {
                comentariosHTML += `<div class="comment"><strong>${comentario.autor}:</strong> ${comentario.texto}</div>`;
            });

            postElement.innerHTML = `
                <div class="post-author">${post.autor}</div>
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

// Ação do botão de Postar
document.getElementById('btnPostar').addEventListener('click', async () => {
    let texto = document.getElementById('novoPostTexto').value;
    if (!texto.trim()) return;

    // NOVO: Limpa aspas e quebras de linha para não quebrar o JSON do C++
    texto = texto.replace(/"/g, "'").replace(/\n/g, " - ");

    const autor = localStorage.getItem('usuarioAtivo') || 'Anônimo';

    try {
        await fetch('/api/posts', {
            method: 'POST',
            headers: { 'Content-Type': 'application/x-www-form-urlencoded' },
            body: `conteudo=${encodeURIComponent(texto)}&autor=${encodeURIComponent(autor)}`
        });

        document.getElementById('novoPostTexto').value = '';
        carregarPostagens(); 
    } catch (erro) {
        console.error("Erro ao publicar:", erro);
    }
});

// Ação do botão de Comentar
async function adicionarComentario(postId) {
    const input = document.getElementById(`input-comentario-${postId}`);
    const texto = input.value;
    if (!texto.trim()) return;

    const autor = localStorage.getItem('usuarioAtivo') || 'Anônimo';

    try {
        await fetch('/api/comments', {
            method: 'POST',
            headers: { 'Content-Type': 'application/x-www-form-urlencoded' },
            body: `postId=${postId}&texto=${encodeURIComponent(texto)}&autor=${encodeURIComponent(autor)}`
        });

        input.value = ''; // Limpa o campo
        carregarPostagens(); 
    } catch (erro) {
        console.error("Erro ao comentar:", erro);
    }
}