#include "InterfaceUsuario.hpp"
#include "UsuarioFactory.hpp"
#include "EstrategiasCredito.hpp"
#include <iostream>
#include <limits>
#include <vector>
#include <ctime>
#include <iomanip>

using namespace std;

void InterfaceUsuario::limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void InterfaceUsuario::pausar() {
    cout << "\nPressione Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

int InterfaceUsuario::lerInteiro(const string& mensagem) {
    int valor;
    while (true) {
        cout << mensagem;
        cin >> valor;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Erro: Digite um número válido!\n";
        } else {
            cin.ignore();
            return valor;
        }
    }
}

void InterfaceUsuario::exibirCabecalho(const string& titulo) {
    limparTela();
    cout << "===================================================\n";
    cout << "      SISTEMA DE BIBLIOTECA - " << titulo << "\n";
    cout << "===================================================\n\n";
}

void InterfaceUsuario::telaBoasVindas(Biblioteca* bib, UsuarioObservador& observador) {
    // Adiciona o observador uma única vez no início do sistema
    bib->getNotificador()->adicionar(&observador);

    int escolha;
    do {
        exibirCabecalho("MENU PRINCIPAL");
        cout << "1. Criar conta\n";
        cout << "2. Login\n";
        cout << "0. Sair\n";
        cout << "\nEscolha: ";
        cin >> escolha;
        cin.ignore();

        switch (escolha) {
            case 1: {
                string nome, email, senha;
                exibirCabecalho("CRIAR CONTA");
                cout << "Nome: "; getline(cin, nome);
                cout << "Email: "; getline(cin, email);
                cout << "Senha: "; getline(cin, senha);
                
                try {
                    Usuario* usuario = UsuarioFactory::criarUsuario("Aluno", nome, email, senha);
                    bib->adicionarUsuario(usuario);
                    cout << "\nUsuário cadastrado com sucesso!\n";
                } catch (const std::runtime_error& e) {
                    cout << "\nErro: " << e.what() << "\n";
                }
                pausar();
                break;
            }
            case 2: {
                string email, senha;
                exibirCabecalho("LOGIN");
                cout << "Email: "; getline(cin, email);
                cout << "Senha: "; getline(cin, senha);
                
                Usuario* usuario = bib->autenticarUsuario(email, senha);
                
                if (usuario) {
                    telaMenuPrincipal(bib, usuario);
                } else {
                    cout << "\nLogin falhou! Email ou senha incorretos.\n";
                    pausar();
                }
                break;
            }
            case 0:
                cout << "\nSaindo do sistema...\n";
                break;
            default:
                cout << "\nOpção inválida!\n";
                pausar();
        }
    } while (escolha != 0);
}

void InterfaceUsuario::telaMenuPrincipal(Biblioteca* bib, Usuario* usuario) {
    int opcao;
    do {
        exibirCabecalho("MENU DO USUÁRIO");
        cout << "Bem-vindo, " << usuario->getNome() << "!\n";
        cout << "Créditos disponíveis: " << usuario->getCreditos() << "\n\n";
        
        cout << "1. Emprestar livro\n";
        cout << "2. Ler livro\n";
        cout << "3. Devolver livro\n";
        cout << "4. Ranking de livros\n";
        cout << "5. Histórico de livros cedidos\n";
        cout << "6. Histórico de livros lidos\n";
        cout << "0. Sair\n";
        cout << "\nEscolha: ";
        cin >> opcao;
        cin.ignore();

        switch (opcao) {
            case 1:
                telaEmprestarLivro(bib, usuario);
                break;
            case 2:
                telaLerLivro(bib, usuario);
                break;
            case 3:
                telaDevolverLivro(bib, usuario);
                break;
            case 4:
                telaRankingLivros(bib);
                break;
            case 5:
                telaHistoricoCedidos(usuario);
                break;
            case 6:
                telaHistoricoLidos(usuario);
                break;
            case 0:
                cout << "\nVoltando ao menu principal...\n";
                break;
            default:
                cout << "\nOpção inválida!\n";
                pausar();
        }
    } while (opcao != 0);
}

void InterfaceUsuario::telaEmprestarLivro(Biblioteca* bib, Usuario* usuario) {
    exibirCabecalho("EMPRESTAR LIVRO");
    
    string titulo;
    cout << "Título do livro: "; getline(cin, titulo);
    int edicao = lerInteiro("Edição: ");
    
    Livro livro(titulo, edicao, usuario->getEmail());
    CreditoPorDoacao estrategia;
    usuario->doarLivro(livro, &estrategia);
    bib->adicionarLivro(livro);
    
    cout << "\nLivro emprestado com sucesso! ID: " << livro.getId() << "\n";
    cout << "Você ganhou 1 crédito!\n";
    
    bib->getNotificador()->notificarTodos("Novo livro disponível: " + titulo);
    pausar();
}

