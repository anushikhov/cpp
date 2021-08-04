# The stack and the heap

The memory that a program uses is typically divided into a few different areas, called segments:

* The code segment (also called a text segment), where the compiled program sits in memory. The code segment is typically read-only.  
* The bss (block started by symbol) segment (also called the uninitialized data segment), where zero-initialized global and static variables are stored.
* The data segment (also called the initialized data segment), where initialized global and static variables are stored.  
* The heap, where dynamically allocated variables are allocated from.  
* The call stack, where function parameters, local variables, and other function-related information are stored.  

## The heap segment 

The heap segment (also known as the "free store") keeps track of memory used for dynamic memory allocation. 

In C++, when you use the `new` operator to allocate memory, this memory is allocated in the application's heap segment.

` int ptr* = new int; // ptr is assigned 4 bytes in the heap `  
` int *array = new int[10]; // array is assigned 40 bytes in the heap `  

The address of this memory is passed back by operator `new`, and can then be stored in a pointer. You do not have to worry about the mechanics behind the process of how free memory is located and allocated to the user. However, it is worth knowing that sequential memory requests may not result in sequential memory addresses being allocated.

` int *ptr1 = new int; `  
` int *ptr2 = new int; `  
` // ptr1 and ptr2 may not have sequential addresses `  

When a dynamically allocated variable is deleted, the memory is "returned" to the heap and can then be reassigned as future allocation requests are received. **Deleting a pointer does not delete the variable, it just returns the memoery at the associated address back to the operating system.**  

The heap has advantages and disadvantages:  

* Allocating memory on the heap is comparatively slow.  
* Allocated memory stays allocated until it is specifically deallocated (beware memory leaks) or the application ends (at which point the OS should clean it up).  
* Dynamically allocated memory must be accessed through a pointer. Dereferencing a pointer is slower than accessing a variable directly.  
* Because the heap is a big pool of memory, large arrays, structures, or classes can be allocated here.  

## The call stack  

The **call stack** (usually referred to as "the stack") has a much more interesting role to play. The call stack keeps track of all the active functions (those that have been called but have not yet terminated) from the start of the program to the current point of execution, and handles allocation of all function parameters and local variables.

The call stack is implemented as a stack data structure.

## The stack data structure

A **data structure** is a programming mechanism for organizing data so that it can be used efficiently. Arrays and structs are examples of data structures and both provide mechanisms for storing data and accessing that data in an efficient way. There are many additional data structures that are commonly used in programming, quite a few of which are implemented in the standard library, and a stack is one of those.

Consider a stack of plates in a cafeteria. Because each plate is heavy and they are stacked, you can really only do one of three things:

1. Look at the surface of the top plate  
1. Take the top plate off the stack (exposing the one underneath, if it exists)  
1. Put a new plate on top of the stack (hiding the one underneath, if it exists)  

In computer programming, a stack is a container data structure that holds multiple variables (much like an array). However, whereas an array lets you access and modify elements in any order you wish (called **random access**), a stack is more limited. The operations that can be performed on a stack correspond to the three things mentioned above:  
1. Look at the top item on the stack (usually done via a function called `top()`, but sometimes called `peek()`)  
1. Take the top item off of the stack (done via a function called `pop()`)  
1. Put a new item on top of the stack (done via a function called `push()`)  

A stack is a last-in, first-out (LIFO) structure. The last item pushed onto the stack will be the first item popped off. If you put a new plate on top of the stack, the first plate removed from the stack will be the plate you just pushed on last. Last on, first off. As items are pushed onto a stack, the stack grows larger -- as items are popped off, the stack grows smaller.

## The call stack segment

The call stack segment holds the memory used for the call stack. When the application starts, the `main()` function is pushed on the call stack by the operating system. Then the program begins executing.

When a function call is encountered, the function is pushed onto the call stack. When the current function ends, that function is popped off the call stack. Thus, by looking at the functions pushed on the call stack, we can see all of the functions that were called to get to the current point of execution.

The stack itself is a fixed-size chunk of memory addresses. The "items" we are pushing and popping on the stack are called **stack frames**. A stack frame keeps track of all of the data associated with one function call. A register (a small piece of memory in the CPU) known as the stack pointer (sometimes abbreviated "SP"), keeps track of where the top of the call stack currently is.

When we pop an item off the call stack, we only have to move the stack pointer down -- we don't have to clean up or zero the memory used by the popped stack framel This memory is no longer considered to be "on the stack" (the stack pointer will be at or below the address), so it won't be accessed. If we later push a new stack frame to this memory, it will overwrite the old value we never cleaned up.

## The call stack in action

Here is the sequence of steps that takes place when a function is called:

1. The program encounters a function call.  
1. A stack frame is constructed and pushed on the stack. The stack frame consists of:  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; * The address of the instruction beyond the function call (called the **return address**).  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;This is how the CPU remembers where to return to after the called function exits.   
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; * All function arguments.  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; * Memory for any local variables.  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; * Saved copies of any registers modified by the function that need to be restored when the function returns.  
1. The CPU jumps to the function's start point.  
1. The instructions inside of the function begin executing.  

When the function terminates, the following steps happen:

1. Registers are restored from the call stack  
1. The stack frame is popped off the stack. This frees the memory for all local variables and arguments.  
1. The return value is handled.  
1. The CPU resumes execution at the return address.  

Return values can be handled in a number of different ways, depending on the computer's architecture. Some architectures include the return value as part of the stack frame. Others use CPU registers.

On some architectures, the call stack grows away from memory address 0. On others, it grows towards memory address 0. As a consequence, newly pushed stack frames may have a higher or a lower memory address than the previous ones.

## Stack overflow  

The stack has a limited size, and consequently can only hold a limited amount of information. On Windows, the default stack size is 1MB. On some Unix machines, it can be as large as 8MB. If the program tries to put too much information on the stack, stack overflow will result. **Stack overflow** happens when all the memory in the stack has been allocated -- in that case, further allocations begin overflowing into other sections of memory. 

Stack overflow is generally the result of allocating too many variables on the stack, and/or making too many nested function calls. On modern operating systems, overflowing the stack will generally cause your OS to issue an access violation and terminate the program.

The stack has advantages and disadvantages:

* Allocating memory on the stack is comparatively fast.  
* Memory allocated on the stack stays in scope as long as it is on the stack. It is destroyed when it is popped off the stack.  
* All memory allocated on the stack is known at compile time. Consequently, this memory can be accessed directly through a variable.  
* Because the stack is relatively small, it is generally not a good idea to do anything that eats up lots of stack space. This includes passing by value or creating local variables of large arrays or other memory-intensive structures.
