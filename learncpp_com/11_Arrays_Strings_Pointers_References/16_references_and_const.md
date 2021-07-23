# References and const 

## Reference to const value

To declare a reference to a const value, declare a reference using the const keyword.

` const int apples{ 5 }; `  
` const int &ref{ apples }; `  

A reference to a const variable is often called a **const reference** for short, though this does make for some inconsistent nomenclature with pointers.

## Initializing references to const values

Unlike references to non-const values, which can only be initialized with non-const l-values, references to const values can be initialized with non-const l-values, const l-values, and r-values.

Much like a pointer to a const value, a reference to a const value can reference a non-const variable. When accessed through a reference to a const value, the value is considered const even if the original variable is not:

` int apples{ 5 }; `  
` const int& ref{ apples }; // create const reference to variable apples `  

` apples = 6; // okay, apples is non-const `  
` ref = 7; // illegal -- ref is const `  

## References to r-values extend the lifetime of the referenced value

Normally r-values have expression scope, meaning the values are destroyed at the end of the expression in which they are created.

` std::cout << 2 + 3 << '\n'; // 2 + 3 evalues to r-value 5, which is destroyed at the end of this statement `  

However, when a reference to a const value is initialized with an r-value, the lifetime of the r-value is extended to match the lifetime of the reference.

` int somefcn() `  
` { `  
&emsp;&emsp;&emsp;` const int& ref{ 2 + 3 }; // normally the result has expression scope and is destroyed at the endo of this statement `  
&emsp;&emsp;&emsp;` std::cout << ref << '\n'; // the lifetime of the r-value is extended to here, when the const reference dies `  
` } `  

## const references as function parameters

References used as function parameters can also be const. This allows us to access the argument without making a copy of it, while guaranteeing that the function will not change the value being referenced.

` void changeN(const int& ref) `  
` { `  
&emsp;&emsp;&emsp;` ref = 6; // not allowed, ref is const `  
` } `  

References to const values are particularly useful as function parameters because of their versatility. A const reference parameter allows you to pass in a non-const l-value argument, a const l-value argument, a literal, or the result of an expression:  

To avoid making unnecessary, potentially exprensive copies, variables that are not pointers or fundamental data types (int, double, etc...) should be generally passed by (const) reference. Fundamental data types should be passed by value, unless the function needs to change them. There are a few exceptions to this rule, namely types that are so small that it's faster for the CPU to copy them than having to perform an extra indirection for a reference.

References act like pointers. The compiler adds the indirection, which we'd do manually on a pointer using an asterisk, for us.

One of those fast types is `std::string_view`.

If you're uncertain if a non-fundamental type is fast to pass by value, pass it by const reference.

**Best practice**<br/>
_Pass non-pointer, non-fundamental data type variables (such as structs) by (const) reference, unless you know that passing it by value is faster._


