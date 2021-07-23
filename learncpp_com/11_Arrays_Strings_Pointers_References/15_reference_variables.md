# Reference variables

Besides normal variables, which hold values directly and pointers, which hold the address of another value (or null) and their value can be retrived through indirection of address they point to, there is also a third basic type of variables that C++ supports - references. A **reference** is a type of C++ variables that acts as an alias to another object or value.

C++ supports three kinds of references:

1. References to non-const values (typically just called "references", or "non-const references").  
1. References to const values (often called "const references").
1. r-value references (added in C++11).

## References to non-const values

A reference (to a non-const value) is declared by using an ampersand (&) between the reference type and the variable name:  

` int value{ 5 }; // normal integer `  
` int &ref{ value }; // reference to variable value `  

In this context, the ampersand does not mean "address of", it means "reference to".

References to non-const values are often just called "references" for short.

Just like the position of the asterisk of pointers, it doesn't matter if you place the ampersand at the type or at the variable name.

` int value{ 5 }; `  
` int& ref1{ value }; `  
` int &ref2{ value }; `  

**Best practice**<br/>
_When declaring a reference variable, put the ampersand next to the type to make it easier to distinguish it from the address-of operator._  


### References as aliases

References generally act identically to the values they're referencing. In this sense, a reference acts as an alias for the object being referenced. For example:  

` int x{ 5 }; `  
` int& y{ x }; `  
` int& z{ y }; `  

Setting or getting the value of x, y, or z will all do the same thing (set or get the value of x). ref and value are treated synonymously.

Using the address-of operator on a reference returns the address of the value being referenced: 

` cout << &value; // e.g. 0012FF7C `  
` cout << &ref; // 0012FF7C `  

ref is acting as an alias for the value.

### l-values and r-values  

In C++, variables are a type of l-value. An **l-value** is a value that has an address (in memory). Since all variables have addresses, all variables are l-values. The name l-value came about because l-values are the only values that can be on the left side of an assignment statement. When we do an assignment, the left hand side of the assignment operator must be an l-value. Consequently, a statement like ` 5 = 6; ` will cause a compile error, because 5 is not an l-value. The value of 5 has no memory, and thus nothing can be assigned to it. 5 is 5 and its value cannot be reassigned. When an l-value has a value assigned to it, the current value at that memory address is overwritten.

The opposite of l-values are r-values. An **r-value** is an expression that is not an l-value. Examples of r-values are literals and non-l-value expressions (such as 2 + x).

On the left side of the assignment you must have something that represents a memory address (such as a variable). Everything on the right side of the assignment will be evaluated to produce a value.

const variables are considered non-modifiable l-values.

### References must be initialized  

References must be initialized when created:  

` int value{ 5 }; `  
` int& ref{ value }; // valid reference, initialized to variable value `  
` int& invalidRef; // invalid, reference, needs to reference something `  

Unlike pointers, which can hold a null value, there is no such thing as a null reference.

References to non-const values can only be initialized with non-const l-values. They can not be initialized with const l-values or r-values.

` int x{ 5 }; `  
` int& ref1{ x }; // okay, x is a non-const l-value `  

` const int y{ 7 }; `  
` int& ref2{ y }; // not okay, y is a const l-value `  

` int& ref3{ 6 }; // not okay, 6 is an r-value `  

You can't initialize a non-const reference with a const object -- otherwise you'd be able to change the value of the const object through the reference, which would violate the const-ness of the object.

### References can not be reassigned  

Once initialized, a reference cannot be changed to reference anothe variable.

` int value1{ 5 }; `  
` int value2{ 6 }; `  

` int& ref{ value1 }; // okay, ref is now an alias for value1 `  
` ref = value2; // assigns 6 (the value of value2) to value1 -- does not change the reference! `  

Instead of changing ref to reference variable value2, the second statement assigns the value of value2 to value1.  

### References as function parameters

References are most often used as function parameters. In this context, the reference parameter acts as an alias for the argument, and no copy of the argument is made into the parameter. This can lead to better performance if the argument is large or expensive to copy.

Passing a pointer argument to a function allows the function to perform indirection through the pointer to modify the argument's value directly. Refernces work similarly in this regard. Because the reference parameter acts as an alias for the argument, a function that uses a reference parameter is able to modify the argument passed in.

When an argument is passed to a function, the function's ref parameter is set as a reference to the argument. This allows the function to change the value of the argument through ref. Note that the argument does not need to be a reference itself. 

**Best practice**<br/>
_Pass arguments by non-const reference (rather than by pointer) when the argument needs to be modified by the function._  

The primary downside of using non-const references as function parameters is that the argument must be a non-const l-value. This can be restrictive.  

### Using references to pass C-style arrays to functions

One of the most annoying issues with C-style arrays is that in most cases they decay to pointers when evaluated. However, if a C-style array is passed by reference, this decaying does not happen.

` #include <iostream> `  
` #include <iterator> `  

` void printElements(int (&arr)[4]) `  
` { `  
&emsp;&emsp;&emsp;` int length{ static_cast<int>(std::size(arr)) }; `  

&emsp;&emsp;&emsp;` for(int i{ 0 }; i < length; ++i) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << arr[i] << '\n'; `  
&emsp;&emsp;&emsp;` } `  
` } `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` int arr[]{ 99, 20, 14, 80 }; `  

&emsp;&emsp;&emsp;` printElements(arr); `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

Note that in order for this to work, you explicitly need to define the array size in the parameter.

### References as shortcuts

A secondary (much less used) use of references is to provide easier access to nested data.

` struct Something `  
` { `  
&emsp;&emsp;&emsp;` int value1; `  
&emsp;&emsp;&emsp;` float value2; `  
` }; `  

` struct Other `  
` { `  
&emsp;&emsp;&emsp;` Something something; `  
&emsp;&emsp;&emsp;` int otherValue; `  
` }; `  

` Other other; `  

If we needed to work with the value1 field of the Something struct of other. Normally, we'd access that member as `other.something.value1`. If there are many separate accesses to this member, the code can become messy. References allow you to more easily access the member:  

` int& ref{ other.something.value1 }; `  

This can help keep your code cleaner and more readable.

### References vs pointers

References and pointers have an interesting relationship -- a reference acts like a pointer that implicitly performs indirection through it when accessed (references are usually implemented internally by the compiler using pointers). Thus given the following:  

` int value{ 5 }; `  
` int* const ptr{ &value }; `  
` int& ref{ value }; `  

\*ptr and ref evaluate identically. As a result, the following two statements produce the same effect:  

` *ptr = 5; `  
` ref = 5; `  

Because references must be initialized to a valid objects (cannot be null) and can not be changed once set, references are generally much safer to use than pointers (since there's no risk of indirection through a null pointer). However, they are also a bit more limited in functionality accordingly.

If a given task can be solved with either a reference or a pointer, the reference should generally be preferred. Pointers should only be used in situations where references are not sufficient (such as dynamically allocating memory).  

...  

References allow us to define aliases to other objects or values. References to non-const values can only be initialized with non-const l-values. References can not be reassigned once initialized.

References are most often used as function parameters when we either want to modify the value of the argument, or when we want to avoid making an expensive copy of the argument.
