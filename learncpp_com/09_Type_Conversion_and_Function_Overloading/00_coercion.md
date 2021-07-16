# Implicit type conversion (coercion)

The value of an object is stored as a sequence of bits, and the data type of the object tells the compiler how to interpret those bits into meaningful values. Different data types may represent the "same" number differently.

The process of converting a value from one data type to another data type is called a **type conversion**.

Type conversion can be invoked in one of two ways: either implicitly (as needed by the compiler), or explicitly (when requested by the programmer).


## Implicit type conversion

**Implicit type conversion** (also called **automatic type conversion** or **coercion**) is performed automatically by the compiler when one data type is required, but a different type is supplied.

Implicit type conversion happens in the following cases:

* When initializing (or assigning a value to) a variable with a value of a different data type
* When the type of a return value is different from the function's declared return type
* When using certain binary operators with operands of different types
* When using a non-Boolean value in an if-statement
* When an argument passed to a function is a different type than the function parameter


## What happens when a type conversion is invoked

When a type conversion is invoked (whether implicitly or explicitly), the compiler will determine whether it can convert the value from the current type to the desired type. If a valid conversion can be found, then the compiler will produce a new value of the desired type. Conversions don't change the value or type of the value being converted.

If the compiler can't find an acceptable conversion, then the compilation will fail with a compile error. Type conversions can fail for any number of reasons. For example, the compiler might not know how to convert a value between the original type and the desired type. In other cases, statements may disallow certain types of conversions:

` int x { 3.5 }; // brace initialization disallows conversions that result in data loss `  

There are also cases where the compiler may not be able to figure out which of several possible type conversions is unambiguously the best one to use.


## The standard conversions

The C++ language standard defines how different fundamental types (and in some cases, compound types) can be converted to other types. These conversion rules are called the **standard conversions**.

The standard conversion can be divided into 4 categories:

* Numeric promotions
* Numeric conversions
* Arithmetic conversions
* Other conversions (includes various pointer and reference conversions)

When a type conversion is needed, the compiler will see if there are standard conversions that it can use to convert the value to the desired type. The compiler may apply zero, one, or more than one standard conversions in the conversion process.

On architectures where `int` and `long` both have the same size and range, the same sequence of bits is used to represent values of both types. Therefore, no actual conversion (zero conversion) is needed to convert a value between those types -- the value can simply be copied.
