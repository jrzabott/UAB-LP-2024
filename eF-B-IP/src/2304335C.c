#include <stdio.h>
#include <stdlib.h>

#define DEBUG_MODE 0

#define DIAS_VIDA_OPERARIA 40
#define MINUTOS_POR_DIA 1440
#define MAX_CELULAS_POR_FAVO 3000
#define TOTAL_ZANGOES 40
#define TOTAL_RAINHAS 1
#define TOTAL_REALEZA (TOTAL_ZANGOES + TOTAL_RAINHAS)

/* Tipos de abelhas */
typedef enum {
    FAXINEIRA, NUTRIZ, CONSTRUTORA, GUARDIA, FORRAGEIRA, ZANGAO, RAINHA, DESCONHECIDO
} TipoAbelha;

/* Estrutura para representar uma abelha */
typedef struct {
    TipoAbelha tipo;
    int idade;
    int ultimaRefeicao;
    int viva;
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

TipoAbelha tipoAbelhaPorNumero(int i) {
    switch (i % 7) {
        case 0: return FAXINEIRA;
        case 1: return NUTRIZ;
        case 2: return CONSTRUTORA;
        case 3: return GUARDIA;
        case 4: return FORRAGEIRA;
        case 5: return ZANGAO;
        case 6: return RAINHA;
        default: return DESCONHECIDO;
    }
}

char *nomeTipoAbelhaPorNumero(int i) {
    switch (i) {
        case FAXINEIRA: return "FAXINEIRA";
        case NUTRIZ: return "NUTRIZ";
        case CONSTRUTORA: return "CONSTRUTORA";
        case GUARDIA: return "GUARDIA";
        case FORRAGEIRA: return "FORRAGEIRA";
        case ZANGAO: return "ZANGAO";
        case RAINHA: return "RAINHA";
        default: return "DESCONHECIDO";
    }
}

void incializarAbelhas(Colmeia *colmeia, int totalAbelhas) {
    debugLog("Inicializando abelhas...");
    colmeia->abelhas = (Abelha *) malloc((totalAbelhas + TOTAL_ZANGOES + TOTAL_RAINHAS) * sizeof(Abelha));
    if (!colmeia->abelhas) {
        fprintf(stderr, "[ERROR] Falha ao alocar memória para abelhas.\n");
        exit(EXIT_FAILURE);
    }
    colmeia->totalAbelhas = totalAbelhas;

    if (DEBUG_MODE) {
        char message[100];
        sprintf(message, "Total de abelhas: %d (sem contar a realesza). Total Abelhas com Realeza: %d", totalAbelhas,
                (totalAbelhas + TOTAL_REALEZA));
        debugLog(message);
    }

    for (int i = 0; i < totalAbelhas; i++) {
        colmeia->abelhas[i] = (Abelha){tipoAbelhaPorNumero(i % 5), 0, 0, 1}; // Inicialmente vivas e idade zero
    }

    // inicializa as abelhas da realeza 40 ZAN
    for (int i = 0; i < 40; i++) {
        colmeia->abelhas[totalAbelhas + i] = (Abelha){ZANGAO, 0, 0, 1};
    }
    // 1 rainha
    colmeia->abelhas[totalAbelhas + TOTAL_ZANGOES] = (Abelha){RAINHA, 0, 0, 1};

    if (DEBUG_MODE) {
        int abelhasTipoCounter[7] = {0, 0, 0, 0, 0, 0, 0};
        for (int i = 0; i < totalAbelhas; i++) {
            abelhasTipoCounter[colmeia->abelhas[i].tipo]++;
        }
        for (int i = 0; i < 7; i++) {
            printf("Tipo %s: %d\n", nomeTipoAbelhaPorNumero(i), abelhasTipoCounter[i]);
        }
    }
}

void inicializarFavos(Colmeia *colmeia, int totalCelulas) {
    debugLog("Inicializando favos...");

    // Calcula o número de favos necessários
    colmeia->totalFavos = (totalCelulas + MAX_CELULAS_POR_FAVO - 1) / MAX_CELULAS_POR_FAVO;

    colmeia->favos = (Favo *) malloc(colmeia->totalFavos * sizeof(Favo));
    if (!colmeia->favos) {
        fprintf(stderr, "[ERROR] Falha ao alocar memória para favos.\n");
        exit(EXIT_FAILURE);
    }

    // Calcula o número de células (excluindo ZAN) para distribuir uniformemente
    int celulasPorFavoBase = totalCelulas / colmeia->totalFavos;
    int celulasExtras = totalCelulas % colmeia->totalFavos;

    for (int i = 0; i < colmeia->totalFavos; i++) {
        int numCelulas = celulasPorFavoBase + (i < celulasExtras ? 1 : 0); // Não inclui ZAN
        colmeia->favos[i].totalCelulas = numCelulas; // Soma apenas as células reais
        colmeia->favos[i].celulas = (Celula *) malloc((numCelulas + 1) * sizeof(Celula)); // +1 para ZAN
        if (!colmeia->favos[i].celulas) {
            fprintf(stderr, "[ERROR] Falha ao alocar memória para células do favo %d.\n", i);
            exit(EXIT_FAILURE);
        }
    }

    if (DEBUG_MODE) {
        char message[100];
        sprintf(message, "Total de favos: %d", colmeia->totalFavos);
        debugLog(message);
        sprintf(message, "Células por favo (sem contar ZAN): %d", celulasPorFavoBase);
        debugLog(message);
        sprintf(message, "Células extras: %d", celulasExtras);
        debugLog(message);
    }
}


void inicializarCelulas(Colmeia *colmeia) {
    debugLog("Inicializando células...");

    TipoCelula ordemCelulas[] = {MEL, POLEN, NECTAR, CRIA};
    int tiposUsaveis = sizeof(ordemCelulas) / sizeof(ordemCelulas[0]);

    for (int i = 0; i < colmeia->totalFavos; i++) {
        Favo *favo = &colmeia->favos[i];
        int totalCelulas = favo->totalCelulas;

        for (int j = 0; j < totalCelulas + 1; j++) {
            // +1 para incluir ZAN sem interferir no total real
            if (j == totalCelulas) {
                // Ultima  célula do favo é sempre ZAN
                favo->celulas[j] = (Celula){ZAN, 1};
                continue;
            }
            // Distribui os outros tipos de células
            TipoCelula tipo = ordemCelulas[(j) % tiposUsaveis];
            int quantidade = 0;

            if (tipo == MEL) quantidade = 500;
            if (tipo == POLEN) quantidade = 20;
            if (tipo == NECTAR) quantidade = 40;
            if (tipo == CRIA) quantidade = 0;
            favo->celulas[j] = (Celula){tipo, quantidade};
        }
    }
    // mensagem detalhada com a distribuicao de cada tipo de celula em cada 1 dos favo via debugLog
    if (DEBUG_MODE) {
        for (int i = 0; i < colmeia->totalFavos + 1; i++) {
            char message[100];
            sprintf(message, "Favo %d:", i);
            debugLog(message);
            int mel, polen, nectar, cria, zan;
            mel = polen = nectar = cria = zan = 0;
            for (int j = 0; j < colmeia->favos[i].totalCelulas + 1; j++) {
                // nao esquecer do +1 para incluir ZAN (pq, meu Deus???)
                Celula *celula = &colmeia->favos[i].celulas[j];
                switch (celula->tipo) {
                    case MEL: mel++;
                        break;
                    case POLEN: polen++;
                        break;
                    case NECTAR: nectar++;
                        break;
                    case CRIA: cria++;
                        break;
                    case ZAN: zan++;
                    default: break;
                }
            }
            sprintf(message, "MEL=%d, POLEN=%d, NECTAR=%d, CRIA=%d, ZAN=%d", mel, polen, nectar, cria, zan);
            debugLog(message);
        }
    }
    debugLog("Todas as células inicializadas corretamente.");
}

/* Inicializa a colmeia */
void inicializarColmeia(Colmeia *colmeia, int totalAbelhas, int totalCelulas) {
    debugLog("Inicializando colmeia...");

    incializarAbelhas(colmeia, totalAbelhas);
    inicializarFavos(colmeia, totalCelulas);
    inicializarCelulas(colmeia);

    debugLog("Colmeia inicializada.");
}

/* Gera relatórios detalhados */
void gerarRelatorio(Colmeia *colmeia, int instanteAtual) {
    int dias = instanteAtual / (60 * 24);
    int horas = (instanteAtual % (60 * 24)) / 60;
    int minutos = instanteAtual % 60;

    if (instanteAtual == 0) {
        printf("Relatorio colmeia:\n");
    } else {
        printf("Relatorio colmeia: ");
        if (dias > 0) {
            printf("%d dia(s) ", dias);
        }
        if (horas > 0 || dias > 0) { // Inclui horas se houver dias ou horas > 0
            printf("%d hora(s) ", horas);
        }
        if (minutos > 0 || (dias == 0 && horas == 0)) { // Sempre inclui minutos se for o único valor significativo
            printf("%d minuto(s)", minutos);
        }
        printf("\n");
    }

    printf(" fax nut con gua for zan rai ovo lar pup mel pol nec cri zan rea\n");

    int fax = 0, nut = 0, con = 0, gua = 0, forr = 0, zan = 0, rai = 0;

    for (int i = 0; i < colmeia->totalAbelhas; i++) {
        if (colmeia->abelhas[i].viva) {
            switch (colmeia->abelhas[i].tipo) {
                case FAXINEIRA: fax++;
                    break;
                case NUTRIZ: nut++;
                    break;
                case CONSTRUTORA: con++;
                    break;
                case GUARDIA: gua++;
                    break;
                case FORRAGEIRA: forr++;
                    break;
                case ZANGAO: zan++;
                    break;
                case RAINHA: rai++;
                    break;
            }
        }
    }

    printf("  %d  %d  %d  %d  %d  %d   %d\n",
           fax, nut, con, gua, forr, zan, rai);

    for (int f = 0; f < colmeia->totalFavos; f++) {
        int mel = 0, polen = 0, nectar = 0, cri = 0;

        for (int c = 0; c < colmeia->favos[f].totalCelulas; c++) {
            switch (colmeia->favos[f].celulas[c].tipo) {
                case MEL: mel++;
                    break;
                case POLEN: polen++;
                    break;
                case NECTAR: nectar++;
                    break;
                case CRIA: cri++;
                    break;
                default: break;
            }
        }

        printf("    Favo   %d:            celulas vazias:              %d   1\n",
               f, cri);
        printf("                                 usadas:  %d  %d  %d\n",
               mel, polen, nectar);
    }
}

/* Alimenta as abelhas e processa envelhecimento */
void processarCiclo(Colmeia *colmeia, int instanteAtual) {
    for (int i = 0; i < colmeia->totalAbelhas; i++) {
        Abelha *abelha = &colmeia->abelhas[i];
        if (!abelha->viva) continue;

        // Envelhecimento
        abelha->idade++;
        if (abelha->idade > DIAS_VIDA_OPERARIA) {
            abelha->viva = 0;
            continue;
        }

        // Alimentação
        if (instanteAtual - abelha->ultimaRefeicao >= MINUTOS_POR_DIA) {
            int alimentada = 0;
            for (int f = 0; f < colmeia->totalFavos && !alimentada; f++) {
                for (int c = 0; c < colmeia->favos[f].totalCelulas; c++) {
                    if (colmeia->favos[f].celulas[c].tipo == MEL && colmeia->favos[f].celulas[c].quantidade >= 10) {
                        colmeia->favos[f].celulas[c].quantidade -= 10;
                        abelha->ultimaRefeicao = instanteAtual;
                        alimentada = 1;
                        break;
                    }
                }
            }

            if (!alimentada) {
                abelha->viva = 0; // Morre de fome
            }
        }
    }
}

/* Simula a colmeia */
void simularColmeia(Colmeia *colmeia, int minutosPorTemporada, int numeroTemporadas) {
    int instanteAtual = 0;

    gerarRelatorio(colmeia, instanteAtual);
    while (numeroTemporadas--) {
        for (int i = 0; i < minutosPorTemporada; i++) {
            instanteAtual++;
            processarCiclo(colmeia, instanteAtual);
        }
        gerarRelatorio(colmeia, instanteAtual);
    }
}

/* Libera memória da colmeia */
void liberarColmeia(Colmeia *colmeia) {
    free(colmeia->abelhas);
    for (int i = 0; i < colmeia->totalFavos; i++) {
        free(colmeia->favos[i].celulas);
    }
    free(colmeia->favos);
}

int main() {
    debugLog("Inicio da execução");
    debugLog("Leitura de dados");

    /*
      *    totalAbelhasOperarias: número total de abelhas operárias na colmeia. Lembrando que o prof acredita que 41 abelhas da realeza nao devem ser contabilizadas aqui (???)
     *    celulas: número total de células na colmeia - celula é um espaço onde as abelhas armazenam mel, pólen, néctar, cria, zangões ou rainha
     *    minutosPorTemporada: número de minutos por temporada - uma temporada é um período de tempo em que as abelhas trabalham
     *    numeroTemporadas: número de temporadas - quantidade de temporadas que a colmeia deve simular, ou ainda, numero de relatorios a imprimir além do relatorio inicial. Deus sabe lá porquê o número informado é negativo.
     */
    int totalAbelhasOperarias, celulas, minutosPorTemporada, numeroTemporadas;
    scanf("%d%d%d%d", &totalAbelhasOperarias, &celulas, &minutosPorTemporada, &numeroTemporadas);

    if (numeroTemporadas < 0) {
        numeroTemporadas = numeroTemporadas * -1;
    }

    Colmeia colmeia;
    inicializarColmeia(&colmeia, totalAbelhasOperarias, celulas);
    simularColmeia(&colmeia, minutosPorTemporada, numeroTemporadas);
    liberarColmeia(&colmeia);
    return 0;
}
