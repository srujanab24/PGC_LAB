# Performance Analysis of Matrix Multiplication

Empirical performance comparison of a 4000 x 4000 matrix multiplication
(`C = A x B`) using two computing approaches: **Sequential** and **OpenMP**.

## Repository Structure

```text
PGC_Lab/
├── src/
│   ├── sequential/
│   │   └── matrix_sequential.c   # Baseline single-threaded O(N^3)
│   └── openmp/
│       └── matrix_openmp.c      # Shared-memory parallel execution
├── scripts/
│   └── build_all.sh              # Builds Sequential and OpenMP
├── images/                       # Result screenshots and charts
└── .gitignore