"""
statistics.py
Assignment 7: Multi-Paradigm Problem Solving - Object-oriented approach (Python)

Calculates the mean, median, and mode(s) of a list of integers. The data and
the operations on it are encapsulated in a StatisticsCalculator class, with
one method per statistic.

Run: python statistics.py             (uses the sample dataset)
     python statistics.py 3 1 4 1 5   (uses the integers given on the command line)
"""

import sys


class StatisticsCalculator:
    """Stores a list of integers and calculates summary statistics on it."""

    SAMPLE_DATA = [4, 2, 7, 2, 9, 4, 2, 5, 7, 2]

    def __init__(self, numbers):
        """Validate the input and keep a private copy of the numbers."""
        if not numbers:
            raise ValueError("At least one integer is required.")
        self._numbers = list(numbers)

    @classmethod
    def from_arguments(cls, arguments):
        """Create a calculator from command-line strings, or the sample data
        if no arguments were given. Raises ValueError for non-integers."""
        if not arguments:
            return cls(cls.SAMPLE_DATA)
        numbers = []
        for argument in arguments:
            try:
                numbers.append(int(argument))
            except ValueError:
                raise ValueError(f"'{argument}' is not a valid integer.") from None
        return cls(numbers)

    @property
    def numbers(self):
        """Return a copy, so callers cannot change the internal list."""
        return list(self._numbers)

    def calculate_mean(self):
        """Return the arithmetic mean."""
        return sum(self._numbers) / len(self._numbers)

    def calculate_median(self):
        """Return the middle value, or the average of the two middle values."""
        sorted_numbers = sorted(self._numbers)
        n = len(sorted_numbers)
        if n % 2 == 1:
            return sorted_numbers[n // 2]
        return (sorted_numbers[n // 2 - 1] + sorted_numbers[n // 2]) / 2

    def calculate_mode(self):
        """Return a sorted list of every value that occurs most often
        (ties are kept)."""
        frequency = {}
        for number in self._numbers:
            frequency[number] = frequency.get(number, 0) + 1

        highest_frequency = max(frequency.values())
        return sorted(number for number, count in frequency.items()
                      if count == highest_frequency)

    def summary(self):
        """Return all three statistics in a dictionary."""
        return {
            "mean": self.calculate_mean(),
            "median": self.calculate_median(),
            "mode": self.calculate_mode(),
        }

    def __str__(self):
        """Format the dataset and its statistics as a printable report."""
        stats = self.summary()
        modes = ", ".join(str(value) for value in stats["mode"])
        return (
            "Multi-Paradigm Statistics Program - Python\n"
            "------------------------------------------\n"
            f"Numbers: {' '.join(str(n) for n in self._numbers)}\n\n"
            f"Mean: {stats['mean']:.2f}\n"
            f"Median: {stats['median']:.2f}\n"
            f"Mode: {modes}"
        )


def main():
    try:
        calculator = StatisticsCalculator.from_arguments(sys.argv[1:])
    except ValueError as error:
        print(f"Error: {error}", file=sys.stderr)
        sys.exit(1)
    print(calculator)


if __name__ == "__main__":
    main()
