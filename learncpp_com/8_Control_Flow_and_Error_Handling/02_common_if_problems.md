# Common if statements problems

## Nested if statements and the dangling else problem

It is possible to nest if statements within other if statements.

**An `else statement` is paired up with the last unmatched if statement in the same block.**

To avoid the **dangling else** ambiguity problem when nesting if statements, it is a good idea to enclose the inner statement within a block.

Encasing the inner if statement in a block also allows us to explicitly attach an else to the outer if statement. The use of a block tells the compiler that the else statement should attach to the if statement before the block. Without the block, the else statement would attach to the nearest unmatched if statement, which would be the inner if statement.

Nested if statements can often be flattened by either restructuring the logic or by using logical operators. Code that is less nested is less error prone.

## Null statements

A **null statement** is a statement that consists of just a semicolon.

` if (x > 7) `  
&emsp;&emsp;&emsp;` ; `  

Null statements do nothing. They are typically used when the language requires a statement to exist but the programmer doesn't need one. For readability, null statements are typically placed on their own lines.

Null statements are rarely intentionally used with if statements.

**Be careful not to "terminate" your if statement with a semicolon, otherwise your conditional statement(s) will execute unconditionally (even if they are inside a block).**
