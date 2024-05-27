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
    Retangulo *retangulo = criarRetangulo(75, 3, 10, 5); // Ultrapassa o limite x=80
    TEST_ASSERT_NULL(retangulo);
}

void test_interseta(void) {
    Retangulo r1 = {1, 1, 5, 5};
    Retangulo r2 = {3, 3, 5, 5}; // Intersecciona com r1
    Retangulo r3 = {7, 7, 2, 2}; // Não intersecciona com r1

    TEST_ASSERT_TRUE(interseta(&r1, &r2));
    TEST_ASSERT_FALSE(interseta(&r1, &r3));
}

void test_insersetaDevePermitirQueDoisRetangulosToquemSeusLados(void) {
    Retangulo r1 = {1, 1, 5, 5};
    Retangulo r2 = {6, 1, 5, 5}; // Não intersecciona com r1
    Retangulo r3 = {6, 6, 2, 2}; // Não intersecciona com r1

    TEST_ASSERT_FALSE(interseta(&r1, &r2));
    TEST_ASSERT_FALSE(interseta(&r1, &r3));
}

void test_aposCriarNovoRetanguloEsteFicaSalvoNoArray(void) {
    Retangulo *retangulo = criarRetangulo(1, 3, 12, 5);
    TEST_ASSERT_EQUAL(1, contadorRetangulos);
    TEST_ASSERT_EQUAL(1, retangulos[0].x);
    TEST_ASSERT_EQUAL(1, retangulos[0].y);
    TEST_ASSERT_EQUAL(12, retangulos[0].largura);
    TEST_ASSERT_EQUAL(5, retangulos[0].altura);
}

void test_criarDoisRetangulosDistintosAdicionaNoArrayENaoModificaORetanguloExistente(void) {
    Retangulo *retangulo1 = criarRetangulo(1, 3, 12, 5);
    Retangulo *retangulo2 = criarRetangulo(15, 3, 12, 5);

    TEST_ASSERT_EQUAL(2, contadorRetangulos);

    TEST_ASSERT_EQUAL(1, retangulos[0].x);
    TEST_ASSERT_EQUAL(1, retangulos[0].y);
    TEST_ASSERT_EQUAL(12, retangulos[0].largura);
    TEST_ASSERT_EQUAL(5, retangulos[0].altura);

    TEST_ASSERT_EQUAL(15, retangulos[1].x);
    TEST_ASSERT_EQUAL(1, retangulos[1].y);
    TEST_ASSERT_EQUAL(12, retangulos[1].largura);
    TEST_ASSERT_EQUAL(5, retangulos[1].altura);
}

void test_criar3RetangulosSendoQueUmDelesInterseccionaComOsOutros(void) {
    Retangulo *retangulo1 = criarRetangulo(1, 3, 12, 5);
    Retangulo *retangulo2 = criarRetangulo(15, 3, 12, 5);
    Retangulo *retangulo3 = criarRetangulo(10, 3, 12, 5); // Intersecciona com retangulo1

    TEST_ASSERT_EQUAL(2, contadorRetangulos);

    TEST_ASSERT_EQUAL(1, retangulos[0].x);
    TEST_ASSERT_EQUAL(1, retangulos[0].y);
    TEST_ASSERT_EQUAL(12, retangulos[0].largura);
    TEST_ASSERT_EQUAL(5, retangulos[0].altura);

    TEST_ASSERT_EQUAL(15, retangulos[1].x);
    TEST_ASSERT_EQUAL(1, retangulos[1].y);
    TEST_ASSERT_EQUAL(12, retangulos[1].largura);
    TEST_ASSERT_EQUAL(5, retangulos[1].altura);

    TEST_ASSERT_NULL(retangulo3);
}

void test_aplicarGravidadeAUmRetangulo(void) {
    Retangulo *retangulo = criarRetangulo(1, 3, 12, 5);
    aplicarGravidade(retangulo);
    TEST_ASSERT_EQUAL(1, retangulo->x);
    TEST_ASSERT_EQUAL(1, retangulo->y);
    TEST_ASSERT_EQUAL(12, retangulo->largura);
    TEST_ASSERT_EQUAL(5, retangulo->altura);
}

