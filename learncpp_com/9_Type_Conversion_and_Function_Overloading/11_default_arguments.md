# Default arguments

A **default argument** is a default value provided for a function parameter.

When making a function call, the caller can optionally provide an argument for any function parameter that has a default argument. If the caller provides an argument, the value of the argument in the function call is used. If the caller does not provide an argument, the value of the default argument is used.

Default arguments are an excellent option when a function needs a value that has a reasonable default value, but for which you want to let the caller override if they wish.

` int rollDie(int sides = 6); `  
` void openLogFile(std::string filename = "default.log"); `  

Because the user can choose whether to supply a specific argument value or use the default value, a parameter with a default value provided is sometimes called an optional parameter. However, the term is also used to refer to several other types of parameters (including parameters passed by address, and parameters using std::optional), so it is recommended to avoid the term.

## Multiple default arguments

A function can have multiple parameters with default arguments.

C++ (as of C++20) does not support a function call syntax such as `print(,,3)`. This has two major consequences:

1. Default arguments can only be supplied for the rightmost parameters.
1. If more than one default argument exists, the leftmost default argument should be the one most likely to be explicitly set by the user.

**Default arguments can only be provided for the rightmost parameters.**

## Default arguments can not be redeclared

Once declared, a default argument can not be redeclared (in the same file). That means for a function with a forward declaration and a function definition, the default argument can be declared in either the forward declaration or the function definition, but not both.

Best practice is to declare the default argument in the forward declaration and not in the function definition, as the forward declaration is more likely to be seen by other files (particularly if it's in a header file).

**Best practice**<br/>
_If the function has a forward declaration (especially one in a header file), put the default argument there. Otherwise, put the default argument in the function definiton._

## Default arguments and function overloading

Functions with default arguments may be overloaded.

Parameters with default values will differentiate a function overload, however such functions can lead to potentially ambiguous functon calls.

` void print(int x); `  
` void print(int x, int y = 10); ` 
` void print(int x, double y = 20.5); `  

` print(1, 2); // will resolve to print(int int) `  
` print(1, 2.5); // will resolve to print(int, double) `  
` print(1); // ambiguous function call `  

In the last case, the compiler is unable to tell whether `print(1)` should resolve to `print(int)` or one of the two function calls where the second parameter has a default value. The result is an ambiguous function call.

Default arguments provide a useful mechanism to specify vales for parameters that the user may or may not want to override.
