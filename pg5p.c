#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    int num_students;

    printf("Enter the number of students: ");
    scanf("%d", &num_students);

    double *cgpas = (double *)malloc(num_students * sizeof(double));

    srand(0);  // Set a random seed for reproducibility
    for (int i = 0; i < num_students; i++) {
        cgpas[i] = (double)(rand() % 10000) / 1000.0;
    }

    double max_cgpa = 0.0;
    int highest_student = -1;

    double start_time = omp_get_wtime();

    #pragma omp parallel for reduction(max:max_cgpa)
    for (int i = 0; i < num_students; i++) {
        if (cgpas[i] > max_cgpa) {
            #pragma omp critical
            {
                if (cgpas[i] > max_cgpa) {
                    max_cgpa = cgpas[i];
                    highest_student = i;
                }
            }
        }
    }

    double end_time = omp_get_wtime();

    printf("The student with the highest CGPA is student %d with CGPA %.2f\n", highest_student + 1, max_cgpa);
    printf("Time Taken: %lf seconds\n", end_time - start_time);

    free(cgpas);

    return 0;
}
