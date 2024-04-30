#include "util/unity/unity.h"
#include "../include/livro/livro.h"
#include "../include/utilizador/utilizador.h"
#include "../include/emprestimo/emprestimo.h"
#include "../include/livro/livro_dao.h"
#include "../include/utilizador/utilizador_dao.h"
#include "../include/emprestimo/emprestimo_dao.h"
#include "../include/relatorio/relatorio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


void setUp(void) {
    inicializarLivros();
    inicializarUtilizadores();
    inicializarEmprestimos();
}

void tearDown(void) {
    liberarGestaoEmprestimos();
    liberarMemoriaLivros();
    liberarMemoriaUtilizadores();
}

void adicionarDados() { // Adicionar dados de teste para livros
    adicionarLivro((Livro){1, "Livro A", "Autor A", "Ficção", 3, 3});
    adicionarLivro((Livro){2, "Livro B", "Autor B", "História", 2, 2});
    adicionarLivro((Livro){3, "Livro C", "Autor C", "Ciência", 2, 2});
    adicionarLivro((Livro){4, "Livro D", "Autor D", "Tecnologia", 1, 1});
    adicionarLivro((Livro){5, "Livro E", "Autor E", "Arte", 4, 4});

    // Adicionar dados de teste para utilizadores
    adicionarUtilizador((Utilizador){1, "João", "joao@example.com", 0});
    adicionarUtilizador((Utilizador){2, "Maria", "maria@example.com", 0});
    adicionarUtilizador((Utilizador){3, "Ana", "ana@example.com", 0});

    // Adicionar empréstimos de teste
    adicionarEmprestimo((Emprestimo){1, 1, 1, time(NULL), time(NULL) + 86400, 0});
    adicionarEmprestimo((Emprestimo){2, 2, 2, time(NULL), time(NULL) + 86400, 0});
    adicionarEmprestimo((Emprestimo){3, 3, 3, time(NULL), time(NULL) + 86400, 0});
    adicionarEmprestimo((Emprestimo){4, 5, 3, time(NULL), time(NULL) + 86400, 0});
    adicionarEmprestimo((Emprestimo){5, 1, 3, time(NULL), time(NULL) + 86400, 0});
}

void test_IntegracaoCompletaSistema(void) {
    // Adicionar dados
    adicionarDados();

    // Salvar os dados iniciais em CSV
    guardarLivrosEmCSV("livros.csv");
    guardarUtilizadoresEmCSV("utilizadores.csv");
    guardarEmprestimosEmCSV("emprestimos.csv");

// imprimir todos os livros, utilizadores e emprestimos para debug
//    printf("\nLivros:\n");
//    listarTodosOsLivros();
//
//    printf("\nUtilizadores:\n");
//    listarTodosOsUtilizadores();
//
//    printf("\nEmprestimos:\n");
//    listarTodosOsEmprestimos();


    // Limpar a memória para simular o reinício do sistema
    tearDown();
    setUp();

    // Carregar os dados dos arquivos CSV
    carregarLivrosDeCSV("livros.csv");
    carregarUtilizadoresDeCSV("utilizadores.csv");
    carregarEmprestimosDeCSV("emprestimos.csv");

// imprimir todos os livros, utilizadores e emprestimos para debug
//    printf("\nLivros:\n");
//    listarTodosOsLivros();
//
//    printf("\nUtilizadores:\n");
//    listarTodosOsUtilizadores();
//
//    printf("\nEmprestimos:\n");
//    listarTodosOsEmprestimos();


    // Gerar relatórios
    gerarRelatorioLivrosMaisEmprestados();
    gerarRelatorioLivrosNaoDevolvidos();
    gerarRelatorioUtilizadoresComMaisEmprestimos();
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_IntegracaoCompletaSistema);
    return UNITY_END();
}
