document.addEventListener('DOMContentLoaded', () => {
    const formLogin = document.getElementById('form-login');
    const formCadastro = document.getElementById('form-cadastro');
    const linkCadastro = document.getElementById('link-cadastro');
    const linkLogin = document.getElementById('link-login');

    // --- TROCA DE TELAS (LOGIN <-> CADASTRO) ---
    if (linkCadastro) {
        linkCadastro.addEventListener('click', (e) => {
            e.preventDefault();
            formLogin.style.display = 'none';
            formCadastro.style.display = 'block';
        });
    }

    if (linkLogin) {
        linkLogin.addEventListener('click', (e) => {
            e.preventDefault();
            formCadastro.style.display = 'none';
            formLogin.style.display = 'block';
        });
    }

    // --- LÓGICA DE LOGIN ---
    if (formLogin) {
        formLogin.addEventListener('submit', async (e) => {
            e.preventDefault();
            
            // O login pode continuar usando 'usuario' (que pode ser o email ou cpf, dependendo de como você tratar no C++) e 'senha'
            const usuario = document.getElementById('usuario').value;
            const senha = document.getElementById('senha').value;

            try {
                const response = await fetch('/api/login', {
                    method: 'POST',
                    headers: { 'Content-Type': 'application/json' },
                    body: JSON.stringify({ usuario: usuario, senha: senha })
                });
                const result = await response.json();

                if (result.sucesso) {
                    // Redireciona para o Feed
                    localStorage.setItem("usuarioLogadoId", result.id);
                    window.location.href = 'home.html';
                } else {
                    alert('Erro: ' + (result.erro || 'Usuário ou senha incorretos.'));
                }
            } catch (error) {
                console.error('Erro no login:', error);
                // Fallback de segurança para você testar a interface caso o back-end esteja desligado
                if (usuario === 'admin' && senha === 'admin') {
                    window.location.href = 'home.html';
                } else {
                    alert('Erro de conexão com o servidor C++.');
                }
            }
        });
    }

    // --- LÓGICA DE CADASTRO ---
    if (formCadastro) {
        formCadastro.addEventListener('submit', async (e) => {
            e.preventDefault();
            
            // usuario e senha para entrar no sistema
            const usuario = document.getElementById('novo-usuario').value;
            const senha = document.getElementById('nova-senha').value;
            // Capturando os novos campos alinhados à classe Pessoa no C++
            const nome = document.getElementById('nome').value;
            const cpf = document.getElementById('cpf').value;
            const telefone = document.getElementById('telefone').value;
            const email = document.getElementById('email').value;

            const dadosCadastro = {
            usuario: usuario,
            senha: senha,
            nome: nome,
            cpf: cpf,
            telefone: telefone,
            email: email
            };

            try {
            const response = await fetch('/api/register', {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify(dadosCadastro) // Enviando tudo junto!
            });
            const result = await response.json();

            if (result.sucesso) {
                alert('Cadastro realizado com sucesso! Faça o login.');
                formCadastro.reset();
                linkLogin.click(); // Volta automaticamente para a tela de login
            } else {
                alert('Erro no cadastro: ' + (result.erro || 'Tente novamente.'));
            }
            } catch (error) {
            console.error('Erro no cadastro:', error);
            alert('Erro de conexão com o servidor C++.');
            }
            });
    }
});