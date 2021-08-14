# Introduction to lambdas (anonymous functions)

A **lambda expression** (also called a **lambda** or **closure**) allows us to define an anonymous function inside another function. The nesting is important, as it allows us both to avoid namespace naming pollution, and to define the function as close to where it is used as possible (providing additional context).

Lambdas take the form:

` [ captureClause ] ( parameters ) -> returnType `  
` { `  
&emsp;&emsp;&emsp;` statements; `  
` } `  

The `capture clause` and `parameters` can both be empty if they are not needed.

The `return type` is optional, and if omitted, `auto` will be assumed (thus using type inference used to determine the return type). While type inference for function return types should be avoided, in this context, it's fine to use(because these functions are typically so trivial).

Also note that lambdas have no name, so we don't need to provide one.

A trivial lambda definition looks like this:

` #include <iostream> `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` []() {}; // defines a lambda with no captures, no parameters, and no return type `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

...  

` #include <algorithm> `  
` #include <array> `  
` #include <iostream> `  
` #include <string_view> `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` constexpr std::array<std::string_view, 4> arr{ "apple", "banana", "walnut", "lemon" }; `  

&emsp;&emsp;&emsp;` // Define the function right where we use it. `  
&emsp;&emsp;&emsp;` const auto found{ std::find_if(arr.begin(), arr.end(), `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` [](std::string_view str) // lambda with no capture clause `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` return (str.find("nut") != std::string_view::npos); `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` }) }; `  

&emsp;&emsp;&emsp; ` if(found == arr.end()) `   
&emsp;&emsp;&emsp; ` { `   
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; ` std::cout << "No nuts\n:"; `  
&emsp;&emsp;&emsp; ` } `  
&emsp;&emsp;&emsp; ` else `   
&emsp;&emsp;&emsp; ` { `   
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; ` std::cout << "Found" << *found << '\n'; `  
&emsp;&emsp;&emsp; ` } `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

## Type of a lambda  

In the above example we, defined a lambda right where it was needed. This use of a lambda is sometimes called a **function literal**.  

However, writing a lambda in the same line as it's used can sometimes make code harder to read. Much like we can initialize a variable with a literal value (or a function pointer) for use later, we can also initialize a lambda variable with a lambda definition and then use it later. A named lambda along with a good function name can make code easier to read.

For example, in the following snippet, we're using `std::all_of` to check if all elements of an array are even: 

` // Bad: we have to read the lambda to understand what's happening. `  
` return std::all_of(array.begin(), array.end(), [](int i){ return ((i % 2) == 0); }); `  

We can improve the readability of this as follows:

` // Good: Instead, we can store the lambda in a named variable and pass it to the function `  
` auto isEven() `  
` { `  
&emsp;&emsp;&emsp;` [](int i) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` return ((i % 2 ) == 0); `  
&emsp;&emsp;&emsp;` } `  
` }; `  

` return std::all_of(array.begin(), array.end(), isEven); `   

Lambdas don't have a type that we can explicitly use. When we write a lambda, the compiler generates a unique type just for the lambda that is not exposed to us.

In actuality, lambdas aren't functions (which is part of how they avoid the limitation of C++ not supporting nested function). They're a special kind of object called a **functor**. Functors are objects that contain an overloaded `operator()` that makes them callable like a function.

Although we don't know the type of a lambda, there are several ways of storing a lambda for use post-definition. If the lambda has an empty capture clause, we can use a regular function pointer. A function pointer won't work with lambda captures, however `std::function` can be used for lambdas even if they are capturing something.

` #include <functional> `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` // A regular function pointer - only works with an empty capture clause. `   
&emsp;&emsp;&emsp;` double (*addNumbers1)(double, double) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` [](double a, double b) `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` return (a + b); `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` } `  
&emsp;&emsp;&emsp;` }; `  

&emsp;&emsp;&emsp;` addNumbers1(1, 2); `  

&emsp;&emsp;&emsp;` // Using std::function - the lambda could have a non-empty capture clause. `  
&emsp;&emsp;&emsp;` std::function addNumbers2 // pre-C++17, use std::function<double(double, double)> instead `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` [](double a, double b) `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` return (a + b); `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` } `  
&emsp;&emsp;&emsp;` }; `  

&emsp;&emsp;&emsp;` addNumbers2(3, 4); `  

