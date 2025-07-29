#pragma once
#include <string>
#include <random>
#include <sstream>
#include <atomic>

class Livro {
private:
    std::string titulo;
    int edicao;
    int emprestimos;
    std::string id;
    std::string donoEmail;

    // Contador atômico para gerar IDs únicos
    static std::atomic<int> contadorIds;

public:
    Livro(std::string t, int e, std::string dono = "");
    Livro() = default; // Construtor padrão necessário

    // Métodos de acesso
    std::string getTitulo() const;
    int getEdicao() const;
    void registrarEmprestimo();
    int getEmprestimos() const;
    std::string getId() const;
    std::string getDonoEmail() const;
    void setDonoEmail(std::string email);

    // Sobrecarga do operador de igualdade para comparação
    bool operator==(const Livro& outro) const {
        return this->id == outro.id;
    }
};