# Type deduction for functions

Since the compiler already has to deduce the return type from the return statement, in C++14, the `auto` keyword was extended to do function return type deduction. This works by using the `auto` keyword in place of the function's return type.

When using an `auto` return type, all return values of a function must be of the same type, otherwise an error will result.

A major downside of functions that use an `auto` return type is that such functions must be fully defined before they can be used (a forward declaration is not sufficient).

This makes sense: a forward declaration does not have enough information for the compiler to deduce the function's return type. This means normal functions that return `auto` are typically only callable from within the fine in which they are defined.

Unlike type deduction for objects, there isn't as much consensus on best practices for function return type deduction. When using type deduction with objects, the initializer is always present as part of the same statement, so it's usually not overly burdensome to determine what type will be deduced. With functions, that is not the case -- when looking at a function's prototype, there is no context to help indicate what type the function returns. A good programming IDE should make clear what the deduced type fo the function is, but in absence of having that available, a user would actually have to dig into the function body itself to determine what type the functio returned. The odds of mistakes being made are higher. And the ability for such functions to be forward declared limits their usefulness in multi-file programs.

**Best practice**<br/>
_Favor explicit return types over function return type deduction for normal functions._

## Trailing return type syntax

The `auto` keyword can also bo used to declare functions using a **trailing return syntax**, where the return type is specified after the rest of the function prototype.


` auto add(int x, int y) -> int `  
` { `  
&emsp;&emsp;&emsp;` return (x + y); `  
` } `  

In this case, `auto` does not perform type deduction -- it is just part of the syntax to use a trailing return type.

One nice thing is that it makes all of your function names line up.

` auto add(int x, int y) -> int; `  
` auto divide(double x, double y) -> double; `  
` auto printSomething() -> void; `  
` auto generateSubstring(const std::string &s, int start ,int len) -> std::string; `  

The trailing return syntax is also required for lambdas.

## Type deduction cannot be used for function parameter types

` #include <iostream> `  

` void addAndPrint(auto x, auto y) `  
` { `  
&emsp;&emsp;&emsp;` std::cout << x + y; `  
` } `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` addAndPrint(2, 3); `  
&emsp;&emsp;&emsp;` addAndPrint(4.5, 6.7); `  
` } `  

Type deduction doesn't work for function parameters, and prior to C++20, the above program won't compile. In C++20, the `auto` keyword was extended so that the above program will compile and function correctly -- however, `auto` is not invoking type deduction in this case. Rather, it is triggering _function templates_, which were designed to actually handle such cases.
