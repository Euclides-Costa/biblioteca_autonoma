#include "GerenciadorBancoDados.hpp"
#include <fstream>
#include <sstream>

const std::string ARQUIVO_USUARIOS = "usuarios.txt";
const std::string ARQUIVO_LIVROS = "livros.txt";

void GerenciadorBancoDados::salvarUsuarios(const std::vector<Usuario*>& usuarios) {
    std::ofstream arquivo(ARQUIVO_USUARIOS);
    for (const auto& usuario : usuarios) {
        arquivo << usuario->getNome() << ","
                << usuario->getEmail() << ","
                << usuario->getSenha() << ","
                << usuario->getCreditos() << "\n";
    }
}

void GerenciadorBancoDados::salvarLivros(const std::vector<Livro>& livros) {
    std::ofstream arquivo(ARQUIVO_LIVROS);
    for (const auto& livro : livros) {
        arquivo << livro.getTitulo() << ","
                << livro.getEdicao() << ","
                << livro.getId() << ","
                << livro.getDonoEmail() << ","
                << livro.getEmprestimos() << "\n";
    }
}

std::vector<Usuario*> GerenciadorBancoDados::carregarUsuarios() {
    std::vector<Usuario*> usuarios;
    std::ifstream arquivo(ARQUIVO_USUARIOS);
    std::string linha;
    
    while (getline(arquivo, linha)) {
        std::stringstream ss(linha);
        std::string nome, email, senha, creditosStr;
        getline(ss, nome, ',');
        getline(ss, email, ',');
        getline(ss, senha, ',');
        getline(ss, creditosStr);
        
        int creditos = stoi(creditosStr);
        Usuario* usuario = new Usuario(nome, email, senha);
        usuario->setCreditos(creditos);
        usuarios.push_back(usuario);
    }
    
    return usuarios;
}

std::vector<Livro> GerenciadorBancoDados::carregarLivros() {
    std::vector<Livro> livros;
    std::ifstream arquivo(ARQUIVO_LIVROS);
    std::string linha;
    
    while (getline(arquivo, linha)) {
        std::stringstream ss(linha);
        std::string titulo, edicaoStr, id, donoEmail, emprestimosStr;
        getline(ss, titulo, ',');
        getline(ss, edicaoStr, ',');
        getline(ss, id, ',');
        getline(ss, donoEmail, ',');
        getline(ss, emprestimosStr);
        
        int edicao = stoi(edicaoStr);
        int emprestimos = stoi(emprestimosStr);
        Livro livro(titulo, edicao, donoEmail);
        // Ajustar número de empréstimos
        for (int i = 0; i < emprestimos; i++) {
            livro.registrarEmprestimo();
        }
        livros.push_back(livro);
    }
    
    return livros;
}