#include <stdlib.h>

#include "unity/unity.h"
#include "../src/mundoRetangulos.h"

void setUp(void) {
    inicializarRetangulos();
}

void tearDown(void) {
    limparRetangulos();
}

void test_criarRetanguloForaLimites(void) {
    int retanguloIndex = criarRetangulo(75, 3, 10, 5); // Ultrapassa o limite
    TEST_ASSERT_EQUAL(-1, retanguloIndex);
}

void test_aposCriarNovoRetanguloEsteFicaSalvoNoArray(void) {
    int retanguloIndex = criarRetangulo(0, 0, 10, 5);
    TEST_ASSERT_EQUAL(0, retanguloIndex);
    TEST_ASSERT_EQUAL(1, contadorRetangulos);
    TEST_ASSERT_EQUAL(0, retangulos[0].x);
    TEST_ASSERT_EQUAL(0, retangulos[0].y);
    TEST_ASSERT_EQUAL(10, retangulos[0].largura);
    TEST_ASSERT_EQUAL(5, retangulos[0].altura);
}

void test_criarDoisRetangulosDistintosAdicionaNoArrayENaoModificaORetanguloExistente(void) {
    int retanguloIndex1 = criarRetangulo(0, 0, 10, 5);
    int retanguloIndex2 = criarRetangulo(11, 0, 10, 5);

    TEST_ASSERT_EQUAL(0, retanguloIndex1);
    TEST_ASSERT_EQUAL(1, retanguloIndex2);
    TEST_ASSERT_EQUAL(2, contadorRetangulos);

    TEST_ASSERT_EQUAL(0, retangulos[retanguloIndex1].x);
    TEST_ASSERT_EQUAL(0, retangulos[retanguloIndex1].y);
    TEST_ASSERT_EQUAL(10, retangulos[retanguloIndex1].largura);
    TEST_ASSERT_EQUAL(5, retangulos[retanguloIndex1].altura);

    TEST_ASSERT_EQUAL(11, retangulos[retanguloIndex2].x);
    TEST_ASSERT_EQUAL(0, retangulos[retanguloIndex2].y);
    TEST_ASSERT_EQUAL(10, retangulos[retanguloIndex2].largura);
    TEST_ASSERT_EQUAL(5, retangulos[retanguloIndex2].altura);
}

void test_interseta(void) {
    // Inicializar o array de retângulos sabendo antecipadamente que serão necessários 3 retângulos
    contadorRetangulos = 0;
    retangulos = malloc(sizeof(Retangulo) * 2);

    // Adicionar um primeiro retângulo ao cenário, sendo o primeiro retângulo, obviamente, não intersecciona com nenhum outro
    Retangulo retangulo1 = {0, 0, 10, 5};
    TEST_ASSERT_FALSE(interseta(&retangulo1));
    retangulos[contadorRetangulos++] = retangulo1; // Adicionar o retângulo ao array de retângulos

    // Adicionar um segundo retangulo que nao intersecciona com o primeiro
    Retangulo retangulo2 = {11, 0, 10, 5};
    TEST_ASSERT_FALSE(interseta(&retangulo2));
    retangulos[contadorRetangulos++] = retangulo2; // Adicionar o retângulo ao array de retângulos

    // Tentar adicionar um terceiro retangulo que intersecciona com o primeiro
    Retangulo retangulo3 = {5, 2, 10, 5};
    TEST_ASSERT_TRUE(interseta(&retangulo3));
}

void test_interseta2(void) {
    // Inicializar o array de retângulos sabendo antecipadamente que serão necessários 3 retângulos
    contadorRetangulos = 0;
    retangulos = malloc(sizeof(Retangulo) * 2);

    // Adicionar um primeiro retângulo ao cenário, sendo o primeiro retângulo, obviamente, não intersecciona com nenhum outro
    Retangulo retangulo1 = {1, 0, 1, 4};
    TEST_ASSERT_FALSE(interseta(&retangulo1));
    retangulos[contadorRetangulos++] = retangulo1; // Adicionar o retângulo ao array de retângulos

    // Adicionar um segundo retangulo que nao intersecciona com o primeiro
    Retangulo retangulo2 = {0, 2, 3, 2};
    TEST_ASSERT_TRUE(interseta(&retangulo2));
}

