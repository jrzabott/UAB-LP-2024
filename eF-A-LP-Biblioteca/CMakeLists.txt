cmake_minimum_required(VERSION 3.10)
project(eF-A-LP-Biblioteca)

# Set the C standard for the project.
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Add the headers location to your project.
include_directories(include)

# Add source files.
#add_executable(eF-A-LP-Biblioteca src/main.c)

# Specify where the executable should be built.
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")
