# Introduction to global variables

In C++, variables declared outside of a function are called **global variables**.

By convention, global variables are declared at the top of a file, below the includes, but above any code.

**Best practice**<br/>
_Consider using a "g" or "g\_" prefix for global variables to help differentiate them from local variables._

Global variables have **file scope** (also informally called **global scope** or **global namespace scope**), which means they are visible from the point of declaration until the end of the file in which they are declared. Once declared, a global variable can be used anywhere in the file from that point onward.

Because they are defined outside of a function, global variables are considered to be part of the global namespace (hence the term "global namespace scope").

Global variables are created when the program starts, and destroyed when it ends. This is called **static duration**. Variables with static duration are sometimes called **static variables**.

**Unlike local variables, which are uninitialized by default, static variables are zero-initialized by default.**

Non-constant global variables can be optionally initialized.

Just like local variables, global variables can be constant. As with all constants, constant global variables must be initialized.

**Avoid using non-constant global variables.**
