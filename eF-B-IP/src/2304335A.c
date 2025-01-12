/************************************************************
 *  Includes, Defines, Structs, Enums
 ************************************************************/
#include <stdio.h>   // printf, scanf
#include <stdlib.h>  // malloc, free

typedef enum {
    FAXINEIRA,
    NUTRIZ,
    CONSTRUTORA,
    GUARDIA,
    FORRAGEIRA,
    ZANGAO,
    RAINHA,
    OVO,
    LARVA,
    PUPA
} TipoAbelha;

typedef struct {
    TipoAbelha tipo;
    int idadeEmMinutos;    // ex.: -1440 => nasceu há 1 dia
    int ultimaRefeicao;    // ex.: -108 => alimentou-se há 108 min
} Abelha;

/************************************************************
 *  Protótipos das Funções
 ************************************************************/
void lerDadosEntrada(int *pNumAbelhas, int *pNumCelulas,
                     int *pMinutosPorTemp, int *pTemporadas);

Abelha *alocarColmeia(int n);

/************************************************************
 *  Implementação das Funções
 ************************************************************/

void lerDadosEntrada(int *pNumAbelhas, int *pNumCelulas,
                     int *pMinutosPorTemp, int *pTemporadas) {
    scanf("%d", pNumAbelhas);
    scanf("%d", pNumCelulas);
    scanf("%d", pMinutosPorTemp);
    scanf("%d", pTemporadas);
}

/*
 * Esta função aloca um array (vetor) de Abelha,
 * com dimensão n.
 * Devolve o ponteiro para a memória alocada.
 */
Abelha *alocarColmeia(int n) {
    // Por quê? Precisamos de armazenar n abelhas
    // na heap, pois o número n depende da entrada.
    Abelha *vetor = (Abelha *) malloc(n * sizeof(Abelha));

    // Verificação simples: se malloc falhar, retorna NULL
    // Em contexto de VPL, dificilmente falha, mas é boa prática.
    if (vetor == NULL) {
        printf("Erro: nao foi possivel alocar memoria para abelhas.\n");
        return NULL;
    }

    // Inicializar cada abelha com um valor padrão,
    // evitando lixo de memória.
    for (int i = 0; i < n; i++) {
        vetor[i].tipo = FAXINEIRA;
        // Por enquanto, colocamos tudo como FAXINEIRA.
        // No Passo 3, faremos a distribuição real.
    }

    return vetor;
}

/*
 * Esta função distribui as abelhas na colmeia.
 * A colmeia é um vetor de abelhas, com dimensão n.
 * A distribuição segue as regras do enunciado.
 * A rainha é a primeira abelha, seguida de 40 zangões.
 * As restantes abelhas são operárias, distribuídas
 * em 5 tipos: faxineira, nutriz, construtora, guardiã e forrageira.
 * A idade das abelhas varia de 1 a 40 dias.
 * A última refeição varia de 1 a 36 minutos.
 * A distribuição é feita de forma cíclica, em "round robin".
 * Por "round robin" entende-se que as abelhas operárias são
 * distribuídas de forma cíclica, em 5 tipos, repetindo-se. Para melhor ilustrar:
 * 0 => FAXINEIRA, 1 => NUTRIZ, 2 => CONSTRUTORA, 3 => GUARDIA, 4 => FORRAGEIRA
 * Exemplo: se tivermos 100 abelhas operárias, teremos 20 de cada tipo. Sendo assim,
 * as abelhas de índice 41 a 60 serão do tipo FAXINEIRA, as de 61 a 80 serão NUTRIZ, e assim por diante.
 *
 */
void distribuirAbelhas(Abelha *colmeia, int n) {
    // 1) Se não for possível ter 1 rainha + 40 zangões, "colmeia vazia".
    if (n < 41) {
        printf("Colmeia vazia (n < 41). Nenhuma abelha distribuida.\n");
        return;
    }

    // 2) Criar a rainha na posição 0
    colmeia[0].tipo = RAINHA;
    colmeia[0].idadeEmMinutos = 0;      // Rainha com idade 0 (acabou de "surgir")
    colmeia[0].ultimaRefeicao = 0;     // Alimentou-se no instante 0

    // 3) Criar 40 zangões nas posições 1..40
    //    Vamos distribuir as idades de 1 dia até 40 dias:
    for (int i = 1; i <= 40; i++) {
        colmeia[i].tipo = ZANGAO;

        int idadeDias = i;  // ex.: i=1 => 1 dia, i=40 => 40 dias
        colmeia[i].idadeEmMinutos = -(idadeDias * 1440);

        // Ultima refeicao = -( (K*1440)/40 )
        // Observando que se K=40, ultima refeicao = -( (40*1440)/40 ) => -1440
        // Se K=1, ultima refeicao = -(1440/40) => -36
        colmeia[i].ultimaRefeicao = -((idadeDias * 1440) / 40);
    }

    // 4) As restantes (n-41) abelhas são operárias:
    //    Precisamos distribuir em fax, nut, con, gua, for.
    int operarias = n - 41;
    int idx = 41;

    // Vamos usar um "round robin" simples para os tipos operários:
    // 0 => FAXINEIRA, 1 => NUTRIZ, 2 => CONSTRUTORA, 3 => GUARDIA, 4 => FORRAGEIRA
    // Precisaríamos também de idades, de 1 a 40 dias, repetindo se exceder 40.
    // Exemplo básico:
    for (int j = 0; j < operarias; j++) {
        // Definir o tipo cíclico
        int t = j % 5; // remainders 0..4
        switch (t) {
            case 0:
                colmeia[idx].tipo = FAXINEIRA;
                break;
            case 1:
                colmeia[idx].tipo = NUTRIZ;
                break;
            case 2:
                colmeia[idx].tipo = CONSTRUTORA;
                break;
            case 3:
                colmeia[idx].tipo = GUARDIA;
                break;
            case 4:
                colmeia[idx].tipo = FORRAGEIRA;
                break;
        }

        // Definir a idade (1..40 dias), repetindo se formos além de 40
        int idadeDias = (j % 40) + 1;  // se j=0 => 1, j=39 => 40, j=40 => 1 de novo
        colmeia[idx].idadeEmMinutos = -(idadeDias * 1440);

        // Definir ultimaRefeicao
        colmeia[idx].ultimaRefeicao = -((idadeDias * 1440) / 40);

        idx++;
    }
}

/************************************************************
 *  Função principal
 ************************************************************/
int main() {
    int numAbelhas = 0;
    int numCelulas = 0;
    int minutosPorTemporada = 0;
    int numTemporadas = 0;

    // Ler os parâmetros de entrada
    lerDadosEntrada(&numAbelhas, &numCelulas,
                    &minutosPorTemporada, &numTemporadas);

    // Alocar dinamicamente o vetor de abelhas
    Abelha *colmeia = alocarColmeia(numAbelhas);

    if (colmeia == NULL) {
        // Se a alocacao falhar, vamos abortar o programa.
        return 1;
    }

    // Por enquanto, só fazemos algo simples, como exibir
    // a quantidade total de abelhas alocadas e o tipo padrão
    printf("Alocadas %d abelhas. Todas inicialmente definidas como FAXINEIRA.\n",
           numAbelhas);

    // Liberar a memória antes de sair
    free(colmeia);

    return 0;
}
