#include "SistemaBiblioteca.hpp"
#include "UsuarioFactory.hpp"
#include "Disponivel.hpp"
#include "Livro.hpp"
#include "CreditoPorLeitura.hpp"
#include "CreditoPorDoacao.hpp"
#include "Emprestado.hpp"

#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

// Função auxiliar para login
Usuario* autenticar(map<string, Usuario*>& usuarios) {
    string nome, senha;
    cout << "Nome: ";
    getline(cin, nome);

    if (!usuarios.count(nome)) {
        cout << "Usuário não encontrado.\n";
        return nullptr;
    }

    cout << "Senha: ";
    getline(cin, senha);

    Usuario* u = usuarios[nome];
    if (!u->validarSenha(senha)) {
        cout << "Senha incorreta.\n";
        return nullptr;
    }

    return u;
}

int main() {
    SistemaBiblioteca* sistema = SistemaBiblioteca::getInstancia();

    map<string, Usuario*> usuarios;
    vector<Livro*> livrosDisponiveis;

    int opcao;

    cout << "=== Bem-vindo à Biblioteca Autônoma ===\n";

    while (true) {
        cout << "\n1. Criar Conta\n";
        cout << "2. Ceder Livro\n";
        cout << "3. Ver Créditos\n";
        cout << "4. Pegar Livro Emprestado\n";
        cout << "5. Devolver Livro\n";
        cout << "6. Ler Livro\n";
        cout << "7. Sair\n";
        cout << "Escolha uma opção: ";
        cin >> opcao;
        cin.ignore();

        if (opcao == 1) {
            string nome, email, senha;
            cout << "Nome do usuário: ";
            getline(cin, nome);
            cout << "Email: ";
            getline(cin, email);
            cout << "Senha: ";
            getline(cin, senha);

            if (usuarios.count(nome)) {
                cout << "Usuário já existe.\n";
                continue;
            }

            Usuario* novo = UsuarioFactory::criarUsuario("aluno", nome, email, senha);
            usuarios[nome] = novo;
            sistema->registrarUsuario(novo);
            cout << "Conta criada com sucesso.\n";

        } else if (opcao == 2) {
            Usuario* usuario = autenticar(usuarios);
            if (!usuario) continue;

            cout << "Título do livro que deseja doar: ";
            string titulo;
            getline(cin, titulo);

            Livro* livro = new Livro(titulo, new Disponivel());
            livrosDisponiveis.push_back(livro);
            usuario->cedeuLivro();
            usuario->adicionarCredito(1);

            cout << "Livro \"" << titulo << "\" doado com sucesso. Crédito adicionado.\n";

        } else if (opcao == 3) {
            Usuario* usuario = autenticar(usuarios);
            if (!usuario) continue;

            cout << "Créditos disponíveis: " << usuario->getCreditos() << "\n";

        } else if (opcao == 4) {
            Usuario* usuario = autenticar(usuarios);
            if (!usuario) continue;

            if (livrosDisponiveis.empty()) {
                cout << "Nenhum livro disponível no momento.\n";
                continue;
            }

            cout << "Livros disponíveis:\n";
            for (size_t i = 0; i < livrosDisponiveis.size(); ++i)
                cout << i << ". " << livrosDisponiveis[i]->getTitulo() << "\n";

            cout << "Escolha o número do livro: ";
            int escolha;
            cin >> escolha;
            cin.ignore();

            if (escolha < 0 || escolha >= (int)livrosDisponiveis.size()) {
                cout << "Escolha inválida.\n";
                continue;
            }

            Livro* escolhido = livrosDisponiveis[escolha];
            escolhido->emprestar();
            usuario->adicionarCredito(1); // ganha direito de leitura
            cout << "Livro emprestado com sucesso. Crédito de leitura concedido.\n";

            livrosDisponiveis.erase(livrosDisponiveis.begin() + escolha);

        } else if (opcao == 5) {
            Usuario* usuario = autenticar(usuarios);
            if (!usuario) continue;

            cout << "Título do livro devolvido: ";
            string titulo;
            getline(cin, titulo);

            cout << "Foi devolvido com atraso? (1 = sim, 0 = não): ";
            int atraso;
            cin >> atraso;
            cin.ignore();

            Livro* livro = new Livro(titulo, new Emprestado());
            livro->devolver(atraso == 1);

            if (atraso == 1) {
                cout << "Crédito será descontado por atraso.\n";
                usuario->removerCredito(1);
            } else {
                cout << "Obrigado pela pontualidade!\n";
            }

            livrosDisponiveis.push_back(livro);

        } else if (opcao == 6) {
            Usuario* usuario = autenticar(usuarios);
            if (!usuario) continue;

            if (usuario->getCreditos() < 1) {
                cout << "Você não tem créditos de leitura. Pegue um livro emprestado primeiro.\n";
                continue;
            }

            cout << "Qual livro você deseja ler? ";
            string titulo;
            getline(cin, titulo);

            usuario->removerCredito(1);
            usuario->leuLivro();

            cout << "Leitura do livro \"" << titulo << "\" registrada. Crédito consumido.\n";

        } else if (opcao == 7) {
            break;

        } else {
            cout << "Opção inválida.\n";
        }
    }

    cout << "Saindo...\n";
    return 0;
}
