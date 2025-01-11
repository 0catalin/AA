#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ss_backtracking.h"

#include <stdio.h>
#include <stdbool.h>

void print_subset(int subset[], int subset_size) {
    printf("Subset: ");
    int total_sum = 0;
    for (int i = 0; i < subset_size; i++) {
        printf("%d ", subset[i]);
        total_sum += subset[i];
    }
    printf("\n");
    printf("TOTAL SUM!!!!!!: %d\nHAHAHAHAHAHAHAHA\n", total_sum);
}

bool backtrack(int nums[], int n, int target, int current_sum, int subset[], int subset_size, int i) {
    
    if (current_sum == target) {
        print_subset(subset, subset_size);
        return true;
    }
    
    if (i == n) {
        return false;
    }
    
    subset[subset_size] = nums[i];
    if (backtrack(nums, n, target, current_sum + nums[i], subset, subset_size + 1, i + 1)) {
        return true;
    }
    
    if (backtrack(nums, n, target, current_sum, subset, subset_size, i + 1)) {
        return true;
    }
    
    return false;
}

bool subset_sum(int nums[], int n, int target) {
    int subset[n];
    return backtrack(nums, n, target, 0, subset, 0, 0);
}

int main(int argc, char **argv) {
    int nr_values, target_sum;
    int *values_arr;
    if (argc != 2) {
        printf("Must introduce 2 arguments!");
        exit(1);
    }
    char path[100];
    strcpy(path, "../tests/");
    strcat(path, argv[1]);
    FILE *file = fopen(path, "r");
    if (!file) {
        printf("File not found!");
        exit(1);
    }
    fscanf(file, "%d %d", &nr_values, &target_sum);
    values_arr = malloc(nr_values * sizeof(int));
    for (int i = 0; i < nr_values; ++i) {
        fscanf(file, "%d", &values_arr[i]);
    }
    //printf("Number of values: %d\nTarget sum: %d\n", nr_values, target_sum);
    //for (int i = 0; i < nr_values; ++i) {
    //    printf("%d\n", values_arr[i]);
    //}
    if (!subset_sum(values_arr, nr_values, target_sum)) {
        printf("No subset with sum %d found.\n", target_sum);
    }
    fclose(file);
    return 0;
}