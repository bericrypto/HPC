#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    int n_sections = 4;
    const char *sections[] = {"Clothing", "Gaming", "Grocery", "Stationery"};

    int n_items;
    printf("Enter the number of items per section: ");
    scanf("%d", &n_items);

    int total_bill = 0;

    printf("Items and prices in each section:\n");

    #pragma omp parallel reduction(+:total_bill)
    {
        int section_total = 0;

        #pragma omp for
        for (int i = 0; i < n_sections; i++) {
            printf("\n%s Section:\n", sections[i]);
            for (int j = 0; j < n_items; j++) {
                int price = rand() % 100 + 1;
                printf("  Item %d: $%d\n", j + 1, price);
                section_total += price;
            }
            printf("Thread %d processed %s Section with total $%d\n",
                   omp_get_thread_num(), sections[i], section_total);

            total_bill += section_total;
            section_total = 0;
        }
    }

    printf("\nFinal Total Bill: $%d\n", total_bill);

    return 0;
}
