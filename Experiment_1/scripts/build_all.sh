#!/bin/bash
# Builds the sequential and OpenMP implementations.
# Run from the repository root.
set -e

echo "Building sequential..."
gcc -O2 src/sequential/matrix_sequential.c -o src/sequential/matrix_sequential

echo "Building OpenMP..."
gcc -fopenmp -O2 src/openmp/matrix_openmp.c -o src/openmp/matrix_openmp

echo "All builds complete."
