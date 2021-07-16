# Compound statements (blocks)

A **compound statement** (also called a **block**, or **block statement**) is a group of zero or more statements that is treated by the compiler as if it were a single statement.

Blocks can be used anywhere a single statement is allowed. No semicolon is needed at the end of a block.

Function body is a block. Although functions cannot be nested inside one another, blocks can be nested inside other blocks. 

When blocks are nested, the enclosing block is typically called the **outer block** and the enclosed block is called the **inner block** or **nested block**.

By default, an if statement executes a single statement if the condition evaluates to true. However, we can replace this single statement with a block of statements if we want multiple statements to execute when the condition evaluates to true.

The **nesting level** (also called the **nesting depth**) of a function is the maximum number of nested blocks you can be inside at any point in the function (including the outer block).

The C++ standard says that C++ compilers should support 256 levels of nesting -- however not all do.

Despite what C++ technically supports, it's a good idea to keep your nesting level to 3 or less. 

Just as overly-long functions are good candidates for refactoring, overly-nested functions are hard to read and are good condidates for refactoring (with the most nested blocks becoming separate functions).

**Best practice**<br/>
_Keep the nesting level of your functions to 3 or less. If your function has a need for more nested levels, consider refactoring your function into sub-functions._
