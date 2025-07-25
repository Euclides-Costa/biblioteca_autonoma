#include <iostream>
#include <vector>
#include "UsuarioFactory.hpp"
#include "UsuarioObservador.hpp"
#include "Biblioteca.hpp"
#include "EstrategiasCredito.hpp"

void menuLogado() {
    std::cout << "\n1. Emprestar livro\n2. Ler livro\n3. Ver créditos\n"
              << "4. Devolver livro\n5. Ranking\n6. Histórico de livros cedidos\n"
              << "7. Histórico de livros lidos\n0. Sair\nEscolha: ";
}

int main() {
    Biblioteca* bib = Biblioteca::getInstancia();
    Usuario* usuario = nullptr;
    UsuarioObservador observador;
    bib->getNotificador()->adicionar(&observador);

    while (true) {
        int escolha;
        std::cout << "\n1. Criar conta\n2. Login\n0. Sair\nEscolha: ";
        std::cin >> escolha;
        std::cin.ignore();

        if (escolha == 1) {
            std::string nome, email, senha;
            std::cout << "Nome: "; std::getline(std::cin, nome);
            std::cout << "Email: "; std::getline(std::cin, email);
            std::cout << "Senha: "; std::getline(std::cin, senha);
            
            usuario = UsuarioFactory::criarUsuario("Aluno", nome, email, senha);
            bib->adicionarUsuario(usuario);
            std::cout << "Usuário cadastrado com sucesso!\n";
            
        } else if (escolha == 2) {
            std::string email, senha;
            std::cout << "Email: "; std::getline(std::cin, email);
            std::cout << "Senha: "; std::getline(std::cin, senha);
            usuario = bib->autenticarUsuario(email, senha);
            
            if (!usuario) {
                std::cout << "Login falhou!\n";
                continue;
            }

            int opcao;
            do {
                menuLogado();
                std::cin >> opcao;
                std::cin.ignore();
                
                if (opcao == 1) {
                    std::string titulo;
                    int edicao;
                    std::cout << "Título do livro: "; std::getline(std::cin, titulo);
                    std::cout << "Edição: "; std::cin >> edicao;
                    std::cin.ignore();
                    
                    Livro l(titulo, edicao, usuario->getEmail());
                    CreditoPorDoacao c;
                    usuario->doarLivro(l, &c);
                    bib->adicionarLivro(l);
                    
                    std::cout << "Livro emprestado com sucesso! ID: " << l.getId() 
                              << "\nVocê ganhou 1 crédito!\n";
                    bib->getNotificador()->notificarTodos("Novo livro disponível: " + titulo);
                    
                } else if (opcao == 2) {
                    if (usuario->getCreditos() <= 0) {
                        std::cout << "Você não tem créditos suficientes para ler um livro.\n";
                        continue;
                    }
                    
                    auto livros = bib->getAcervo();
                    if (livros.empty()) {
                        std::cout << "Nenhum livro disponível.\n";
                        continue;
                    }
                    
                    std::cout << "\nLivros disponíveis:\n";
                    for (const auto& livro : livros) {
                        std::cout << "- " << livro.getTitulo() 
                                 << " | Edição: " << livro.getEdicao()
                                 << " | ID: " << livro.getId() << "\n";
                    }
                    
                    std::string idLivro;
                    std::cout << "Informe o ID do livro que deseja ler (ou 'voltar' para cancelar): ";
                    std::getline(std::cin, idLivro);
                    
                    if (idLivro == "voltar") continue;
                    
                    bool encontrado = false;
                    for (auto& livro : livros) {
                        if (livro.getId() == idLivro) {
                            // Gasta crédito do leitor
                            CreditoPorLeitura estrategiaLeitura;
                            usuario->lerLivro(livro, &estrategiaLeitura);
                            
                            // Dá crédito para o dono do livro
                            Usuario* dono = bib->encontrarUsuarioPorEmail(livro.getDonoEmail());
                            if (dono && dono->getEmail() != usuario->getEmail()) {
                                CreditoPorDoacao estrategiaDoacao;
                                Livro copiaLivro = livro;
                                dono->doarLivro(copiaLivro, &estrategiaDoacao);
                                std::cout << "O dono do livro foi creditado!\n";
                            }
                            
                            std::cout << "Livro lido com sucesso! 1 crédito debitado.\n";
                            encontrado = true;
                            break;
                        }
                    }
                    
                    if (!encontrado) {
                        std::cout << "Livro não encontrado.\n";
                    }
                    
                } else if (opcao == 3) {
                    std::cout << "Créditos disponíveis: " << usuario->getCreditos() << "\n";
                    
                } else if (opcao == 4) {
                    if (usuario->getLivrosEmprestadosComData().empty()) {
                        std::cout << "Você não tem livros para devolver.\n";
                        continue;
                    }
                    
                    while (true) {
                        std::cout << "Livros emprestados:\n";
                        for (const auto& pair : usuario->getLivrosEmprestadosComData()) {
                            std::cout << "- ID: " << pair.first.getId() 
                                      << " | " << pair.first.getTitulo() << "\n";
                        }
                        
                        std::string idLivro;
                        std::cout << "Informe o ID do livro a devolver (ou 'voltar' para cancelar): ";
                        std::getline(std::cin, idLivro);
                        
                        if (idLivro == "voltar") break;
                        
                        bool livroEncontrado = false;
                        for (const auto& pair : usuario->getLivrosEmprestadosComData()) {
                            if (pair.first.getId() == idLivro) {
                                livroEncontrado = true;
                                break;
                            }
                        }
                        
                        if (!livroEncontrado) {
                            std::cout << "ID inválido. Tente novamente.\n";
                            continue;
                        }
                        
                        int diasAtraso = usuario->verificarAtraso(idLivro);
                        
                        if (usuario->removerLivroEmprestado(idLivro)) {
                            std::cout << "Livro devolvido com sucesso!\n";
                            
                            if (diasAtraso > 0) {
                                CreditoPorAtraso estrategia(diasAtraso);
                                for (const auto& livro : bib->getAcervo()) {
                                    if (livro.getId() == idLivro) {
                                        usuario->lerLivro(livro, &estrategia);
                                        break;
                                    }
                                }
                                std::cout << "Atraso detectado! " << diasAtraso 
                                         << " créditos foram debitados.\n";
                            }
                        } else {
                            std::cout << "Erro ao devolver livro.\n";
                        }
                        break;
                    }
                    
                } else if (opcao == 5) {
                    bib->mostrarRankingLivros();
                    
                } else if (opcao == 6) {
                    usuario->mostrarHistoricoCedidos();
                    
                } else if (opcao == 7) {
                    usuario->mostrarHistoricoLidos();
                }
                
            } while (opcao != 0);
            
        } else if (escolha == 0) {
            break;
        }
    }

    return 0;
}