void test_insersetaDevePermitirQueDoisRetangulosToquemSeusLados(void) {
    // Inicializar o array de retângulos sabendo antecipadamente que serão necessários 3 retângulos
    contadorRetangulos = 0;
    retangulos = malloc(sizeof(Retangulo) * 2);

    // Adicionar um primeiro retângulo ao cenário, sendo o primeiro retângulo, obviamente, não intersecciona com nenhum outro
    Retangulo retangulo1 = {0, 0, 1, 4};
    TEST_ASSERT_FALSE(interseta(&retangulo1));
    retangulos[contadorRetangulos++] = retangulo1; // Adicionar o retângulo ao array de retângulos

    // Adicionar um segundo retangulo que nao intersecciona com o primeiro
    Retangulo retangulo2 = {1, 0, 3, 2};
    TEST_ASSERT_FALSE(interseta(&retangulo2));
    retangulos[contadorRetangulos++] = retangulo2; // Adicionar o retângulo ao array de retângulos
}

void test_criar3RetangulosSendoQueUmDelesInterseccionaComOsOutros(void) {
    int retanguloIndex1 = criarRetangulo(1, 3, 12, 5);
    int retanguloIndex2 = criarRetangulo(15, 3, 12, 5);
    int retanguloIndex3 = criarRetangulo(2, 2, 20, 5); // Intersecciona com os dois primeiros

    TEST_ASSERT_EQUAL(2, contadorRetangulos);

    TEST_ASSERT_EQUAL(1, retangulos[retanguloIndex1].x);
    TEST_ASSERT_EQUAL(0, retangulos[retanguloIndex1].y);
    TEST_ASSERT_EQUAL(12, retangulos[retanguloIndex1].largura);
    TEST_ASSERT_EQUAL(5, retangulos[retanguloIndex1].altura);

    TEST_ASSERT_EQUAL(15, retangulos[retanguloIndex2].x);
    TEST_ASSERT_EQUAL(0, retangulos[retanguloIndex2].y);
    TEST_ASSERT_EQUAL(12, retangulos[retanguloIndex2].largura);
    TEST_ASSERT_EQUAL(5, retangulos[retanguloIndex2].altura);

    TEST_ASSERT_EQUAL(-1, retanguloIndex3);
}

void test_aplicarGravidadeAUmRetangulo(void) {
    int retanguloIndex = criarRetangulo(1, 3, 12, 5);
    Retangulo retangulo = retangulos[retanguloIndex];
    aplicarGravidade(retangulo);
    
    TEST_ASSERT_EQUAL(1, retangulo.x);
    TEST_ASSERT_EQUAL(0, retangulo.y);
    TEST_ASSERT_EQUAL(12, retangulo.largura);
    TEST_ASSERT_EQUAL(5, retangulo.altura);
}

void test_aplicarGravidadeADoisRetangulosLadoALado(void) {
    int retanguloIndex1 = criarRetangulo(1, 3, 12, 5);
    int retanguloIndex2 = criarRetangulo(15, 3, 12, 5);
    
    Retangulo retangulo1 = retangulos[retanguloIndex1];
    Retangulo retangulo2 = retangulos[retanguloIndex2];
    
    aplicarGravidade(retangulo1);
    aplicarGravidade(retangulo2);
    TEST_ASSERT_EQUAL(1, retangulo1.x);
    TEST_ASSERT_EQUAL(0, retangulo1.y);
    TEST_ASSERT_EQUAL(12, retangulo1.largura);
    TEST_ASSERT_EQUAL(5, retangulo1.altura);
    TEST_ASSERT_EQUAL(15, retangulo2.x);
    TEST_ASSERT_EQUAL(0, retangulo2.y);
    TEST_ASSERT_EQUAL(12, retangulo2.largura);
    TEST_ASSERT_EQUAL(5, retangulo2.altura);
}

void test_aplicarGravidadeADoisRetangulosUmSobreOOutroComMesmaLargura(void) {
    int retanguloIndex1 = criarRetangulo(1, 3, 12, 5);
    TEST_ASSERT_EQUAL(0, retanguloIndex1);
    Retangulo retangulo1 = retangulos[retanguloIndex1];
    aplicarGravidade(retangulo1);
    
    int retanguloIndex2 = criarRetangulo(1, 8, 12, 5);
    TEST_ASSERT_EQUAL(1, retanguloIndex2);
    Retangulo retangulo2 = retangulos[retanguloIndex2];
    
    aplicarGravidade(retangulo2);
    TEST_ASSERT_EQUAL(1, retangulo1.x);
    TEST_ASSERT_EQUAL(0, retangulo1.y);
    TEST_ASSERT_EQUAL(12, retangulo1.largura);
    TEST_ASSERT_EQUAL(5, retangulo1.altura);
    TEST_ASSERT_EQUAL(1, retangulo2.x);
    TEST_ASSERT_EQUAL(5, retangulo2.y);
    TEST_ASSERT_EQUAL(12, retangulo2.largura);
    TEST_ASSERT_EQUAL(5, retangulo2.altura);
}

