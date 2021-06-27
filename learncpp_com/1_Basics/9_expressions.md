# Introduction to expressions

An **expression** is a combination of literals, variables, operators, and explicit function calls (not shown above) that produce a single output value. When an expression is executed, each of the terms in the expression is evaluated until a single value remains.

Expressions do not end in a semicolon, and cannot be compiled by themselves. Rather, expressions are always evaluated as part of statements.

**Wherever you can use a single value in C++, you can use an expression instead, and the compiler will resolve the expression down to a single value.**

Certain expressions (like _x = 5_) are useful by themselves. We can convert any expression into an equivalent statement (called an expression statement). An **expression statement** is a statement that consists of an expression followed by a semicolon. When the statement is executed, the expression will be evaluated (and the result will be descarded).

**Values calculated in an expression are discarded at the end of the expression.**

Statements are used when we want the program to perform an action. Expressions are used when we want the program to calculate a value.
