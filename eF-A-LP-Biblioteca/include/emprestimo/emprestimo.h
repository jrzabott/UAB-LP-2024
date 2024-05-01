#ifndef EF_A_LP_BIBLIOTECA_EMPRESTIMO_H
#define EF_A_LP_BIBLIOTECA_EMPRESTIMO_H

#include "../livro/livro.h"
#include "../utilizador/utilizador.h"
#include <time.h>

// Estrutura para representar um empréstimo de livro
typedef struct {
    int idEmprestimo;                // Identificador único do empréstimo
    int idLivro;                     // Identificador do livro emprestado
    int idUtilizador;                // Identificador do utilizador que pegou o livro
    time_t dataEmprestimo;           // Data do empréstimo
    time_t dataDevolucaoPrevista;    // Data prevista para devolução
    time_t dataDevolucaoReal;        // Data real de devolução
} Emprestimo;

// Estrutura para armazenar os empréstimos
typedef struct {
    Emprestimo *emprestimos;
    int totalEmprestimos;
    int capacidadeEmprestimos;
} GestaoEmprestimos;

extern GestaoEmprestimos *gestao;

// Inicializa a gestão de empréstimos
void inicializarEmprestimos();

// Regista um novo empréstimo (retorna 0 em caso de sucesso, -1 em caso de erro)
int adicionarEmprestimo(Emprestimo novoEmprestimo);

// Atualiza a data de devolução de um empréstimo
void actualizarDevolucaoEmprestimo(int idEmprestimo, time_t novaDataDevolucao);

// Renova um empréstimo, estendendo a data de devolução prevista
void renovarEmprestimo(int idEmprestimo, int diasAdicionais);

// Finaliza um empréstimo indicando a devolução do livro
int finalizarEmprestimo(int idEmprestimo);

// Lista todos os empréstimos activos (livros ainda não devolvidos)
void listarEmprestimosActivos();

// Libera recursos utilizados pelo sistema de empréstimos
void liberarGestaoEmprestimos();

// Listar todos os emprestimos
void listarTodosOsEmprestimos();

// Buscar emprestimo por id
Emprestimo *buscarEmprestimoPorId(int idEmprestimo);

#endif //EF_A_LP_BIBLIOTECA_EMPRESTIMO_H
