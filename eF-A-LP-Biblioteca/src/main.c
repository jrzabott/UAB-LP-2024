#include <stdio.h>
#include <stdlib.h>
#include "../include/livro/livro.h"
#include "../include/utilizador/utilizador.h"
#include "../include/emprestimo/emprestimo.h"
#include "../include/relatorio/relatorio.h"
#include "../include/livro/livro_dao.h"
#include "../include/utilizador/utilizador_dao.h"
#include "../include/emprestimo/emprestimo_dao.h"
#include <string.h>

#define LIVROS_CSV "livros.csv"
#define UTILIZADORES_CSV "utilizadores.csv"
#define EMPRESTIMOS_CSV "emprestimos.csv"

void carregarDados();
void salvarDados();
void menuPrincipal();
void menuLivros();
void menuUtilizadores();
void menuEmprestimos();
void menuRelatorios();

int main() {
    inicializarLivros();
    inicializarUtilizadores();
    inicializarEmprestimos();

    carregarDados();
    menuPrincipal();
    salvarDados();

    liberarGestaoEmprestimos();
    liberarMemoriaUtilizadores();
    liberarMemoriaLivros();
    return 0;
}

void carregarDados() {
    carregarLivrosDeCSV(LIVROS_CSV);
    carregarUtilizadoresDeCSV(UTILIZADORES_CSV);
    carregarEmprestimosDeCSV(EMPRESTIMOS_CSV);
}

void salvarDados() {
    guardarLivrosEmCSV(LIVROS_CSV);
    guardarUtilizadoresEmCSV(UTILIZADORES_CSV);
    guardarEmprestimosEmCSV(EMPRESTIMOS_CSV);
}

void menuPrincipal() {
    int opcao;
    do {
        printf("\nMenu Principal:\n");
        printf("1. Livros\n");
        printf("2. Utilizadores\n");
        printf("3. Empréstimos\n");
        printf("4. Relatórios\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                menuLivros();
                break;
            case 2:
                menuUtilizadores();
                break;
            case 3:
                menuEmprestimos();
                break;
            case 4:
                menuRelatorios();
                break;
            case 5:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opção inválida, tente novamente.\n");
        }
    } while (opcao != 5);
}

void adicionarLivroInterativo() {
    Livro novoLivro;

    novoLivro.idLivro = 0; // ID será atribuído automaticamente

    printf("Digite o título do livro: ");
    novoLivro.titulo = malloc(100 * sizeof(char));
    fgets(novoLivro.titulo, 100, stdin);
    novoLivro.titulo[strcspn(novoLivro.titulo, "\n")] = 0;  // Remove newline character

    printf("Digite o autor do livro: ");
    novoLivro.autor = malloc(100 * sizeof(char));
    fgets(novoLivro.autor, 100, stdin);
    novoLivro.autor[strcspn(novoLivro.autor, "\n")] = 0;

    printf("Digite o gênero do livro: ");
    novoLivro.genero = malloc(100 * sizeof(char));
    fgets(novoLivro.genero, 100, stdin);
    novoLivro.genero[strcspn(novoLivro.genero, "\n")] = 0;

    printf("Digite o total de exemplares: ");
    scanf("%d", &novoLivro.exemplaresTotal);
    getchar();

    novoLivro.exemplaresDisponiveis = novoLivro.exemplaresTotal;

    novoLivro.idLivro = adicionarLivro(novoLivro);

    // mensagem a confirmar adicao do livro
    printf("Livro adicionado com sucesso!\nID: %d\nTítulo: %s\nAutor: %s\nGênero: %s\nTotal de exemplares: %d\n", novoLivro.idLivro, novoLivro.titulo, novoLivro.autor, novoLivro.genero, novoLivro.exemplaresTotal);
}

void removerLivroInterativo() {
    int id;
    printf("Digite o ID do livro a ser removido: ");
    scanf("%d", &id);
    removerLivro(id);
}

void atualizarLivroInterativo() {
    int id;
    printf("Digite o ID do livro a atualizar: ");
    scanf("%d", &id);
    getchar();

    Livro livroAtualizado = *buscarLivroPorId(id);
    if (&livroAtualizado == NULL) {
        printf("Livro não encontrado!\n");
        return;
    }

    printf("Atualize o título do livro (%s): ", livroAtualizado.titulo);
    fgets(livroAtualizado.titulo, 100, stdin);
    livroAtualizado.titulo[strcspn(livroAtualizado.titulo, "\n")] = 0;

    printf("Atualize o autor do livro (%s): ", livroAtualizado.autor);
    fgets(livroAtualizado.autor, 100, stdin);
    livroAtualizado.autor[strcspn(livroAtualizado.autor, "\n")] = 0;

    printf("Atualize o gênero do livro (%s): ", livroAtualizado.genero);
    fgets(livroAtualizado.genero, 100, stdin);
    livroAtualizado.genero[strcspn(livroAtualizado.genero, "\n")] = 0;

    printf("Atualize o total de exemplares (%d): ", livroAtualizado.exemplaresTotal);
    scanf("%d", &livroAtualizado.exemplaresTotal);
    getchar();

    livroAtualizado.exemplaresDisponiveis = livroAtualizado.exemplaresTotal;

    atualizarLivro(livroAtualizado);
}

