#ifndef EF_A_LP_BIBLIOTECA_UTILIZADOR_H
#define EF_A_LP_BIBLIOTECA_UTILIZADOR_H

// Estrutura para representar um utilizador da biblioteca
typedef struct {
    int idUtilizador;       // Identificador único do utilizador
    char *nome;             // Nome do utilizador
    char *email;            // Email do utilizador
    int livrosEmprestados;  // Quantidade de livros atualmente emprestados pelo utilizador
} Utilizador;

// Variáveis para manter o controle de todos os utilizadores
extern Utilizador *listaUtilizadores;
extern int totalUtilizadores;

// Inicializa a lista de utilizadores
void inicializarUtilizadores();

// Adiciona um novo utilizador ao sistema
void adicionarUtilizador(Utilizador novoUtilizador);

// Remove um utilizador pelo ID
void removerUtilizador(int idUtilizador);

// Atualiza os dados de um utilizador existente
void atualizarUtilizador(Utilizador utilizadorAtualizado);

// Busca um utilizador pelo nome
Utilizador *buscarUtilizadorPorNome(const char *nome);

// Lista todos os utilizadores
void listarTodosOsUtilizadores();

#endif //EF_A_LP_BIBLIOTECA_UTILIZADOR_H