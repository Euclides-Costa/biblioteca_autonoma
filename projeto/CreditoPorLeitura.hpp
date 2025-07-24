#ifndef CREDITO_POR_LEITURA_HPP
#define CREDITO_POR_LEITURA_HPP

#include "EstrategiaCredito.hpp"

class CreditoPorLeitura : public EstrategiaCredito {
public:
    int calcular(Usuario* usuario) override {
        return usuario->getLivrosLidos();
    }
};

#endif