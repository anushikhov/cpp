# Arrays

An **array** is an aggregate data type that lets us access many variables of the same type through a single identifier.

Consider the case where you want to record the test scores for 30 students in a class. Without arrays, you would have to allocate 30 almost-identical variables.

` int testScore[30]{}; // allocate 30 integer variables in a fixed array `  

In an array variable declaration, we use square brackets ([]) to tell the compiler both that this is an array variable (instead of a normal variable), as well as how many variables to allocate (called the **array length**).

A **fixed array** (also called a **fixed length array** or **fixed size array**) is an array where the length is known at compile time.

### Array elements and subscripting

Each of the variables in an array is called an **element**. To access individual elements of an array, we use the array name, along with the **subscript operator ([])**, and a parameter called a **subscript** (or **index**) that tells the compiler which element we want. This process is called **subscipting** or **indexing** the array.

For an array of length N, the array elements are numbered 0 through N-1. This is called the array's **range**.

Arrays can be made from any data type. Arrays can even be made from arrays.

### Array subscripts

In C++, array subscripts must always be an integral type. This includes char, short, int, long, long long, etc... and strangely enough bool (where false gives an index of 0 and true gives an index of 1). An array subscript can be a literal value, a variable (constant or non-constant), or an expression that evaluates to an integral type.

### Fixed array declarations

When declaring a fixed array, the length of the array must be a compile-time constant. This is because the length of a fixed array must be known at compile time. Non-const variables or runtime constants cannot be used. Some compilers may allow these kinds of arrays (for C99 compatibility reasons), but they are invalid in C++, and should not be used in C++ programs. If your compiler allows these arrays, you probably forgot to disable compiler extensions.

### A note on dynamic arrays

Because fixed arrays have memory allocated at compile time, that introduces two limitations:

* Fixed arrays cannot have a length based on either user input or some other value calculated at runtime.
* Fixed arrays have a fixed length that can not be changed.

In many cases, these limitations are problematic. C++ supports a second kind of array known as a **dynamic array**. The length of a dynamic array can be set at runtime, and their length can be changed.

Fixed arrays provide an easy way to allocate and use multiple variables of the same type so long as the length of the array is known at compile time.
