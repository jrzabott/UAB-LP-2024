#include <stdio.h>
#include <stdlib.h>

#define DIAS_VIDA_OPERARIA 40

/*
 * =========================
 * Alínea A: Abelhas
 * =========================
 */
void calcularDistribuicaoOperarias(int N, int *resFax, int *resNut, int *resCon, int *resGua, int *resFor)
{
    *resFax = 0;
    *resNut = 0;
    *resCon = 0;
    *resGua = 0;
    *resFor = 0;

    if (N < 200) {
        // Colmeia vazia (nenhuma abelha operária)
        return;
    }

    int daily = N / DIAS_VIDA_OPERARIA;  // floor(N/40)

    for (int dia = 0; dia < DIAS_VIDA_OPERARIA; dia++)
    {
        for (int i = 0; i < daily; i++)
        {
            int tipo = i % 5;
            switch (tipo) {
                case 0: (*resFax)++;  break;
                case 1: (*resNut)++;  break;
                case 2: (*resCon)++;  break;
                case 3: (*resGua)++;  break;
                case 4: (*resFor)++;  break;
            }
        }
    }
}

void imprimirRelatorioAbelhas(int fax, int nut, int con, int gua, int forr, int zan, int rai)
{
    printf("Relatorio colmeia:\n");
    printf(" fax nut con gua for zan rai ovo lar pup mel pol nec cri zan rea\n");

    int total = fax + nut + con + gua + forr + zan + rai;
    if (total > 0) {
        printf("  %d  %d  %d  %d  %d  %d   %d\n",
               fax, nut, con, gua, forr, zan, rai);
    } else {
        // Colmeia vazia => linha em branco
        printf("\n");
    }
}

/*
 * =========================
 * Alínea B: Favos e Células
 * =========================
 */

typedef struct {
    int mel;
    int pol;
    int nec;
    int cri;
    int zan; // sempre 1 extra, fora do W
} FavoDistribuicao;

/*
 * Distribui 'numCelFavo' células em [mel, pol, nec, cri]
 * + 1 célula extra 'zan'.
 */
FavoDistribuicao distribuirFavo(int numCelFavo)
{
    FavoDistribuicao r;
    r.mel = 0;
    r.pol = 0;
    r.nec = 0;
    r.cri = 0;
    r.zan = 1;  // "uma célula é para zan, não descontando das restantes"

    for (int i = 0; i < numCelFavo; i++) {
        int tipo = i % 4;  // 0=mel, 1=pol, 2=nec, 3=cri
        switch (tipo) {
            case 0: r.mel++;  break;
            case 1: r.pol++;  break;
            case 2: r.nec++;  break;
            case 3: r.cri++;  break;
        }
    }

    return r;
}

/*
 * Imprime o favo no layout do enunciado.
 * Exemplo:
 *    Favo   0:            celulas vazias:             12   1
 *                                 usadas:  13  13  12
 */
void imprimirFavo(int indiceFavo, FavoDistribuicao dist)
{
    printf("    Favo   %d:            celulas vazias:             %d   %d\n",
           indiceFavo, dist.cri, dist.zan);
    printf("                                 usadas:  %d  %d  %d\n",
           dist.mel, dist.pol, dist.nec);
}

/*
 * Cria e imprime Z favos, onde Z = ceil(W/3000).
 * Cada favo => floor(W/Z) células em [mel, pol, nec, cri],
 * ignorando qualquer resto.
 */
void distribuirECriarFavos(int W)
{
    if (W <= 0) {
        // Nenhuma célula => não imprimir "Favo" no relatório
        return;
    }

    // Número de favos:
    int Z = (W + 2999) / 3000;  // ceil(W/3000)

    // Quantidade de células em cada favo:
    int baseSize = W / Z;       // floor(W/Z), resto ignorado

    for (int i = 0; i < Z; i++) {
        // Apenas baseSize, sem sobras
        FavoDistribuicao dist = distribuirFavo(baseSize);
        imprimirFavo(i, dist);
    }
}

/*
 * =========================
 * main: Alínea A + B
 * =========================
 */
int main()
{
    int N, nCelulas, minTemp, temporadas;
    scanf("%d %d %d %d", &N, &nCelulas, &minTemp, &temporadas);

    // Alínea A: abelhas
    int cntFax, cntNut, cntCon, cntGua, cntFor;
    calcularDistribuicaoOperarias(N, &cntFax, &cntNut, &cntCon, &cntGua, &cntFor);

    int cntZan = (N >= 200) ? 40 : 0;
    int cntRai = (N >= 200) ? 1 : 0;

    // Imprime contagem de abelhas
    imprimirRelatorioAbelhas(cntFax, cntNut, cntCon, cntGua, cntFor, cntZan, cntRai);

    // Alínea B: favos/células
    distribuirECriarFavos(nCelulas);

    return 0;
}
