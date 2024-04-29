#include "../../include/emprestimo/emprestimo_dao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

void carregarEmprestimosDeCSV(const char *caminhoArquivo) {
    FILE *file = fopen(caminhoArquivo, "r");
    if (!file) {
        perror("Erro ao abrir arquivo de empréstimos");
        return;
    }

    char linha[MAX_LINE_LENGTH];
    while (fgets(linha, sizeof(linha), file)) {
        Emprestimo e;
        char *token = strtok(linha, ",");
        e.idEmprestimo = atoi(token);

        token = strtok(NULL, ",");
        e.idLivro = atoi(token);

        token = strtok(NULL, ",");
        e.idUtilizador = atoi(token);

        token = strtok(NULL, ",");
        e.dataEmprestimo = (time_t)atoll(token);

        token = strtok(NULL, ",");
        e.dataDevolucaoPrevista = (time_t)atoll(token);

        token = strtok(NULL, ",");
        e.dataDevolucaoReal = (time_t)atoll(token);

        // Suponha uma função adicionarEmprestimo() que adiciona à lista em memória
        adicionarEmprestimo(e);
    }
    fclose(file);
}

void guardarEmprestimosEmCSV(const char *caminhoArquivo) {
    FILE *file = fopen(caminhoArquivo, "w");
    if (!file) {
        perror("Erro ao salvar arquivo de empréstimos");
        return;
    }

    // Suponha que 'emprestimos' e 'totalEmprestimos' sejam acessíveis aqui
    for (int i = 0; i < gestao->totalEmprestimos; i++) {
        fprintf(file, "%d,%d,%d,%ld,%ld,%ld\n",
                gestao->emprestimos[i].idEmprestimo,
                gestao->emprestimos[i].idLivro,
                gestao->emprestimos[i].idUtilizador,
                (long)gestao->emprestimos[i].dataEmprestimo,
                (long)gestao->emprestimos[i].dataDevolucaoPrevista,
                (long)gestao->emprestimos[i].dataDevolucaoReal);
    }
    fclose(file);
}
