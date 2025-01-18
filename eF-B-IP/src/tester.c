#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>

#define INPUT_DIR "/Users/jrzab/CLionProjects/UAB-LP-2024/eF-B-IP/src/test_fixtures/input"
#define EXPECTED_DIR "/Users/jrzab/CLionProjects/UAB-LP-2024/eF-B-IP/src/test_fixtures/output_expected/"
#define ACTUAL_DIR "/Users/jrzab/CLionProjects/UAB-LP-2024/eF-B-IP/src/test_fixtures/output_actual/"
#define MAX_LINE_LENGTH 1024

void ensure_directory_exists(const char *directory) {
    DIR *dir = opendir(directory);
    if (!dir) {
        if (errno == ENOENT) {
            fprintf(stderr, "[ERROR] Directory '%s' does not exist.\n", directory);
            exit(EXIT_FAILURE);
        } else {
            perror("[ERROR] Failed to open directory");
            exit(EXIT_FAILURE);
        }
    }
    closedir(dir);
}

void compare_files(const char *expected_file, const char *actual_file, const char *test_name) {
    FILE *expected = fopen(expected_file, "r");
    FILE *actual = fopen(actual_file, "r");

    if (!expected || !actual) {
        fprintf(stderr, "[ERROR] Unable to open files for comparison: %s or %s\n", expected_file, actual_file);
        exit(EXIT_FAILURE);
    }

    char expected_line[MAX_LINE_LENGTH], actual_line[MAX_LINE_LkENGTH];
    int line_number = 1;
    int differences_found = 0;

    while (fgets(expected_line, MAX_LINE_LENGTH, expected) && fgets(actual_line, MAX_LINE_LENGTH, actual)) {
        if (strcmp(expected_line, actual_line) != 0) {
            printf("[DIFF] Test: %s | Line: %d\n", test_name, line_number);
            printf("Expected: %s", expected_line);
            printf("Actual  : %s", actual_line);
            differences_found = 1;
        }
        line_number++;
    }

    // Check for extra lines in either file
    while (fgets(expected_line, MAX_LINE_LENGTH, expected)) {
        printf("[DIFF] Test: %s | Line: %d\n", test_name, line_number);
        printf("Expected: %s", expected_line);
        printf("Actual  : (no line)\n");
        differences_found = 1;
        line_number++;
    }

    while (fgets(actual_line, MAX_LINE_LENGTH, actual)) {
        printf("[DIFF] Test: %s | Line: %d\n", test_name, line_number);
        printf("Expected: (no line)\n");
        printf("Actual  : %s", actual_line);
        differences_found = 1;
        line_number++;
    }

    if (!differences_found) {
        printf("[INFO] Test: %s | No differences found.\n", test_name);
    }

    fclose(expected);
    fclose(actual);
}

void process_test_files() {
    struct dirent *entry;
    DIR *input_dir = opendir(INPUT_DIR);

    if (!input_dir) {
        perror("[ERROR] Failed to open input directory");
        exit(EXIT_FAILURE);
    }

    while ((entry = readdir(input_dir)) != NULL) {
        if (strstr(entry->d_name, "_input.txt")) {
            char test_name[256];
            strncpy(test_name, entry->d_name, strstr(entry->d_name, "_input.txt") - entry->d_name);
            test_name[strstr(entry->d_name, "_input.txt") - entry->d_name] = '\0';

            // Build file paths
            char input_file[512], expected_file[512], actual_file[512];
            snprintf(input_file, sizeof(input_file), "%s%s", INPUT_DIR, entry->d_name);
            snprintf(expected_file, sizeof(expected_file), "%s%s_expected.txt", EXPECTED_DIR, test_name);
            snprintf(actual_file, sizeof(actual_file), "%s%s_actual.txt", ACTUAL_DIR, test_name);

            // Placeholder: Process the input and generate the actual output
            // TODO: Replace with actual application function call
            FILE *actual = fopen(actual_file, "w");
            fprintf(actual, "Placeholder output for %s\n", test_name);
            fclose(actual);

            // Compare actual vs expected
            compare_files(expected_file, actual_file, test_name);
        }
    }

    closedir(input_dir);
}

int main() {
    printf("[INFO] Starting automated test runner...\n");

    // Ensure directories exist
    ensure_directory_exists(INPUT_DIR);
    ensure_directory_exists(EXPECTED_DIR);
    ensure_directory_exists(ACTUAL_DIR);

    // Process test files
    process_test_files();

    printf("[INFO] Test runner completed.\n");
    return 0;
}
