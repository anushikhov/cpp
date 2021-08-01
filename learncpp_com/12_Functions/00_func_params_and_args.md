# Function parameters and arguments

A **function parameter** (sometimes called a **formal parameter**) is a variable declared in the function declaration.

An **argument** (sometimes called an **actual parameter**) is the value that is passed to the function by the caller.

When a function is called, all of the parameters of the function are created as variables, and the value of the arguments are copied into the parameters.

Even though parameters are not declared inside the function block, function parameters have local scope. This means that they are created when the function is invoked, and are destroyed when the function block terminates.

There are 3 primary methods of passing arguments to functions: pass by value, pass by reference, and pass by address.
