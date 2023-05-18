#include <stdio.h>

int available_resources = 10;

// Decrease available resources by count
// Return 0 if sufficient resources available, otherwise return -1
int decrease_count(int count) {
    if (available_resources < count)
        return -1;
    else {
        available_resources -= count;
        return 0;
    }
}

// Increase available resources by count
int increase_count(int count) {
    available_resources += count;
    return 0;
}

int main() {
    int num_iterations = 5;
    int num_threads = 3;
    int i, result;

    // Consuming resources
    for (i = 0; i < num_iterations; i++) {
        printf("Iteration %d:\n", i + 1);

        // Simulating threads consuming resources
        for (int j = 0; j < num_threads; j++) {
            int count = 2; // Amount of resources to consume

            result = decrease_count(count);
            if (result == 0) {
                printf("Thread %d consumed %d resources\n", j + 1, count);
            } else {
                printf("Thread %d cannot consume %d resources, not enough available\n", j + 1, count);
            }
        }

        // Simulating work being done with the resources
        printf("Working...\n");
        // Sleep or do actual work here

        // Returning resources
        for (int j = 0; j < num_threads; j++) {
            int count = 2; // Amount of resources to return

            increase_count(count);
            printf("Thread %d returned %d resources\n", j + 1, count);
        }

        printf("\n");
    }

    printf("Program finished\n");

    return 0;
}