&emsp;&emsp;&emsp;` // Using auto - stores the lambda with its real type. `  
&emsp;&emsp;&emsp;` auto addNumbers3 `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` [](double a, double b) `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` { `   
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` return (a + b); `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` } `  
&emsp;&emsp;&emsp;` }; `  

&emsp;&emsp;&emsp;` addNumbers3(5, 6); `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

The only way of using the lambda's actual type is by means of `auto`. `auto` also has the benefit of having no overhead compared to `std::function`.

Unfortunately, we can't always use `auto`. In cases where the actual lambda is unknown (e.g. because we're passing a lambda to a function as a parameter and the caller determines what lambda will be passed in), we can't use `auto` without compromises. In such cases, `std::function` can be used.

` #include <functional> `  
` #include <iostream> `  

` // We don't know what fn will be. std::function works with regular functions and lambdas. `  
` void repeat(int repetitions, const std::function<void(int)>& fn) `  
` { `  
&emsp;&emsp;&emsp;` for(int i{ 0 }; i < repetitions; ++i) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` fn(i); `  
&emsp;&emsp;&emsp;` } `  
` } `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` repeat(3, [](int i) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << i << '\n'; `  
&emsp;&emsp;&emsp;` }); `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

If we had used `auto` for the type of `fn`, the caller of the function wouldn't know what parameters and return type `fn` needs to have. Furthermore, functions with `auto` parameters cannot be separated into a header and source file. 

**Use `auto` when initializing variables with lambdas, and `std::function` if you can't initialize the variable with the lambda.**  

## Generic lambdas  

For the most part, lambda parameters work by the same rules as regular function parameters.

One notable exception is that since C++14 we're allowed to use `auto` for parameters (in C++20, regular functions are able to use `auto` for parameters too). When a lambda has one or more `auto` parameter, the compiler will infer what parameter types are needed from the calls to the lambda.

Because lambdas with one or more `auto` parameters can potentially work with a wide variety of types, they are called **generic lambdas**.

When used in the context of a lambda, `auto` is just a shorthand for a template parameter.

...  

` #include <algorithm> `  
` #include <array> `  
` #include <iostream> `  
` #include <string_view> `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` constexpr std::array weekdays // pre-C++17 use std::array<const char*, 12> `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` "Monday", `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` "Tuesday", `   
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` "Wednesday", `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` "Thursday", `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` "Friday", `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` "Saturday", `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` "Sunday" `  
&emsp;&emsp;&emsp;` }; `  

&emsp;&emsp;&emsp;` // Search for two consecutive weekdays that start with the same letter. `  
&emsp;&emsp;&emsp;` const auto sameLetter{ std::adjacent_find(weekdays.begin(), weekdays.end(), `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` [](const auto& a, const auto& b) `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` return (a[0] == b[0]); `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` }) }; `  

&emsp;&emsp;&emsp;` // Make sure that two days were found. `  
&emsp;&emsp;&emsp;` if(sameletter != months.end()) `  
&emsp;&emsp;&emsp;` { `   
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` // std::next returns the next iterator after sameLetter `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << *sameLetter << " and " << *std::next(sameLetter) `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` << " start with the same letter\n"; `  
&emsp;&emsp;&emsp;` } `  


&emsp;&emsp;&emsp;` return 0; `  
` } `  


In the above example, `auto` parameters are used to capture strings by `const` reference. Because all string types allow access to their individual characters via `operator[]`, we don't need to care whether the user is passing in a `std::string`, C-style string, or something else. This allows us to write a lambda that could accept any of these, meaning if we change the type of `weekdays` later, we won't  have to rewrite the lambda.

However, `auto` isn't always the best choice.

` #include <algorithm> `  
` #include <array> `  
` #include <iostream> `  
` #include <string_view> `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` constexpr std::array weekdays // pre-C++17 use std::array<const char*, 12> `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` "Monday", `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` "Tuesday", `   
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` "Wednesday", `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` "Thursday", `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` "Friday", `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` "Saturday", `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` "Sunday" `  
&emsp;&emsp;&emsp;` }; `  

