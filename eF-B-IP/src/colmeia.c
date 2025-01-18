#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIAS_VIDA_OPERARIA 40
#define MINUTOS_POR_DIA 1440
#define DEBUG_MODE 0

/* Tipos de abelhas */
typedef enum {
    FAXINEIRA, NUTRIZ, CONSTRUTORA, GUARDIA, FORRAGEIRA, ZANGAO, RAINHA
} TipoAbelha;

/* Estrutura para representar uma abelha */
typedef struct {
    TipoAbelha tipo;
    int idade;
    int ultimaRefeicao;
} Abelha;

/* Tipos de células */
typedef enum {
    MEL, POLEN, NECTAR, CRIA, ZAN, REA
} TipoCelula;

/* Estrutura para representar uma célula */
typedef struct {
    TipoCelula tipo;
    int quantidade; // Quantidade em miligramas ou ocupação
} Celula;

/* Estrutura para representar um favo */
typedef struct {
    Celula *celulas;
    int totalCelulas;
} Favo;

/* Estrutura para representar a colmeia */
typedef struct {
    Abelha *abelhas;
    int totalAbelhas;

    Favo *favos;
    int totalFavos;
} Colmeia;

/* Função para log de depuração */
void debugLog(const char *message) {
    if (DEBUG_MODE) {
        fprintf(stderr, "[DEBUG] %s\n", message);
    }
}

/* Função para inicializar abelhas */
void inicializarAbelhas(Colmeia *colmeia, int totalAbelhas) {
    debugLog("Inicializando abelhas...");

    if (totalAbelhas <= 0) {
        debugLog("Nenhuma abelha para inicializar.");
        colmeia->abelhas = NULL;
        colmeia->totalAbelhas = 0;
        return;
    }

    colmeia->abelhas = (Abelha *)malloc(totalAbelhas * sizeof(Abelha));
    if (!colmeia->abelhas) {
        fprintf(stderr, "[ERROR] Falha ao alocar memória para abelhas.\n");
        exit(EXIT_FAILURE);
    }

    colmeia->totalAbelhas = 0;

    // Adicionar 40 zangões
    for (int i = 0; i < 40 && colmeia->totalAbelhas < totalAbelhas; i++) {
        colmeia->abelhas[colmeia->totalAbelhas++] = (Abelha){ZANGAO, i + 1, (i + 1) * MINUTOS_POR_DIA / DIAS_VIDA_OPERARIA};
    }

    // Adicionar 1 rainha
    if (colmeia->totalAbelhas < totalAbelhas) {
        colmeia->abelhas[colmeia->totalAbelhas++] = (Abelha){RAINHA, 0, 0};
    }

    // Adicionar operárias
    int operariasRestantes = totalAbelhas - colmeia->totalAbelhas;
    int daily = operariasRestantes / DIAS_VIDA_OPERARIA;
    int extra = operariasRestantes % DIAS_VIDA_OPERARIA;

    for (int dia = 0; dia < DIAS_VIDA_OPERARIA; dia++) {
        for (int i = 0; i < daily + (dia < extra ? 1 : 0) && colmeia->totalAbelhas < totalAbelhas; i++) {
            TipoAbelha tipo = (TipoAbelha)(i % 5); // Ciclo: FAXINEIRA -> NUTRIZ -> ...
            colmeia->abelhas[colmeia->totalAbelhas++] = (Abelha){tipo, dia + 1, (dia + 1) * MINUTOS_POR_DIA / DIAS_VIDA_OPERARIA};
        }
    }

    debugLog("Abelhas inicializadas.");
}

