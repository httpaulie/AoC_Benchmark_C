#include "experiment.h"

volatile int conditional_counter = 0;
volatile int inconditional_counter = 0;
volatile int global_result = 0;

//Occurs only IF is true
void dependent_action(){
    conditional_counter++;
}

void independent_action(){
    inconditional_counter++;
}


//OMITTED CURLY BRACES
void omitted_curly_braces_confusing(int condition_flag){
    if(condition_flag) dependent_action(); independent_action();
}

void omitted_curly_braces_clean(int condition_flag){
    if(condition_flag){
        dependent_action();
    }
    independent_action();
}

//IMPLICIT PREDICATE
void implicit_predicate_confusing(int condition_flag){
    if(condition_flag){
        dependent_action();
    }
}

void implicit_predicate_clean(int condition_flag){
    //Explicits the comparison
    if(condition_flag != 0){
        dependent_action();
    }
}

//INFIX OPERATOR PRECEDENCE
void infix_precedence_confusing(int a, int b, int c){
    if(a && b || c){
        dependent_action();
    }
}

void infix_precedence_clean(int a, int b, int c){
    if((a && b) || c){
        dependent_action();
    }
}

//CONDITIONAL OPERATOR
void conditional_operator_confusing(int condition_flag, int val1, int val2){
    global_result = (condition_flag) ? val1 : val2;
}

void conditional_operator_clean(int condition_flag, int val1, int val2){
    if(condition_flag){
        global_result = val1;
    } else {
        global_result = val2;
    }
}

//POST INCREMENT
void post_increment_confusing(int base_value){
    int temp = base_value;
    global_result = temp++;
}

void post_increment_clean(int base_value){
    int temp = base_value;
    global_result = temp;
    temp += 1;
}