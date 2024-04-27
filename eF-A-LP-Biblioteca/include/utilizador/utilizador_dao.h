#ifndef EF_A_LP_BIBLIOTECA_UTILIZADOR_DAO_H
#define EF_A_LP_BIBLIOTECA_UTILIZADOR_DAO_H

#include "utilizador.h"

// Carrega a lista de utilizadores a partir de um arquivo CSV
void carregarUtilizadoresDeCSV(const char *caminhoArquivo);

// Salva a lista atual de utilizadores em um arquivo CSV
void guardarUtilizadoresEmCSV(const char *caminhoArquivo);

#endif //EF_A_LP_BIBLIOTECA_UTILIZADOR_DAO_H
