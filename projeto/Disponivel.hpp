#ifndef DISPONIVEL_HPP
#define DISPONIVEL_HPP

#include "EstadoLivro.hpp"
#include "Livro.hpp"
#include "Emprestado.hpp"
#include <iostream>

class Disponivel : public EstadoLivro {
public:
    void emprestar(Livro* livro) override {
        std::cout << "Livro emprestado.\n";
        livro->setEstado(new Emprestado());
    }
    void devolver(Livro*, bool) override {
        std::cout << "Livro já está disponível.\n";
    }
    std::string getNomeEstado() const override {
        return "Disponível";
    }
};

#endif