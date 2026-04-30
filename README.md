# Atoms of Confusion Benchmark Suite

This is an experimental evaluation tool for analyzing the impact of Atoms of Confusion on runtime performance and hardware utilization compared to clean code equivalents.

## About the Project

This project consists of a suite of micro-benchmarks designed to test code snippets containing **Atoms of Confusion** (syntactically valid programming patterns that are highly confusing to humans). 

The main goal is to answer the question: *Does the structural confusion in code also result in performance penalties for the machine, or is it merely a cognitive burden for the programmer?*

⚠️ **Warning:** This is an work in progress. It serves purely as a laboratory for academic and personal testing and experimentation. New atoms and tests will be added over time.

## Quickstart Guide

To run the benchmarks, you must pass the name of the atom you want to test as an argument. The project is divided into two isolated evaluation environments to prevent measurement interference: CPU/Time profiling and Memory footprint analysis.

### 1. CPU and Performance Profiling (Nanobench):
```bash
./benchmark_linux <atom_name>
```
### 2. CPU and Performance Profiling (Nanobench):
```bash
valgrind --tool=cachegrind --cache-sim=yes ./benchmark_memory <atom_name>
```

When run without arguments (or depending on the implementation), the program will display a help menu on the terminal listing the atom options available for testing.

## Automated Data Collection
This repository includes automated bash scripts for high-precision data collection. To avoid the distortions on the metrics, the collection is separated into two scripts.


### Prerequisites
This script requires a Linux environment (or WSL) with Valgrind installed. Before using it for the first time, grant execution permissions:
```bash
chmod +x collector.sh collector_memory.sh
```

### CPU Collector `(collector.sh)`
Pins the execution to a single CPU core and runs the Nanobench suite multiple times (defaults to 30), automatically rejecting iterations with high measurement noise (> 5% error margin).
```bash
./collector.sh <atom_name> [number_of_executions]
```
**Output:** `result_<atom_name>_cpu.csv`

### Memory Collector `(collector_memory.sh)`
Runs a version of the benchmark without the Nanobench framework purely inside Valgrind to extract deterministic data reads and writes from the L1 Cache.
```bash
./collector_memory.sh <atom_name> [number_of_executions]
```
**Output:** `result_<atom_name>_memory_.csv`

## Compilation and Customization

If you want to alter the experiment parameters or add new atoms, you will need to recompile the code. 

### Pre-Requisites
* **G++** (GNU C++ Compiler).

### Compiling
Open the terminal in the project root directory. You must compile the two separate executables:

## 1. Compile the CPU Benchmark

```bash
g++ main.cpp functions.c -O0 -g -o benchmark_linux
```

## 2. Compile the Memory Benchmark

```bash
g++ main_memory.cpp functions.c -O0 -g -o benchmark_memory
```

### Important Compilation Flags
* `-O0`: By default, the command above uses the `-O0` flag. This **disables** the compiler optimizations. Modern compilers often rewrite or “clean up” poorly structured code during compilation. To test the actual cost of the atom of confusion on the CPU, we need to force the compiler to translate the code exactly as it was written. (Change to `-O2` or `-O3` to test compiler mitigation).
* `-g`: Generates debugging information, which is crucial if you plan to run the executable through Valgrind to track cache misses back to the exact line of code.

## Repository Structure

* `main.cpp`: It includes the workload, nanobench setup, and the command-line interface.
* `main_memory.cpp`: A workload runner for Valgrind simulation.
* `functions.c`: Contains the paired implementations (Confused vs. Clean) for each atom studied.
* `experiment.h`: Header file containing function signatures.
* `nanobench.h`: The external header-only benchmarking library.
* `collector.h`: Bash script for automated CPU benchmark iteration and CSV generation.
* `collector_memory.h`: Bash script for memory footprint extraction.
