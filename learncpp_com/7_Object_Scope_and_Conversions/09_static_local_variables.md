# Static local variables

The term static has different meanings in different contexts. 

Global variables have static duration, which means they are created when the program starts and destroyed when the program ends.

The `static` keyword gives a global identifier internal linkage, which means the identifier can only be used in the file in which it is defined.

Local variables have automatic duration by default, which means they are created at the point of definition, and destroyed when the block is exited.

Using the `static` keyword on a local variable changes its duration from automatic to static. This means the variable is now created at the start of the program, and destroyed at the end of the program (just like a global variable). As a result, the static variable will retain its value even after it goes out of scope.

When a variable is declared as static, it is created at the program start. Static local variables that are zero initialized or have a constexpr initializer can be initialized at program start. Static local variables with non-constexpr initializers are initialized the first time the variable definition is encountered (the definition is skipped on subsequent calls, so no reinitialization happens).

Just like we use "g_" to prefix global variables, it's common to use "s_" to prefix static (static duration) local variables.

One of the most common uses for static duration local variables is for unique ID generators:
  
` int generateID() `  
` { `  
&emsp;&emsp;&emsp;` static int s_itemID{ 0 }; `  
&emsp;&emsp;&emsp;` return s_itemID++; `  
` } `  

Static variables offer some of the benefits of global variables (they don't get destroyed until the end of the program) while limiting their visibility to block scope. This makes them safer for use even if you change their values regularly.

**Best practice**<br/>
_Initialize your static local variables. Static local variables are only initialized the first time the code is executed, not on subsequent calls._

## Static local constants

Static local variables can be made const. One good use for a const static variable is when you have a function that needs to use a const value, but creating or initializing the object is expensive (e.g. you need to read the value from a database). If you used  a normal local variable, the variable would be created and initialized every time the function was executed. With a const static local variable, you can create and initialize the expensive object once, and then reuse it whenver the function is called.

## Don't use static local variables to alter flow

Static local variables should only be used if in your entire program and in the foreseeable future of your program, the variable is unique and it wouldn't make sense to reset the variable.

**Best practice**<br/>
_Avoid static local variables unless the variable never needs to be reset._

...  

When applied to a global variable, the static keyword defines the global variable as having internal linkage, meaning the variable cannot be exported to other files.

When applied to a local variable, the static keyword defines the local variable as having static duration, meaning the variable will only be created once, and will not be destroyed until the end of the program.
