# Function return values

When you write a user-defined function, you get to determine whether your function will return a value back to the caller or not. To return a value back to the caller, two things are needed.

1. Your function has to indicate what type of value will be returned. This is done by setting the function's **return type**, which is the type that is defined before the function's name.
1. Inside the function that will return a value, we use a **return statement** to indicate the specific value being returned to the caller.

The specific value being returned from a function is called the **return value**. 

When the return statement is executed, the return value is copied from the function back to the caller. This process is called **return by value**.

Functions are not required to return a value. To tell the compiler that a function does not return a value, a return type of **void** is used.

When a program is executed, the operating system makes a function call to _main_. Execution then jumps to the top of _main_. The statements in _main_ are executed sequentially. Finally, _main_ returns an integer value (usually 0), and the program terminates. The return value from _main_ is sometimes called a **status code** (also sometimes called an **exit code**, or rarely a **return code**), as it is used to indicate whether the program ran successfully or not.

By definition, a status code of 0 means the program executed successfully.

**Best practice**
_Your main function should return 0 if the program ran normally._

A non-zero status code is often used to indicate failure (and whie this works fine on most operating systems, strictly speaking, it's not guaranteed to be portable).

The C++ standard only defines the meaning of 3 status codes: **0**, **EXIT_SUCCESS**, and **EXIT_FAILURE**. 0 and EXIT_SUCCESS both mean the program executed successfully. EXIT_FAILURE means the program did not execute successfully.

EXIT_SUCCESS and EXIT_FAILURE are defined in the **<cstdlib>** header:

` #include <cstdlib> // for EXIT_SUCCESS and EXIT_FAILURE`  
` int main()`  
` {`  
`     return EXIT_SUCCESS;`  
` }`

To maximize portability, you should only use 0 or EXIT_SUCCESS to indicate a successful termination, or EXIT_FAILURE to indicate an unsuccessful termination.

C++ disallows calling the _main_ function explicitly.

If a function has a non-void return type, it _must_ return a value of that type (using a return statement). Failure to do so will result in undefined behavior. The only exception to this rule is for function main(), which will assume a return value of 0 if one is not explicitly provided. That said, it is best practice to explicitly return a value from main, both to show you intent, and for consistency with other functions (which will not let you omit the return value).

**Best practice**
_Always explicitly provide a return value for any function that has a non-void return type._

**Failure to return a value from a function with a non-void return type (other than main) will result in undefined behavior.**

When a return statement is executed, the function returns back to the caller immediately at that point. Any additional code in the function is ignored.

A function can only return a single value back to the caller each time it is called. The value can be a literal, the result of any valid expression, including a variable or even a call to another function that returns a value.

What the function returns and the meaning of that value is defined by the function's author. Some functions use return values as status codes, others return a calculated or selected value or nothing. Because of the wide variety of possibilities here, it's a good idea to document your function with a comment indicating what the return values mean.

One of the central tenants of good programming is "**Don't Repeat Yourself**" (often abbreviated "DRY").

This is the essence of modular programming: the ability to write a function, test it, ensure that it works, and then know that we can reuse it as many times as we want and it will continue to work (so long as we don't modify the function -- at which point we'll have to retest it).

**Best practice**
_Follow the DRY best practice: "don't repeat yourself". If you need to do something more than once, consider how to modify your code to remove as much redundancy as possible._

* **Variables can be used to store the results of calculations that need to be used more than once** (so we don't have to repeat the calculation).
* **Functions can be used to define a sequence of statements we want to execute more than once.**
* **Loops can be used to execute a statement more than once.**

Functions provide a way to minimize redundancy in our programs.
