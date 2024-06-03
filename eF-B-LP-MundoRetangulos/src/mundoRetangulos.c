#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mundoRetangulos.h"

Retangulo *retangulos;
int contadorRetangulos = 0;

// Este metodo faz 3 coisas:
// 1. Cria um novo retangulo
// 2. Realoca o array de retangulos para acomodar o novo retangulo e incrementa o contador de retangulos
// 3. Aplica Gravidade no novo retangulo, para que este esteja salvo na posição correta
// retorna -1 se nao for possivel criar o retangulo, do contrario, retorna o index do retangulo no array de retangulos
int criarRetangulo(int x, int y, int largura, int altura) {
    // Verificar validade dos parametros. Retornar NULL se invalidos.
    // 1. X e Y devem ser positivos e dentro dos limites
    if (x < 0 || y < 0 || x >= MAX_X || y >= MAX_Y) {
        return -1;
    }
    // 2. Largura e Altura devem ser positivos e dentro dos limites
    if (largura <= 0 || altura <= 0 || largura > MAX_X || altura > MAX_Y) {
        return -1;
    }
    // 3. A soma de X e Largura deve ser menor que MAX_X
    if (x + largura > MAX_X) {
        return -1;
    }
    // 4. A soma de Y e Altura deve ser menor que MAX_Y
    if (y + altura > MAX_Y) {
        return -1;
    }

    // Criar um novo retângulo
    Retangulo novoRetangulo = {x, y, largura, altura};

    // Verificar se existe interseção com outros retângulos antes de aplicar gravidade e salvar no array.
    // Se houver interseção, devemos imprimir uma mensagem de erro e retornar -1.
    // A mensagem de erro sera delegada ao metodo interseta.
    if (interseta(&novoRetangulo)) {
        // mensagem de interseção contendo informacoes sobre o retangulo que causou a interseção, e o retangulo interseptado
        printf("Interseção com retângulo em (%d, %d) com largura %d e altura %d\n",
               novoRetangulo.x, novoRetangulo.y,novoRetangulo.largura, novoRetangulo.altura);
        return -1;
    }

    // Aplicar Gravidade antes de adicionar o novo retangulo.
    novoRetangulo = aplicarGravidade(novoRetangulo);

    // Realocar o array de retângulos para acomodar o novo retângulo
    retangulos = realloc(retangulos, sizeof(Retangulo) * (contadorRetangulos + 1));
    if (retangulos == NULL) {
        printf("Erro ao alocar memória para o novo retângulo\n");
        return -1;
    }

    // exibe a informar que o retangulo foi criado com sucesso, a posicao atual, e o numero de retangulos existentes
    printf("Retângulo criado com sucesso em (%d, %d) com largura %d e altura %d\n", novoRetangulo.x, novoRetangulo.y, novoRetangulo.largura, novoRetangulo.altura);

    // Adicionar o novo retângulo ao array de retângulos
    retangulos[contadorRetangulos] = novoRetangulo;

    // Retornar a referência para o novo retângulo, no array de retângulos e incrementar o contador de retângulos
    return contadorRetangulos++;
}

// Este metodo recebe um retangulo, e aplica a gravidade. Retorna um novo retangulo com a gravidade aplicada.
Retangulo aplicarGravidade(Retangulo retangulo) {
    // como este metodo deve retornar um novo retangulo, vamos criar um novo retangulo
    Retangulo novoRetangulo = {retangulo.x, retangulo.y, retangulo.largura, retangulo.altura};

    // se o retangulo estiver no chão, não aplicar gravidade
    if (novoRetangulo.y == 0)
        return novoRetangulo;

    // A aplicacao da gravidade deve ser feita de forma que:
    // 1. O retangulo deve ser movido para baixo, até que esteja no chao ou sobre outro retangulo.
    // 2. Se o retangulo estiver sobre outro retangulo, ele deve parar de cair.
    for (int i = novoRetangulo.y - 1; i >= 0; i--) {
        novoRetangulo.y = i;
        if (interseta(&novoRetangulo)) {
            novoRetangulo.y++;
            break;
        }
    }
    // exibe a informar se houve alguma alteracao de posicao do retangulo
    if (novoRetangulo.y != retangulo.y) {
        printf("Gravidade Aplicada. Retângulo movido de (%d, %d) para (%d, %d)\n", retangulo.x, retangulo.y, novoRetangulo.x, novoRetangulo.y);
    }
    return novoRetangulo;
}



// Este metodo ira inicializar o array de retangulos
void inicializarRetangulos() {
    retangulos = malloc(sizeof(Retangulo)); // Alocar memória para o array de retângulos
    contadorRetangulos = 0;
}

