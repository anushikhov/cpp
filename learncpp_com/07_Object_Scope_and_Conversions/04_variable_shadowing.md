# Variable shadowing (name hiding)

Each block defines its own scope region. When you have a variable inside a nested block that has the same name as a variable in an outer block, the nested variable "hides" the outer variable in areas where they are both in scope. This is called **name hiding** or **shadowing**.

When inside the nested block, there's no way to directly access the shadowed variable from the outer block.

Similar to how variables in a nested block can shadow variables in an outer block, local variables with the same name as a global variable will shadow the global variable wherever the local variable is in scope.

However, because global variables are part of the global namespace, we can use the scope operator (::) with no prefix to tell the compiler we mean the global variable instead of the local variable.

## Avoid variable shadowing

Shadowing of local variables should generally be avoided, as it can lead to inadvertent errors where the wrong variable is used or modified. Some compilers will issue a warning when a variable is shadowed.

For the same reason avoid shadowing global variables. This is trivially avoidable if all of your global names use a "g_" prefix.

**Best practice**<br/>
_Avoid variable shadowing._
