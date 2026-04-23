document.getElementById('loginForm').addEventListener('submit', async function(evento) {
    evento.preventDefault(); 

    const form = evento.target;
    const formData = new URLSearchParams(new FormData(form));

    try {
        const resposta = await fetch('/api/login', {
            method: 'POST',
            headers: { 'Content-Type': 'application/x-www-form-urlencoded' },
            body: formData.toString()
        });

        const resultado = await resposta.json();
        const mensagemEl = document.getElementById('mensagem');

        if (resultado.sucesso) {
            mensagemEl.style.color = '#27ae60';
            mensagemEl.textContent = 'Login aprovado! Redirecionando...';
        } else {
            mensagemEl.style.color = '#e74c3c';
            mensagemEl.textContent = 'Erro: ' + resultado.erro;
        }
    } catch (erro) {
        console.error('Erro na conexão:', erro);
    }
});
