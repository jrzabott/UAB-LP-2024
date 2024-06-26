#include "../../include/utilizador/utilizador.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Utilizador *listaUtilizadores = NULL; // Definindo a lista de utilizadores
int totalUtilizadores = 0;            // Definindo o total de utilizadores
static int maiorId = 0;                       // Definindo o maior ID de utilizador

void inicializarUtilizadores() {
    listaUtilizadores = malloc(sizeof(Utilizador) * 10); // Inicializando espaço para 10 utilizadores
    // Inicializar lista de utilizadores com valores nulos
    for (int i = 0; i < 10; i++) {
        listaUtilizadores[i].idUtilizador = 0;
        listaUtilizadores[i].nome = NULL;
        listaUtilizadores[i].email = NULL;
    }
    totalUtilizadores = 0;
    maiorId = 0;
}

// procura o maior id, salva em cache e retorna o proximo id disponivel
static int obterIdValido(int id) {
    if (id > maiorId) {
        maiorId = id;
        return maiorId;
    }
    if (maiorId == 0) {
        // procurar o maior id
        for (int i = 0; i < totalUtilizadores; i++) {
            if (listaUtilizadores[i].idUtilizador > maiorId)
                maiorId = listaUtilizadores[i].idUtilizador;
        }
    }
    return ++maiorId;
}

void adicionarUtilizador(Utilizador novoUtilizador) {
    if (totalUtilizadores % 10 == 0) {
        // Aumentar o tamanho da lista quando necessário
        listaUtilizadores = realloc(listaUtilizadores, (totalUtilizadores + 10) * sizeof(Utilizador));
        // Inicializar novas posicoes com valores nulos
        for (int i = totalUtilizadores; i < totalUtilizadores + 10; i++) {
            listaUtilizadores[i].idUtilizador = 0;
            listaUtilizadores[i].nome = NULL;
            listaUtilizadores[i].email = NULL;
        }
    }
    novoUtilizador.idUtilizador = obterIdValido(novoUtilizador.idUtilizador);

    listaUtilizadores[totalUtilizadores] = novoUtilizador; // Copiar novo utilizador para a lista
    totalUtilizadores++;
}

void removerUtilizador(int idUtilizador) {
    for (int i = 0; i < totalUtilizadores; i++) {
        if (listaUtilizadores[i].idUtilizador == idUtilizador) {
            for (int j = i; j < totalUtilizadores - 1; j++) {
                listaUtilizadores[j] = listaUtilizadores[j + 1];
            }
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
        listaUtilizadores[i].nome = NULL;
        listaUtilizadores[i].email = NULL;
        free(listaUtilizadores[i].nome);
        free(listaUtilizadores[i].email);
    }
    free(listaUtilizadores);
    listaUtilizadores = NULL;
}
