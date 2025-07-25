#pragma once
#include <string>

class IObserver {
public:
    virtual void notificar(const std::string& mensagem) = 0;
};