// A prime number is a whole number greater than 1 that can only be divided evenly by 1 and itself.
// Write a program that asks the user to enter a single digit integer.
// If the user enters a single digit that is prime (2, 3, 5, or 7), print "The digit is prime."
// Otherwise, print "The digit is not prime."


#include <iostream>

bool isPrime(int input)
{
	if (input == 2 || input == 3 || input == 5 || input == 7)
		return true;
	return false;
}

int main()
{
    std::cout << "Enter a digit: ";
    int input{};
    std::cin >> input;

    if ( isPrime(input) )
	    std::cout << "The digit is prime.\n";
    else
	    std::cout << "The digit is not prime.\n";

    return 0;
}
