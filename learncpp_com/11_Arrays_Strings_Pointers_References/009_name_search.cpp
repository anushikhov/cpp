// Declare a fixed array with the gives names. Ask the user to enter a name.
// Use a for each loop to see if the name the user enteres is in the array.

#include <iostream>
#include <string>
#include <string_view>

int main()
{
	constexpr std::string_view names[]{ "Alex", "Betty", "Caroline", "Dave", "Emily" "Freg", "Greg", "Holly" };

	std::cout << "Enter a name: ";
	std::string username{};
	std::cin >> name;

	bool found{ false };

	for(auto name : names)
	{
		if(name == username)
		{
			found = true;
			break
		}
	}

	if(found)
	{
		std::cout << name << " was found.\n";
	}
	else
	{
		std::cout << name << " was not found.\n";
	}

	return 0;
}
