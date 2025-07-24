#ifndef SISTEMA_BIBLIOTECA_HPP
#define SISTEMA_BIBLIOTECA_HPP

#include "Usuario.hpp"
#include <vector>

class SistemaBiblioteca {
private:
    static SistemaBiblioteca* instancia;
    std::vector<Usuario*> usuarios;

    SistemaBiblioteca() {}

public:
    static SistemaBiblioteca* getInstancia() {
        if (!instancia)
            instancia = new SistemaBiblioteca();
        return instancia;
    }

    void registrarUsuario(Usuario* usuario);
    void listarUsuarios();
};

#endif