#include "UsuarioObservador.hpp"

void UsuarioObservador::notificar(const std::string& mensagem) {
    std::cout << "[Notificação]: " << mensagem << std::endl;
}