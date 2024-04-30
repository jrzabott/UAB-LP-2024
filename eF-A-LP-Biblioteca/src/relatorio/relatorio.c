#include "../../include/relatorio/relatorio.h"
#include "../../include/emprestimo/emprestimo.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int compararRelatorioLivrosMaisEmprestados(const void *a, const void *b) {
    RelatorioLivrosMaisEmprestados *relatorioLivrosA = (RelatorioLivrosMaisEmprestados *) a;
    RelatorioLivrosMaisEmprestados *relatorioLivrosB = (RelatorioLivrosMaisEmprestados *) b;

    if (relatorioLivrosA->totalEmprestimos > relatorioLivrosB->totalEmprestimos) {
        return -1;
    } else if (relatorioLivrosA->totalEmprestimos < relatorioLivrosB->totalEmprestimos) {
        return 1;
    }

    Livro *livroA = buscarLivroPorId(relatorioLivrosA->idLivro);
    Livro *livroB = buscarLivroPorId(relatorioLivrosB->idLivro);
    if (livroA && livroB) {
        return strcmp(livroA->titulo, livroB->titulo);
    }
    return 0;
}

void gerarRelatorioLivrosMaisEmprestados() {
    RelatorioLivrosMaisEmprestados *relatorioLivros = calloc(totalLivros, sizeof(RelatorioLivrosMaisEmprestados));
    if (relatorioLivros == NULL) {
        printf("Falha na alocação de memória\n");
        return;
    }
    // Inicializar o array com valores nulos
    for (int i = 0; i < totalLivros; i++) {
        relatorioLivros[i].idLivro = 0;
        relatorioLivros[i].totalEmprestimos = 0;
    }

    for (int i = 0; i < gestao->totalEmprestimos; i++) {
        int idLivro = gestao->emprestimos[i].idLivro;
        for (int j = 0; j < totalLivros; j++) {
            if (livros[j].idLivro == idLivro) {
                relatorioLivros[j].idLivro = idLivro;
                relatorioLivros[j].totalEmprestimos++;
            }
        }
    }

    qsort(relatorioLivros, totalLivros, sizeof(RelatorioLivrosMaisEmprestados), compararRelatorioLivrosMaisEmprestados);

    printf("Relatório de Livros Mais Emprestados:\n");
    for (int i = 0; i < totalLivros; i++) {
        Livro *livro = buscarLivroPorId(relatorioLivros[i].idLivro);
        if (livro) {
            printf("ID: %d, Título: %s, Autor: %s, Gênero: %s, Total de Empréstimos: %d\n",
                   livro->idLivro, livro->titulo, livro->autor, livro->genero, relatorioLivros[i].totalEmprestimos);
        }
    }

    free(relatorioLivros);
}


void gerarRelatorioLivrosNaoDevolvidos() {
    // metodo listarLivrosEmprestados() em livro.c cumpre esta funcao
    listarLivrosEmprestados();
}

int compararRelatorioUtilizadoresComMaisEmprestimos(const void *a, const void *b) {
    RelatorioUtilizadoresComMaisEmprestimos *relatorioUtilizadoresA = (RelatorioUtilizadoresComMaisEmprestimos *) a;
    RelatorioUtilizadoresComMaisEmprestimos *relatorioUtilizadoresB = (RelatorioUtilizadoresComMaisEmprestimos *) b;

    // Ordena por quantidade de empréstimos em ordem decrescente
    if (relatorioUtilizadoresA->totalEmprestimos > relatorioUtilizadoresB->totalEmprestimos) {
        return -1;
    } else if (relatorioUtilizadoresA->totalEmprestimos < relatorioUtilizadoresB->totalEmprestimos) {
        return 1;
    }

    return 0;
}

void gerarRelatorioUtilizadoresComMaisEmprestimos() {
    // Inicializa o array de RelatorioUtilizadoresComMaisEmprestimos
    RelatorioUtilizadoresComMaisEmprestimos *relatorio = (RelatorioUtilizadoresComMaisEmprestimos *) malloc(
            sizeof(RelatorioUtilizadoresComMaisEmprestimos) * totalUtilizadores);
    // Inicializa o array com valores nulos
    for (int i = 0; i < sizeof(*relatorio); i++) {
        relatorio[i].idUtilizador = 0;
        relatorio[i].totalEmprestimos = 0;
    }

    // Preenche o array com os dados dos utilizadores e a quantidade de empréstimos
    for (int i = 0; i < gestao->totalEmprestimos; i++) {
        int idUtilizador = gestao->emprestimos[i].idUtilizador;
        for (int j = 0; j < totalUtilizadores; j++) {
            if (listaUtilizadores[j].idUtilizador == idUtilizador) {
                relatorio[j].idUtilizador = idUtilizador;
                relatorio[j].totalEmprestimos++;
            }
        }
    }

    // Ordena o array de RelatorioUtilizadoresComMaisEmprestimos por quantidade de empréstimos em ordem decrescente
    qsort(relatorio, totalUtilizadores, sizeof(RelatorioUtilizadoresComMaisEmprestimos),
          compararRelatorioUtilizadoresComMaisEmprestimos);

    //imprime relatorio no terminal
    printf("Relatório de Utilizadores com Mais Empréstimos:\n");
    for (int i = 0; i < totalUtilizadores; i++) {
        printf("ID: %d, Nome: %s, Email: %s, Livros Emprestados: %d\n",
               relatorio[i].idUtilizador, listaUtilizadores[i].nome,
               listaUtilizadores[i].email, relatorio[i].totalEmprestimos);
    }
    free(relatorio);
}