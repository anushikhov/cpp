// Write a function called calculate() that takes two integers
// and a char representing one of the following mathematical operators: +, -, *, /, or % (modulus).
// Use a switch statement to perform the appropriate mathematical operaton on the integers, and return the result.
// If an invalid operator is passed into the function, the function should print an error.
// For the division operator, do an integer division.

#include <iostream>

int getInt()
{
	std::cout << "Enter an integer: ";
	int input{};
	std::cin >> input;

	return input;
}

char getOp()
{
	std::cout << "Enter one of the following operators +, -, *, /, %: ";
	char op{};
	std::cin >> op;

	return op;
}

int calculate(int x, int y, char op)
{
	switch(op)
	{
		case '+':
			return x + y;
		case '-':
			return x - y;
		case '*':
			return x * y;
		case'/':
			return x / y;
		case '%':
			return x % y;
		default:
			{
				std::cout << "Invalid operator.\n";
				op = getOp();				// implementing a suitable weird logic :p
				return calculate(x, y, op);
			}
	}
}

int main()
{
	int x{ getInt() };
	int y{ getInt() };
	char op{ getOp() };

	std::cout << calculate( x, y, op);

	return 0;
}
