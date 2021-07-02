# Using an integrated debugger: Running and breakpoints

### Run to cursor

The **Run to cursor** command executes the program until exection reaches the statement selected by your cursor. Then it returns control to you so you can debug starting at that point. This makes for an efficient way to start debugging at a particular point in your code, or if already debugging, to move straight to some place you want to examine further.

If you _run to cursor_ to a location that doesn't execute, _run_to_cursor_ will simply run your program until termination.

### Continue

Once you're in the middle of a debugging session, you may want to just run the program from that point forward. The easiest way to do this is to use the _continue_ command. The **continue** debug command simply continues running the program as per normal, either until the program terminates, or until something triggers control to return back to you again (such as a breakpoint).

### Start

The _continue_ command has a twin brother named _start_. The **start** command performs the same action as _continue_, just starting from the beginning of the program. It can only be invoked when not already in a debug session.

### Breakpoints

A **breakpoint** is a special marker that tells the debugger to stop execution of the program at the breakpoint when running in debug mode.

Breakpoints have a coupe of advantages over _run_to_cursor_. First, a breakpoint will cause the debugger to return control to you everytime they are encountered (unlike _run_to_cursor_, which only runs to the cursor once each time it is invoked). Second, you can set a breakpoint and it will persist until you remove it, whereas with _run_to_cursor_ you have to locate the spot you want to run to each time you invoke the command.

Breakpoints placed on lines that are not in the path of execution will not cause the debugger to halt execution of the code.

### Set next statement

The **set next statement** command allows us to change the point of execution to some other statement (sometimes informally called _jumping_). This can be used to jump the point of execution forwards and skip some code that would otherwise execute, or backwards and have something that already executed run again.

We discussed commenting out a function as a way to determine whether that function had a role in causing an issue. This requires modifying our code, and remembering to uncomment the function later. In the debugger, there's no direct way to skip a function, so if you decide you want to do this, using _set next statement_ so jump over a function call is the easiest way to do so.

Jumping backwards can also be useful if we want to watch a function that just executed run again, so we can see what it is doing.

The _set next statement_ command will change the point of execution, but will not othewise change the program state. Your variables will retain whatever values they had before the jump. As a result; jumping may cause your program to produce different values, results, or behaviors than it would otherwise. Use this capability judiciously (especially jumping backwards).

**You should not use _set next statement_ to change the point of execution to a different function. This will result in undefined behavior, and likely a crush.**