void test_aplicarGravidadeADoisRetangulosLadoALado(void) {
    Retangulo *retangulo1 = criarRetangulo(1, 3, 12, 5);
    Retangulo *retangulo2 = criarRetangulo(15, 3, 12, 5);
    aplicarGravidade(retangulo1);
    aplicarGravidade(retangulo2);
    TEST_ASSERT_EQUAL(1, retangulo1->x);
    TEST_ASSERT_EQUAL(1, retangulo1->y);
    TEST_ASSERT_EQUAL(12, retangulo1->largura);
    TEST_ASSERT_EQUAL(5, retangulo1->altura);
    TEST_ASSERT_EQUAL(15, retangulo2->x);
    TEST_ASSERT_EQUAL(1, retangulo2->y);
    TEST_ASSERT_EQUAL(12, retangulo2->largura);
    TEST_ASSERT_EQUAL(5, retangulo2->altura);
}

void test_aplicarGravidadeADoisRetangulosUmSobreOOutroComMesmaLargura(void) {
    Retangulo *retangulo1 = criarRetangulo(1, 3, 12, 5);
    TEST_ASSERT_TRUE(retangulo1 == &retangulos[0]);
    aplicarGravidade(retangulo1);
    Retangulo *retangulo2 = criarRetangulo(1, 8, 12, 5);
    aplicarGravidade(retangulo2);
    TEST_ASSERT_EQUAL(1, retangulo1->x);
    TEST_ASSERT_EQUAL(1, retangulo1->y);
    TEST_ASSERT_EQUAL(12, retangulo1->largura);
    TEST_ASSERT_EQUAL(5, retangulo1->altura);
    TEST_ASSERT_EQUAL(1, retangulo2->x);
    TEST_ASSERT_EQUAL(6, retangulo2->y);
    TEST_ASSERT_EQUAL(12, retangulo2->largura);
    TEST_ASSERT_EQUAL(5, retangulo2->altura);
}

void test_aplicarGravidadeATresRetangulosPrimeiroESegundoLadoALadoComAlturasDiferentesTerceiroNaoInterseccionaMasDeveCairSobreOMaisAlto() {
    Retangulo *retangulo1 = criarRetangulo(1, 3, 12, 5);
    Retangulo *retangulo2 = criarRetangulo(15, 10, 12, 7);
    aplicarGravidade(retangulo1);
    aplicarGravidade(retangulo2);
    Retangulo *retangulo3 = criarRetangulo(10, 20, 12, 5);
    aplicarGravidade(retangulo3);
    TEST_ASSERT_EQUAL(1, retangulo1->x);
    TEST_ASSERT_EQUAL(1, retangulo1->y);
    TEST_ASSERT_EQUAL(12, retangulo1->largura);
    TEST_ASSERT_EQUAL(5, retangulo1->altura);
    TEST_ASSERT_EQUAL(15, retangulo2->x);
    TEST_ASSERT_EQUAL(1, retangulo2->y);
    TEST_ASSERT_EQUAL(12, retangulo2->largura);
    TEST_ASSERT_EQUAL(7, retangulo2->altura);
    TEST_ASSERT_EQUAL(10, retangulo3->x);
    TEST_ASSERT_EQUAL(8, retangulo3->y);
    TEST_ASSERT_EQUAL(12, retangulo3->largura);
    TEST_ASSERT_EQUAL(5, retangulo3->altura);
}

// teste para criar 3 retangulos, aplicar gravidade e imprimir no ecra o cenarios
void test_criar3RetangulosComDiferentesAlturasEscreverNoEcraParaConsultaDoCenario(void) {
    Retangulo *retangulo1 = criarRetangulo(1, 3, 12, 5);
    Retangulo *retangulo2 = criarRetangulo(15, 10, 12, 7);
    aplicarGravidade(retangulo1);
    aplicarGravidade(retangulo2);
    Retangulo *retangulo3 = criarRetangulo(10, 20, 12, 5);
    aplicarGravidade(retangulo3);
    imprimirCenario(retangulos, contadorRetangulos);
}

