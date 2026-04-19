#define ANKERL_NANOBENCH_IMPLEMENT
#include "nanobench.h"
#include "experiment.h"
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "No specified atom.\n";
        std::cout << "How to use: .\\benchmark.exe <atom_name>\n\n";
        std::cout << "Available options:\n";
        std::cout << "  omitted_curly\n";
        std::cout << "  implicit_predicate\n";
        std::cout << "  infix_precedence\n";
        std::cout << "  conditional_operator\n";
        std::cout << "  post_increment\n";
        return 1;
    }

    std::string chosen_atom = argv[1];

    const size_t DATA_SIZE = 8192;
    const size_t MASK = DATA_SIZE - 1; 

    std::vector<int> conditions(DATA_SIZE);
    std::vector<int> values_a(DATA_SIZE);
    std::vector<int> values_b(DATA_SIZE);

    for (size_t i = 0; i < DATA_SIZE; ++i) {
        conditions[i] = i % 2;
        values_a[i] = (i % 10) + 1;
        values_b[i] = (i % 5) + 1;
    }

    size_t index = 0;

    ankerl::nanobench::Bench bench;
    bench.title("Atom: " + chosen_atom);
    bench.relative(true);

    if (chosen_atom == "omitted_curly") {
        
        bench.run("Confusing", [&] {
            omitted_curly_braces_confusing(conditions[index & MASK]);
            index++;
        });
        
        index = 0; // Reseta o índice para o teste da versão limpa
        
        bench.run("Clean", [&] {
            omitted_curly_braces_clean(conditions[index & MASK]);
            index++;
        });

    } 
    else if (chosen_atom == "implicit_predicate") {
        
        bench.run("Confusing", [&] {
            implicit_predicate_confusing(conditions[index & MASK]);
            index++;
        });
        index = 0;
        bench.run("Clean", [&] {
            implicit_predicate_clean(conditions[index & MASK]);
            index++;
        });

    }
    else if (chosen_atom == "infix_precedence") {
        
        bench.run("Confusing", [&] {
            infix_precedence_confusing(conditions[index & MASK], values_a[index & MASK], values_b[index & MASK]);
            index++;
        });
        index = 0;
        bench.run("Clean", [&] {
            infix_precedence_clean(conditions[index & MASK], values_a[index & MASK], values_b[index & MASK]);
            index++;
        });

    }
    else if (chosen_atom == "conditional_operator") {
        
        bench.run("Confusing", [&] {
            conditional_operator_confusing(conditions[index & MASK], values_a[index & MASK], values_b[index & MASK]);
            index++;
        });
        index = 0;
        bench.run("Clean", [&] {
            conditional_operator_clean(conditions[index & MASK], values_a[index & MASK], values_b[index & MASK]);
            index++;
        });

    }
    else if (chosen_atom == "post_increment") {
        
        bench.run("Confusing", [&] {
            post_increment_confusing(values_a[index & MASK]);
            index++;
        });
        index = 0;
        bench.run("Clean", [&] {
            post_increment_clean(values_a[index & MASK]);
            index++;
        });

    }
    else {
        std::cout << "Error: Atom '" << chosen_atom << "' unknown.\n";
        return 1;
    }

    return 0;
}