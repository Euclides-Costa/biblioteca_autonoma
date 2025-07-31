#pragma once
#include <vector>
#include <string>
#include <ctime>
#include "Livro.hpp"
#include "CreditoStrategy.hpp"

class Usuario {
protected:
    std::string nome;
    std::string email;
    std::string senha;
    int creditos;
    std::vector<Livro> livrosCedido;
    std::vector<Livro> livrosLidos;
    std::vector<std::pair<Livro, time_t>> livrosEmprestadosComData;

public:
    Usuario(std::string nome, std::string email, std::string senha);
    bool autenticar(std::string e, std::string s);
    void doarLivro(const Livro& livro, ICreditoStrategy* estrategia);
    void lerLivro(const Livro& livro, ICreditoStrategy* estrategia);
    void emprestarLivro(Livro livro, ICreditoStrategy* estrategia);
    bool removerLivroEmprestado(const std::string& idLivro);
    void devolverLivro(const std::string& idLivro);
    int verificarAtraso(const std::string& idLivro) const;
    int getCreditos() const;
    void setCreditos(int novosCreditos);
    std::string getNome() const;
    std::string getEmail() const;
    std::string getSenha() const { return senha; } // Novo método adicionado
    const std::vector<Livro>& getLivrosCedido() const;
    const std::vector<Livro>& getLivrosLidos() const;
    const std::vector<std::pair<Livro, time_t>>& getLivrosEmprestadosComData() const;
    void mostrarHistoricoCedidos() const;
    void mostrarHistoricoLidos() const;
    void salvarHistorico() const;
    void carregarHistorico();
};