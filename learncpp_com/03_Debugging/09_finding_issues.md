# Findig issues before they become problems

When you make a semantic error, that error may or may not be immediately noticeable when you run your program. An issue may lurk undetected in your code for a long time before newly introduced code or changed circumstances cause it to manifest as a program malfunction. The longer an error sits in the code base before it is found, the more likely it is to be hard to find, and something that may have been easy to fix originally turns into a debugging adventure that eats up time and energy.

So what can we do about that?

## Don't make errors

Here's an incomplete list of things that can help avoid making errors:

* Follow best practices
* Don't program when you're tired
* Understand where the common  pitfalls are in a language
* Keep your programs simple
* Don't let your functions get too long
* Prefer using the standard library to writing your own code, when possible
* Comment your code liberally

### Refactoring functions

As you add new capabilities to your programs ("behavioral changes"), you will find that some of your functions grow in length. As functions get longer, they get both more complex and harder to understand.

One way to address this is to break a single long function into multiple short ones. This process of making structural changes to your code without changing its behavior (typically in order to make your programs more maintainable) is called **refactoring**.

Functions less than ten lines are good. Functions that are less than five lines are even better.

**When making changes to your code, make behavioral changes OR structural changes, and then retest for correctness. Making behavioral and structural changes at the same time tends to lead to more errors as well as errors that are harder to find.**

### An introduction to defensive programming

Errors can be not only of your own making, but also occur when your users use the application in a way that you did not anticipate.

**Defensive programming** is a practice whereby the programmer tries to aniticipate all of the ways the software could be misused, either by end-users, or by other developers using the code. These misuses can often be detected and then mitigated (e.g. by asking a user who entered bad input to try again).

### Finding errors fast

The best way to do this is to program a little bit at a time, and then test your code and make sure it works.

However, there are few other techniques we can also use.

### An introduction to testing functions

Once common way to help uncover issues with your program is to write testing functions to "exercise" the code you've written. 

**Unit testing** is a software testing method by which small units of source code are tested to determine whether they are correct.

As with logging frameworks, there are many 3rd party unit testing frameworks that can be used. And you can write your own.

### An introduction to constraints

Constraints-based techniques involve the addition of some extra code to check that some set of assumptions or expectations are not violated. 

Once common method of doing this is via _assert_ and _static\_assert_.

### Shotgunning for general issues

Programmers tend to make certain kinds of common mistakes, and some of those mistakes can be discovered by programs trained to look for them. These programs are known as **static analysis tools** (sometimes informally called **linters**) are programs that analyze your code to identify specific semantic issues (in this context, _static_ means that these tools analyze the source code). The issues found by static analysis tools may or may not be the cause of any particular problem you are having, but may help point out fragile areas of code or issues that can be problematic in certain circumstances.

In addition to ensureing your program is syntactically correct, most modern C++ compilers will do some light static analysis to identify some common problems.

**Best practice**
_Use a static analysis tool on your programs to help find areas where your code is non-compliant with best pracices._

