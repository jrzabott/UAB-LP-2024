#ifndef EF_A_LP_BIBLIOTECA_LIVRO_H
#define EF_A_LP_BIBLIOTECA_LIVRO_H

// Estrutura para representar um livro
typedef struct {
    int idLivro;                 // Identificador único do livro
    char *titulo;                // Título do livro
    char *autor;                 // Autor do livro
    char *genero;                // Gênero do livro
    int exemplaresTotal;         // Total de exemplares do livro
    int exemplaresDisponiveis;   // Exemplares disponíveis para empréstimo
} Livro;

// Inicializa a lista de livros
void inicializarLivros();

// Adiciona um novo livro à lista
void adicionarLivro(Livro novoLivro);

// Remove um livro pelo ID
void removerLivro(int idLivro);

// Atualiza os dados de um livro existente
void atualizarLivro(Livro livroAtualizado);

// Busca um livro pelo título
Livro *buscarLivroPorTitulo(const char *titulo);

// Busca um livro pelo autor
Livro *buscarLivroPorAutor(const char *autor);

// Busca um livro pelo gênero
Livro *buscarLivroPorGenero(const char *genero);

// Lista todos os livros disponíveis
void listarLivrosDisponiveis();

// Lista todos os livros
void listarTodosOsLivros();

#endif //EF_A_LP_BIBLIOTECA_LIVRO_H
