/*
** UC: 21111 - Sistemas Operativos
** e-fólio B 2023-24 (mtxor.c)
**
** Aluno: 2304335 - Daniel Junior
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Estrutura de buffer circular - FIFO - para comunicação de dados entre tasks produtoras e consumidoras.
// O buffer é um array de inteiros, com dimensão dimbuf, que armazena os itens produzidos pelas tasks produtoras.
typedef struct {
    int *buffer;                // Array de inteiros
    int dimbuf;                 // Dimensão do buffer
    int count;                  // Contador de itens no buffer
    int in;                     // usado quando uma task produtora insere um item no buffer, para que o mesmo seja armazenado na posição correta.
    int out;                    // usado quando uma task consumidora remove um item do buffer, para que o item seja retirado da posição correta.
    pthread_mutex_t mtx_buf;    // representa o mutex (exclusão mútua) para proteger o acesso concorrente ao buffer
} bufferGlobal;

// Estrutura que representa o resultado de uma tarefa consumidora.
// O resultado de uma tarefa é o resultado do XOR dos itens processados e o número de operações realizadas.
typedef struct {
    int resultadoXor;     // Resultado do XOR
    int contadorOperacoes; // Contador de operações realizadas
} resultadoTarefa;

static const int DEFAULT_SEED = 737; // Semente para geração de números aleatórios como definida no enunciado.
bufferGlobal buf; // Variável global que representa o buffer, que contempla a estrutura de dados.
int totalItensAProcessar; // Total de itens que devem ser processados

// Função que insere um item no buffer. Recebe como argumentos o buffer e o item a ser inserido.
void inserir(bufferGlobal *buf, int item) {
    buf->buffer[buf->in] = item;
    buf->in = (buf->in + 1) % buf->dimbuf;
    buf->count++;

    // debug output com todos os dados da inserção para verificar item inserido no buffer
    // printf("Inserido item %d no buffer, count=%d, in=%d, out=%d\n", item, buf->count, buf->in, buf->out);
}

// Função que remove um item do buffer. Recebe como argumento o buffer. Retorna o item removido.
int remover(bufferGlobal *buf) {
    int item = buf->buffer[buf->out];
    buf->out = (buf->out + 1) % buf->dimbuf;
    buf->count--;
    return item;
}

// Função que representa a tarefa consumidora. Recebe como argumento um ponteiro para um inteiro que representa o número da tarefa.
void* tarefaConsumidora(void *arg) {
    int num = *(int*)arg; // tricky code: cast do argumento para int pointer e depois dereferencing (para obter o valor do argumento)
    resultadoTarefa *resultado = malloc(sizeof(resultadoTarefa));
    resultado->resultadoXor = 0;
    resultado->contadorOperacoes = 0;

    // Loop infinito para processar os itens do buffer
    // O loop é interrompido somente quando todos os itens foram processados
    // O número de itens a serem processados por cada tarefa é calculado de forma a dividir os itens de forma mais justa possível
    while (1) {
        pthread_mutex_lock(&buf.mtx_buf);
        if (buf.count > 0) {
            int itensParaConsumo = (buf.count + num) / (num + 1); // Divisão mais justa dos itens
            for (int i = 0; i < itensParaConsumo; i++) {
                if (buf.count == 0) break;
                int item = remover(&buf);
                resultado->resultadoXor ^= item;
                resultado->contadorOperacoes++;
            }
            pthread_mutex_unlock(&buf.mtx_buf);
        } else if (totalItensAProcessar <= 0) {
            pthread_mutex_unlock(&buf.mtx_buf);
            break; // Saia do loop se todos os itens tiverem sido processados
        } else {
            pthread_mutex_unlock(&buf.mtx_buf);
        }
    }
    printf("T%d: %d operações realizadas\n", num, resultado->contadorOperacoes);
    pthread_exit((void*)resultado); // Retornar o resultado da tarefa
}

// Função para inicializar o buffer. Recebe como argumento a dimensão do buffer.
void inicializarBuffer(int dimbuf) {
    buf.buffer = (int*)malloc(dimbuf * sizeof(int));
    buf.dimbuf = dimbuf;
    buf.count = 0;
    buf.in = 0;
    buf.out = 0;
    pthread_mutex_init(&buf.mtx_buf, NULL);
}

// Função para limpar o buffer e destruir o mutex.
void limparBuffer() {
    free(buf.buffer);
    pthread_mutex_destroy(&buf.mtx_buf);
}

// Função para validar os argumentos de entrada do programa. Recebe os argumentos da linha de comando e ponteiros para as variáveis de dimensão do buffer, número de itens e número de tarefas. Retorna 1 se os argumentos são válidos, caso contrário retorna 0.
int validarArgumentos(int argc, char *argv[], int *dimbuf, int *N, int *nt) {
    if (argc != 4) {
        fprintf(stderr, "Uso: %s dimbuf N nt\nOnde:\n"
                        "\tdimbuf\t- representa o tamanho de buffer a ser utilizado;\n"
                        "\tN\t\t- representa o número de itens da sequência aleatória;\n"
                        "\tnt\t\t- o número de tarefas/threads consumidoras.\n", argv[0]);
        return 0;
    }

    // Uso aqui atoi pois os argumentos são inteiros, em seguida verifico que todos os valores são positivos, ou seja, maiores que 0.
    *dimbuf = atoi(argv[1]);
    *N = atoi(argv[2]);
    *nt = atoi(argv[3]);

    if (*dimbuf <= 0 || *N <= 0 || *nt <= 0) {
        fprintf(stderr, "Valores de argumentos inválidos\n");
        return 0;
    }

    return 1;
}

int main(int argc, char *argv[]) {
    int dimbuf, N, nt;
    if (!validarArgumentos(argc, argv, &dimbuf, &N, &nt)) {
        exit(EXIT_FAILURE);
    }

    printf("Cálculo XOR de sequência com %d itens, %d tarefas e buffer %d itens\n", N, nt, dimbuf);

    inicializarBuffer(dimbuf);
    totalItensAProcessar = N;

    srand(DEFAULT_SEED); // Inicializar a semente para geração de números aleatórios

    // Notamos aqui que teremos de realizar a insercao de items em 2 momentos distintos:
    // antes e depois de criar as tarefas consumidoras.
    // Isto porque o buffer é partilhado entre as tarefas produtoras e consumidoras. E sua capacidade pode ser
    // insuficiente para armazenar todos os itens produzidos de uma só vez.
    //
    // Exemplo: no caso de um buffer com tamanho 2 e com 4 itens e 4 tarefas:
    //     > Neste caso, teremos de inserir 2 itens antes de criar as tarefas e os restantes 2 itens depois de criar
    //     > as tarefas consumidoras. Temos recursos que bastem, mas o buffer não é suficiente para armazenar todos os
    //     > itens de uma so vez.
    //     > TODO: monitorizar e informar o utilizador sobre o numero de operacoes relacionadas somente ao buffer.
    for (int i = 0; i < dimbuf && totalItensAProcessar > 0; i++, totalItensAProcessar--) {
        int item = rand();
        inserir(&buf, item); // BUFFER_INSERT1:: primeiro momento de insercao de items.
    }

    pthread_t consumidores[nt];
    int ids[nt];
    resultadoTarefa *resultados[nt];
    for (int i = 0; i < nt; i++) {
        ids[i] = i;
        pthread_create(&consumidores[i], NULL, tarefaConsumidora, &ids[i]);
    }

    // Loop para inserir os itens restantes no buffer, após a criação das tarefas consumidoras.
    while (totalItensAProcessar > 0) {
        pthread_mutex_lock(&buf.mtx_buf);
        if (buf.count == buf.dimbuf) { // Se o buffer estiver cheio, aguarde
            pthread_mutex_unlock(&buf.mtx_buf);
            sched_yield();
        } else { // Se o buffer não estiver cheio, insira um item e atualize o total de itens a processar
            int item = rand();
            inserir(&buf, item); // BUFFER_INSERT2:: segundo momento de insercao de items.
            totalItensAProcessar--;
            pthread_mutex_unlock(&buf.mtx_buf);
        }
    }

    int contadorOperacoes = 0;
    int resultadoFinalXor = 0;
    for (int i = 0; i < nt; i++) { // Aguardar a conclusão de todas as tarefas consumidoras, obter os resultados e liberar a memória alocada para um dado resultado ja visto.
        pthread_join(consumidores[i], (void**)&resultados[i]);
        contadorOperacoes += resultados[i]->contadorOperacoes;
        resultadoFinalXor ^= resultados[i]->resultadoXor;
        free(resultados[i]);
    }

    // Output dos resultados
    printf("Total de operações efetuadas: %d\n", contadorOperacoes);
    printf("Resultado final do XOR: %d\n", resultadoFinalXor);

    limparBuffer();

    return 0;
}
