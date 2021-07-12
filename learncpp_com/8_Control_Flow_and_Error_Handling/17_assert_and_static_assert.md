# assert and static_assert

If the program terminates (via `std::exit`) then we will have lost our call stack and any debugging information that might help us isolate the problem. `std::abort` is a better option for such cases, as typically the developer will be given the option to start debugging at the point where the program aborted.

## Preconditions, invariants, and postconditions

In programming, a **precondition** is any condition that must always be true prior to the execution of component of code.

An **invariant** is a condition that must be true while some component is executing.

A **postcondition** is something that must be true after the execution of some component of code.

## Assertions

An **assertion** is an expression that will be true unless there is a bug in the program. If the expression evaluates to true, the assertion statement does nothing. If the conditional expression evaluates to false, an error message is displayed and the program is terminated (via `std::abort`). This error message typically contains the expression that failed as text, along with the name of the code file and the line number of the assertion. This makes it very easy to tell not only what the problem was, but where in the code the problem occurred. This can help with debugging efforts immensely.

In C++, runtime assertions are implemented via the **assert** preprocessor macro, which lives in the <cassert> header.

` #include <cassert> `  
` #include <cmath> `  
` #include <iostream> `  

` double calculateTimeUntilObjectHitsGround(double initialHeight, double gravity) `  
` { `  
&emsp;&emsp;&emsp;` assert(gravity > 0.0); // The object won't reach the ground unless there is positive gravity `  

&emsp;&emsp;&emsp;` if(initialHeight <= 0.0) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` // The object is already on the ground, or buried. `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` return 0.0; `  
&emsp;&emsp;&emsp;` } `  

&emsp;&emsp;&emsp;` return std::sqrt((2.0 * initialHeight) / gravity); `  
` } `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` std::cout << "Took " << calculateTimeUntilObjectHitsGround(100.0, -9.8) << " second(s)\n"; `  

&emps;&emsp;&emsp;` return 0; `  
` } `  

The condition `gravity > 0.0` will fail, which will tirgger the assert. That will print an error message. The actual message varies depending on the compiler used.

Although asserts are most often used to validate function parameters, they can be used anywhere you would like to validate that something is true.

Asserts are one of the few preprocessor macros that are considered acceptable to use.

Use assert statements liberally throughout your code.

### Making your assert statements more descriptive

Sometimes assert expressions are not very descriptive. There is a little trick you can use to make your assert statements more descriptive. Simply add a string literal joined by a logical AND:

` assert(found && "Car could not be found in database"); `  

A string literal always evaluates to Boolean true. Thus, logical AND-ing a string literal does not impact the evaluation of the assert. However, wehn the assert triggers, the string literal will be included in the assert message. That gives you some additional context as to what went wrong.


## NDEBUG

The `assert` macro comes with a small performance cost that is incorred each time the assert condition is checked. Furthermore, asserts should never be encountered in production code (because your code should already be thoroughly tested). Consequently, many developers prefer that asserts are only active in debug builds. C++ comes with a way to turn off asserts in production code. If the macro NDEBUG is defined, the assert macro gets disabled.

Some IDEs set NDEBUG by default as part of the project settings for release configurations.

### Some assert limitations and warnings

There are a few pitfalls and limitations to asserts. First, the assert itself can have a bug. If this happens, the assert will either report an error where none exists, or fail to report a bug where one does exist.

Second, asserts should have no side effects -- that is, the program should run the same with and without the assert. Otherwise, what you are testing in a debug configuration will not be the same as in a release configuration (assuming you ship with NDEBUG).

The `abort()` function terminates the program immediately, without a chance to do any further cleanup (e.g. close a file or database). Because of this, asserts should be used only in cases where corruption isn't likely to occur if the program terminates unexpectedly.

### Asserts vs error handling

The goal of an assertion is to catch programming errors by documenting something that should never happen. If that thing does happen, then the programmer made an error somewhere, and that error can be identified and fixed. Assertions do not allow recovery from errors (after all, if something should never happen, there's no need to recover from it), and the program will not produce a friendly error message.

Error handling is designed to gracefully handle cases that could happen (however rarely) in release configurations. These may or may not be recoverable, but one should always assume a user of the program may encounter them.

**Best practice**<br/>
_Use assertions to document cases that should be logically impossible._

Assertions are also sometimes used to document cases that were not implemented because they were not needed at the time the programmer wrote the code:

` assert(moved && "Need to handle case where student was just moved to another classroom"); `  

That way, if a future user of the code does encounter a situation where the case is needed, the code will fail with a useful error message, and the programmer can then determine how to implement that case.


## static_assert

A **static_assert** is an assertion that is checked at compile-time rather than at runtime, with a failing `static_assert` causing a compile error.

Unlike `assert`, which is declared in the `<cassert>` header, `static_assert` is a keyword, so no header needs to be included to use it.

A `static_assert` takes the following form:

` static_assert(condition, diagnostic_message) `  

If the condition is not true, the diagnostic message is printed. Here's an exampel of using `static_assert` to ensure types have a certain size:

` static_assert(sizeof(long) == 8, "long must be 8 bytes"); `  
` static_assert(sizeof(int) == 4, "int must be 4 butes"); `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` return 0; `  
` } `  

Becuase `static_assert` is evaluated by the compiler, the condition must be able to be evaluated at compile time. Also, unlike `assert` (which is evaluated at runtime), `static_assert` can be placed anywhere in the code file (even in global space).

Prior to C++17, the diagnostic message must be supplied as the second parameter. Since C++17, providing a diagnostic message is optional. 

