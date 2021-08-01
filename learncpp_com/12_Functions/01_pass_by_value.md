# Passing arguments by value

By default, non-pointer arguments in C++ are passed by value. When an argument is **passed by value**, the argument's value is copied into the value of the corresponding function parameter.

Because a copy of the argument is passed to the function, the original argument can not be modified by the function.

Function parameters passed by value can also be made const. This will enlist the compiler's help in ensuring the function doesn't try to change the parameter's value.

### Pros and cons of pass by value

Advantages of passing by value:

* Arguments passed by value can be variables (e.g. x), literals (e.g. 6), expressions (e.g. x+1), structs, classes and enumerators. In other words, just about anything.
* Arguments are never changed by the function being called, which prevents side effects.

Disadvantages of passing by value:

* Copying structs and classes can incur a significant performance penalty, especially if the function is called many times.

When to use pass by value:

* When passing fundamental data types and enumerators, and the function does not need to change the argument.

When not to use pass by value:

* When passing structs or classes (including std::array, std::vector, and std::string).

In most cases, pass by value is the best way to accept parameters of fundamental types when the function does not need to change the argument. Pass by value is flexible and safe, and in the case of fundamental types, efficient.
