#include "Emprestado.hpp"
#include "Livro.hpp"
#include "Disponivel.hpp"
#include <iostream>

void Emprestado::emprestar(Livro*) {
    std::cout << "Livro já está emprestado.\n";
}

void Emprestado::devolver(Livro* livro, bool atraso) {
    if (atraso) {
        std::cout << "Livro devolvido com atraso.\n";
    } else {
        std::cout << "Livro devolvido no prazo.\n";
    }
    livro->setEstado(new Disponivel());
}

std::string Emprestado::getNomeEstado() const {
    return "Emprestado";
}
