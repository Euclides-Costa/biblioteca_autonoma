#ifndef CREDITO_POR_DOACAO_HPP
#define CREDITO_POR_DOACAO_HPP

#include "EstrategiaCredito.hpp"

class CreditoPorDoacao : public EstrategiaCredito {
public:
    int calcular(Usuario* usuario) override {
        return usuario->getLivrosCedido();
    }
};

#endif