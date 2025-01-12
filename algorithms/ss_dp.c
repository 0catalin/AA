#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void print_subset(int *subset, int subset_size) {
    printf("Subset found: ");
    int total_sum = 0;
    for (int i = 0; i < subset_size; i++) {
        printf("%d ", subset[i]);
        total_sum += subset[i];
    }
    printf("\nChecking sum of subset: %d\n", total_sum);
}



int main(int argc, char **argv) {
    int nr_values, target_sum;
    int *values_arr;
    if (argc != 2) {
        printf("Must introduce 1 argument!");
        exit(1);
    }
    char path[100];
    strcpy(path, "../");
    strcat(path, argv[1]);
    FILE *file = fopen(path, "r");
    if (!file) {
        printf("File not found!");
        exit(1);
    }
    if (fscanf(file, "%d %d", &nr_values, &target_sum) != 2) {
        fprintf(stderr, "Error: Failed to read `nr_values` and `target_sum` from the file.\n");
        fclose(file);
        if (values_arr)
            free(values_arr);
        exit(1);
    }
    values_arr = malloc(nr_values * sizeof(int));
    for (int i = 0; i < nr_values; ++i) {
        if (values_arr != NULL && fscanf(file, "%d", &values_arr[i]) != 1) {
            fprintf(stderr, "Error: Failed to read `values_arr[i]` from the file.\n");
            fclose(file);
            if (values_arr)
                free(values_arr);
            exit(1);
        }
    }

    // TODO

    if (values_arr)
        free(values_arr);
    fclose(file);
    return 0;
}