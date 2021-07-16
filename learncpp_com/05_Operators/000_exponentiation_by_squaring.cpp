#include <iostream>
#include <cstdint>     // for std::int_fast64_t

std::int_fast64_t powint(int base, int exp)
{
	std::int_fast64_t result{ 1 };
	while (exp)
	{
		if (exp & 1)
			result *= base;
		exp >>= 1;
		base *= base;
	}

	return result;
}

int main()
{
	std::cout << "Enter the base: ";
	int base{};
	std::cin >> base;

	std::cout << "Enter a non-negative exponent: ";
	int exp{};
	std::cin >> exp;

	std::cout << powint(base, exp);

	return 0;
}
