# Using an integrated debugger: Stepping

At any point in time while your program is running, the program is keeping track of a lot of things: the value of the variables you're using, which functions have been called, and the current point of execution within the program. All of this tracked information is called your **program state** (or just _state_).

A **debugger** is a computer program that allows the programmer to control how another program executes and examine the program state while that program is running. The programmer can use a debugger to execute a program line by line, examining the value of variables along the way. By comparing the actual value of variables to what  is expected, or watching the path of execution through the code, the debugger can help immensely in tracking down semantic (logic) errors.

Early debuggers, such as **gdb**, were separate programs that had command-line interfaces. Most modern IDEs available these days have an **integrated debugger** -- that is, a debugger uses the same interface as the code editor, so you can debug using the same environment that you use to write your code (rather than having to switch programs).

When trying to make use of the debugger, make sure your project is compiled using a debug build configuration. If you're compiling your project using a release configuration instead, the functionality of the debugger may not work correctly (e.g. when you try to step into your program, it will just run the program instead).

## Stepping

**Stepping** is the name for a set of related debugger features that let us execute (step through) our code statement by statement.

### Step into

The **step into** command executes the next statement in the normal execution path of the program, and then pauses execution of the program so we can examine the program's state using the debugger. If the statement being executed contains a function call, _step into_ causes the program to jump to the top of the function being called, where it will pause. 

The _Stop Debugging_ can be used at any point in the debugging process to end the dubugging session.

### Step over

The **step over** command executes the next statement in the normal execution path of the program. However, whereas _step into_ will enter function calls and execute them line by line, _step over_ will execute an entire function without stopping and return control to you after the function has been executed.

In some IDEs, the _step over_ command is called _Next line_ instead.

The _step over_ command provides a convenient way to skip functions when you are sure they already work or are not interested in debugging them right now.

### Step out

Unlike the other two stepping commands, **step out** does not just execute the next line of code. Instead, it executes all remaining code in the function currently being executed, and then returns control to you when the function has returned.

This command is most useful when you've accidently stepped into a function that you don't want to debug.

### Step back

Some debuggers have introduced a stepping capability generally referred to as _step back_ or _reverse debugging_. The goal of a _step back_ is to rewind the last step, so you can return the program to a prior state. This can be useful if you overstep, or if you want to re-examine a statement that just executed.

Implementing _step back_ requires a great deal of sophistication on the part of the debugger (because it has to keep track of a separate program state for each step). Because of the complexity, this capability isn't standardized yet, and varies by debugger.
