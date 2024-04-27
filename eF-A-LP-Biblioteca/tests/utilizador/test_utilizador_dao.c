#include "unity.h"
#include "../../include/utilizador/utilizador_dao.h"
#include <string.h>
#include <stdlib.h>

void setUp(void) {
    inicializarUtilizadores();
}

void tearDown(void) {
    free(listaUtilizadores);
    listaUtilizadores = NULL;
    totalUtilizadores = 0;
}

void test_carregarUtilizadoresDeCSV_NaoExiste(void) {
    carregarUtilizadoresDeCSV("arquivo_nao_existente.csv");
    TEST_ASSERT_EQUAL(0, totalUtilizadores); // Espera-se que nenhum utilizador seja carregado
}

void test_guardarUtilizadoresEmCSV_FalhaAoSalvar(void) {
    // Simular uma situação onde o arquivo não pode ser aberto para escrita
    Utilizador u = {1, "Maria João", "maria.joao@example.com", 3};
    adicionarUtilizador(u);
    guardarUtilizadoresEmCSV("/caminho/invalido/test_saida.csv");
    // Não há uma forma simples de testar a falha de escrita sem verificar logs ou mensagens de erro
    // Esta parte do teste é mais sobre garantir que a função de manipulação de erro esteja em lugar
}

void test_EscritaELeitura_Consistencia(void) {
    // Criando e adicionando utilizadores
    Utilizador u1 = {1, "Maria João", "maria.joao@example.com", 3};
    Utilizador u2 = {2, "José Silva", "jose.silva@example.com", 1};
    adicionarUtilizador(u1);
    adicionarUtilizador(u2);

    // Escrevendo para o arquivo
    guardarUtilizadoresEmCSV("test_utilizadores_temp.csv");

    // Limpando a lista atual e recarregando do arquivo
    tearDown();
    setUp();
    carregarUtilizadoresDeCSV("test_utilizadores_temp.csv");

    // Verificações
    TEST_ASSERT_EQUAL(2, totalUtilizadores);
    TEST_ASSERT_EQUAL_STRING("Maria João", listaUtilizadores[0].nome);
    TEST_ASSERT_EQUAL_STRING("José Silva", listaUtilizadores[1].nome);
}

void test_carregarUtilizadoresDeCSV_MalFormatado(void) {
    // O conteúdo do arquivo mal formatado (simulação)
    // Escreve-se intencionalmente um conteúdo mal formatado para um arquivo
    FILE *file = fopen("test_utilizadores_malformatado.csv", "w");
    fprintf(file, "1,Maria João,maria.joao@example.com,Três\n");  // 'Três' deveria ser um número
    fclose(file);

    carregarUtilizadoresDeCSV("test_utilizadores_malformatado.csv");
    TEST_ASSERT_EQUAL(0, totalUtilizadores); // Deve falhar ao carregar dados mal formatados
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_carregarUtilizadoresDeCSV_NaoExiste);
    RUN_TEST(test_carregarUtilizadoresDeCSV_MalFormatado);
    RUN_TEST(test_guardarUtilizadoresEmCSV_FalhaAoSalvar);
    RUN_TEST(test_EscritaELeitura_Consistencia);
    return UNITY_END();
}