// Este metodo ira limpar o array de retangulos
void limparRetangulos() {
    free(retangulos); // Liberar a memória alocada para o array de retângulos
    contadorRetangulos = 0;
}

int interseta(Retangulo *retangulo) {
    // Aqui iremos verificar, se o retangulo informado, intersepta com algum outro retangulo no array de retangulos.
    // Se houver interseção, devemos retornar 1, caso contrário, retornar 0.
    for (int i = 0; i < contadorRetangulos; ++i) {
        if (checarSobreposicao(retangulo, &retangulos[i]) > 0)
            return 1;
    }
    return 0; // Não houve interseção com nenhum dos retangulos existentes
}

// os retangulos devem ter o perimetro represetados por X
// os retangulos devem ter o interior representado por O
// os espacos vazios serao representados por .
// devemos imprimir uma matriz de 80x25
// devemos imprimir tambem eixo-x e eixo-y (opcional)
void imprimirCenario(Retangulo *retangulos, int numRetangulos) {
    // preparar a matriz de 80x25
    char matriz[MAX_Y][MAX_X];
    for (int i = 0; i < MAX_Y; i++) {
        for (int j = 0; j < MAX_X; j++) {
            matriz[i][j] = '.';
        }
    }
    // se retangulos for NULL, algo esta errado. Imprimir mensagem de erro e retornar
    if (retangulos == NULL) {
        printf("Erro ao imprimir cenário\n");
        return;
    }

    // preencher a matriz com os retangulos
    for (int i = 0; i < numRetangulos; i++) {
        for (int j = retangulos[i].y; j < retangulos[i].y + retangulos[i].altura; j++) {
            for (int k = retangulos[i].x; k < retangulos[i].x + retangulos[i].largura; k++) {
                if (j == retangulos[i].y || j == retangulos[i].y + retangulos[i].altura - 1 || k == retangulos[i].x || k == retangulos[i].x + retangulos[i].largura - 1) {
                    matriz[j][k] = 'X';
                } else {
                    matriz[j][k] = 'O';
                }
            }
        }
    }

    // imprimir a matriz tendo em consideracao o formato do eixo-y em cada linha
    for (int i = MAX_Y - 1; i >= 0; i--) {
        printf("%2d ", i);
        for (int j = 0; j < MAX_X; j++) {
            printf("%c", matriz[i][j]);
        }
        printf("\n");
    }

    // imprimir o eixo-x conforme formato de duas linhas no exemplo acima
    printf("   ");
    for (int i = 0; i < MAX_X + 1; i++) {
        if (i % 10 == 0)
            printf("%d", i % 100 / 10);
        else
            printf(" ");
    }
    printf("\n   ");
    for (int i = 0; i < MAX_X + 1; i++) {
        printf("%d", i % 10);
    }
    printf("\n");
}

int moverDireita(int x, int y, int p) {
    // verificar se exite um retangulo que o ponto x,y pertence
    for (int i = 0; i < contadorRetangulos; i++) {
        if (x >= retangulos[i].x && x < retangulos[i].x + retangulos[i].largura // x está dentro do retangulo
        && y >= retangulos[i].y && y < retangulos[i].y + retangulos[i].altura)  // y está dentro do retangulo
        {
            Retangulo novoRetangulo = {retangulos[i].x + p, retangulos[i].y, retangulos[i].largura, retangulos[i].altura};
            // verificar se o retangulo quando movido para a direita esta numa posicao valida
            if (novoRetangulo.x + novoRetangulo.largura > MAX_X) {
                return 0;
            }

            // verificar se o retangulo pode ser movido para a nova posicao e nao ha intersecao
            if (!intersetaExceto(&novoRetangulo, i)) {
                retangulos[i] = aplicarGravidade(novoRetangulo);
                aplicarGravidadeEmTodos();
                // mensagem de sucesso a informar ao utilizador que o retangulo foi movido com sucesso
                return 1;
            }
        }
    }
    return 0;
}

int moverEsquerda(int x, int y, int p) {
    // verificar se exite um retangulo que o ponto x,y pertence
    for (int i = 0; i < contadorRetangulos; i++) {
        if (x >= retangulos[i].x && x < retangulos[i].x + retangulos[i].largura // x está dentro do retangulo
        && y >= retangulos[i].y && y < retangulos[i].y + retangulos[i].altura)  // y está dentro do retangulo
        {
            Retangulo novoRetangulo = {retangulos[i].x - p, retangulos[i].y, retangulos[i].largura, retangulos[i].altura};
            // verificar se o retangulo quando movido para a esquerda esta numa posicao valida
            if (novoRetangulo.x < 0) {
                return 0;
            }

            // verificar se o retangulo pode ser movido para a nova posicao e nao ha intersecao
            if (!intersetaExceto(&novoRetangulo, i)) {
                retangulos[i] = aplicarGravidade(novoRetangulo);
                aplicarGravidadeEmTodos();
                return 1;
            }
        }
    }
    return 0;
}

