#pragma once
#include <vector>
#include "Observer.hpp"

class Notificador {
    std::vector<IObserver*> observadores;
public:
    void adicionar(IObserver* obs);
    void notificarTodos(const std::string& msg);
};