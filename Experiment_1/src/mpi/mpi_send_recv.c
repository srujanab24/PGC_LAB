// mpi_send_recv.c
// Simple point-to-point MPI_Send / MPI_Recv connectivity test across ranks
// Compile: mpicc -O2 mpi_send_recv.c -o mpi_send_recv
// Run:     mpirun -np 4 -hostfile hostfile ./mpi_send_recv
#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    char hostname[256];
    gethostname(hostname, sizeof(hostname));

    if (rank == 0) {
        for (int src = 1; src < size; src++) {
            char buf[256];
            MPI_Recv(buf, 256, MPI_CHAR, src, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Rank 0 received from rank %d: %s\n", src, buf);
        }
    } else {
        char msg[256];
        snprintf(msg, sizeof(msg), "Hello from rank %d on %s", rank, hostname);
        MPI_Send(msg, 256, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
