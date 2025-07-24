#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <string>

class Usuario {
protected:
    std::string nome;
    int livrosLidos;
    int livrosCedido;
    int creditos;

public:
    Usuario(const std::string& nome) : nome(nome), livrosLidos(0), livrosCedido(0), creditos(0) {}
    virtual ~Usuario() {}

    std::string getNome() const { return nome; }
    int getCreditos() const { return creditos; }
    void adicionarCredito(int c) { creditos += c; }
    void removerCredito(int c) { creditos -= c; if (creditos < 0) creditos = 0; }
    void leuLivro() { livrosLidos++; }
    void cedeuLivro() { livrosCedido++; }

    int getLivrosLidos() const { return livrosLidos; }
    int getLivrosCedido() const { return livrosCedido; }
};

#endif