#ifndef EF_A_LP_BIBLIOTECA_EMPRESTIMO_DAO_H
#define EF_A_LP_BIBLIOTECA_EMPRESTIMO_DAO_H

#include "emprestimo.h"

// Carrega a lista de empréstimos a partir de um arquivo CSV
void carregarEmprestimosDeCSV(const char *caminhoArquivo);

// Salva a lista atual de empréstimos em um arquivo CSV
void guardarEmprestimosEmCSV(const char *caminhoArquivo);

#endif //EF_A_LP_BIBLIOTECA_EMPRESTIMO_DAO_H
