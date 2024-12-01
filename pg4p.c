#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    int n;

    printf("Enter the number of Fibonacci numbers to generate: ");
    scanf("%d", &n);

    int *fib = (int *)malloc(n * sizeof(int));

    if (fib == NULL) {
        printf("Memory allocation failed.\n");
        return -1;
    }

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            int a = 0, b = 1, next;
            for (int i = 0; i < n; i++) {
                if (i == 0) {
                    fib[i] = a;
                } else if (i == 1) {
                    fib[i] = b;
                } else {
                    next = a + b;
                    fib[i] = next;
                    a = b;
                    b = next;
                }
            }
        }

        #pragma omp section
        {
            printf("Fibonacci Series: ");
            for (int i = 0; i < n; i++) {
                printf("%d ", fib[i]);
            }
            printf("\n");
        }
    }

    free(fib);

    return 0;
}