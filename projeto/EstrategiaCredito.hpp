#ifndef ESTRATEGIA_CREDITO_HPP
#define ESTRATEGIA_CREDITO_HPP

#include "Usuario.hpp"

class EstrategiaCredito {
public:
    virtual int calcular(Usuario* usuario) = 0;
    virtual ~EstrategiaCredito() {}
};

#endif
