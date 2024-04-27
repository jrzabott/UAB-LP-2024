#include "../../include/utilizador/utilizador_dao.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

#define MAX_LINE_LENGTH 1024

int validarDadosUtilizador(char *linha, Utilizador *u, int linhaNum) {
    char *token;
    int valid = 1;

    token = strtok(linha, ",");
    u->idUtilizador = atoi(token);
    if (!u->idUtilizador) {
        fprintf(stderr, "ID inválido '%s'\n", token);
        valid = 0;
    }

    token = strtok(NULL, ",");
    u->nome = token && strlen(token) > 0 ? strdup(token) : NULL;
    if (!u->nome) {
        fprintf(stderr, "Nome está vazio\n");
        valid = 0;
    }

    token = strtok(NULL, ",");
    u->email = token ? strdup(token) : strdup("");

    token = strtok(NULL, ",");
    token = strtok(token, "\n");
    char *endptr;
    errno = 0;  // Assegurar que o errno está limpo antes da chamada
    long livrosEmprestados = strtol(token, &endptr, 10);

    if (errno == ERANGE || *endptr != '\0' || endptr == token) {
        fprintf(stderr, "Número de empréstimos inválido '%s'\n", token);
        valid = 0;
    } else {
        u->livrosEmprestados = (int)livrosEmprestados;
    }

    if (!valid) {
        if (u->nome) free(u->nome);
        if (u->email) free(u->email);
        return 0;
    }
    return 1;
}

void carregarUtilizadoresDeCSV(const char *caminhoArquivo) {
    FILE *file = fopen(caminhoArquivo, "r");
    if (!file) {
        perror("Erro ao abrir arquivo de utilizadores");
        return;
    }

    char linha[MAX_LINE_LENGTH];
    int linhaNum = 0;
    while (fgets(linha, sizeof(linha), file)) {
        linhaNum++;
        Utilizador u;
        if (validarDadosUtilizador(linha, &u, linhaNum)) {
            adicionarUtilizador(u);
        } else {
            fprintf(stderr, "Erro na linha %d: Dados inválidos.\n", linhaNum);
        }
    }
    fclose(file);
}


void guardarUtilizadoresEmCSV(const char *caminhoArquivo) {
    FILE *file = fopen(caminhoArquivo, "w");
    if (!file) {
        perror("Erro ao salvar arquivo de utilizadores");
        return;
    }

    for (int i = 0; i < totalUtilizadores; i++) {
        fprintf(file, "%d,%s,%s,%d\n",
                listaUtilizadores[i].idUtilizador,
                listaUtilizadores[i].nome,
                listaUtilizadores[i].email,
                listaUtilizadores[i].livrosEmprestados);
    }
    fclose(file);
}
