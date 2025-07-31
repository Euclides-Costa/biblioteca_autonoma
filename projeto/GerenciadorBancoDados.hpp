#pragma once
#include <string>
#include <vector>
#include "Usuario.hpp"
#include "Livro.hpp"

class GerenciadorBancoDados {
public:
    static void salvarUsuarios(const std::vector<Usuario*>& usuarios);
    static void salvarLivros(const std::vector<Livro>& livros);
    static std::vector<Usuario*> carregarUsuarios();
    static std::vector<Livro> carregarLivros();
};