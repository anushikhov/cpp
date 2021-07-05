// Write a program that asks the user to input an integer, and tells the user whether the number is even or odd.
// Write a function called isEven() that returns true if an integer passed to it is even, and false otherwise.
// Use the modulus operator to test whether the integer parameter is even.

#include <iostream>


// Get user input
int getInput()
{
	std::cout << "Enter an integer: ";
	int input{};
	std::cin >> input;

	return input;
}

// Check whether the number is even
bool isEven(int input)
{
	if(input % 2 == 0)
		return true;
	
	return false;
}

// Print the number's parity
void printParity(int input)
{
	if(isEven(input))
		std::cout << "The number is even.\n";
	else
		std::cout << "The number is odd.\n";
}

int main()
{
	printParity(getInput());

	return 0;
}