void test_criarGravidadeEAplicadaNaCriacaoDeTodosRetangulos(void) {
    Retangulo *retangulo1 = criarRetangulo(1, 3, 12, 5);
    Retangulo *retangulo2 = criarRetangulo(15, 10, 12, 7);
    Retangulo *retangulo3 = criarRetangulo(10, 20, 12, 5);
    TEST_ASSERT_EQUAL(3, contadorRetangulos);

    // verificar que todos os retangulos foram movidos para a posicao correta
    TEST_ASSERT_EQUAL(1, retangulo1->x);
    TEST_ASSERT_EQUAL(1, retangulo1->y);
    TEST_ASSERT_EQUAL(12, retangulo1->largura);
    TEST_ASSERT_EQUAL(5, retangulo1->altura);

    TEST_ASSERT_EQUAL(15, retangulo2->x);
    TEST_ASSERT_EQUAL(1, retangulo2->y);
    TEST_ASSERT_EQUAL(12, retangulo2->largura);
    TEST_ASSERT_EQUAL(7, retangulo2->altura);

    TEST_ASSERT_EQUAL(10, retangulo3->x);
    TEST_ASSERT_EQUAL(8, retangulo3->y);
    TEST_ASSERT_EQUAL(12, retangulo3->largura);
    TEST_ASSERT_EQUAL(5, retangulo3->altura);
}

void test_moverUmRetanguloParaADireitaMoveORetangulo(void) {
    Retangulo *retangulo = criarRetangulo(1, 3, 12, 5);
    // apesar do retangulo ser criado em y = 3, a gravidade faz com que ele caia para y = 1
    moverDireita(1, 1, 5);
    TEST_ASSERT_EQUAL(6, retangulo->x);
    TEST_ASSERT_EQUAL(1, retangulo->y);
    TEST_ASSERT_EQUAL(12, retangulo->largura);
    TEST_ASSERT_EQUAL(5, retangulo->altura);
}

void test_moverUmRetanguloQueEstaSobreOutroFazComQueEsteCaiaAposUltrapassarLarguraDoRetanguloDeBaixo(void) {
    Retangulo *retangulo1 = criarRetangulo(1, 3, 5, 5);
    Retangulo *retangulo2 = criarRetangulo(1, 8, 12, 5);

    // move o retangulo2 para a direita
    moverDireita(1, 6, 5);

    TEST_ASSERT_EQUAL(1, retangulo1->x);
    TEST_ASSERT_EQUAL(1, retangulo1->y);
    TEST_ASSERT_EQUAL(5, retangulo1->largura);
    TEST_ASSERT_EQUAL(5, retangulo1->altura);

    TEST_ASSERT_EQUAL(6, retangulo2->x);
    TEST_ASSERT_EQUAL(1, retangulo2->y);
    TEST_ASSERT_EQUAL(12, retangulo2->largura);
    TEST_ASSERT_EQUAL(5, retangulo2->altura);
}

void test_moverUmRetanguloParaADireitaNaoPermiteInterseccaoComOutroRetangulo(void) {
    Retangulo *retangulo1 = criarRetangulo(1, 3, 5, 5);
    Retangulo *retangulo2 = criarRetangulo(6, 3, 5, 5);

    moverDireita(1, 1, 5);

    TEST_ASSERT_EQUAL(1, retangulo1->x);
    TEST_ASSERT_EQUAL(1, retangulo1->y);
    TEST_ASSERT_EQUAL(5, retangulo1->largura);
    TEST_ASSERT_EQUAL(5, retangulo1->altura);

    TEST_ASSERT_EQUAL(6, retangulo2->x);
    TEST_ASSERT_EQUAL(1, retangulo2->y);
    TEST_ASSERT_EQUAL(5, retangulo2->largura);
    TEST_ASSERT_EQUAL(5, retangulo2->altura);
}

void test_moverUmRetanguloParaAEsquerdaMoveORetangulo(void) {
    Retangulo *retangulo = criarRetangulo(6, 3, 12, 5);
    // apesar do retangulo ser criado em y = 3, a gravidade faz com que ele caia para y = 1
    moverEsquerda(6, 1, 5);
    TEST_ASSERT_EQUAL(1, retangulo->x);
    TEST_ASSERT_EQUAL(1, retangulo->y);
    TEST_ASSERT_EQUAL(12, retangulo->largura);
    TEST_ASSERT_EQUAL(5, retangulo->altura);
}

void test_moverParaEsquerdaUmRetanguloQueEstaSobreOutroFazComQueEsteCaiaAposUltrapassarLarguraDoRetanguloDeBaixo(void) {
    Retangulo *retangulo1 = criarRetangulo(6, 3, 5, 5);
    Retangulo *retangulo2 = criarRetangulo(6, 8, 3, 3);

    // mover retangulo2 para a esquerda
    moverEsquerda(6, 6, 3);

    TEST_ASSERT_EQUAL(6, retangulo1->x);
    TEST_ASSERT_EQUAL(1, retangulo1->y);
    TEST_ASSERT_EQUAL(5, retangulo1->largura);
    TEST_ASSERT_EQUAL(5, retangulo1->altura);

    TEST_ASSERT_EQUAL(3, retangulo2->x);
    TEST_ASSERT_EQUAL(1, retangulo2->y);
    TEST_ASSERT_EQUAL(3, retangulo2->largura);
    TEST_ASSERT_EQUAL(3, retangulo2->altura);
}

