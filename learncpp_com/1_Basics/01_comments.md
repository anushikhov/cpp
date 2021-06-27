# Comments

A **comment** is a programmer-readable note that is inserted directly into the source code of the program.

Comments serve the purpose of helping programmers document the code in some way.

#### Single-line comments

` std::cout << "Hi!"; // Everything from here is ignored by the compiler`

#### Multi-line comments

`/* This is a multi-line comment.
    This line will be ignored.
    So will this one. */`

**Don't use multi-line comments inside other multi-line comments. Wrapping single-line comments inside a multi-line comment is okay.**

Converting one or more lines of code into a comment is called **commenting out** your code. This provides a convenient way to (temporarily) exclude parts of your code from being included in your compiled program.

Reasons to do this:
1. You're working on a new piece of code that won't compile yet, and you need to run the program.
1. You've written new code that compiles but doesn't work correctly, and you don't have time to fix it until later.
1. You want to replace one piece of code with another piece of code.

**Tip**
If you always use single-line comments for your normal comments, then you can always use multi-line comments to comment out your code without conflict. If you use multi-line comments to document your code, then commenting-out code using comments can become more challenging. If you do need to comment out a code block that contains multi-line comments, you can also consider using the `#if 0` preprocessor directive.

* At the library, program, or function level, use comments to describe _what_.
* Inside the library, program, or function, use comments to describe _how_.
* At the statement level, use comments to describe _why_.

