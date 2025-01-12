#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ss_backtracking.h"


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

bool backtrack(int *values_arr, int nr_values, int target_sum, int current_sum, int *subset, int subset_size, int value_index) {
    // If we have found a subset with the target sum,
    // print it and return true.
    if (current_sum == target_sum) {
        print_subset(subset, subset_size);
        return true;
    }
    // If we have reached the end of the array, return false.
    if (value_index == nr_values) {
        return false;
    }
    // Add current element to subset array
    subset[subset_size] = values_arr[value_index];
    // Call recursively for both the inclusion and exclusion case:
    //  1. When including the current element, we increase the subset size to 
    //     consider the last added element (and add it to the current sum).
    //  2. When excluding the current element, subset size is left the same, so
    //     that the current element will be overwritten for the next call (and the
    //     current sum is left the same).
    return backtrack(values_arr, nr_values, target_sum, current_sum + values_arr[value_index], subset, subset_size + 1, value_index + 1) ||
            backtrack(values_arr, nr_values, target_sum, current_sum, subset, subset_size, value_index + 1);
}

bool subset_sum(int *values_arr, int nr_values, int target_sum) {
    int *subset = malloc(nr_values * sizeof(int));
    bool ret = backtrack(values_arr, nr_values, target_sum, 0, subset, 0, 0);
    
    free(subset);
    return ret;
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
    if (!subset_sum(values_arr, nr_values, target_sum)) {
        printf("No subset with sum %d found.\n", target_sum);
    }
    if (values_arr)
        free(values_arr);
    fclose(file);
    return 0;
}