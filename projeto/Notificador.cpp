#include "Notificador.hpp"

void Notificador::adicionar(IObserver* obs) {
    observadores.push_back(obs);
}

void Notificador::notificarTodos(const std::string& msg) {
    for (auto& obs : observadores)
        obs->notificar(msg);
}