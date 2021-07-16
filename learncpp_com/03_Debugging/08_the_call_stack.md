# Using an integrated debugger: The call stack

When your program calls a function, it "bookmarks" the current location, makes the function call, and then returns. It "knows" where exactly to return to because it keeps track in the call stack.

The **call stack** is a list of all the active functions that have been called to get to the current point of execution. The call stack includes an entry for each function called, as well as which line of code will be returned to when the functions returns. Whenever a new function is called, that function is added to the top of the call stack. When the current function returns to the caller, it is removed from the top of the call stack, and control returns to the fuction just below it.

The **call stack window** is a debugger window that shows the current call stack.

The call stack is useful in a conjunction with breakpoints, when a breakpoint is hit and you want to know what functions were called to get to that specific point in the code.


