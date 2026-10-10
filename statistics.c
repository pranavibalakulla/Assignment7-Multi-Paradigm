/*
 * statistics.c
 * Assignment 7: Multi-Paradigm Problem Solving - Procedural approach (C)
 *
 * Calculates the mean, median, and mode(s) of a list of integers.
 * The integers are stored in a dynamically allocated array. Sorting and
 * counting are implemented directly, and every block of heap memory is
 * released manually with free(), because C has no garbage collector.
 *
 * Build: gcc -Wall -Wextra -o statistics statistics.c
 * Run:   ./statistics             (uses the sample dataset)
 *        ./statistics 3 1 4 1 5   (uses the integers given on the command line)
 */

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

/* Sample dataset used when no numbers are given on the command line. */
static const int SAMPLE_DATA[] = {4, 2, 7, 2, 9, 4, 2, 5, 7, 2};
#define SAMPLE_COUNT (sizeof(SAMPLE_DATA) / sizeof(SAMPLE_DATA[0]))

/* Allocates a new heap array and copies 'count' integers into it.
 * Returns NULL if allocation fails. The caller must free the result. */
int *copy_array(const int *source, size_t count) {
    int *copy = malloc(count * sizeof(int));
    if (copy == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < count; i++) {
        copy[i] = source[i];
    }
    return copy;
}

/* Sorts the array in ascending order, in place, using insertion sort. */
void insertion_sort(int *values, size_t count) {
    for (size_t i = 1; i < count; i++) {
        int current = values[i];
        size_t j = i;
        while (j > 0 && values[j - 1] > current) {
            values[j] = values[j - 1];
            j--;
        }
        values[j] = current;
    }
}

/* Returns the arithmetic mean. The sum uses long long to avoid overflow. */
double calculate_mean(const int *values, size_t count) {
    long long sum = 0;
    for (size_t i = 0; i < count; i++) {
        sum += values[i];
    }
    return (double)sum / (double)count;
}

/* Returns the median. A sorted copy is used so the caller's array is not
 * changed; the copy is freed before returning. Returns 0 on allocation
 * failure (reported through *ok). */
double calculate_median(const int *values, size_t count, int *ok) {
    int *sorted = copy_array(values, count);
    if (sorted == NULL) {
        *ok = 0;
        return 0.0;
    }
    insertion_sort(sorted, count);

    double median;
    if (count % 2 == 1) {
        median = sorted[count / 2];
    } else {
        median = ((double)sorted[count / 2 - 1] + (double)sorted[count / 2]) / 2.0;
    }

    free(sorted);
    *ok = 1;
    return median;
}

/* Finds every value that occurs with the highest frequency.
 * Works on a sorted copy so equal values sit next to each other and can be
 * counted in runs. Returns a new heap array of modes and stores how many
 * there are in *mode_count. Returns NULL on allocation failure.
 * The caller must free the result. */
int *calculate_modes(const int *values, size_t count, size_t *mode_count) {
    int *sorted = copy_array(values, count);
    if (sorted == NULL) {
        return NULL;
    }
    insertion_sort(sorted, count);

    /* First pass: find the length of the longest run of equal values. */
    size_t highest = 0;
    size_t run = 0;
    for (size_t i = 0; i < count; i++) {
        run = (i > 0 && sorted[i] == sorted[i - 1]) ? run + 1 : 1;
        if (run > highest) {
            highest = run;
        }
    }

    /* Second pass: collect every value whose run reaches that length. */
    int *modes = malloc(count * sizeof(int));
    if (modes == NULL) {
        free(sorted);
        return NULL;
    }
    *mode_count = 0;
    run = 0;
    for (size_t i = 0; i < count; i++) {
        run = (i > 0 && sorted[i] == sorted[i - 1]) ? run + 1 : 1;
        if (run == highest) {
            modes[(*mode_count)++] = sorted[i];
        }
    }

    free(sorted);
    return modes;
}

/* Converts the command-line arguments into a heap array of integers.
 * Returns 1 on success, 0 if an argument is not a valid integer or memory
 * runs out. On success the caller must free *values. */
int parse_arguments(int argc, char *argv[], int **values, size_t *count) {
    *count = (size_t)(argc - 1);
    *values = malloc(*count * sizeof(int));
    if (*values == NULL) {
        fprintf(stderr, "Error: out of memory.\n");
        return 0;
    }

    for (int i = 1; i < argc; i++) {
        char *end;
        errno = 0;
        long number = strtol(argv[i], &end, 10);
        if (end == argv[i] || *end != '\0' || errno == ERANGE ||
            number < INT_MIN || number > INT_MAX) {
            fprintf(stderr, "Error: '%s' is not a valid integer.\n", argv[i]);
            free(*values);
            *values = NULL;
            return 0;
        }
        (*values)[i - 1] = (int)number;
    }
    return 1;
}

/* Prints the integers on one line, separated by spaces. */
void print_numbers(const int *values, size_t count) {
    printf("Numbers: ");
    for (size_t i = 0; i < count; i++) {
        printf("%s%d", (i > 0) ? " " : "", values[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    int *numbers = NULL;
    size_t count = 0;

    /* Use command-line numbers if given, otherwise the sample dataset. */
    if (argc > 1) {
        if (!parse_arguments(argc, argv, &numbers, &count)) {
            return 1;
        }
    } else {
        count = SAMPLE_COUNT;
        numbers = copy_array(SAMPLE_DATA, count);
        if (numbers == NULL) {
            fprintf(stderr, "Error: out of memory.\n");
            return 1;
        }
    }

    double mean = calculate_mean(numbers, count);

    int median_ok = 0;
    double median = calculate_median(numbers, count, &median_ok);

    size_t mode_count = 0;
    int *modes = calculate_modes(numbers, count, &mode_count);

    if (!median_ok || modes == NULL) {
        fprintf(stderr, "Error: out of memory.\n");
        free(modes);
        free(numbers);
        return 1;
    }

    printf("Multi-Paradigm Statistics Program - C\n");
    printf("-------------------------------------\n");
    print_numbers(numbers, count);
    printf("\n");
    printf("Mean: %.2f\n", mean);
    printf("Median: %.2f\n", median);
    printf("Mode: ");
    for (size_t i = 0; i < mode_count; i++) {
        printf("%d%s", modes[i], (i + 1 < mode_count) ? ", " : "\n");
    }

    /* Release all heap memory before exiting. */
    free(modes);
    free(numbers);
    return 0;
}
