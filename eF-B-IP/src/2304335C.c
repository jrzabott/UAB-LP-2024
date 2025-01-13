#include <stdio.h>
#include <stdlib.h>

#define DIAS_VIDA_OPERARIA   40
#define MINUTOS_POR_DIA      1440
#define MG_POL_POR_REFEICAO  4
#define MG_MEL_POR_REFEICAO 10

/*
   NOTAS SOBRE A LÓGICA PEDIDA:
   ---------------------------------------
   - Cada minuto, **apenas uma** abelha (por tipo que precisa agir) é verificada.
   - Isto está explícito nas saídas de teste em que, no mesmo minuto,
     apenas **uma** abelha de um certo tipo morre ou é alimentada,
     mesmo que haja várias com a condição para morrer.
   - Em outras palavras, se duas abelhas do mesmo tipo atingem 40 dias
     simultaneamente, apenas **uma** morre naquele minuto (a "mais velha"
     ou alguma “prioridade”) e a outra morre no minuto seguinte.
   - A mesma ideia vale para a alimentação: somente uma abelha do mesmo tipo
     por minuto faz a refeição (se houver comida).
   - Isso explica por que nos relatórios vemos a contagem de um único tipo
     diminuir de 40 para 39 no primeiro minuto, depois de 39 para 38 no segundo,
     e assim por diante, em vez de cair várias de uma só vez.

   Para adequar-se ao **comportamento** visível nos testes,
   uma abordagem possível:
   ---------------------------------------
   1) Separar as abelhas em “categorias” (fax, nut, con, gua, for, zan, rai).
   2) A cada minuto, dentro de cada categoria (exceto rainha, que só morre de fome):
      - Encontrar a abelha mais “urgente” (mais velha ou mais tempo sem comer).
      - Verificar se ela morre de idade (>=40 dias) ou fome (sem alimento).
      - Caso contrário, tentar alimentá-la se estiver >=24h sem comer;
        se não tiver comida, ela morre.
   3) Assim, em **cada minuto**, **cada categoria** sofre no máximo **1** ação
      (morte por idade ou alimentação ou morte por falta de alimento).
   4) A rainha é uma categoria à parte: ou não morre de idade,
      mas sim se não houver alimento quando ela precisar comer.

   O código abaixo implementa essa lógica de modo simplificado,
   mas respeitando a "apenas uma abelha por tipo" a cada minuto.

   OBSERVAÇÃO:
   - Os testes do enunciado mostram que a rainha também pode morrer
     se passar 24h e não houver alimento.
   - As células de favos e sua distribuição (mel/pol) seguem a mesma
     ideia do "menor mg" no favo mais novo, mas iremos manter igual
     aos códigos anteriores, sem 'hardcode'.

   Esperamos que este comportamento se alinhe melhor aos exemplos.
*/

typedef enum {
    FAXINEIRA = 0,
    NUTRIZ,
    CONSTRUTORA,
    GUARDIA,
    FORRAGEIRA,
    ZANGAO,
    RAINHA
} TipoAbelha;

typedef struct {
    TipoAbelha tipo;
    int viva;
    int nascimento;
    int ultimaRefeicao;
} Abelha;

typedef struct {
    Abelha *vet;
    int total;
} ColmeiaAbelhas;

/* -----------------------------------------------------
   Funções Alínea A (Relatório Inicial)
   ----------------------------------------------------- */
void calcularDistribuicaoOperarias(int N,int *fax,int *nut,int *con,int *gua,int *forr)
{
    *fax=0; *nut=0; *con=0; *gua=0; *forr=0;
    if(N<200) return;
    int daily = N/40;
    for(int d=0; d<40; d++){
        for(int i=0; i<daily; i++){
            int t = i%5;
            if(t==0) (*fax)++;
            if(t==1) (*nut)++;
            if(t==2) (*con)++;
            if(t==3) (*gua)++;
            if(t==4) (*forr)++;
        }
    }
}