void test_aplicarGravidadeATresRetangulosPrimeiroESegundoLadoALadoComAlturasDiferentesTerceiroNaoInterseccionaMasDeveCairSobreOMaisAlto() {
    criarRetangulo(0, 0, 2, 2);
    criarRetangulo(2, 0, 2, 4);
    criarRetangulo(0, 10, 6, 5);
    Retangulo retangulo1 = retangulos[0];
    Retangulo retangulo2 = retangulos[1];
    Retangulo retangulo3 = retangulos[2];

    TEST_ASSERT_EQUAL(3, contadorRetangulos);

    TEST_ASSERT_EQUAL(0, retangulo1.x);
    TEST_ASSERT_EQUAL(0, retangulo1.y);
    TEST_ASSERT_EQUAL(2, retangulo1.largura);
    TEST_ASSERT_EQUAL(2, retangulo1.altura);

    TEST_ASSERT_EQUAL(2, retangulo2.x);
    TEST_ASSERT_EQUAL(0, retangulo2.y);
    TEST_ASSERT_EQUAL(2, retangulo2.largura);
    TEST_ASSERT_EQUAL(4, retangulo2.altura);

    TEST_ASSERT_EQUAL(0, retangulo3.x);
    TEST_ASSERT_EQUAL(4, retangulo3.y);
    TEST_ASSERT_EQUAL(6, retangulo3.largura);
    TEST_ASSERT_EQUAL(5, retangulo3.altura);
}

// teste para criar 3 retangulos, e inspecionar o cenário visualmente
void test_criar3RetangulosComDiferentesAlturasEscreverNoEcraParaConsultaDoCenario(void) {
    criarRetangulo(0, 0, 2, 2);
    criarRetangulo(2, 0, 2, 4);
    criarRetangulo(0, 10, 6, 5);
    imprimirCenario(retangulos, contadorRetangulos);
}

void test_criarGravidadeEAplicadaNaCriacaoDeTodosRetangulos(void) {
    criarRetangulo(1, 3, 12, 5);
    criarRetangulo(15, 10, 12, 7);
    criarRetangulo(10, 20, 12, 5);

    Retangulo retangulo1 = retangulos[0];
    Retangulo retangulo2 = retangulos[1];
    Retangulo retangulo3 = retangulos[2];
    TEST_ASSERT_EQUAL(3, contadorRetangulos);

    // verificar que todos os retangulos foram movidos para a posicao correta
    TEST_ASSERT_EQUAL(1, retangulo1.x);
    TEST_ASSERT_EQUAL(0, retangulo1.y);
    TEST_ASSERT_EQUAL(12, retangulo1.largura);
    TEST_ASSERT_EQUAL(5, retangulo1.altura);

    TEST_ASSERT_EQUAL(15, retangulo2.x);
    TEST_ASSERT_EQUAL(0, retangulo2.y);
    TEST_ASSERT_EQUAL(12, retangulo2.largura);
    TEST_ASSERT_EQUAL(7, retangulo2.altura);

    TEST_ASSERT_EQUAL(10, retangulo3.x);
    TEST_ASSERT_EQUAL(7, retangulo3.y);
    TEST_ASSERT_EQUAL(12, retangulo3.largura);
    TEST_ASSERT_EQUAL(5, retangulo3.altura);
}

void test_moverUmRetanguloParaADireitaMoveORetangulo(void) {
    Retangulo *retangulo = &retangulos[criarRetangulo(1, 3, 12, 5)];
    // apesar do retangulo ser criado em y = 3, a gravidade faz com que ele caia para y = 0
    TEST_ASSERT_TRUE(moverDireita(1, 1, 5));

    TEST_ASSERT_EQUAL(6, retangulo->x);
    TEST_ASSERT_EQUAL(0, retangulo->y);
    TEST_ASSERT_EQUAL(12, retangulo->largura);
    TEST_ASSERT_EQUAL(5, retangulo->altura);
}

