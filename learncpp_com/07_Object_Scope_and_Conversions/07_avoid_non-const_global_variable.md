# Why (non-const) global variables are evil

By far the biggest reason non-const global variables are dangerous is because their values can be changed by any function that is called, and there is no easy way for the programmer to know that this will happen.

Global variables make the program's state unpredictable. Every function call becomes potentially dangerous, and the programmer has no eay way of knowing which ones are dangerous and which ones are not. Local variables are much safer because other functions can not affect them directly.

One of the key reasons to declare local variables as close to where they are used as possible is because doing so minimizes the amount of code you need to look through to understand what the variable does. Global variables are at the opposite end of the spectrum -- because they can be accessed anywhere,  you might have to look through the entire program to understand their usage. In small programs, this might not be an issue. In large ones, it will be.

Global variables also make your program less modular and less flexible. A function that utilizes nothing but its parameters and has no side effects is perfectly modular. Modularity helps both in understanding what a program does, as well as with reusability. Global variables reduce modularity significantly.

In particular, avoid using global variables for important "decision-point" variables. Your program isn't likely to break if a global variable holding an information value changes. It is much more likely to break if you change a global variable that impacts how your program actually functions.

**Best practice**<br/>
_Use local variables instead of global variables whenever possible._

## The initialization order problem of global variables

Initialization of static variables (which includes global variables) happens as part of program startup, before execution of the main function. This proceeds in two phases.

The first phase is called `static initialization`. In the static initialization phase, global variables with constexpr initializers (including literals) are initialized to those values. Also, global variables without initializers are zero-initialized.

The second phase is called `dynamic initialization`. This phase is more complex and nuanced, but the gist of it is that global variables with non-constexpr initializers are initialized.

Within a single file, global variables are generally initialized in order of definition (there are a few exceptions to this rule). Given this, you need to be careful not to have variables dependent on the initialization value of other variables that won't be initialized until later.

The order of initialization across different files is not defined. Given two files, either could have its global variables initialized first. This means that if the variables in one file are dependent upon the values of variables in the other file, there's a 50% chance that those variables won't be initialized yet.

**Dynamic initialization of global variables causes a lot of problems in C++. Avoid dynamic initialization whenever possible.**

## What are very good reasons to use non-const global variables?

In some cases, judicious use of non-const global variables can actually reduce program complexity, and in these rare cases, their use may be better than the alternatives.

A good example is a log file, where you can dump error or debug information. It probably makes sense to define this as a global, because you're likely to only have one log in a program and it will likely be used everywhere in your program.

The std::cout and std::cin objects are implemented as global variables inside the std namespace.

As a rule of thumb, any use of a global variable should meet at least the following two criteria: There should only ever be one of the thing the variable represents in your program, and its use should be ubiquitous throughout your program.

## Protecting yourself from global destruction

If you do find a good use for a non-const global variable, a few useful bits of advice will minimize the amount of trouble you can get into. This advice is not only for non-const global variables, but can help with all global variables.

1. Prefix all non-namespaced global variables with "g" or "g_", or better yet, put them in a namespace, to reduce the chance of naming collisions.
1. Instead of allowing direct access to the global variable, it's a better practice to "encapsulate" the variable. Make sure the variable can only be accessed from within the file it's declared in, e.g. by making the variable static or const, then provide external global "access functions" to work with the variable. These functions can ensure proper usage is maintained (e.g. do input validation, range checking, etc...). Also, if you ever decide to change the underlying implementation (e.g. move from one db to another), you only have to update the access functions instead of every piece of code that uses the global variable directly.
1. When writing an otherwise standalone function that uses the global variable, don't use the variable directly in your function body. Pass it in an argument instead. This helps maintain modularity.

