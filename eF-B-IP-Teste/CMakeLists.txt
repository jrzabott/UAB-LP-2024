cmake_minimum_required(VERSION 3.10)
project(eF-A-LP-Biblioteca)

# Set the C standard for the project.
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Localização dos arquivos de cabeçalho.
include_directories(
        src/
)

# Ficheiros de código fonte.
add_executable(
        teste_sensor      # Nome do executável
        src/main.c          # Arquivo principal
        src/TipoVeiculo.c
        src/TipoVeiculo.h
        src/RegistoSensor.c
        src/RegistoSensor.h
)

# Specify where the executable should be built.
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")
