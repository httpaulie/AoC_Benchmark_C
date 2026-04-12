# Atoms of Confusion C Benchmark

This is an experimental C tool for evaluating the impact of Atoms of Confusion on runtime performance compared to clean code.

## About the Project

This project consists of a suite of micro-benchmarks designed to test code snippets containing **Atoms of Confusion** (syntactically valid programming patterns that are highly confusing to humans). 

The main goal is to answer the question: *Does the structural confusion in code also result in performance penalties for the machine, or is it merely a cognitive burden for the programmer?*

⚠️ **Warning:** This is an work in progress. It serves purely as a laboratory for academic and personal testing and experimentation, and should not be considered a professional benchmarking tool. New atoms and tests will be added over time.

## Quickstart Guide

If you already have the compiled executable and want to use the default parameters, simply open a terminal in the project folder and run:

### On Windows:
```bash
.\benchmark
```

### On Linux / Mac:
```bash
./benchmark
```

When run without arguments (or depending on the implementation), the program will display a help menu on the terminal listing the atom options available for testing.

## Compilation and Customization

If you want to change the experiment parameters (such as increasing or decreasing the workload/number of iterations in `main.c`), you will need to recompile the code.

### Pre-Requisites
* Having **GCC** (GNU Compiler Collection) installed in your system.

### Compiling
Open the terminal in the project root directory and run the following command:

```bash
gcc main.c functions.c -O0 -o benchmark
```

### Optimization Flag (`-O0`)
By default, the command above uses the `-O0` flag. This **disables** the compiler optimizations. 
* **Why is this important?** Modern compilers often rewrite or “clean up” poorly structured code during compilation. To test the actual cost of the confusion atom on the CPU, we need to force the compiler to translate the code exactly as it was written.
* If you want to test whether the compiler can “save” the performance of messy code, feel free to change this flag to `-O2` or `-O3` and recompile.

## Repository Structure

* `main.c`: It includes the workload, iteration control, measurement timers, and the command-line interface.
* `functions.c`: Contains the paired implementations (Confused vs. Clean) for each atom studied.
* `experiment.h`: Header file containing function signatures.
