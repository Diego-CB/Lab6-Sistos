#include <stdio.h>
#include <pthread.h>

int available_resources = 10;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
FILE* logfile;

// Decrease available resources by count
// Return 0 if sufficient resources available, otherwise return -1
int decrease_count(int count) {
    pthread_mutex_lock(&mutex);

    while (available_resources < count) {
        fprintf(logfile, "Thread %lu waiting for %d resources...\n", pthread_self(), count);
        pthread_cond_wait(&cond, &mutex);
    }

    available_resources -= count;
    fprintf(logfile, "Thread %lu consumed %d resources\n", pthread_self(), count);

    pthread_mutex_unlock(&mutex);

    return 0;
}

// Increase available resources by count
int increase_count(int count) {
    pthread_mutex_lock(&mutex);

    available_resources += count;
    fprintf(logfile, "Thread %lu returned %d resources\n", pthread_self(), count);

    pthread_cond_broadcast(&cond);

    pthread_mutex_unlock(&mutex);

    return 0;
}

void* thread_function(void* arg) {
    int count = *((int*)arg);

    decrease_count(count);

    // Simulate work being done with the resources
    fprintf(logfile, "Thread %lu working...\n", pthread_self());
    // Sleep or do actual work here

    increase_count(count);

    return NULL;
}

int main() {
    int num_iterations = 5;
    int num_threads = 3;
    int i, result;

    logfile = fopen("log.txt", "w");
    if (logfile == NULL) {
        printf("Error opening log file\n");
        return 1;
    }

    // Create and initialize threads
    pthread_t threads[num_threads];
    int thread_args[num_threads];

    for (i = 0; i < num_threads; i++) {
        thread_args[i] = 2; // Amount of resources to consume/return
        pthread_create(&threads[i], NULL, thread_function, &thread_args[i]);
    }

    // Join threads
    for (i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    fclose(logfile);

    printf("Program finished\n");

    return 0;
}
