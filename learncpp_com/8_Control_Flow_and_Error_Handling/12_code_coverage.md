# Code coverage

The term **code coverage** is used to describe how much of the source code of a program is executed while testing. There are many different metrics used for code coverage. 

## Statement coverage

The term **statement coverage** refers to the percentage of statements in your code that have been exercised by your testing routines.

While aiming for 100% statement coverage is good, it's not enough to ensure correctness.

## Branch coverage

**Branch coverage** refers to the percentage of branches that have been executed, each possible branch (the affirmative case and negative case) counted separately.

**Beat practice**<br/>
_Aim for 100% branch coverage of your code._

## Loop coverage

**Loop coverage** (informally called **the 0, 1, 2 test**) says that if you have a loop in your code, you should ensure it workd properly when it iterates 0 times, 1 time, and 2 times. If it works correctly for the 2-iteration case, it should work correctly for all iterations greater than 2. These three tests therefore cover all possibilites.

**Best practice**<br/>
_Use the 0, 1, 2 test to ensure your loops work correctly with different number of iterations._

## Testing different categories of input

When writing functions that accept parameters, or when accepting use input, consider what happens with different categories of input. In this context, "category" means a set of inputs that have similar characteristics.

For integers, make sure you've considered how your function handles negative values, zero, and positive values. You should also check for overflow if that's relevant.

For floating point numbers, make sure you've considered how your function handles values that have precision issues (values that are slightly larger or smaller than expected). Good test values are 0.1 and -0.1 (to test numbers that are slightly larger than expected) and 0.6 and -0.6 (to test numbers that are slightly smaller than expected).

For strings, make sure you've considered how your function handles an empty string (just a null terminator), normal valid strings, strings that have whitespace, and strings that are all whitespace.

If your function takes a pointer, don't forget to test `nullptr` as well.

**Best practice**<br/>
_Test different categories of input values to make sure your unit handles them properly._
