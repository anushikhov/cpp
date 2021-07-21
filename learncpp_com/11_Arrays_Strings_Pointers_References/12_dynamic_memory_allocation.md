# Dynamic memory allocation with new and delete

## The need for dynamic memory allocation

C++ supports three basic types of memory allocation:

* **Static memory allocation** happens for static and global variables. Memory for these types of variables is allocated once when your program is run and persists throughout the life of your program.  
* **Automatic memory allocation** happens for function parameters and local variables. Memory for these types of variables is allocated when the relevant block is entered, and freed when the block is exited, as many times as necessary.  
* **Dynamic memory allocation**  

Both static and automatic allocation have two things in common:

* The size of the variable/array must be known at compile time.
* Memory allocation and deallocation happens automatically (when the variable is instantiated/destroyed.

You may come across situations where one or both of these constraints cause problems, usually when dealing with external (user or file) input.

**Dynamic memory allocation** is a way for running programs to request memory from the operating system when needed. This memory does not come from the program's limited stack memory -- instead, it is allocated from a much larger pool of memory managed by the operating system called the **heap**.

## Dynamically allocating single variables

To allocate a single variable dynamically, we use the scalar (non-array) form of the **new** operator:

` new int; // dynamically allocate an integer (and discard the result) `  

We're requesting an integer's worth of memory from the operating system. The `new` operator creates the object using that memory, and then returns a pointer containing the address of the memory that has been allocated.

Most often, we'll assign the return value to our own pointer variable so we can access the allocated memory later.

` int* ptr{ new int }; // dynamically allocate an integer and assign the address to ptr so we can access it later `  

We can then perform indirection through the pointer to access the memory:

`\*ptr = 7; // assign value 7 to the allocated memory `  

Without a pointer to hold the address of the memory the allocated memory, we'd have no way to access it.


## How does dynamic memory allocation work?

Computers have memory that is available for applications to use. When an application is run, the OS loads it into some of that memory. The memory used by the application is divided into different areas. One area contains the application code, another area is used for normal operations (keeping track of which functions were called, creating and destroying global and local variables, etc...). However, much of the memory available just sits there, waiting to be handed out to programs that request it.

When you dynamically allocate memory, you're asking the OS to reserve some of that memory for your program's use. If it can fulfill the request, it will return the address of that memory to your application. From that point forward your application can use this memory as it wishes. When your application is done with the memory, it can return the memory back to the operating system to be given to another program.

Unlike static or automatic memory, the program itself is responsible for requesting and disposing of dynamically allocated memory.

## Initializing a dynamically allocated variable 

When you dynamically allocate a variable, you can also initialize it via direct initialization or uniform initialization (in C++11):

` int* ptr1{ new int( 5 ) }; `  
` int* ptr2{ new int{ 6 } }; `  

## Deleting single variables

When we are done with a dynamically allocated variable, we need to explicitly tell C++ to free the memory for reuse. For single variables, this is done via the scalar (non-array) form of the **delete** operator:

` delete ptr; // return the memory pointed to by ptr to the operating system `  
` ptr = 0; // set ptr to be a null pointer (use nullptr instead of 0 in C++) `  

## What does it mean to delete memory?

The delete operator simply returns the memory being pointed to back to the operating system. The OS is then free to reassign that memory to another application (or to this application again later).

Although it looks like we're deleting a variable, this is not the case. The pointer variable still has the same scope as before, and can be assigned a new value just like any other variable.

Note that deleting a pointer that is not pointing to dynamically allocated memory may cause bad thing to happen.

## Dangling pointers

C++ does not make any guarantees about what will happen to the contents of deallocated memory, or to the value of the pointer being deleted. In most cases, the memory returned to the OS will contain the same values it had before it was returned, and the pointer will be left pointing to the now deallocated memory.

A pointer that is pointing to deallocated memory is called a **dangling pointer**. Indirection through- or deleting a dangling pointer will lead to undefined behavior. 

` #include <iostream> `  

` int main() ` 
` { ` 
&emsp;&emsp;&emsp;` int* ptr{ new int }; `  
&emsp;&emsp;&emsp;` *ptr = 7; `  

&emsp;&emsp;&emsp;` delete ptr; // ptr is now a dangling pointer `  

&emsp;&emsp;&emsp;` std::cout << *ptr; // indirection through a dangling pointer will cause undefined behavior `  

&emsp;&emsp;&emsp;` delete ptr; // trying to deallocate the memory again will also lead to undefined behavior `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

The value of 7 that was assigned to the allocated memory will probably still be there, but it's possible that the value at that memory address could have changed. It's also possible the memory could be allocated to another application (or for the operating system's own usage), and trying to access that memory will cause the OS to shut the program down.

Deallocating memory may create multiple dangling pointers.

` #includ <iostream> `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` int* ptr{ new int{} }; // dynamically allocate an integer `  
&emsp;&emsp;&emsp;` int* otherPtr{ ptr }; // otherPtr is now pointed at the same memory location `  

&emsp;&emsp;&emsp;` delete ptr; // return the memory to the operating system. ptr and otherPtr are now dangling pointers `  

&emsp;&emsp;&emsp;` ptr = nullptr; // ptr is now a nullptr `  

&emsp;&emsp;&emsp;` // however, otherPtr is still a dangling pointer `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

Try to avoid having multiple pointers point at the same piece of dynamic memory. If this is not possible, be clear about which pointer "owns" the memory (and is responsible for deleting it) and which pointers are just accessing it. 

When you delete a pointer, if that pointer is not going out of scope immediately afterward, set the pointer to 0 (or nullptr in C++11).

**Best practice**<br/>
_Set deleted pointer to 0 (or nullptr in C++11) unless they are going out of scope immediately afterward._   

## Operator new can fail

When requesting memory from the operating system, in rare circumstances, the operating system may not have any memory to grant the request with.

By default, if `new` fails, a `bad_alloc` exception is thrown. If the exception isn't properly handled, the program will simply terminate with an unhandled exception error.

In many cases, having `new` throw an exception (or having your program crash) is undesirable, so there's an alternate form of `new` that can be used instead to tell `new` to return a null pointer if memory can't be allocated. This is done by addint the constant `std::nothrow` between the `new` keyword and the allocation type:

` int* value{ new (std::nothrow) int }; `  

If `new` fails to allocate memory, it will return a null pointer instead of the address of the allocated memory. 

Note that if you then attempt indirection through this pointer, undefined behavior will result (most likely, your program will crash). Consequently, the best practice is to check all memory requests to ensure they actually succeeded before using the allocated memory.

` int* value { new (std::nothrow) int{} }; // ask for integer's worth of memory `  
` if (!value) // handle case where new returned null `  
` { `  
&emsp;&emsp;&emsp;` // Do error handling here `  
&emsp;&emsp;&emsp;` std::cout << "Could not allocate memory\n"; `  
` } `  

Because asking `new` for memory only fails rarely (and almost never in a dev environment), it's common to forget to do this check!

## Null pointers and dynamic memory allocation

Null pointers (pointers set to address 0 or nullptr) are particularly useful when dealing with dynamic memory allocation. In the context of dynamic memory allocation, a null pointer basically says "no memory has been allocated to this pointer". This allows us to do things like conditionally allocate memory:

` // If ptr isn't already allocated, allocate it `  
` if(!ptr) `  
&emsp;&emsp;&emsp;` ptr = new int; `  

Deleting a null pointer has no effect. You can just write:

` delete ptr; `  

If `ptr` is not-null, the dynamically allocated variable will be deleted. If it is null, nothing will happen.

## Memory leaks

Dynamically allocated memory stays allocated until it is explicitly deallocated or until the program ends (and the operating system cleans it up, assuming your operating system does that). However, the pointers used to hold dynamically allocated memory addresses follow the normal scoping rules for local variables. This mismatch can create interesting problems. Consider the following function: 

` void doSomething() `  
` { `  
&emsp;&emsp;&emsp;` int* ptr{ new int{} }; `  
` }
This function allocates an integer dynamically, but never frees it using `delete`. Because pointer variables are just normal variables, when the function ends, `ptr` will go out of scope. And  because `ptr` is the only variable holding the address of the dynamically allocated integer, when `ptr` is destroyed there are no more references to the dynamically allocated memory. This means the program has now "lost" the address of the dynamically allocated memory. As a result, this dynamically allocated integer can not be deleted.

This is called a **memory leak**. Memory leaks happen when your program loses the address of some bit of dynamically allocated memory before giving it back to the operating system. When this happens, your program can't delete the dynamically allocated memory, because it no longer knows where it is. The operating system also can't use this memory, because that memory is considered to be still in use by your program.

Memory leaks eat up free memory while the program is running, making less memory available not only to this program, but to other programs as well. Programs with severe memory leak problems can eat all the availble memory, causing the entire machine to run slowly or even crash. Only after your program terminates is the operating system able to clean up and "reclaim" all leaked memory.

Although memory leaks can result from a pointer going out of scope, there are other way that memory leaks can result. For example, a memory leak can occur if a pointer holding the address of the dynamically allocated memory is assigned another value: 

` int value{ 5 }; `  
` int\* ptr{ new int{} }; // allocate memory `  
` ptr = &value; // old address lost, memoory leak results `  

This can be fixed by deleting the pointer before reassinging it:  

` int value{ 5 }; `  
` int\* ptr{ new int{} }; `  
` delete ptr; `  
` ptr = &value; `  

Relatedly, it is also possible to get a memory leak via double-allocation: 

` int\* ptr{ new int{} }; `  
` ptr = new int{}; // old address lost, memory leak results `  

The address returned from the second allocation overwrites the address of the first allocation. Consequently, the first allocation becomes a memory leak.

Similarly, this can be avoided by ensuring you delete the pointer before reassigning.

...  

Operators `new` and `delete` allow us to dynamically allocate single variables for our programs.

Dynamically allocated memory has dynamica duration and will stay allocated until you deallocate it or the program terminates.

Be careful not to perform indirection through dangling or null pointers.