void imprimirRelatorioAbelhas(int fax,int nut,int con,int gua,int forr,int zan,int rai)
{
    printf("Relatorio colmeia:\n");
    printf(" fax nut con gua for zan rai ovo lar pup mel pol nec cri zan rea\n");
    int total= fax+nut+con+gua+forr+zan+rai;
    if(total>0){
        printf("  %d  %d  %d  %d  %d  %d   %d\n",
               fax,nut,con,gua,forr,zan,rai);
    } else {
        printf("\n");
    }
}

/* -----------------------------------------------------
   Criar Abelhas c/ idades (N≥200 => daily*(40) +40 +1)
   ----------------------------------------------------- */
ColmeiaAbelhas* criarColmeiaAbelhas(int N)
{
    ColmeiaAbelhas* c= (ColmeiaAbelhas*)malloc(sizeof(ColmeiaAbelhas));
    if(!c) return NULL;
    if(N<200){
        c->vet=NULL; c->total=0;
        return c;
    }
    int daily=N/40;
    int oper= daily*40;
    int zang= 40;
    int rain= 1;
    int tot= oper+ zang+ rain;
    c->vet=(Abelha*)malloc(sizeof(Abelha)*tot);
    c->total= tot;

    int idx=0;
    for(int d=0; d<40; d++){
        for(int i=0; i<daily; i++){
            Abelha* ab=&c->vet[idx];
            ab->viva=1;
            ab->tipo=(TipoAbelha)(i%5);
            int idadeDias=d+1;
            ab->nascimento= -(idadeDias*MINUTOS_POR_DIA);
            ab->ultimaRefeicao= -((idadeDias*MINUTOS_POR_DIA)/40);
            idx++;
        }
    }
    for(int z=1; z<=40; z++){
        Abelha* ab=&c->vet[idx];
        ab->viva=1;
        ab->tipo=ZANGAO;
        ab->nascimento= -(z*MINUTOS_POR_DIA);
        ab->ultimaRefeicao= -((z*MINUTOS_POR_DIA)/40);
        idx++;
    }
    Abelha* r=&c->vet[idx];
    r->viva=1;
    r->tipo=RAINHA;
    r->nascimento=0;
    r->ultimaRefeicao=0;
    return c;
}

/* -----------------------------------------------------
   Favos e Células (Alínea B) – Mesma Lógica
   ----------------------------------------------------- */
typedef enum {
    CEL_MEL=0, CEL_POL, CEL_NEC, CEL_CRI, CEL_ZAN, CEL_REA
} TipoCelula;

typedef struct {
    TipoCelula tipo;
    int mg;
} Celula;

typedef struct {
    Celula *cels;
    int qtd;
} Favo;

typedef struct {
    Favo *favos;
    int qtdFavos;
} ColmeiaFavos;

typedef struct {
    int mel, pol, nec, cri, zan;
} FavoDist;

static FavoDist distribuirFavoDist(int tam)
{
    FavoDist d;
    d.mel=0; d.pol=0; d.nec=0; d.cri=0; d.zan=1;
    for(int i=0;i<tam;i++){
        int t=i%4;
        if(t==0) d.mel++;
        if(t==1) d.pol++;
        if(t==2) d.nec++;
        if(t==3) d.cri++;
    }
    return d;
}

static Favo criarFavo(int tam)
{
    FavoDist dist= distribuirFavoDist(tam);
    int total= tam+1;
    Favo f;
    f.cels=(Celula*)malloc(sizeof(Celula)* total);
    f.qtd= total;

    int idx=0, ml=dist.mel, pl=dist.pol, nl=dist.nec, cl=dist.cri;
    for(int i=0; i<tam; i++){
        int t= i%4;
        if(t==0 && ml>0){
            f.cels[idx].tipo=CEL_MEL;
            f.cels[idx].mg=500;
            ml--;
        }
        else if(t==1 && pl>0){
            f.cels[idx].tipo=CEL_POL;
            f.cels[idx].mg=20;
            pl--;
        }
        else if(t==2 && nl>0){
            f.cels[idx].tipo=CEL_NEC;
            f.cels[idx].mg=40;
            nl--;
        }
        else {
            f.cels[idx].tipo=CEL_CRI;
            f.cels[idx].mg=0;
            cl--;
        }
        idx++;
    }
    f.cels[idx].tipo=CEL_ZAN;
    f.cels[idx].mg=0;
    return f;
}

