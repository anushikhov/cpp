# break and continue

The **break** statement causes a while loop, do-while loop, for loop, or switch statement to end, with execution continuing with the next statement after the loop or switch being broken out of.

A break statement terminates the switch or loop, and execution continues at the first statement beyond the switch or loop. A return statement terminates the entire function that the loop is within, and execution continues at point where the function was called.

The **continue** statement provides a convenient way to end the current iteration of a loop without terminating the entire loop.

Continue statements work by causing the current point of execution to jump to the bottom of the current loop.

In the case of a for loop, the end-statement of the for loop still executes after a continue (since  this happens after the end of the loop body).

Be careful when using a continue statement with while or do-while loops. These loops typically change the value of variable used in the condition inside the loop body. If use of continue statement causes these lines to be skipped, then the loop can become infinite.

Using judiciously, `break` and `continue` can help make loops more readable by keeping the number of nested blocks down and reducing the need for comlicated looping logic.

**Best practice**<br/>
_Use break and continue when they simplify your loop logic._

A return statement that is not the last statement in a function is called an **early return**. 

**Best practice**<br/>
_Use early returns when they simplify your function's logic._
