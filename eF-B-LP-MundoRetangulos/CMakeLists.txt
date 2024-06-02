cmake_minimum_required(VERSION 3.10)
project(eF-B-LP-MundoRetangulos)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/src)

# Add the executable for the main application
add_executable(
        mainMundoRetangulos
        ${PROJECT_SOURCE_DIR}/src/mundoRetangulos.c # Main source file
)

# Set the output directory for the executable
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

# Add the executable for the test
add_executable(
        testMundoRetangulos
        ${PROJECT_SOURCE_DIR}/tests/unity/unity.c       # Unity framework source
        ${PROJECT_SOURCE_DIR}/src/mundoRetangulos.c # Main source file
        ${PROJECT_SOURCE_DIR}/tests/testMundoRetangulos.c # Test source file
)

# Add the RUN_TESTS definition to the test target
target_compile_definitions(testMundoRetangulos PRIVATE RUN_TESTS)
