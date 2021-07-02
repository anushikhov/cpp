# Basic debugging tactics

### Debugging tactic #1: Commenting out your code

If your program is exhibiting erroneous behavior, one way to reduce the amount of code you have to search through is to comment some code out and see if the issue persists. If the issue remains, the commented out code wasn't responsible.

### Debugging tactic #2: Validating your code flow

Another problem common in more complex programs is that the program is calling a function too many or too few times (including not at all).

In such cases, it can be helpful to place statements at the top of your functions to print the function's name. That way, when the program runs, you can see which functions are getting called.

**When printing information for debugging purposes, use std::cerr, instead of std::cout. One reason for this is that std::cout may be buffered, which means there may be a pause between when you ask std::cout to output information and when it actually does. If you output using std::cout and then your program crashes immediately afterward, std::cout may or may not have actually output yet. This can mislead you about where the issue is. On the other hand, std::cerr is unbuffered, which means anything you send to it will output immediately. This helps ensure all debug output appears as soon as possible (at the cost of some performance, which we usually don't care about when debugging).**

**When adding temporary debug statements, it can be helpful to not indent them. This makes them easier to find for removal later.**

### Debugging tactic #3: Printing values

With some types of bugs, the program may be calculating or passing the wrong value. We can output the value of variables (including parameters) or expressions to ensure that they are correct.

### Why using printing statements to debut isn't good

While adding debug statements to programs for diagnostic purposes is a common rudimentary technique, and a functional one (especially when a debugger is not available for some reason). it'snot that great for a number of reasons:

1. Debug statements clutter code.
1. Debug statements clutter the output of your program.
1. Debug statements must be removed after you're done with them, which makes them non-reusable.
1. Debug statements require modification of your code to both add and to remove, which can introduce new bugs.
