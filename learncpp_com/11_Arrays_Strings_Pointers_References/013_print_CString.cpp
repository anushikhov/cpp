// Write a function to print a C-style string character by character.
// Use a pointer to step through each character of the string and print that character.
// Stop when you hit the null terminator.
// Write a main function that tests the function with the string literal "Hello, World!".

#include <iostream>

void printCString(const char* str)
{
	while(*str != '\0')
	{
		std::cout << *str;

		++str;
	}
}		

int main()
{
	printCString("Hello world!");

	std::cout << '\n';

	return 0;
}
