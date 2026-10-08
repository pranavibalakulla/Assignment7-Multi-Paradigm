# Assignment 7: Multi-Paradigm Problem Solving

## Overview

This project implements a statistics program in three different programming languages:

- C
- OCaml
- Python

The program calculates three basic statistics from a list of integers:

- Mean
- Median
- Mode

The assignment demonstrates how the same problem can be solved using different programming paradigms.

## Programming Paradigms

### C – Procedural Programming

The C implementation uses a procedural approach. It uses functions, arrays, loops, sorting, and direct counting logic to calculate the statistics.

File:

`statistics.c`

### OCaml – Functional Programming

The OCaml implementation uses a functional programming approach. It uses immutable lists and functional operations such as `List.fold_left`, `List.sort`, and `List.filter`-style processing.

File:

`statistics.ml`

### Python – Object-Oriented Programming

The Python implementation uses an object-oriented approach. The `StatisticsCalculator` class contains separate methods for calculating the mean, median, and mode.

File:

`statistics.py`

## Sample Dataset

The programs use the following list of integers:

```text
[4, 2, 7, 2, 9, 4, 2, 5, 7, 2]