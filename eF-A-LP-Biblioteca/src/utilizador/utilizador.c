#include "../../include/utilizador/utilizador.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Utilizador *listaUtilizadores = NULL; // Definindo a lista de utilizadores
int totalUtilizadores = 0;            // Definindo o total de utilizadores

void inicializarUtilizadores() {
    listaUtilizadores = malloc(sizeof(Utilizador) * 10); // Inicializando espaço para 10 utilizadores
    totalUtilizadores = 0;
}

void adicionarUtilizador(Utilizador novoUtilizador) {
    if (totalUtilizadores % 10 == 0) {
        // Aumentar o tamanho da lista quando necessário
        listaUtilizadores = realloc(listaUtilizadores, (totalUtilizadores + 10) * sizeof(Utilizador));
    }
    listaUtilizadores[totalUtilizadores] = novoUtilizador; // Copiar novo utilizador para a lista
    totalUtilizadores++;
}

void removerUtilizador(int idUtilizador) {
    for (int i = 0; i < totalUtilizadores; i++) {
        if (listaUtilizadores[i].idUtilizador == idUtilizador) {
            memmove(&listaUtilizadores[i], &listaUtilizadores[i + 1], (totalUtilizadores - i - 1) * sizeof(Utilizador));
            totalUtilizadores--;
            break;
        }
    }
}

void atualizarUtilizador(Utilizador utilizadorAtualizado) {
    for (int i = 0; i < totalUtilizadores; i++) {
        if (listaUtilizadores[i].idUtilizador == utilizadorAtualizado.idUtilizador) {
            listaUtilizadores[i] = utilizadorAtualizado; // Atualizar os dados do utilizador
            break;
        }
    }
}

Utilizador *buscarUtilizadorPorNome(const char *nome) {
    for (int i = 0; i < totalUtilizadores; i++) {
        if (strcmp(listaUtilizadores[i].nome, nome) == 0) {
            return &listaUtilizadores[i]; // Retornar o primeiro utilizador encontrado com o nome correspondente
        }
    }
    return NULL; // Nenhum utilizador encontrado
}

void listarTodosOsUtilizadores() {
    for (int i = 0; i < totalUtilizadores; i++) {
        printf("ID: %d, Nome: %s, Email: %s, Livros Emprestados: %d\n",
               listaUtilizadores[i].idUtilizador, listaUtilizadores[i].nome,
               listaUtilizadores[i].email, listaUtilizadores[i].livrosEmprestados);
    }
}

Utilizador *buscarUtilizadorPorId(int idUtilizador) {
    for (int i = 0; i < totalUtilizadores; i++) {
        if (listaUtilizadores[i].idUtilizador == idUtilizador) {
            return &listaUtilizadores[i]; // Retornar o utilizador com o ID correspondente
        }
    }
    return NULL; // Nenhum utilizador encontrado
}

int utilizadorExiste(int idUtilizador) {
    return buscarUtilizadorPorId(idUtilizador) != NULL;
}

void liberarMemoriaUtilizadores() {
    for (int i = 0; i < totalUtilizadores; i++) {
        free(listaUtilizadores[i].nome);
        free(listaUtilizadores[i].email);
        listaUtilizadores[i].nome = NULL;
        listaUtilizadores[i].email = NULL;
    }
    free(listaUtilizadores);
    totalUtilizadores = 0;
}
