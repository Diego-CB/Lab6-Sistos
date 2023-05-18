#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int available_resources = 10;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
FILE* logfile;
int num_iterations = 5;

// Decrease available resources by count
// Return 0 if sufficient resources available, otherwise return -1
int decrease_count(int count) {
    pthread_mutex_lock(&mutex);

    while (available_resources < count) {
        fprintf(logfile, "%lu - (!) Recurso tomado\n", pthread_self());
        pthread_cond_wait(&cond, &mutex);
    }

    available_resources -= count;
    fprintf(logfile, "Se consumiran %d recursos\n", count);

    pthread_mutex_unlock(&mutex);

    return 0;
}

// Increase available resources by count
int increase_count(int count) {
    pthread_mutex_lock(&mutex);

    available_resources += count;
    fprintf(logfile, "Thread %lu devolvio %d recursos\n", pthread_self(), count);

    pthread_cond_broadcast(&cond);

    pthread_mutex_unlock(&mutex);

    return 0;
}

void* thread_function(void* arg) {
    int count = *((int*)arg);

    for (int i; i < num_iterations; i++){
        decrease_count(count);

        // Simulate work being done with the resources
        fprintf(logfile, "Thread %lu working...\n", pthread_self());
        // Sleep or do actual work here

        increase_count(count);
    }


    return NULL;
}

int main() {
    int num_threads = 10;
    int i, result;
    logfile = fopen("monitor.txt", "w");
    fprintf(logfile, "Iniciando Programa\n");

    if (logfile == NULL) {
        printf("Error opening log file\n");
        return 1;
    }

    // Crear threads
    fprintf(logfile, "Creando threads\n");
    pthread_t threads[num_threads];
    int thread_args[num_threads];

    for (i = 0; i < num_threads; i++) {
        thread_args[i] = rand() % 6;
        pthread_create(&threads[i], NULL, thread_function, &thread_args[i]);
    }

    fprintf(logfile, "Esperando Threads\n");
    // Join threads
    for (i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    fclose(logfile);
    return 0;
}
