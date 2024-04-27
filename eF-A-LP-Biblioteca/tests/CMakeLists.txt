cmake_minimum_required(VERSION 3.10)
project(eF-A-LP-Biblioteca-Tests)

# Include the main project's header files and Unity test framework.
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(util/unity)

# Add Unity source files and the test file.
add_executable(runTests
        util/unity/unity.c
        ../include/utilizador/utilizador.h
        ../src/utilizador/utilizador.c
        utilizador/test_utilizador.c
)

# Specify where the test executable should be built.
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")
