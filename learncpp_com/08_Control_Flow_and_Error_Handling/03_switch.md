# switch statement basics

Because testing a variable or expression for equality against a set of different values is common, C++ provides an alternative conditional statement called a **switch statement** that is specialized for this purpose. 

` #include <iostream> `  

` void printDigitName(int x) `  
` { `  
&emsp;&emsp;&emsp;` switch (x) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` case 1: `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << "one"; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` return; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` case 2: `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << "two"; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` return; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` case 3: `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << "three"; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` return; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` default: `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << "unknown"; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` return; `  
&emsp;&emsp;&emsp;` } `  
` } `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` printDigitName(2); `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

Compared to equivalent if statements chain, the switch statement has the advantage of only evaluating the expression once (making it more efficient), and the switch statement also makes it clearer to the reader that it is the same expression being tested for equality in each case.

**Best practice**<br/>
_Prefer switch statements over if-else chains when there is a choice._

The conditional expression can either be a single variable, or any valid expression.

The one restriction is that the condition must evaluate to an integral type or an enumerated type, or by convertable to one. Expressions that evaluate to floating point types, strings, and most other non-integral types may not be used here.

The switch type only allows for integral or enumerated types because it is designed to be highly optimized. Historically, the most common way for compilers to implement switch statements is via jump tables (aka branch tables) -- and jump tables only work with integral values.

A jump table works much like an array, an integral value is used as the array index to "jump" directly to a result. This can be much more efficient than doing a bunch of sequential comparisons.

Compilers don't have to implement switches using jump tables, and sometimes they don't. There is technically no reason that C++ couldn't relax the restriction so that other types could be used as well, they just haven't done so yet as of C++20.

There are two kinds of labels.

## Case labels

The first kind of label is the **case label**, which is declared using the case keyword and followed by a constant expression. The constant expression must either match the type of the condition or must be convertible to the type.

If the value of the conditional expression equals the expression after a case label, execution begins at the first statement after that case label and then continues sequentially.

There is no practical limit to the number of case labels you can have, but all case labels in a switch must be unique.

## The default label

The second kind of label is the **default label** (often called the **default case**), which is declared using the default keyword. If the conditional expression does not match any case label and a default label exists, execution begins at the first statement after the default label.

The default label is optional, and there can only be one default label per switch statement. By convention, the default case is placed last in the switch block.

**Best practice**<br/>
_Place the default case last in the switch block._

## Taking a break  

In the above example, we used `return statement` to stop execution of the statements after our labels. However, this also exits the entire function.

A **break** statement tells the compiler that we are done executing statements within the switch, and that execution should continue with the statement after the end of the switch block. This allows us to exit a switch statement without exiting the entire function.

**Best practice**<br/>
_Each set of statements underneath a label should end in a break statement or a return statement._


