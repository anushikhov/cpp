// Write the following program:
// The user is asked to enter 2 floating point numbers (use doubles).
// The user is then asked to enter one of the following mathematical symbols: +, -, *, or /.
// The program computes the answer on the two numbers the user entered and prints the results.
// If the user enters an invalid symbol, the program should print nothing.

#include <iostream>

double getValue()
{
	std::cout << "Enter a double value: ";
	double input{};
	std::cin >> input;

	return input;
}

char getOperator()
{
	std::cout << "Enter one of the following: +, -, *, or /: ";
	char input{};
	std::cin >> input;

	return input;
}

void printResult(double firstNumber, double secondNumber, char op)
{
	if(op == '+')
		std::cout << firstNumber << " + " << secondNumber << " is " << firstNumber + secondNumber << '\n';
	else if(op == '-')
		std::cout << firstNumber << " - " << secondNumber << " is " << firstNumber - secondNumber << '\n';
	else if(op == '*')
		std::cout << firstNumber << " * " << secondNumber << " is " << firstNumber * secondNumber << '\n';
	else if(op == '/')
		std::cout << firstNumber << " / " << secondNumber << " is " << firstNumber / secondNumber << '\n';
}

int main()
{
	double firstNumber{ getValue() };
	double secondNumber{ getValue() };
	char op{ getOperator() };

	printResult(firstNumber, secondNumber, op);

	return 0;
}

