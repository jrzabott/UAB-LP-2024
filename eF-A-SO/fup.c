/*
** UC: 21111 - Sistemas Operativos
** e-flio A 2023-24 (fdup.c)
** Aluno: 2304335 - Daniel Junior
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>

// Função para verificar a existência do diretório e a validade dos argumentos passados ao programa.
// Garante que o número correto de argumentos seja fornecido e que o diretório exista.
void checkArguments(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Erro: Utilização incorreta. Forma correta: %s <diretório> <padrão do ficheiro>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    struct stat statbuf;
    // Verifica se o diretório existe e se é realmente um diretório.
    if (stat(argv[1], &statbuf) != 0 || !S_ISDIR(statbuf.st_mode)) {
        fprintf(stderr, "Erro: O diretório '%s' é inválido ou não existe.\n", argv[1]);
        exit(EXIT_FAILURE);
    }
}

// Executa um comando específico, manipulando entrada e saída conforme necessário.
// Cria um processo filho para executar o comando e aguarda a sua conclusão.
void executeCommand(char* command[], const char* outputFile) {
    pid_t pid = fork();

    if (pid == 0) { // Processo filho
        if (outputFile != NULL) {
            // Redireciona a saída padrão para o arquivo especificado.
            if (freopen(outputFile, "w", stdout) == NULL) {
                fprintf(stderr, "Erro ao redirecionar a saída para o arquivo %s\n", outputFile);
                exit(EXIT_FAILURE);
            }
        }
        execvp(command[0], command);
        // Caso execvp retorne, indica que ocorreu um erro na execução do comando.
        fprintf(stderr, "Erro ao executar o comando %s\n", command[0]);
        exit(EXIT_FAILURE);
    } else if (pid > 0) { // Processo pai
        int status;
        wait(&status); // Espera pela conclusão do processo filho.
        if (status) {
            fprintf(stderr, "Erro: O comando %s falhou na execução.\n", command[0]);
        }
    } else {
        // Caso a criação do processo filho falhe.
        fprintf(stderr, "Erro ao criar um novo processo com fork().\n");
        exit(EXIT_FAILURE);
    }
}

// Funo para a execuo do comando find.
void findFiles(char* directory, char* pattern) {
    char* command[] = {"find", directory, "-type", "f", "-name", pattern, "-printf", "%h %f\n", NULL};
    executeCommand(command, "tmp1.txt");
}

// Funo para a execuo do comando sort.
void sortFiles() {
    char* command[] = {"sort", "-t", " ", "-k2,2", "tmp1.txt", NULL};
    executeCommand(command, "tmp2.txt");
}

// Funo para a execuo do comando uniq.
void uniqFiles() {
    char* command[] = {"uniq", "-f1", "-D", "tmp2.txt", NULL};
    executeCommand(command, "tmp3.txt");
}

// Funo para a execuo do comando awk.
void formatOutput() {
    char* command[] = {"awk", "{print $2,$1}", "tmp3.txt", NULL};
    executeCommand(command, NULL); // A sada ser direcionada para a sada padro.
}

int main(int argc, char* argv[]) {
    checkArguments(argc, argv);

    findFiles(argv[1], argv[2]);
    sortFiles();
    uniqFiles();
    formatOutput();

    return 0;
}