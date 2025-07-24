#ifndef ESTADO_LIVRO_HPP
#define ESTADO_LIVRO_HPP

#include <string>

class Livro;

class EstadoLivro {
public:
    virtual void emprestar(Livro* livro) = 0;
    virtual void devolver(Livro* livro, bool atraso) = 0;
    virtual std::string getNomeEstado() const = 0;
    virtual ~EstadoLivro() {}
};

#endif