#pragma once
#include <iostream>
#include "Observer.hpp"

class UsuarioObservador : public IObserver {
public:
    void notificar(const std::string& mensagem) override;
};