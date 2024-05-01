#include "../../include/livro/livro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Livro *livros = NULL;
int totalLivros = 0;
int capacidadeLivros = 10;
static int maiorId = 0;

Livro LIVRO_NAO_ENCONTRADO;

void inicializarLivroNaoEncontrado();

void inicializarLivros() {
    livros = malloc(sizeof(Livro) * capacidadeLivros);
    // Inicializar a lista de livros
    for (int i = 0; i < capacidadeLivros; i++) {
        livros[i].idLivro = 0;
        livros[i].titulo = NULL;
        livros[i].autor = NULL;
        livros[i].genero = NULL;
        livros[i].exemplaresDisponiveis = 0;
        livros[i].exemplaresTotal = 0;
    }
    totalLivros = 0;
    maiorId = 0;
    inicializarLivroNaoEncontrado();
}

void inicializarLivroNaoEncontrado() {
    LIVRO_NAO_ENCONTRADO.idLivro = 0;
    LIVRO_NAO_ENCONTRADO.titulo = "Livro não encontrado";
    LIVRO_NAO_ENCONTRADO.autor = "";
    LIVRO_NAO_ENCONTRADO.genero = "";
    LIVRO_NAO_ENCONTRADO.exemplaresTotal = 0;
    LIVRO_NAO_ENCONTRADO.exemplaresDisponiveis = 0;
}

// procura o maior id, salva em cache e retorna o proximo id disponivel
static int obterIdValido(int id) {
    if (id > maiorId) {
        maiorId = id;
        return maiorId;
    }
    if (maiorId == 0) {
        // procurar o maior id
        for (int i = 0; i < totalLivros; i++) {
            if (livros[i].idLivro > maiorId)
                maiorId = livros[i].idLivro;
        }
    }
    return ++maiorId;
}

int adicionarLivro(Livro novoLivro) {
    if (totalLivros == capacidadeLivros) {
        capacidadeLivros *= 2;
        livros = realloc(livros, sizeof(Livro) * capacidadeLivros);
        // Inicializar as novas posições
        for (int i = totalLivros; i < capacidadeLivros; i++) {
            livros[i].idLivro = 0;
            livros[i].titulo = NULL;
            livros[i].autor = NULL;
            livros[i].genero = NULL;
            livros[i].exemplaresDisponiveis = 0;
            livros[i].exemplaresTotal = 0;
        }
    }
    // verificar se livro com este ID ja existe, caso positivo, procurar o proximo ID disponivel
    novoLivro.idLivro = obterIdValido(novoLivro.idLivro);

    livros[totalLivros] = novoLivro;
    livros[totalLivros].titulo = strdup(novoLivro.titulo);
    livros[totalLivros].autor = strdup(novoLivro.autor);
    livros[totalLivros].genero = strdup(novoLivro.genero);
    totalLivros++;
    return novoLivro.idLivro;
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
        livros[i].exemplaresDisponiveis = 0;
        livros[i].exemplaresTotal = 0;
    }
    free(livros);
    livros = NULL;

    free(LIVRO_NAO_ENCONTRADO.titulo);
    free(LIVRO_NAO_ENCONTRADO.autor);
    free(LIVRO_NAO_ENCONTRADO.genero);
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
    return &LIVRO_NAO_ENCONTRADO;
}

void listarLivrosEmprestados() {
    printf("Lista de Livros Emprestados:\n");
    for (int i = 0; i < totalLivros; i++) {
        if (livros[i].exemplaresDisponiveis < livros[i].exemplaresTotal) {
            printf("%d: %s por %s (%s) - %d / %d exemplares disponíveis\n",
                   livros[i].idLivro, livros[i].titulo, livros[i].autor,
                   livros[i].genero, livros[i].exemplaresDisponiveis,
                   livros[i].exemplaresTotal);
        }
    }
}
