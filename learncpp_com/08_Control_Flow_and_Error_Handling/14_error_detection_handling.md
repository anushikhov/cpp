# Detecting and handling errors

If an error is the result of a misused language feature or logic error, the error can simply be corrected. But most errors in a program don't occur as the result of inadvertently misusing language features -- rather, most errors occur due to faulty assumptions made by the programmer and/or a lack of proper error detection/handling.

There are three key places where assumption errors typically occur:

* When a function returns, the programmer may have assumed the called function was successful when it was not.
* When program receives input (either from the user, or a file), the programmer may have assumed the input was in the correct formal and semantically valid when it was not.
* When a function has been called, the programmer may have assumed the parameters would be semantically valid when they were not.


## Handling errors in functions

There are 4 general strategies that can be used to handle an error the causes a function to fail:

* Handle the error within the function
* Pass the error back to the caller to deal with
* Halt the program
* Throw an exception

### Handling the error within the function

If possible, the best strategy is to recover from the error in the same function in which the error occurred, so that the error can be contained and corrected without impacting any code outside the function. There are two options here: retry until successful, or cancel the operation being executed.

If the error has occurred due to something outside of the program's control, the program can retry until success is archieved. For example if the program requires an internet connection, and the user has lost their connection, the program may be able to display a warning and then use a loop to periodically recheck for internet connectivity.

An alternate strategy is just to ignore the error and/or cancel the operation. The primary challenge with doing this is that the caller or user have no way to identify that something went wrong. In such case, printing an error message can be helpful. 

However, if the calling function is expecting the called function to produce a return value or some useful side-effect, then just ignoring the error may not be an option.

### Passing errors back to the caller

In many cases, the error can't reasonably be handled in the function that detects the error. In such cases, the best option can be to pass the error back to the caller.

If the function has a void return type, it can be changed to return a Boolean that indicates success or failure. That way, the caller can check the return value to see if the function failed for some reason.

If the function returns a normal value, in some cases, the full range of return values isn't used. In such cases, we can use a return value that wouldn't otherwise be possible to occur normally to indicate an error.

If the full range of return values are needed, then using the return value to indicate an error will not be possible. In such a case, an `out` might be a viable choice.

### Fatal errors

If the error is so bad that the program can not continue to operate properly, this is called a **non-recoverable** error (also called a **fatal error**). In such cases, the best thing to do is terminate the program. If your code is in `main()` or a function called directly from `main()`, the best thing to do is let `main()` return a non-zero status code. However, if you're deep in some nested subfunction, it may not be convenient or possible to propagate the error all the way back to `main()`. In such a case, a halt statement (such as `std::exit()`) can be used.

### Exceptions

Because returning an error from a function back to the caller is complicated (and the many different ways to do so leads to inconsistency, and inconsistency leads to mistakes), C++ offers an entirely separate way to pass errors back to the caller: _exceptions_.

The basic idea is that when an error occurs, an exception is "thrown". If the current function does not "catch" the error, the caller of the function has a chance to catch the error. If the caller does not catch the error, the caller's caller has a chance to catch the error. The error progressively moves up the call stack until it is either caught and handled (at which point execution continues normally), or until `main()` fails to handle the error (at which point the program is terminated with an exception error).
