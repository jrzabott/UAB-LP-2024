/************************************************************
 *  Includes, Defines, Structs, Enums
 ************************************************************/
#include <stdio.h>   // printf, scanf
#include <stdlib.h>  // malloc, free

// Opção: Usar enumeradores para tipos de abelhas.
// Observação: alguns nomes foram encurtados para evitar conflitos
// e facilitar a leitura, mas mantemos termos em português.
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

// Estrutura para representar uma abelha.
// Adicionaremos campos (ex.: nome, idade, última refeição, etc.) nos próximos passos.
typedef struct {
    TipoAbelha tipo;
    // Por enquanto, não definimos idade, ultimaRefeicao, etc.
    // Faremos isso num passo posterior.
} Abelha;

/************************************************************
 *  Protótipos das Funções
 ************************************************************/
void lerDadosEntrada(int *pNumAbelhas, int *pNumCelulas,
                     int *pMinutosPorTemp, int *pTemporadas);

/************************************************************
 *  Implementação das Funções
 ************************************************************/

// Ler os 4 inteiros de entrada, guardando nos endereços passados.
void lerDadosEntrada(int *pNumAbelhas, int *pNumCelulas,
                     int *pMinutosPorTemp, int *pTemporadas)
{
    // Por quê? Precisamos destas leituras para configurar o programa
    // e, nesta alínea A, utilizaremos principalmente "pNumAbelhas".
    scanf("%d", pNumAbelhas);
    scanf("%d", pNumCelulas);
    scanf("%d", pMinutosPorTemp);
    scanf("%d", pTemporadas);
}

/************************************************************
 *  Função principal
 ************************************************************/
int main()
{
    // Variáveis para a entrada
    int numAbelhas = 0;
    int numCelulas = 0;
    int minutosPorTemporada = 0;
    int numTemporadas = 0;

    // Ler dados de entrada
    lerDadosEntrada(&numAbelhas, &numCelulas,
                    &minutosPorTemporada, &numTemporadas);

    // Por enquanto, apenas exibimos para verificar se está ok
    printf("Lido: abelhas=%d, celulas=%d, minutosTemp=%d, temporadas=%d\n",
           numAbelhas, numCelulas, minutosPorTemporada, numTemporadas);

    // Encerramos, sem alocar memória ou criar abelhas ainda.
    return 0;
}
