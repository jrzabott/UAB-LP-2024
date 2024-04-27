#ifndef EF_A_LP_BIBLIOTECA_EMPRESTIMO_H
#define EF_A_LP_BIBLIOTECA_EMPRESTIMO_H

#include "../livro/livro.h"
#include "../utilizador/utilizador.h"
#include <time.h>

// Estrutura para representar um empréstimo
typedef struct {
    int idEmprestimo;              // Identificador único do empréstimo
    int idLivro;                   // Identificador do livro emprestado
    int idUtilizador;              // Identificador do utilizador que tomou o livro emprestado
    time_t dataEmprestimo;         // Data do empréstimo
    time_t dataDevolucaoPrevista;  // Data prevista para devolução
    time_t dataDevolucaoReal;      // Data real da devolução (0 se ainda não devolvido)
} Emprestimo;

// Inicializa a lista de empréstimos
void inicializarEmprestimos();

// Registra um novo empréstimo
void registrarEmprestimo(Emprestimo novoEmprestimo);

// Finaliza um empréstimo indicando a devolução do livro
void finalizarEmprestimo(int idEmprestimo, time_t dataDevolucao);

// Renova um empréstimo, estendendo a data de devolução prevista
void renovarEmprestimo(int idEmprestimo, time_t novaDataDevolucaoPrevista);

// Busca empréstimos por ID de utilizador
Emprestimo *buscarEmprestimosPorUtilizador(int idUtilizador);

// Lista todos os empréstimos
void listarTodosOsEmprestimos();

#endif //EF_A_LP_BIBLIOTECA_EMPRESTIMO_H
