# Local variables

## Local variables have block scope

Local variables have **block scope**, which means they are in scope from their point of definition to the end of the block they are defined within.

## All variable names within a scope must be unique

Variable names must be unique within a give scope, otherwise any references to the name will be ambiguous.

## Local variables have automatic storage duration

A variable's **storage duration** (usually just called **duration**) determines what rules govern when and how a variable will be created and destroyed. In most cases, a variable's storage duration directly determines its lifetime.

Local variables have **automatic storage duration**, which means they are created at the point of definiton and destroyed at the end of the block they are defined in.

For this reason, local variables are sometimes called **automatic variables**.

## Local variables in nested blocks

Local variables can be defined inside nested blocks. A variable's scope is limited from its point of definition to the end of the nested block, and the lifetime is the same. Because the scope of variable is limited to the inner block in which it is defined, it's not accessible anywhere in the outer block.

Nested blocks are considered part of the scope of the outer block in which they are defined. Consequently, variables defined in the outer block can be seen inside a nested block.

## Local variables have no linkage

An identifier's **linkage** determines whether other declarations of that name refer to the same object or not.

Scope defines where a single declaration can be seen and used. Linkage defines whether multiple declarations refer to the same object or not.

Local variables have no linkage, which means that each declaration refers to a unique object.

## Variables should be defined in the most limited scope

If a variable is only used within a nested block, it should be defined inside that nested block.

By limiting the scope of a variable, you reduce the complexity of the program because the number of active variables is reduced. Further, it makes it easier to see where variables are used (or aren't used). A variable defined inside a block can only be used within that block (or nested blocks). This can make the program easier to understand.

**Best practice**<br/>
_Define variables in the most limited existing scope. Avoid creating new blocks whose only purpose is to limit the scope of variables._

...  

A variable's scope determines where the variable is accessible.

Duration defines the rules that govern when a variable is created and destroyed.

A variable's lifetime is the actual time between its creation and destruction.

Local variables have block scope, which means they can be accessed inside the block in which they are defined.

Local variables have automatic duration, which means they are created at the point of definition, and destroyed at the end of the block in which they are defined.