ColmeiaFavos* criarColmeiaFavos(int W)
{
    ColmeiaFavos* cf=(ColmeiaFavos*)malloc(sizeof(ColmeiaFavos));
    if(!cf) return NULL;
    if(W<=0){
        cf->favos=NULL; cf->qtdFavos=0;
        return cf;
    }
    int Z= (W+2999)/3000;
    int base= W/Z;
    cf->favos=(Favo*)malloc(sizeof(Favo)*Z);
    cf->qtdFavos= Z;
    for(int i=0;i<Z;i++){
        cf->favos[i] = criarFavo(base);
    }
    return cf;
}

static void imprimirFavoDist(int idx,FavoDist d)
{
    printf("    Favo   %d:            celulas vazias:             %d   %d\n",
           idx,d.cri,d.zan);
    printf("                                 usadas:  %d  %d  %d\n",
           d.mel,d.pol,d.nec);
}

void imprimirFavosRelatorio(ColmeiaFavos* cf,int W)
{
    if(!cf||cf->qtdFavos<=0||W<=0) return;
    int Z=cf->qtdFavos;
    int base=W/Z;
    for(int i=0;i<Z;i++){
        FavoDist dist= distribuirFavoDist(base);
        imprimirFavoDist(i,dist);
    }
}

/* -----------------------------------------------------
   Buscar Célula p/ Alimentar (Alínea C)
   ----------------------------------------------------- */
typedef struct {
    int favoIdx;
    int celIdx;
    int mgVal;
} CelEncontrada;

CelEncontrada procurarCelula(ColmeiaFavos* cf, TipoCelula tip)
{
    CelEncontrada found;
    found.favoIdx=-1;
    found.celIdx=-1;
    found.mgVal=0;
    if(!cf||cf->qtdFavos<=0) return found;
    for(int f= cf->qtdFavos-1; f>=0; f--){
        Favo* fav= &cf->favos[f];
        int bestI=-1, bestVal=0;
        for(int c=fav->qtd-1;c>=0;c--){
            if(fav->cels[c].tipo==tip && fav->cels[c].mg>0){
                int val=fav->cels[c].mg;
                if(bestI<0){ bestI=c; bestVal=val; }
                else if(val<bestVal){ bestI=c; bestVal=val; }
            }
        }
        if(bestI>=0){
            found.favoIdx=f;
            found.celIdx=bestI;
            found.mgVal=bestVal;
            return found;
        }
    }
    return found;
}

static int alimentarAbelha(Abelha* ab,int tempo, ColmeiaFavos* cf)
{
    if(!ab||!cf) return 0;
    /* Procurar pol */
    CelEncontrada pol= procurarCelula(cf, CEL_POL);
    if(pol.favoIdx<0|| pol.mgVal< MG_POL_POR_REFEICAO){
        ab->viva=0;
        return 0;
    }
    /* Procurar mel */
    CelEncontrada mel= procurarCelula(cf, CEL_MEL);
    if(mel.favoIdx<0|| mel.mgVal< MG_MEL_POR_REFEICAO){
        ab->viva=0;
        return 0;
    }
    cf->favos[pol.favoIdx].cels[pol.celIdx].mg -= MG_POL_POR_REFEICAO;
    cf->favos[mel.favoIdx].cels[mel.celIdx].mg -= MG_MEL_POR_REFEICAO;
    ab->ultimaRefeicao=tempo;
    return 1;
}

/*
   Precisamos processar **apenas 1 abelha por tipo** a cada minuto.
   Passo:
    1) ordenar as abelhas vivas por tipo
    2) para cada tipo (exceto rainha separada?), achar a abelha “mais urgente”:
       se for morte por idade => morre,
       senão, se >=24h => tenta comer => se falha => morre
   3) para a rainha (1 abelha do tipo RAINHA) => se >=40 dias, ela **não** morre,
      mas se >=24h e sem comida => morre.
*/
static int cmpAb(const void* A, const void* B)
{
    const Abelha* a=(const Abelha*)A;
    const Abelha* b=(const Abelha*)B;
    /* 1) ordem por tipo (fax(0)->nut(1)->con(2)->gua(3)->for(4)->zan(5)->rai(6)) */
    if(a->tipo < b->tipo) return -1;
    if(a->tipo > b->tipo) return 1;
    /* 2) dentro do mesmo tipo => a “mais urgente” é a mais velha? */
    /*    => maior (tempoAtual - nascimento) =>
          equivalently => (nascimento) menor.
    */
    if(a->nascimento < b->nascimento) return -1;
    if(a->nascimento > b->nascimento) return 1;
    /* se empatar, pode usar ultimaRefeicao p/ priorizar fome, etc.
       mas d p/ testes, parece so a idade ja basta.
    */
    return 0;
}

