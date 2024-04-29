#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/utilizador/utilizador.h"
#include "../include/utilizador/utilizador_dao.h"

void exibirMenu() {
    printf("\nGestão de Utilizadores:\n");
    printf("1. Listar todos os utilizadores\n");
    printf("2. Adicionar um novo utilizador\n");
    printf("3. Remover um utilizador\n");
    printf("4. Carregar utilizadores de um arquivo CSV\n");
    printf("5. Salvar utilizadores em um arquivo CSV\n");
    printf("0. Sair\n");
    printf("Escolha uma opção: ");
}

int main() {
    int opcao;
    inicializarUtilizadores();

    do {
        exibirMenu();
        scanf("%d", &opcao);
        getchar(); // Limpar buffer do teclado após ler um número

        switch (opcao) {
            case 1:
                listarTodosOsUtilizadores();
                break;
            case 2: {
                Utilizador u;
                printf("Digite o ID do utilizador: ");
                scanf("%d", &u.idUtilizador);
                getchar();

                printf("Digite o nome do utilizador: ");
                u.nome = malloc(256);
                fgets(u.nome, 255, stdin);
                u.nome[strcspn(u.nome, "\n")] = 0; // Remove newline

                printf("Digite o email do utilizador: ");
                u.email = malloc(256);
                fgets(u.email, 255, stdin);
                u.email[strcspn(u.email, "\n")] = 0;

                printf("Digite o número de livros emprestados: ");
                scanf("%d", &u.livrosEmprestados);
                getchar();

                adicionarUtilizador(u);
                break;
            }
            case 3: {
                int id;
                printf("Digite o ID do utilizador que deseja remover: ");
                scanf("%d", &id);
                removerUtilizador(id);
                break;
            }
            case 4: {
                char arquivo[256];
                printf("Digite o nome do arquivo CSV para carregar os utilizadores: ");
                fgets(arquivo, 255, stdin);
                arquivo[strcspn(arquivo, "\n")] = 0; // Remove newline
                carregarUtilizadoresDeCSV(arquivo);
                break;
            }
            case 5: {
                char arquivo[256];
                printf("Digite o nome do arquivo CSV para salvar os utilizadores: ");
                fgets(arquivo, 255, stdin);
                arquivo[strcspn(arquivo, "\n")] = 0;
                guardarUtilizadoresEmCSV(arquivo);
                break;
            }
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}

// TODO - livro.c - adicionar livro deveria verificar se livro ja existe por titulo e incrementar total de exemplares

// TODO - livro.c - atualizar livro nao valida dados de entrada, do ponto de vista logico.

// TODO - *_dao.c - deve de haver uma abstracao tal que a leitura e escrita de CSV existam a parte.
//                  devemos ainda tornar o CSV configuravel a partir de um ficheiro com os cabecalhos na ordem correta.
//                  o mesmo para o tamanho maximo de linha suportado