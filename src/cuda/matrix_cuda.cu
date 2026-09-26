// matrix_cuda.cu
// Massively parallel matrix multiplication using CUDA
// Compile: nvcc -O2 matrix_cuda.cu -o matrix_cuda
#include <stdio.h>
#include <cuda_runtime.h>

#define N 4000
#define BLOCK_SIZE 16

__global__ void matMulKernel(const double *A, const double *B, double *C, int n) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if (row < n && col < n) {
        double sum = 0.0;
        for (int k = 0; k < n; k++) {
            sum += A[row * n + k] * B[k * n + col];
        }
        C[row * n + col] = sum;
    }
}

int main() {
    size_t bytes = (size_t)N * N * sizeof(double);

    double *h_A = (double *)malloc(bytes);
    double *h_B = (double *)malloc(bytes);
    double *h_C = (double *)malloc(bytes);

    for (int i = 0; i < N * N; i++) {
        h_A[i] = 1.0;
        h_B[i] = 1.0;
    }

    double *d_A, *d_B, *d_C;
    cudaMalloc(&d_A, bytes);
    cudaMalloc(&d_B, bytes);
    cudaMalloc(&d_C, bytes);

    cudaEvent_t startTotal, stopTotal, startKernel, stopKernel;
    cudaEventCreate(&startTotal);
    cudaEventCreate(&stopTotal);
    cudaEventCreate(&startKernel);
    cudaEventCreate(&stopKernel);

    cudaEventRecord(startTotal);

    cudaMemcpy(d_A, h_A, bytes, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, bytes, cudaMemcpyHostToDevice);

    dim3 block(BLOCK_SIZE, BLOCK_SIZE);
    dim3 grid((N + BLOCK_SIZE - 1) / BLOCK_SIZE, (N + BLOCK_SIZE - 1) / BLOCK_SIZE);

    cudaEventRecord(startKernel);
    matMulKernel<<<grid, block>>>(d_A, d_B, d_C, N);
    cudaEventRecord(stopKernel);
    cudaEventSynchronize(stopKernel);

    cudaMemcpy(h_C, d_C, bytes, cudaMemcpyDeviceToHost);

    cudaEventRecord(stopTotal);
    cudaEventSynchronize(stopTotal);

    float totalMs = 0, kernelMs = 0;
    cudaEventElapsedTime(&totalMs, startTotal, stopTotal);
    cudaEventElapsedTime(&kernelMs, startKernel, stopKernel);

    printf("CUDA Total Execution Time: %f seconds\n", totalMs / 1000.0);
    printf("CUDA Kernel Execution Time: %f seconds\n", kernelMs / 1000.0);
    printf("Verification C[0][0] = %.2f\n", h_C[0]);

    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);
    free(h_A);
    free(h_B);
    free(h_C);

    return 0;
}
