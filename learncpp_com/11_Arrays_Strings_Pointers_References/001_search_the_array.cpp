// Repeatedly ask the user for a number between 1 and 9. Once they have entered, print the array.
// Then search the array for the value that the user entered and print the index of that element.


#include <iostream>
#include <iterator>
#include <limits>

int getValue()
{
	while(true)
	{
		std::cout << "Enter an integer value between 1 and 9: ";
		int input{};
		std::cin >> input;
		
		if(input >= 1 && input <= 9 )
		{
			return input;
		}
		else if(std::cin.fail())
		{ 
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}
}

int returnIndex(int input, const int array[], int size)
{
	for(int i{ 0 }; i < size; ++i)
	{
		if(array[i] == input)
			return i;
	}

	return -1;
}

void printIndex(int input, const int array[], int size)
{
	for(int i{ 0 }; i < size; ++i)
	{
		std::cout << array[i] << ' ';
	}
	
	std::cout << '\n';
	std::cout << input << " has the index " << returnIndex(input, array, size) << '\n';
}

int main()
{
	int input{ getValue() };

	constexpr int array[]{ 4, 6, 7, 3, 8, 2, 1, 9, 5 };
	int size = static_cast<int>(std::size(array));

	printIndex(input, array, size);

	return 0;
}
