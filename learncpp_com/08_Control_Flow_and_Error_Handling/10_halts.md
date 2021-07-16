# Halts (exiting your program early)

A **halt** is a flow control statement that terminates the program. In C++, halts are implemented as functions (rather than keywords).

When a program exits normally and the `main()` function returns (either by reaching the end of the function, or via a return statement), a number of things happen. All local variables and function parameters are destroyed. Next, a pecial function called `std::exit()` is called, with the return value from `main()` (the status code) passed in as an argument. 

## The std::exit() function

`std::exit()` is a function that causes the program to terminate normally. **Normal termination** means the program has exited in an expected way. It does not imply anything about whether the program was successful (that's what the status code is for).

`std::exit()` performs a number of cleanup function. First, objects with static storage duration are destroyed. Then some other miscellaneous file cleanup is done if any files were used. Finally, control is returned back to the OS, with the argument passed to std::exit() used as the status code.

## Calling std::exit() explicitly

Although `std::exit()` is called implicitly when function `main()` ends, `std::exit()` can also be called explicitly to halt the program before it would normally terminate. When `std::exit()` is called this way, you will need to include the `cstdlib` header.

` #include <cstdlib> `  
` #include <iostream> `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` std::cout << 1 << '\n'; `  

&emsp;&emsp;&emsp;` std::exit(0); // terminates and returns status code 0 to operating system `  

&emsp;&emsp;&emsp;` // The following statements never execute `  

&emsp;&emsp;&emsp;` std::cout << 2 << '\n'; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

`std::exit()` can be called from any function to terminate the program at that point.

**The `std::exit()` function does not clean up local variables in the current function or up the call stack. Because of this, it's generally better to avoid calling `std::exit()`.**

## std::atexit

Because `std::exit() terminates the program immediately, you may want to manually do some cleanup before terminating. Remembering to manually call a cleanup function before calling every call to exit() adds burden to the programmer.

To assist with this, C++ offers the `std::atexit()` function, which allows you to specify a function that will automatically be called on program termination via `std::exit()`.

` #include <cstdlib> `  
` #include <iostream> `  

` void cleanup() `  
` { `  
&emsp;&emsp;&emsp;` // code here to do any kind of cleanup required `  
` } `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` // register cleanup() to be called automatically when std::exit() is called `  
&emsp;&emsp;&emsp;` std::atexit(cleanup); // we use cleanup rather than cleanup() since we're not making a function call to cleanup() right now `  

&emsp;&emsp;&emsp;` std::cout << 1 << '\n'; `  

&emsp;&emsp;&emsp;` std::exit(0); // terminate and return status code 0 to operating system `  

&emsp;&emsp;&emsp;` // The following statements never execute `  
&emsp;&emsp;&emsp;` std::cout << 2 << '\n'; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

Because `std::exit()` is called implicitly when `main()` terminates, this will invoke any functions registered by `std::atexit()` if the program exits that way. 

The function being registered must take no parameters, and have no return value.

You can register multiple cleanup functions using `std::atexit()` if you want, and they will be called in reverse order of registration (the last one registered will be called first).

In multi-threaded programs, calling `std::exit()` can cause your program to crash (because the thread calling `std::exit() will cleanup static objects that may still be accessed by other threads). For this reason, C++ has introduced another pair of functions that work similarly to `std::exit()` and `std::atexit()` called `std::quick_exit()` and `std::at_quick_exit()`. `std::quick_exit()` terminates the program normally, but does not clean up static objects, and may or may not do other types of cleanup. `std::at_quick_exit()` performs the same roel as `std::atexit()` for programs terminated with `std::quick_exit()`.

## std::abort and std::terminate

The `std::abort()` function causes your program to terminate abnormally. **Abnormal termination** means the program had some kind of unusual runtime error and the program couldn't continue to run. For example, trying to divide by 0 will result in an abnormal termination. `std::abort()` does not do any cleanup.

The `std::terminate()` function is typically used in conjuntion with exceptions. Although `std::terminate` can be called explicitly, it is more often called implicitly when an exception isn't handled (and in a few other exception-related cases). By default, `std::terminate()` calls `std::abort()`.

Destroying local objects is an important part of C++ (particularly when we get into classes), and none of the above-mentioned functions clean up local variables. Exceptions are a better and safer mechanism for handling error cases.

**Best practice**<br/>
_Only use a halt if there is no safe way to return normally from the main function. If you haven't disabled exceptions, prefer using exceptions for handling errors safely._