&emsp;&emsp;&emsp;` // Count how many weekdays consist of 6 letters `  
&emsp;&emsp;&emsp;` const auto sixLetterDays{ std::count_if(weekdays.begin(), weekdays.end(), `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` [](std::string_view str) { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` return (str.length() == 6);  `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` }) }; `  

&emsp;&emsp;&emsp;` std::cout << "There are " << sixLetterDays << " weekdays with 6 letters\n"; `  

&emsp;&emsp;&emsp;` return 0; `   
` } `  

In this example, using `auto` would infer a type of `const char*`. C-style strings aren't easy to work with (apart from using `operator[]`). In this case, we prefer to explicitly define the parameter as a `std::string_view`, which allows us to work with the underlying data much more easily (e.g. we can ask the string view for its length, even if the user passed in a C-style array).

## Generic lambdas and static variables

A unique lambda will be generated for each different type that `auto` resolves to. 

Note that if the a generic lambda uses static duration variables, those variables are not shared between the generated lambdas.

To have a shared counter between different generated lambdas, define a global variable or a `static` local variable outside of the lambda. However, both global and static local variables can cause problems and make it more difficult to understand code. We'll be able to avoid this through lambda captures.

## Return type deduction and trailing return types

If return type deduction is used, a lambda's return type is deduced from the `return`-statements inside the lambda. If return type inference is used, all return statements in the lambda must return the same type (otherwise the compiler won't know which one to prefer).

In the case where we're returning different types, we have two options:

1. Do explicit casts to make all the return types match, or  
1. explicitly specify a return type for the lambda, and let the compiler do implicit conversions.

The second case is usually the better choice:

` #include <iostream> `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` // explicitly specifying this returns a double `  
&emsp;&emsp;&emsp;` auto divide{ [](int x, int y, bool bInteger) -> double { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` if(bInteger) `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` return x / y; // will do implicit conversion to double `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` else `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` return static_cast<double>(x) / y; `  
&emsp;&emsp;&emsp;` } }; `  

&emsp;&emsp;&emsp;` std::cout << divide(3, 2, true) << '\n'; `  
&emsp;&emsp;&emsp;` std::cout << divide(3, 2, false) << '\n'; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

That way, if you ever decide to change the return type, you (usually) only need to change the lambda's return type, and not touch the lambda body. 

## Standard library function objects

For common operations (e.g. addition, negation, or comparison) you don't need to write your own lambdas, because the standard library comes with many basic callable objects that can be used instead. These are defined in the `<functional>` header.

` #include <algorithm> `  
` #include <array> `  
` #include <iostream> `  

` bool greater(int a, int b) `  
` { `  
&emsp;&emsp;&emsp;` // Order @a before @b if @a is greater than @b. `  
&emsp;&emsp;&emsp;` return (a > b); `  
` } `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` std::array arr{ 13, 90, 99, 5, 40, 80 }; `  

&emsp;&emsp;&emsp;` // Pass greater to std::sort `  
&emsp;&emsp;&emsp;` std::sort(arr.begin(), arr.end(), greater); `  

&emsp;&emsp;&emsp;` for(int i : arr) `  
&emsp;&emsp;&emsp;` { `   
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << i << ' '; `  
&emsp;&emsp;&emsp;` } `  

&emsp;&emsp;&emsp;` std::cout << '\n'; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

Instead of converting the `greater` function to a lambda (which would obscure its meaning a bit), we can instead use `std::greater`:

` #include <algorithm> `  
` #include <array> `  
` #include <functional> `  
` #include <iostream> `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` std::array arr{ 13, 90, 99, 5, 40, 80 }; `  

&emsp;&emsp;&emsp;` std::sort(arr.begin(), arr.end(), std::greater{}); // need curly braces to instantiate object `  

&emsp;&emsp;&emsp;` for(int i : arr) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << i << ' '; `  
&emsp;&emsp;&emsp;` } `  

&emsp;&emsp;&emsp;` std::cout << '\n'; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

...   

Lambdas and the algorithm library may seem unnecessarily complicated when compared to a solution that uses a loop. However, this combination can allow some very powerful operations in just a few lines of code, and can be more readable than writing your own loops. On top of that, the algorithm library features powerful and easy-to-use parallelism, which you won't get with loops. Upgrading source code that uses library functions is easier than upgrading code that uses loops.

Lambdas are great, but they don't replace regular functions for all cases. Prefer regular functions for non-trivial and reusable cases.
