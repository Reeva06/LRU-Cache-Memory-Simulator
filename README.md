# LRU Cache Architecture & Memory Replacement Simulator (C)

## Overview
This repository contains a performance-driven **Cache Memory Simulator** written in C, modeling the **Least Recently Used (LRU)** page replacement policy. The simulator evaluates memory access patterns, eviction penalties, and hit/miss dynamics representative of modern SSD controller buffering and hierarchical memory architectures.

## Architectural Features
- **Configurable Cache Sizing:** Parameterized cache lines (`CACHE_CAPACITY`, default: 4 slots).
- **LRU Eviction Mechanism:** Tracks memory recency using logical timestamps to resolve optimal block eviction.
- **Trace Evaluation:** Simulates sequential and non-contiguous memory reference strings.
- **Analytical Metrics:** Provides runtime hit/miss logs, cache state snapshots, and final Hit/Miss ratio computations.

## Simulation Output
Compiled and executed using GCC with runtime terminal logging.

![Simulation Output](cache_output.png)

### Key Metrics Observed:
- Handles compulsory misses during initial cache warmup.
- Correctly identifies temporal locality to yield cache hits.
- Evaluates replacement overhead with deterministic LRU evictions.

## How to Compile & Run

### Local GCC Compilation:
```bash
gcc -Wall -O2 lru_cache_sim.c -o lru_cache_sim
./lru_cache_sim
