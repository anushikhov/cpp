# Recursion

A **recursive function** in C++ is a function that calls itself. 

## Recursive termination conditions

Recursive function calls generally work just like normal function calls. The most important difference is that they must include recursive termination condition, or they will run "forever" (actually, until the call stack runs out of memory). A **recursive termination** is a condition that, when met, will cause the recursive function to stop calling itself.

Recursive termination generally involves using an `if` statement.

` #include <iostream> `  

` void countDown(int count) `  
` { `  
&emsp;&emsp;&emsp;` std::cout << "push " << count << '\n'; `  

&emsp;&emsp;&emsp;` if(count > 1) `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` countDown(count - 1); `  

&emsp;&emsp;&emsp;` std::cout << "pop " << count << '\n'; `  
` } `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` countDown(5); `  

&emsp;&emsp;&emps;` return 0; `  
` } `  

The output will be the following:  

` push 5 `  
` push 4 `  
` push 3 `  
` push 2 `  
` push 1 `   
` pop 1 `  
` pop 2 `  
` pop 3 `  
` pop 4 `  
` pop 5 `  

If you were to look at the call stack at this point, you would see the following:

` countDown(1) `  
` countDown(2) `  
` countDown(3) `  
` countDown(4) `  
` countDown(5) `  
` main() `  

It's worth noting that the "push" outputs happen in forward order since they occur before the recursive function call. The "pop" outputs occur in reverse order because they occur after the recursive function call, as the functions are being popped off the stack (which happens in the reverse order that they were put on). 

Because recursive functions can be hard to understand by looking at them, good comments are particularly important.

` // return the sum of all the integers between 1 (inclusive) and sumto (inclusive)  `  
` // returns 0 for negative numbers `  
` int sumTo(int sumto) `  
` { `  
&emsp;&emsp;&emsp;` if(sumto <= 0) `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` return 0; `  
&emsp;&emsp;&emsp;` else if(sumto == 1) `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` return 1; `  
&emsp;&emsp;&emsp;` else `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` return sumTo(sumto - 1) + sumto; `  
` } `  

## Recursive algorithms

Recursive functions typically solve a problem by first finding the solution to a subset of the problem (recursively), and then modifying that sub-solution to get to a solution. In the above algorithm, `sumTo(value)` first solves `sumTo(value-1)`, and then adds the value of variable value to find the solution for `sumTo(value)`.

In many recursive algorithms, some inputs produce trivial outputs. For example, `sumTo(1)` has the trivial output 1, and does not benefit from further recursion. Inputs for which an algorithm trivially produces an output is called a **base case**. Base cases act as termination conditions for the algorithm. Base cases can often be identified by considering the output for an input of 0, 1, "", '', or null.

## Fibonacci numbers

One of the most famous mathematical recursive algorithms is the Fibonacci sequence. Fibonacci sequences appear in many places in nature. In the Fibonacci spiral each of the Fibonacci numbers is the length of the side of the square that the number appears in.

Fibonacci numbers are defined mathematically as:  

F(n) = 0, if n = 0
F(n) = 1, if n = 1
F(n) = f(n - 1) + f(n - 2), if n > 1  

Consequently, it's rather simple to write a (not very efficient) recursive function to calculate the nth Fibonacci number:  

` #include <iostream> `  

` int fibonacci(int count) `  
` { `  
&emsp;&emsp;&emsp;` if(count == 0) `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` return 0; `  
&emsp;&emsp;&emsp;` if(count == 1) `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` return 1; ` 
&emsp;&emsp;&emsp;` return fibonacci(count - 1) + fibonacci(count - 2); `  
` } `  

` // display the first 13 Fibonacci numbers `  
` int main() `  
` { `  
&emsp;&emsp;&emsp;` for(int count{ 0 }; count < 13; ++count) `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << fibonacci(count) << " "; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

## Memoization algorithm

The above recursive Fibonacci algorithm isn't very efficient, in part because each call to Fibonacci non-base case results in two more Fibonacci calls. This produces an exponential number of function calls (in fact, the above example calls fibonacci() 1205 times). There are techniques that can be used to reduce the number of calls necessary. One technique, called **memoization**, caches the results of expensive function calls so the result can be returned when the same input occurs again.

Here's a memoized version of the recursive Fibonacci algorithm:

` #include <iostream> `  
` #include <vector> `  

` int fibonacci(int count) `  
` { `  
&emsp;&emsp;&emsp;` // A static std::vector to cache calculated results `  
&emsp;&emsp;&emsp;` static std::vector<int> results{ 0, 1 }; `  

&emsp;&emsp;&emsp;` // If we've already seen this count, then use the cached result `  
&emsp;&emsp;&emsp;` if(count < static_cast<int>(std::size(results))) `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` return results[count]; `  
&emsp;&emsp;&emsp;` else `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` // Otherwise calculate the new result and add it `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` results.push_back(fibonacci(count - 1) + fibonacci(count - 2)); `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` return results[count]; `  
&emsp;&emsp;&emsp;` } `  
` } `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` for(int count{ 0 }; count < 13; ++count) `   
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << fibonacci(count) << " "; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

The memoized version makes 35 function calls, which is much better than the 1205 of the original algorithm.

## Recursive vs iterative

You can always solve a recursive problem iteratively -- however, for non-trivial problems, the recursive version is often much simpler to write (and read). 

Iterative functions are almost always more efficient than their recursive counterparts. This is because every time you call a function there is some amount of overhead that takes place in pushing and popping stack frames. Iterative functions avoid this overhead.

That's not to say iterative functions are always a better choice. Sometimes the recursive implementation of a function is so much clearer and easier to follow that incurring a little extra overhead is more than worth it for the benefit in maintainability, particularly if the algorithm doesn't need to recurse too many times to find a solution.

In general, recursion is a good choice when most of the following are true:

* The recursive code is much simpler to implement.  
* The recursion depth can be limited (e.g. there's no way to provide an input that will cause it to recurse down 100,000 levels).  
* The iterative version of the algorithm requires managing a stack of data.  
* This is not a performance-critical section of code.  

However, if the recursive algorithm is simpler to implement, it may make sense to start recursively and then optimize to an iterative algorithm later.  

**Best practice**<br/>  
_Generally favor iteration over recursion, except when recursion really makes sense._

