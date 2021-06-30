#include "io.h"      // also needed for detecting return type errors in function declarations/definitions
#include <iostream>

int readNumber()
{
	std::cout << "Enter an integer: ";
	int input{};
	std::cin >> input;

	return input;
}

void writeAnswer(int x)
{
	std::cout << "Result of the addition: " << x << '\n';
}
