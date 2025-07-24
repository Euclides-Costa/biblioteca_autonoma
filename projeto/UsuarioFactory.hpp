#ifndef USUARIO_FACTORY_HPP
#define USUARIO_FACTORY_HPP

#include "Usuario.hpp"

class UsuarioFactory {
public:
    static Usuario* criarUsuario(const std::string& tipo, const std::string& nome) {
        // Pode expandir com subclasses
        return new Usuario(nome);
    }
};

#endif
