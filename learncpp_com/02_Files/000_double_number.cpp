#include <iostream>

int doubleNumber(int input)
{
	return 2 * input;
}

int main()
{
	std::cout << "Enter an integer: ";
	int input{};
	std::cin >> input;

	std::cout << "Double the value is " << doubleNumber(input) << "." << '\n';

	return 0;
}
