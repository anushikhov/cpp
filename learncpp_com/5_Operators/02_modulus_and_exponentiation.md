# Modulus and exponentiation

## The modulus operator

The **modulus operator** (also informally known as the remainder operator) is an operator that returns the remainder after doing an integer division.

Modulus is most useful for testing whether a number is evenly divisible by another number: if x % y evaluates to 0, then we know that x is evenly divisible by y.

**The modulus operator can also work with negative operands: x % y always returns results with the sign of x.**


## Exponentiation

The ^ operator is a Bitwise XOR operation in C++. C++ does not include an exponent operator.

To do exponents in C++, #include the <cmath> header, and use the pow() function:

` #include <cmath> `  
<br/>  
` double x{ std::pow(3.0, 4.0) }; // 3 to the 4th power `  

The parameters and the return value of function pow() are of type double. Due to rounding errors in floating point numbers, the results of pow() may not be precise (even if you pass it integers or whole numbers).

If you want to do integer exponentiation, you're better off using your own function to do so. The following function implements integer exponentiation (using the non-intuitive "**exponentiation by squaring**" algorithm for efficiency):

` #include <cstdint> // for std::int_fast64_t `  
<br/>
` // exp must be non-negative `  
` std::int_fast64_t pow(int base, int exp) `  
` { `  
&emsp;        ` std::int_fast64_t result{ 1 }; `  
&emsp;        ` while (exp) `  
&emsp;        ` { `
&emsp;              ` if (exp & 1) `  
&emsp;                    ` result *= base; `  
&emsp;              ` exp >>= 1; `  
&emsp;              ` base *= base; `  
&emsp;        ` } `  
<br/>
&emsp;        ` return result; `  
` } `  

**In the vast majority of cases, integer exponentiation will overflow the integral type. This is likely why such a function wasn't included in the standard library in the first place.**
