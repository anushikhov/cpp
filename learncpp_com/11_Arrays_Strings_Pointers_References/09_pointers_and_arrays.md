# Pointers and arrays

## Array decay

` int array[5]{ 9, 7, 5, 3, 1}; `  

To us, the above is an array of 5 integers, but to the compiler, array is a variable of type int[5].

In all but two cases, when a fixed array is used in an expression, the fixed array will **decay** (be implicitly converted) into a pointer that points to the first element of the array. You can see this in the following program: 

` #include <iostream> `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` int array[5]{ 9, 7, 5, 3, 1 }; `  

&emsp;&emsp;&emsp;` // print address of the array's first element `  
&emsp;&emsp;&emsp;` std::cout << "Element 0 has address: " << &array[0] << '\n'; `  

&emsp;&emsp;&emsp;` // print the value of the pointer the array decays to `  
&emsp;&emsp;&emsp;` std::cout << "The array decays to a pointer holding address: " << array << '\n'; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

An array and a pointer to the array are not identical. In the above case, array is of type "int[5]", and its "value" is the array elements themselves. A pointer to the array would be of type "int", and its value would be the address of the first element of the array.

All elements of the array can still be accessed through the pointer, but information derived from the array's type can not be accessed from the pointer. However, this also effectively allows us to treat fixed arrays and pointers identically in most cases. For example, we can use indirection through the array to get the value of the first element:  

` std::cout << *array; // will print 9 `  

We're not actually indirecting through the array itself. The array gets implicitly converted into a pointer, and we use indirection through the pointer to get the value at the memory address the pointer is holding (the value of the first element of the array).

We can also assign a pointer to point at the array:

` int* ptr { array }; `  
` std::cout << *ptr << '\n'; // will print 9 `  

This works because the array decays into a pointer of type int\*, and our pointer (also of type int\*), has the same type.

## Difference between pointers and fixed arrays

There are a few cases where the difference in typing between fixed arrays and pointers makes a difference. These help illustrate that a fixed array and a pointer are not the same.

The primary differences occur when using the `sizeof()` operator. When used on a fixed array, `sizeof` returns the size of the entire array (array length * element size). When used on a pointer, `sizeof` returns the size of a memory address (in bytes). The following program illustrates this:

` #include <iostream> `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` int array[5]{ 9, 7, 5, 3, 1 }; `  

&emsp;&emsp;&emsp;` std::cout << sizeof(array) << '\n'; // will print sizeof(int) * array length `  

&emsp;&emsp;&emsp;` int* ptr{ array }; `  

&emsp;&emsp;&emsp;` std::cout << sizeof(ptr) << '\n'; // will print the size of a pointer `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

A fixed array knowns how long the array it is pointing to is. A pointer to the array does not.

The second difference occurs when using the address-of operator (&). Taking the address of a pointer yields the memory address of the pointer variable. Taking the address of the array returns a pointer to the entire array. This pointer also points to the first element of the array, but the type information is different (in the above example, the type of `&array` is `int(*)[5]`. 

## Revisiting passing fixed arrays to functions

Because copying large arrays can be very expensive, C++ does not copy an array when an array is passed into a function. When passing an array as an argument to a function, a fixed array decays into a pointer, and the pointer is passed to the function:  

` #include <iostream> `  

` void printSize(int\* array) `  
` { `  
&emsp;&emsp;&emsp;` // array is treated as a pointer here `  
&emsp;&emsp;&emsp;` std::cout << sizeof(array) << '\n'; // prints the size of a pointer, not the size of the array `  
` } `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` int array[]{ 1, 1, 2, 3, 5, 8, 13, 21 }; `  
&emsp;&emsp;&emsp;` std::cout << sizeof(array) << '\n'; // will print sizeof(int) * array length `  

&emsp;&emsp;&emsp;` printSize(array); // the array argument decays into a pointer here `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

Note that this happens even if the parameter is declared as a fixed array: 

` #include <iostream> `  

` // C++ will implicitly convert parameter array[] to *array `  
` void printSize(int array[]) `  
` { `  
&emsp;&emsp;&emsp;` // array is treated as a pointer here, not a fixed array `  
&emsp;&emsp;&emsp;` std::cout << stizeof(array) << '\n'; // prints the size of a pointer, not the size of the array `  
` } `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` int array[]{ 1, 1, 2, 3, 5, 8, 13, 21 }; `  
&emsp;&emsp;&emsp;` std::cout << sizeof(array) << '\n'; // will print sizeof(int) * array length `  

&emsp;&emsp;&emsp;` printSize(array); // the array argument decaus into a pointer here `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

In the above example, C++ implicitly converts parameters using the array syntax ([]) to the pointer syntax (\*). That means the following two function declarations are identical:

` void printSize(int array[]); `  
` void printSize(int* array); `  

Some programmers prefer using the [] syntex because it makes it clear that the function is expecting an array, not just a pointer to a value. However, in most cases, because the pointer doesn't know how large the array is, you'll need to pass in the array size as a separate parameter  anyway (strings being an exception because they're null terminated).

We lightly recommend using the pointer syntax, because it makes it clear that the parameter is being treated as a pointer, not a fixed array, and that certain operations, such as `sizeof()`, will operate as if the parameter is a pointer. 

**Best practice**<br/>
_Favor the pointer syntax (*) over the array syntax ([]) for array function parameters._

## An intro to pass by address

The fact that arrays decay into pointers when passed to a function explains the underlying reason why changing an array in a function changes the actual array argument passed in. Consider the following example:

` #include <iostream> `  

` // parameter ptr contains a copy of the array's address `  
` void changeArray(int* ptr) `  
` { `  
&emsp;&emsp;&emsp;` *ptr = 5; // so changing an array element changes the _actual_array `  
` } `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` int array[]{ 1, 1, 2, 3, 5, 8, 13, 21 }; `  
&emsp;&emsp;&emsp;` std::cout << "Element 0 has value: " << array[0] << '\n'; `  

&emsp;&emsp;&emsp;` changeArray(array); `  

&emsp;&emsp;&emsp;` std::cout << "Element 0 has value: " << array[0] << '\n'; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

When `changeArray()` is called, array decays into a pointer, and the value of that pointer (the memory address of the first element of the array) is copied into the `ptr` parameter of function `changeArray()`. Although the value in `ptr` is a copy of the address of the array, `ptr` still points at the actual array (not a copy). Consequently, when indirection through `ptr` is performed, the element accessed is the actual first element of the array.

## Arrays in structs and classes don't decay

Arrays that are part of structs or classes do not decay when the whole struct or class is passed to a function. This yields a useful way to prevent decay if desired. 


