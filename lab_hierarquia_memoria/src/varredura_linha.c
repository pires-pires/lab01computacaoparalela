#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s <dimensao_N>\n", argv[0]);
        return 1;
    }

    int N = atoi(argv[1]);
    double *A = (double *)malloc((size_t)N * N * sizeof(double));
    if (!A) {
        perror("Erro ao alocar memoria");
        return 1;
    }

    // inicialização
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i * N + j] = (double)(i + j);
        }
    }

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    // codigo referencia para medição
    long pares = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if ((int)A[i * N + j] % 2 == 0) {
                pares++;
            }
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("[LINHA] N: %d | Pares: %ld | Tempo: %.6f s\n", N, pares, elapsed);

    free(A);
    return 0;
}