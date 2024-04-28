cmake_minimum_required(VERSION 3.10)
project(eF-A-LP-Biblioteca-Tests)

# Incluir o ficheiro de cabeçalho do projeto principal e o framework de testes Unity.
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(util/unity)

# Adicionar os ficheiros de código fonte do Unity e o ficheiro C necessarios para o teste.
add_executable(
        test_utilizador                     # Nome do executável de teste.
        util/unity/unity.c                  # Ficheiros necessario ao teste...
        ../include/utilizador/utilizador.h
        ../src/utilizador/utilizador.c
        utilizador/test_utilizador.c
)

add_executable(
        test_utilizador_dao                 # Nome do executável de teste.
        util/unity/unity.c                  # Ficheiros necessario ao teste...
        ../include/utilizador/utilizador.h
        ../include/utilizador/utilizador_dao.h
        ../src/utilizador/utilizador.c
        ../src/utilizador/utilizador_dao.c
        utilizador/test_utilizador_dao.c
)

add_executable(
        test_livro                          # Nome do executável de teste.
        util/unity/unity.c                  # Ficheiros necessario ao teste...
        ../include/livro/livro.h
        ../src/livro/livro.c
        livro/test_livro.c
)

# Especificar onde o executável de teste deve ser "built".
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")
# Adicionar a biblioteca de testes ao executável de teste.
enable_testing()

# Adicionar o executável de teste ao CTest.
add_test(NAME test_utilizador COMMAND test_utilizador)
add_test(NAME test_utilizador_dao COMMAND test_utilizador_dao)
add_test(NAME test_livro COMMAND test_livro)