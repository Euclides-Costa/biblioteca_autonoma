#ifndef LIVRO_HPP
#define LIVRO_HPP

#include "EstadoLivro.hpp"
#include <string>

class Livro {
private:
    std::string titulo;
    EstadoLivro* estado;

public:
    Livro(const std::string& titulo, EstadoLivro* estadoInicial) : titulo(titulo), estado(estadoInicial) {}

    void setEstado(EstadoLivro* e) { estado = e; }
    void emprestar() { estado->emprestar(this); }
    void devolver(bool atraso) { estado->devolver(this, atraso); }
    std::string getTitulo() const { return titulo; }
    std::string getEstado() const { return estado->getNomeEstado(); }
};

#endif