// With each iteration of bubble sort, the biggest number remaining gets bubbled to the end of the array.
// After the first iteration, the last array element is sorted. And so on...
// Change your loop to not re-check elements that are already sorted.
//
// If we go through an entire iteration without doing a swap, 
// then we know the array must already be sorted. 
// Implement a check to determine whether any swaps were made this iteration, 
// and if not, terminate the loop early.
// If the loop was terminated early, print on which iteration the sort ended early.


#include <iostream>
#include <iterator>
#include <utility>

int main()
{
	int array[]{ 6, 3, 2, 9, 7, 1, 5, 4, 8 };
	
	constexpr int length{ static_cast<int>(std::size(array)) };

	for(int iteration{ 0 }; iteration < length - 1; ++iteration)
	{
		int track{ 0 };
		for(int currentIndex{ 0 }; currentIndex < length - iteration; ++currentIndex)
		{
			if(array[currentIndex] > array[currentIndex + 1])
			{
				std::swap(array[currentIndex], array[currentIndex + 1]);
				++track;
			}
		}

		
		std::cout << '\n';

		for(int index{ 0 }; index < length; ++index)
		{
			std::cout << array[index] << ' ';
		}

		std::cout << '\n';

		if(track == 1)
		{
			std::cout << "\nEarly termination on iteration: " << ++iteration << '\n';
			break;
		}
	}
	return 0;
}
