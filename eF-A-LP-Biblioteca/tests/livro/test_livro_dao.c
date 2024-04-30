#include "../util/unity/unity.h"
#include "../../include/livro/livro_dao.h"
#include "../../include/livro/livro.h"

// Função auxiliar para criar um arquivo CSV para testes
void criarArquivoCSVTeste(const char *nomeArquivo) {
    FILE *file = fopen(nomeArquivo, "w");
    if (file != NULL) {
        fprintf(file, "1,1984,George Orwell,Ficção,10,10\n");
        fprintf(file, "2,Brave New World,Aldous Huxley,Ficção,8,8\n");
        fprintf(file, "3,The Hobbit,J.R.R. Tolkien,Fantasia,15,15\n");
        fclose(file);
    }
}

void setUp(void) {
    inicializarLivros();
}

void tearDown(void) {
    liberarMemoriaLivros();
}

// Teste para carregar livros de um arquivo CSV válido
void test_carregarLivrosDeCSV_Valido(void) {
    criarArquivoCSVTeste("livros_valido.csv");
    carregarLivrosDeCSV("livros_valido.csv");
    TEST_ASSERT_EQUAL(3, totalLivros);
    TEST_ASSERT_EQUAL_STRING("1984", livros[0].titulo);
    TEST_ASSERT_EQUAL_STRING("George Orwell", livros[0].autor);
}

// Teste para verificar o comportamento com um arquivo CSV inválido
void test_carregarLivrosDeCSV_Invalido(void) {
    criarArquivoCSVTeste("livros_invalido.csv");
    // Adicionar dados inválidos intencionalmente
    FILE *file = fopen("livros_invalido.csv", "a");
    if (file != NULL) {
        fprintf(file, "4,,Missing Title,,5,3\n"); // Título faltando
        fclose(file);
    }
    carregarLivrosDeCSV("livros_invalido.csv");
    TEST_ASSERT_EQUAL(3, totalLivros); // Assume que apenas livros válidos anteriores foram carregados
}

// Teste de escrita e leitura para verificar a consistência dos dados
void test_gravacaoLeituraConsistencia(void) {
    Livro l = {4, "Sapiens", "Yuval Noah Harari", "História", 12, 12};
    adicionarLivro(l);
    guardarLivrosEmCSV("livros_consistencia.csv");
    liberarMemoriaLivros();  // Limpar a memória para simular reinicialização do programa

    setUp();
    carregarLivrosDeCSV("livros_consistencia.csv");
    TEST_ASSERT_EQUAL(1, totalLivros);
    TEST_ASSERT_EQUAL_STRING("Sapiens", livros[0].titulo);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_carregarLivrosDeCSV_Valido);
    RUN_TEST(test_carregarLivrosDeCSV_Invalido);
    RUN_TEST(test_gravacaoLeituraConsistencia);
    return UNITY_END();
}
