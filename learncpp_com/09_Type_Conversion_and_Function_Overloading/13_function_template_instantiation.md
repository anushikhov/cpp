# Function template instantiation

Function templates are not actually functions -- their code isn't compiled or executed directly. Instead, function templates have one job: to generate functions (that are compiled and executed).

To use max<T> function template, we can make a function call with the following syntax:

` max<actual_type>(arg1, arg2); `  

The process of creating functions (with specific types) from function templates (with template types) is called **function template instantiation** (or **instantiation** for short). When this process happens due to a function call, it's called **implicit instantiation**. An instantiated function is often called a **function instance** (**instance** for short) or a **template functions**. Function instances are normal functions in all regards.

The process for instantiating a function is simple: the compiler essentially clones the function template and replaces the template type (T) with the actual type specified (e.g. `int`).

Here's what the compiler actually compiles after all instantiations are done:

` #include <iostream> `  

` template <typename T> `  
` T max(T x, T y); `  

` template<> `  
` int max<int>(int x, int y) `  
` { `  
&emsp;&emsp;&emsp;` return (x > y) ? x : y; `  
` } `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` std::cout << max<int>(1, 2) << '\n'; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

An instantiated function is only instantiated the first time a function call is made. Further calls to the function are routed to the already instantiated function.

## Template argument deduction

In cases where the type of the arguments match the actual type we want, we do not need to specify the actual type -- instead, we can use **template argument deduction** to have the compiler deduce the actual type that should be used from the argument types in the fuction call.

For example, instead of making a function call like this:

` std::cout << max<int>(1, 2) << '\n'; `  

We can do one of these instead:

` std::cout << max<>(1, 2) << '\n'; `  
` std::cout << max(1, 2) << '\n'; `  

In either case, the compiler will see that we haven't provided an actual type, so it will attempt to deduce an actual type from the function arguments that will allow it to generate a `max()` function where all template parameters match the type of the provided arguments.

The difference between the two cases has to do with how the compiler resolves the function call from a set of overloaded functions. In the top case (with the empty angled brackets), the compiler will only consider `max<int>` template function overloads when determining which overloaded function to call. In the bottom case (with no angled brackets), the compiler will consider both `max<int>` template function overloads and `max` non-template function overloads.

**Best practice**<br/>
_Favor the normal function call syntax when using function templates._

## Function templates with non-template parameters

It's possible to create function templates that have both template types and non-template type parameters. The template parameters can be matched to any type, and the non-template parameters work like the parameters of normal functions:

` template <typename T> `  
` int someFcn (T x, double y) `  
` { `  
&emsp;&emsp;&emsp;` return 4; `  
` } `  

This function template has a templated first parameter, but second parameter and return type.

Instantiated functions may not always compile.

## Generic programming

Because template types can be replaced with any actual type, template types are sometimes called **generic types**. And because templates can be written agnostically of specific types, programming with templates is sometimes called **generic programming**. Whereas C++ typically has a strong focus on types and type checking, in contrast, generic programming lets us focus on the logic of algorithms and design of data structures without having to worry so much about type information.

### Conclusion

Function templates can significantly reduce code maintenance and errors by minimizing the amount of code that needs to be written and maintained.

Function templates also have a few drawbacks. First, the compiler will create (and compile) a function for each function call with a unique set of argument types. So while function templates are compact to write, they can expand into a crazy amount of code, which can lead to code bloat and slow compile times. The bigger downside of function tempaltes is that they tend to produce crazy-looking, borderline unreadable error messages that are much harder to decipher than those of regular functions. Once you understand what the error messages are trying to tell, the problems they are pinpointing are often quite straightforward to resolve.

These drawbacks are fairly minor compared with the power and safety that templates bring to your programming toolkit, so use templates liberally anywhere you need type flexibility. A good rule of thumb is to create normal functions at first, and then convert them into function templates if you find you need an overload for different parameter types.

**Best practice**<br/>
_Use function templates to write generic code that can work with a wide variety of types whenever you have the need._


