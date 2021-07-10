# for statements

The **for statement** (also called a **for loop**) is preferred when we have an obvious loop variable because it lets us easily and concisely define, initialize, test, and change the value of loop variables.

` for (init-statement; condition; end-expression) `  
&emsp;&emsp;&emsp;` statement `  

**Off-by-one errors** occur when the loop iterates one too many or one too few times to produce the desired result. Although the most common cause for these errors is using the wrong relational operator, they can sometimes occur by using pre-increment or pre-decrement instead of post-increment or post-decrement, or vice-versa.

It is possible to write for loops that omit  any or all of the statements or expressions. 

There are cases where not declaring a loop variable (because you already have one) or not incrementing it in the end-expression (because you're incrementing it some other way) is desired.

The following example produces an infinite loop:

` for (;;) `  
&emsp;&emsp;&emsp;` statement; `  

The C++ standard explicitly (and inconsistently) defines that an omitted condition-expression in a for loop should be treated as true.

Avoid using this form of the for loop altogether and use `while(true)` instead.

Sometimes for loops need to work with multiple variables. To assist with this, the programmer can define multiple variables in the init-statement, and can make use of the comma operator to change the value of multiple variables in the end-expression.

This is about the only place in C++ where defining multiple variables in the same statement, and use of the comma operator is considered an acceptable practice.

**Best practice**<br/>
_Defining multiple variables (in the init-statement) and using the comma operator (in the end-expression) is acceptable inside a for statement._

Like other types of loops, for loops can be nested inside other loops.

For statements excel when you have a counter variable. If you do not have a counter, a while statement is probably a better choice.

**Best practice**<br/>
_Prefer_ `for` _loops over_ `while` _loops when there is an obvious loop variable._
_Prefer_ `while` _loops over_ `for` _when there is no obvious loop variable._
