#include <iostream>

int main()
{
	std::cout << "Enter an integer: ";
	int input{};

	std::cin >> input;

	std::cout << "Double the number is: " << input * 2 << '\n';

	return 0;
}
