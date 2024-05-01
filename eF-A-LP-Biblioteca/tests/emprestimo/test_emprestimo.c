#include "unity.h"
#include "../../include/emprestimo/emprestimo.h"
#include <string.h>

void setUp(void) {
    inicializarUtilizadores();
    inicializarLivros();
    inicializarEmprestimos();

    //Adicionar Livro e Utilizador
    Livro l = {101, "1984", "George Orwell", "Ficção", 10, 10};
    adicionarLivro(l);
    Utilizador u = {201, "João Silva", "email", 0};
    adicionarUtilizador(u);
}

void tearDown(void) {
    liberarGestaoEmprestimos();
    liberarMemoriaLivros();
    liberarMemoriaUtilizadores();
}

void test_inicializacao(void) {
    TEST_ASSERT_NOT_NULL(gestao->emprestimos);
    TEST_ASSERT_EQUAL(0, gestao->totalEmprestimos);
    TEST_ASSERT_EQUAL(10, gestao->capacidadeEmprestimos);
}

void test_adicionarEmprestimo_Valido(void) {
    Livro l = {101, "1984", "George Orwell", "Ficção", 10, 10};
    adicionarLivro(l);
    Utilizador u = {201, "João Silva", "email", 0};
    adicionarUtilizador(u);
    Emprestimo e = {1, 101, 201, time(NULL), time(NULL) + 86400, 0};
    adicionarEmprestimo(e);

    TEST_ASSERT_EQUAL(1, gestao->totalEmprestimos);
    TEST_ASSERT_EQUAL(101, gestao->emprestimos[0].idLivro);
}

void test_actualizarDevolucaoEmprestimo_Existente(void) {
    Emprestimo e = {1, 101, 201, time(NULL), time(NULL) + 86400, 0};
    adicionarEmprestimo(e);
    time_t novaData = time(NULL) + 172800; // Adiciona dois dias
    actualizarDevolucaoEmprestimo(1, novaData);
    TEST_ASSERT_EQUAL(novaData, gestao->emprestimos[0].dataDevolucaoReal);
}

void test_renovarEmprestimo_Existente(void) {
    Emprestimo e = {1, 101, 201, time(NULL), time(NULL) + 86400, 0};
    adicionarEmprestimo(e);
    renovarEmprestimo(1, 2); // Renova por mais 2 dias
    TEST_ASSERT_EQUAL(time(NULL) + 86400 * 3, gestao->emprestimos[0].dataDevolucaoPrevista);
}

void test_finalizarEmprestimo_Existente(void) {
    Emprestimo e = {1, 101, 201, time(NULL), time(NULL) + 86400, 0};
    adicionarEmprestimo(e);
    finalizarEmprestimo(1);
    TEST_ASSERT(time(NULL) - gestao->emprestimos[0].dataDevolucaoReal < 5); // Deve finalizar quase imediatamente
}

void test_listarEmprestimosActivos_NenhumDevolvido(void) {
    // Adicionar livro com Id:1022 e utilizador com Id:202
    Livro l = {102, "Brave New World", "Aldous Huxley", "Ficção", 8, 8};
    adicionarLivro(l);
    Utilizador u = {202, "Maria João", "email", 0};
    adicionarUtilizador(u);

    Emprestimo e1 = {1, 101, 201, time(NULL), time(NULL) + 86400, 0};
    Emprestimo e2 = {2, 102, 202, time(NULL), time(NULL) + 86400, 0};
    adicionarEmprestimo(e1);
    adicionarEmprestimo(e2);
    // A implementação real de listarEmprestimosActivos deve ser alterada para testar o output
    // Considerar armazenar output em uma string e verificar aqui
}

void test_actualizarDevolucaoEmprestimo_Inexistente(void) {
    time_t novaData = time(NULL) + 172800; // Dois dias adicionais
    actualizarDevolucaoEmprestimo(999, novaData); // ID que não existe
    // Esperamos que não altere nenhum empréstimo
    TEST_ASSERT_EQUAL(0, gestao->totalEmprestimos);
}

void test_renovarEmprestimo_Inexistente(void) {
    renovarEmprestimo(999, 2); // ID que não existe
    // Esperamos que não altere nenhum empréstimo
    TEST_ASSERT_EQUAL(0, gestao->totalEmprestimos);
}

