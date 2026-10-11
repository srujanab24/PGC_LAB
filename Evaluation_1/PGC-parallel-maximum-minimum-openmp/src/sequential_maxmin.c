#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <omp.h>

#define N 10000000

int main()
{
    int *data;
    int i;
    int minimum, maximum;
    double start, end;

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

    start = omp_get_wtime();

    minimum = INT_MAX;
    maximum = INT_MIN;

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

    printf("Sequential Maximum/Minimum Search Completed\n");
    printf("Data Size = %d\n", N);
    printf("Minimum = %d\n", minimum);
    printf("Maximum = %d\n", maximum);
    printf("Execution Time = %f seconds\n", end - start);

    free(data);

    return 0;
}

