#ifndef EXPERIMENT_H
#define EXPERIMENT_H

#ifdef __cplusplus
extern "C" {
#endif

void dependent_action();
void independent_action();

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

#ifdef __cplusplus
}
#endif

#endif

