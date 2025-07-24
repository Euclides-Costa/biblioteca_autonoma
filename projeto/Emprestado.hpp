#ifndef EMPRESTADO_HPP
#define EMPRESTADO_HPP

#include "EstadoLivro.hpp"
#include <string>

class Livro; // forward declaration

class Emprestado : public EstadoLivro {
public:
    void emprestar(Livro*) override;
    void devolver(Livro* livro, bool atraso) override;
    std::string getNomeEstado() const override;
};

#endif
