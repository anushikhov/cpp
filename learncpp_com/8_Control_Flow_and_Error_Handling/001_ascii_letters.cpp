// Write a program that prints out the letters a through z along with their ASCII codes.

#include <iostream>

int main()
{
	char i{ 'a' };

	while ( i <= 'z' )
	{
		std::cout << i << " - " << static_cast<int>(i) << '\n';
		++i;
	}

	return 0;
}
