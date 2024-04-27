cmake_minimum_required(VERSION 3.10)
project(eF-A-LP-Biblioteca)

# Set the C standard for the project.
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Localização dos arquivos de cabeçalho.
include_directories(
        include
        include/emprestimo
        include/livro
        include/utilizador
)

# Ficheiros de código fonte.
add_executable(
        main        # Nome do executável
        src/main.c  # Arquivo principal
        src/utilizador/utilizador.c
        src/utilizador/utilizador_dao.c
)

# Specify where the executable should be built.
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")
