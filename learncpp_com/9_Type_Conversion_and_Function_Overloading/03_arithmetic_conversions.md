# Arithmetic conversions

In C++, certain operators require that their operands be of the same type. If one of these operators is invoked with operands of different types, one or both of the operands will be implicitly converted to matching types using a set of rules called the **usual arithmetics conversions**.

## The operators that require operands of the same type

The following operators require their operands to be of the same type:

* The binary arithmetic operators: +, -, \*, /, %
* The binary relational operators: <, >, <=, >=, ==, !=
* The binary bitwise arithmetic operators: &, ^, |
* The conditional operator ?: (excluding the condition, which is expected to be of type `bool`)

## The usual arithmetic conversion rules

The compiler has a prioritized list of types that looks something like this:

* long double (highest)
* double
* float
* unsigned long long
* long long
* unsigned long
* long
* unsigned int
* int (lowest)

There are two rules:

* If the type of at least one of the operands is on the priority list, the operand with lower priority is converted to the type of the operand with higher priority
* Othewise (the type of neither operand is on the list), both operands are numerically promoted

` #include <iostream> `  
` #include <typeinfo> // for typeid() `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` int i{ 2 }; `  
&emsp;&emsp;&emsp;` double d{ 3.5 }; `  
&emsp;&emsp;&emsp;` std::cout << typeid(i + d).name() << ' ' << i + d << '\n'; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

The `double` operand has the highest priority, so the lower priority operand (of type `int`) is type converted to `double` value `2.0`. Then `double` value `2.0` and `3.5` are added to produce `double` result `5.5`.

The output of `typeid.name()` can vary depending on the compiler used.

` #include <iostream> `  
` #include <typeinfo> `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` short a{ 4 }; `  
&emsp;&emsp;&emsp;` short b{ b }; `  
&emsp;&emsp;&emsp;` std::cout << typeid(a + b).name() << ' ' << a + b << '\n'; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

Because neither operand appears on the priority list, both operands undergo integral promotion to type `int`.

### Signed and unsigned issues

The prioritization hierarchy can cause some problematic issues when mixing signed and unsigned values:

` #include <iostream> `  
` #include <typeinfo> `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` std::cout << typeid(5u-10).name() << ' ' << 5u - 10; `  

&emsp;&emsp;&emsp;` std::cout << std::boolalpha << (-3 < 5u); `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

This is one of the primary reasons to avoid unsigned integers -- when you mix them with signed integers in arithmetic expressions, you're at risk for unexpected results. And the compiler probably won't even issue a warning.