/* Função para inicializar favos e células */
void inicializarFavos(Colmeia *colmeia, int totalCelulas) {
    debugLog("Inicializando favos e células...");

    colmeia->totalFavos = (totalCelulas + 2999) / 3000; // ceil(totalCelulas / 3000)
    char debugMessage[200];
    sprintf(debugMessage, "Total de favos calculados: %d", colmeia->totalFavos);
    debugLog(debugMessage);

    colmeia->favos = (Favo *)malloc(colmeia->totalFavos * sizeof(Favo));
    if (!colmeia->favos) {
        fprintf(stderr, "[ERROR] Falha ao alocar memória para favos.\n");
        exit(EXIT_FAILURE);
    }

    int celulasPorFavo = totalCelulas / colmeia->totalFavos; // floor(totalCelulas / totalFavos)
    int restoCelulas = totalCelulas % colmeia->totalFavos; // Restante para distribuir

    sprintf(debugMessage, "Células por favo: %d, Resto de células: %d", celulasPorFavo, restoCelulas);
    debugLog(debugMessage);

    for (int f = 0; f < colmeia->totalFavos; f++) {
        int celulasNesteFavo = celulasPorFavo + (f < restoCelulas ? 1 : 0); // Distribuir restos

        if (celulasNesteFavo <= 0) {
            sprintf(debugMessage, "Favo %d possui número inválido de células: %d", f, celulasNesteFavo);
            debugLog(debugMessage);
            continue;
        }

        sprintf(debugMessage, "Favo %d - Células neste favo: %d", f, celulasNesteFavo);
        debugLog(debugMessage);

        Favo *favo = &colmeia->favos[f];
        favo->totalCelulas = celulasNesteFavo;
        favo->celulas = (Celula *)malloc(celulasNesteFavo * sizeof(Celula));
        if (!favo->celulas) {
            fprintf(stderr, "[ERROR] Falha ao alocar memória para células do favo %d.\n", f);
            exit(EXIT_FAILURE);
        }

        for (int c = 0; c < celulasNesteFavo; c++) {
            TipoCelula tipo = (TipoCelula)(c % 4); // Ciclo: MEL -> POLEN -> NECTAR -> CRIA
            favo->celulas[c] = (Celula){tipo, tipo == MEL ? 500 : tipo == POLEN ? 20 : tipo == NECTAR ? 40 : 0};
            sprintf(debugMessage, "Favo %d - Célula %d inicializada como tipo %d", f, c, tipo);
            debugLog(debugMessage);
        }

        // Adicionar célula ZAN
        if (celulasNesteFavo > 0) {
            favo->celulas[celulasNesteFavo - 1].tipo = ZAN;
            favo->celulas[celulasNesteFavo - 1].quantidade = 0;
            debugLog("Célula ZAN adicionada no final do favo.");
        }
    }

    debugLog("Favos e células inicializados.");
}

/* Função para liberar memória alocada */
void liberarColmeia(Colmeia *colmeia) {
    debugLog("Liberando memória...");

    free(colmeia->abelhas);

    for (int f = 0; f < colmeia->totalFavos; f++) {
        char debugMessage[100];
        sprintf(debugMessage, "Liberando memória do favo %d", f);
        debugLog(debugMessage);
        free(colmeia->favos[f].celulas);
    }

    free(colmeia->favos);

    debugLog("Memória liberada.");
}

/* Função para inicializar a colmeia */
void inicializarColmeia(Colmeia *colmeia, int totalAbelhas, int totalCelulas) {
    debugLog("Inicializando colmeia...");

    inicializarAbelhas(colmeia, totalAbelhas);
    inicializarFavos(colmeia, totalCelulas);

    debugLog("Colmeia inicializada.");
}

/* Função para imprimir relatório inicial */
void imprimirRelatorioInicial(Colmeia *colmeia) {
    int fax = 0, nut = 0, con = 0, gua = 0, forr = 0, zan = 0, rai = 0;

    for (int i = 0; i < colmeia->totalAbelhas; i++) {
        switch (colmeia->abelhas[i].tipo) {
            case FAXINEIRA: fax++; break;
            case NUTRIZ: nut++; break;
            case CONSTRUTORA: con++; break;
            case GUARDIA: gua++; break;
            case FORRAGEIRA: forr++; break;
            case ZANGAO: zan++; break;
            case RAINHA: rai++; break;
        }
    }

    printf("Relatorio colmeia:\n");
    printf(" fax nut con gua for zan rai ovo lar pup mel pol nec cri zan rea\n");
    printf("  %d  %d  %d  %d  %d  %d   %d\n", fax, nut, con, gua, forr, zan, rai);

    for (int f = 0; f < colmeia->totalFavos; f++) {
        Favo *favo = &colmeia->favos[f];
        int cri = 0, zan = 0, mel = 0, pol = 0, nec = 0;

        for (int c = 0; c < favo->totalCelulas; c++) {
            switch (favo->celulas[c].tipo) {
                case MEL: mel++; break;
                case POLEN: pol++; break;
                case NECTAR: nec++; break;
                case CRIA: cri++; break;
                case ZAN: zan++; break;
                default: break;
            }
        }

        printf("    Favo   %d:            celulas vazias:             %d   %d\n", f, cri, zan);
        printf("                                 usadas:  %d  %d  %d\n", mel, pol, nec);
    }
}

int main() {
    int N, nCelulas, minTemp, temporadas;
    scanf("%d %d %d %d", &N, &nCelulas, &minTemp, &temporadas);

    Colmeia colmeia;
    inicializarColmeia(&colmeia, N, nCelulas);
    imprimirRelatorioInicial(&colmeia);
    liberarColmeia(&colmeia);

    return 0;
}