int checarSobreposicao(Retangulo *novoRetangulo, Retangulo *retangulo) {
    if (novoRetangulo->x < retangulo->x + retangulo->largura // lado esquerdo do novoRetangulo está à esquerda do lado direito do retangulo
        && novoRetangulo->x + novoRetangulo->largura > retangulo->x // lado direito do novoRetangulo está à direita do lado esquerdo do retangulo
        && novoRetangulo->y < retangulo->y + retangulo->altura // lado inferior do novoRetangulo está abaixo do lado superior do retangulo
        && novoRetangulo->y + novoRetangulo->altura > retangulo->y) // lado superior do novoRetangulo está acima do lado inferior do retangulo
        return 1; // Há sobreposição
    return 0;
}

int intersetaExceto(Retangulo *retangulo, int indexAIgnorar) {
    // index invalido
    if (indexAIgnorar < 0 || indexAIgnorar >= contadorRetangulos)
        return 0;

    // Aqui iremos verificar, se o retangulo informado, intersepta com algum outro retangulo no array de retangulos.
    // Se houver interseção, devemos retornar 1, caso contrário, retornar 0.
    for (int i = 0; i < contadorRetangulos; ++i) {
        if (i == indexAIgnorar)
            continue;
        if (checarSobreposicao(retangulo, &retangulos[i]) > 0)
            return 1;
    }
    return 0; // Não houve interseção com nenhum dos retangulos existentes
}

void aplicarGravidadeEmTodos() {
    for (int i = 0; i < contadorRetangulos; i++) {
        retangulos[i] = aplicarGravidadeIgnorarIntersecaoCom(retangulos[i], i);
    }
}

Retangulo aplicarGravidadeIgnorarIntersecaoCom(Retangulo retangulo, int indexAIgnorar) {
        Retangulo novoRetangulo = {retangulo.x, retangulo.y, retangulo.largura, retangulo.altura};

        // se o retangulo estiver no chão, não aplicar gravidade
        if (novoRetangulo.y == 0)
            return novoRetangulo;

        // A aplicacao da gravidade deve ser feita de forma que:
        // 1. O retangulo deve ser movido para baixo, até que esteja no chao ou sobre outro retangulo.
        // 2. Se o retangulo estiver sobre outro retangulo, ele deve parar de cair.
        for (int i = novoRetangulo.y - 1; i >= 0; i--) {
            novoRetangulo.y = i;
            if (intersetaExceto(&novoRetangulo, indexAIgnorar)) {
                novoRetangulo.y++;
                break;
            }
        }
        // exibe a informar se houve alguma alteracao de posicao do retangulo
        if (novoRetangulo.y != retangulo.y) {
            printf("Gravidade Aplicada. Retângulo movido de (%d, %d) para (%d, %d)\n", retangulo.x, retangulo.y, novoRetangulo.x, novoRetangulo.y);
        }
        return novoRetangulo;
}