void test_moverUmRetanguloQueEstaSobreOutroFazComQueEsteCaiaAposUltrapassarLarguraDoRetanguloDeBaixo(void) {
    criarRetangulo(0, 0, 10, 5);
    criarRetangulo(6, 10, 3, 3);
    Retangulo *retangulo1 = &retangulos[0];
    Retangulo *retangulo2 = &retangulos[1];

//    imprimirCenario(retangulos, contadorRetangulos);

    // mover retangulo2 para a direita
    TEST_ASSERT_TRUE(moverDireita(6, 6, 5));

    TEST_ASSERT_EQUAL(0, retangulo1->x);
    TEST_ASSERT_EQUAL(0, retangulo1->y);
    TEST_ASSERT_EQUAL(10, retangulo1->largura);
    TEST_ASSERT_EQUAL(5, retangulo1->altura);

    TEST_ASSERT_EQUAL(11, retangulo2->x);
    TEST_ASSERT_EQUAL(0, retangulo2->y);
    TEST_ASSERT_EQUAL(3, retangulo2->largura);
    TEST_ASSERT_EQUAL(3, retangulo2->altura);

//    imprimirCenario(retangulos, contadorRetangulos);
}

void test_moverUmRetanguloParaADireitaNaoPermiteInterseccaoComOutroRetangulo(void) {
    criarRetangulo(1, 3, 5, 5);
    criarRetangulo(6, 3, 5, 5);
    Retangulo *retangulo1 = &retangulos[0];
    Retangulo *retangulo2 = &retangulos[1];

    moverDireita(1, 1, 5);

    TEST_ASSERT_EQUAL(1, retangulo1->x);
    TEST_ASSERT_EQUAL(0, retangulo1->y);
    TEST_ASSERT_EQUAL(5, retangulo1->largura);
    TEST_ASSERT_EQUAL(5, retangulo1->altura);

    TEST_ASSERT_EQUAL(6, retangulo2->x);
    TEST_ASSERT_EQUAL(0, retangulo2->y);
    TEST_ASSERT_EQUAL(5, retangulo2->largura);
    TEST_ASSERT_EQUAL(5, retangulo2->altura);
}

void test_moverUmRetanguloParaAEsquerdaMoveORetangulo(void) {
    Retangulo *retangulo = &retangulos[criarRetangulo(6, 3, 12, 5)];
    // apesar do retangulo ser criado em y = 3, a gravidade faz com que ele caia para y = 1
    moverEsquerda(6, 1, 5);
    TEST_ASSERT_EQUAL(1, retangulo->x);
    TEST_ASSERT_EQUAL(0, retangulo->y);
    TEST_ASSERT_EQUAL(12, retangulo->largura);
    TEST_ASSERT_EQUAL(5, retangulo->altura);
}

void test_moverParaEsquerdaUmRetanguloQueEstaSobreOutroFazComQueEsteCaiaAposUltrapassarLarguraDoRetanguloDeBaixo(void) {
    criarRetangulo(6, 3, 5, 5);
    criarRetangulo(6, 8, 3, 3);

    Retangulo *retangulo1 = &retangulos[0];
    Retangulo *retangulo2 = &retangulos[1];

    // mover retangulo2 para a esquerda
    moverEsquerda(6, 6, 3);

    TEST_ASSERT_EQUAL(6, retangulo1->x);
    TEST_ASSERT_EQUAL(0, retangulo1->y);
    TEST_ASSERT_EQUAL(5, retangulo1->largura);
    TEST_ASSERT_EQUAL(5, retangulo1->altura);

    TEST_ASSERT_EQUAL(3, retangulo2->x);
    TEST_ASSERT_EQUAL(0, retangulo2->y);
    TEST_ASSERT_EQUAL(3, retangulo2->largura);
    TEST_ASSERT_EQUAL(3, retangulo2->altura);
}

void test_moverUmRetanguloParaADireitaAteOLimiteEVerificarQueNaoUltrapassa(void) {
    Retangulo *retangulo = &retangulos[criarRetangulo(75, 3, 5, 5)];
    moverDireita(75, 1, 10);
    TEST_ASSERT_EQUAL(75, retangulo->x);
    TEST_ASSERT_EQUAL(0, retangulo->y);
    TEST_ASSERT_EQUAL(5, retangulo->largura);
    TEST_ASSERT_EQUAL(5, retangulo->altura);
}

