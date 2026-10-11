#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <omp.h>

#define DEFAULT_N 10000000

int main(int argc, char *argv[])
{
    int *data;
    int i;
    int minimum, maximum;
    int N;
    double start, end;

    if (argc > 1)
    {
        N = atoi(argv[1]);
    }
    else
    {
        N = DEFAULT_N;
    }

    data = (int *)malloc(N * sizeof(int));

    if (data == NULL)
    {
        printf("Memory allocation failed\n");
        return 1;
    }

    srand(42);

    for (i = 0; i < N; i++)
    {
        data[i] = rand() % 1000000 + 1;
    }

    minimum = INT_MAX;
    maximum = INT_MIN;

    start = omp_get_wtime();

    #pragma omp parallel for reduction(min:minimum) reduction(max:maximum)
    for (i = 0; i < N; i++)
    {
        if (data[i] < minimum)
        {
            minimum = data[i];
        }

        if (data[i] > maximum)
        {
            maximum = data[i];
        }
    }

    end = omp_get_wtime();

    printf("OpenMP Maximum/Minimum Search Completed\n");
    printf("Data Size = %d\n", N);
    printf("Number of Threads Used = %d\n", omp_get_max_threads());
    printf("Minimum = %d\n", minimum);
    printf("Maximum = %d\n", maximum);
    printf("Execution Time = %f seconds\n", end - start);

    free(data);

    return 0;
}

