// Write a program that asks the user to enter their full name and their age.
// As output, tell the user how many years they've lived for each letter in their name (count the space as a letter).

#include <iostream>
#include <string>

int main()
{
	std::cout << "Enter your full name: ";
	std::string fullName{};
	std::getline(std::cin >> std::ws, fullName);

	std::cout << "Enter your age: ";
	int age{};
	std::cin >> age;

	std::cout << "You've lived " 
		  << age / static_cast<double>(fullName.length()) 
		  << " years for each letter in your name. \n";

	return 0;
}
