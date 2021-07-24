# Void pointers

The **void pointer**, also known as the generic pointer, is a special type of pointer that can be pointed at objects of any data type. A void pointer is declared like a normal pointer, using the void keyword as the pointer's type:  

`void* ptr; `  

A void pointer can point to objects of any data type:

` int nValue; `  
` float fValue; `  

` struct Something `  
` { `  
&emsp;&emsp;&emsp;` int n; `  
&emsp;&emsp;&emsp;` float f; `  
` }; `  

` Something sValue; `  

` void* ptr; `  
` ptr = &nValue; `  
` ptr = &fValue; `  
` ptr = &sValue; `  

However, because the void pointer does not know what type of object it is pointing to, direct indirection through it is not possible. Rather, the void pointer must first be explicitly cast to another pointer type before indirecting through the new pointer:

` int value{ 5 }; `  
` void* voidPtr { &value }; `  

` // std::cout << *voidPtr << '\n'; // illegal: Indirection through a void pointer `  

` int* intPtr{ static_cast<int*>(voidPtr) }; `  

` std::cout << *intPtr << '\n'; `  

Here's an example of a void pointer in use: 

` #include <iostream> `  
` #include <cassert> `  

` enum class Type `  
` { `  
&emsp;&emsp;&emsp;` tInt, `  
&emsp;&emsp;&emsp;` tFloat, `  
&emsp;&emsp;&emsp;` tCString `  
` }; `  

` void printValue(void* ptr, Type type) `  
` { `  
&emsp;&emsp;&emsp;` switch(type) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` case Type::tInt: `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << *static_cast<int*>(ptr) << '\n'; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` break; `   
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` case Type::tFloat: `   
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << *static_cast<float*>(ptr) << '\n'; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` break; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` case Type::tCString: `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << *static_cast<char*>(ptr) << '\n'; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` break; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` default: `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` assert(false && "type not found"); `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` break; `  
&emsp;&emsp;&emsp;` } `
` } ` 

` int main() `  
` { `  
&emsp;&emsp;&emsp;` int nValue{ 5 }; `  
&emsp;&emsp;&emsp;` float fValue{ 7.5f }; `  
&emsp;&emsp;&emsp;` char szValue[]{ "Mollie" }; `  

&emsp;&emsp;&emsp;` printValue(&nValue, Type::tInt); `  
&emsp;&emsp;&emsp;` printValue(&fValue, Type::tFloat); `  
&emsp;&emsp;&emsp;` printValue(&szValue, Type::tCString); `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

## Void pointer miscellany

Void pointers can be set to a null value:

` void* ptr{ nullptr }; `  

Although some compilers allow deleting a void pointer that points to dynamically allocated memory, doing so should be avoided, as it can result in undefined behavior.

It is not possible to do pointer arithmetic on a void pointer. This is because pointer arithmetic requires the pointer to know what size object it is pointing to, so it can increment or decrement the pointer appropriately.

Note that there is no such thing as a void reference. This is because a void reference would be of type void &, and would not know what type of value it referenced. 

...  

In general it is a good idea to avoid using void pointers unless absolutely necessary as they effectively allow you to avoid type checking. This allows you to inadvertently do things that make no sense, and the compiler won't complain about it. For example, the following would be valid:  

` int nValue{ 5 }; `  
` printValue(&nValue, Type::CSTRING); `  

Although the above function seems like a neat way to make a single function handle multiple data types, C++ actually offers a much better way to do the same thing (via function overloading) that retains type checking to help prevent misuse. Many other places where void pointers would once be used to handle multiple data types are now better done using templates, which also offer strong type checking.

However, very occasionally, you may still find a reasonable use for the void pointer. Just make sure there isn't a better (safer) way to do the same thing using other language mechanisms first.
