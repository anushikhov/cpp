#include <iostream>

int sqrtFloor(int input)
{
	if(input == 0 || input == 1)
	{
		return input;
	}

	int i{ 1 };
	int result{ 1 };
	while(result < input)
	{
		++i;
		result = i * i;
	}

	if(i * i != input)
	{
		return i - 1;
	}

	return i;
}

int getInt()
{
	std::cout << "Enter a positive integer: ";
	int input{};
	std::cin >> input;

	return input;
}

int main()
{
	while(true)
	{
		int input{ getInt() };

		if(input >= 0)
		{
			std::cout << "Square root: " << sqrtFloor(input) << '\n';

			return 0;
		}
	}
}
