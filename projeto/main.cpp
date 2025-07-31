// main.cpp
#include "InterfaceUsuario.hpp"
#include <cstdlib>

void salvarAoEncerrar() {
    auto bib = Biblioteca::getInstancia();
    bib->salvarDados();
}

int main() {
    std::atexit(salvarAoEncerrar);
    
    try {
        InterfaceUsuario::executarSistema();
    } catch (...) {
        salvarAoEncerrar();
        return 1;
    }
    
    return 0;
}