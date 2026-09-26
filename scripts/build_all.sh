#!/bin/bash
# Builds all four implementations. Run from the repo root.
set -e

echo "Building sequential..."
gcc -O2 src/sequential/matrix_sequential.c -o src/sequential/matrix_sequential

echo "Building OpenMP..."
gcc -fopenmp -O2 src/openmp/matrix_openmp.c -o src/openmp/matrix_openmp

echo "Building MPI..."
mpicc -O2 src/mpi/matrix_mpi.c -o src/mpi/matrix_mpi
mpicc -O2 src/mpi/mpi_send_recv.c -o src/mpi/mpi_send_recv

echo "Building CUDA (requires nvcc)..."
nvcc -O2 src/cuda/matrix_cuda.cu -o src/cuda/matrix_cuda

echo "All builds complete."
