#pragma once
#include "Biblioteca.hpp"
#include "Usuario.hpp"
#include "UsuarioObservador.hpp"

class InterfaceUsuario {
public:
    static void executarSistema();
    
private:
    static void limparTela();
    static void pausar();
    static int lerInteiro(const std::string& mensagem);
    static void exibirCabecalho(const std::string& titulo);
    static void telaBoasVindas(Biblioteca* bib, UsuarioObservador& observador);
    static void telaMenuPrincipal(Biblioteca* bib, Usuario* usuario);
    static void telaEmprestarLivro(Biblioteca* bib, Usuario* usuario);
    static void telaLerLivro(Biblioteca* bib, Usuario* usuario);
    static void telaDevolverLivro(Biblioteca* bib, Usuario* usuario);
    static void telaRankingLivros(Biblioteca* bib);
    static void telaHistoricoCedidos(Usuario* usuario);
    static void telaHistoricoLidos(Usuario* usuario);
};