#ifndef UAB_LP_2024_MUNDORETANGULOS_H
#define UAB_LP_2024_MUNDORETANGULOS_H

#define MAX_X 80 // tamanho maximo lateral do mundo dos retângulos - logicamente o valor e 80, mas como o array comeca em 0, o valor maximo e 79
#define MAX_Y 25 // tamanho máximo vertical do mundo dos retângulos - como acima.

typedef struct {
    int x, y, largura, altura;
} Retangulo;

// Array para armazenar os retângulos
extern Retangulo *retangulos;
extern int contadorRetangulos;

// Função para criar um retângulo. Retorna o index do retângulo no array de retângulos
int criarRetangulo(int x, int y, int largura, int altura);

// Função para mover um retângulo para a direita
int moverDireita(int x, int y, int p);

// Função para mover um retângulo para a esquerda
int moverEsquerda(int x, int y, int p);

// Função para verificar interseção entre dois retângulos
int interseta(Retangulo *retangulo);

// Função para aplicar gravidade em um retângulo
//void aplicarGravidade(Retangulo** retangulos, int numRetangulos, Retangulo* retangulo);
Retangulo aplicarGravidade(Retangulo retangulo);

// Função para imprimir o cenário com todos os retângulos
void imprimirCenario(Retangulo *retangulos, int numRetangulos);

// Função para interpretar e executar comandos
void executarComando(char* comando);

// Função para inicializar o array de retângulos
void inicializarRetangulos();

// Função para limpar o array de retângulos
void limparRetangulos();

// Função para verificar se dois retângulos se sobrepõem.
int checarSobreposicao(Retangulo *novoRetangulo, Retangulo *retangulo);

// Verifica se um retângulo se sobrepõe a qualquer outro, exceto o retângulo no índice especificado.
int intersetaExceto(Retangulo *retangulo, int indexAIgnorar);

// Aplica a gravidade a todos os retângulos no array.
void aplicarGravidadeEmTodos();

// Aplica a gravidade a um retângulo, ignorando a interseção com o retângulo no índice especificado.
Retangulo aplicarGravidadeIgnorarIntersecaoCom(Retangulo retangulo, int indexAIgnorar);

// Verifica se é possível unir dois retângulos com base em suas posições e dimensões.
int mergePossivel(Retangulo *ret1, Retangulo *ret2);

// Une dois retângulos no array de retângulos, se possível, e remove o segundo retângulo.
void mergeRetangulos(int index1, int index2);

// Verifica se há retângulos que podem ser unidos e imprime um alerta.
void alertaSobreposicao();

#endif //UAB_LP_2024_MUNDORETANGULOS_H
