# Introduction to fundamental data types

## Bits, bytes, and memory addressing

The smallest unit of memory is a **binary digit** (also called **bit**), which can hold a value of 0 or 1. 

Memory is organized into sequential units called **memory addresses** (or **addresses** for short). The memory address allows us to find and access the contents of memory at a particular location.

In modern computer architectures, each bit does not get its own unique memory address. This is because the number of memory addresses are limited, and the need to access data bit-by-bit is rare. Instead, each memory address holds 1 byte of data. A **byte** is a group of bits that are operated on as a unit. The modern standard is that a byte is comprised of 8 sequential bits.

**In C++, we typically work with "byte-sized" chunks of data.**

Some older or non-standard machines may have bytes of a different size (from 1 to 48 bits) -- however, we generally need not worry about these, as the modern de-facto standard is that a byte is 8 bits.

### Data types

Because all data on a computer is just sequence of bits, we use a **data type** (often called a "type" for short) to tell the compiler how to interpret the contents of memory in some meaningful way. 

When you give an object a value, the compiler and CPU take care of encoding your value into the appropriate sequence of bits for that data type, which are then stored in memory.

### Fundamental data types

C++ comes with built-in support for many different data types. These are called **fundamental data type**, but are often informally called **basic types**, **primitive types**, or **built-in types**.

Here is a list of the fundamental data types:
![Fundamental data types](https://raw.githubusercontent.com/anushikhov/cpp/main/4_Fundamental_Data_Types/img/fundamental_data_types.png)

C++ also supports a number of other more complex types, called _compound types_.

The terms _integer_ and _integral_ are similar, but have different meanings. An integer is a specific data type that hold non-fractional numbers. Integral means "like an integer". Most often, integral is used as part of the term integral type, which includes all of the Boolean, characters, and integer types, also enumerated types. Integral type are named so because they are stored in memory as integers, even though their behaviors might vary.

Most modern programming languages include a fundamental string type. In C++, strings are not a fundamental type (they're a compound type).

### The \_t suffix

Many of the types defined in newer versions of C++ (e.g. std::nullptr_t) use a \_t suffix. This suffix means "type", and it's a common nomenclature applied to modern types.


