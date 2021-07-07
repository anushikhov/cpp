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

int returnBit(int input, int power)
{
	return ((input) >= power) ? 1 : 0;
}

int main()
{
	int input = getInput();
	std::cout << returnBit(input, 128);
	
	if(input >= 128)
		input -= 128;
	std::cout << returnBit(input, 64);
	
	if(input >= 64)
		input -= 64;
	std::cout << returnBit(input, 32);

	if(input >= 32)
		input -= 32;
	std::cout << returnBit(input, 16);

	if(input >= 16)
		input -= 16;
	std::cout << returnBit(input, 8);

	if(input >= 8)
		input -= 8;
	std::cout << returnBit(input, 4);
	
	if(input >= 4)
		input -= 4;
	std::cout << returnBit(input, 2);

	if(input >= 2)
		input -= 2;
	std::cout << returnBit(input, 1);

	return 0;
}
