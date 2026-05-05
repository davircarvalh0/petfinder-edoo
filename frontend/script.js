// Alternar entre telas de Login e Cadastro
document.getElementById('btnIrParaCadastro').addEventListener('click', (e) => {
    e.preventDefault();
    document.getElementById('secaoLogin').style.display = 'none';
    document.getElementById('secaoCadastro').style.display = 'block';
});

document.getElementById('btnIrParaLogin').addEventListener('click', (e) => {
    e.preventDefault();
    document.getElementById('secaoCadastro').style.display = 'none';
    document.getElementById('secaoLogin').style.display = 'block';
});

// Lógica de Cadastro
document.getElementById('cadastroForm').addEventListener('submit', async function(evento) {
    evento.preventDefault(); 

    const form = evento.target;
    const formData = new URLSearchParams(new FormData(form));
    const mensagemEl = document.getElementById('mensagemCadastro');

    try {
        // Envia os dados para a rota de cadastro no seu backend C++
        const resposta = await fetch('/api/register', {
            method: 'POST',
            headers: { 'Content-Type': 'application/x-www-form-urlencoded' },
            body: formData.toString()
        });

        const resultado = await resposta.json();

        if (resultado.sucesso) {
            mensagemEl.style.color = '#27ae60';
            mensagemEl.textContent = 'Cadastro realizado com sucesso! Faça login.';
            form.reset();
            // Volta para a tela de login após 2 segundos
            setTimeout(() => document.getElementById('btnIrParaLogin').click(), 2000);
        } else {
            mensagemEl.style.color = '#e74c3c';
            mensagemEl.textContent = 'Erro: ' + resultado.erro;
        }
    } catch (erro) {
        console.error('Erro na conexão:', erro);
        mensagemEl.style.color = '#e74c3c';
        mensagemEl.textContent = 'Erro ao tentar conectar ao servidor.';
    }
});

// Lógica de Login
document.getElementById('loginForm').addEventListener('submit', async function(evento) {
    evento.preventDefault(); 

    const form = evento.target;
    const formData = new URLSearchParams(new FormData(form));
    const mensagemEl = document.getElementById('mensagemLogin');

    try {
        const resposta = await fetch('/api/login', {
            method: 'POST',
            headers: { 'Content-Type': 'application/x-www-form-urlencoded' },
            body: formData.toString()
        });

        const resultado = await resposta.json();

        if (resultado.sucesso) {
            mensagemEl.style.color = '#27ae60';
            mensagemEl.textContent = 'Login aprovado! Redirecionando...';
            
            // SALVA O NOME DO USUÁRIO NO NAVEGADOR
            // Se o seu backend retornar o nome, use resultado.nomeUsuario. 
            // Caso contrário, usamos o que ele digitou no campo.
            const nomeUsuario = formData.get('usuario'); 
            localStorage.setItem('usuarioAtivo', nomeUsuario);

            window.location.href = "/home.html";
        } else {
            mensagemEl.style.color = '#e74c3c';
            mensagemEl.textContent = 'Erro: ' + resultado.erro;
        }
    } catch (erro) {
        console.error('Erro na conexão:', erro);
        mensagemEl.style.color = '#e74c3c';
        mensagemEl.textContent = 'Erro ao tentar conectar ao servidor.';
    }
});