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
        printf("  repurposed_variable\n");
        printf("  pre_increment\n");
        printf("  comma_operator\n");
        printf("  reversed_subscripts\n");
        printf("  type_conversion\n");
        printf("  logic_as_control_flow\n");
        printf("  assignment_as_value\n");
        printf("  macro_operator_precedence\n");
        printf("  preprocessor_in_statement\n");
        printf("  change_of_literal_encoding\n");
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
    else if (strcmp(argv[1], "repurposed_variable") == 0) {
        for(int i = 0; i < iterations; i++) repurposed_variable_confusing(values_a[i % data_size], values_b[i % data_size]);
        for(int i = 0; i < iterations; i++) repurposed_variable_clean(values_a[i % data_size], values_b[i % data_size]);
    }
    else if (strcmp(argv[1], "pre_increment") == 0) {
        for(int i = 0; i < iterations; i++) pre_increment_confusing(values_a[i % data_size]);
        for(int i = 0; i < iterations; i++) pre_increment_clean(values_a[i % data_size]);
    }
    else if (strcmp(argv[1], "comma_operator") == 0) {
        for(int i = 0; i < iterations; i++) comma_operator_confusing(values_a[i % data_size]);
        for(int i = 0; i < iterations; i++) comma_operator_clean(values_a[i % data_size]);
    }
    else if (strcmp(argv[1], "reversed_subscripts") == 0) {
        for(int i = 0; i < iterations; i++) reversed_subscripts_confusing((i % data_size) % 3);
        for(int i = 0; i < iterations; i++) reversed_subscripts_clean((i % data_size) % 3);
    }
    else if (strcmp(argv[1], "type_conversion") == 0) {
        for(int i = 0; i < iterations; i++) type_conversion_confusing(values_a[i % data_size], values_b[i % data_size]);
        for(int i = 0; i < iterations; i++) type_conversion_clean(values_a[i % data_size], values_b[i % data_size]);
    }
    else if (strcmp(argv[1], "logic_as_control_flow") == 0) {
        for(int i = 0; i < iterations; i++) logic_as_control_flow_confusing(conditions[i % data_size]);
        for(int i = 0; i < iterations; i++) logic_as_control_flow_clean(conditions[i % data_size]);
    }
    else if (strcmp(argv[1], "assignment_as_value") == 0) {
        for(int i = 0; i < iterations; i++) assignment_as_value_confusing(values_a[i % data_size]);
        for(int i = 0; i < iterations; i++) assignment_as_value_clean(values_a[i % data_size]);
    }
    else if (strcmp(argv[1], "macro_operator_precedence") == 0) {
        for(int i = 0; i < iterations; i++) macro_operator_precedence_confusing(values_a[i % data_size]);
        for(int i = 0; i < iterations; i++) macro_operator_precedence_clean(values_a[i % data_size]);
    }
    else if (strcmp(argv[1], "preprocessor_in_statement") == 0) {
        for(int i = 0; i < iterations; i++) preprocessor_in_statement_confusing(values_a[i % data_size]);
        for(int i = 0; i < iterations; i++) preprocessor_in_statement_clean(values_a[i % data_size]);
    }
    else if (strcmp(argv[1], "change_of_literal_encoding") == 0) {
        for(int i = 0; i < iterations; i++) change_of_literal_encoding_confusing(values_a[i % data_size]);
        for(int i = 0; i < iterations; i++) change_of_literal_encoding_clean(values_a[i % data_size]);
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