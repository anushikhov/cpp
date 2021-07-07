#include <iostream>

int printAndDecrementOne(int x, int pow)
{
	std::cout << '1';
	return (x - pow);
}

int printAndDecrementBit(int x, int pow)
{
	if (x >= pow)
		return printAndDecrementOne(x, pow);
	std::cout << '0';
	return x;
}

int main()
{
	std::cout << "Enter an integer between 0 and 255: ";
	int x{};
	std::cin >> x;

	x = printAndDecrementBit(x, 128);
	x = printAndDecrementBit(x, 64);
	x = printAndDecrementBit(x, 32);
	x = printAndDecrementBit(x, 16);
	
	std::cout << ' ';

	x = printAndDecrementBit(x, 8);
	x = printAndDecrementBit(x, 4);
	x = printAndDecrementBit(x, 2);
	x = printAndDecrementBit(x, 1);

	std::cout << '\n';

	return 0;
}
