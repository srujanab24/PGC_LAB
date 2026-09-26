# Performance Analysis of Matrix Multiplication

Empirical performance comparison of a 4000 x 4000 matrix multiplication
(`C = A x B`) across four parallel computing paradigms: **Sequential**,
**OpenMP**, **MPI**, and **CUDA**.

## Repository Structure

```
PGC_Lab/
├── src/
│   ├── sequential/matrix_sequential.c   # Baseline single-threaded O(N^3)
│   ├── openmp/matrix_openmp.c           # Shared-memory, 8 threads
│   ├── mpi/matrix_mpi.c                 # Distributed, Scatter/Bcast/Gather
│   ├── mpi/mpi_send_recv.c              # Point-to-point connectivity test
│   └── cuda/matrix_cuda.cu              # GPU kernel, 16M threads
├── scripts/build_all.sh                 # Builds all four implementations
├── images/                              # Result screenshots (add your own)
└── .gitignore
```

## Building

```bash
chmod +x scripts/build_all.sh
./scripts/build_all.sh
```

Each implementation can also be built individually — see the comment
at the top of its source file for the exact compile command.

## Running

| Paradigm   | Command                                              |
|------------|-------------------------------------------------------|
| Sequential | `./src/sequential/matrix_sequential`                  |
| OpenMP     | `./src/openmp/matrix_openmp`                          |
| MPI        | `mpirun -np 4 -hostfile hostfile ./src/mpi/matrix_mpi`|
| CUDA       | `./src/cuda/matrix_cuda`                              |

All four implementations initialize `A[i][j] = 1.0` and `B[i][j] = 1.0`,
so a correct run always verifies `C[0][0] = 4000.00`.

## Results

Fill in your own measured times here once you've run each implementation
on your hardware — swap in screenshots under `images/` to match.

| Model      | Execution Time (s) | Speedup |
|------------|---------------------|---------|
| Sequential | —                   | 1.00x   |
| OpenMP     | —                   | —       |
| MPI        | —                   | —       |
| CUDA       | —                   | —       |
