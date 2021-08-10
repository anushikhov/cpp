# Ellipsis (and why to avoid them)

There are certain cases where it can be useful to be able to pass a variable number of parameters to a function. C++ provides a special specifier known as ellipsis (aka "...") that allow us to do precisely this. 

Functions that use ellipsis take the form:

` return_type function_name(argument_list, ...) `  

The `argument_list` is one or more normal function parameters. Functions that use ellipsis must have at least one non-ellipsis parameter. Any arguments passed to the function must match the `argument_list` parameters first. The ellipsis must always be the last parameter in the function. The ellipsis capture any additional arguments (if there are any). Though it is not quite accurate, it is conceptually useful to think of the ellipsis as an array that holds any additional parameters beyond those in the `argument_list`.

` #include <iostream> `  
` #include <cstdarg> // needed to use ellipsis `  

` // The ellipsis must be the last parameter `  
` // count is how many additional arguments we're passing `  
` double findAverage(int count, ...) `  
` { `  
&emsp;&emsp;&emsp;` double sum{ 0 }; `  

&emsp;&emsp;&emsp;` // We access the ellipsis through a va_list `  
&emsp;&emsp;&emsp;` va_list list; `  


&emsp;&emsp;&emsp;` // We initialize the va_list using va_start. `  
&emsp;&emsp;&emsp;` // The first parameter is the list to initialize. `  
&emsp;&emsp;&emsp;` // The second parameter is the last non-ellipsis parameter. `  
&emsp;&emsp;&emsp;` va_start(list, count); `  

&emsp;&emsp;&emsp;` // Loop through all the ellipsis arguments `  
&emsp;&emsp;&emsp;` for(int arg{ 0 }; arg < count; ++arg) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` // We use va_arg to get parameters out of our ellipsis `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` // The first parameter is va_list we're using `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` // The second parameter is the type of the parameter `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` sum += va_arg(list, int); `  
&emsp;&emsp;&emsp;` } `  

&emsp;&emsp;&emsp;` // Cleanup the va_list when we're done `  
&emsp;&emsp;&emsp;` va_end(list); `  

&emsp;&emsp;&emsp;` return sum / count; `  
` } `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` std::cout << findAverage(5, 1, 2, 3, 4, 5) << '\n'; `  
&emsp;&emsp;&emsp;` std::cout << findAverage(6, 1, 2, 3, 4, 5, 6) << '\n'; `  
` } `  

We have to include the `cstdarg` header. This header defines `va_list`, `va_arg`, `va_start`, and `va_end`, which are macros that we need to use to access the parameters that are part of the ellipsis.

We then declare our function that uses the ellipsis. The ellipsis parameter has no name. Instread, we access the values in the ellipsis through a special type known as `va_list`. It is conceptually useful to think of `va_list` as a pointer that points to the ellipsis array. First, we declare a `va_list`, which we've called "list" for simplicity.

The next thing we need to do is make list pointer to our ellipsis parameters. We do this by calling `va_start()`. `va_start()` takes two parameters: the `va_list` itself, and the name of the last non-ellipsis parameter in the function. Once `va_start()` has been called, `va_list` points to the first parameter in the ellipsis. 

To get the value of the parameter that `va_list` currently points to, we use `va_arg()`. `va_arg()` also takes two parameters: the `va_list` itself, and the type of the parameter we're trying to access. Note that `va_arg()` also moves the `va_list` to the next parameter in the ellipsis.

Finally, to clean up when we are done, we call `va_end()`, with `va_list` as the parameter.

`va_start()` can be called again any time we want to reset the `va_list` to point to the first parameter in the ellipsis again.


## Why ellipsis are dangerous: Type checking is suspended

With regular function parameters, the compiler uses type checking to ensure the types of the function arguments match the types of the function parameters (or can be implicitly converted so they match). This helps ensure you don't pass a function an integer when it was expecting a string, or vice versa. However, note that ellipsis parameters have no type declarations. When using ellipsis, the compiler completely suspends type checking for ellipsis parameters. This means it is possible to send arguments of any type to the ellipsis. However, the downside is that the compiler will no longer be able to warn you if you call the function with ellipsis arguments that do not make sense. When using ellipsis, it is completely up to the caller to ensure the function is called with ellipsis arguments that do not make sense. When using the ellipsis, it is completely up to the caller to ensure the function is called with ellipsis arguments that the function can handle. That leaves quite a bit of room for error (especially if the caller wan't the one who wrote the function).

Type checking on the parameters is suspended, and we have to trust the caller to pass in the right type of parametesr. If they don't, the compiler won't complain -- our program will just produce garbage (or maybe crash).


## Why ellipsis are dangerous: ellipsis don't know how many parameters were passed  

Not only do the ellipsis throw away the type of the parameters, it also throws away the number of parameters in the ellipsis. This means we have to devise our own solution for keeping track of the number of parameters passed into the ellipsis. Typically, this is done in one of three ways.

### Method 1: Pass a length parameter

Method #1 is to have one of the fixed parameters represent the number of optional parameters passed.

### Method 2: Use a sentinel value  

