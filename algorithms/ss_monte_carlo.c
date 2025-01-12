#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include <stdbool.h>



int abs_value(int number) {
    if (number >= 0)
        return number;
    return -number;
}

void print_subset(int *subset, int subset_size, int target_sum) {
    //printf("Subset found: ");
    int total_sum = 0;
    for (int i = 0; i < subset_size; i++) {
    //    printf("%d ", subset[i]);
        total_sum += subset[i];
    }
    //printf("\nChecking sum of subset: %d\n", total_sum);
    printf("%d %d", target_sum, abs_value(total_sum - target_sum));
    //printf("Sum difference: %d\n", abs_value(total_sum - target_sum));
}



bool take_number_or_not() {
    int random_number = rand() % 2;
    if (random_number == 1)
        return true;
    return false;
}


int* montecarlo(int nr_values, int *values_arr, int number_of_iterations, int target_sum, int* subset_size) {
    int* best_values = malloc(nr_values * sizeof(int));
    int best_sum = 0;

    for (int i = 0; i < number_of_iterations; ++i) {
        int* current_subset = malloc(nr_values * sizeof(int));
        int current_subset_size = 0;
        int current_sum = 0;

        
        for (int j = 0; j < nr_values; ++j) {
            if (take_number_or_not()) {
                current_subset[current_subset_size] = values_arr[j];
                current_sum += values_arr[j];
                current_subset_size++;
            }
        }

        if (abs_value(current_sum - target_sum) < abs_value(best_sum - target_sum)) {
            memcpy(best_values, current_subset, current_subset_size * sizeof(int));
            *subset_size = current_subset_size;
            best_sum = current_sum;
        }
        

        free(current_subset);

        if (current_sum == target_sum) {
            break;
        }
    }
    return best_values;
}




int main(int argc, char **argv) {
    srand((unsigned int)clock());
    int nr_values, target_sum;
    int *values_arr = NULL;
    if (argc != 3) {
        printf("Must introduce 2 arguments!\n");
        exit(1);
    }


    char path[100];
    strcpy(path, "../");
    strcat(path, argv[1]);
    FILE *file = fopen(path, "r");
    if (!file) {
        printf("File not found!\n");
        exit(1);
    }


    char* endptr;
    int number_of_iterations = strtol(argv[2], &endptr, 10);
    if (endptr == argv[2]) {
        printf("Error: No valid number found in '%s'\n", argv[2]);
        exit(1);
    } else if (*endptr != '\0') {
        printf("Error: Trailing characters after number: '%s'\n", endptr);
        exit(1);
    } else if (number_of_iterations > 100000) {
        printf("Number higher than 100000 you are crazy!\n");
        exit(1);
    } else if (number_of_iterations <= 0) {
        printf("Number lower than 1 you are crazy!\n");
        exit(1);
    }
    //printf("Number of iterations is %d\n", number_of_iterations);



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

    //for (int i = 0; i < nr_values; i++) {
    //    if (take_number_or_not()) {
    //        printf("%d ", values_arr[i]);
    //    }
    //}
    //printf("\n");

    int subset_size = 0;
    int* result = montecarlo(nr_values, values_arr, number_of_iterations, target_sum, &subset_size);

    
    print_subset(result, subset_size, target_sum);

    free(result);
    if (values_arr)
        free(values_arr);
    fclose(file);
    return 0;
}