#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    int n;
    int A[n][n], B[n], C[n];

    printf("Enter size of the matrix: ");
    scanf("%d", &n);

    printf("Matrix A:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = rand() % 10 + 1;
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }

    printf("\nVector B:\n");
    for (int i = 0; i < n; i++) {
        B[i] = rand() % 10 + 1;
        printf("%d\n", B[i]);
    }

    for (int i = 0; i < n; i++) {
        C[i] = 0;
    }

    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i] += A[i][j] * B[j];
        }
        printf("Thread %d computed C[%d] = %d\n", omp_get_thread_num(), i, C[i]);
    }

    printf("\nResult Vector C:\n");
    for (int i = 0; i < n; i++) {
        printf("%d\n", C[i]);
    }

    return 0;
}
