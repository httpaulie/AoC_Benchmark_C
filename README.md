# Atoms of Confusion C Benchmark

This is an experimental evaluation tool for analyzing the impact of Atoms of Confusion on runtime performance and hardware utilization compared to clean code equivalents.

## About the Project

This project consists of a suite of micro-benchmarks designed to test code snippets containing **Atoms of Confusion** (syntactically valid programming patterns that are highly confusing to humans). 

The main goal is to answer the question: *Does the structural confusion in code also result in performance penalties for the machine, or is it merely a cognitive burden for the programmer?*

⚠️ **Warning:** This is an work in progress. It serves purely as a laboratory for academic and personal testing and experimentation. New atoms and tests will be added over time.

## Quickstart Guide

To run the benchmark and see the statistical table, you must pass the name of the atom you want to test as an argument.

### On Windows/Linux/Mac:
```bash
./benchmark
```

When run without arguments (or depending on the implementation), the program will display a help menu on the terminal listing the atom options available for testing.

## Compilation and Customization

If you want to alter the experiment parameters or add new atoms, you will need to recompile the code. 

### Pre-Requisites
* **G++** (GNU C++ Compiler).
* *(Optional)* **Valgrind** (Linux/WSL).

### Compiling
Open the terminal in the project root directory and run the following command:

```bash
g++ main.cpp functions.c -O0 -g -o benchmark
```

### Important Compilation Flags
* `-O0`: By default, the command above uses the `-O0` flag. This **disables** the compiler optimizations. Modern compilers often rewrite or “clean up” poorly structured code during compilation. To test the actual cost of the atom of confusion on the CPU, we need to force the compiler to translate the code exactly as it was written. (Change to `-O2` or `-O3` to test compiler mitigation).
* `-g`: Generates debugging information, which is crucial if you plan to run the executable through Valgrind to track cache misses back to the exact line of code.

## Repository Structure

* `main.cpp`: It includes the workload, nanobench setup, and the command-line interface.
* `functions.c`: Contains the paired implementations (Confused vs. Clean) for each atom studied.
* `experiment.h`: Header file containing function signatures.
* `nanobench.h`: The external header-only benchmarking library.
