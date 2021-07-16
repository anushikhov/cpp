# Fixed-width integers and size_t

C++ only guarantees that integer variables will have a minimum size -- but they could be larger depending on the target system.

The reason integer variables don't have a fixed size goes back to C, when computers were slow and performance was of the utmost concern. C opted to intentionally leave the size of an integer open so that the compiler implementors could pick a size for int that performs best on the target architecture.


## Fixed-width integers

To help with cross-platform portability, C99 defined a set of **fixed-width integers** (in the stdint.h) header that are guaranteed to have the same size on any architecture.

These are defined as follows:

![Fixed-width integers](https://raw.githubusercontent.com/anushikhov/cpp/master/learncpp_com/4_Fundamental_Data_Types/img/fixed_width_ints.png)  

C++ officially adopted these fixed-width integers as part of C++11. They can be accessed by including the _cstdint_ header, where they are defined inside the _std_ namespace. 

` #include <cstdint> `  
` #include <iostream> `  
` `  
` int main() `  
` { `  
`    std::int16_t i{5}; `  
`    std::cout << i; `  
`    return 0; `  
` } `  

The fixed-width integers have two downsides:

1. They are optional and only exist if there are fundamental types matching their widths and following a certain binary representation. Using a fixed-width integer makes your code less portable, it might not compile on other systems.
1. If you use a fixed-width integer, it may also be slower than a wider type on some architectures. If you need an integer to hold values from -10 to 20, you might be tempted to use std::int8_t. But your CPU might be better at processing 32 bit wide integers, so you just lost speed by making a restriction that was not necessary.

**The above fixed-width integers should be avoided, as they may not be defined on all target architectures.**


## Fast and least integers

To help address the above downsides, C++ also defines two alternative sets of integers.

The **fast type** (std::int_fast#\_t) provides the fastest signed integer type with a width of at least # bits (where # = 8, 16, 32, 64). For example, _std::int\_fast32\_t_ will give you the fastest signed integer type that's at least 32 bits.

The **least type** (std::int_least#\_t) provides the smallest signed integer type with a width of at least # bits.

There is also an unsigned set of fast and least types (std::uint_fast#\_t and std::uint_least#\_t).

These fast and least types are guaranteed to be defined, and are safe to use.

**Best practice**
_Favor the std::int_fast#\_t and std::int_least#\_t integers when you need an integer guaranteed to be at least a certain minimum size._

### Warning: std::int8_t and std::uint8_t may behave like chars instead of integers

Due to an oversight in the C++ specification, most compilers define and treat std::int8_t and std::uint8_t (and the corresponding fast and least fixed-width types) identically to types signed char and unsigned char respectively.
Consequently, std::cin and std::cout may work differently than you're expecting.

**Avoid the 8-bit fixed-width integer types. If you do use them, note that they are often treated like chars.**


## Integer best practices

* int should be preferred when the size of the integer doesn't matter
* If you need a variable guaranteed to be a particular size and want to favor performance, use std::int_fast#\_t.
* If you need a variable guaranteed to be a particular size and want to favor memory conservation over performance, use std::int_least#\_t. This is used most often when allocating lots of variables.

Avoid the following if possible:

* Unsigned types, unless you have a compelling reason
* The 8-bit fixed-width integer types
* Any compiler-specific fixed-width integers

## std::size_t 

The sizeof operator and many functions that return a size or length value return a value of type std::size_t. **std::size_t** is defined as an unsigned integral type, and it is typically used to represent the size or length of objects.

We can use the sizeof operator (which returns a value of type std::size_t) to ask for the size of std::size_t itself.

` #include <cstddef> // std::size_t `  
` #include <iostream> `  
` `  
` int main() `  
` { `  
`    std::cout << sizeof(std::size_t) << '\n'; `  
`    return 0; `  
` } `  

Depending on the system, std::size_t also varies in size. std::size_t is guaranteed to be unsigned and at least 16 bits, but on most systems will be equivalent to the address-width of the application. That is, for 32-bit applications, _std::size_t_ will typically be a 32-bit unsigned integer, and for a 64-bit application, _std::size_t_ will typically be a 64-bit unsigned integer. 

std::size_t is defined to be big enough to hold the size of the largest object creatable on your system (in bytes). 
For example, if std::size_t is 4 bytes wide, the largest object creatable on your system can't be larger than 4,294,967,295 bytes, because this is the largest number a 4 byte unsigned integer can store. This is only the uppermost limit of an object's size, the real size limit can be lower depending on the compiler you're using.

By definition, any object larger that the largest value size_t can hold is considered ill-formed (and will cause a compile error), as the sizeof operator would not be able to return the size without wrapping around.