void test_moverUmRetanguloParaADireitaAteOLimiteEVerificarQueNaoUltrapassa(void) {
    Retangulo *retangulo = criarRetangulo(75, 3, 5, 5);
    moverDireita(75, 1, 5);
    TEST_ASSERT_EQUAL(75, retangulo->x);
    TEST_ASSERT_EQUAL(1, retangulo->y);
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
    TEST_ASSERT_EQUAL(1, contadorRetangulos);
    TEST_ASSERT_EQUAL(1, retangulos[0].x);
    TEST_ASSERT_EQUAL(1, retangulos[0].y);
    TEST_ASSERT_EQUAL(12, retangulos[0].largura);
    TEST_ASSERT_EQUAL(5, retangulos[0].altura);

    executarComando("moveright 1,1+5");
    TEST_ASSERT_EQUAL(6, retangulos[0].x);
    TEST_ASSERT_EQUAL(1, retangulos[0].y);
    TEST_ASSERT_EQUAL(12, retangulos[0].largura);
    TEST_ASSERT_EQUAL(5, retangulos[0].altura);

    executarComando("moveleft 6,1+5");
    TEST_ASSERT_EQUAL(1, retangulos[0].x);
    TEST_ASSERT_EQUAL(1, retangulos[0].y);
    TEST_ASSERT_EQUAL(12, retangulos[0].largura);
    TEST_ASSERT_EQUAL(5, retangulos[0].altura);

    executarComando("create 15,3+12,5");
    TEST_ASSERT_EQUAL(2, contadorRetangulos);
    TEST_ASSERT_EQUAL(15, retangulos[1].x);
    TEST_ASSERT_EQUAL(1, retangulos[1].y);
    TEST_ASSERT_EQUAL(12, retangulos[1].largura);
    TEST_ASSERT_EQUAL(5, retangulos[1].altura);

    executarComando("moveright 15,1+5");
    TEST_ASSERT_EQUAL(20, retangulos[1].x);
    TEST_ASSERT_EQUAL(1, retangulos[1].y);
    TEST_ASSERT_EQUAL(12, retangulos[1].largura);
    TEST_ASSERT_EQUAL(5, retangulos[1].altura);

    executarComando("moveleft 20,1+5");
    TEST_ASSERT_EQUAL(15, retangulos[1].x);
    TEST_ASSERT_EQUAL(1, retangulos[1].y);
    TEST_ASSERT_EQUAL(12, retangulos[1].largura);
    TEST_ASSERT_EQUAL(5, retangulos[1].altura);

    executarComando("create 26,8+12,5");
    TEST_ASSERT_EQUAL(3, contadorRetangulos);
    TEST_ASSERT_EQUAL(26, retangulos[2].x);
    TEST_ASSERT_EQUAL(6, retangulos[2].y);
    TEST_ASSERT_EQUAL(12, retangulos[2].largura);

    executarComando("moveright 26,6+5");
    TEST_ASSERT_EQUAL(31, retangulos[2].x);
    TEST_ASSERT_EQUAL(1, retangulos[2].y);
    TEST_ASSERT_EQUAL(12, retangulos[2].largura);
    TEST_ASSERT_EQUAL(5, retangulos[2].altura);

    executarComando("moveleft 31,1+5");
    TEST_ASSERT_EQUAL(31, retangulos[2].x);
    TEST_ASSERT_EQUAL(1, retangulos[2].y);
    TEST_ASSERT_EQUAL(12, retangulos[2].largura);
    TEST_ASSERT_EQUAL(5, retangulos[2].altura);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_criarRetanguloForaLimites);
    RUN_TEST(test_aposCriarNovoRetanguloEsteFicaSalvoNoArray);
    RUN_TEST(test_criarDoisRetangulosDistintosAdicionaNoArrayENaoModificaORetanguloExistente);
    RUN_TEST(test_criar3RetangulosSendoQueUmDelesInterseccionaComOsOutros);
    RUN_TEST(test_interseta);
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

    // RUN_TEST(test_criar3RetangulosComDiferentesAlturasEscreverNoEcraParaConsultaDoCenario);
    return UNITY_END();
}

