# Introduction to pointers

## The address-of operator (&)

The address-of operator (&) allows us to see what memory address is assigned to a variable.

` #include <iostream> `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` int x{ 5 }; `  
&emsp;&emsp;&emsp;` std::cout << x << '\n'; // print the value of variable x `  
&emsp;&emsp;&emsp;` std::cout << &x << '\n'; // print the memory address of variable x `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

Although the address-of operator looks just like the bitwise-and operator, you can distinguish them because the address-of operator is unary, whereas the bitwise-and operator is binary.


## The indirection operator (*)

The indirection operator (\*) (also called dereference operator) allows us to access the value at a particular address:

` #include <iostream> `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` int x{ 5 }; `  
&emsp;&emsp;&emsp;` std::cout << x << '\n'; // print the value of variable x `  
&emsp;&emsp;&emsp;` std::cout << &x << '\n'; // print the memory address of variable x `  
&emsp;&emsp;&emsp;` std::cout *(&x) << '\n'; // print the value at the memory address of variable x (parethesis not required, but make it easier to read) `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

Although the indirection operator looks just like the multiplication operator, you can distinguish them because the indirection operator is unary, whereas the multiplication operator is binary.


## Pointers

A **pointer** is a variable that holds a memory address as its value.

Pointer variables are declared just like normal variables, only with an asterisk between the data type and the variable name. Note that this asterisk is not an indirection. It is part of the pointer declaration syntax.

` int* iPtr{}; // a pointer to an integer value `  
` double* dPtr{}; // a pointer to a double value `  

` int *iPtr2{}; // also valid syntax `  
` int * iPtr3{}; // also valid syntax (but don't do this, it looks like multiplication) `  

` // When declaring multiple variables in one line, the asterisk has to appear once for every variable `  
` int *iPtr4{}, *iPtr5{}; // declare two pointers to integer varaibles (not recommended) `  

Syntactically, C++ will accept the asterisk next to the data type, next to the variable name, or even in the middle.

**Best practice**<br/>
_When declaring a pointer variable, put the asterisk next to the type to make it easier to distinguish it from an indirection._

Just like normal variables, pointers are not initialized when declared. If not initialized with a value, they will contain garbage.


## Assigning a value to a pointer

Since pointers only hold addresses, when we assign a value to a pointer, that value has to be an address. One of the most common things to do with pointers is have them hold the address of a different variable.

To get the address of a variable, we use the address-of operator:

` int v{ 5 }; `  
` int* ptr{ &v }; // initialize ptr with address of variable v `  

` std::cout << &v; // print the address of variable v `  
` std::cout << ptr; // print the address that ptr is holding `  

The type of the pointer has to match the type of the variable being pointed to. 

The following is also not lega:

` int* ptr{ 5 }; `  

This is because pointers can only hold addresses, and the integer literal 5 does not have a memory address. If you try this, the compiler will tell you it cannot convert an integer to an integer pointer. 

C++ will also not allow you to directly convert literal memory addresses to a pointer:

` double* dPtr{ 0x0012FF7C }; // not okay `  


## The address-of operator returns a pointer

The address-of operator (&) doesn't return the address of its operand as a literal. Instead, it returns a pointer containing the address of the operand, whose type is derived from the argument (e.g. taking the address of an int will return the address in an int pointer).


## Indirection through pointers

Once we have a pointer variable pointing at something, the other common thing to do with it is indirection through the pointer to get  the value of what it's pointing at. Indirection through a pointer evaluates to the contents of the address it is pointing to.

` int value{ 5 }; `  
` std::cout << &value; // prints address of value `  
` std::cout << value; //prints contents of value `  

` int* ptr{ &value }; // ptr points to value `  
` std::cout << ptr; // prints address held in ptr, which is &value `  
` std::cout << *ptr; // indirection through ptr (get the value that ptr is pointing to) `  

This is why pointers must have a type. Without a type, when indirecting through a pointer, the pointer wouldn't know how to interpret the contents it was pointing to. It's also why the type of the pointer and the variable address it's being assigned to must match. If they did not, indirection through the pointer would misinterpret the bits as a different type.

Once assigned, a pointer value can be reassigned to another value:

` int value1{ 5 }; `  
` int value2{ 7 }; `  

` int* ptr{}; `  

` ptr = &value1; // ptr points to value1 `  
` std::cout << *ptr; // prints 5 `  

` ptr = &value2; //ptr points to value2 `  
` std::cout << *ptr; // prints 7 `  

When the address of variable is assigned to `ptr`, the following are true:  

* ptr is the same as &value  
* \*ptr is treated the same as value  

Because \*ptr is treated the same as value, you can assign values to it just as if it were variable value.

` int value{ 5 }; `  
` int* ptr{ &value }; // ptr points to value `  

` *ptr = 7; // *ptr is the same as value, which is assigned 7 `  
` std::cout << value << '\n'; // prints 7 `  

## A warning about indirection through invalid pointers

Pointers in C++ are inherently unsafe. During indirection through a pointer, the application attempts to go to the memory location that is stored in the pointer and retrieve the contents of memory. For security reasons, modern operating systems sandbox applications to prevent them from improperly interacting with other applications, and to protect the stability of the operating system itself. If an application tries to access a memory location not allocated to it by the operating system, the operating system may shut down the application.


## The size of pointers

The size of a pointer is dependent upon the architecture the executable is compiled for -- a 32-bit executable uses 32-bit memory addresses -- consequently, a pointer on a 32-bit machine is 32 bits (4 bytes). With a 64-bit executable, a pointer would be 64 bits (8 bytes). This is true regardless of the size of the object being pointed to.

The size of the pointer is always the same. This is because the pointer is just a memory address, and the number of bits needed to access a memory address on a given machine is always constant.


## What good are pointers?

Pointers are useful in many different cases:

1. Arrays are implemented using pointers. Pointers can be used to iterate through an array (as an alternative to array indices).

1. They are the only way you can dynamically allocate memory in C++. This is by far the most common use case for pointers.

1. They can be used to pass a function as a parameter to another function.

1. They can be used to achieve polymorphism when dealing with inheritance.

1. They can be used to have one struct/class point at another struct/class, to form a chain. This is useful in some data structures, such as linked lists and trees.

...

Pointers are variables that hold a memory address. The value they are pointing to can be accessed using the indirection operator (\*). Indirection through a garbage pointer causes undefined behavior.
