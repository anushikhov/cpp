# Literals

In programming, a **constant** is a fixed value that my not be changed. C++ has two kinds of constants: literal constants, and symbolic constants. 

**Literal constants** (usually just called **literals**) are values inserted directly into the code. 

They are constants because their values can not be changed dynamically (you have to change them, and then recompile for the change to take effect). 

Just like objects have a type, all literals have a type. The type of a literal is assumed from the value and format of the literal itself.

Integral literals default to int, boolean values to bool, floating point values to double, chars to char and C-style strings to const char[14].

If the default type of a literal is not as desired, you can change the type of a literal by adding a suffix.

![Literal suffixes](https://raw.githubusercontent.com/anushikhov/cpp/master/learncpp_com/4_Fundamental_Data_Types/img/literal_suffixes.png)

By default, floating point literal constants have a type of double. To make them float literals instead, the f (or F) suffix should be used.

` float f { 5.0f }; `  

Literals are fine to use in C++ code so long as their menaings are clear. This is most often the case when used to initialize or assign a value to a variable, do math, or print some text to the screen.

You can declare floating-point literals either in standard or scientific notation.

To use an octal literal, prefix your literal with a 0. To use a hexadecimal literal, prefix your literal with 0x.

Hexadecimal values are often used to represent memory addresses or raw values in memory.

Prior to C++14, there is no way to assign a binary literal. However, hexadecimal pairs provide us with a useful workaround:

` int bin{}; `  
` bin = 0x01; // assign binary 0000 0001 to the variable `  

In C++14, we can assign binary literals by using the 0b prefix:

` bin = 0b1; // assign binary 0000 0001 to the variable `  

Because long literals can be hard to read, C++14 also adds the ability to use a quotation mark (') as a digit separator.

` int bin { 0b1011'0010 }; // assign binary 1011 0010 to the variable `  
` long value{ 2'132'673'427 }; // much easier to read than 2132673427 `  

By default, C++ prints values in decimal. However, you can tell it to print in other formats. Printing in decimal, octal, or hex is easy via use of std::dec, std::oct, and std::hex:

` int x { 27 }; `  
` std::cout << x << '\n';             // decimal (by default) `  
` std::cout << std::hex << x << '\n'; // hexadecimal `  
` std::cout << x << '\n' ;            // now hexadecimal `  
` std::cout << std::oct << x << '\n'; // now octal `  
` std::cout << std::dec << x << '\n'; // return to decimal `  
` std::cout << x << '\n';             // decimal `  

The C++ standard library includes a type called std::bitset in the <bitset> header that lets printing in binary. To use std::bitset, we can define a std::bitset variable and tell std::bitset how many bits we want to store. The number of bits must be a compile time constant. std::bitset can be initialized with an unsigned integral value (in any format, including decimal, octal, hex, or binary).

` #include <bitset> // for std::bitset `  
` #include <iostream> `  
` `  
` int main() `  
` { `  
`     // std::bitset<8> means we want to store 8 bits `  
`     std::bitset<8> bin1{ 0b1100'0101 };             // binary literal for binary 1100 0101 `  
`     std::bitset<8> bin2{ 0xC5 };                    // hexadecimal literal for binary 1100 0101 `  
` `  
`     std::cout << bin1 << ' ' << bin2 << '\n'; `  
`     std::cout << std::bitset<4>{ 0b1010 } << '\n';  // we can also print from std::bitset directly `  
` `  
`     return 0; `  
` } `  

We can also create a temporary (anonymous) std::bitset to print a single value. In the above code, this line:  

` std::cout << std::bitset<4>{ 0b1010 } << '\n'; `  

creates a temporary std::bitset object with 4 bits, initializes it with 0b1010, prints the value in binary, and then discards the temporary std::bitset.


## Magic numbers, and why they are bad

A **magic number** is a literal (usually a number) in the middle of the code that does not have any context.
 
Using magic numbers is generally considered bad practice because, in addition to not providing context as to what they are being used for, they pose problems if the value needs to change.

Fortunately, better options (symbolic constants) exist.

**Best practice**
_Don't use magic numbers in your code._
