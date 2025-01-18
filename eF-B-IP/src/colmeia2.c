#include <stdio.h>
#include <stdlib.h>

// Function to process input numbers and generate output
void run() {
    int a, b, c, d;

    // Read four integers from standard input
    if (scanf("%d %d %d %d", &a, &b, &c, &d) != 4) {
        fprintf(stderr, "[ERROR] Invalid input format. Expected 4 integers.\n");
        exit(EXIT_FAILURE);
    }

    // Generate and print the output (example output format)
    printf("Processed numbers: %d, %d, %d, %d\n", a, b, c, d);

    // Example: Add additional processing logic here if needed
}

int main() {
    // Invoke the run function to process inputs
    run();
    return 0;
}