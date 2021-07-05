# Logical operators

Logical operators provide us with the capability to test multiple conditions.

C++ has 3 logical operators: logical NOT (!), logical AND (&&), logical OR (||).


## Logical NOT 

Logical NOT flips a Boolean value from true to fale, and vice versa.

Logical NOT has a very high precedence.

**Best practice**<br/>
_If logical NOT is intended to operate on the result of other operators, the other operators and their operands need to be enclosed in parentheses._

Simple uses of logical NOT, such as ` if (!value) ` do not need parentheses because precedence does not come into play.


## Logical OR

The logical OR operator is used to test whether either of two conditions is true.


## Logical AND

The logical AND operator is used to test whether both operands are true.

You can string together many logical OR and logical AND statements.


## Short circuit evaluation

In order for logical AND to return true, both operands must evaluate to true. If the first operand evaluates to false, _logical AND_ knows it must return false regardless of whether the second operand evaluates to true or false. In this case, the logical AND operator will go ahead and return false immediately without even evaluating the second operand. This is known as **short circuit evaluation**, and is done primarily for optimization purposes.

Similarly, if the first operand for logical OR is true, then the entire OR condition has to evaluate to true, and the second operand won't be evaluated.

Short circuit evaluation presents another opportunity to show why operators that cause side effects should not be used in compound expressions. Consider the following snippet:

` if (x == 1 && ++y == 2) `  
&emsp;` // do something `  

If x does not equal 1, the whole condition must be false, so ++y never gets evaluated.

**Short circuit evaluation may cause Logical OR and Logical AND to not evaluate one operand. Avoid using expressions with side effects in conjunction with these operators.**

**Best practice**<br/>
_When mixing logical AND and logical OR in a single expression, explicitly parenthesize each operation to ensure they evaluate how you intend._


## De Morgan's law

De Morgan's low tells us how the logical NOT should be distributed:

**!(x && y) is equivalent to !x || !y**<br/>
**!(x || y) is equivalent to !x && !y**<br/>

In other words, when you distribute the logical NOT, you also need to flip logical AND to logical OR, and vice versa.

This can sometimes be useful when trying to make complex expressions easier to read.


### Logical exclusive or (XOR)

Logical XOR is a logical operator provided in some languages that is used to test whether an odd number of conditions is true.

C++ doesn't provide a logical XOR operator. Unlike logical OR or logical AND, logical XOR cannot be short circuit evaluated. Because of this, making a logical XOR operator out of logical OR and logical AND operators is challenging. However you can easily mimic logical XOR using inequality operator (!=):

` if (a != b) ... // a XOR b, assuming a and b are Bolleans `  

This can be extended to multiple operands as follows:  

` if (a != b != c != d) ... // a XOR b XOR c XOR d, assuming a, b, c, and d are Booleans `  

The above XOR patterns only work if the operands are Booleans (not integers). If you need a form of logical XOR that works with non-Boolean operands, you can static_cast them to bool:

` if (static_cast<bool>(a) != static_cast<bool>(b) != static_cast<bool>(c) != static_cast<bool>(d)) ... `

