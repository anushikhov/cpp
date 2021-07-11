# Introduction to testing your code

**Software verification** (a.k.a. **software testing**) is the process of determining whether or not the software works as expected in all cases.

Testing a small part of your code in isolation to ensure that "unit" of code is correct is called **unit testing**. Each **unit test** is designed to ensure that a particular behavior of the unit is correct.

**Best practice**<br/>
_Write your program in small, well defined units (functions or classes), compile often, and test your code as you go._

## Informal testing

After writing a unit of code (a function, a class, or some other discrete "package" of code), you can write some code to test the unit that was just added, and then erase the test once the test passes or preserve the test code in a function along with the expected results for future use.

## Unit testing frameworks

Because writing functions to exercise other functions is so common and useful, there are entire frameworks (called **unit testing frameworks**) that are designed to help simplify the process of writing, maintaining, and executing unit tests.

## Integration testing

Once each of your units has been tested in isolation, they can be integrated into your program and retested to make sure they were integrated properly. This is called an **integration test**.
