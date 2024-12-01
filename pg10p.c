#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    int n;
    printf("Enter the dimension of square matrices: ");
    scanf("%d", &n);

    int** arr1 = (int**)malloc(n * sizeof(int*));
    int** arr2 = (int**)malloc(n * sizeof(int*));
    int** res = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        arr1[i] = (int*)malloc(n * sizeof(int));
        arr2[i] = (int*)malloc(n * sizeof(int));
        res[i] = (int*)malloc(n * sizeof(int));
    }

    srand(0); // Fixed seed for reproducibility
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            arr1[i][j] = rand() % 100;
            arr2[i][j] = rand() % 100;
        }
    }

    double start_time = omp_get_wtime();
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            res[i][j] = 0;
            for (int k = 0; k < n; k++) {
                res[i][j] += arr1[i][k] * arr2[k][j];
            }
        }
    }
    double parallel_time = omp_get_wtime() - start_time;
    printf("Time taken by parallel algorithm: %lf seconds\n", parallel_time);

    start_time = omp_get_wtime();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            res[i][j] = 0;
            for (int k = 0; k < n; k++) {
                res[i][j] += arr1[i][k] * arr2[k][j];
            }
        }
    }
    double sequential_time = omp_get_wtime() - start_time;
    printf("Time taken by sequential algorithm: %lf seconds\n", sequential_time);

    for (int i = 0; i < n; i++) {
        free(arr1[i]);
        free(arr2[i]);
        free(res[i]);
    }
    free(arr1);
    free(arr2);
    free(res);

    return 0;
}