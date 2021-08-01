# Passing arguments by reference

While pass by value is suitable in many cases, it has a couple of limitation. First, when passing a large struct or class to a function, pass by value will make a copy of the arguments into the function parameter. In many cases, this is a needless performance hit, as the original argument would have sufficed. Second, when passing arguments by value, the only way to return a value back to the caller is via the function's return value. While this is often suitable, there are cases where it would be more clear and efficient to have the function modify the argument passed in. Pass by reference solves both of these issues.

To pass a variable by reference, we simply declare the function parameters as references rather than as normal variables:

` void addOne(int& ref) `  
` { `  
&emsp;&emsp;&emsp;` ref = ref + 1; `  
` } `  

When the function is called, ref will become a reference to the argument. Since a reference to a variable is treated exactly the same as the variable itself, any changes made to the reference are passed through to the argument.

## Returning multiple values via out parameters

Sometimes we need a function to return multiple values. However, functions can only have one return value. One way to return multiple values is using reference parameters:

` #include <iostream> `  
` #include <cmath> `  

` void getSinCos(double degrees, double& sinOut, double& cosOut) `  
` { `  
&emsp;&emsp;&emsp;` constexpr double pi { 3.14159265358979323846 }; `  
&emsp;&emsp;&emsp;` double radians{ degrees * pi / 180.0 }; `  
&emsp;&emsp;&emsp;` sinOut = std::sin(radians); `  
&emsp;&emsp;&emsp;` cosOut = std::cos(radians); `  
` } `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` double sin{ 0.0 }; `  
&emsp;&emsp;&emsp;` double cos{ 0.0 }; `  

&emsp;&emsp;&emsp;` getSinCos(30.0, sin, cos); `  

&emsp;&emsp;&emsp;` std::cout << "The sin is " << sin << '\n'; `  
&emsp;&emsp;&emsp;` std::cout << "The cos is " << cos << '\n'; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

Parameters that are only used for returning values back to the caller are called **out parameters**. We've named these out parameters with the suffix "out" to denote that they're out parameters. This helps remind the caller that the initial value passed to these parameters doesn't matter, and that we should expect them to be rewritten. By convention, output parameters are typically the rightmost parameters.

This method, while functional, has a few minor downsides. First, the caller must pass in arguments to hold the updated outputs even if it doesn't intend to use them. More importantly, the syntax is a bit unnatural, with both the input and output parameters being put together in the function call. It's not obvious from the caller's end that `sin` and `cos` are out parameters and will be changed. This is probably the most dangerous part of this method (as it can lead to mistakes being made). Some programmers and companies feel this is big enough problem to advise avoiding output parameters altogether, or using pass by address for out parameters instead (which has a clearer syntax indicating whether a parameter is modifiable or not).


## Limitations of pass by reference

Non-const references can only reference non-const l-values (e.g. non-const variables), so a reference parameter cannot accept an argument that is a const l-value or an r-value (e.g. literals and the results of expressions).

### Pass by const reference

One of the major disadvantages of pass by value is that all arguments passed by value are copied into the function parameters. When the arguments are large structs or classes, this can take a lot of time. References provide a way to avoid this penalty. When an argument is passed by reference, a reference is created to the actual argument (which takes minimal time) and no copying of values takes place. This allows us to pass large structs and classes with a minimum performance penalty.

However, this also opens us up to potential trouble. References allow the function to change the value of the argument, which is undesirable when we want an argument by read-only. If we know that a function should not change the value of an argument, but don't want to pass by value, the best solution is to pass by const reference.

A const reference is a reference that does not allow the variable being referenced to be changed through the reference. Consequently, if we use a const reference as a parameter, we guarantee to the caller that the function will not change the argument.

The following program will produce a compiler error:

` void foo(const std::string& x) `  
` { `  
&emsp;&emsp;&emsp;` x = "hello"; `  
` } `  

Using const is useful for several reasons:

* It enlists the compiler's help in ensuring values that shouldn't be changed aren't changed.
* It tells the programmer that the function won't change the value of the argument. This can help with debugging.
* You can't pass a const argument to a non-const reference parameter. Using const parameters ensures you can pass both non-const and const arguments to the function.
* Const references can accept any type of argument, including non-const l-values, const l-values, and r-values (non-const references cannot bind to r-values).

**Best practice**<br/>
_When passing an argument by reference, always use a const reference unless you need to change the value of the argument._

### References and pointers

It's possible to pass a pointer by reference, and have the function change the address of the pointer entirely:

` #include <iostream> `  

` void foo(int*& ptr) `  
` { `  
&emsp;&emsp;&emsp;` ptr = nullptr; `  
` } `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` int x{ 5 }; `  

&emsp;&emsp;&emsp;` int *ptr{ &x }; `  

&emsp;&emsp;&emsp;` std::cout << "ptr is: " << (ptr ? "non-null" : "null") << '\n'; `  

&emsp;&emsp;&emsp;` foo(ptr); `  

&emsp;&emsp;&emsp;` std::cout << "ptr is: " << (ptr ? "non-null" : "null") << '\n'; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

As a reminder, you can pass a C-style array by reference. This is useful if you need the ability for the function to change the array (e.g. for a sort function) or you need access to the array's type information of a fixed array (to do sizeof() or a for-each loop). However, note that in order for this to work, you explicitly need to define the array size in the parameter:

` #include <iostream> `  

` void printElements(int (&arr)[4]) `  
` { `  
&emsp;&emsp;&emsp;` int length{ sizeof(arr) / sizeof(arr[0]) }; `  

&emsp;&emsp;&emsp;` for(int i{ 0 }; i < length; ++i) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << arr[i] << '\n'; `  
&emsp;&emsp;&emsp;` } `  
` } `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` int arr[]{ 99, 20, 14, 80 }; `  

&emsp;&emsp;&emsp;` printElements(arr); `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

This means this only works with fixed arrays of one particular length. If we need this to work with fixed arrays of any length, we can make the array length a template parameter.

### Pros and cons of pass by reference

Advantages of passing by reference:

* References allow a function to change the value of the argument, which is sometimes useful. Otherwise, const references can be used to guarantee the function won't change the argument.  
* Because a copy of the argument is not made, pass by reference is fast, even when used with large structs or classes.  
* References can be used to return multiple values from a function (via out parameters).  
* References must be initialized, so there's no worry about null values.  

Disadvantages of passing by reference:

* Because a non-const reference cannot be initialized with a const l-value or an r-value (e.g. a literal or an expression), arguments to non-const reference parameters must be normal variables.  
* It can be hard to tell whether an argument passed by non-const reference is meant to be input, output, or both. Judicious use of const and a naming suffix for out variables can help.  
* It's impossible to tell from the function call whether the argument may change. An argument passed by value and passed by reference looks the same. We can only tell whether an argument is passed by value or reference by looking at the function declaration. This can lead to situations where the programmer does not realize a function will change the value of the argument.  

When to use pass by reference:

* When passing structs or classes (use const if read-only).  
* When you need the function to modify an argument.   
* When you need access to the type information of a fixed array.  

When not to use pass by reference:

* When passing fundamental types that don't need to be modified (use pass by value).

**Best practice**<br/>
_Use pass by (const) reference instead of pass by value for structs and classes and other expensive-to-copy types._
