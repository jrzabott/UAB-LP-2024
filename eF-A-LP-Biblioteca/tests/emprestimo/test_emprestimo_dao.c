#include "unity.h"
#include "../../include/emprestimo/emprestimo_dao.h"
#include "../../include/emprestimo/emprestimo.h"
#include "../../include/utilizador/utilizador.h"
#include "../../include/livro/livro.h"

#define TEST_CSV_PATH "test_emprestimos.csv"

void setUp(void) {
    inicializarEmprestimos();
    inicializarUtilizadores();
    inicializarLivros();

    // Criar dados de teste para utilizadores e livros
    Utilizador user1 = {201, "João Silva", "joao@example.com", 0};
    Utilizador user2 = {202, "Ana Pereira", "ana@example.com", 0};
    adicionarUtilizador(user1);
    adicionarUtilizador(user2);

    Livro book1 = {101, "Código Limpo", "Robert C. Martin", "Programação", 5, 5};
    Livro book2 = {102, "O Programador Pragmático", "Andrew Hunt", "Programação", 5, 5};
    adicionarLivro(book1);
    adicionarLivro(book2);
}

void tearDown(void) {
    liberarGestaoEmprestimos();
    liberarMemoriaLivros();
    liberarMemoriaUtilizadores();
    remove(TEST_CSV_PATH);  // Remove o arquivo de teste para evitar poluição
}

void test_carregarEmprestimosDeCSV(void) {
    // Configura um CSV de teste com conteúdo conhecido que depende de utilizadores e livros válidos
    FILE *file = fopen(TEST_CSV_PATH, "w+");
    fprintf(file, "1,101,201,1622494800,1622581200,1622678400\n");
    fprintf(file, "2,102,202,1622494800,1622581200,1622678400\n");
    fclose(file);

    // Testa carregar empréstimos do CSV
    carregarEmprestimosDeCSV(TEST_CSV_PATH);
    // Verificar se os empréstimos foram carregados corretamente
    TEST_ASSERT_EQUAL(2, gestao->totalEmprestimos); // Verifica se dois empréstimos foram carregados
    // Verificar se conteudo carregado esta correto
    TEST_ASSERT_EQUAL(1, gestao->emprestimos[0].idEmprestimo);
    TEST_ASSERT_EQUAL(101, gestao->emprestimos[0].idLivro);
    TEST_ASSERT_EQUAL(201, gestao->emprestimos[0].idUtilizador);
    TEST_ASSERT_EQUAL(1622494800, gestao->emprestimos[0].dataEmprestimo);
    TEST_ASSERT_EQUAL(1622581200, gestao->emprestimos[0].dataDevolucaoPrevista);
    TEST_ASSERT_EQUAL(1622678400, gestao->emprestimos[0].dataDevolucaoReal);
    TEST_ASSERT_EQUAL(2, gestao->emprestimos[1].idEmprestimo);
    TEST_ASSERT_EQUAL(102, gestao->emprestimos[1].idLivro);
    TEST_ASSERT_EQUAL(202, gestao->emprestimos[1].idUtilizador);
    TEST_ASSERT_EQUAL(1622494800, gestao->emprestimos[1].dataEmprestimo);
    TEST_ASSERT_EQUAL(1622581200, gestao->emprestimos[1].dataDevolucaoPrevista);
    TEST_ASSERT_EQUAL(1622678400, gestao->emprestimos[1].dataDevolucaoReal);
}

void test_guardarEmprestimosEmCSV(void) {
    // Configura estado do sistema para ser salvo
    Emprestimo e1 = {1, 101, 201, 1622494800, 1622581200, 1622678400};
    Emprestimo e2 = {2, 102, 202, 1622494800, 1622581200, 1622678400};
    adicionarEmprestimo(e1);
    adicionarEmprestimo(e2);

    // Testa salvar o estado em um CSV
    guardarEmprestimosEmCSV(TEST_CSV_PATH);

    // Reabre o arquivo para verificar conteúdo
    FILE *file = fopen(TEST_CSV_PATH, "r");
    char buffer[1024];
    int count = 0;
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        count++;
    }
    fclose(file);
    TEST_ASSERT_EQUAL(2, count);  // Verifica se dois empréstimos foram salvos corretamente
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_carregarEmprestimosDeCSV);
    RUN_TEST(test_guardarEmprestimosEmCSV);
    return UNITY_END();
}
