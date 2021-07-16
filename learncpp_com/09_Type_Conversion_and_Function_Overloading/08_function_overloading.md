# Introduction to function overloading

**Function overloading** allows us to create multiple functions with the same name, so long as each identically named function has different parameters (or the functions can be otherwise differentiated). Each function sharing a name (in the same scope) is called an **overloaded function** (sometimes called an **overload** for short).

**Functions can be overloaded so long as each overloaded function can be differentiated by the compiler. If an overloaded function can not be differentiated, a compile error will result.**

Because operators in C++ are just functions, operators can also be overloaded.

When a function call is made to function that has been overloaded, the compiler will try to match the function call to the appropriate overload based on the arguments used in the function call. This is called **overload resolution**.

In order for a program using overloaded functions to compile, two things have to be true:

1. Each overloaded function has to be differentiated from the others.
1. Each call to an overloaded function has to resolve to an overloaded function.

If an overloaded function is not differentiated, or if a function call to an overloaded function can not be resolved to an overloaded function, then a compile error will result.

Function overloading provides a great way to reduce the complexity of your program by reducing the number of function names you need to remember. It can and should be used liberally.

**Best practice**<br/>
_Use function overloading to make your program simpler._
