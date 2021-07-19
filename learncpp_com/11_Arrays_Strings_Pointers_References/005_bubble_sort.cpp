// Bubble sort works by comparing adjacent pairs of elements, and swapping them if the criteria is met,
// so the elements "bubble" to the end of the array.
// Unoptimized bubble sort performs the following steps to sort an array from smallest to largest:
// Compare array element 0 with array element 1. If element 0 is larger, swap it with element 1.
// Now do the same for elements 1 and 2, and every subsequent pair of elements until you hit the end of the array.
// At this point, the last element of the array will be sorted.
// Repeat the first two steps again until the array is sorted.
// Write code that bubble sorts the given array according to the rules above.
// Print the sorted array elements at the end of your program.
// If we're able to sort one element per iteration, that means we'll need to iterate roughly as many times
// as there are numbers in our array to guarantee that the whole array is sorted.


#include <iostream>
#include <iterator>
#include <utility>

int main()
{
	int array[]{ 6, 3, 2, 9, 7, 1, 5, 4, 8 };
	
	constexpr int length{ static_cast<int>(std::size(array)) };

	for(int startIndex{ 0 }; startIndex < length - 1; ++startIndex)
	{
		for(int currentIndex{ 0 }; currentIndex < length - 1; ++currentIndex)
		{
			if(array[currentIndex] > array[currentIndex + 1])
				std::swap(array[currentIndex], array[currentIndex + 1]);
		}
	}

	for(int index{ 0 }; index < length; ++index)
	{
		std::cout << array[index] << ' ';
	}

	std::cout << '\n';

	return 0;
}

