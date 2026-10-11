// matrix_openmp.c
// Shared-memory parallel matrix multiplication using OpenMP
// Compile: gcc -fopenmp -O2 matrix_openmp.c -o matrix_openmp
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 4000
#define NUM_THREADS 8

int main() {
    double *A = malloc((size_t)N * N * sizeof(double));
    double *B = malloc((size_t)N * N * sizeof(double));
    double *C = malloc((size_t)N * N * sizeof(double));

    if (!A || !B || !C) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < N * N; i++) {
        A[i] = 1.0;
        B[i] = 1.0;
    }

    omp_set_num_threads(NUM_THREADS);
    double start = omp_get_wtime();

    #pragma omp parallel for schedule(dynamic)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            double sum = 0.0;
            for (int k = 0; k < N; k++) {
                sum += A[i * N + k] * B[k * N + j];
            }
            C[i * N + j] = sum;
        }
    }

    double end = omp_get_wtime();
    printf("OpenMP Execution Time (%d threads): %f seconds\n", NUM_THREADS, end - start);
    printf("Verification C[0][0] = %.2f\n", C[0]);

    free(A);
    free(B);
    free(C);
    return 0;
}
