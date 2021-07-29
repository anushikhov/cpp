# Introduction to standard library algorithms

Because searching, counting, and sorting are such common operations to do, the C++ standard library comes with a bunch of functions to do these things in just a few lines of code. Additionally, these standard library functions come pre-tested, are efficient, work on a variety of different container types, and many support parallelization (the ability to devote multiple CPU threads to the same task in order to complete it faster).

The functionality provided in the algorithms library generally fall into one of three categories:

* **Inspectors** -- Used to view (but not modify) data in a container. Examples include searching and counting.  
* **Mutators** -- Used to modify data in a container. Examples include sorting and shuffling.  
* **Facilitators** -- Used to generate result based on values of the data members. Examples include objects that multiply values, or objects that determine what order pairs of elements should be sorted in.  

These algorithms live in the ![algorithms library](https://en.cppreference.com/w/cpp/algorithm) library. 

## Using std::find to find an element by value

`std::find` searches for the first occurrence of a value in a container. It takes 3 parameters: an iterator to the starting element in the sequence, an iterator to the ending element in the sequence, and a value to search for. It returns an iterator pointing to the element (if it is found) or the end of the container (if the element is not found).  

` #include <algorithm> `  
` #include <array> `  
` #include <iostream> `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` std::array arr{ 13, 90, 99, 5, 40, 80 }; `  

&emsp;&emsp;&emsp;` std::cout << "Enter a value to search for and replace with: "; `  
&emsp;&emsp;&emsp;` int search{}; `  
&emsp;&emsp;&emsp;` int replace{}; `  
&emsp;&emsp;&emsp;` std::cin >> search >> replace; `  

&emsp;&emsp;&emsp;` // Input validation omitted `  

&emsp;&emsp;&emsp;` // std::find returns an iterator pointing to the found element (or the end of the container) `   
&emsp;&emsp;&emsp;` // we'll store it in a variable, using type inference to deduce the type of the iterator `  
&emsp;&emsp;&emsp;` auto found{ std::found(arr.begin(), arr.end(), search) }; `  

&emsp;&emsp;&emsp;` // Algorithms that don't find what they were looking for return the end iterator. `  
&emsp;&emsp;&emsp;` // We can access it by using the end() member function. `  
&emsp;&emsp;&emsp;` if(found == arr.end()) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << "Could not find " << search << '\n'; `  
&emsp;&emsp;&emsp;` } `  
&emsp;&emsp;&emsp;` else `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` // Override the found element. `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` *found = replace; `  
&emsp;&emsp;&emsp;` } `  

&emsp;&emsp;&emsp;` for(int i : arr) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << i << ' '; `  
&emsp;&emsp;&emsp;` } `  

&emsp;&emsp;&emsp;` std::cout << '\n'; `  

&emsp;&emsp;&emsp;` return 0; `
` } `  

## Using std::find_if to find an element that matches some condition

Sometimes we want to see if there is a value in a container that matches some condition (e.g. a string that contains a specific substring) rather than an exact value. In such cases, `std::find_if` is perfect. The `std::find_if` function works similarly to `std::find`, but instead of passing in a value to search for, we pass in a callable object, such as a function pointer (or a lambda) that checks to see if a match is found. `std::find_if` will call this function for every element until a matching element is found (or no more elements remain in the container to check).

` #include <algorithm> `  
` #include <array> `  
` #include <iostream> `  
` #include <string_view> `  

` bool containsNut(std::string_view str) `  
` { `  
&emsp;&emsp;&emsp;` // std::string_view::find returns std::string_view::npos if it doesn't find the substring. `  
&emsp;&emsp;&emsp;` // Otherwise it returns the index where the substring occurs in str. `  
&emsp;&emsp;&emsp;` return (str.find("nut") != std::string_view::npos); `  
` } `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` std::array<std::string_view, 4> arr{ "apple", "banana", "walnut", "lemon" }; `  

&emsp;&emsp;&emsp;` // Scan the array to see if any elements contain the "nut" substring `   
&emsp;&emsp;&emsp;` auto found{ std::find_if(arr.begin(), arr.end(), containsNut) }; `  

&emsp;&emsp;&emsp;` if(found == arr.end()) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << "No nuts\n"; `  
&emsp;&emsp;&emsp;` } `  
&emsp;&emsp;&emsp;` else `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << "Found " << *found << '\n'; `  
&emsp;&emsp;&emsp;` } `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

## Using std::count and std::count_if to count how many occurrences there are

`std::cout` and `std::cout_if` search for all occurrences of an element or an element fullfilling a condition.  

` #include <algorithms> `  
` #include <array> `  
` #include <iostream> `  
` #inclue <string_view> `  

