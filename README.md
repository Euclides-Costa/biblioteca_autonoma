📚 Biblioteca Autônoma IFPB
Autores: Euclides Benício e Arthur Augusto
Disciplina: Padrões de Projeto

🚀 Visão Geral
Sistema de biblioteca autônoma que permite:

Troca de créditos por livros (1 livro cedido = 1 crédito)

Empréstimos com penalidades por atraso

Ranking dos livros mais populares

Notificações automáticas

🛠️ Padrões de Projeto Implementados
Padrão	Classe(s) Envolvidas	Benefício Chave
Singleton	Biblioteca	Garante uma única instância global
Strategy	ICreditoStrategy + implementações	Flexibilidade nas regras de créditos
Observer	Notificador + UsuarioObservador	Notificações desacopladas
Factory	UsuarioFactory	Isola a criação de usuários
💻 Como Executar
Pré-requisitos
Compilador C++ (g++ ou Clang)

Terminal Linux/MacOS (ou WSL no Windows)

Passo a Passo
Clone o repositório:
bash
git clone https://github.com/seu-usuario/biblioteca-autonoma.git  
cd biblioteca-autonoma  
Compile o projeto:

bash
g++ *.cpp -o biblioteca  
Execute:

bash
./biblioteca  

