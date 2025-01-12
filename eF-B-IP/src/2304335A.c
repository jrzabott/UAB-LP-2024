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
    // Vamos em breve adicionar mais campos:
    //   idadeEmMinutos, ultimaRefeicao, etc.
} Abelha;

/************************************************************
 *  Protótipos das Funções
 ************************************************************/
void lerDadosEntrada(int *pNumAbelhas, int *pNumCelulas,
                     int *pMinutosPorTemp, int *pTemporadas);
Abelha* alocarColmeia(int n);

/************************************************************
 *  Implementação das Funções
 ************************************************************/

void lerDadosEntrada(int *pNumAbelhas, int *pNumCelulas,
                     int *pMinutosPorTemp, int *pTemporadas)
{
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
Abelha* alocarColmeia(int n)
{
    // Por quê? Precisamos de armazenar n abelhas
    // na heap, pois o número n depende da entrada.
    Abelha *vetor = (Abelha*) malloc(n * sizeof(Abelha));

    // Verificação simples: se malloc falhar, retorna NULL
    // Em contexto de VPL, dificilmente falha, mas é boa prática.
    if (vetor == NULL)
    {
        printf("Erro: nao foi possivel alocar memoria para abelhas.\n");
        return NULL;
    }

    // Inicializar cada abelha com um valor padrão,
    // evitando lixo de memória.
    for (int i = 0; i < n; i++)
    {
        vetor[i].tipo = FAXINEIRA;
        // Por enquanto, colocamos tudo como FAXINEIRA.
        // No Passo 3, faremos a distribuição real.
    }

    return vetor;
}

/************************************************************
 *  Função principal
 ************************************************************/
int main()
{
    int numAbelhas = 0;
    int numCelulas = 0;
    int minutosPorTemporada = 0;
    int numTemporadas = 0;

    // Ler os parâmetros de entrada
    lerDadosEntrada(&numAbelhas, &numCelulas,
                    &minutosPorTemporada, &numTemporadas);

    // Alocar dinamicamente o vetor de abelhas
    Abelha *colmeia = alocarColmeia(numAbelhas);

    if (colmeia == NULL)
    {
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
