#include <stdio.h>
#include <stdlib.h>
#include <string.h>




int abs_value(int number) {
    if (number >= 0)
        return number;
    return -number;
}

int compare_descending(const void* a, const void* b) {
    return (abs_value(*(int*)b) - abs_value(*(int*)a));
}

int* greedy_ss(int* values_arr, int nr_values, int* subset_size, int acceptable_error, int target_sum) {

    int* subset = malloc(sizeof(int) * nr_values);
    *subset_size = 0;
    int crt_sum = 0;
    int crt_diff;

    for(int i = 0; i < nr_values; i++) {
        crt_diff = abs_value(crt_sum - target_sum);
        if (crt_diff <= acceptable_error)
            break;
        if (abs_value(values_arr[i] + crt_sum - target_sum) < crt_diff) {
            subset[*subset_size] = values_arr[i];
            (*subset_size)++;
            crt_sum += values_arr[i];
        }
    }



    return subset;
}


void print_subset(int *subset, int subset_size, int target_sum) {
    printf("Subset found: ");
    int total_sum = 0;
    for (int i = 0; i < subset_size; i++) {
        printf("%d ", subset[i]);
        total_sum += subset[i];
    }
    printf("\nChecking sum of subset: %d\n", total_sum);
    printf("Printing target sum: %d\n", target_sum);
    printf("Sum difference: %d\n", abs_value(total_sum - target_sum));
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

    qsort(values_arr, nr_values, sizeof(int), compare_descending);

    //printf("Number of values: %d\nTarget sum: %d\n", nr_values, target_sum);
    //for (int i = 0; i < nr_values; ++i) {
    //   printf("%d\n", values_arr[i]);
    //}

    int subset_size = 0;
    int* result = greedy_ss(values_arr, nr_values, &subset_size, 0, target_sum);
    print_subset(result, subset_size, target_sum);


    
    free(result);
    if (values_arr)
        free(values_arr);
    fclose(file);
    return 0;
}