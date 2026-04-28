document.addEventListener("DOMContentLoaded", carregarPostagens);

async function carregarPostagens() {
    const resposta = await fetch('/api/posts');
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
}

document.getElementById('btnPostar').addEventListener('click', async () => {
    const texto = document.getElementById('novoPostTexto').value;
    if (!texto.trim()) return;

    await fetch('/api/posts', {
        method: 'POST',
        headers: { 'Content-Type': 'application/x-www-form-urlencoded' },
        body: `conteudo=${encodeURIComponent(texto)}`
    });

    document.getElementById('novoPostTexto').value = '';
    carregarPostagens(); 
});

async function adicionarComentario(postId) {
    const input = document.getElementById(`input-comentario-${postId}`);
    const texto = input.value;
    if (!texto.trim()) return;

    await fetch('/api/comments', {
        method: 'POST',
        headers: { 'Content-Type': 'application/x-www-form-urlencoded' },
        body: `postId=${postId}&texto=${encodeURIComponent(texto)}`
    });

    carregarPostagens(); 
}