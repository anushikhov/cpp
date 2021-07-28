# Introduction to iterators

Iterating over an array (or other structure) of data is quite a common thing to do in programming. We did so with loops and an index (for loops and while loops), with pointers and pointer arithmetic, and with range-based for loops:

` #include <array> `  
` #include <cstddef> `  
` #include <iostream> `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` // The type is automatically deduced to std::array<int, 7> (requires C++17) `  
&emsp;&emsp;&emsp;` // std::array<int, y> if the compiler doesn't support C++17 `  
&emsp;&emsp;&emsp;` std::array data{ 0, 1, 2, 3, 4, 5, 6 }; `  
&emsp;&emsp;&emsp;` std::size_t length{ std::size(data) }; `  

&emsp;&emsp;&emsp;` // while-loop with explicit index `  
&emsp;&emsp;&emsp;` std::size_t index{ 0 }; `  
&emsp;&emsp;&emsp;` while(index != length) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << data[index] << ' '; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` ++index; `  
&emsp;&emsp;&emsp;` } `  
&emsp;&emsp;&emsp;` std::cout << '\n'; `  

&emsp;&emsp;&emsp;` // for-loop with explicit index `  
&emsp;&emsp;&emsp;` for(index = 0; index < length; ++index) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << data[index] << ' '; `  
&emsp;&emsp;&emsp;` } `  
&emsp;&emsp;&emsp;` std::cout << '\n'; `  

&emsp;&emsp;&emsp;` // for-loop with pointer (ptr can't be const, because we increment it) `  
&emsp;&emsp;&emsp;` for(auto ptr{ &data[0] }; ptr != (&data[0] + length); ++ptr) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << *ptr << ' '; `  
&emsp;&emsp;&emsp;` } `  
&emsp;&emsp;&emsp;` std::cout << '\n'; `  

&emsp;&emsp;&emsp;` // ranged-based for loop `  
&emsp;&emsp;&emsp;` for(int i : data) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << i << ' '; `  
&emsp;&emsp;&emsp;` } `  
&emsp;&emsp;&emsp;` std::cout << '\n'; `  

&emsp;&emsp;&emsp;` return 0; `   
` } `  

Looping using indexed is more typing than needed if we only use the index to access elements. It also only works if the container (e.g. the array) provides direct access to elements (which arrays do, but some other types of containers, such as lists, do not).

Looping with pointers and pointer arithmetic is verbose, and can be confusing to readers who do not know the rules of pointer arithmetic. Pointer arithmetic also only works if elements are consecutive in memory (which is true for arrays, but not true for other types of containers, such as lists, trees, and maps).

Pointers (without pointer arithmetic) can also be used to iterate through some non-sequential structures. In a linked lis, each element is connected to the prior element by a pointer. We can iterate through the list by following the chain of pointers.

Range-based for-loops are a little more interesting, as the mechanism for iterating through the container is hidden -- and yet, they still work for all kinds of different structures (arrays, lists, trees, maps, etc...). They use iterators.

## Iterators

An **iterator** is an object designed to traverse through a container (e.g. the values in an array, or the characters in a string), providing access to each element along the way.

A container may provide different kinds of iterators. For example, an array container might offer a forwards iterator to traverse the array in forward order, and a reverse iterator that walks through the array in reverse order.

Once the appropriate type of iterator is created, the programmer can then use the interface provided by the iterator to traverse and access elements without having to worry about what kind of traversal is being done or how the data is being stored in the container. And because C++ iterators typically use the same interface for traversal (operator++ to move to the next element) and access (operator\* to access the current element), we can iterate through a wide variety of different container types using a consistent method.

## Pointers as an iterator

The simplest kind of iterator is a pointer, which (using pointer arithmetic) works for data stored sequentially in memory.

` #include <array> `  
` #include <iostream> `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` std::array data{ 0, 1, 2, 3, 4, 5, 6 }; `  

&emsp;&emsp;&emsp;` auto begin{ &data[0] }; `  
&emsp;&emsp;&emsp;` // this points to one spot beyond the last element `  
&emsp;&emsp;&emsp;` auto end{ begin + std::size(data) }; `  