void executarComando(char* comando) {
    // Os comandos possíveis são:
    // 1. "create x,y+largura,altura" - cria um novo retângulo nas coordenadas x,y com largura e altura especificadas
    // 2. "moveright x,y+p" - move o retângulo que contém o ponto x,y para a direita p posições
    // 3. "moveleft x,y+p" - move o retângulo que contém o ponto x,y para a esquerda p posições
    // Ao fim da execucao de cada comando, o cenário deve ser impresso

    // verificar se comando esta em um dos 3 formatos validos.
    // deve contar create, moveright ou moveleft como primeira palavra
    // deve conter um espaco imediaamente apos a primeira palavra
    // deve conter 4 numeros inteiros se a palavra inicial for create, ou 3 numeros inteiros se for moveright ou moveleft
    // os dois primeiros numeros devem ser sempre separados por virgula
    // o terceiro numero e sempre separado por um sinal de +
    // o quarto numero e sempre um numero inteiro e separado por virgula do terceiro
    // os numeros devem ser positivos
    // os numeros devem estar dentro dos limites do mundo de retangulos
    int x, y, largura, altura, p;
    int x1, y1, x2, y2;

    if (sscanf(comando, "create %d,%d+%d,%d", &x, &y, &largura, &altura) == 4) {
        if (x < 0 || y < 0 || largura <= 0 || altura <= 0 || x + largura > MAX_X || y + altura > MAX_Y) {
            printf("Comando inválido\n");
            return;
        }
        if (criarRetangulo(x, y, largura, altura) == -1) {
            printf("Erro ao criar retângulo\n");
            return;
        } else {
            imprimirCenario(retangulos, contadorRetangulos);
        }
    } else if (sscanf(comando, "moveright %d,%d+%d", &x, &y, &p) == 3) {
        if (x < 0 || y < 0 || p <= 0 || x >= MAX_X || y >= MAX_Y) {
            printf("Comando inválido\n");
            return;
        }
        if (!moverDireita(x, y, p)) {
            printf("Erro ao mover retângulo para a direita\n");
            return;
        } else {
            imprimirCenario(retangulos, contadorRetangulos);
        }
    } else if (sscanf(comando, "moveleft %d,%d+%d", &x, &y, &p) == 3) {
        if (x < 0 || y < 0 || p <= 0 || x >= MAX_X || y >= MAX_Y) {
            printf("Comando inválido\n");
            return;
        }
        if (!moverEsquerda(x, y, p)) {
            printf("Erro ao mover retângulo para a esquerda\n");
            return;
        } else {
            imprimirCenario(retangulos, contadorRetangulos);
        }
    } else if (sscanf(comando, "merge %d,%d+%d,%d", &x1, &y1, &x2, &y2) == 4) {
        if (x1 < 0 || y1 < 0 || x2 < 0 || y2 < 0 || x1 >= MAX_X || y1 >= MAX_Y || x2 >= MAX_X || y2 >= MAX_Y) {
            printf("Comando inválido\n");
            return;
        }

        int index1 = -1, index2 = -1;
        for (int i = 0; i < contadorRetangulos; i++) {
            if (retangulos[i].x == x1 && retangulos[i].y == y1) {
                index1 = i;
            }
            if (retangulos[i].x == x2 && retangulos[i].y == y2) {
                index2 = i;
            }
        }

        if (index1 == -1 || index2 == -1) {
            printf("Retângulos não encontrados\n");
            return;
        }

        mergeRetangulos(index1, index2);
        imprimirCenario(retangulos, contadorRetangulos);
    } else {
        printf("Comando inválido\n");
        return;
    }

    // Após a execução de cada comando, verificar sobreposições
    alertaSobreposicao();
}
    int mergePossivel(Retangulo *ret1, Retangulo *ret2) {
        return (
                ret1->x == ret2->x // estao na mesma coluna
                && ret1->largura == ret2->largura // tem a mesma largura
                && ret2->y == ret1->y + ret1->altura // ret2 esta imediatamente acima de ret1
        );

    }

    void mergeRetangulos(int index1, int index2) {
        if (index1 < 0 || index1 >= contadorRetangulos || index2 < 0 || index2 >= contadorRetangulos) {
            printf("Índices inválidos para mesclagem\n");
            return;
        }
        Retangulo *ret1 = &retangulos[index1];
        Retangulo *ret2 = &retangulos[index2];

        if (!mergePossivel(ret1, ret2)) {
            printf("Os retângulos não são elegíveis para mesclagem\n");
            return;
        }

        // Atualiza ret1 para a mesclagem
        ret1->altura = ret1->altura + ret2->altura;

        // Remove ret2 do array
        for (int i = index2; i < contadorRetangulos - 1; i++) {
            retangulos[i] = retangulos[i + 1];
        }
        contadorRetangulos--;
        retangulos = realloc(retangulos, sizeof(Retangulo) * contadorRetangulos);
    }

    void alertaSobreposicao() {
        for (int i = 0; i < contadorRetangulos; i++) {
            for (int j = i + 1; j < contadorRetangulos; j++) {
                if (mergePossivel(&retangulos[i], &retangulos[j])) {
                    printf("Os retângulos em (%d, %d) e (%d, %d) podem ser unidos.\n",
                           retangulos[i].x, retangulos[i].y, retangulos[j].x, retangulos[j].y);
                }
            }
        }
    }

    // metodo main deve ser um loop que ira sair apenas quando o usuario informar a palavra exit,
    // do contrario delegamos o conteudo para o metodo executarComando
    #ifndef RUN_TESTS // required for unit testing
    int main() {
        char comando[100];
        inicializarRetangulos();
        while (1) {
            printf("Digite um comando (create x,y+largura,altura | moveright x,y+p | moveleft x,y+p | merge x1,y1+x2,y2 | exit): ");
            fgets(comando, 100, stdin);
            comando[strcspn(comando, "\n")] = 0;
            if (strcmp(comando, "exit") == 0) {
                break;
            }
            executarComando(comando);
        }
        limparRetangulos();
        return 0;
    }
    #endif
