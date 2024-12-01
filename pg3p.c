#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

int main() {
    int num;

    printf("Enter the number of steps: ");
    scanf("%d", &num);

    omp_set_num_threads(num);

    double start_time = omp_get_wtime();

    double step = 1.0 / (double)num;
    double pi = 0.0;

    #pragma omp parallel for reduction(+:pi)
    for (int i = 0; i < num; i++) {
        double x = (i + 0.5) * step;
        pi += (4.0 * step / (1.0 + x * x));
    }

    double end_time = omp_get_wtime();

    printf("Time Taken: %lf seconds\n", end_time - start_time);
    printf("Computed value of Pi: %.15f\n", pi);

    return 0;
}
