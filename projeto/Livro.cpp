#include "Livro.hpp"
#include <random>
#include <sstream>

Livro::Livro(std::string t, int e, std::string dono) : 
    titulo(t), edicao(e), emprestimos(0), donoEmail(dono) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1000, 9999);
    std::ostringstream oss;
    oss << "LIV" << dis(gen);
    id = oss.str();
}

std::string Livro::getTitulo() const { return titulo; }
int Livro::getEdicao() const { return edicao; }
void Livro::registrarEmprestimo() { /* Não faz mais nada */ }
int Livro::getEmprestimos() const { return emprestimos; }
std::string Livro::getId() const { return id; }
std::string Livro::getDonoEmail() const { return donoEmail; }
void Livro::setDonoEmail(std::string email) { donoEmail = email; }