// teste para testar todos os formatos suportados para executarComando, e tambem como reage a erros e entradas invalidas.
// formatos corretos suportados:
//  create x,y+l,h - cria um retângulo em que (x,y) são as coordenadas do canto inferior esquerdo e (l,h) o comprimento e altura, respetivamente.
//  moveright x,y+p - desloca o retângulo situado nas coordenadas (x,y) para a direita p posições
//  moveleft x,y+p - desloca o retângulo que contém o ponto (x,y) para a esquerda p posições
void test_executarComando(void) {
    executarComando("create 1,3+12,5");
    executarComando("create 9,6+11,3");
    executarComando("create 18,10+6,3");
    executarComando("moveleft 12,7+3");

    // testar comandos invalidos
    executarComando("create 1,3+12,5+5"); // comando invalido
    executarComando("create 1,3+12,5+"); // comando invalido
    executarComando("create 1,3+12,5+5+5"); // comando invalido
    executarComando("create 1,3+12,5+5,5"); // comando invalido
    executarComando("create 1,3+12,5+5,5+5"); // comando invalido
    executarComando("create 1,3+12,5+5,5+"); // comando invalido
    executarComando("create 1,3+12,5+5,5+5,5"); // comando invalido
    executarComando("create 1,3+12,5+5,5+5,5+5"); // comando invalido

    TEST_ASSERT_EQUAL(3, contadorRetangulos);

    TEST_ASSERT_EQUAL(0, retangulos[0].x);
    TEST_ASSERT_EQUAL(0, retangulos[0].y);
    TEST_ASSERT_EQUAL(12, retangulos[0].largura);
    TEST_ASSERT_EQUAL(5, retangulos[0].altura);

    TEST_ASSERT_EQUAL(5, retangulos[1].x);
    TEST_ASSERT_EQUAL(5, retangulos[1].y);
    TEST_ASSERT_EQUAL(11, retangulos[1].largura);
    TEST_ASSERT_EQUAL(3, retangulos[1].altura);

    TEST_ASSERT_EQUAL(17, retangulos[2].x);
    TEST_ASSERT_EQUAL(0, retangulos[2].y);
    TEST_ASSERT_EQUAL(6, retangulos[2].largura);
    TEST_ASSERT_EQUAL(3, retangulos[2].altura);
}

// Commandos propostos
//  create 1,3+12,5
//  create 9,6+11,3
//  create 18,10+6,3
//  moveleft 12,7+3
void test_imprimirComandosPropostosEVisualizarResultado(void) {
    executarComando("create 1,3+12,5");
    executarComando("create 9,6+11,3");
    executarComando("create 18,10+6,3");
    executarComando("moveleft 12,7+3");
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_criarRetanguloForaLimites);
    RUN_TEST(test_aposCriarNovoRetanguloEsteFicaSalvoNoArray);
    RUN_TEST(test_criarDoisRetangulosDistintosAdicionaNoArrayENaoModificaORetanguloExistente);
    RUN_TEST(test_criar3RetangulosSendoQueUmDelesInterseccionaComOsOutros);
    RUN_TEST(test_interseta);
    RUN_TEST(test_interseta2);
    RUN_TEST(test_insersetaDevePermitirQueDoisRetangulosToquemSeusLados);
    RUN_TEST(test_aplicarGravidadeAUmRetangulo);
    RUN_TEST(test_aplicarGravidadeADoisRetangulosLadoALado);
    RUN_TEST(test_aplicarGravidadeADoisRetangulosUmSobreOOutroComMesmaLargura);
    RUN_TEST(test_aplicarGravidadeATresRetangulosPrimeiroESegundoLadoALadoComAlturasDiferentesTerceiroNaoInterseccionaMasDeveCairSobreOMaisAlto);
    RUN_TEST(test_criarGravidadeEAplicadaNaCriacaoDeTodosRetangulos);
    RUN_TEST(test_moverUmRetanguloParaADireitaMoveORetangulo);
    RUN_TEST(test_moverUmRetanguloQueEstaSobreOutroFazComQueEsteCaiaAposUltrapassarLarguraDoRetanguloDeBaixo);
    RUN_TEST(test_moverUmRetanguloParaADireitaNaoPermiteInterseccaoComOutroRetangulo);
    RUN_TEST(test_moverUmRetanguloParaAEsquerdaMoveORetangulo);
    RUN_TEST(test_moverParaEsquerdaUmRetanguloQueEstaSobreOutroFazComQueEsteCaiaAposUltrapassarLarguraDoRetanguloDeBaixo);
    RUN_TEST(test_moverUmRetanguloParaADireitaAteOLimiteEVerificarQueNaoUltrapassa);
    RUN_TEST(test_executarComando);
    RUN_TEST(test_imprimirComandosPropostosEVisualizarResultado);
    RUN_TEST(test_criar3RetangulosComDiferentesAlturasEscreverNoEcraParaConsultaDoCenario);
    return UNITY_END();
}

