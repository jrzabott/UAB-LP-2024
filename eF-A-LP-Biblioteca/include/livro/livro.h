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

extern Livro *livros;  // Array dinâmico de livros
extern int totalLivros;  // Contador de livros

// Inicializa a lista de livros
void inicializarLivros();

// Adiciona um novo livro à lista
int adicionarLivro(Livro novoLivro);

// Remove um livro pelo ID
void removerLivro(int idLivro);

// Atualiza os dados de um livro existente
void atualizarLivro(Livro livroAtualizado);

// Busca livros pelo título
Livro** buscarLivrosPorTitulo(const char *titulo, int *count);

// Busca livros pelo autor
Livro** buscarLivrosPorAutor(const char *autor, int *count);

// Busca livros pelo gênero
Livro** buscarLivrosPorGenero(const char *genero, int *count);

// Busca livros pelo id
Livro* buscarLivroPorId(int idLivro);

// Lista todos os livros disponíveis
void listarLivrosDisponiveis();

// Lista todos os livros emprestados
void listarLivrosEmprestados();

// Lista todos os livros
void listarTodosOsLivros();

// Libera a memória alocada para os livros
void liberarMemoriaLivros();

#endif //EF_A_LP_BIBLIOTECA_LIVRO_H
