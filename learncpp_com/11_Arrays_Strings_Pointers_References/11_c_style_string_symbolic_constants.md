# C-style string symbolic constants

Besides C-style strings:

` #include <iostream> `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` char myName[]{ "Alex" }; // fixed array `  
&emsp;&emsp;&emsp;` std::cout << myName << '\n'; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

C++ also supports a way to create C-style string symbolic constants using pointers:

` #include <iostream> `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` const char* myName{ "Alex" }; // pointer to symbolic constant `  
&emsp;&emsp;&emsp;` std::cout << myName << '\n'; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

While these above two programs operate and produce the same results, C++ deals with the memory allocation for these slightly differently.

In the fixed array case, the program allocates memory for a fixed array of length 5, and initializes that memory with the string "Alex\0". Because memory has been specifically allocated for the array, you're free to alter the contents of the array. The array itself is treated as a normal local variable, so when the array goes out of scope, the memory used by the array is freed up for other users.

In the symbolic constant case, how the compiler handles this is implementation defined. What usually happens is that the compiler palces the string "Alex\0" into read-onlly memory somewhere, and then sets the pointer to point to it. Because this memory may be read-only, best practice is to make sure the string is const.

For optimization purposes, multipel string literals may be considered into a single value. For example: 

` const char* name1{ "Alex" }; `  
` const char* name2{ "Alex" }; `  

These are two different string literals with the same value. The compiler may opt to combine these into a single shared string literal, with both name1 and name2 pointed at the same address. Thus, if name1 was not const, making a change to name1 could also impact name2 (which might not be expected).

As a result of string literals being stored in a fixed location in memory, string literals have static duration rather than automatic duration (that is, they die at the end of the program, not the end of the block in which they are defined). That means that when we use string literals, we don't have to worry about scoping issues. Thus, the following is okay:

` const char* getName() `  
` { `  
&emsp;&emsp;&emsp;` return "Alex"; `  
` } `  

`getName()` will return a pointer to C-style string "Alex". If this function were returning any other local variables by address, the variable would be destroyed at the end of `getName()`, and we'd return a dangling pointer back to the caller. However, because string literals have static duration, "Alex" will not be destroyed when `getName()` terminates, so the caller can still successfully access it.

C-style strings are used in a lot of old or low-level code, because they have a very small memory footprint. Modern code should favor the use of `std::string` and `std::string_view`, as those provide safe and easy access to the string.


### std::cout and char pointers

` #include <iostream> `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` int nArray[5]{ 9, 7, 5, 3, 1 }; `  
&emsp;&emsp;&emsp;` char cArray[]{ "Hello!" }; `  
&emsp;&emsp;&emsp;` const char* name{ "Alex" }; `  

&emsp;&emsp;&emsp;` std::cout << nArray << '\n'; // nArray will decay to type int*, will print the address of 9 `  
&emsp;&emsp;&emsp;` std::cout << cArray << '\n'; // cArray will decay to type char*, will print "Hello!" `  
&emsp;&emsp;&emsp;` std::cout << name << '\n'; // name is already type char*, will print "Alex" `  

&emsp;&emsp;&emsp;` return  0; `  
` } ` 

`std::cout` makes some assumptions about you intent. If you pass it a non-char pointer, it will simply print the contents of that pointer (the address that the pointer is holding). However, if you pass it an object of type `char*` or `const char*`, it will assume you're intending to print a string. Consequently, instead of printing the pointer's value, it will print the string being pointed to instead.

This can also lead to unexprected results:

` #include <iostream> `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` char c{ 'Q' }; `  
&emsp;&emsp;&emsp;` std::cout << &c; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

The compiler assumes &c was a string, so it prints the 'Q', and then keeps going. Next it prints a bunch of garbage from memory until it runt into some memory holding a 0 value, which is interpreted as a null terminator, so it stops. 
