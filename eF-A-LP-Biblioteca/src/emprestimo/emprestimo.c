#include "../../include/emprestimo/emprestimo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

GestaoEmprestimos *gestao;

void inicializarEmprestimos() {
    gestao = malloc(sizeof(GestaoEmprestimos) * 10);
    gestao->emprestimos = malloc(sizeof(Emprestimo) * 10);
    gestao->totalEmprestimos = 0;
    gestao->capacidadeEmprestimos = 10;
}

int adicionarEmprestimo(Emprestimo novoEmprestimo) {
    // Verificar se o utilizador existe
    if (!utilizadorExiste(novoEmprestimo.idUtilizador)) {
        printf("Erro: Utilizador com ID %d não existe.\n", novoEmprestimo.idUtilizador);
        return -1; // Falha ao adicionar empréstimo
    }

    // Verificar se o livro está disponível
    Livro* livro = buscarLivroPorId(novoEmprestimo.idLivro);
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
    }
    gestao->emprestimos[gestao->totalEmprestimos++] = novoEmprestimo;
    return 0; // Sucesso
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
            break;
        }
    }
}

void liberarGestaoEmprestimos() {
    free(gestao->emprestimos);
    gestao->totalEmprestimos = 0;
    gestao->capacidadeEmprestimos = 0;
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
