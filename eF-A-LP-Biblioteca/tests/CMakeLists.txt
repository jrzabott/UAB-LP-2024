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

add_executable(
        test_livro_dao                       # Nome do executável de teste.
        util/unity/unity.c                   # Ficheiros necessario ao teste...
        ../include/livro/livro_dao.h
        ../src/livro/livro.c
        ../src/livro/livro_dao.c
        livro/test_livro_dao.c
)
add_executable(
        test_emprestimo                       # Nome do executável de teste.
        util/unity/unity.c                   # Ficheiros necessario ao teste...
        ../include/livro/livro.h
        ../include/utilizador/utilizador.h
        ../include/emprestimo/emprestimo.h
        ../src/livro/livro.c
        ../src/utilizador/utilizador.c
        ../src/emprestimo/emprestimo.c
        emprestimo/test_emprestimo.c
)

add_executable(
        test_emprestimo_dao                   # Nome do executável de teste.
        util/unity/unity.c                   # Ficheiros necessario ao teste...
        ../include/livro/livro.h
        ../include/utilizador/utilizador.h
        ../include/emprestimo/emprestimo.h
        ../include/emprestimo/emprestimo_dao.h
        ../src/livro/livro.c
        ../src/utilizador/utilizador.c
        ../src/emprestimo/emprestimo.c
        ../src/emprestimo/emprestimo_dao.c
        emprestimo/test_emprestimo_dao.c
)

add_executable(
        test_relatorio                   # Nome do executável de teste.
        util/unity/unity.c                   # Ficheiros necessario ao teste...
        ../include/livro/livro.h
        ../include/utilizador/utilizador.h
        ../include/emprestimo/emprestimo.h
        ../include/relatorio/relatorio.h
        ../src/livro/livro.c
        ../src/utilizador/utilizador.c
        ../src/emprestimo/emprestimo.c
        ../src/relatorio/relatorio.c
        relatorio/test_relatorio.c
)
add_executable(
        test_sistema                  # Nome do executável de teste.
        util/unity/unity.c                   # Ficheiros necessario ao teste...
        ../include/livro/livro.h
        ../include/livro/livro_dao.h
        ../include/utilizador/utilizador.h
        ../include/utilizador/utilizador_dao.h
        ../include/emprestimo/emprestimo.h
        ../include/emprestimo/emprestimo_dao.h
        ../include/relatorio/relatorio.h
        ../src/livro/livro.c
        ../src/livro/livro_dao.c
        ../src/utilizador/utilizador.c
        ../src/utilizador/utilizador_dao.c
        ../src/emprestimo/emprestimo.c
        ../src/emprestimo/emprestimo_dao.c
        ../src/relatorio/relatorio.c
        test_sistema.c
)

# Especificar onde o executável de teste deve ser "built".
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")
# Adicionar a biblioteca de testes ao executável de teste.
enable_testing()

# Adicionar o executável de teste ao CTest.
add_test(NAME test_utilizador COMMAND test_utilizador)
add_test(NAME test_utilizador_dao COMMAND test_utilizador_dao)
add_test(NAME test_livro COMMAND test_livro)
add_test(NAME test_livro_dao COMMAND test_livro_dao)
add_test(NAME test_emprestimo COMMAND test_emprestimo)
add_test(NAME test_emprestimo_dao COMMAND test_emprestimo_dao)
add_test(NAME test_relatorio COMMAND test_relatorio)
add_test(NAME test_sistema COMMAND test_sistema)