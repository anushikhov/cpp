# Explicit type conversion (casting) and static_cast

C++ comes with a number of different **type casting operators** (more commonly called **casts**) that can be used by the programmer to request that the compiler perform a type conversion. Because casts are explicit requests by the programmer, this form of type conversion is often called **explicit conversion**.

## Type casting

C++ supports 5 different types of casts: `C-style casts, static casts, const casts, dynamic casts, reinterpret casts`. The latter four are sometimes referred to as **named casts**.

`const casts` and `reinterpret casts` should generally be avoided because they are only useful in rare cases and can be harmful if used incorrectly.

**Avoid const casts and reinterpret casts unless you have a very good reason to use them.**


## C-style casts

In standard C programming, casts are done via the () operator, with the name of the type to convert the value to placed inside the parenthesis. You may still see these used in code that have been converted from C.

` double d{ (double)x / y }; // convert x to a double so we get floating point division `  

C++ will also let you use a C-style cast with a more function-call like syntax:

` double d{ double(x) / y }; `  

This performs identically to the prior example, but has the benefit of parenthesizing the value being converted (making it easier to tell what is being converted).

Although a C-style cast appears to be a single cast, it can actually perform a variety of different conversions depending on context. This can include a `static cast`, a `const cast` or a `reinterpret cast`. As a result, C-style casts are at risk of being inadvertently misused and not producing the expected behavior, something which is easily avoidable by using the C++ casts instead.

**Best practice**<br/>
_Avoid using C-style casts._


## static_cast

C++ introduces a casting operator called **static_cast**, which can be used to convert a value of one type to a value of another type.

` std::cout << 'a' << ' ' << static_cast<int>('a') << '\n'; `  

The `static_cast` operator takes an expression as input, and returns the evaluated value converted to the type specified inside the angled brackets. `static_cast` is best used to convert one fundamental type into another.

` double d{ static_cast<double>(x) / y }; `  

The main advantage of `static_cast` is that it provides compile-time type checking, making it harder to make an inadvertent error. `static_cast` is also (intentionally) less powerful than C-style casts, so you can't inadvertently remove `const` or do other things you may not have intended to do.

**Best practice**<br/>
_Favor_ `static_cast` _when you need to convert a value from one type to another type._

## Using static_cast to make narrowing conversions explicit

Compilers will often issue warnings when a potentially unsafe (narrowing) implicit type conversion is performed. Casting an `int` (2 or 4 bytes) to a `char` (1 byte) is potentially unsafe (as the compiler can't tell whether the integer value will overflow the range of the `char` or not), and so the compiler will typically print a warning. If we used list initialization, the compiler would yield an error. To get around this, we can use a static cast to convert an `int` to a `char`. When we do this, we're explicitly telling the compiler that this conversion is intended, and we accept responsibility for the consequences (e.g. overflowing the range of a `char` if that happens. 
