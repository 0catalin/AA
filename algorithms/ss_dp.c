#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void print_subset(int *subset, int subset_size) {
    printf("Subset found: ");
    int total_sum = 0;
    for (int i = 0; i < subset_size; i++) {
        printf("%d ", subset[i]);
        total_sum += subset[i];
    }
    printf("\nChecking sum of subset: %d\n", total_sum);
}

void dynamic_subset(int *values_arr, int target_sum, int nr_values) {
    bool **matrix = NULL;
    matrix = calloc((nr_values + 1), sizeof(bool *));
    for (int i = 0; i <= nr_values; ++i) {
        matrix[i] = calloc((target_sum + 1), sizeof(bool));
    }

    for (int i = 0; i <= nr_values; ++i)
        matrix[i][0] = true;

    for (int i = 1; i <= nr_values; ++i) {
        for (int j = 1; j <= target_sum; ++j) {
            if (j < values_arr[i - 1]) {
                matrix[i][j] = matrix[i - 1][j];
            } else {
                matrix[i][j] = matrix[i - 1][j] || matrix[i - 1][j - values_arr[i - 1]];
            }
        }
    }

    if (!matrix[nr_values][target_sum]) {
        printf("Subset not found!\n");
        for (int i = 0; i <= nr_values; ++i)
            free(matrix[i]);
        free(matrix);
        return;
    }

    int *subset = NULL;
    subset = malloc(nr_values * sizeof(int));
    int subset_index = 0;
    int crt_sum = target_sum;
    for (int i = nr_values; i > 0 && crt_sum > 0; i--) {
        if (matrix[i][crt_sum] != matrix[i - 1][crt_sum]) {
            subset[subset_index] = values_arr[i - 1];
            subset_index++;
            crt_sum -= values_arr[i - 1];
        }
    }
    print_subset(subset, subset_index);
    for (int i = 0; i <= nr_values; ++i)
        free(matrix[i]);
    free(matrix);
    free(subset);
}

int main(int argc, char **argv) {
    int nr_values, target_sum;
    int *values_arr = NULL;
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
    dynamic_subset(values_arr, target_sum, nr_values);
    if (values_arr)
        free(values_arr);
    fclose(file);
    return 0;
}