#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "experiment.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Error: No specified atom.\n");
        printf("Correct use: .\\benchmark_memoria <atom_name>\n\n");
        printf("Available options:\n");
        printf("  omitted_curly\n");
        printf("  implicit_predicate\n");
        printf("  infix_precedence\n");
        printf("  conditional_operator\n");
        printf("  post_increment\n");
        return 1;
    }

    int iterations = 100000; 
    int data_size = 8192; // Array pequeno para não poluir o Cache L1
    
    int *conditions = (int *)malloc(data_size * sizeof(int));
    int *values_a = (int *)malloc(data_size * sizeof(int));
    int *values_b = (int *)malloc(data_size * sizeof(int));

    if (!conditions || !values_a || !values_b) {
        printf("Erro de alocacao de memoria!\n");
        return 1;
    }

    // generates pseudo-random data
    for(int i = 0; i < data_size; i++) {
        conditions[i] = i % 2;       // alternates between 0 and 1
        values_a[i] = (i % 10) + 1;  // values between 1 and 10
        values_b[i] = (i % 5) + 1;   // values between 1 and 5
    }

    printf("==========================================\n");
    printf(" RUNNING MEMORY TEST: %s\n", argv[1]);
    printf(" Iterations: %d\n", iterations);
    printf("==========================================\n\n");

    if (strcmp(argv[1], "omitted_curly") == 0) {
        for(int i = 0; i < iterations; i++) omitted_curly_braces_confusing(conditions[i % data_size]);
        for(int i = 0; i < iterations; i++) omitted_curly_braces_clean(conditions[i % data_size]);
    } 
    else if (strcmp(argv[1], "implicit_predicate") == 0) {
        for(int i = 0; i < iterations; i++) implicit_predicate_confusing(conditions[i % data_size]);
        for(int i = 0; i < iterations; i++) implicit_predicate_clean(conditions[i % data_size]);
    }
    else if (strcmp(argv[1], "infix_precedence") == 0) {
        for(int i = 0; i < iterations; i++) infix_precedence_confusing(conditions[i % data_size], values_a[i % data_size], values_b[i % data_size]);
        for(int i = 0; i < iterations; i++) infix_precedence_clean(conditions[i % data_size], values_a[i % data_size], values_b[i % data_size]);
    }
    else if (strcmp(argv[1], "conditional_operator") == 0) {
        for(int i = 0; i < iterations; i++) conditional_operator_confusing(conditions[i % data_size], values_a[i % data_size], values_b[i % data_size]);
        for(int i = 0; i < iterations; i++) conditional_operator_clean(conditions[i % data_size], values_a[i % data_size], values_b[i % data_size]);
    }
    else if (strcmp(argv[1], "post_increment") == 0) {
        for(int i = 0; i < iterations; i++) post_increment_confusing(values_a[i % data_size]);
        for(int i = 0; i < iterations; i++) post_increment_clean(values_a[i % data_size]);
    }
    else {
        printf("Error: Unknown '%s' atom.\n", argv[1]);
        free(conditions); free(values_a); free(values_b);
        return 1;
    }

    free(conditions);
    free(values_a);
    free(values_b);

    return 0;
}