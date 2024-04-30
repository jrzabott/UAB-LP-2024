#include "../../include/emprestimo/emprestimo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

GestaoEmprestimos *gestao;
static int maiorId = 0;

void inicializarEmprestimos() {
    gestao = malloc(sizeof(GestaoEmprestimos) * 10);
    gestao->emprestimos = malloc(sizeof(Emprestimo) * 10);
    gestao->totalEmprestimos = 0;
    gestao->capacidadeEmprestimos = 10;

    // Inicializar array com valores nulos
    for (int i = 0; i < gestao->capacidadeEmprestimos; i++) {
        gestao->emprestimos[i].idEmprestimo = 0;
        gestao->emprestimos[i].idLivro = 0;
        gestao->emprestimos[i].idUtilizador = 0;
        gestao->emprestimos[i].dataDevolucaoPrevista = 0;
        gestao->emprestimos[i].dataDevolucaoReal = 0;
    }
}

// procura o maior id, salva em cache e retorna o proximo id disponivel
int obterIdValido(int id) {
    if (id > maiorId) {
        maiorId = id;
        return maiorId;
    }
    if (maiorId == 0) {
        // procurar o maior id
        for (int i = 0; i < gestao->totalEmprestimos; i++) {
            if (gestao->emprestimos[i].idEmprestimo > maiorId)
                maiorId = gestao->emprestimos[i].idEmprestimo;
        }
    }
    return ++maiorId;
}

int adicionarEmprestimo(Emprestimo novoEmprestimo) {
    // Verificar se o utilizador existe
    if (!utilizadorExiste(novoEmprestimo.idUtilizador)) {
        printf("Erro: Utilizador com ID %d não existe.\n", novoEmprestimo.idUtilizador);
        return -1; // Falha ao adicionar empréstimo
    }

    // Verificar se o livro está disponível
    Livro *livro = buscarLivroPorId(novoEmprestimo.idLivro);
    if (livro == NULL || livro->exemplaresDisponiveis <= 0) {
        printf("Erro: Livro com ID %d não está disponível para empréstimo.\n", novoEmprestimo.idLivro);
        return -1; // Falha ao adicionar empréstimo
    }

    // Decrementar um exemplar disponível do livro
    livro->exemplaresDisponiveis--;

    // Adicionar o empréstimo
    if (gestao->totalEmprestimos == gestao->capacidadeEmprestimos) {
        gestao->capacidadeEmprestimos *= 2;
        gestao->emprestimos = realloc(gestao->emprestimos, sizeof(Emprestimo) * gestao->capacidadeEmprestimos);

        // inicializar novas posicoes com valores a nulo
        for (int i = gestao->totalEmprestimos; i < gestao->capacidadeEmprestimos; i++) {
            gestao->emprestimos[i].idEmprestimo = 0;
            gestao->emprestimos[i].idLivro = 0;
            gestao->emprestimos[i].idUtilizador = 0;
            gestao->emprestimos[i].dataDevolucaoPrevista = 0;
            gestao->emprestimos[i].dataDevolucaoReal = 0;
        }
    }
    novoEmprestimo.idEmprestimo = obterIdValido(novoEmprestimo.idEmprestimo);
    gestao->emprestimos[gestao->totalEmprestimos++] = novoEmprestimo;

    // Incrementar o contador de livros emprestados para o utilizador
    buscarUtilizadorPorId(novoEmprestimo.idUtilizador)->livrosEmprestados++;

    return novoEmprestimo.idEmprestimo; // Sucesso
}

void actualizarDevolucaoEmprestimo(int idEmprestimo, time_t novaDataDevolucao) {
    for (int i = 0; i < gestao->totalEmprestimos; i++) {
        if (gestao->emprestimos[i].idEmprestimo == idEmprestimo) {
            gestao->emprestimos[i].dataDevolucaoReal = novaDataDevolucao;
            break;
        }
    }
}

void renovarEmprestimo(int idEmprestimo, int diasAdicionais) {
    for (int i = 0; i < gestao->totalEmprestimos; i++) {
        if (gestao->emprestimos[i].idEmprestimo == idEmprestimo) {
            time_t novaData = gestao->emprestimos[i].dataDevolucaoPrevista + (diasAdicionais * 86400);
            gestao->emprestimos[i].dataDevolucaoPrevista = novaData;
            break;
        }
    }
}

void finalizarEmprestimo(int idEmprestimo) {
    for (int i = 0; i < gestao->totalEmprestimos; i++) {
        if (gestao->emprestimos[i].idEmprestimo == idEmprestimo) {
            // Marcar o empréstimo como concluído pode envolver apenas ajustar a data de devolução real para agora
            gestao->emprestimos[i].dataDevolucaoReal = time(NULL);
            // Reduzir contador de livros emprestados de utilizador
            buscarUtilizadorPorId(gestao->emprestimos[i].idUtilizador)->livrosEmprestados--;
            break;
        }
    }
}

void liberarGestaoEmprestimos() {
    free(gestao->emprestimos);
    gestao->totalEmprestimos = 0;
    gestao->capacidadeEmprestimos = 0;
    free(gestao);
    gestao = NULL;
}

void listarEmprestimosActivos() {
    printf("Emprestimos Ativos:\n");
    for (int i = 0; i < gestao->totalEmprestimos; i++) {
        if (gestao->emprestimos[i].dataDevolucaoReal == 0) { // dataDevolucaoReal não definida significa ainda ativo
            printf("Emprestimo ID: %d, Livro ID: %d, Utilizador ID: %d, Data Prevista: %s\n",
                   gestao->emprestimos[i].idEmprestimo, gestao->emprestimos[i].idLivro,
                   gestao->emprestimos[i].idUtilizador, ctime(&gestao->emprestimos[i].dataDevolucaoPrevista));
        }
    }
}

void listarTodosOsEmprestimos() {
    printf("Lista de Empréstimos:\n");
    for (int i = 0; i < gestao->totalEmprestimos; i++) {
        printf("Emprestimo ID: %d, Livro ID: %d, Livro Titulo: %s, Utilizador ID: %d, Utilizador Nome: %s, Data Prevista: %s, Data Real: %s",
               gestao->emprestimos[i].idEmprestimo, gestao->emprestimos[i].idLivro,
               buscarLivroPorId(gestao->emprestimos[i].idLivro)->titulo,
               gestao->emprestimos[i].idUtilizador, buscarUtilizadorPorId(gestao->emprestimos[i].idUtilizador)->nome,
               ctime(&gestao->emprestimos[i].dataDevolucaoPrevista),
               ctime(&gestao->emprestimos[i].dataDevolucaoReal));
    }
}

Emprestimo *buscarEmprestimoPorId(int idEmprestimo) {
    for (int i = 0; i < gestao->totalEmprestimos; i++) {
        if (gestao->emprestimos[i].idEmprestimo == idEmprestimo) {
            return &gestao->emprestimos[i];
        }
    }
    return NULL;
}