&emsp;&emsp;&emsp;` for(auto ptr{ begin }; ptr != end; ++ptr) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << *ptr << ' '; `  
&emsp;&emsp;&emsp;` } `  
&emsp;&emsp;&emsp;` std::cout << '\n'; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

We defined two variables, `begin` (which points to the beginning of the container), and `end` (which marks an end point). For arrays, the end marker is typically the place in memory where the last element would be if the container contained one more element. 

The pointer then iterates between `begin` and `end`, and the current element can be accessed by indirection.

You might be tempted to calculate the end marker using the address-of operator and array syntax like so:  

` int* end{ &array[std::size(array)] }; `  

But this causes undefined behavior, because `array[std::size(array)]` accesses an element that is off the end of the array. 

Instead, use:  

` int* end{ array.data() + std::size(array) }; // data() returns a pointer to the first element `  

## Standard library iterators

Iterating is such a common operation that all standard library containers offer direct support for iteration. Instead of calculating our own being and end points, we can simply ask the container for the being and end poits via functions conveniently named `begin()` and `end()`:

` #include <array> `  
` #include <iostream> `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` std::array array{ 1 2, 3 }; `  

&emsp;&emsp;&emsp;` auto begin{ array.begin() }; `  
&emsp;&emsp;&emsp;` auto end{ array.end() }; `  

&emsp;&emsp;&emsp;` for( auto p{ begin }; p != end; ++p) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << *p << ' '; `  
&emsp;&emsp;&emsp;` } `  
&emsp;&emsp;&emsp;` std::cout << '\n'; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

The `iterator` header also contains two generic functions (`std::begin` and `std::end`) that can be used: 

` #include <array> `  
` #include <iostream> `  
` #include <iterator> `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` std::array array{ 1, 2, 3 }; `  

&emsp;&emsp;&emsp;` auto begin{ std::begin(array) }; `  
&emsp;&emsp;&emsp;` auto end{ std::end(array) }; `  

&emsp;&emsp;&emsp;` for(auto p{ begin }; p != end; ++p) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << *p << ' '; `  
&emsp;&emsp;&emsp;` } `  
&emsp;&emsp;&emsp;` std::cout << '\n'; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

Iterators take care of the details of iterating through the container. All we need are four things: the begin point, the end point, operator++ to move the iterator to the next element (or the end), and operator\* to get the value of the current element.

## Back to range-based for loops

All types that have `being` and `end` member functions or can be used with `std::begin` and `std::end` are usable in range-based for loops.

` #include <array> `  
` #include <iostream> `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` std::array array{ 1, 2, 3}; `  

&emsp;&emsp;&emsp;` // This does exactly the same as the loop we used before. `  
&emsp;&emsp;&emsp;` for(int i : array) `   
&emsp;&emsp;&emsp;` { `   
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << i << ' '; `  
&emsp;&emsp;&emsp;` } `  
&emsp;&emsp;&emsp;` std::cout << '\n'; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

Behind the scenes, the range-based for-loop calls `begin()` and `end()` of the type to iterate over. `std::array` has `begin` and `end` member functions, se we can use it in a range-based loop. C-style fixed arrays can be used with `std::begin` and `std::end` functions, so we can loop through them with a range-based loop as well. Dynamic arrays don't work though, because there is no `std::end` function for them (because the type information doesn't contain the array's length).

You can also add functions to your types, so that they can be use with range-based for loops too.

Besides range-based for loops, iterators are also used in `std::sort` and other algorithms. They are used quite a bit in the standard library.

## Iterator invalidation (danglingn iterators)  

Muck like pointers and references, iterators can be left "dangling" if the elements being iterated over change address or are destroyed. When this happens, we say the iterator has been **invalidated**. Accessing an invalidated iterator produces undefined behavior.


Some operations that modify containers (such as adding an element to a `std::vector`) can have the side effect of causing the elements in the container to change addresses. When this happens, existing iterators to those elements will be invalidated.

` #include <iostream> `  
` #include <vector> `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` std::vector v{ 1, 2, 3, 4, 5, 6, 7 }; `  

&emsp;&emsp;&emsp;` auto it{ v.begin() }; `  

&emsp;&emsp;&emsp;` ++it; // move to second element `   
&emsp;&emsp;&emsp;` std::cout << *it << '\n'; // prints 2 `  

&emsp;&emsp;&emsp;` v.erase(it); // erase the element currently being iterated over `  

&emsp;&emsp;&emsp;` // erase() invalidates iterators to the erased element (and subsequent elements) `  
&emsp;&emsp;&emsp;` // so iterator "it" is now invalidated `  

&emsp;&emsp;&emsp;` ++it; // undefined behavior `  
&emsp;&emsp;&emsp;` std::cout << *it << '\n'; // undefined behavior `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  
