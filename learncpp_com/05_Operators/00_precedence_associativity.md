# Operator precedence and associativity

In Mathematics, an operation is a mathematical calculation involving zero or more input values (called operands) that produces a new value (called an output value). The specific operation to be performed is denoted by a construct (typically a symbol or pair of symbols) called an operator.

The order in which operators are evaluated in a compound expression is determined by an operator's **precedence**.

In C++, when the compiler encounters an expression, it must similarly analyze the expression and determine how it should be evaluated. To assist with this, all operators are assigned a level of precedence. Operators with the highest level of precedence are evaluated first.

If two operators with the same precedence level are adjacent to each other in an expression, the operator's **associativity** tells the compiler whether to evaluate the operators from left to right or from right to left.

C++ doesn't include an operator to do exponentiation (operator^ has a different function in C++).

**Best practice**
_Use parentheses to make it clear how an expression should evaluate, even if they are technically unnecessary._
