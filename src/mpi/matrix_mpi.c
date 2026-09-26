// matrix_mpi.c
// Distributed matrix multiplication using MPI (Scatter / Bcast / Gather)
// Compile: mpicc -O2 matrix_mpi.c -o matrix_mpi
// Run:     mpirun -np 4 -hostfile hostfile ./matrix_mpi
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define N 4000

int main(int argc, char **argv) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int rows_per_proc = N / size;

    double *A = NULL, *B = malloc((size_t)N * N * sizeof(double));
    double *C = NULL;
    double *local_A = malloc((size_t)rows_per_proc * N * sizeof(double));
    double *local_C = malloc((size_t)rows_per_proc * N * sizeof(double));

    if (rank == 0) {
        A = malloc((size_t)N * N * sizeof(double));
        C = malloc((size_t)N * N * sizeof(double));
        for (int i = 0; i < N * N; i++) A[i] = 1.0;
    }
    for (int i = 0; i < N * N; i++) B[i] = 1.0;

    double start = MPI_Wtime();

    MPI_Scatter(A, rows_per_proc * N, MPI_DOUBLE,
                local_A, rows_per_proc * N, MPI_DOUBLE,
                0, MPI_COMM_WORLD);
    MPI_Bcast(B, N * N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    for (int i = 0; i < rows_per_proc; i++) {
        for (int j = 0; j < N; j++) {
            double sum = 0.0;
            for (int k = 0; k < N; k++) {
                sum += local_A[i * N + k] * B[k * N + j];
            }
            local_C[i * N + j] = sum;
        }
    }

    MPI_Gather(local_C, rows_per_proc * N, MPI_DOUBLE,
               C, rows_per_proc * N, MPI_DOUBLE,
               0, MPI_COMM_WORLD);

    double end = MPI_Wtime();

    if (rank == 0) {
        printf("MPI Execution Time (%d ranks): %f seconds\n", size, end - start);
        printf("Verification C[0][0] = %.2f\n", C[0]);
        free(A);
        free(C);
    }

    free(B);
    free(local_A);
    free(local_C);
    MPI_Finalize();
    return 0;
}
