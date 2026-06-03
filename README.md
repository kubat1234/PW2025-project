# Taxi Routes

This repository contains a small concurrent programming project for the *Taksówki* assignment. It compares several implementations of the same graph algorithm, from a simple baseline to optimized multi-threaded and OpenMP versions.

## Task

Given an undirected graph and many queries, determine whether there exists a walk of exactly `d` edges between two vertices. The full task statement is included in [statement.pdf](statement.pdf).

## Solutions

- `slow.cpp` uses a parity-aware BFS from every start vertex.
- `optimized.cpp` and `optimized2.cpp` reduce allocation and queue overhead in the single-threaded version.
- `thread.cpp` and `thread2.cpp` parallelize the outer loop with `std::thread`.
- `omp.cpp` and `omp2.cpp` do the same with OpenMP.

## Results

The best variants in this repo are `thread2.cpp` and `omp2.cpp`.

| Version | Laptop | Student server |
| --- | ---: | ---: |
| `slow.cpp` | 10.16s | 17.54s |
| `optimized2.cpp` | 2.45s | 7.36s |
| `thread2.cpp` | 1.37s | 2.81s |
| `omp2.cpp` | 1.36s | 3.21s |

The source files are in [src/](src), and the benchmark binaries are built into [build/](build).