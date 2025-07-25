#include "UsuarioFactory.hpp"

Usuario* UsuarioFactory::criarUsuario(const std::string&, const std::string& nome, const std::string& email, const std::string& senha) {
    return new Usuario(nome, email, senha);
}