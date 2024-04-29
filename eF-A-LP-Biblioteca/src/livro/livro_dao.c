#include "../../include/livro/livro_dao.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX_LINE_LENGTH 1024

//int validarDadosLivro(char *linha, Livro *l, int linhaNum) {
//    char *token;
//    int valid = 1;
//
//    token = strtok(linha, ",");
//    l->idLivro = atoi(token);
//    if (!l->idLivro) {
//        fprintf(stderr, "Erro na linha %d: ID inválido '%s'\n", linhaNum, token);
//        valid = 0;
//    }
//
//    token = strtok(NULL, ",");
//    l->titulo = token && strlen(token) > 0 ? strdup(token) : NULL;
//    if (!l->titulo) {
//        fprintf(stderr, "Erro na linha %d: Título está vazio\n", linhaNum);
//        valid = 0;
//    }
//
//    token = strtok(NULL, ",");
//    l->autor = token && strlen(token) > 0 ? strdup(token) : NULL;
//    if (!l->autor) {
//        fprintf(stderr, "Erro na linha %d: Autor está vazio\n", linhaNum);
//        valid = 0;
//    }
//
//    token = strtok(NULL, ",");
//    l->genero = token && strlen(token) > 0 ? strdup(token) : NULL;
//    if (!l->genero) {
//        fprintf(stderr, "Erro na linha %d: Gênero está vazio\n", linhaNum);
//        valid = 0;
//    }
//
//    token = strtok(NULL, ",");
//    l->exemplaresTotal = atoi(token);
//    if (l->exemplaresTotal <= 0) {
//        fprintf(stderr, "Erro na linha %d: Total de exemplares inválido '%s'\n", linhaNum, token);
//        valid = 0;
//    }
//
//    token = strtok(NULL, "\n");
//    l->exemplaresDisponiveis = atoi(token);
//    if (l->exemplaresDisponiveis < 0 || l->exemplaresDisponiveis > l->exemplaresTotal) {
//        fprintf(stderr, "Erro na linha %d: Exemplares disponíveis inválido '%s'\n", linhaNum, token);
//        valid = 0;
//    }
//
//    if (!valid) {
//        if (l->titulo) free(l->titulo);
//        if (l->autor) free(l->autor);
//        if (l->genero) free(l->genero);
//        return 0;
//    }
//    return 1;
//}

int validarDadosLivro(char *linha, Livro *l, int linhaNum) {
    char *token;
    int valid = 1;

    token = strtok(linha, ",");
    if (token == NULL || (l->idLivro = atoi(token)) == 0) {
        fprintf(stderr, "Erro na linha %d: ID inválido ou ausente '%s'\n", linhaNum, token);
        valid = 0;
    }

    token = strtok(NULL, ",");
    if (token == NULL || strlen(token) == 0) {
        fprintf(stderr, "Erro na linha %d: Título ausente\n", linhaNum);
        valid = 0;
    } else {
        l->titulo = strdup(token);
    }

    token = strtok(NULL, ",");
    if (token == NULL || strlen(token) == 0) {
        fprintf(stderr, "Erro na linha %d: Autor ausente\n", linhaNum);
        valid = 0;
    } else {
        l->autor = strdup(token);
    }

    token = strtok(NULL, ",");
    if (token == NULL || strlen(token) == 0) {
        fprintf(stderr, "Erro na linha %d: Gênero ausente\n", linhaNum);
        valid = 0;
    } else {
        l->genero = strdup(token);
    }

    token = strtok(NULL, ",");
    if (token == NULL || (l->exemplaresTotal = atoi(token)) <= 0) {
        fprintf(stderr, "Erro na linha %d: Total de exemplares inválido ou ausente '%s'\n", linhaNum, token);
        valid = 0;
    }

    token = strtok(NULL, "\n");
    if (token == NULL || (l->exemplaresDisponiveis = atoi(token)) < 0 || l->exemplaresDisponiveis > l->exemplaresTotal) {
        fprintf(stderr, "Erro na linha %d: Exemplares disponíveis inválidos ou ausentes '%s'\n", linhaNum, token);
        valid = 0;
    }

    if (!valid) {
        free(l->titulo);
        free(l->autor);
        free(l->genero);
    }
    return valid;
}

void carregarLivrosDeCSV(const char *caminhoArquivo) {
    FILE *file = fopen(caminhoArquivo, "r");
    if (!file) {
        perror("Erro ao abrir arquivo de livros");
        return;
    }

    char linha[MAX_LINE_LENGTH];
    int linhaNum = 0;
    while (fgets(linha, sizeof(linha), file)) {
        linhaNum++;
        Livro l;
        if (validarDadosLivro(linha, &l, linhaNum)) {
            adicionarLivro(l);
        } else {
            fprintf(stderr, "Erro na linha %d: Dados inválidos.\n", linhaNum);
        }
    }
    fclose(file);
}

void guardarLivrosEmCSV(const char *caminhoArquivo) {
    FILE *file = fopen(caminhoArquivo, "w");
    if (!file) {
        perror("Erro ao salvar arquivo de livros");
        return;
    }

    for (int i = 0; i < totalLivros; i++) {
        fprintf(file, "%d,%s,%s,%s,%d,%d\n",
                livros[i].idLivro,
                livros[i].titulo,
                livros[i].autor,
                livros[i].genero,
                livros[i].exemplaresTotal,
                livros[i].exemplaresDisponiveis);
    }
    fclose(file);
}
