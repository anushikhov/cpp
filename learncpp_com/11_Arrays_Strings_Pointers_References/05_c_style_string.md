# C-style strings

Modern C++ supports two different types of strings: `std::string` (as part of the standard library), and C-style strings (natively, as inherited from the C language). `std::string` is implemented using C-style strings. 

A **C-style string** is simply an array of characters that uses a null terminator. A **null terminator** is a special character ('\0', ascii code 0) used to indicate the end of the string. More generally, a C-style string is called a **null-terminated string**.

To define a C-style string, simply declare a char array and initialize it with a string literal.

` char myString[]{ "string" }; `  

Although the string has only 6 letters, C++ automatically adds a null terminator to the end of the string for us (we don't need to include it ourselves). Consequently, myString is actually an array of length 7.

When declaring strings in this manner, it is a good idea to use [] and let the compiler calculate the length of the array. That way if you change the string later, you won't have to manually adjust the array length.

One important point to note is that C-style strings follow all the same rules as arrays. This means you can initialize the string upon creation, but you cannot assign values to it using the assignment operator after that.

` char myString[]{ "string" }; // ok `  
` myString = "rope"; // not ok `  

Since C-style strings are arrays, you can use the [] operator to change individual characters in the string:

` myString[1] = 'p'; `  

When printing a C-style string, `std::cout` prints characters until it encounters the null terminator. If you accidently overwrite the null terminator in a string (e.g. by assigning something to myString[6]), you'll not only get al the characters in the string, but `std::cout` will just keep printing everything in adjacent memory slots until it happens to hit a 0.

It is fine if the array is larger than the string it contains.

### C-style strings and std::cin

There are many cases where we don't know in advance how long our string is going to be. For example, consider the problem of writing a program where we need to ask the user to enter their name. We don't know how long is there name until they enter it. In this case, we can declare an array larger than we need. Although this is commonly seen in C/C++ programming, it is poor programming practice, because nothing is stopping the user from entering more characters than we allocated (either unintentionally, or maliciously). The recommended way of reading C-style strings using `std::cin` is as follows:

` #include <iostream> `  
` #include <iterator> `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` char name[255] {}; `  
&emsp;&emsp;&emsp;` std::cout << "Enter your name: "; `  
&emsp;&emsp;&emsp;` std::cin.getline(name, std::size(name)); `  
&emsp;&emsp;&emsp;` std::cout << "You entered: " << name << '\n'; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

This call to `cin.getline()` will read up to 254 characters into name (leaving room for the null terminator). Any excess characters will be discarded. In this way, we guarantee that we will not overflow the array.

### Manipulating C-style strings

C++ provides many functions to manipulate C-style strings as part of the <cstring> header. 

`strcpy()` allows you to copy a string to another string. More commonly, this is used to assign a value to a string:  

` #include <cstring> `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` char source[]{ "Copy this." }; `  
&emsp;&emsp;&emsp;` char dest[50]; `  
&emsp;&emsp;&emsp;` std::strcpy(dest, source); `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

However, `strcpy()` can easily cause array overflows. Many programmers recommend using `strncpy()` instead, which allows you to specify the size of the buffer, and ensures overflow doesn't occur. Unfortunately, `strncpy()` doesn't ensure strings are null termianted, which still leaves plenty of room for array overflow.

In C++11, `strcpy_s()` is preferred, which adds a new parameter to define the size of the destination. However, not all compilers support this function, and to use it, you have to define \__STDC_WANT_LIB_EXT1__ with integer value 1.

` #define __STDC_WANT_LTB_EXT1__ 1 `  
` #include <cstring> `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` char source[]{ "Copy this." }; `  
&emsp;&emsp;&emsp;` char dest[5]; `  
&emsp;&emsp;&emsp;` strcpy_s(dest, 5, source); // a runtime error will occur in debug mode `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

Because not all compilers support `strcpy_s()`, `strlcpy()` is a popular alternative -- even though it's non-standard, and thus not included in a lot of compilers. It also has its own set of issues. In short, there's no universally recommended solution here if you need to copy a C-style string.

Another useful function is the `strlen()` function, which returns the length of the C-style string (without the null terminator).

` #include <iostream> `  
` #include <cstring> `  
` #include <iterator> `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` char name[20]{ "Alex" }; `   
&emsp;&emsp;&emsp;` std::cout << "Author's name is: " << name << '\n'; `  
&emsp;&emsp;&emsp;` std::cout << name << " has " << std::strlen(name) << " letters.\n"; `  
&emsp;&emsp;&emsp;` std::cout << name << " has " << std::size(name) << " characters in the array.\n"; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

`strcat()` -- appends one string to another  
`strncat()` -- appens one string to another (with buffer length check)  
`strcmp()` -- compares two strings (returns 0 if equal)  
`strncmp()` -- compares two strings up to a specific number of characters (return 0 if equal)


## Don't use C-style strings

It is important to know about C-style strings because they are used in a lot of code. However, we recommend avoiding them altogether whenever possible. Unless you have a specific, compelling reason to use C-style strings, use `std::string` (defined in the `<string>` header) instead. `std::string` is easier, safer, and more flexible.

In the rare case that you do need to work with fixed buffer sizes and C-style strings (e.g. for memory limited devices), we'd recommend using a well-tested 3rd party string libraray designed for the purpose, or `std::string_view`.

**Use `std::string` or `std::string_view` instead of C-style strings.**
