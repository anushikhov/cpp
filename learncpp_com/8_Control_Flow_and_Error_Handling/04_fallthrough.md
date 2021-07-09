# switch fallthrough and scoping

## Fallthrough

When a switch expression matches a case label or optional default label, execution begins at the first statement following the matching label. Execution will then continue sequentially until one of the following termination conditions happens: 

1. The end of the switch block is reached
1. Another control flow statement (typically a break or return) causes the switch block or function to exit.
1. Something else interrupts the normal flow of the program (e.g. the OS shuts the program down, the universe implodes, etc...)  

Without a break or return, execution will overflow into subsequent cases.

When execution flows from a statement underneath a label into statements underneath a subsequent label, this is called **fallthrough**.

**Once the statements underneath a case or default label have started executing, they will overflow (fallthrough) into subsequent cases. Break or return statements are typically used to prevent this.**

## The [[fallthrough]] attribute

Commenting intentional fallthrough is a common convention to tell other developers that fallthrough is intended. While this works for other developers, the compiler and code analysis tools don't know how to interpret comments, so it won't get rid of the warnings.

To help address this, C++17 adds a new attribute called `[[fallthrough]]`.

**Attributes** are a modern C++ feature that allow the programmer to provide the compiler with some additional data about the code. To specify an attribute, the attribute name is placed between double hard braces. Attributes are not statements -- rather, they can be used almost anywhere where they are contextually relevant.

The [[fallthrough]] attribute modifies a null statement to indicate that fallthrough is intentional (and no warnings should be triggered).

**Best practice**<br/>
_Use the_ `[[fallthrough]]` _attribute (along with a null statement) to indicate intentional fallthrough._

## Sequential case labels

Logical OR operator can be used to combine multiple tests into a single statement:

` bool isVowel(char c) `  
` { `  
&emsp;&emsp;&emsp;` return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'); `  
` } `  

You can do something similar using switch statements by placing multiple case labels in sequence:

` bool isVowel(char c) `  
` { `  
&emsp;&emsp;&emsp;` switch (c) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` case 'a': `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` case 'e': `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` case 'i': `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` case 'o': `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` case 'u': `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` return true; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` default: `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` return false; ` 
&emsp;&emsp;&emsp;` } `  
` } `  

We can "stack" case labels to make all of those case labels share the same set of statements afterward. This is not considered fallthrough behavior, so use of comments or `[[fallthrough]]` is not needed here.

## switch case scoping

With if statements, you can only have a single statement after the if-condition, and that statement is considered to be implicitly inside a block. However, with switch statements, the statements after labels are all scoped to the switch block. No implicit blocks are created.

## Variable declaration and initialization inside case statements

You can declare (but not initialize) variables inside the switch, both before and after the case labels.

All statements inside the switch are part of the same scope. Thus, a variable defined in one case can be used in a later case, even if the case in which the variable is defined is never executed. Defining a variable without an intializer is just telling the compiler that the variable is now in scope from that point on. This doesn't require the definition to actually be executed.

However, initialization of variables is disallowed and will cause a compile error. This is because initializing a variable does require execution, and initialization could be skipped over depending on which cases are executed.

If a case needs to define and/or initialize a new variable, best practice is to do so inside a block underneath the case statement.

**If defining variables used in a case statement, do so in a block inside the case (or before the switch if appropriate).**




