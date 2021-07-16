// Print the following:
// 1
// 1 2
// 1 2 3
// 1 2 3 4
// 1 2 3 4 5


#include <iostream>

int main()
{
	int outer{ 1 };
	while(outer <= 5)
	{
		int inner{ 1 };
		while(inner <= outer)
		{
			std::cout << inner << ' ';
			++inner;
		}

		std::cout << '\n';
		++outer;
	}
	
	return 0;
}
