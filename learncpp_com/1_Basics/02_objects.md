# Introduction to objects and variables

Programs produce results by manipulating (reading, changing, and writing) data. 

Data is any information that can be moved, processed, or stored by a computer.

**Programs are collections of insturctions that manipulate data to produce a desired result.**

A program can acquire data to work with in many ways: from a file or database, over a network, from the user providing input on a keyboard, or from the programmer putting data directly into the source code of the program itself.

Data on a computer is typically stored in a format (binary) that is efficient for storage or processing (and is thus not human readable).

**R**andom **A**ccess **M**emory is available for programs to use.

A single piece of data, stored in memory somewhere, is called a **value**.

In some older programming languages you could directly access memory addresses.

**In C++ direct memory access is not allowed.**

Instead, memory is accessed indirectly through an object. 

An **object** is a region of storage (usually memory) that has a value and other associated properties.

Objects can be named or unnamed (anonymous). A named object is called a **variable**, and the name of the object is called an **identifier**.

_In general programming, the term object typically refers to a variable, data structure in memory, or function. In C++, the term object has a narrower definition that excludes functions._

In order to create a variable, we use a special kind of declaration statement called a **definition**.

`int x; // define a variable named x, of type int`

When the program is run (called **runtime**), the variable will be instantiated. **Instantiation** means the object will be created and assigned a memory address. Variables must be instantiated before they can be used to store values. An instantiated object is sometimes also called in **instance**.

A **data type** tells the compiler what type of value the variable will store.

In C++, the type of a variable must be known at **compile-time**, and that type cannot be changed without recompiling the program.

C++ also allows you to create your own user-defined types.


## Defining multiple variables

` int a;
  int b;
`

` int a, b;`

` int a;
  double b;
`

` int a; double b;`

**Best practice**
_Avoid defining multiple variables in a single statement._

In C++, we use variables to access memory. Variables have an identifier, a type, and a value (and some other attributes). A variable's type is used to determine how the value in memory should be interpreted.

* **Data** is any information that can be moved, processed, or stored by a computer.
* A **value** is a single piece of data stored in memory.
* A **variable** is a named region of memory.
* An **identifier** is the name that a variable is accessed by.
* A **type** tells the program how to interpret a value in memory.

