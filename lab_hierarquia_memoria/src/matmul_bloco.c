#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Uso: %s <N> <tamanho_bloco_B>\n", argv[0]);
        return 1;
    }

    int N = atoi(argv[1]);
    int B_size = atoi(argv[2]);

    double *A = (double *)malloc((size_t)N * N * sizeof(double));
    double *B = (double *)malloc((size_t)N * N * sizeof(double));
    double *C = (double *)calloc((size_t)N * N, sizeof(double));

    if (!A || !B || !C) {
        perror("Erro de alocacao");
        return 1;
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i * N + j] = (double)(i + j);
            B[i * N + j] = (double)(i * j);
        }
    }

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    // multiplicação com blocagem 
    for (int ii = 0; ii < N; ii += B_size) {
        for (int jj = 0; jj < N; jj += B_size) {
            for (int kk = 0; kk < N; kk += B_size) {

                for (int i = ii; i < ii + B_size && i < N; i++) {
                    for (int k = kk; k < kk + B_size && k < N; k++) {
                        double rA = A[i * N + k];
                        for (int j = jj; j < jj + B_size && j < N; j++) {
                            C[i * N + j] += rA * B[k * N + j];
                        }
                    }
                }

            }
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    double gflops = (2.0 * N * N * N) / (elapsed * 1e9);

    printf("[Matmul Blocado] N: %d | Bloco B: %d | Tempo: %.6f s | GFLOPS: %.2f\n", N, B_size, elapsed, gflops);

    free(A); free(B); free(C);
    return 0;
}