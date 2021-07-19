# Sorting an array using selection sort

Sorting is generally performed by repeatedly comparing pairs of array elements, and swapping them if they meet some predefined criteria. The order in which these elements are compared differs depending on which sorting algorithm is used. The criteria depends on how the list will be sorted (e.g. in ascending or descending order).

To swap two elements, we can use the `std::swap()` function from the C++ standard library, which is defined in the utility header.

` #include <iostream> `  
` #include <utility> `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` int x{ 2 }; `  
&emsp;&emsp;&emsp;` int y{ 4 }; `  
&emsp;&emsp;&emsp;` std::cout << "Before swap: x = " << x << ", y = " << y << '\n'; `  
&emsp;&emsp;&emsp;` std::swap(x, y); `  
&emsp;&emsp;&emsp;` std::cout << "After swap: x = " << x << ", y = " << y << '\n'; `  
` } `  


## Selection sort

There are many ways to sort an array. Selection sort is one of the slower sorts.

Selection sort performs the following steps to sort an array from smallest to largest:
1. Starting at array index 0, search the entire array to find the smallest value  
1. Swap the smallest value found in the array with the value at index 0  
1. Repeat steps 1 & 2 starting from the next index  

In other words, we're going to find the smallest element in the array, and swap it into the first position. Then we're going to find the next smallest element, and swap it into the second position. This process will be repeated until we run out of elements. The last comparison will always be with itself (which is redundant), so we can actually stop 1 element before the end of the array.


## Selection sort in C++

` #include <iostream> `  
` #include <iterator> `  
` #include <utility> `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` int array[]{ 30, 50, 20, 10, 40 }; `  
&emsp;&emsp;&emsp;` constexpr int length{ static_cast<int>(std::size(array)) }; `  

&emsp;&emsp;&emsp;` for(int startIndex{ 0 }; startIndex < length - 1; ++startIndex) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` int smallestIndex{ startIndex }; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` for(int currentIndex{ startIndex + 1 }; currentIndex < length; ++currentIndex) `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` if(array[currentIndex] < array[smallestIndex]) `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` smallestIndex = currentIndex; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` } `

&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::swap(array[startIndex], array[smallestIndex]); `  
&emsp;&emsp;&emsp;` } `  

&emsp;&emsp;&emsp;` for(int index{ 0 }; index < length; ++index) `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << array[index] << ' '; `  

&emsp;&emsp;&emsp;` std::cout << '\n'; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

Sorting names works using the same algorithms. Just change the array type from `int` to `std::string`, and initialize with the appropriate values.


## std::sort

Because sortin arrays is so common, the C++ standard library includes a sorting function named `std::sort`. `std::sort` lives in the `<algorithm>` header, and can be invoked on an array like so:  

` #include <algorithm> `  
` #include <iostream> `  
` #include <iterator> `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` int array[]{ 30, 50, 20, 10, 40 }; `  

&emsp;&emsp;&emsp;` std::sort(std::begin(array), std::end(array)); `  

&emsp;&emsp;&emsp;` for(int i{ 0 }; i < static_cast<int>(std::size(array)); ++i) `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << array[i] << ' '; `  

&emsp;&emsp;&emsp;` std::cout << '\n'; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

By default, `std::sort` sorts in ascending order using operator< to compare pairs of elements and swapping them if necessary.
