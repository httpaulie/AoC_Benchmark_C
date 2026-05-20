#ifndef EXPERIMENT_H
#define EXPERIMENT_H

#ifdef __cplusplus
extern "C" {
#endif

extern volatile int conditional_counter;
extern volatile int inconditional_counter;
extern volatile int global_result;

void dependent_action();
void independent_action();
int dependent_action_return();

//Omitted Curly Braces
void omitted_curly_braces_confusing(int condition_flag);
void omitted_curly_braces_clean(int condition_flag);

//Implicit Predicate
void implicit_predicate_confusing(int condition_flag);
void implicit_predicate_clean(int condition_flag);

//Infix Operator Precedence
void infix_precedence_confusing(int a, int b, int c);
void infix_precedence_clean(int a, int b, int c);

//Conditional Operator
void conditional_operator_confusing(int condition_flag, int val1, int val2);
void conditional_operator_clean(int condition_flag, int val1, int val2);

//Post Incremnt/Decrement
void post_increment_confusing(int base_value);
void post_increment_clean(int base_value);

// Repurposed Variable
void repurposed_variable_confusing(int input_val, int modifier);
void repurposed_variable_clean(int input_val, int modifier);

// Pre Increment/Decrement
void pre_increment_confusing(int base_value);
void pre_increment_clean(int base_value);

// Comma Operator
void comma_operator_confusing(int base_value);
void comma_operator_clean(int base_value);

// Reversed Subscripts
void reversed_subscripts_confusing(int index);
void reversed_subscripts_clean(int index);

// Type Conversion
void type_conversion_confusing(int num, int den);
void type_conversion_clean(int num, int den);

// Logic as Control Flow
void logic_as_control_flow_confusing(int condition_flag);
void logic_as_control_flow_clean(int condition_flag);

// Assignment as Value
void assignment_as_value_confusing(int val);
void assignment_as_value_clean(int val);

// Macro Operator Precedence
void macro_operator_precedence_confusing(int val);
void macro_operator_precedence_clean(int val);

// Preprocessor in Statement
void preprocessor_in_statement_confusing(int val);
void preprocessor_in_statement_clean(int val);

// Change of Literal Encoding
void change_of_literal_encoding_confusing(int val);
void change_of_literal_encoding_clean(int val);

#ifdef __cplusplus
}
#endif

#endif

