# Pointers and const

We cannot set a non-const pointer to a const variable. A const variable is one whose value cannot be changed. Hypothetically, if we could set a non-const pointer to a const value, then we would be able to perform indirection through the non-const pointer and change the value. That would violate the intention of const.

## Pointer to const value

A **pointer to a const value** is a (non-const) pointer that points to a constant value.

To declare a pointer to a const value, use the const keyword before the data type:

` const int value{ 5 }; `  
` const int* ptr{ &value }; // ptr is a non-const pointer that is pointing to a const int `  
` *ptr = 6; // not allowed, we can't change a const value `  

A pointer to a constant variable can point to a non-constant variable.

` int value{ 5 }; `  
` const int* ptr{ &value }; `  

A pointer to a constant variable treats the variable as constant when it is accessed through the pointer, regardless of whether the variable was initally defined as const or not. Thus, the following is okay:

` int value{ 5 }; `  
` const int* ptr{ &value }; // ptr points to a "const int" `  
` value = 6; // the value is non-const when accessed through a non-const identifier `  

But the following is not: 

` int value{ 5 }; `  
` const int* ptr{ &value }; `  
` *ptr = 6; // ptr treats its value as const, so changing the value through ptr is not legal `  

Because a pointer to a const value is not a const itself (it just points to a const value), the pointer can be redirected to point at other values:  

` int value1{ 5 }; `  
` const int *ptr{ &value1 }; // ptr points to a const int `  

` int value2{ 6 }; `  
` ptr = &value2; // ptr now points at some other const int `  

## const pointers

We can also make a pointer itself constant. A **const pointer** is a pointer whose value can not be changed after initialization.

To declare a const pointer, use the `const` keyword between the asterisk and the pointer name: 

` int value{ 5 }; `  
` int* const ptr{ &value }; `  

Just like a normal const variable, a const pointer must be initialized to a value upon declaration. This means a const pointer will always point to the same address. In the above case, ptr will always point to the address of value(until ptr goes out of scope and is destroyed).

` int value1{ 5 }; `  
` int value2{ 6 }; `  

` int* const ptr{ &value1 }; // the const pointer is initialized to the address of value1 `  
` ptr = &value2; // not okay, once initialized, a const pointer cannot be changed `  

However, because the value being pointed to is still non-const, it is possible to change the value being pointed to indirectly through the const pointer:  

` int value{ 5 }; `  
` int* const ptr{ &value }; // ptr will always point to value `  
` *ptr = 6; // allowed, since ptr points to a non-const int `  

## const pointer to a const value

It is possible to declare a const pointer to a const value by using the `const` keyword both before the type and before the variable name:

` int value{ 5 }; `  
` const  int* const ptr{ &value }; `  

A const pointer to a const value can not be set to point to another address, nor can the value it is pointing to be changed through the pointer.   

...  

* A non-const pointer can be redirected to point to other addresses.  
* A const pointer always points to the same address, and this address can not be changed.  
* A pointer to a non-const value can change the value it is pointing to. These cannot point to a const value.  
* A pointer to a const value treats the value as const (even if it is not), and thus cannot change the value it is pointing to.  

The type of value the pointer points to is always on the far left:

` int value{ 5 }; `  
` const int* ptr1{ &value }; // ptr1 points to a "const int", so this is a pointer to a const value. `  
` int* const ptr2{ &value }; // ptr2 points to an "int", so this is a const pointer to a non-const value. `  
` const int* const ptr3{ &value }; // ptr3 points to a "const int", so this is a const pointer to a const value. `  

...  

Pointers to const values are primarily used in function parameters (e.g., when passing an array to a function) to help ensure the function doesn't inadvertently change the passed in argument. 
