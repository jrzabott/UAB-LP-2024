#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINE_LENGTH 1024

// Function to compare the outputs line by line
bool compare_outputs(const char *expected_file, const char *actual_file) {
    FILE *expected = fopen(expected_file, "r");
    FILE *actual = fopen(actual_file, "r");

    if (!expected || !actual) {
        perror("Error opening files");
        return false;
    }

    char expected_line[MAX_LINE_LENGTH];
    char actual_line[MAX_LINE_LENGTH];
    int line_number = 0;

    while (fgets(expected_line, MAX_LINE_LENGTH, expected) && fgets(actual_line, MAX_LINE_LENGTH, actual)) {
        line_number++;
        if (strcmp(expected_line, actual_line) != 0) {
            printf("Mismatch at line %d:\n", line_number);
            printf("Expected: %s", expected_line);
            printf("Actual:   %s", actual_line);
            fclose(expected);
            fclose(actual);
            return false;
        }
    }

    // Check if both files have reached EOF
    bool both_eof = feof(expected) && feof(actual);
    if (!both_eof) {
        printf("Files have different lengths.\n");
    }

    fclose(expected);
    fclose(actual);
    return both_eof;
}

// Function to run the program and capture its output
void run_test(const char *input_file, const char *output_file, const char *program) {
    char command[MAX_LINE_LENGTH];
    snprintf(command, sizeof(command), "%s < %s > %s", program, input_file, output_file);
    system(command);
}

int main() {
    const char *program = "./bin/colmeia.exe"; // Path to your compiled executable
    const char *input_dir = "../../src/test_fixtures/input/";
    const char *expected_dir = "../../src/test_fixtures/output_expected/";
    const char *actual_dir = "../../src/test_fixtures/output_actual/";

    const char *test_cases[] = {
        "test1_input.txt",
        "test2_input.txt",
        "test3_input.txt",
        "test4_input.txt",
        "test5_input.txt",
        "test6_input.txt",
        "test7_input.txt",
        "test8_input.txt",
        "test9_input.txt",
        "test10_input.txt",
    };

    const char *expected_outputs[] = {
        "test1_expected.txt",
        "test2_expected.txt",
        "test3_expected.txt",
        "test4_expected.txt",
        "test5_expected.txt",
        "test6_expected.txt",
        "test7_expected.txt",
        "test8_expected.txt",
        "test9_expected.txt",
        "test10_expected.txt",
    };

    const size_t test_count = sizeof(test_cases) / sizeof(test_cases[0]);

    for (size_t i = 0; i < test_count; i++) {
        char input_file[MAX_LINE_LENGTH];
        char expected_file[MAX_LINE_LENGTH];
        char actual_output[MAX_LINE_LENGTH];

        snprintf(input_file, sizeof(input_file), "%s%s", input_dir, test_cases[i]);
        snprintf(expected_file, sizeof(expected_file), "%s%s", expected_dir, expected_outputs[i]);
        snprintf(actual_output, sizeof(actual_output), "%soutput_test%d.txt", actual_dir, (int)(i + 1));

        printf("Running Test %zu...\n", i + 1);
        run_test(input_file, actual_output, program);

        if (compare_outputs(expected_file, actual_output)) {
            printf("Test %zu passed.\n", i + 1);
        } else {
            printf("Test %zu failed.\n", i + 1);
        }
    }

    return 0;
}
