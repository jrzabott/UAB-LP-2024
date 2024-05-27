cmake_minimum_required(VERSION 3.10)
project(eF-B-LP-MundoRetangulos-Tests)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/unity)
include_directories(${PROJECT_SOURCE_DIR}/../src)

# Add the executable for tests
add_executable(
        testMundoRetangulos
        ${PROJECT_SOURCE_DIR}/unity/unity.c       # Unity framework source
        ${PROJECT_SOURCE_DIR}/../src/mundoRetangulos.c # Main source file
        ${PROJECT_SOURCE_DIR}/testMundoRetangulos.c # Test source file
)

# Set the output directory for the executable
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

# Enable testing
enable_testing()

# Add the test
add_test(NAME testMundoRetangulos COMMAND testMundoRetangulos)