void InterfaceUsuario::telaLerLivro(Biblioteca* bib, Usuario* usuario) {
    exibirCabecalho("LER LIVRO");
    
    if (usuario->getCreditos() <= 0) {
        cout << "Você não tem créditos suficientes para ler um livro.\n";
        pausar();
        return;
    }
    
    auto livros = bib->getAcervo();
    if (livros.empty()) {
        cout << "Nenhum livro disponível.\n";
        pausar();
        return;
    }
    
    cout << "Livros disponíveis:\n";
    for (const auto& livro : livros) {
        cout << "- " << livro.getTitulo() 
             << " | Edição: " << livro.getEdicao()
             << " | ID: " << livro.getId() << "\n";
    }
    
    string idLivro;
    cout << "\nInforme o ID do livro que deseja ler (ou 'voltar' para cancelar): ";
    getline(cin, idLivro);
    
    if (idLivro == "voltar") return;
    
    bool encontrado = false;
    for (const auto& livro : livros) {
        if (livro.getId() == idLivro) {
            bib->removerLivro(idLivro);
            
            time_t now = time(0);
            usuario->emprestarLivro(livro, nullptr);
            
            CreditoPorLeitura estrategiaLeitura;
            usuario->lerLivro(livro, &estrategiaLeitura);
            
            Usuario* dono = bib->encontrarUsuarioPorEmail(livro.getDonoEmail());
            if (dono && dono->getEmail() != usuario->getEmail()) {
                dono->setCreditos(dono->getCreditos() + 1);
                cout << "\nO dono do livro (" << dono->getNome() << ") foi creditado com 1 ponto!\n";
            }
            
            tm* tm_info = localtime(&now);
            tm_info->tm_mday += 7;
            mktime(tm_info);
            
            cout << "\nLivro emprestado com sucesso! 1 crédito debitado.\n";
            cout << "Data limite para devolução: " << put_time(tm_info, "%d/%m/%Y") << "\n";
            
            encontrado = true;
            break;
        }
    }
    
    if (!encontrado) {
        cout << "\nLivro não encontrado.\n";
    }
    pausar();
}

void InterfaceUsuario::telaDevolverLivro(Biblioteca* bib, Usuario* usuario) {
    exibirCabecalho("DEVOLVER LIVRO");
    
    if (usuario->getLivrosEmprestadosComData().empty()) {
        cout << "Você não tem livros para devolver.\n";
        pausar();
        return;
    }
    
    while (true) {
        exibirCabecalho("DEVOLVER LIVRO");
        cout << "Livros emprestados:\n";
        for (const auto& pair : usuario->getLivrosEmprestadosComData()) {
            tm* tm_info = localtime(&pair.second);
            cout << "- ID: " << pair.first.getId() 
                 << " | " << pair.first.getTitulo()
                 << " | Emprestado em: " << put_time(tm_info, "%d/%m/%Y") << "\n";
        }
        
        string idLivro;
        cout << "\nInforme o ID do livro a devolver (ou 'voltar' para cancelar): ";
        getline(cin, idLivro);
        
        if (idLivro == "voltar") break;
        
        bool livroEncontrado = false;
        Livro livroDevolvido("", 0);
        
        for (const auto& pair : usuario->getLivrosEmprestadosComData()) {
            if (pair.first.getId() == idLivro) {
                livroEncontrado = true;
                livroDevolvido = pair.first;
                break;
            }
        }
        
        if (!livroEncontrado) {
            cout << "\nID inválido. Tente novamente.\n";
            pausar();
            continue;
        }
        
        int diasAtraso = usuario->verificarAtraso(idLivro);
        
        if (usuario->removerLivroEmprestado(idLivro)) {
            bib->adicionarLivro(livroDevolvido);
            cout << "\nLivro devolvido com sucesso!\n";
            
            if (diasAtraso > 0) {
                CreditoPorAtraso estrategia(diasAtraso);
                usuario->lerLivro(livroDevolvido, &estrategia);
                cout << "Atraso detectado! " << diasAtraso 
                     << " créditos foram debitados.\n";
            } else {
                cout << "Livro devolvido dentro do prazo.\n";
            }
        } else {
            cout << "\nErro ao devolver livro.\n";
        }
        pausar();
        break;
    }
}

void InterfaceUsuario::telaRankingLivros(Biblioteca* bib) {
    exibirCabecalho("RANKING DE LIVROS");
    bib->mostrarRankingLivros();
    pausar();
}

void InterfaceUsuario::telaHistoricoCedidos(Usuario* usuario) {
    exibirCabecalho("HISTÓRICO DE LIVROS CEDIDOS");
    usuario->mostrarHistoricoCedidos();
    pausar();
}

void InterfaceUsuario::telaHistoricoLidos(Usuario* usuario) {
    exibirCabecalho("HISTÓRICO DE LIVROS LIDOS");
    usuario->mostrarHistoricoLidos();
    pausar();
}

void InterfaceUsuario::executarSistema() {
    Biblioteca* bib = Biblioteca::getInstancia();
    UsuarioObservador observador;
    telaBoasVindas(bib, observador);
}