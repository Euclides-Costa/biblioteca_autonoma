#pragma once
#include "CreditoStrategy.hpp"
#include "Usuario.hpp"

class CreditoPorDoacao : public ICreditoStrategy {
public:
    int calcularCredito(Usuario* usuario) override;
};

class CreditoPorLeitura : public ICreditoStrategy {
public:
    int calcularCredito(Usuario* usuario) override;
};

class CreditoPorAtraso : public ICreditoStrategy {
    int diasAtraso;
public:
    CreditoPorAtraso(int dias);
    int calcularCredito(Usuario* usuario) override;
};