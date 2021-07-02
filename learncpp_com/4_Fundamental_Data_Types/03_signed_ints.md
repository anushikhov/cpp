# Signed integers

An **integer** is an integral type that can represent positive and negative whole numbers, including 0. C++ has 4 different fundamental integer types available for use: short (min 15 bits), int (min 16 bits, but typically 32 bits on modern architectures), long (32 bits), long long (64 bits).


## Signed integers

By default, integers are **signed**, which means the number's sign is preserved. Therefore, a signed integer can hold both positive and negative numbers (and 0).


## Defining signed integers

All integers (except int) can be defined with an optional _int_ suffix:

` short s; `  

or 

` short int s; `  

This suffix should not be used. In addition to being more typing, adding the _int_ suffix makes the type harder to distinguish from variables of type _int_. This can lead to mistakes if the short or long modifier is inadvertently missed.

The integer types can also take an optional _signed_ keyword, which by convention is typically placed before the type name:

` signed short ss; `  

However, this keyword should not be used, as it is redundant, since integers are signed by default.

**Best practice**
_Prefer the shorthand types that do not use the int suffix or signed prefix._


## Signed integer ranges

The set of specific values that a data type can hold is called its **range**. The range of an integer variable is determined by two factors: its size (in bits), and whether it is signed or not.

By definition, an 8-bit signed integer has a range of -128 to 127. This means a signed integer can store any integer value between -128 and 127 (inclusive) safely.

An 8-bit integer contains 8 bits. 2^8 is 256, so an 8-bit integer can hold 256 possible values. There are 256 possible values between -128 and 127, inclusive.

**An n-bit signed variable has a range of -(2^(n-1)) to 2^(n-1).**


## Integer overflow

**Integer overflow** (often called _overflow_ for short) occurs when we try to store a value that is outside the range of the type. Essentially, the number we are trying to store requires more bits to represent than the object has available. In such a case, data is lost because the object doesn't have enough memory to store everything.

In the case of signed integers, which bits are lost is not well defined.

**Signed integer overflow will result in undefined behavior.**


## Integer division

When doing division with two integers (called **integer division**), C++ always produces an integer result. Since integers can't hold fractional values, any fractional portion is simply dropped.

**Be careful when using integer division, as you will lose any fractional parts of the quotient. However, if it's what you want, integer division is safe to use, as the results are predictable.**

