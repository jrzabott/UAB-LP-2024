#include "../util/unity/unity.h"
#include "../../include/livro/livro.h"
#include <string.h>

void setUp(void) {
    inicializarLivros();
}

void tearDown(void) {
    liberarMemoriaLivros();
}

void test_adicionarLivro(void) {
    Livro l = {1, "1984", "George Orwell", "Ficção", 10, 10};
    adicionarLivro(l);
    TEST_ASSERT_EQUAL(1, totalLivros);
    TEST_ASSERT_EQUAL_STRING("1984", livros[0].titulo);

    // Testar a realocação
    for (int i = 1; i < 15; i++) {
        l.idLivro = i + 1;
        adicionarLivro(l);
    }
    TEST_ASSERT_EQUAL(15, totalLivros);
}

void test_atualizarLivro(void) {
    Livro l = {1, "1984", "George Orwell", "Ficção", 10, 10};
    adicionarLivro(l);
    l.titulo = "1984 (Edição Especial)";
    l.autor = "George Orwell Jr.";
    l.genero = "Ficção Científica";
    l.exemplaresTotal = 15;
    l.exemplaresDisponiveis = 15;
    atualizarLivro(l);
    TEST_ASSERT_EQUAL_STRING("1984 (Edição Especial)", livros[0].titulo);
    TEST_ASSERT_EQUAL_STRING("George Orwell Jr.", livros[0].autor);
    TEST_ASSERT_EQUAL_STRING("Ficção Científica", livros[0].genero);
    TEST_ASSERT_EQUAL(15, livros[0].exemplaresTotal);
    TEST_ASSERT_EQUAL(15, livros[0].exemplaresDisponiveis);
}

void test_listarLivrosDisponiveis(void) {
    Livro l1 = {1, "1984", "George Orwell", "Ficção", 10, 10};
    Livro l2 = {2, "Animal Farm", "George Orwell", "Ficção", 5, 0};
    Livro l3 = {3, "Brave New World", "Aldous Huxley", "Ficção", 3, 5};
    adicionarLivro(l1);
    adicionarLivro(l2);
    adicionarLivro(l3);
    listarLivrosDisponiveis();
}

void test_listarTodosOsLivros(void) {
    Livro l1 = {1, "1984", "George Orwell", "Ficção", 10, 10};
    Livro l2 = {2, "Animal Farm", "George Orwell", "Ficção", 5, 0};
    Livro l3 = {3, "Brave New World", "Aldous Huxley", "Ficção", 3, 5};
    adicionarLivro(l1);
    adicionarLivro(l2);
    adicionarLivro(l3);
    listarTodosOsLivros();
}

void test_removerLivro(void) {
    Livro l = {1, "1984", "George Orwell", "Ficção", 10, 10};
    adicionarLivro(l);
    removerLivro(1);
    TEST_ASSERT_EQUAL(0, totalLivros);

    // Tentar remover um livro que não existe
    removerLivro(2);
    TEST_ASSERT_EQUAL(0, totalLivros);
}

void test_buscarLivrosPorTitulo(void) {
    Livro l1 = {1, "1984", "George Orwell", "Ficção", 10, 10};
    Livro l2 = {2, "1984", "Outro Autor", "Ficção", 5, 5};
    adicionarLivro(l1);
    adicionarLivro(l2);

    int livros_encontrados = 0;  // Esta variável armazenará o número de resultados
    Livro **found = buscarLivrosPorTitulo("1984", &livros_encontrados);  // Passa o endereço de 'count'

    TEST_ASSERT_EQUAL(2, livros_encontrados);  // Verifica se o número correto de livros foi retornado
    TEST_ASSERT_EQUAL_STRING("1984", found[0]->titulo);
    TEST_ASSERT_EQUAL_STRING("1984", found[1]->titulo);
}

void test_buscarLivrosPorAutor(void) {
    Livro l1 = {1, "1984", "George Orwell", "Ficção", 10, 10};
    Livro l2 = {2, "Animal Farm", "George Orwell", "Ficção", 5, 5};
    adicionarLivro(l1);
    adicionarLivro(l2);

    int count = 0;
    Livro **found = buscarLivrosPorAutor("George Orwell", &count);

    TEST_ASSERT_EQUAL(2, count);
    TEST_ASSERT_EQUAL_STRING("George Orwell", found[0]->autor);
    TEST_ASSERT_EQUAL_STRING("George Orwell", found[1]->autor);

    // Teste para autor que não existe
    found = buscarLivrosPorAutor("Aldous Huxley", &count);
    TEST_ASSERT_EQUAL(0, count);
}

void test_buscarLivrosPorGenero(void) {
    Livro l1 = {1, "1984", "George Orwell", "Ficção", 10, 10};
    Livro l2 = {2, "Brave New World", "Aldous Huxley", "Ficção", 5, 5};
    adicionarLivro(l1);
    adicionarLivro(l2);

    int count = 0;
    Livro **found = buscarLivrosPorGenero("Ficção", &count);

    TEST_ASSERT_EQUAL(2, count);
    TEST_ASSERT_EQUAL_STRING("Ficção", found[0]->genero);
    TEST_ASSERT_EQUAL_STRING("Ficção", found[1]->genero);

    // Teste para gênero que não existe
    found = buscarLivrosPorGenero("História", &count);
    TEST_ASSERT_EQUAL(0, count);
}

void test_buscarLivroPorId(void) {
    Livro l1 = {1, "1984", "George Orwell", "Ficção", 10, 10};
    adicionarLivro(l1);
    Livro *found = buscarLivroPorId(1);
    TEST_ASSERT_NOT_NULL(found);
    TEST_ASSERT_EQUAL_STRING("1984", found->titulo);

    // Teste para livro que não existe
    found = buscarLivroPorId(2);
    TEST_ASSERT_NULL(found);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_adicionarLivro);
    RUN_TEST(test_removerLivro);
    RUN_TEST(test_buscarLivrosPorTitulo);
    RUN_TEST(test_buscarLivrosPorAutor);
    RUN_TEST(test_buscarLivrosPorGenero);
    RUN_TEST(test_atualizarLivro);
    RUN_TEST(test_listarLivrosDisponiveis);
    RUN_TEST(test_listarTodosOsLivros);
    RUN_TEST(test_buscarLivroPorId);
    return UNITY_END();
}
