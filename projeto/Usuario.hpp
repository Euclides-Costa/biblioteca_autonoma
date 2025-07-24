#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <string>

class Usuario {
protected:
    std::string nome;
    std::string email;
    std::string senha;
    int creditos;
    int livrosCedido;
    int livrosLidos;

public:
    Usuario(std::string nome, std::string email, std::string senha)
        : nome(nome), email(email), senha(senha), creditos(0), livrosCedido(0), livrosLidos(0) {}

    std::string getNome() const { return nome; }
    std::string getEmail() const { return email; }
    bool validarSenha(const std::string& s) const { return s == senha; }

    int getCreditos() const { return creditos; }
    void adicionarCredito(int valor) { creditos += valor; }
    void removerCredito(int valor) { creditos -= valor; }

    void cedeuLivro() { livrosCedido++; }
    void leuLivro() { livrosLidos++; }

    int getLivrosCedido() const { return livrosCedido; }
    int getLivrosLidos() const { return livrosLidos; }
};

#endif