` bool containsNut(std::string_view str) `  
` { `  
&emsp;&emsp;&emsp;` return (str.find("nut") != std::string_view::npos); `  
` } `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` std::array<std::string_view, 5> arr{ "apple", "banana", "walnut", "lemon", "peanut" }; `  

&emsp;&emsp;&emsp;` auto nuts{ std::count_if(arr.gegin(), arr.end(), containsNut) }; `  

&emsp;&emsp;&emsp;` std::cout << "Counted " << nuts << " nuts(s)\n"; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

## Using std::sort to custom sort 

By default, `std::sort` sorts the elements in ascending order. There's a version of `std::sort` that takes a function as its third parameter that allows us to sort however we like. The function takes two parameters to compare, and returns true if the first argument should be ordered before the second.

` #include <algorithm> `  
` #include <array> `  
` #include <iostream> `  

` bool greater(int a, int b) `  
` { `  
&emsp;&emsp;&emsp;` return (a > b); `  
` } `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` std::array arr{ 13, 90, 99, 5, 40, 80 }; `  

&emsp;&emsp;&emsp;` // Pass greater to std::sort `  
&emsp;&emsp;&emsp;` std::sort(arr.begin(), arr.end(), greater); `  

&emsp;&emsp;&emsp;` for(int i : arr) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << i << ' '; `  
&emsp;&emsp;&emsp;` } `  

&emsp;&emsp;&emsp;` std::cout << '\n'; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

The `greater` function needs 2 arguments, but we're not passing it any. When we use a function without parentheses(), it's only a function pointer, not a call. `std::sort` uses this pointer and calls the actual `greater` function with any 2 elements of the array. We don't know which elements `greater` will be called with, because it's ot defined which sorting algorithm `std::sort` is using under the hood. 

Because sorting in descening order is so common, C++ provides a custom type (named `std::greater`) for that too (which is part of the functional header). In the above example we can replace:

` std::sort(arr.begin(), arr.end(), greater); // call the custom greater function `  

with:  

` std::sort(arr.begin(), arr.end(), std::greater{}); // use the standard library greater comparison `  
` // Before C++17, we had to specify the element type when we create std::greater `  
` std::sort(arr.begin(), arr.end(), std::greater<int>{}); // use the standard library greater comparison `  

`std::greater{}` needs the curly braces because it is not a callable function. It's a type, and in order to use it, we need to instantiate an object of that type. The curly braces instantiate an anonymous object of that type (which then gets passed as an argument to `std::sort`).

To further understand how `std::sort` uses the comparison function, we'll have to take a step back to a modified version of the selection sort example:

` #include <iostream> `  
` #include <iterator> `  
` #include utility> `  

` void sort(int\* begin, int\* end) `  
` { `  
&emsp;&emsp;&emsp;` for(auto startElement{ begin }; startElement != end; ++startElement) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` auto smallestElement{ startElement }; `  

&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` // std::next returns a pointer to the next element `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` for(auto currentElement{ std::next(startElement) }; currentElement != end; ++currentElement) `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` if(*currentElement < *smallestElement) `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` smallestElement = currentElement; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` } `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` } `  

&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::swap(*startElement, *smallestElement); `  

&emsp;&emsp;&emsp;` } `  
` } `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` int array[]{ 2, 1, 9, 4, 5 }; `  

&emsp;&emsp;&emsp;` sort(std::begin(array), std::end(array)); `  

&emsp;&emsp;&emsp;` for(auto i : array) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << i << ' '; `  
&emsp;&emsp;&emsp;` } `  

&emsp;&emsp;&emsp;` std::cout << '\n'; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

To add a comparison function, we have to use a new type, `std::function`, to store a function that takes 2 int parameters and returns a bool.

` void sort(int *begin, int *end, std::function<bool(int, int)> compare) `  

We can now pass a comparison function like `greater` to `sort` and for `sort` to use it, all we need to do is replace the line: 

` if(*currentElement < *smallestElement) `  

with 

` if(compare(*currentElement, *smallestElement)) `  

Now the caller of `sort` can choose how to compare two elements. 

` #include <functional> `  
` #include <iostream> `  
` #include <iterator> `  
` #include <utility> `  

