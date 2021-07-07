// Write a program that asks the user to input a number between 0 and 255.
// Print this number as an 8-bit binary number (of the form #### ####).
// Don't use any bitwise operators or std::bitset.


#include <iostream>

int getInput()
{
	std::cout << "Enter an integer between 0 and 255: ";
	int input{};
	std::cin >> input;

	return input;
}

int returnBit(int input, int pow)
{
	return (input >= pow) ? 1 : 0;
}

int evaluateInput(int input, int pow)
{
	return (input >= pow) ? input - pow : input;
}

int decreasePow(int pow)
{
	return pow / 2;
}

void printBits(int input, int pow)
{
	std::cout << returnBit(input, pow);
}

int main()
{
	int input{ getInput() };
	int pow{ 128 };

	printBits(input, pow);

	input = evaluateInput(input, pow);
	pow = decreasePow(pow);
	printBits(input, pow);

	input = evaluateInput(input, pow);
	pow = decreasePow(pow);
	printBits(input, pow);

	input = evaluateInput(input, pow);
	pow = decreasePow(pow);
	printBits(input, pow);
	
	std::cout << ' ';

	input = evaluateInput(input, pow);
	pow = decreasePow(pow);
	printBits(input, pow);

	input = evaluateInput(input, pow);
	pow = decreasePow(pow);
	printBits(input, pow);

	input = evaluateInput(input, pow);
	pow = decreasePow(pow);
	printBits(input, pow);

	input = evaluateInput(input, pow);
	pow = decreasePow(pow);
	printBits(input, pow);

	return 0;
}
