# Why functions are useful, and how to use them effectively

Functions provide a number of benefits that make them extremely useful in programs of non-trivial length or complexity.
* **Organization** -- A function is almost like a mini-program that we can write separately from the main program, without having to think about the rest of the program while we write it. This allows us to reduce a complicated program into smaller, more manageable chunks, which reduces the overall complexity of our program.

* **Reusability** -- This avoids duplicated code and minimizes the probability of copy/paste errors. Functions can also be shared with other programs, reducing the amount of code that has to be written from scratch (and retested) each time.

* **Testing** -- Reducing redundancy, there's less code test in the first place. Also because functions are self-contained, once we've tested a function to ensure it works, we don't need to test it again unless we change it.

* **Extensibility** -- When we need to extend our program to handle a case it didn't handle before, functions allow us to make the change in one place and have that change take effect every time the function is called.

* **Abstraction** -- In order to use functions, you only need to know its name, inputs, outputs, and where it lives. You don't need to know how it works, or what other code it's dependent upon to use it. This lowers the amount of knowledge requried to use other people's code (including everything in the standard library).


#### Effectively using functions

Here are a few guidelines for writing functions:

* Statements that appear more than once in a program should generally be made into a function.
* Code that has a well-defined set of inputs and outputs is a good candidate for a function, particularly if it is complicated. For example, if we have a list of items that we want to sort, the code to do the sorting would make a great function, even if it's only done once. The input is the unsorted list, and the output is the sorted list.
* A function should generally perform one and only one task.
* When a function becomes too long, too complicated, or hard to understand, it can be split into multiple sub-functions. This is called **refactoring**.