void menuLivros() {
    int opcao;
    do {
        printf("\nGestão de Livros:\n");
        printf("1. Adicionar Livro\n");
        printf("2. Remover Livro\n");
        printf("3. Atualizar Livro\n");
        printf("4. Listar Todos os Livros\n");
        printf("5. Listar Livros Disponíveis\n");
        printf("6. Voltar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();  // Consume newline left in the input buffer

        switch (opcao) {
            case 1:
                adicionarLivroInterativo();
                break;
            case 2:
                removerLivroInterativo();
                break;
            case 3:
                atualizarLivroInterativo();
                break;
            case 4:
                listarTodosOsLivros();
                break;
            case 5:
                listarLivrosDisponiveis();
                break;
            case 6:
                return;  // Retorna ao menu principal
            default:
                printf("Opção inválida, tente novamente.\n");
        }
    } while (opcao != 6);
}


void adicionarUtilizadorInterativo() {
    Utilizador novoUtilizador;
    novoUtilizador.idUtilizador = 0;  // ID será atribuído automaticamente

    printf("Digite o nome do utilizador: ");
    novoUtilizador.nome = malloc(100 * sizeof(char));
    fgets(novoUtilizador.nome, 100, stdin);
    novoUtilizador.nome[strcspn(novoUtilizador.nome, "\n")] = 0;

    printf("Digite o email do utilizador: ");
    novoUtilizador.email = malloc(100 * sizeof(char));
    fgets(novoUtilizador.email, 100, stdin);
    novoUtilizador.email[strcspn(novoUtilizador.email, "\n")] = 0;

    novoUtilizador.livrosEmprestados = 0;  // Inicializando com zero empréstimos

    adicionarUtilizador(novoUtilizador);
}

void removerUtilizadorInterativo() {
    int id;
    printf("Digite o ID do utilizador a ser removido: ");
    scanf("%d", &id);
    removerUtilizador(id);
}

void atualizarUtilizadorInterativo() {
    int id;
    printf("Digite o ID do utilizador a atualizar: ");
    scanf("%d", &id);
    getchar();

    Utilizador *utilizadorAtualizado = buscarUtilizadorPorId(id);
    if (utilizadorAtualizado == NULL) {
        printf("Utilizador não encontrado!\n");
        return;
    }

    printf("Atualize o nome do utilizador (%s): ", utilizadorAtualizado->nome);
    fgets(utilizadorAtualizado->nome, 100, stdin);
    utilizadorAtualizado->nome[strcspn(utilizadorAtualizado->nome, "\n")] = 0;

    printf("Atualize o email do utilizador (%s): ", utilizadorAtualizado->email);
    fgets(utilizadorAtualizado->email, 100, stdin);
    utilizadorAtualizado->email[strcspn(utilizadorAtualizado->email, "\n")] = 0;

    atualizarUtilizador(*utilizadorAtualizado);
}

void menuUtilizadores() {
    int opcao;
    do {
        printf("\nGestão de Utilizadores:\n");
        printf("1. Adicionar Utilizador\n");
        printf("2. Remover Utilizador\n");
        printf("3. Atualizar Utilizador\n");
        printf("4. Listar Todos os Utilizadores\n");
        printf("5. Voltar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();  // Limpar buffer de entrada para evitar problemas com entradas subsequentes.

        switch (opcao) {
            case 1:
                adicionarUtilizadorInterativo();
                break;
            case 2:
                removerUtilizadorInterativo();
                break;
            case 3:
                atualizarUtilizadorInterativo();
                break;
            case 4:
                listarTodosOsUtilizadores();
                break;
            case 5:
                return;  // Retorna ao menu principal
            default:
                printf("Opção inválida, tente novamente.\n");
        }
    } while (opcao != 5);
}

void registrarEmprestimoInterativo() {
    Emprestimo novoEmprestimo;
    int diasEmprestimo;

    printf("Digite o ID do livro: ");
    scanf("%d", &novoEmprestimo.idLivro);
    getchar();  // Limpa o buffer para evitar qualquer entrada pendente.

    printf("Digite o ID do utilizador: ");
    scanf("%d", &novoEmprestimo.idUtilizador);
    getchar();  // Limpa o buffer para evitar qualquer entrada pendente.

    printf("Digite o número de dias para o empréstimo: ");
    scanf("%d", &diasEmprestimo);
    getchar();  // Limpa o buffer para garantir que não há caracteres extras lidos.

    novoEmprestimo.dataEmprestimo = time(NULL);  // Data atual como data de início do empréstimo
    novoEmprestimo.dataDevolucaoPrevista = novoEmprestimo.dataEmprestimo + (diasEmprestimo * 86400); // Calcula a data de devolução prevista
    novoEmprestimo.dataDevolucaoReal = 0; // Ainda não devolvido

    // Adiciona o empréstimo ao sistema e verifica o resultado
    int idNovoEmprestimo = adicionarEmprestimo(novoEmprestimo);
    if (idNovoEmprestimo == -1) {
        printf("Falha ao registrar o empréstimo. Verifique os dados e tente novamente.\n");
    } else {
        printf("Empréstimo registrado com sucesso! Devolução prevista para %s.\n", ctime(&novoEmprestimo.dataDevolucaoPrevista));
    }

    // Obter emprestimo por ID e imprimir no console sumario do emprestimo
    Emprestimo *emprestimo = buscarEmprestimoPorId(idNovoEmprestimo);
    printf("ID: %d\nLivro: %s\nUtilizador: %s\nData de Empréstimo: %s\nData de Devolução Prevista: %s\nData de Devolução Real: %s\n",
           emprestimo->idEmprestimo, buscarLivroPorId(emprestimo->idLivro)->titulo, buscarUtilizadorPorId(emprestimo->idUtilizador)->nome,
           ctime(&emprestimo->dataEmprestimo), ctime(&emprestimo->dataDevolucaoPrevista), emprestimo->dataDevolucaoReal == 0 ? "" : ctime(&emprestimo->dataDevolucaoReal));
}

void renovarEmprestimoInterativo() {
    int idEmprestimo, diasAdicionais;
    printf("Digite o ID do empréstimo a ser renovado: ");
    scanf("%d", &idEmprestimo);
    getchar();

    printf("Digite o número de dias adicionais para o empréstimo: ");
    scanf("%d", &diasAdicionais);
    getchar();

    renovarEmprestimo(idEmprestimo, diasAdicionais);
    printf("Empréstimo renovado com sucesso para mais %d dias.\n", diasAdicionais);
}

void finalizarEmprestimoInterativo() {
    int idEmprestimo;
    printf("Digite o ID do empréstimo a ser finalizado (devolvido): ");
    scanf("%d", &idEmprestimo);
    getchar();

    finalizarEmprestimo(idEmprestimo);
    printf("Empréstimo finalizado com sucesso.\n");
}

void menuEmprestimos() {
    int opcao;
    do {
        printf("\nGestão de Empréstimos:\n");
        printf("1. Registrar Novo Empréstimo\n");
        printf("2. Renovar Empréstimo\n");
        printf("3. Finalizar Empréstimo\n");
        printf("4. Listar Todos os Empréstimos\n");
        printf("5. Listar Empréstimos Ativos\n");
        printf("6. Voltar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();  // Limpar o buffer de entrada para evitar problemas com entradas subsequentes.

        switch (opcao) {
            case 1:
                registrarEmprestimoInterativo();
                break;
            case 2:
                renovarEmprestimoInterativo();
                break;
            case 3:
                finalizarEmprestimoInterativo();
                break;
            case 4:
                listarTodosOsEmprestimos();
                break;
            case 5:
                listarEmprestimosActivos();
                break;
            case 6:
                return;  // Retorna ao menu principal
            default:
                printf("Opção inválida, tente novamente.\n");
        }
    } while (opcao != 6);
}


void menuRelatorios() {
    int opcao;
    do {
        printf("\nGestão de Relatórios:\n");
        printf("1. Relatório de Livros Mais Emprestados\n");
        printf("2. Relatório de Livros Não Devolvidos\n");
        printf("3. Relatório de Utilizadores com Mais Empréstimos\n");
        printf("4. Voltar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();  // Limpar o buffer de entrada para evitar problemas com entradas subsequentes.

        switch (opcao) {
            case 1:
                gerarRelatorioLivrosMaisEmprestados();
                break;
            case 2:
                gerarRelatorioLivrosNaoDevolvidos();
                break;
            case 3:
                gerarRelatorioUtilizadoresComMaisEmprestimos();
                break;
            case 4:
                return;  // Retorna ao menu principal
            default:
                printf("Opção inválida, tente novamente.\n");
        }
    } while (opcao != 4);
}


