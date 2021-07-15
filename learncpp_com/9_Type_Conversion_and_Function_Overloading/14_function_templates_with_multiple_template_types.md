# Function templates with multiple tempalte types

` max(2, 3.5); ` 

Type conversion is done only when resolving function overloads, not when performing template argument deduction.

This lack of type conversion is intentional for at least two reasons. First, it helps keep things simple: we either find an exact match between the function call arguments and template type parameters, or we don't. Second, it allows us to create function templates for cases where we want to ensure that two or more parameters have the same type.

To use different types of arguments, we can:

#### Use static_cast to convert the arguments to matching types

` std::cout << max(static_cast<double>(2), 3.5); // convert int to a double so we can call max(double, double) `  

#### Provide an actual type

` std::cout << max<double>(2, 3.5) << we provided actual type double, so the compiler won't use template argument dedutiont `  

However, it would be better if we didn't even have to think about the types when making a function call to max at all.


## Functions templates with multiple template type parameters

The root of our problem is that we've only defined the single template type (T) for our function template, and then specified that both parameters must be of this same type.

The best way to solve this problem is to rewrite our function template in such a way that our parameters can resolve to differen types. Rather than using one template type parameter T, we'll now use two (T and U):

` #include <iostream> `  

` template <typename T, typename U> `  
` T max(T x, U y) `  
` { `  
&emps;&emsp;&emsp;` return (x > y) ? x : y; `  
` } `  

` int main() `  
` { `   
&emsp;&emsp;&emsp;` std::cout << max(2, 3.5) << '\n'; `  

&emps;&emsp;&emsp;` return 0; `  
` } `  

Using the usual arithmetic rules `double` takes precedence over `int`, so our conditional operator will return a a`double`. But our function is defined as returning a T -- in cases where T resolves to an `int`, our `double` return value will undergo a narrowing conversion to an `int`, which will produce a warning (and possible loss of data).

Making the return type a U instead doesn't solve the problem, as we can always flip the order of the operands in the function call to flip the types of T and U.

It is better to let the compiler deduce what the return type shoulde be from the return statement, by using the `auto` return type.

## Abbreviated function templates

C++20 introduces a new use of the `auto` keyword. When the `auto` keyword is used as a parameter type in a normal function, the compiler will automatically convert the function into a function template with each `auto` parameter becoming an independent template type parameter. This method for creating a function template is called an **abbreviated function template**.

` auto max(auto x, auto y) `  
` { `  
&emsp;&emsp;&emsp;` return (x > y) ? x : y; `  
` } `  

is shorthand in C++20 for:

` template <typename T, typename U> `  
` auto max(T x, U y) `  
` { `  
&emsp;&emsp;&emsp;` return (x > y) ? x : y; `  
` } `  

In cases where you want each template type parameter to be an independent type, this form is preferred as the removal of the template parameter declaration line makes your code more conside and readable.

**Best practice**<br/>
_Feel free to use abbreviated function templates if each auto parameter should be an independent template type (an d your language standard is set to C++20 or newer)._
