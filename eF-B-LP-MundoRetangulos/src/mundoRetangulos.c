#include <stdlib.h>
#include <stdio.h>
#include "mundoRetangulos.h"

Retangulo retangulos[MAX_RETANGULOS];
int contadorRetangulos = 0;

Retangulo* criarRetangulo(int x, int y, int largura, int altura) {
    if (x < 1 || y < 1 || x + largura > MAX_X || y + altura > MAX_Y) {
        printf("Fora dos limites: x=[1,%d], y=[1,%d]\n", MAX_X, MAX_Y);
        return NULL; // Fora dos limites
    }

    Retangulo novoRetangulo;
    novoRetangulo.x = x;
    novoRetangulo.y = y;
    novoRetangulo.largura = largura;
    novoRetangulo.altura = altura;

    // Verificar se ha intersecao com outros retangulos
    for (int i = 0; i < contadorRetangulos; i++) {
        if (interseta(&novoRetangulo, &retangulos[i])) {
            printf("Erro: Retangulo (%d,%d,%d,%d) intersecciona com retangulo (%d,%d,%d,%d)\n",
                   x, y, largura, altura, retangulos[i].x, retangulos[i].y, retangulos[i].largura, retangulos[i].altura);
            return NULL; // Intersecao com outro retangulo
        }
    }

    // Adicionar novo retangulo ao array e incrementar contador antes de retornar
    retangulos[contadorRetangulos++] = novoRetangulo;

    // aplicar gravidade
    aplicarGravidade(&retangulos[contadorRetangulos - 1]);

    return &retangulos[contadorRetangulos - 1];
}

// verificar se dois retangulos se intersectam
// deve permitir que dois retangulos toquem seus lados, nao sobrepor, mas tocar.
int interseta(Retangulo* r1, Retangulo* r2) {
    if (r1->x + r1->largura <= r2->x || r1->x >= r2->x + r2->largura
        || r1->y + r1->altura <= r2->y || r1->y >= r2->y + r2->altura) {
        return 0;
    }
    return 1;
}

void aplicarGravidade(Retangulo* retangulo) {
    // verificar em todos os retangulos existentes, a maior altura ocupada (afinal, nosso novo retangulo ha de cair
    // em maxY.
    int maxY = 1;
    for (int i = 0; i < contadorRetangulos; i++) {
        // se o retangulo que estamos a testar for o mesmo que estamos a tentar aplicar a gravidade, passar para o proximo.
        if (retangulo == &retangulos[i])
            continue;

        if (retangulo->x + retangulo->largura > retangulos[i].x
            && retangulo->x < retangulos[i].x + retangulos[i].largura) {
            if (retangulos[i].y + retangulos[i].altura > maxY) {
                maxY = retangulos[i].y + retangulos[i].altura;
            }
        }
    }

    // descer para maximo Y desocupado
    retangulo->y = maxY;
}

// metodo imprimir cenario serve para escrever no ecrã o estado actual do mundo dos retangulos.
// os retangulos sao representados em seus limites por letras X, e seu interior e preenchido com letras O
// espacos vazios sao representados por hifen "-"
// y=0, deve ficar embaixo, e y=MAX_Y deve ficar em cima
// devemos tambem imprimir uma linha vertical com os valores de 1
// e duas linhas abaixo do output para representar o eixo X
// a primeira linha representa as unidades com caracateres de 0123456789
// a segunda linha representa as dezenas, com espacos vazios entre os numeros das dezenas
// exemplo:
// Linha unidades: 12345678901234567890
// Linha dezednas: 0        1        2
void imprimirCenario() {
    char cenario[MAX_Y + 1][MAX_X + 1];
    for (int i = 0; i < MAX_Y + 1; i++) {
        for (int j = 0; j < MAX_X + 1; j++) {
            cenario[i][j] = '-';
        }
    }

    // desenhar retangulos
    // Big O notation: O(n^3) - pessimo. Mas para o nosso caso, n é pequeno, entao nao ha problema.
    for (int i = 0; i < contadorRetangulos; i++) {
        // desenhar linha vertical
        for (int j = retangulos[i].y; j < retangulos[i].y + retangulos[i].altura; j++) {
            // desenhar linha horizontal
            for (int k = retangulos[i].x; k < retangulos[i].x + retangulos[i].largura; k++) {
                // se estamos na linha vertical ou horizontal, desenhar X
                if (j == retangulos[i].y || j == retangulos[i].y + retangulos[i].altura - 1
                    || k == retangulos[i].x || k == retangulos[i].x + retangulos[i].largura - 1) {
                    cenario[j][k] = 'X';
                } else { // senao, desenhar O para o interior do retangulo
                    cenario[j][k] = 'O';
                }
            }
        }
    }

    // imprimir cenario, porem adicionar a numeracao do eixo Y nas duas primeiras posicoes de cada linha e um
    // espaco imediatamente depois.
    // adicionar tambem uma linha extra para termos o numero 25 no eixo Y
    for (int i = MAX_Y; i >= 0; i--) {
        printf("%2d ", i);
        for (int j = 0; j < MAX_X + 1; j++) {
            printf("%c", cenario[i][j]);
        }
        printf("\n");
    }

    //imprimir linha das unidades do eixo X
    // imprime tambem uma coluna extra para fazer com que a numeracao do eixo-X va ate o numero 80.
    printf("   "); // 3 espacos para alinhar com a linha das dezenas
    for (int i = 0; i < MAX_X + 1; i++) {
        printf("%d", i % 10);
    }
    printf("\n");

    //imprimir linha das dezenas do eixo X
    printf("   "); // 3 espacos para alinhar com a linha das unidades
    for (int i = 0; i < MAX_X + 1; i++) {
        if (i % 10 == 0) {
            printf("%d", i / 10);
        } else {
            printf(" ");
        }
    }
    printf("\n");
}

