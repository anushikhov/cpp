# Comma and conditional operators

The **comma operator (,)** allows you to evaluate multiple expressions wherever a single expression is allowed. The comma operator evaluates the left operand, then the right operand, and then returns the result of the right operand.

Note that comma has the lowest precedence of all the operators, even lower than assignment. Because of this, the following two lines of code do different things:

` z = (a, b); `  
` z = a, b; `  

This makes the comma operator somewhat dangerous to use.

In almost every case, a statement written using the comma operator would be better written as separate statements.

**Best practice**<br/>
_Avoid using the comma operator, except within for loops._

### Comma as a separator

In C++, the comma symbol is often used as a separator (e.g. multiple variable assignment, function parameters, arguments), and these uses do not invoke the comma operator.

There is no need to avoid separator commas (except when declaring multiple variables, which you should not do).

### The conditional operator

THe **conditional operator (?:)** (also sometimes called the "arithmetic if" operator) is a ternary operator. Because it has historically been C++'s only ternary operator, it's also sometimes referred to as "the ternary operator".

The ?: operator takes the following form:

`(condition) ? expression1 : expression2; `  

If condition evaluates to true, then expression1 is executed, otherwise expression2 is executed.

`if (x > y) `  
&emsp;&emsp;` larger = x; `  
`else `  
&emsp;&emsp;` larger = y; `  

can be written as:

` larger = (x > y) ? x : y; `  

In such uses, the conditional operator can help compact code without losing readability.

### Parenthesization of the conditional operator

It is common convention to put the conditional part of the operation inside the parentheses, both to make it easier to read, and also to make sure the precedence is correct. The other operands evaluate as if they were parenthesized, so explicit parenthesization is not required for those.

The conditional operator has a very low precedence. If doing anything other than assigning the result to a variable, the whole ?: operator also needs to be wrapped in parentheses.

**Best practice**<br/>
_Always parenthesize the conditional part of the conditional operator, and consider parenthesizing the whole thing as well._

### The conditional operator evaluates as an expression

Because the conditional operator operands are expressions rather than statements, the conditional operator can by used in some places where if/else can not.

For example, when initializing a constant variable:

` #include <iostream> `<br/><br/>
` int main() `  
` { `  
&emsp;&emsp;&emsp;` constexpr bool inBigClassroom { false }; `  
&emsp;&emsp;&emsp;` constexpr int classSize { inBigClassroom ? 30 : 20 }; `  
&emsp;&emsp;&emsp;` std::cout << "The class size is: " << classSize << '\n'; `<br/><br/>
&emsp;&emsp;&emsp;` return 0; `  
` } `  

There is no satisfactory if/else statement for this. Much like how variables defined inside functions die at the end of the function, variables defined inside an if or else statement die at the end of the if or else statement.

### The type of the expressions must match or be convertible

**To properly comply with C++'s type checking, either the type of both expressions in a conditional statement must match, or the second expression must be convertible to the type of the first expression.**

The conditional operator gives us a convenient way to compact some if/else statements. It's most useful when we need a conditional initializer (or assignment) for a variable, or to pass a conditional value to a function.

It should not be used for complex if/else statements, as it quickly becomes both unreadable and error prone.

**Best practice**<br/>
_Only use the conditional operator for simple conditionals where you use the result and where it enhances readability._
