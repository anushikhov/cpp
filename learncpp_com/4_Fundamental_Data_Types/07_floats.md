# Floating point numbers

A **floating point** type variable is a variable that can hold a real number. 

There are three different floating point data types: **float**, **double**, and **long double**. As with integers, C++ does not define the actual size of these types (but it does guarantee minimum sizes). On modern architectures, floating point representation almost always follows IEEE 754 binary format. In this format float is 4 bytes, a double is 8, and a long double can be equivalent to a double (8 bytes), 80-bits (often padded to 12 bytes), or 16 bytes. 

**Floating point data types are always signed (can hold positive and negative values).**

![Floating point sizes](https://raw.githubusercontent.anushikhov.com/cpp/master/learncpp_com/4_Fundamental_Data_Types/img/float_sizes.png)

When using floating point literals, always include at least one decimal place (even if the deciaml is 0). This helps the compiler understand that the number is a floating point number and not an integer.

**By default, floating point literals default to type double. An f suffix is used to denote a literal of type float.**

**Best practice**
_Always make sure the type of your literals match the type of the variables they're being assigned to or used to initialize. Otherwise an unnecessary conversion will result, possibly with a loss of precision._

**Make sure you don't use integer literals where floating point literals should be used. This includes when initializing or assigning values to floating point objects, doing floating point arithmetic, and calling functions that expect floating point values.**

By default, std::cout will not print the fractional part of a number if the fractional part is 0.

### Floating point range

Assuming IEEE 754 representation:

![Floating point ranges](https://raw.githubusercontent.anushikhov.com/cpp/master/learncpp_com/4_Fundamental_Data_Types/img/float_ranges.png)

The 80-bit floating point type is a bit of a historical anomaly. On modern processors, it is typically implemented using 12 or 16 bytes (which is a more natural size for processors to handle).

The 80-bit and 16-byte floating point types have the same number of bits dedicated to the exponent, but the 16-byte number can store more significant digits.


## Floating point precision

The **precision** of a floating point number defines how many significant digits it can represent without information loss.

When outputting floating point numbers, std::cout has a default precision of 6 -- that is, it assumes all floating pont variables are only significant to 6 digits (the minimum precision of a float), and hence it will truncate anything after that.

std::cout will switch to outputting numbers in scientific notation in some cases. Depending on the compiler, the exponent will typically be padded to a minimum number of digits. 9.87654e006 is the same as 9.87654e6, just with some padding 0's. The minimum number of exponent digits displayed is compiler-specific.

The number of digits of precision a floating point variable has depends on both the size (floats have less precision than doubles) and the particular value being stored (some values have more precision than others). Float values have between 6 and 9 digits of precision, with most float values having at least 7 significant digits. Double values have between 15 and 18 digits of precision, with most double values having at least 16 significant digits. Long double has a minimum precision of 15, 18, or 33 significant digits depending on how many bytes it occupies.

We can override the default precision that std::cout shows by using an output manipulator function named std::setprecision(). **Output manipulators** alter how data is output, and are defined in the _iomanip_ header.

Precision issues don't just impact fractional numbers, they impact any number with too many significant digits.

When precision is lost because a number can't be stored precisely, this is called a **rounding error**.

Be careful when using floating point numbers that require more precision than the variables can hold.

**Best practice**
_Favor double over float unless space is at a premium, as the lack of precision in a float will often lead to inaccuracies._


### Rounding errors make floating point comparisons tricky

Foating point numbers are tricky to work with due to non-obvious differences between binary and decimal numbers. In decimal, the fraction 1/10 is represented as 0.1, however, in binary, 0.1 is represented by the infinite sequence: 0.0(0011) Because of this, when we assign 0.1 to a floating point number, we'll run into precision problems.

Rounding errors may make a number either slightly smaller or slightly larger, depending on where the truncation happens. Rounding errors can have unexpected consequences.

Because floating point numbers tend to be inexact, comparing floating point numbers is generally problematic.

Mathematical operations (such as addition and multiplication) tend to make rounding errors grow. Even though 0.1 has a rounding error in the 17th significant digit, when we add 0.1 ten times, the rounding error has crept into the 16th significant digit. Continued operations would cause this error to become increasingly significant.

**Rounding errors occur when a number cannot be stored precisely. This can happen even with simple numbers, like 0.1. Therefore, rounding errors can, and do happen all the time. Rounding errors aren't the exception -- they're the rule. Never assume your floating point numbers are exact.**

**A corollary of this rule is: be wary of using floating point numbers for financial or currency data.**


## NaN and Inf

There are two special categories of floating point numbers. The first is **Inf**, which represents infinity. Inf can be positive or negative. The second is **NaN**, which stands for "Not a Number". There are several different kinds of NaN. NaN and Inf are only available if the compiler uses a specific format (IEEE 754) for floating point numbers. If another format is used, the following code produces undefined behavior:

` #include <iostream> `  
` `  
` int main() `  
` { `  
`    double zero {0.0}; `  
`    double posinf {5.0 / zero}; // positive infinity `  
`    std::cout << posinf << '\n'; `  
` `  
`    double neginf {-5.0 / zero }; // negative infinity `  
`    std::cout << neginf << '\n'; `  
` `  
`    double nan {zero / zero}; // not a number (mathematically invalid) `  
`    std::cout << nan << '\n'; `  
` `  
`    return 0; `  
` } `  

**Best practice**
_Avoid division by 0 altogether, even if your compiler supports it._

Floating point numbers are useful for storing very large or very small numbers, including those with fractional components.

Floating point numbers often have small rounding errors, even when the number has fewer significant digits than the precision. Many times these go unnoticed because they are so small, and because the numbers are truncated for output. However, comparisons of floating point numbers may not give the expected results. Performing mathematical operations on these values will cause the rounding errors to grow larger.

