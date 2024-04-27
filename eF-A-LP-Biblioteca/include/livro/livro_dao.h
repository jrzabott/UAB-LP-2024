#ifndef EF_A_LP_BIBLIOTECA_LIVRO_DAO_H
#define EF_A_LP_BIBLIOTECA_LIVRO_DAO_H

#include "livro.h"

// Carrega a lista de livros a partir de um arquivo CSV
void carregarLivrosDeCSV(const char *caminhoArquivo);

// Salva a lista atual de livros em um arquivo CSV
void guardarLivrosEmCSV(const char *caminhoArquivo);

#endif //EF_A_LP_BIBLIOTECA_LIVRO_DAO_H
