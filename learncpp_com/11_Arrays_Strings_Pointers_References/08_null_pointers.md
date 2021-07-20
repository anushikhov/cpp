# Null pointers

## Null values and null pointers

Just like normal variables, pointers are not initialized when they are instantiated. Unless a value is assigned, a pointer will point to some garbage address by default.

Besides memory addresses, there is one additional value that a pointer can hold: a null value. A **null value** is a special value that means the pointer is not pointing at anything. A pointer holding a null value is called a **null pointer**.

In C++, we can assign a pointer a null value, by initializing or assigning it the literal 0:

` float* ptr { 0 }; // ptr is now a null pointer `  
` float* ptr2; // ptr2 is uninitialized `  
` ptr2 = 0; // ptr2 is now a null pointer `  

Pointers converto to Boolean false if they are null, and boolean true if they are non-null. Therefore, we can use a conditional to test whether a pointer is null or not.

**Best practice**<br/>
_Initialize your pointers to a null value if you're not giving them another value._  

Indirection through a garbage pointer would lead to undefined results. Indirection through a null pointer also results in undefined behavior. In most cases, it will crash your application. 

Conceptually, this makes sense. Indirection through a pointer means "go to the address the pointer is pointing at and access the value there". A null pointer doesn't have an address.

## The NULL macro

In C++, there is a special preprocessor macro called NULL (defined in the <cstddef> header). This macro was inherited from C, where it is commonly used to indicate a null pointer.

` #include <cstddef> // for NULL `  
` double* ptr { NULL }; // ptr is a null pointer `  

The value of NULL is implementation defined, but is usually defined as the integer constant 0. As of C++11, NULL can be defined as nullptr instead.

**Best practice**<br/>
_Because NULL is a preprocessor macro with an implementation defined value, avoid using NULL._

## The perils of using 0 (or NULL) for null pointers

The value of 0 isn't a pointer type, so assinging 0 (or NULL, pre-C++11) to a pointer to denote that the pointer is a null pointer is a little inconsistent. In rare cases, when used as a literal argument, it can even cause problems because the compiler can't tell whether we mean a null pointer or the integer 0:

` #include <iostream> `  
` #include <cstddef> `  

` void print(int x) `  
` { `   
&emsp;&emsp;&emsp;` std::cout << "print(int: " << x << '\n'; `  
` } `  

` void pirnt(int* x) `  
` { `  
&emsp;&emsp;&emsp;` if(!x) `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << "print(int*): null\n"; `  
&emsp;&emsp;&emsp;` else `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << "print(int*): " << *x << '\n'; `  
` } `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` int* x { NULL }; `  
&emsp;&emsp;&emsp;` print(x); // calls print(int*) because x has type int* `  
&emsp;&emsp;&emsp;` print(0); // calls print(int) because 0 is an integer literal `  
&emsp;&emsp;&emsp;` print(NULL); // likely calls print(int), although we probably wanter print(int*) `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

In the likely case where NULL is defined as value 0, print(NULL) will call print(int), not print(int\*) like you might expect for a null pointer literal.

## nullptr in C++11

To address the above issues, C++11 introduces a new keyword called **nullptr**. nullptr is a keyword, much like the Boolean keywords true and false are.

Starting with C++11, this should be favored instead of 0 when we want a null pointer:

` int* ptr { nullptr }; // ptr is still an integer pointer, just set to a null value `  

C++ will implicitly convert nullptr to any pointer type. So in the above example, nullptr is implicitly converted to an integer pointer, and then the value of nullptr assigned to ptr. This has the effect of making integer pointer ptr a null pointer.

We can also call a function with a nullptr literal, which will match to any parameter that takes a pointer value.

**Best practice**<br/>
_Use nullptr to initialize your pointers to a null value._  

## std::nullptr_t

C++11 also introduces a new type called `std::nullptr_t` (in header <cstddef>). `std::nullptr_t` can only hold one value: nullptr. If we want to write a function that accepts only a `nullptr` argument, we set the parameters to the `std::nullptr_t` type.

` #include <iostream> `  
` #include <cstddef> `  

` void doSomething(std::nullptr_t ptr) `  
` { `  
&emsp;&emsp;&emsp;` std::cout << "in doSomething()\n"; `  
` } `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` doSomething(nullptr); // call doSomething with an argument of type std::nulllptr_t `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  
