#include "SistemaBiblioteca.hpp"
#include <iostream>

SistemaBiblioteca* SistemaBiblioteca::instancia = nullptr;

void SistemaBiblioteca::registrarUsuario(Usuario* usuario) {
    usuarios.push_back(usuario);
}

void SistemaBiblioteca::listarUsuarios() {
    for (auto u : usuarios)
        std::cout << "Usuário: " << u->getNome() << "\n";
}