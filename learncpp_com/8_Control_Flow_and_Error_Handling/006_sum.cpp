// Write a function named sumTo() that takes an integer parameter named value,
// and returns the sum of all the numbers from 1 to value.

#include <iostream>

int sumTo(int value)
{
	int sum{ 0 };
	for(int i{ 1 }; i <= value; ++i)
	{
		sum += i;
	}

	return sum;
}

int getValue()
{
	std::cout << "Enter an integer: ";
	int value{};
	std::cin >> value;

	return value;
}

void printSum(int value, int sum)
{
	std::cout << "The sum of numbers up to " << value << " is " << sum << ".\n";
}

int main()
{
	int value{ getValue() };
	int sum { sumTo(value) };

	printSum(value, sum);

	return 0;
}
