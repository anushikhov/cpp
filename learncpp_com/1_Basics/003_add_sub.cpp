#include <iostream>

int main()
{
	std::cout << "Enter an integer: ";
	int firstInt{};
	std::cin >> firstInt;

	std::cout << "Enter another integer: ";
	int secondInt{};
	std::cin >> secondInt;

	std::cout << firstInt << " + " << secondInt << " is " << firstInt + secondInt << "." << '\n';
	std::cout << firstInt << " - " << secondInt << " is " << firstInt - secondInt << "." << '\n';

	return 0;
}
