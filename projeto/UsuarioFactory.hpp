#pragma once
#include "Usuario.hpp"

class UsuarioFactory {
public:
    static Usuario* criarUsuario(const std::string& tipo, const std::string& nome, const std::string& email, const std::string& senha);
};