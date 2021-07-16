// Write a program that asks the user to enter two integers, one named smaller, the other named larger.
// If the user enters a smaller value for the second integer, use a block and a temporary variable to swap the values.
// Then print the values of the smaller and larger variables.

#include <iostream>

int main()
{
	std::cout << "Enter an integer: ";
	int smaller{};
	std::cin >> smaller;

	std::cout << "Enter a larger integer: ";
	int larger{};
	std::cin >> larger;

	if (smaller > larger)
	{
		std::cout << "Swapping the values\n";
		
		int temp{ smaller };
		smaller = larger;
		larger = temp;
	}

	std::cout << "The smaller value is " << smaller << '\n';
	std::cout << "The larger value is "  << larger  << '\n';

	return 0;
}