` // sort accpets a comparison function `  
` void sort(int* begin, int* end, std::function<bool(int, int)> compare) `  
` { `  
&emsp;&emsp;&emsp;` for(auto startElement{ begin }; startElement != end; ++startElement) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` auto smallestElement{ startElement }; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` for(auto currentElement{ std::next(startElement) }; currentElement != end; ++currentElement) `   
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` { `   
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` // The comparison function is used to check if the current element should be ordered `   
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` // before the currently "smallest" element. `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` if(compare(*currentElement, *smallestElement)) `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` smallestElement = currentElement; `   
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` } `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` } `  

&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::swap(*startElement, *smallestElement); `  
&emsp;&emsp;&emsp; ` } `  
` } `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` int array[]{ 2, 1, 9, 4, 5 }; `  

&emsp;&emsp;&emsp;` // Use std::greater to sort in descending order `  
&emsp;&emsp;&emsp;` // (We have to use the global namespace selector to prevent a collision `  
&emsp;&emsp;&emsp;` // between our sort function and std::sort.) `  
&emsp;&emsp;&emsp;` ::sort(std::begin(array), std::end(array), std::greater{}); `  

&emsp;&emsp;&emsp;` for(auto i : array) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << i << ' '; `  
&emsp;&emsp;&emsp;` } `  

&emsp;&emsp;&emsp;` std::cout << '\n'; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

## Using std::for_each to do something to all elements of a container

`std::for_each` takes a list as input and applies a custom function to every element. This is useful when we want to perform the same operation to every element in a list.

` #include <algorithm> `  
` #include <array> `  
` #include <iostream> `  

` void doubleNumber(int& i) `  
` { `  
&emsp;&emsp;&emsp;` i *= 2; `  
` } `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` std::array arr{ 1, 2, 3, 4 }; `  

&emsp;&emsp;&emsp;` std::for_each(arr.begin(), arr.end(), doubleNumber); `  

&emsp;&emsp;&emsp;` for(int i : array) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << i << ' '; `  
&emsp;&emsp;&emsp;` } `  

&emsp;&emsp;&emsp;` std::cout << '\n'; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

This often seems like the most unnecessary algorithm, because equivalent code with a range-based for loop is shorter and easier. But there are benefits to `std::for_each`.

` std::ranges::for_each(arr, doubleNumber); // Since C++20, we don't have to use begin() and end(). `  
` // std::for_each(arr.begin(), arr.end(), doubleNumber); // Before C++20 `  

` for (auto& i : arr) `  
` { `  
&emsp;&emsp;&emsp;` doubleNumber(i); `  
` } `  

With `std::for_each`, our intentions are clear. Call `doubleNumber` with each element of `arr`. In the range-based for-loop, we have to add a new variable, `i`. This leads to several mistakes that a programmer could do when they're tired or not paying attention. For one, there could be an implicit conversion if we don't use `auto`. We could forget the ampersand, and `doubleNumber` wouldn't affect the array. We could accidently pass a variable other than `i` to `doubleNumber`. These mistakes cannot happen with `std::for_each`.

Additionally, `std::for_each` can skip elements at the beginning or end of a container, for example to skip the first element of `arr`, `std::next` can be used to advance begin to the next element.

` std::for_each(std::next(arr.begin()), arr.end(), doubleNumber); `  
` // Now the arr is [1, 4, 6, 8]. The first element wasn't doubled. `  

This is not possible with a range-based for loop.

Like many algorithms, `std::for_each` can be parallelized to achieve faster processing, making it better suited for large projects and big data than a range-based for loop.

## Order of execution

Note that most of the algorithms in the algorithms library do not guarantee a particular order of execution. For such algorithms, take care to ensure any functions you pass in do not assume a particular ordering, as the order of invocation may not be the same on every compiler.

The following algorithms do guarantee sequential execution: `std::for_each`, `std::copy`, `std::copy_backward`, `std::move`, and `std::move_backward`.

**Best practice**<br/> 
_Unless otherwise specified, do not assume that standard library algorithms will execute in a particular sequence. std::for_each, std::copy, std::copy_backward, std::move, and std::move_backward have sequential guarantees._

## Ranges in C++20

C++20 adds ranges, which allow us to simply pass `arr`, instead of explicitly passing `arr.begin()` and `arr.end()`. This will make the code even shorter and more readable.

...  

The algorithms library has a ton of useful functionality that can make the code simple and more robust. Because most of these functions work very similarly, once you know how a few work, you can make use of most of them.

**Best practice**<br/>
_Favor using functions from the algorithms library over writing your own functionality to do the same thing._
