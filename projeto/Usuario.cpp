#include "Usuario.hpp"
#include "Biblioteca.hpp"
#include <iostream>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <iomanip>

// Construtor do Usuário
Usuario::Usuario(std::string nome, std::string email, std::string senha)
    : nome(nome), email(email), senha(senha), creditos(0) {}

// Método de autenticação
bool Usuario::autenticar(std::string e, std::string s) {
    return e == email && s == senha;
}

// Método para doar livro
void Usuario::doarLivro(const Livro& livro, ICreditoStrategy* estrategia) {
    livrosCedido.push_back(livro);
    if (estrategia) {
        creditos += estrategia->calcularCredito(this);
    }
    salvarHistorico(); // Salva após modificar os dados
}

// Método para ler livro
void Usuario::lerLivro(const Livro& livro, ICreditoStrategy* estrategia) {
    livrosLidos.push_back(livro);
    if (estrategia) {
        creditos += estrategia->calcularCredito(this);
    }
    salvarHistorico();
}

// Método para emprestar livro
void Usuario::emprestarLivro(Livro livro, ICreditoStrategy* estrategia) {
    time_t now = time(0);
    livrosEmprestadosComData.push_back(std::make_pair(livro, now));
    if (estrategia) {
        creditos += estrategia->calcularCredito(this);
    }
    salvarHistorico();
}

// Remove um livro emprestado
bool Usuario::removerLivroEmprestado(const std::string& idLivro) {
    auto it = std::remove_if(livrosEmprestadosComData.begin(), 
                           livrosEmprestadosComData.end(),
                           [&idLivro](const auto& pair) {
                               return pair.first.getId() == idLivro;
                           });
    
    if (it != livrosEmprestadosComData.end()) {
        livrosEmprestadosComData.erase(it, livrosEmprestadosComData.end());
        salvarHistorico();
        return true;
    }
    return false;
}

// Método para devolver livro
void Usuario::devolverLivro(const std::string& idLivro) {
    if (removerLivroEmprestado(idLivro)) {
        salvarHistorico();
    }
}

// Verifica atraso na devolução
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

// Getters
int Usuario::getCreditos() const { return creditos; }
std::string Usuario::getNome() const { return nome; }
std::string Usuario::getEmail() const { return email; }
const std::vector<Livro>& Usuario::getLivrosCedido() const { return livrosCedido; }
const std::vector<Livro>& Usuario::getLivrosLidos() const { return livrosLidos; }
const std::vector<std::pair<Livro, time_t>>& Usuario::getLivrosEmprestadosComData() const { 
    return livrosEmprestadosComData; 
}

// Setter para créditos
void Usuario::setCreditos(int novosCreditos) {
    creditos = novosCreditos;
    salvarHistorico();
}

// Salva o histórico em arquivo
void Usuario::salvarHistorico() const {
    std::ofstream arquivo("historico_" + email + ".txt");
    
    // Seção de livros cedidos
    arquivo << "[CEDIDOS]\n";
    for (const auto& livro : livrosCedido) {
        arquivo << livro.getId() << "\n";
    }
    
    // Seção de livros lidos
    arquivo << "[LIDOS]\n";
    for (const auto& livro : livrosLidos) {
        arquivo << livro.getId() << "\n";
    }
    
    // Seção de livros emprestados com datas
    arquivo << "[EMPRESTADOS]\n";
    for (const auto& par : livrosEmprestadosComData) {
        arquivo << par.first.getId() << "," << par.second << "\n";
    }
    
    // Seção de créditos
    arquivo << "[CREDITOS]\n";
    arquivo << creditos << "\n";
}

// Carrega o histórico do arquivo
void Usuario::carregarHistorico() {
    std::ifstream arquivo("historico_" + email + ".txt");
    if (!arquivo) return;
    
    std::string linha;
    std::string secao;
    Biblioteca* bib = Biblioteca::getInstancia();
    
    while (getline(arquivo, linha)) {
        if (linha == "[CEDIDOS]") {
            secao = "CEDIDOS";
        } else if (linha == "[LIDOS]") {
            secao = "LIDOS";
        } else if (linha == "[EMPRESTADOS]") {
            secao = "EMPRESTADOS";
        } else if (linha == "[CREDITOS]") {
            secao = "CREDITOS";
        } else if (!linha.empty()) {
            if (secao == "CEDIDOS") {
                // Carrega livros cedidos
                for (const auto& livro : bib->getAcervo()) {
                    if (livro.getId() == linha) {
                        livrosCedido.push_back(livro);
                        break;
                    }
                }
            } else if (secao == "LIDOS") {
                // Carrega livros lidos
                for (const auto& livro : bib->getAcervo()) {
                    if (livro.getId() == linha) {
                        livrosLidos.push_back(livro);
                        break;
                    }
                }
            } else if (secao == "EMPRESTADOS") {
                // Carrega livros emprestados com data
                std::stringstream ss(linha);
                std::string idLivro, dataStr;
                getline(ss, idLivro, ',');
                getline(ss, dataStr);
                
                time_t data = stol(dataStr);
                for (const auto& livro : bib->getAcervo()) {
                    if (livro.getId() == idLivro) {
                        livrosEmprestadosComData.push_back(std::make_pair(livro, data));
                        break;
                    }
                }
            } else if (secao == "CREDITOS") {
                creditos = stoi(linha);
            }
        }
    }
}

// Mostra histórico de livros cedidos
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

// Mostra histórico de livros lidos
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