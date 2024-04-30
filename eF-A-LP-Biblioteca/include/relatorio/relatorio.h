#ifndef EF_A_LP_BIBLIOTECA_TESTS_RELATORIO_H
#define EF_A_LP_BIBLIOTECA_TESTS_RELATORIO_H

typedef struct {
    int idLivro;
    int totalEmprestimos;
} RelatorioLivrosMaisEmprestados;

typedef struct {
    int idUtilizador;
    int totalEmprestimos;
} RelatorioUtilizadoresComMaisEmprestimos;

void gerarRelatorioLivrosMaisEmprestados();
void gerarRelatorioLivrosNaoDevolvidos();
void gerarRelatorioUtilizadoresComMaisEmprestimos();

#endif //EF_A_LP_BIBLIOTECA_TESTS_RELATORIO_H
