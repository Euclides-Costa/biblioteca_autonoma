#pragma once
#include <string>
#include <random>

class Livro {
private:
    std::string titulo;
    int edicao;
    int emprestimos;
    std::string id;
    std::string donoEmail;

public:
    Livro(std::string t, int e, std::string dono = "");
    std::string getTitulo() const;
    int getEdicao() const;
    void registrarEmprestimo();
    int getEmprestimos() const;
    std::string getId() const;
    std::string getDonoEmail() const;
    void setDonoEmail(std::string email);
};