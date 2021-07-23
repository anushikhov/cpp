# Dynamically allocating arrays

In addition to dynamically allocating single values, we can also dynamically allocate arrays of variables. Unlike a fixed array, where the array size must be fixed at compile time, dynamically allocating an array allows us to choose an array length at runtime.

To allocate an array dynamically, we use the array form of new and delete (often called new[] and delete[]):

` #include <iostream> `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` std::cout << "Enter a positive integer: "; `  
&emsp;&emsp;&emsp;` int length{}; `  
&emsp;&emsp;&emsp;` std::cin >> length; `  

&emsp;&emsp;&emsp;` int* array{ new int[length]{} }; `  

&emsp;&emsp;&emsp;` std::cout << "I just allocated an array of integers of length " << length << '\n'; `  

&emsp;&emsp;&emsp;` array[0] = 5; `  

&emsp;&emsp;&emsp;` delete[] array; // use array delete to deallocate array `  

&emsp;&emsp;&emsp;` we don't need to set array to nullptr/0 here because it's going to go out of scope immediately after this anyway `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

Because we are allocating an array, C++ knows that it should use the array version of `new` instead of the scalar version of `new`. Essentially, the `new[]` operator is called, even though the [] isn't placed next to the new keyword.

The length of dynamically allocated arrays has to be a type that's convertible to `std::size_t`. In practice, using an `int` length is fine, since `int` will convert to `std::size_t`.

Because this memory is allocated from a different place than the memory used for fixed arrays, the size of the array can be quite large. Programs that need to allocate a lot of memory in C++ typically do so dynamically.

## Dynamically deleting arrays

When deleting a dynamically allocated array, we have to use the array version of delete, which is `delete[]`.

This tell the CPU that it needs to clean up multiple variables instead of a single variable. Array `new[]` keeps track of how much memory was allocated to a variable, so that array `delete[]` can delete the proper amount. However, the size/length is not accessible to the programmer.

Using the scalar version of delete on an array will result in undefined behavior, such as data corruption, memory leaks, crashes, or other problems.

## Dynamic arrays are almost identical to fixed arrays

A fixed array holds the memory address of the first array element. A fixed array can decay into a pointer that points to the first element of the array. In this decayed form, the length of the fixed array is not available (and therefore neither is the size of the array via `sizeof()`), but otherwise there is little difference.

A dynamic array starts its life as a pointer that points to the first element of the array. Consequently, it has the same limitations in that it doesn't know its length or size. A dynamic array functions identically to a decayed fixed array, with the exception that the programmer is resonsible for deallocating the dynamic array via the `delete[]` keyword.

## Initializing dynamically allocated arrays

To initialize a dynamically allocated array to 0:

` int* array{ new int[length]{} }; `  

Prior to C++11, there was no easy way to initialize a dynamic array to a non-zero value (initializer lists only worked for fixed arrays). This means you had to loop through the array and assign element values explicitly. However, starting with C++11, it's now possible to initialize dynamic arrays using initializer lists:

` int fixedArray[5] = { 9, 7, 5, 3, 1 }; // initialize a fixed array before C++11 `  
` int* array{ new int[5]{9, 7, 5, 3, 1 } }; // initialize a dynamic array since C++11 `  
` // To prevent writing the type twice, we can use auto. This is often done for types with long names. `  
` auto* array{ new int[5]{ 9, 7, 5, 3, 1 } }; `  

Note that this syntax has no operator= between the array length and the initializer list. For consistency, fixed arrays can also be initialized using uniform initialization:

` int fixedArray[]{ 9, 7, 5, 3, 1 }; // initialize a fixed array in C++11 `  
` char fixedArray[]{ "Hello, world! }; `  

Explicitly stating the size of the array is optional. Doing so can help catching errors early, because the compiler will warn you when the specified length is less than the actual length. 

## Resizing arrays

Dynamically allocating an array allows you to set the array length at the time of allocation. However, C++ does not provide a built-in way to resize an array that has already been allocated. It is possible to work around this limitation by dynamically allocating a new array, copying the elements over, and deleting the old array. However, this is error prone, especially when the element type is a class (which have special rules governing how they are created). 

If you need this capability, C++ provides a resizable array as part of the standard library called `std::vector`.
