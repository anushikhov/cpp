// Write a program that asks the user to enter a positive integer, and then uses a recursive function 
// to print out the binary representation for that number.

#include <iostream>

void printBinary(int x)
{
	if(x == 0)
		return;

	printBinary(x / 2);

	std::cout << x % 2;
}

int main()
{
	int x;
	std::cout << "Enter a positive integer: ";
	std::cin >> x;

	printBinary(x);
}
