class StatisticsCalculator:
    """Calculate basic statistics using an object-oriented approach."""

    def __init__(self, numbers):
        self.numbers = numbers

    def calculate_mean(self):
        """Calculate the mean."""
        return sum(self.numbers) / len(self.numbers)

    def calculate_median(self):
        """Calculate the median."""
        sorted_numbers = sorted(self.numbers)
        n = len(sorted_numbers)

        if n % 2 == 1:
            return sorted_numbers[n // 2]
        else:
            middle1 = sorted_numbers[n // 2 - 1]
            middle2 = sorted_numbers[n // 2]
            return (middle1 + middle2) / 2

    def calculate_mode(self):
        """Calculate the mode."""
        frequency = {}

        for number in self.numbers:
            if number in frequency:
                frequency[number] += 1
            else:
                frequency[number] = 1

        highest_frequency = max(frequency.values())

        modes = [
            number
            for number, count in frequency.items()
            if count == highest_frequency
        ]

        return modes


def main():
    numbers = [4, 2, 7, 2, 9, 4, 2, 5, 7, 2]

    calculator = StatisticsCalculator(numbers)

    mean = calculator.calculate_mean()
    median = calculator.calculate_median()
    mode = calculator.calculate_mode()

    print("Multi-Paradigm Statistics Program - Python")
    print("------------------------------------------")

    print("Numbers:", numbers)
    print()

    print(f"Mean: {mean:.2f}")
    print(f"Median: {median:.2f}")
    print(f"Mode: {mode}")


if __name__ == "__main__":
    main()