#include "SistemaBiblioteca.hpp"
#include "UsuarioFactory.hpp"
#include "Disponivel.hpp"
#include "Livro.hpp"
#include "CreditoPorLeitura.hpp"
#include "CreditoPorDoacao.hpp"

#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

int main() {
    SistemaBiblioteca* sistema = SistemaBiblioteca::getInstancia();

    map<string, Usuario*> usuarios;
    vector<Livro*> livrosDisponiveis;

    int opcao;
    string nome;

    cout << "=== Bem-vindo à Biblioteca Autônoma ===\n";

    while (true) {
        cout << "\n1. Criar Conta\n";
        cout << "2. Ceder Livro\n";
        cout << "3. Ver Créditos\n";
        cout << "4. Pegar Livro Emprestado\n";
        cout << "5. Devolver Livro\n";
        cout << "6. Sair\n";
        cout << "Escolha uma opção: ";
        cin >> opcao;
        cin.ignore();

        if (opcao == 1) {
            cout << "Nome do usuário: ";
            getline(cin, nome);
            if (usuarios.count(nome)) {
                cout << "Usuário já existe.\n";
                continue;
            }
            Usuario* novo = UsuarioFactory::criarUsuario("aluno", nome);
            usuarios[nome] = novo;
            sistema->registrarUsuario(novo);
            cout << "Conta criada com sucesso.\n";

        } else if (opcao == 2) {
            cout << "Seu nome: ";
            getline(cin, nome);
            if (!usuarios.count(nome)) {
                cout << "Usuário não encontrado.\n";
                continue;
            }

            cout << "Título do livro que deseja doar: ";
            string titulo;
            getline(cin, titulo);

            Livro* livro = new Livro(titulo, new Disponivel());
            livrosDisponiveis.push_back(livro);
            usuarios[nome]->cedeuLivro();
            usuarios[nome]->adicionarCredito(1);

            cout << "Livro \"" << titulo << "\" doado com sucesso. Crédito adicionado.\n";

        } else if (opcao == 3) {
            cout << "Seu nome: ";
            getline(cin, nome);
            if (!usuarios.count(nome)) {
                cout << "Usuário não encontrado.\n";
                continue;
            }
            cout << "Créditos disponíveis: " << usuarios[nome]->getCreditos() << "\n";

        } else if (opcao == 4) {
            cout << "Seu nome: ";
            getline(cin, nome);
            if (!usuarios.count(nome)) {
                cout << "Usuário não encontrado.\n";
                continue;
            }
            if (usuarios[nome]->getCreditos() < 1) {
                cout << "Créditos insuficientes!\n";
                continue;
            }

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
            usuarios[nome]->removerCredito(1);
            cout << "Livro emprestado com sucesso.\n";

            livrosDisponiveis.erase(livrosDisponiveis.begin() + escolha); // remover da lista

        } else if (opcao == 5) {
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
                usuarios[nome]->removerCredito(1);
            } else {
                cout << "Obrigado pela pontualidade!\n";
            }

            livrosDisponiveis.push_back(livro);

        } else if (opcao == 6) {
            break;

        } else {
            cout << "Opção inválida.\n";
        }
    }

    cout << "Saindo...\n";
    return 0;
}
