// A implementação do nanobench deve ser definida antes do include
#define ANKERL_NANOBENCH_IMPLEMENT
#include "nanobench.h"
#include "experiment.h"
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {
    // 1. VERIFICAÇÃO DE ARGUMENTOS (CLI)
    if (argc < 2) {
        std::cout << "Erro: Nenhum atomo especificado.\n";
        std::cout << "Uso correto: .\\benchmark.exe <nome_do_atomo>\n\n";
        std::cout << "Opcoes disponiveis:\n";
        std::cout << "  omitted_curly\n";
        std::cout << "  implicit_predicate\n";
        std::cout << "  infix_precedence\n";
        std::cout << "  conditional_operator\n";
        std::cout << "  post_increment\n";
        return 1;
    }

    std::string atomo_escolhido = argv[1];

    // 2. GERAÇÃO DE DADOS PARA A CARGA DE TRABALHO
    // Usamos 8192 (potência de 2) para podermos usar máscara de bits (& 8191) em vez de módulo (%),
    // que é uma operação muito mais rápida para a CPU e não suja a medição do tempo.
    const size_t DATA_SIZE = 8192;
    const size_t MASK = DATA_SIZE - 1; 

    std::vector<int> condicoes(DATA_SIZE);
    std::vector<int> valores_a(DATA_SIZE);
    std::vector<int> valores_b(DATA_SIZE);

    for (size_t i = 0; i < DATA_SIZE; ++i) {
        condicoes[i] = i % 2;
        valores_a[i] = (i % 10) + 1;
        valores_b[i] = (i % 5) + 1;
    }

    size_t indice = 0;

    // 3. CONFIGURAÇÃO DO BENCHMARK
    ankerl::nanobench::Bench bench;
    bench.title("Atomo: " + atomo_escolhido);
    bench.relative(true); // Adiciona uma coluna mostrando quem foi % mais rápido

    // 4. ROTEAMENTO DOS TESTES
    if (atomo_escolhido == "omitted_curly") {
        
        bench.run("Confuso", [&] {
            omitted_curly_braces_confusing(condicoes[indice & MASK]);
            indice++;
        });
        
        indice = 0; // Reseta o índice para o teste da versão limpa
        
        bench.run("Limpo", [&] {
            omitted_curly_braces_clean(condicoes[indice & MASK]);
            indice++;
        });

    } 
    else if (atomo_escolhido == "implicit_predicate") {
        
        bench.run("Confuso", [&] {
            implicit_predicate_confusing(condicoes[indice & MASK]);
            indice++;
        });
        indice = 0;
        bench.run("Limpo", [&] {
            implicit_predicate_clean(condicoes[indice & MASK]);
            indice++;
        });

    }
    else if (atomo_escolhido == "infix_precedence") {
        
        bench.run("Confuso", [&] {
            infix_precedence_confusing(condicoes[indice & MASK], valores_a[indice & MASK], valores_b[indice & MASK]);
            indice++;
        });
        indice = 0;
        bench.run("Limpo", [&] {
            infix_precedence_clean(condicoes[indice & MASK], valores_a[indice & MASK], valores_b[indice & MASK]);
            indice++;
        });

    }
    else if (atomo_escolhido == "conditional_operator") {
        
        bench.run("Confuso", [&] {
            conditional_operator_confusing(condicoes[indice & MASK], valores_a[indice & MASK], valores_b[indice & MASK]);
            indice++;
        });
        indice = 0;
        bench.run("Limpo", [&] {
            conditional_operator_clean(condicoes[indice & MASK], valores_a[indice & MASK], valores_b[indice & MASK]);
            indice++;
        });

    }
    else if (atomo_escolhido == "post_increment") {
        
        bench.run("Confuso", [&] {
            post_increment_confusing(valores_a[indice & MASK]);
            indice++;
        });
        indice = 0;
        bench.run("Limpo", [&] {
            post_increment_clean(valores_a[indice & MASK]);
            indice++;
        });

    }
    else {
        std::cout << "Erro: Atomo '" << atomo_escolhido << "' desconhecido.\n";
        return 1;
    }

    return 0;
}