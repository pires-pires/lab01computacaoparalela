#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

typedef struct {
    int thread_id;
    int num_threads;
    int N;
    double *A;
    double *B;
    double *C;
} ThreadData;

void *worker_padrao(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    int N = data->N;
    int start_row = data->thread_id * (N / data->num_threads);
    int end_row = (data->thread_id == data->num_threads - 1) ? N : start_row + (N / data->num_threads);

    for (int i = start_row; i < end_row; i++) {
        for (int j = 0; j < N; j++) {
            double sum = 0.0;
            for (int k = 0; k < N; k++) {
                sum += data->A[i * N + k] * data->B[k * N + j];
            }
            data->C[i * N + j] = sum;
        }
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Uso: %s <N> <num_threads>\n", argv[0]);
        return 1;
    }

    int N = atoi(argv[1]);
    int num_threads = atoi(argv[2]);

    double *A = (double *)malloc((size_t)N * N * sizeof(double));
    double *B = (double *)malloc((size_t)N * N * sizeof(double));
    double *C = (double *)calloc((size_t)N * N, sizeof(double));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i * N + j] = (double)(i + j);
            B[i * N + j] = (double)(i * j);
        }
    }

    pthread_t threads[num_threads];
    ThreadData tdata[num_threads];

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int t = 0; t < num_threads; t++) {
        tdata[t].thread_id = t;
        tdata[t].num_threads = num_threads;
        tdata[t].N = N;
        tdata[t].A = A; tdata[t].B = B; tdata[t].C = C;
        pthread_create(&threads[t], NULL, worker_padrao, (void *)&tdata[t]);
    }

    for (int t = 0; t < num_threads; t++) {
        pthread_join(threads[t], NULL);
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("[Pthreads Padrao] N: %d | Threads: %d | Tempo: %.6f s\n", N, num_threads, elapsed);

    free(A); free(B); free(C);
    return 0;
}