Method #2 is to use a sentinel value. A **sentinel** is a special value that is used to terminate a loop when it is encountered. For example, with strings, the null terminator is used as a sentinel value to denote the end of the string. With ellipsis, the sentinel is typically passed in as the last parameter. Here's an example that uses a sentinel value of -1:

` #include <iostream> `  
` #include <cstdarg> `  

` double findAverage(int first, ...) `  
` { `  
&emsp;&emsp;&emsp;` double sum{ status_cast<double>(first) }; `  

&emsp;&emsp;&emsp;` va_list list; `  

&emsp;&emsp;&emsp;` va_start(list, first); `  

&emsp;&emsp;&emsp;` int count{ 1 }; `  

&emsp;&emsp;&emsp;` while(true) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` int arg{ va_arg(list, int) }; `  

&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` if(arg == -1) `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` break; `  

&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` sum += arg; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` ++count; `  
&emsp;&emsp;&emsp;` } `  

&emsp;&emsp;&emsp;` va_end(list); `  

&emsp;&emsp;&emsp;` return sum / count; `  
` } `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` std::cout << findAverage(1, 2, 3, 4, 5, -1) << '\n'; `  
&emsp;&emsp;&emsp;` std::cout << findAverage(1, 2, 3, 4, 5, 6, -1) << '\n'; `  
` } `  

We no longer need to pass an explicit length as the first parameter. Instead, we pass a sentinel value as the last parameter.

However, there are a couple of challenges here. First, C++ requires that we pass at least one fixed parameter. In the previous example, this was our count variable. In this example, the first value is actually part of the numbers to be averaged. So instead of treating the first value to be averaged as part of the ellipsis parameters, we explicitly declare it as a normal parameter. We then need special handling for it inside the function (in this case, we set sum to first instead of 0 to start).

Second, this requires the user to pass in the sentinel as the last value. If the user forgets to pass in the sentinel value (or passes in the wrong value), the function will loop continuously until it runs into garbage that matches the sentinel (or crashes).

Finally, note that we've chosen -1 as our sentinel. That's fine if we only wanted to find the average of positive numbers, but what if we wanted to include negative numbers? Sentinel values only work well if there is a value that falls outside the valid set of values for the problem you are trying to solve.

### Method 3: Use a decoder string  

Method #3 involves passing a "decoder string" that tells the program how to interpret the parameters.

` #include <iostream> `  
` #include <string> `  
` #include <cstdarg> `  

` double findAverage(std::string decoder, ...) `  
` { `  
&emsp;&emsp;&emsp;` double sum{ 0 }; `  

&emsp;&emsp;&emsp;` va_list list; `  

&emsp;&emsp;&emsp;` va_start(list, decoder); `  

&emsp;&emsp;&emsp;` int count = 0; `  

&emsp;&emsp;&emsp;` while(true) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` char codetype{ decoder[count] }; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` switch(codetype) `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` default: `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` case '\0': `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` // Cleanup the va_list when we're done `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` va_end(list) `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` return sum / count; `  

&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` case 'i': `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` sum += va_arg(list, int); `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` ++count; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` break; `  

&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` case 'd': `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` sum += va_arg(list, double); `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` ++count; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` break; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` } `  
&emsp;&emsp;&emsp;` } `  
` } `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` std::cout << findAverage("iiiii", 1, 2, 3, 4, 5) << '\n'; `  
&emsp;&emsp;&emsp;` std::cout << findAverage("iiiiii", 1, 2, 3, 4, 5, 6) << '\n'; `  
&emsp;&emsp;&emsp;` std::cout << findAverage("iiddi", 1, 2, 3.5, 4.5, 5) << '\n'; `  
` } `  

In this example, we pass a string that encodes both the number of optional variables and their types. The cool thing is that this lets us deal with parameters of different types. However, this method has downsides as well: the decoder string can be a bit cryptic, and if the number or types of the optional parameters don't match the decoder string precisely, bad things can happen.

This is what C `printf` does.

### Recommendations for safer use of ellipsis  

First, if possible, do not use ellipsis at all. Oftentimes, other reasonable solutions are available, even if they require slightly more work. For example, in our `findAverage()` program, we could have passed in a dynamically sized array of integers instead. This would have provided both strong type checking (to make sure the caller doesn't try to do something nonsensical) while preserving the ability to pass a variable number of integers to be averaged.

Second, if you do use ellipsis, do not mix expected argument types within your ellipsis if possible. Doing so vastly increases the possibility of the caller inadvertently passing in data of the wrong type and `va_arg()` producing a garbage result.

Third, using a count parameter or decoder string as part of the argument list is generally safer than using a sentinel as an ellipsis parameter. This forces the user to pick an appropriate value for the count/decoder parameter, which ensures the ellipsis loop will terminate after a reasonable number of iterations even if it produces a garbage value.

...  

To improve upon ellipsis-like functionality, C++11 introduced `parameter packs` and `variadic templates`, which offers functionality similar to ellipsis, but with strong type checking. However, significant usability challenges impeded adoption of this feature.

In C++17, `fold expressions` were added, which significantly improve the usability of parameter packs, to the point where they are now a viable option.
