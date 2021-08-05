// Write a recursive function called factorial that returns the factorial of the input.
// Test it with the first 7 factorials.

#include <iostream>

int factorial(int n)
{
	if(n > 1)
	{
		return n * factorial(n - 1);
	}

	return n;
}

int main()
{
        for(int i{ 0 }; i < 7; ++i)
	{
		std::cout << factorial(i) << '\n'; 
	}	

	return 0;
}