void test_finalizarEmprestimo_JaDevolvido(void) {
    // Adiciona um empréstimo ja finalizado com a data de devolução real igual
    // a data atual mais 86400 segundos (1 dia)
    Emprestimo e = {1, 101, 201, time(NULL), time(NULL) + 86400, time(NULL)};
    adicionarEmprestimo(e);
    finalizarEmprestimo(1); // Tentar finalizar novamente
    // Checar se a data de devolução real não mudou
    TEST_ASSERT(time(NULL) - gestao->emprestimos[0].dataDevolucaoReal < 5);
}

void test_RedimensionamentoArray(void) {
    liberarMemoriaUtilizadores(); // necessario pois metodo setUp adicionar dois utilizadores por defeito.
    inicializarUtilizadores();
    liberarMemoriaLivros(); // da mesma forma
    inicializarLivros();

    for (int i = 0; i < 20; i++) {  // Adiciona mais empréstimos do que a capacidade inicial de 10
        // para cada iteracao, precisamos de um novo livro e um novo utilizador
        Livro l = {100+i, "Livro", "Autor", "Categoria", 10, 10};
        adicionarLivro(l);
        Utilizador u = {200+i, "Utilizador", "email", 0};
        adicionarUtilizador(u);

        Emprestimo e = {i, 100+i, 200+i, time(NULL), time(NULL) + 86400, 0};
        adicionarEmprestimo(e);
    }
    TEST_ASSERT_EQUAL(20, gestao->totalEmprestimos);
    TEST_ASSERT(gestao->capacidadeEmprestimos >= 20);
}

void test_ConsistenciaOperacoes(void) {
    Emprestimo e = {1, 101, 201, time(NULL), time(NULL) + 86400, 0};
    adicionarEmprestimo(e);
    renovarEmprestimo(1, 1); // Renova por mais 1 dia
    finalizarEmprestimo(1);

    Livro l = {102, "Brave New World", "Aldous Huxley", "Ficção", 8, 8};
    adicionarLivro(l);
    Utilizador u = {202, "Maria João", "email", 0};
    adicionarUtilizador(u);

    Emprestimo e2 = {2, 102, 202, time(NULL), time(NULL) + 86400, 0};
    adicionarEmprestimo(e2);
    TEST_ASSERT_EQUAL(2, gestao->totalEmprestimos);
    TEST_ASSERT_EQUAL(time(NULL) + 86400 * 2, gestao->emprestimos[0].dataDevolucaoPrevista);
    TEST_ASSERT(time(NULL) - gestao->emprestimos[0].dataDevolucaoReal < 5);
}

// Testa empréstimo para um utilizador que não existe
void test_emprestimoParaUtilizadorInexistente(void) {
    Emprestimo e = {1, 101, 9999, time(NULL), time(NULL) + 86400, 0};  // 9999: ID de utilizador inexistente
    int resultado = adicionarEmprestimo(e);
    TEST_ASSERT_EQUAL(-1, resultado);  // Falha esperada na adição do empréstimo
    TEST_ASSERT_EQUAL(0, gestao->totalEmprestimos);  // Nenhum empréstimo deve ser adicionado
}

// Testa empréstimo para um livro sem disponibilidade
void test_emprestimoParaLivroSemDisponibilidade(void) {
    Emprestimo e = {2, 102, 201, time(NULL), time(NULL) + 86400, 0};  // 102: ID de um livro sem exemplares disponíveis
    int resultado = adicionarEmprestimo(e);
    TEST_ASSERT_EQUAL(-1, resultado);  // Falha esperada na adição do empréstimo
    TEST_ASSERT_EQUAL(0, gestao->totalEmprestimos);  // Nenhum empréstimo deve ser adicionado
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_inicializacao);
    RUN_TEST(test_adicionarEmprestimo_Valido);
    RUN_TEST(test_actualizarDevolucaoEmprestimo_Existente);
    RUN_TEST(test_renovarEmprestimo_Existente);
    RUN_TEST(test_finalizarEmprestimo_Existente);
    RUN_TEST(test_listarEmprestimosActivos_NenhumDevolvido);
    RUN_TEST(test_actualizarDevolucaoEmprestimo_Inexistente);
    RUN_TEST(test_renovarEmprestimo_Inexistente);
    RUN_TEST(test_finalizarEmprestimo_JaDevolvido);
    RUN_TEST(test_RedimensionamentoArray);
    RUN_TEST(test_ConsistenciaOperacoes);
    return UNITY_END();
}
