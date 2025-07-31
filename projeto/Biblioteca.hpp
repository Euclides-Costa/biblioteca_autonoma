#pragma once
#include <vector>
#include <map>
#include "Usuario.hpp"
#include "Notificador.hpp"

class Biblioteca {
private:
    static Biblioteca* instancia;
    std::vector<Usuario*> usuarios;
    std::vector<Livro> acervo;
    Notificador notificador;

    Biblioteca();

public:
    static Biblioteca* getInstancia();
    void adicionarUsuario(Usuario* usuario);
    Usuario* autenticarUsuario(std::string email, std::string senha);
    void adicionarLivro(const Livro& livro);
    void removerLivro(const std::string& idLivro);
    std::vector<Livro> getAcervo();
    void mostrarRankingLivros();
    Notificador* getNotificador();
    std::vector<Usuario*> getUsuarios();
    Usuario* encontrarUsuarioPorEmail(std::string email);
    bool emailJaCadastrado(std::string email);
    
    // Adicione estas declarações
    void salvarDados();
};