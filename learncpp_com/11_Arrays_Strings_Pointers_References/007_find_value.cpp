// Write a function named find that takes a pointer to the beginning and a pointer to the end 
// (1 element past the last) of an array, as well as a value.
// The function should search for the given value and return a pointer to the first element with that value, 
// or the end pointer if no element was found. 

#include <iostream>
#include <iterator>


int* find(int* begin, int* end, int value)
{
	for(int* p{ begin }; p != end; p++)
	{
		if(*p == value)
			return p;
	}

	return end;
}

int main()
{
	int arr[]{ 2, 5, 4, 10, 8, 20, 16, 40 };

	int* found{ find(std::begin(arr), std::end(arr), 20) };

	if(found != std::end(arr))
	{
		std::cout << *found << '\n';
	}

	return 0;
}
