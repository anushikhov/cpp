#include <iostream>


// Get user input
int getInt()
{
	std::cout << "Enter a positive integer: ";
	int input{};
	std::cin >> input;

	return input;
}

// Calculate the square root of the number
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

	if(input != i * i)
	{
		return i - 1;
	}

	return i;
}

// Check whether the number is prime
bool isPrime(int input)
{
	if(input == 1 || input ==  0)
	{
		return false;
	}

	int i{ 2 };
	while(i <= sqrtFloor(input))
	{
		if(input % i == 0)
			return false;

		++i;
	}

	return true;
}

// Print whether the number is prime
void printAnswer(int input)
{
	if(isPrime(input))
	{
		std::cout << "The number is prime.\n";
	}
	else
	{
		std::cout << "The number is not prime.\n";
	}
}

int main()
{
	std::cout << "JFF\n\n"
		  << "Sift the Two's and Sift the Three's,\n"
		  << "The Sieve of Eratosthenes.\n"
		  << "When the multiples sublime,\n"
		  << "The numbers that remain are Prime.\n\n\n";
	
	while(true)
	{
		int input { getInt() };

		if(input >= 0)
		{
			printAnswer(input);
			return 0;
		}
	}
}
