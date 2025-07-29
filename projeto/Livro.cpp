#include "Livro.hpp"
#include <random>
#include <sstream>

std::atomic<int> Livro::contadorIds(0);

Livro::Livro(std::string t, int e, std::string dono) : 
    titulo(t), edicao(e), emprestimos(0), donoEmail(dono) {
    // Gera um ID único combinando um número aleatório com o contador
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1000, 9999);
    
    std::ostringstream oss;
    oss << "LIV" << dis(gen) << "-" << ++contadorIds;
    id = oss.str();
}

std::string Livro::getTitulo() const { return titulo; }
int Livro::getEdicao() const { return edicao; }
void Livro::registrarEmprestimo() { emprestimos++; }
int Livro::getEmprestimos() const { return emprestimos; }
std::string Livro::getId() const { return id; }
std::string Livro::getDonoEmail() const { return donoEmail; }
void Livro::setDonoEmail(std::string email) { donoEmail = email; }