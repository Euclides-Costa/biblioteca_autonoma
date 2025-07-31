#include "Biblioteca.hpp"
#include "GerenciadorBancoDados.hpp"
#include <algorithm>
#include <iostream>

// Inicializa a instância estática como nula
Biblioteca* Biblioteca::instancia = nullptr;

// Construtor privado que carrega os dados ao iniciar
Biblioteca::Biblioteca() {
    // Carrega usuários e livros dos arquivos
    usuarios = GerenciadorBancoDados::carregarUsuarios();
    acervo = GerenciadorBancoDados::carregarLivros();
    
    // Carrega históricos dos usuários
    for (auto usuario : usuarios) {
        usuario->carregarHistorico();
    }
}

// Método para obter a instância singleton
Biblioteca* Biblioteca::getInstancia() {
    if (!instancia) {
        instancia = new Biblioteca();
    }
    return instancia;
}

// Verifica se um e-mail já está cadastrado
bool Biblioteca::emailJaCadastrado(std::string email) {
    for (auto u : usuarios) {
        if (u->getEmail() == email) {
            return true;
        }
    }
    return false;
}

// Adiciona um novo usuário e salva no arquivo
void Biblioteca::adicionarUsuario(Usuario* usuario) {
    if (emailJaCadastrado(usuario->getEmail())) {
        throw std::runtime_error("E-mail já cadastrado!");
    }
    usuarios.push_back(usuario);
    salvarDados();
}

// Autentica um usuário
Usuario* Biblioteca::autenticarUsuario(std::string email, std::string senha) {
    for (auto u : usuarios) {
        if (u->autenticar(email, senha)) {
            return u;
        }
    }
    return nullptr;
}

// Adiciona um livro ao acervo e salva no arquivo
void Biblioteca::adicionarLivro(const Livro& livro) {
    acervo.push_back(livro);
    salvarDados();
}

// Remove um livro do acervo e salva no arquivo
void Biblioteca::removerLivro(const std::string& idLivro) {
    acervo.erase(std::remove_if(acervo.begin(), acervo.end(),
        [&idLivro](const Livro& livro) {
            return livro.getId() == idLivro;
        }), acervo.end());
    salvarDados();
}

// Retorna uma cópia do acervo
std::vector<Livro> Biblioteca::getAcervo() {
    return acervo;
}

// Mostra o ranking dos livros mais lidos
void Biblioteca::mostrarRankingLivros() {
    std::map<std::string, int> rankingLeitura;
    
    // Conta quantas vezes cada livro foi lido
    for (auto u : usuarios) {
        for (auto l : u->getLivrosLidos()) {
            rankingLeitura[l.getTitulo()]++;
        }
    }

    if (rankingLeitura.empty()) {
        std::cout << "\nNão há ranking disponível (nenhum livro lido ainda).\n";
        return;
    }

    // Ordena por livros mais lidos
    std::vector<std::pair<std::string, int>> ordenado(rankingLeitura.begin(), rankingLeitura.end());
    std::sort(ordenado.begin(), ordenado.end(),
        [](auto& a, auto& b) { return a.second > b.second; });

    // Mostra os top 3
    std::cout << "\nTop 3 livros mais lidos:\n";
    int count = 0;
    for (auto& p : ordenado) {
        if (count++ >= 3) break;
        std::cout << count << ". " << p.first << ": " << p.second << " leituras\n";
    }
}

// Salva todos os dados nos arquivos
void Biblioteca::salvarDados() {
    GerenciadorBancoDados::salvarUsuarios(usuarios);
    GerenciadorBancoDados::salvarLivros(acervo);
    
    // Salva os históricos dos usuários
    for (auto usuario : usuarios) {
        usuario->salvarHistorico();
    }
}

// Retorna a lista de usuários
std::vector<Usuario*> Biblioteca::getUsuarios() {
    return usuarios;
}

// Encontra um usuário pelo e-mail
Usuario* Biblioteca::encontrarUsuarioPorEmail(std::string email) {
    for (auto u : usuarios) {
        if (u->getEmail() == email) {
            return u;
        }
    }
    return nullptr;
}

// Retorna o notificador
Notificador* Biblioteca::getNotificador() {
    return &notificador;
}