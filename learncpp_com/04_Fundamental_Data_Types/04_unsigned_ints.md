# Unsigned integers, and why to avoid them

**Unsigned integers** are integers that can only hold non-negative whole numbers.


## Defining unsigned integers

To define an unsigned integer, we use the _unsigned_ keyword. By convention, this is placed before the type:

` unsigned short us; `  


## Unsigned integer range

A 1-byte unsigned integer has a range of 0 to 255. 

**An n-bit unsigned variable has a range of 0 to (2^n)-1.**

When no negative numbers are required, unsigned integers are well-suited for networking and systems with little memory, because unsigned integers can store more positive numbers without taking up extra memory.


## Unsigned integer "overflow"

The C++ standard explicitly says "a computation involving unsigned operands can never overflow". This is contrary to general programming consensus that integer overflow encompasses both signed and unsigned use cases.

**If an unsigned value is out of range, it is divided by one greater than the largest number of the type, and only the remainder kept.**

The number 280 is too big to fit in 1-byte range of 0 to 255. 1 greater than the largest number of the type is 256. Therefore, we divide 280 by 256, getting 1 remainder 24. The remainder of 24 is what is stored.

Any number bigger than the largest number representable by the type simply "wraps around" (sometimes called "module wrapping", or more obscurely, "saturation"). 

255 is in range of a 1-byte integer, so 255 is fine. 256, however, is outside the range, so it wraps around to the value 0. 257 wraps around to the value 1. 280 wraps around to the value 24.

It's possible to wrap around the other direction as well. 0 is representable in a 2-byte integer, so that's fine. -1 is not representable, so it wraps around to the top of the range, producing the value 65,535. -2 wraps around 65,534.

Many notable bugs in vide game history happened due to wrap around behavior with unsigned integers.


### The controversy over unsigned numbers

Many developers and some large development houses, such as Google, believe that developers should generally avoid unsigned integers.

This is largely because of two behaviors that can cause problems.

1. Consider the subtraction of two unsigned numbers, such as 3 and 5. The result cannot be represented as an unsigned number. -2 will wrap around to a number close to the top of the range of a 4-byte integer. A common unwanted wrap-around happens when an unsigned integer is repeatedly decremented.

1. Unexpected behavior can result when you mix signed and unsigned integers. Even if one of the operands is signed, the other operand will cause the signed one to be promoted to an unsigned integer, and the same behavior will result.

C++ will freely convert between signed and unsigned numbers, but it won't do any range checking to make sure you don't overflow your type.

If you need to protect a function against negative inputs, ause an assertion or exception instead.

Some modern programming languages (such as Java) and frameworks (such as .NET) either don't include unsigned types, or limit their use.

Bjarne Stroustrup, the designer of C++, said, "Using an unsigned instead of an int to gain one more bit to represent positive integers is almost never a good idea."

**Avoid using unsigned numbers, except in specific cases or when unavoidable. If you do use unsigned numbers, avoid mixing signed and unsigned numbers where possible.**

### So where is it reasonable to use unsigned number?

There are still a few cases in C++ where it's okay (or necessary) to use unsigned numbers.

1. Unsigned numbers are preferred when dealing with bit manipulation.

1. Use of unsigned number is still unavoidable in some cases, mainly those having to do with array indexing.

1. If you're developing for an embedded system (e.g. an Arduino) or some other processor/memory limited context, use of unsigned numbers is more common and accepted (and in some cases, unavoidable) for performance reasons.

