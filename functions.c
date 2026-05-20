#include "experiment.h"
#include <math.h>

volatile int conditional_counter = 0;
volatile int inconditional_counter = 0;
volatile int global_result = 0;

//Occurs only IF is true
void dependent_action(){
    conditional_counter++;
}

int dependent_action_return(){
    conditional_counter++;
    return 1;
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


//REPURPOSED VARIABLE
void repurposed_variable_confusing(int input_val, int modifier){
    input_val = input_val + modifier; 
    global_result = input_val;
}

void repurposed_variable_clean(int input_val, int modifier){
    int final_value = input_val + modifier; 
    global_result = final_value;
}

// PRE INCREMENT
void pre_increment_confusing(int base_value){
    int temp = base_value;
    global_result = ++temp;
}

void pre_increment_clean(int base_value){
    int temp = base_value;
    temp += 1;
    global_result = temp;
}

// COMMA OPERATOR
void comma_operator_confusing(int base_value){
    int temp = base_value;
    global_result = (temp++, temp);
}

void comma_operator_clean(int base_value){
    int temp = base_value;
    temp++;
    global_result = temp;
}

// REVERSED SUBSCRIPTS
void reversed_subscripts_confusing(int index){
    const char* str = "abc";
    global_result = index[str]; 
}

void reversed_subscripts_clean(int index){
    const char* str = "abc";
    global_result = str[index]; 
}

// TYPE CONVERSION
void type_conversion_confusing(int num, int den){
    global_result = num / den; 
}

void type_conversion_clean(int num, int den){
    global_result = (int)trunc((double)num / (double)den); 
}

// LOGIC AS CONTROL FLOW
void logic_as_control_flow_confusing(int condition_flag){
    condition_flag && dependent_action_return();
}

void logic_as_control_flow_clean(int condition_flag){
    if (condition_flag) {
        dependent_action_return();
    }
}

// ASSIGNMENT AS VALUE
void assignment_as_value_confusing(int val){
    int v1;
    global_result = v1 = val;
}

void assignment_as_value_clean(int val){
    int v1 = val;
    global_result = v1;
}

// MACRO OPERATOR PRECEDENCE
#define M1_CONFUSING 64 - 1
void macro_operator_precedence_confusing(int val){
    global_result = val * M1_CONFUSING; 
}

void macro_operator_precedence_clean(int val){
    // Escrito de forma literal e explícita
    global_result = val * 64 - 1; 
}

// PREPROCESSOR IN STATEMENT
void preprocessor_in_statement_confusing(int val){
    int v1 = val
    #define M2_DUMMY 1
    + 1;
    
    global_result = v1;
}

void preprocessor_in_statement_clean(int val){
    #define M3_DUMMY 1
    int v1 = val + 1;
    
    global_result = v1;
}

// CHANGE OF LITERAL ENCODING
void change_of_literal_encoding_confusing(int val){
    global_result = val + (208 & 13);
}

void change_of_literal_encoding_clean(int val){
    global_result = val + (0xD0 & 0x0D);
}