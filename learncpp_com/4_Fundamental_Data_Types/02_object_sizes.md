# Object sizes and the sizeof operator

An object can take up more than 1 byte of memory. A single object may use 2, 4, 8 or even more consecutive memory addresses.

**The amount of memory that an object uses is based on its data type.**

Because we typically access memory through variable names (and not directly via memory addresses), the compiler is able to hide the details of how many bytes a given object uses from use. When we access some variable x, the compiler knows how many bytes of data to retrieve (based on the type of variable x), and can handle that task for us.

The more memory an object uses, the more information it can hold.

A single bit can hold 2 possible values, a 0, or a 1. 2 bits can hold 4 possible values. 3 bits can hold 8 possible values. 

To generalize, an object with _n_ bits (where n is an integer) can hold 2^n unique values. Therefore, with an 8-bit byte, a byte-sized object can hold 2^8 (256) different values. An object that uses 2 bytes can hold 2^16 (65,536) different values.

Computers have a finite amount of free memory. Every time we define an object, a small portion of that free memory is used for as long as the object is in existence. Because modern computers have a lot of memory, this impace is usually negligible. However, for programs that need a large amount of object or data (e.g. a game that is rendering millions of polygons), the difference between using 1 byte and 8 byte objects can be significant.

**Best practice**
_Focus on writing maintainable code, and optimize only when and where the benefit will be substantive._


## Fundamental data type sizes

**The size of a given data type is dependent on the compiler and/or the computer architecture.**

**C++ only guarantees that each fundamental data type will have a minimum size.**

![Data type minimum sizes](https://raw.githubusercontent.com/anushikhov/cpp/main/4_Fundamental_Data_Types/img/data_type_min_sizes.png)  


**Best practice**
_For maximum compatibility, you shouldn't assume that variables are larger than the specified minimum size._

Objects of fundamental data types are generally extremely fast.


## The sizeof operator

In order to determine the size of data types on a particular machine, C++ provides an operator named **sizeof**. The _sizeof_ operator is a unary operator that takes either a type or a variable, and returns its size in bytes. 

` std::cout << "bool:\t\t" << sizeof(bool) << " bytes\n"; `  
` std::cout << "x is " << sizeof(x) << " bytes\n";`  

You cannot use the _sizeof_ operator on the _void_ type, since it has no size (doing so will cause a compile error).

### Fundamental data type performance

On modern machines, objects of the fundamental data types are fast, so performance while using these types should generally not be a concern.

You might assume that types that use less memory would be faster than types that use more memory. This is not always true. CPUs are often optimized to process data of a certain size (e.g. 32 bits), and types that match that size may be processed quicker. On such a machine, a 32-bit _int_ could be faster than a 16-bit _short_ or an 8-bit _char_.

