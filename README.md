# Assignment 7: Multi-Paradigm Problem Solving

## Overview

This project implements the same statistics program in three languages, each written in a different programming paradigm. Given a list of integers, every version calculates:

- **Mean** – the average of all integers in the list
- **Median** – the middle value of the sorted list (the average of the two middle values when the length is even)
- **Mode** – every integer that occurs most often (ties are all reported)

| Language | Paradigm | File |
|---|---|---|
| C | Procedural | `statistics.c` |
| OCaml | Functional | `statistics.ml` |
| Python | Object-oriented | `statistics.py` |

## Programming Paradigms

### C – Procedural

Separate functions (`calculate_mean`, `calculate_median`, `calculate_modes`) operate on an array of integers. Sorting (insertion sort) and frequency counting are implemented directly. All arrays are allocated with `malloc` and released with `free`, since C has no garbage collector.

### OCaml – Functional

Pure functions over immutable lists, with no mutable state. Statistics are computed with higher-order functions: `List.fold_left` for the sum and the frequency table, `List.filter` and `List.map` for the modes. Empty input is handled with `option` values instead of exceptions.

### Python – Object-Oriented

A `StatisticsCalculator` class encapsulates the data (stored privately) with one method per statistic: `calculate_mean`, `calculate_median`, and `calculate_mode`. A dictionary stores value frequencies. The class also offers a `from_arguments` constructor, a `summary` method, and a `__str__` report.

## How to Run

Each program uses the sample dataset by default, or any integers passed on the command line.

```bash
# C
gcc -Wall -Wextra -o statistics statistics.c
./statistics                 # Windows: .\statistics.exe
./statistics 1 1 2 2 3

# OCaml
ocaml statistics.ml
ocaml statistics.ml 1 1 2 2 3

# Python
python statistics.py
python statistics.py 1 1 2 2 3
```

Invalid input (for example `3 abc 4`) prints an error message instead of crashing.

## Sample Dataset

```text
[4, 2, 7, 2, 9, 4, 2, 5, 7, 2]
```

## Sample Output

```text
Mean: 4.40
Median: 4.00
Mode: 2
```

With `1 1 2 2 3` as input, every version reports both modes: `Mode: 1, 2`.
