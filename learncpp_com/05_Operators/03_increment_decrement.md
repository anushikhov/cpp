# Increment/decrement operators, and side effects

In the case of prefix increment/decrement operators, first the operand is incremented or decremented, and then the expression evaluates to the value of the operand.

In the case of postfix increment/decrement operators, first, a copy of the operand is made, then the operand is incremented or decremented. Finally, the copy is evaluated.

**Note that the postfix version takes a lot more steps, and thus may not be as performant as the prefix version.**

**Best practice**<br/>
_Strongly favor the prefix version of the increment and decrement operators, as they are generally more performant, and you're less likely to run into strange issues with them._

### Side effects

A function or expression is said to have a **side effect** if it does anything that persists beyond the life of the function or expression itself.

Common examples of side effects include changing the value of objects, doing input and output, or updating a graphical user interface (e.g. enabling or disabling a button).

Most of the time, side effects are useful, however, side effects can also lead to unexpected results.

` int add(int x, int y) `  
` { `  
&emsp;&emsp;&emsp;` return x + y; `  
` } `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` int x{5}; `  
&emsp;&emsp;&emsp;` int value = add(x, ++x); // is this 5 + 6, or 6 + 6 ? `  

&emsp;&emsp;&emsp;` std::cout << value; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

C++ does not define the order in which function arguments are evaluated. 

There are often cases where C++ does not specify the order in which certain things are evaluated (such as operator operands), so different compilers may exhibit different behaviors. Even when C++ does make it clear how things should be evaluated, historically this has been an area where there have been many compiler bugs. These problems can generally all be avoided by ensuring that any variable that has a side-effect applied is used no more than once in a given statement.

**C++ does not define the order of evaluation for function arguments or operator operands.**

**Don't use a variable that has a side effect applied to it more than once in a given statement. If you do, the result may be undefined.**
