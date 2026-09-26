# Performance Analysis of Matrix Multiplication

Empirical performance comparison of a 4000 x 4000 matrix multiplication
(`C = A x B`) using three computing approaches: **Sequential, OpenMP, and MPI**.

## Repository Structure

```text
PGC_Lab/
├── src/
│   ├── sequential/
│   │   └── matrix_sequential.c   # Baseline single-threaded O(N^3)
│   ├── openmp/
│   │   └── matrix_openmp.c       # Shared-memory parallel execution
│   └── mpi/
│       ├── matrix_mpi.c          # Distributed-memory matrix multiplication
│       └── mpi_send_recv.c       # MPI point-to-point communication test
├── scripts/
│   └── build_all.sh              # Builds Sequential, OpenMP and MPI
├── images/                       # Result screenshots and charts
└── .gitignore