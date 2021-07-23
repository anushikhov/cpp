// Write a program that asks the user how many names they wish to enter,
// dynamically allocate a std::string array, ask the user to enter each name,
// call std::sort to sort the names, print the sorted list of names.

#include <algorithm>
#include <iostream>
#include <limits>
#include <string>

int getLength()
{
	std::cout << "How many names would you like to enter: ";
	int length{};
	std::cin >> length;

	return length;
}

void getNames(std::string* names, int length)
{
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	for(int i{ 0 }; i < length; ++i)
	{
		std::cout << "Enter name # " << i + 1 << ": ";
		std::getline(std::cin, names[i]);
	}
}

void printNames(std::string* names, int length)
{
	std::cout << "\nHere is your sorted list:\n";

	for(int i { 0 }; i < length; ++i)
	{
		std::cout << "Name #" << i + 1 << ": " << names[i] << '\n';
	}
}

int main()
{
	int length{ getLength() };

	auto* names{ new std::string[length]{} };

	getNames(names, length);

	std::sort(names, names + length);

	printNames(names, length);

	delete[] names;

	return 0;
}
