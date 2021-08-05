// Write a recursive function that takes an integer as input 
// and returns the sum of each individual digit in the integer (e.g. 357 = 3 + 5 + 7).
// Print the answer for input 93427 (which is 25).  
// Assume the input values are positive.

#include <iostream>

int sum(int input)
{
	if(input / 10 == 0)
		return input;

	return input % 10 + sum(input / 10);
}

int main()
{
	std::cout << sum(93427) << '\n';

	return 0;
}
