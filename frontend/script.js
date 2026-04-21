document.getElementById('loginForm').addEventListener('submit', async function(evento) {
    evento.preventDefault(); // Evita que a página recarregue

    // Pega os dados do formulário e prepara para envio
    const form = evento.target;
    const formData = new URLSearchParams(new FormData(form));

    try {
        // Faz a requisição POST para a rota /api/login no C++
        const resposta = await fetch('/api/login', {
            method: 'POST',
            headers: { 'Content-Type': 'application/x-www-form-urlencoded' },
            body: formData.toString()
        });

        // Converte a resposta do C++ (que será um JSON)
        const resultado = await resposta.json();
        const mensagemEl = document.getElementById('mensagem');

        // Analisa a resposta
        if (resultado.sucesso) {
            mensagemEl.style.color = '#27ae60'; // Verde
            mensagemEl.textContent = 'Login aprovado! Redirecionando...';
            // Aqui você poderia redirecionar para outra página: window.location.href = "/dashboard.html";
        } else {
            mensagemEl.style.color = '#e74c3c'; // Vermelho
            mensagemEl.textContent = 'Erro: ' + resultado.erro;
        }
    } catch (erro) {
        console.error('Erro na conexão:', erro);
    }
});