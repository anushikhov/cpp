// Write your own function to swap the value of two integer variables. Write a main() function to test it.

#include <iostream>

void swap(int& a, int& b)
{
	a = a + b;
	b = a - b;
	a = a - b;
}

int main()
{
	int a{ 6 };
	int b{ 8 };
	swap(a, b);

	if(a == 8 && b == 6)
		std::cout << "It works!\n";
	else
		std::cout << "It's broken!\n";

	return 0;
}
