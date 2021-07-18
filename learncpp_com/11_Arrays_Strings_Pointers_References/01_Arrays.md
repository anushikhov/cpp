# Arrays

Array elements are treated just like normal variables, and as such, they are not initialized when created. 

One way to "initialize" an array is to do it element by element. However, this is a pain, especially as the array gets larger. Furthermore, it's not initialization, but assignment. Assignments don't work if the array is `const`.

C++ provides a more convenient way to initialize entire arrays via use of an **initializer list**:

` int prime[5]{ 2, 3, 5, 7, 11 }; `  

If there are more initializers in the list than the array can hold, the compiler will generate an error.

However, if there are less initializers in the list than the array can hold, the remaining elements are initialized to 0 (or whatever value 0 converts to for a non-integral fundamental type -- e.g. 0.0 for double). This is called **zero initialization**.

To initialize all the elements of an array to 0, you can do this:

` int array[5]{ }; `  

If the initializer list is omitted, the elements are uninitialized, unless they are a class-type:

` int array[5]; `  

**Best practice**<br/>
_Explicitly initialize arrays, even if they would be initialized without an intializer list._

If you are initializing a fixed array of elements using an initializer list, the compiler can figure out the length of the array for you, and you can omit explicitly declaring the length of the array. This not only saves typing, it also means you don't have to update the array length if you add or remove elements later.


## Arrays and enums

One of the big documentation problems with arrays is that integer indices do not provide any information to the programmer about the meaning of the index. This can be solved by setting up an enumeration where one enumerator maps to each of the possible array indices:

` enum StudentNames `  
` { `  
&emsp;&emsp;&emsp;` kenny, `   
&emsp;&emsp;&emsp;` kyle, `  
&emsp;&emsp;&emsp;` stan, `  
&emsp;&emsp;&emsp;` butters, `  
&emsp;&emsp;&emsp;` cartman, `  
&emsp;&emsp;&emsp;` max_students `  
` }; `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` int testScores[max_students]{}; // allocate 5 integers `  
&emsp;&emsp;&emsp;` testScores[stan] = 76; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

In this way, it's much clearer what each of the array elements represents. Note that an extra enumerator named `max_students` has been added. This enumerator is used during the array declaration to ensure the array has the proper length (as the array length should be one greater than the largest index). This is useful both for documentation purposes, and because the array will automatically be resized if another enumerator is added. This trick only works if you don't change the enumerator values manually.

Enum classes don't have an implicit conversion to integer, so if you try to use them instead, you'll get a compile error. This can be addressed by using a `static_cast` to convert the enumerator to an integer. However, it might be better to use a standard enum inside of a namespace instead.


## Passing arrays to functions

When a normal variable is passed by value, C++ copies the value of the argument into the function parameter. Because the parameter is a copy, changing the value of the parameter does not change the value of the original argument.

However, because copying large arrays can be very expensive, C++ does not copy an array when an array is passed into a function. Instead, the actual array is passed.This has the side effect of allowing functions to directly change the value of array elements.

If you want to ensure a function does not modify the array elements passed into it, you can make the array const:

` void passArray(const int prime[5]) // within this function prime should be treated as a constant `  
` { `  
&emsp;&emsp;&emsp;` // each of these lines will cause compile error `  
&emsp;&emsp;&emsp;` prime[0] = 11; `  
&emsp;&emsp;&emsp;` prime[1] = 7; `  
` } `  


## Determining the length of an array

The `std::size()` function from the `<iterator>` header can be used to determine the length of arrays.

` #include <iostream> `  
` #include <iterator> `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` int array[]{1, 1, 2, 3, 5, 8, 13, 21 }; `  
&emsp;&emsp;&emsp;` std::cout << "The array has: " << std::size(array) << " elements\n"; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

Due to the way C++ passes arrays to functions, this will not work for arrays that have been passed to functions. `std::size()` will work with other kinds of objects (such as `std::array` and `std::vector`), and it will cause a compiler error if you try to use it on a fixed array that has been passed to a function. 

`std::size()` returns an unsigned value. If you need a signed value, you can either cast the result or, since C++20, use `std::ssize()` (stands for signed size).

`std::size()` was added in C++17. If you're using an old compiler, you have to use the `sizeof` operator instead. 

When the `sizeof` operator is used on arrays, it returns the total size of the array (array length multiplied by element size). So the result depends on the size of the types on different machines. We can determine the length of a fixed array by dividing the size of the entire array by the size of an array element:

` int array[]{ 1, 1, 2, 3, 5, 8, 13, 21 }; `  
` std::cout << "The array has: " << sizeof(array) / sizeof(array[0]) << " elements\n"; `  

array size = array length * element size

array length = sizeof(array) / sizeof(array[0])  

We typically use array element 0 for the array element, since it's the only element guaranteed to exist no matter waht the array length is.

This again will only work if the array is a fixed-length array, and you're doing this trick in the same function that array is declared in.

When sizeof is used on an array that has been passed to a function, it doesn't error out like `std::sizeof()` does. Instead, it returns the size of a pointer.


## Indexing an array out of range

Remember that an array of length N has array elements 0 through N-1.

**C++ does not do any checking to make sure that your indices are valid for the length of your array.**

When assign value to an element outside of an array length, you will get undefined behavior -- For example, this could overwrite the value of another variable, or cause your program to crash.

Although it happens less often, C++ will also let you use a negative index, with similarly undesirable results.

**When using arrays, ensure that your indices are valid for the range of your array.**
