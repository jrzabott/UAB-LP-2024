#include "../../include/livro/livro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Livro *livros = NULL;
int totalLivros = 0;
int capacidadeLivros = 10;

void inicializarLivros() {
    livros = malloc(sizeof(Livro) * capacidadeLivros);
    totalLivros = 0;
}

void adicionarLivro(Livro novoLivro) {
    if (totalLivros == capacidadeLivros) {
        capacidadeLivros *= 2;
        livros = realloc(livros, sizeof(Livro) * capacidadeLivros);
    }
    livros[totalLivros] = novoLivro;
    livros[totalLivros].titulo = strdup(novoLivro.titulo);
    livros[totalLivros].autor = strdup(novoLivro.autor);
    livros[totalLivros].genero = strdup(novoLivro.genero);
    totalLivros++;
}

void removerLivro(int idLivro) {
    for (int i = 0; i < totalLivros; i++) {
        if (livros[i].idLivro == idLivro) {
            free(livros[i].titulo);
            free(livros[i].autor);
            free(livros[i].genero);
            livros[i].titulo = NULL;
            livros[i].autor = NULL;
            livros[i].genero = NULL;

            for (int j = i; j < totalLivros - 1; j++) {
                livros[j] = livros[j + 1];
            }
            totalLivros--;
            return;
        }
    }
}

Livro** buscarLivrosPorTitulo(const char *titulo, int *count) {
    Livro **resultados = malloc(sizeof(Livro*) * totalLivros);
    *count = 0;
    for (int i = 0; i < totalLivros; i++) {
        if (strcmp(livros[i].titulo, titulo) == 0) {
            resultados[(*count)++] = &livros[i];
        }
    }
    return resultados;
}

Livro** buscarLivrosPorAutor(const char *autor, int *count) {
    Livro **resultados = malloc(sizeof(Livro*) * totalLivros);
    *count = 0;
    for (int i = 0; i < totalLivros; i++) {
        if (strcmp(livros[i].autor, autor) == 0) {
            resultados[(*count)++] = &livros[i];
        }
    }
    return resultados;
}

Livro** buscarLivrosPorGenero(const char *genero, int *count) {
    Livro **resultados = malloc(sizeof(Livro*) * totalLivros);
    *count = 0;
    for (int i = 0; i < totalLivros; i++) {
        if (strcmp(livros[i].genero, genero) == 0) {
            resultados[(*count)++] = &livros[i];
        }
    }
    return resultados;
}

void listarTodosOsLivros() {
    printf("Lista de Livros:\n");
    for (int i = 0; i < totalLivros; i++) {
        printf("%d: %s por %s (%s) - %d/%d disponíveis\n",
               livros[i].idLivro, livros[i].titulo, livros[i].autor,
               livros[i].genero, livros[i].exemplaresDisponiveis,
               livros[i].exemplaresTotal);
    }
}

void liberarMemoriaLivros() {
    for (int i = 0; i < totalLivros; i++) {
        free(livros[i].titulo);
        free(livros[i].autor);
        free(livros[i].genero);
        livros[i].titulo = NULL;
        livros[i].autor = NULL;
        livros[i].genero = NULL;
    }
    free(livros);
}

void listarLivrosDisponiveis() {
    printf("Lista de Livros Disponíveis:\n");
    for (int i = 0; i < totalLivros; i++) {
        if (livros[i].exemplaresDisponiveis > 0) {
            printf("%d: %s por %s (%s) - %d exemplares disponíveis\n",
                   livros[i].idLivro, livros[i].titulo, livros[i].autor,
                   livros[i].genero, livros[i].exemplaresDisponiveis);
        }
    }
}

void atualizarLivro(Livro livroAtualizado) {
    Livro *livro = buscarLivroPorId(livroAtualizado.idLivro);
    if (livro == NULL) {
        printf("Livro não encontrado\n");
        return;
    }

    free(livro->titulo);
    free(livro->autor);
    free(livro->genero);
    livro->titulo = strdup(livroAtualizado.titulo);
    livro->autor = strdup(livroAtualizado.autor);
    livro->genero = strdup(livroAtualizado.genero);
    livro->exemplaresTotal = livroAtualizado.exemplaresTotal;
    livro->exemplaresDisponiveis = livroAtualizado.exemplaresDisponiveis;
}

Livro *buscarLivroPorId(int idLivro) {
    for (int i = 0; i < totalLivros; i++) {
        if (livros[i].idLivro == idLivro) {
            return &livros[i];
        }
    }
    return NULL;
}

// TODO - adicionar livro deveria verificar se livro ja existe por titulo e incrementar total de exemplares
// TODO - atualizar livro nao valida dados de entrada, do ponto de vista logico.
