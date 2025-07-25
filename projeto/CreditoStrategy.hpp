#pragma once
class Usuario;

class ICreditoStrategy {
public:
    virtual int calcularCredito(Usuario* usuario) = 0;
    virtual ~ICreditoStrategy() = default;
};