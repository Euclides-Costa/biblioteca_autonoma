#include "EstrategiasCredito.hpp"

int CreditoPorDoacao::calcularCredito(Usuario*) {
    return 1; // Ganha 1 crédito ao doar
}

int CreditoPorLeitura::calcularCredito(Usuario*) {
    return -1; // Gasta 1 crédito ao ler
}

CreditoPorAtraso::CreditoPorAtraso(int dias) : diasAtraso(dias) {}

int CreditoPorAtraso::calcularCredito(Usuario*) {
    return -diasAtraso; // Perde créditos por atraso
}