// mover um retangulo para a direita:
// deve pesquisar no array de retangulo o retangulo que se encontra nas coordenadas x e y informadas
// verificar se ao mover para direita nao havera intersectacao com outro retangulo
// caso nao haja, mover o retangulo para a direita, e em seguida tentamos aplicar a gravidade
// deve retornar 1 se o movimento foi bem sucedido, e 0 caso contrario
// caso nao seja possivel mover para direita, exibir mensagem de erro, antes de retornar 0
int moverDireita(int x, int y, int p) {
    for (int i = 0; i < contadorRetangulos; i++) {
        if (retangulos[i].x == x && retangulos[i].y == y) {
            // verificar se ha intersecao com outros retangulos
            retangulos[i].x += p;
            for (int j = 0; j < contadorRetangulos; j++) {
                if (i != j && interseta(&retangulos[i], &retangulos[j])) {
                    printf("Erro: Retangulo (%d,%d,%d,%d) intersecciona com retangulo (%d,%d,%d,%d)\n",
                           retangulos[i].x, retangulos[i].y, retangulos[i].largura, retangulos[i].altura,
                           retangulos[j].x, retangulos[j].y, retangulos[j].largura, retangulos[j].altura);
                    retangulos[i].x -= p;
                    return 0;
                }
            }

            // aplicar gravidade
            aplicarGravidade(&retangulos[i]);
            return 1;
        }
    }
    return 0;
}

// mover um retangulo para a esquerda:
// deve pesquisar no array de retangulo o retangulo que se encontra nas coordenadas x e y informadas
// verificar se ao mover para esquerda nao havera intersectacao com outro retangulo
// caso nao haja, mover o retangulo para a esquerda, e em seguida tentamos aplicar a gravidade
// deve retornar 1 se o movimento foi bem sucedido, e 0 caso contrario
// caso nao seja possivel mover para esquerda, exibir mensagem de erro, antes de retornar 0
int moverEsquerda(int x, int y, int p) {
    for (int i = 0; i < contadorRetangulos; i++) {
        if (retangulos[i].x == x && retangulos[i].y == y) {
            // verificar se ha intersecao com outros retangulos
            retangulos[i].x -= p;
            for (int j = 0; j < contadorRetangulos; j++) {
                if (i != j && interseta(&retangulos[i], &retangulos[j])) {
                    printf("Erro: Retangulo (%d,%d,%d,%d) intersecciona com retangulo (%d,%d,%d,%d)\n",
                           retangulos[i].x, retangulos[i].y, retangulos[i].largura, retangulos[i].altura,
                           retangulos[j].x, retangulos[j].y, retangulos[j].largura, retangulos[j].altura);
                    retangulos[i].x += p;
                    return 0;
                }
            }

            // aplicar gravidade
            aplicarGravidade(&retangulos[i]);
            return 1;
        }
    }
    return 0;
}

void inicializarRetangulos() {
    contadorRetangulos = 0;
    // Limpar array de retangulos
    for (int i = 0; i < MAX_RETANGULOS; i++) {
        retangulos[i].x = 0;
        retangulos[i].y = 0;
        retangulos[i].largura = 0;
        retangulos[i].altura = 0;
    }
}

void limparRetangulos() {
    for (int i = 0; i < MAX_RETANGULOS; i++) {
        retangulos[i].x = 0;
        retangulos[i].y = 0;
        retangulos[i].largura = 0;
        retangulos[i].altura = 0;
    }
    contadorRetangulos = 0;
}