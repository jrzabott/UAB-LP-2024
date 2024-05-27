#ifndef UAB_LP_2024_MUNDORETANGULOS_H
#define UAB_LP_2024_MUNDORETANGULOS_H

#define MAX_X 80 // tamanho maximo lateral do mundo dos retângulos
#define MAX_Y 25 // tamanho máximo vertical do mundo dos retângulos
#define MAX_RETANGULOS 100 // tamanho máximo do array de retângulos criados

typedef struct {
    int x, y, largura, altura;
} Retangulo;

// Array para armazenar os retângulos
extern Retangulo retangulos[MAX_RETANGULOS];
extern int contadorRetangulos;

// Função para criar um retângulo
Retangulo* criarRetangulo(int x, int y, int largura, int altura);

// Função para mover um retângulo para a direita
int moverDireita(int x, int y, int p);

// Função para mover um retângulo para a esquerda
int moverEsquerda(int x, int y, int p);

// Função para verificar interseção entre dois retângulos
int interseta(Retangulo* r1, Retangulo* r2);

// Função para aplicar gravidade em um retângulo
//void aplicarGravidade(Retangulo** retangulos, int numRetangulos, Retangulo* retangulo);
void aplicarGravidade(Retangulo* retangulo);

// Função para imprimir o cenário com todos os retângulos
void imprimirCenario();

// Função para interpretar e executar comandos
void executarComando(char* comando, Retangulo** retangulos, int* numRetangulos);

// Função para inicializar o array de retângulos
void inicializarRetangulos();

// Função para limpar o array de retângulos
void limparRetangulos();

#endif //UAB_LP_2024_MUNDORETANGULOS_H
