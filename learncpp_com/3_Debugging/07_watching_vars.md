# Using and integrated debugger: Watching variables

### Watching variables

**Watching a variable** is the process of inspecting the value of a variable while the program is executing in debug mode. 

### The watch window

Using the mouse over or QuickWatch (in VS) to inspect variables is fine if you want to know the value of a variable at a particular point in time, but it's not particularly well suited to watching the value of a variable change as you run the code because you continually have to rehover/reselect the variable.

In order to address this issue, all modern integrated debuggers provide another feature, called a watch window. The **watch window** is a window where you can add variables you would like to continually inspect, and these variables will be updated as you step through your program.

Using watches is the best way to watch the value of a variable change over time as you step through your program.

#### The watch window can evaluate expressions too

The watch window will also allow you to evaluate simple expressions. 

**Identifiers in watches expressions will evaluate to their current values. If you want to know what value an expression in your code is actually evaluating to, _run to cursor_ to it first, so that all identifiers have the correct values.**

#### Local watches

Because inspecting the value of local variables inside a function is common while debugging, many debuggers will offer some way to quickly watch the value of _all_ variables in scope.

If you're just looking to watch the value of a local variable, check the _locals_ window first.
