# Intro to loops and while statements

Loops are control flow constructs that allow a piece of code to execute repeatedly until some condition is met.

When a **while statement** (also called **while loop**) is executed, the condition is evaluated. If the condition evaluates to true, the associated statement executes.

If the expression always evaluates to true, the while loop will execute forever. This is called an **infinite loop**.

You can exit an infinite loop through a return statement, a break statement, an exit statement, a goto statement, an exception being thrown, or the user killing the program.

It is common to see this kind of loop in web server applications that run continuously and service web requests.

**Best practice**<br/>
_Favor_ `while(true)` _for intentional infinite loops._

## Loop variables

Often, we want a loop to execute a certain number of times. To do this, it is common to use a **loop variable**, often called a **counter**. A loop variable is an integer that is used to count how many times a loop has executed.

Loop variables are often given simple names, such as i, j, or k. However, if you want to know where in your programa loop variable is used, and you use the search function on i, j, or k, the search function will return half your program. For this reason, some developers prefer loop variable names like iii, jjj, or kkk. An even better idea is to use "real" variable names, such as `count`, or a name that gives more detail about what you're counting (e.g. `userCount`).

## Loop variables should be signed

Loop variables should almost always be signed, as unsigned integers can lead to unexptected issues.

**Best practice**<br/>
_Loop variables should be of type (signed) int._

## Doing something every N iterations

Each time a loop executes, it is called an **iteration**.

Often, we want to do something every nth iteration, such as print a newline. This can be done by using the modulus operator on the counter.

## Nested loops

It is also possible to nest loops inside of other loops.
