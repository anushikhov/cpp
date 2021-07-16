// Write a for loop that prints every even number from 0 to 20.

#include <iostream>

int main()
{
	for(int count{ 0 }; count <= 20; count += 2)
	{
		std::cout << count << ' ';
	}
	
	return 0;
}
