# Function overload resolution and ambiguous matches

With overloaded functions, there can be many functions that can potentially match a function call. Since a function call can only resolve to one of them, the compiler has to determine which overloaded function is the best match. The process of matching function calls to a specific overloaded function is called **overload resolution**.

## Resolving overloaded function calls

When a function call is made to an overloaded function, the compiler steps through a sequence of rules to determine which (if any) of the overloaded functions is the best match.

At each step, the compiler applies a bunch of different type conversions to the argument(s) in the function call. For each conversion applied, the compiler checks if any of the overloaded functions are now a match. After all the different type conversions have been applied and checked for matches, the step is done. The result will be one of three possible outcomes:

* No matching functions were found. The compiler moves to the next step in the sequence.
* A single matching function was found. This function is considered to be the best match. The matching process is now complete, and subsequent steps are not executed.
* More than one matching function was found. The compiler will issue an ambiguous match compile error. 

If the compiler reaches the end of the entire sequence without finding a match, it will generate a compile error that no matching overloaded function could be found for the function call.

## The argument matching sequence

#### Step 1

The compiler tries to find an exact match.

This happens in two phases.

First, the compiler will see if there is an overloaded function where the type of the arguments in the function call exactly matches the type of the parameters in the overloaded functions.

Second, the compiler will apply a number of trivial conversions to the arguments in the function call. The **trivial conversions** are a set of specific conversion rules that will modify types (without modifying the value) for purposes of finding a match. For example, a non-const type can be trivially converted to a const type.

Converting a non-reference type to a reference type (or vice-versa) is also a trivial conversion.

Matches made via the trivial conversions are considered exact matches.

#### Step 2

If no exact match is found, the compiler tries to find a match by applying the numeric promotion to the argument(s). If, after  numeric promotion, a match is found, the function call is resolved.

#### Step 3

If no match is found via numeric promotion, the compiler tries to find a match by applying numeric conversions to the arguments.

**Matches made by applying numeric promotions take precedence over any matches made by applying numeric conversions.**

#### Step 4

If no match is found via numeric conversions, the compiler tries to find a match through any user-defined conversions. Certain types (e.g. classes) can define conversions to other types that can be implicitly invoked.

We create user-defined conversions for class types by overloading the typecast operator.

#### Step 5

If no match is found via user-defined conversions, the compiler will look for a matching function that uses ellipsis.

#### Step 6

If no matches have been found by this point, the compiler gives up and will issue a compile error about not being able to find a matching function.


## Ambiguous matches

With non-overloaded functions, each function call will either resolve to a function, or no match will be found and the compiler will issue a compile error.

With overloaded functions, there is a third possible outcome: an _ambiguous match_ may be found. An **ambiguous match** occurs when the compiler find two or more functions that can be made to match in the same step. When this occurs, the compiler will stop matching and issue a compile error stating that it has found an ambiguous function call.

**If the compiler finds multiple matches in a given step, an ambiguous function call will result. This means no match from a given step is considered to be better than any other match from the same step.**

The `int` value 0 can be numerically converted to either an `unsigned int` or a `float`, so either overload matches equally well, and the result is an ambiguous function call. The same applies for the conversion of a `double` to either a `float` or `unsigned int`. Both are numeric conversions, so either overload matches equally well, and the result is again ambiguous.

### Resolving ambiguous matches

Because ambiguous matches are a compile-time error, an ambiguous match needs to be disambiguated before your program will compile. There are a few ways to resolve ambiguous matches:

1. The best way is simply to define a new overloaded function that takes parameters of exactly the type you are trying to call the function with. Then C++ will be able to find an exact match for the function call.

1. Alternatively, explicitly cast the ambiguous argument(s) to match the type of the function you want to call. 

1. If your argument is a literal, you can use the literal suffix to ensure your literal is interpreted as the correct type.

### Matching for functions with multiple arguments

If there are multiple arguments, the compiler applies the matching rules to each argument in turn. The function chosen is the one for which each argument matches at least as well as all the other functions, with at least one argument matching better than all the other functions. In other words, the function chosen must provide a better match than all the other candidate functions for at least one parameter, and no worse for all of the other parameters.

In the case that such a function is found, it is clearly and unambiguously the best choice. If no such function can be found, the call will be considered ambiguous (or a non-match).
