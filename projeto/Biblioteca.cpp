#include "Biblioteca.hpp"
#include <iostream>
#include <algorithm>

Biblioteca* Biblioteca::instancia = nullptr;

Biblioteca::Biblioteca() {}

Biblioteca* Biblioteca::getInstancia() {
    if (!instancia)
        instancia = new Biblioteca();
    return instancia;
}

void Biblioteca::adicionarUsuario(Usuario* usuario) {
    usuarios.push_back(usuario);
}

Usuario* Biblioteca::autenticarUsuario(std::string email, std::string senha) {
    for (auto u : usuarios) {
        if (u->autenticar(email, senha)) return u;
    }
    return nullptr;
}

void Biblioteca::adicionarLivro(const Livro& livro) {
    acervo.push_back(livro);
}

std::vector<Livro> Biblioteca::getAcervo() {
    return acervo;
}

void Biblioteca::mostrarRankingLivros() {
    std::map<std::string, int> rankingLeitura;
    
    for (auto u : usuarios) {
        for (auto l : u->getLivrosLidos()) {
            rankingLeitura[l.getTitulo()]++;
        }
    }

    if (rankingLeitura.empty()) {
        std::cout << "Não há ranking disponível (nenhum livro lido ainda).\n";
        return;
    }

    std::vector<std::pair<std::string, int>> ordenado(rankingLeitura.begin(), rankingLeitura.end());
    std::sort(ordenado.begin(), ordenado.end(),
        [](auto& a, auto& b) { return a.second > b.second; });

    std::cout << "\nTop 3 livros mais lidos:\n";
    int count = 0;
    for (auto& p : ordenado) {
        if (count++ >= 3) break;
        std::cout << count << ". " << p.first << ": " << p.second << " leituras\n";
    }
}

Notificador* Biblioteca::getNotificador() {
    return &notificador;
}

std::vector<Usuario*> Biblioteca::getUsuarios() {
    return usuarios;
}

Usuario* Biblioteca::encontrarUsuarioPorEmail(std::string email) {
    for (auto u : usuarios) {
        if (u->getEmail() == email) return u;
    }
    return nullptr;
}