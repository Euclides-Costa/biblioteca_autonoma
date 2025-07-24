#ifndef USUARIO_FACTORY_HPP
#define USUARIO_FACTORY_HPP

#include "Usuario.hpp"
#include <string>

class UsuarioFactory {
public:
    static Usuario* criarUsuario(const std::string& tipo, const std::string& nome, const std::string& email, const std::string& senha) {
        if (tipo == "aluno") {
            return new Usuario(nome, email, senha);
        }
        return nullptr;
    }
};

#endif