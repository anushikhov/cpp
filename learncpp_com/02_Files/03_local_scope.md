# Introduction to local scope

Function parameters, as well as variables defined inside the function body, are called **local variables**.

Function parameters are created and initialized when the function is entered, and variables within the function body are created and initialized at the point of definition.

A local variable is destroyed in the opposite order of creation (instantiation) at the end of the set of curly braces in which it is defined (or for a function parameter, at the end of the function).

An object's **lifetime** is defined to be the time between its creation and destruction.

Variable creation and destruction happen when the program is running (called runtime), not at compile time. Therefore, **lifetime is a runtime property**.

The rules around creation, initialization, and destruction are guarantees. That is, objects must be created and initialized no later than the point of definition, and destroyed no earlier than the end of the set of the curly braces in which they are defined (or, for function parameters, at the end of the function).

In actuality, the C++ specification gives compilers a lot of flexibility to determine when local variables are created and destroyed. Objects may be created earlier, or destroyed later for optimizaton purposes. Most often, local variables are created when the function is entered, and destroyed in the opposite order of creation when the function is exited.

#### Local scope 
An identifier's **scope** determines where the identifier can be accessed within the source code.

When an identifier can be accessed, we say it is **in scope**. When an identifier cannot be access, we say it is **out of scope**.

**Scope is a compile time property**, and trying to use an identifier when it is not in scope will result in a compile error.

**A local variable's scope begins at the point of variable definition**, and stops at the end of the set of curly braces in which they are defined (or for function parameters, at the end of the function). **This  ensures variables can not be used before the point of definition (even if the compiler opts to create them before then).**

Local variables have the same definition for lifetime and scope. For local variables, scope and lifetime are linked -- i.e. a variable's lifetime starts when it enters scope, and ends when it goes out of scope.

Names used for function parameters or variables declared in a function body are only visible within the function that declares them. This means local variables within a function can be named without regard for the names of variables in other functions. This helps keep functions independent.

**Best practice**
_Define your local variables as close to their first use as reasonable._