void simularUmMinuto(ColmeiaAbelhas* col, ColmeiaFavos* cf, int tempo)
{
    if(!col||col->total<=0) return;
    /* filtrar abelhas vivas */
    int numVivas=0;
    for(int i=0;i<col->total;i++){
        if(col->vet[i].viva) numVivas++;
    }
    if(numVivas==0) return;

    /* criar array temporario c/ vivas => ordenar por (tipo, idade) */
    Abelha** tempArr= (Abelha**) malloc(sizeof(Abelha*)* numVivas);
    int idx=0;
    for(int i=0;i<col->total;i++){
        if(col->vet[i].viva) tempArr[idx++]= &col->vet[i];
    }
    /* converter p/ qsort-friendly? ou faz bubble? faremos um qsort manual */
    /* mas iremos só armazenar (tipo, nascimento, ultimaRef, *pointer). */
    /* para simplicidade, vamos criar um array de Abelha c/ pointer?
       Ou definimos struct local e copiamos. Faremos approach direct:
       qsort pointer array.
    */
    int compareAB(const void* A,const void* B){
        const Abelha* a=*(const Abelha**)A;
        const Abelha* b=*(const Abelha**)B;
        if(a->tipo < b->tipo) return -1;
        if(a->tipo > b->tipo) return 1;
        /* maior idade => menor nascimento. */
        if(a->nascimento < b->nascimento) return -1;
        if(a->nascimento > b->nascimento) return 1;
        return 0;
    }
    qsort(tempArr, numVivas, sizeof(Abelha*), compareAB);

    /* percorrer do menor i => grupos de mesmo tipo =>
       o primeiríssimo de cada tipo => faz “passo”
       (ou morre se >=40d, ou come se >=24h sem comer, etc.)
    */
    for(int i=0; i<numVivas;){
        Abelha* ab= tempArr[i];
        TipoAbelha tip= ab->tipo;
        /* processar 1 abelha desse tipo */
        if(tip==RAINHA){
            /* se >=24h e sem comida => morre, se >=40d => vive (n morre de velhice) */
            int idade= tempo - ab->nascimento;
            if((tempo - ab->ultimaRefeicao)>= MINUTOS_POR_DIA){
                int ok= alimentarAbelha(ab,tempo,cf);
                if(!ok){
                    /* ab->viva=0 ja setado se falhou */
                }
            }
        } else {
            /* checar >=40d => morre, senão se >=24h => tenta comer */
            int idade= tempo - ab->nascimento;
            if(idade>= DIAS_VIDA_OPERARIA*MINUTOS_POR_DIA){
                ab->viva=0;
            } else {
                if((tempo - ab->ultimaRefeicao)>= MINUTOS_POR_DIA){
                    int ok= alimentarAbelha(ab,tempo,cf);
                    if(!ok){
                        /* ab->viva=0 se falhou */
                    }
                }
            }
        }

        /* pular as abelhas do mesmo tipo => i++ ate mudar de tipo */
        TipoAbelha currT= tip;
        i++;
        while(i<numVivas){
            if(tempArr[i]->tipo==currT) i++;
            else break;
        }
    }

    free(tempArr);
}

