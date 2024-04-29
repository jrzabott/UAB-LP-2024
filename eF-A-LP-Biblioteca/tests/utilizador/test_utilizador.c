#include "../util/unity/unity.h"
#include "../../include/utilizador/utilizador.h"
#include <string.h>
#include <stdlib.h>

void setUp(void) {
    // Função que é chamada antes de cada teste
    inicializarUtilizadores();
}

void tearDown(void) {
    // Função que é chamada após cada teste
    liberarMemoriaUtilizadores();
}

void test_adicionarUtilizador(void) {
    Utilizador u = {1, "João Silva", "joao.silva@example.com", 0};
    adicionarUtilizador(u);
    TEST_ASSERT_EQUAL(1, totalUtilizadores);
    TEST_ASSERT_EQUAL_STRING("João Silva", listaUtilizadores[0].nome);
}

void test_removerUtilizador(void) {
    Utilizador u1 = {1, "João Silva", "joao.silva@example.com", 0};
    Utilizador u2 = {2, "Maria João", "maria.joao@example.com", 0};
    adicionarUtilizador(u1);
    adicionarUtilizador(u2);
    removerUtilizador(1);
    TEST_ASSERT_EQUAL(1, totalUtilizadores);
    TEST_ASSERT_EQUAL_STRING("Maria João", listaUtilizadores[0].nome);
}

void test_atualizarUtilizador(void) {
    Utilizador u = {1, "João Silva", "joao.silva@example.com", 0};
    adicionarUtilizador(u);
    u.nome = "João Pereira Silva";
    u.email = "joao.pereira@example.com";
    atualizarUtilizador(u);
    TEST_ASSERT_EQUAL_STRING("João Pereira Silva", listaUtilizadores[0].nome);
    TEST_ASSERT_EQUAL_STRING("joao.pereira@example.com", listaUtilizadores[0].email);
}

void test_buscarUtilizadorPorNome(void) {
    Utilizador u = {1, "João Silva", "joao.silva@example.com", 0};
    adicionarUtilizador(u);
    Utilizador *resultado = buscarUtilizadorPorNome("João Silva");
    TEST_ASSERT_NOT_NULL(resultado);
    TEST_ASSERT_EQUAL_STRING("João Silva", resultado->nome);
}

void test_listarTodosOsUtilizadores(void) {
    Utilizador u1 = {1, "João Silva", "joao.silva@example.com", 0};
    Utilizador u2 = {2, "Maria João", "maria.joao@example.com", 0};
    adicionarUtilizador(u1);
    adicionarUtilizador(u2);
    listarTodosOsUtilizadores();  // Verifique a saída manualmente ou use mocks
}

// Teste para verificar se um utilizador existente é encontrado
void test_buscarUtilizadorPorId_Existente(void) {
    Utilizador u1 = {1, "João Silva", "email", 0};
    adicionarUtilizador(u1);
    Utilizador *u = buscarUtilizadorPorId(1);
    TEST_ASSERT_NOT_NULL(u);
    TEST_ASSERT_EQUAL(1, u->idUtilizador);
    TEST_ASSERT_EQUAL_STRING("João Silva", u->nome);
}

// Teste para verificar se retorna NULL quando nenhum utilizador é encontrado
void test_buscarUtilizadorPorId_Inexistente(void) {
    Utilizador *u = buscarUtilizadorPorId(999);
    TEST_ASSERT_NULL(u);
}

// Teste para verificar se utilizadorExiste retorna verdadeiro para um utilizador existente
void test_utilizadorExiste_Existente(void) {
    Utilizador u1 = {1, "João Silva", "email", 0};
    adicionarUtilizador(u1);
    int existe = utilizadorExiste(1);
    TEST_ASSERT_TRUE(existe);
}

// Teste para verificar se utilizadorExiste retorna falso para um utilizador que não existe
void test_utilizadorExiste_Inexistente(void) {
    int existe = utilizadorExiste(999);
    TEST_ASSERT_FALSE(existe);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_adicionarUtilizador);
    RUN_TEST(test_removerUtilizador);
    RUN_TEST(test_atualizarUtilizador);
    RUN_TEST(test_buscarUtilizadorPorNome);
    RUN_TEST(test_listarTodosOsUtilizadores);
    RUN_TEST(test_buscarUtilizadorPorId_Existente);
    RUN_TEST(test_buscarUtilizadorPorId_Inexistente);
    RUN_TEST(test_utilizadorExiste_Existente);
    RUN_TEST(test_utilizadorExiste_Inexistente);
    return UNITY_END();
}
