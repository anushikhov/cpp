// Create a struct to hold a fraction.
// The struct should have an integer numerator and an integer denominator member.
// Declare 2 fraction variables and read them in from the user.
// Write a fraction called multiply that takes both fractions, multiplies them together,
// and returns the result as a decimal number.
// You do not need to reduce the fraction to its lowest terms.
// Print the result of the multiplication of the 2 fraction variables.

#include <iostream>

struct Fraction
{
	int numerator{};
	int denominator{};
};

Fraction getFraction()
{
	Fraction fraction{};

	std::cout << "Enter the numerator of the fraction: ";
	std::cin >> fraction.numerator;

	std::cout << "Enter the denominator of the fraction: ";
	std::cin >> fraction.denominator;

	return fraction;
}

double multiply(Fraction x, Fraction y)
{
	return (static_cast<double>(x.numerator * y.numerator) / (x.denominator * y.denominator));
}

void printResult(Fraction x, Fraction y)
{
	std::cout << multiply(x, y);
}

int main()
{
	Fraction x{ getFraction() };
	Fraction y{ getFraction() };

	printResult(x, y);

	return 0;
}