void contarAbelhasVivas(ColmeiaAbelhas* col,
                        int*fax,int*nut,int*con,int*gua,int*forr,int*zan,int*rai)
{
    *fax=0;*nut=0;*con=0;*gua=0;*forr=0;*zan=0;*rai=0;
    for(int i=0;i<col->total;i++){
        if(!col->vet[i].viva) continue;
        switch(col->vet[i].tipo){
            case FAXINEIRA:   (*fax)++;  break;
            case NUTRIZ:      (*nut)++;  break;
            case CONSTRUTORA: (*con)++;  break;
            case GUARDIA:     (*gua)++;  break;
            case FORRAGEIRA:  (*forr)++; break;
            case ZANGAO:      (*zan)++;  break;
            case RAINHA:      (*rai)++;  break;
        }
    }
}

void imprimirTempo(int minutos)
{
    if(minutos<=0) return;
    int dd= minutos/ MINUTOS_POR_DIA;
    int rr= minutos% MINUTOS_POR_DIA;
    int hh= rr/60;
    int mm= rr%60;
    printf("Relatorio colmeia:");
    int wrote=0;
    if(dd>0){
        printf(" %d dia(s)", dd);
        wrote=1;
    }
    if(hh>0){
        if(wrote) printf(" ");
        printf("%d hora(s)", hh);
        wrote=1;
    }
    if(mm>0){
        if(wrote) printf(" ");
        printf("%d minuto(s)", mm);
    }
    printf("\n");
}

/*
   Lógica de relatórios:
   - Precisamos 1 relatório no t=0
   - Precisamos +abs(temporadas) relatórios em intervalos minTemp
     => total (abs(temporadas)+1) relatórios
   - em cada minuto chamamos simularUmMinuto =>
     "apenas 1 abelha por tipo" sofre efeito
   - se colmeia vazia => imprimir e sair
*/
void simular(ColmeiaAbelhas* col, ColmeiaFavos* cf,
             int N,int W,int minTemp,int temporadas)
{
    int absT= (temporadas<0)? -temporadas: temporadas;
    int f,n,c,g,fo,z,r;
    contarAbelhasVivas(col,&f,&n,&c,&g,&fo,&z,&r);

    /* relatório t=0 */
    imprimirRelatorioAbelhas(f,n,c,g,fo,z,r);
    imprimirFavosRelatorio(cf,W);

    int tot= f+n+c+g+fo+z+r;
    if(tot==0) return;
    if(absT==0) return;

    int relatCount=1;
    int tempo=0;
    /* geraremos relatórios ate relatCount=absT */
    while(relatCount<=absT){
        tempo++;
        /* simulamos 1min => so 1 abelha por tipo */
        simularUmMinuto(col,cf,tempo);

        contarAbelhasVivas(col,&f,&n,&c,&g,&fo,&z,&r);
        if((f+n+c+g+fo+z+r)==0){
            /* colmeia vazia => relatorio final */
            imprimirTempo(tempo);
            imprimirRelatorioAbelhas(f,n,c,g,fo,z,r);
            imprimirFavosRelatorio(cf,W);
            return;
        }
        if((tempo % minTemp)==0){
            imprimirTempo(tempo);
            imprimirRelatorioAbelhas(f,n,c,g,fo,z,r);
            imprimirFavosRelatorio(cf,W);
            relatCount++;
            if(relatCount>absT) break;
        }
    }
}

int main()
{
    int N,W,minTemp,temps;
    scanf("%d%d%d%d",&N,&W,&minTemp,&temps);

    /* Alínea A p/ relatório */
    int fax,nut,con,gua,forr;
    calcularDistribuicaoOperarias(N,&fax,&nut,&con,&gua,&forr);
    int zan=(N>=200)?40:0;
    int rai=(N>=200)?1:0;

    /* Criar abelhas e favos p/ a simulação */
    ColmeiaAbelhas* col= criarColmeiaAbelhas(N);
    ColmeiaFavos*   cFav= criarColmeiaFavos(W);

    /* rodar simulação */
    simular(col,cFav,N,W,(minTemp<=0?1:minTemp),temps);

    /* liberar */
    if(col){
        if(col->vet) free(col->vet);
        free(col);
    }
    if(cFav){
        if(cFav->favos){
            for(int i=0;i<cFav->qtdFavos;i++){
                if(cFav->favos[i].cels) free(cFav->favos[i].cels);
            }
            free(cFav->favos);
        }
        free(cFav);
    }
    return 0;
}
