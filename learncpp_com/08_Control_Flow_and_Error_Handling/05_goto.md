# Goto statements

An unconditional jump causes execution to jump to another spot in the code. The term "unconditional" means the jump always happens (unlike an `if statement` or `switch statement`, where the jump only happens conditionally based on the result of an expression).

In C++, unconditional jumps are implemented via a **goto statement**, and the spot to jump to is identified through use of a **statement label**. 

` #include <iostream> `  
` #include <cmath> `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` double x{}; `  
` tryAgain: // this is a statement label `  
&emsp;&emsp;&emsp;` std::cout << "Enter a non-negative number: "; `  
&emsp;&emsp;&emsp;` std::cin >> x; `  

&emsp;&emsp;&emsp;` if (x < 0.0) `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` goto tryAgain; // this is the goto statement `  

&emsp;&emsp;&emsp;` std::cout << "The square root of " << x << " is " << std::sqrt(x) << '\n'; `  
&emsp;&emsp;&emsp;` return 0; `  
` } `  

## Statement labels have function scope

Statement labels utilize **function scope**, which means the label is visible throughout the function even before its point of declaration. The `goto` statement and its corresponding statement label must appear in the same function. 

`goto` statements can also jump forward.

Statement labels must be associated with a statement. No forward declaration of statement labels is necessary.

There are two primary limitations to jumping:
* You can jump only within the bounds of a single function (you can't jump out of one function and into another).
* If you jump forward, you cannot jump forward over the initialization of any variable that is still in scope at the location being jumed to.

You can jump backwards over a variable initialization, and the variable will be re-initialized when the initialization is executed (unless it is static).

## Avoid using goto

Use of `goto` is shunned in C++ (and other modern high level languages as well). Edsger W. Dijkstra, a noted computer scientist, laid out the case for avoiding `goto` in a famous paper called "Go To Statement Considered Harmful". The primary problem with `goto` is that it allows a programmer to jump around the code arbitrarily. This creates spaghetti code.

As Dijkstra says, "the quality of programmers is a decreasing function of the density of goto statements in the programs they produce".

Almost any code written using a `goto` statement can be more clearly written using other constructs in C++, such as `if statements` and loops. One notable exception is when you need to exit a nested loop but not the entire function -- in such a case, a `goto` to jump beyond the loops is probably the cleanest solution. 

**Best practice**<br/>
_Avoid goto statements (unless the alternatives are significantly worse for code readability)._
