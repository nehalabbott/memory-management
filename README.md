# Memory Management Simulator

A C++ simulator for virtual memory management that implements multiple page table architectures and page replacement policies while benchmarking their performance on **1M+ memory accesses**.

## Features

- Single-Level Page Table
- Two-Level Page Table
- Hash Page Table
- LRU Page Replacement
- FIFO Page Replacement
- Benchmarking Framework
- CSV Export of Results
- Locality-aware Memory Trace Generation

## Tech Stack

- C++17
- STL
- Object-Oriented Programming

## Project Structure

```
include/
src/
results/
scripts/
README.md
```

## Build

```bash
g++ -std=c++17 src/*.cpp -Iinclude -o simulator
```

## Run

```bash
./simulator
```
