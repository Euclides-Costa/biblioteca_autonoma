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
    bool autenticar(std::string email, std::string senha);
    void doarLivro(const Livro& livro, ICreditoStrategy* estrategia);
    void lerLivro(const Livro& livro, ICreditoStrategy* estrategia);
    void emprestarLivro(Livro livro, ICreditoStrategy* estrategia);
    bool removerLivroEmprestado(const std::string& idLivro);
    int verificarAtraso(const std::string& idLivro) const; // Mantenha apenas uma declaração
    void devolverLivro(const std::string& idLivro);
    int getCreditos() const;
    void setCreditos(int novosCreditos);
    std::string getNome() const;
    std::string getEmail() const;
    const std::vector<Livro>& getLivrosCedido() const;
    const std::vector<Livro>& getLivrosLidos() const;
    const std::vector<std::pair<Livro, time_t>>& getLivrosEmprestadosComData() const;
    void mostrarHistoricoCedidos() const;
    void mostrarHistoricoLidos() const;
};