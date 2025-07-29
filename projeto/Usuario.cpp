#include "Usuario.hpp"
#include <iostream>
#include <ctime>
#include <algorithm>

Usuario::Usuario(std::string nome, std::string email, std::string senha)
    : nome(nome), email(email), senha(senha), creditos(0) {}

bool Usuario::autenticar(std::string e, std::string s) {
    return e == email && s == senha;
}

void Usuario::doarLivro(const Livro& livro, ICreditoStrategy* estrategia) {
    livrosCedido.push_back(livro);
    if (estrategia) {
        creditos += estrategia->calcularCredito(this);
    }
}

void Usuario::lerLivro(const Livro& livro, ICreditoStrategy* estrategia) {
    livrosLidos.push_back(livro);
    if (estrategia) {
        creditos += estrategia->calcularCredito(this);
    }
}

void Usuario::emprestarLivro(Livro livro, ICreditoStrategy* estrategia) {
    time_t now = time(0);
    livrosEmprestadosComData.push_back(std::make_pair(livro, now));
    if (estrategia) {
        creditos += estrategia->calcularCredito(this);
    }
}

bool Usuario::removerLivroEmprestado(const std::string& idLivro) {
    auto it = std::remove_if(livrosEmprestadosComData.begin(), 
                           livrosEmprestadosComData.end(),
                           [&idLivro](const auto& pair) {
                               return pair.first.getId() == idLivro;
                           });
    
    if (it != livrosEmprestadosComData.end()) {
        livrosEmprestadosComData.erase(it, livrosEmprestadosComData.end());
        return true;
    }
    return false;
}

void Usuario::devolverLivro(const std::string& idLivro) {
    auto it = std::remove_if(livrosEmprestadosComData.begin(), 
                           livrosEmprestadosComData.end(),
                           [&idLivro](const auto& pair) {
                               return pair.first.getId() == idLivro;
                           });
    
    if (it != livrosEmprestadosComData.end()) {
        livrosEmprestadosComData.erase(it, livrosEmprestadosComData.end());
    }
}

int Usuario::verificarAtraso(const std::string& idLivro) const {
    const int PRAZO_DEVOLUCAO = 7; // 7 dias de prazo
    time_t now = time(0);
    
    for (const auto& pair : livrosEmprestadosComData) {
        if (pair.first.getId() == idLivro) {
            double diferenca = difftime(now, pair.second) / (60 * 60 * 24);
            if (diferenca > PRAZO_DEVOLUCAO) {
                return static_cast<int>(diferenca) - PRAZO_DEVOLUCAO;
            }
            break;
        }
    }
    return 0;
}

int Usuario::getCreditos() const { 
    return creditos; 
}

void Usuario::setCreditos(int novosCreditos) {
    creditos = novosCreditos;
}

std::string Usuario::getNome() const { 
    return nome; 
}

std::string Usuario::getEmail() const { 
    return email; 
}

const std::vector<Livro>& Usuario::getLivrosCedido() const { 
    return livrosCedido; 
}

const std::vector<Livro>& Usuario::getLivrosLidos() const { 
    return livrosLidos; 
}

const std::vector<std::pair<Livro, time_t>>& Usuario::getLivrosEmprestadosComData() const { 
    return livrosEmprestadosComData; 
}

void Usuario::mostrarHistoricoCedidos() const {
    if (livrosCedido.empty()) {
        std::cout << "\nHistórico de livros cedidos: 0\n";
        return;
    }
    
    std::cout << "\nLivros Cedidos:\n";
    for (const auto& livro : livrosCedido) {
        std::cout << "- " << livro.getTitulo() 
                 << " (Edição: " << livro.getEdicao() 
                 << ", ID: " << livro.getId() << ")\n";
    }
}

void Usuario::mostrarHistoricoLidos() const {
    if (livrosLidos.empty()) {
        std::cout << "\nHistórico de livros lidos: 0\n";
        return;
    }
    
    std::cout << "\nLivros Lidos:\n";
    for (const auto& livro : livrosLidos) {
        std::cout << "- " << livro.getTitulo() 
                 << " (Edição: " << livro.getEdicao() 
                 << ", ID: " << livro.getId() << ")\n";
    }
}