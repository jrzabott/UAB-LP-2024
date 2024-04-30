#include "unity.h"
#include "../../include/livro/livro.h"
#include "../../include/utilizador/utilizador.h"
#include "../../include/emprestimo/emprestimo.h"
#include "../../include/relatorio/relatorio.h"
#include <time.h>


void setUp(void) {
    inicializarLivros();
    inicializarUtilizadores();
    inicializarEmprestimos();

    // Adicionar livros de teste
    adicionarLivro((Livro){1, "Livro A", "Autor A", "Categoria A", 5, 5});
    adicionarLivro((Livro){2, "Livro B", "Autor B", "Categoria B", 5, 4}); // 1 emprestado

    // Adicionar utilizadores de teste
    adicionarUtilizador((Utilizador){1, "Utilizador A", "emaila@example.com", 0});
    adicionarUtilizador((Utilizador){2, "Utilizador B", "emailb@example.com", 0});

    // Simular empréstimos
    adicionarEmprestimo((Emprestimo){1, 1, 1, time(NULL), time(NULL) + 86400, 0}); // Livro A por Utilizador A
    adicionarEmprestimo((Emprestimo){2, 2, 1, time(NULL), time(NULL) + 86400, 0}); // Livro B por Utilizador A
}

void tearDown(void) {
    liberarMemoriaLivros();
    liberarMemoriaUtilizadores();
    liberarGestaoEmprestimos();
}

void test_RelatorioLivrosMaisEmprestados(void) {
    gerarRelatorioLivrosMaisEmprestados();
    // Verificar a saída esperada, por exemplo, verificando a saída padrão ou uma variável de log
    // Esta parte do teste pode necessitar de ajustes para capturar a saída do console ou validar os dados de outra forma
}

void test_RelatorioLivrosNaoDevolvidos(void) {
    gerarRelatorioLivrosNaoDevolvidos();
    // Verificações semelhantes ao teste anterior
}

void test_RelatorioUtilizadoresComMaisEmprestimos(void) {
    gerarRelatorioUtilizadoresComMaisEmprestimos();
    // Verificações semelhantes ao teste anterior
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_RelatorioLivrosMaisEmprestados);
    RUN_TEST(test_RelatorioLivrosNaoDevolvidos);
    RUN_TEST(test_RelatorioUtilizadoresComMaisEmprestimos);
    return UNITY_END();
}
