cmake_minimum_required(VERSION 3.10)
project(colmeia)

# Set the C standard for the project.
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Localização dos arquivos de cabeçalho.
include_directories(
        src/
)

# Ficheiros de código fonte.
add_executable(
        colmeia      # Nome do executável
        src/2304335C.c
)

add_executable(
        tester      # Nome do executável
        src/tester.c
        src/2304335A.c
)

# Specify where the executable should be built.
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")
