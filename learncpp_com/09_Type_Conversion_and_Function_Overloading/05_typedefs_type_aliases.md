# Typedefs and type aliases

## Type aliases

In C++, **using** is a keyword that creates an alieas for an existing data type.

` using distance_t = double; `  

By convention, type alias names use a "\_t", "\_type", or no, suffix. The suffixes both indicate that the name is an alias, and helps prevent naming collisions with other types or identifiers.

Once defined, an alias can be used anywhere a type is needed. We can create a variable with the alias name as the type. When the compiler encounters an alias name, it will substitute in the aliased type.

### Type aliases are not new types

An alias does not actually define a new type -- it just introduces a new identifier for an existing type. An alias is completely interchangeable with the aliased type.

**Care must be taken not to mix values of aliases that are intended to be semantically distinct.**

Some languages support the concept of a **strong typedef** (or strong type alias). A strong typedef actually creates a new type that has all the original properties of the original type, but the compiler will throw an error if you try to mix values of the aliased type and the strong typedef. As of C++20, C++ does not directly support strong typedefs (though enum classes are similar), but there are quite a few 3rd party C++ libraries that implement strong typedef-like behavior.

### The scope of a type alias

Because scope is a property of an identifier, type alias identifiers follow the same scoping rules as variable identifiers: a type alias defined inside a block has block scope and is usable only within that block, whereas a type alias defined in the global namespace has file scope and is usable to the end of the file.

If you need to use one or more type alias across multiple files, they can be defined in a header file and #included into any code file that needs to use the definition:

mytypes.h  
` #ifndef MYTYPES `  
` #define MYTYPES `  

&emsp;&emsp;&emsp;` using miles_t = long; `  
&emsp;&emsp;&emsp;` using speed_t = long; `  

` #endif `  

Type aliases #included this way will be imported into the global namespace and thus have global scope.


## Typedef

**typedef** (which is short for "type definition") is a keyword with the same semantics as "using", but reversed syntax.

` typedef long miles_t; `  
` using miles_t = long; `  

Typedefs are still in C++, but their use is discouraged.

Typedefs have a few syntactical issues. First, it's easy to forget whether the `typedef` name or aliased type name come first. If you get backwards, the compiler will complain. Second, the syntax for typedefs can get ugly with more complex types.

` typedef int (*fcn_t)(double, char); `  
` using fcn_t = int(*)(double, char); `  

Third, the name "typedef" suggests that a new type is being defined, but that's not true. As we have seen above, an alias is interchangeable with the aliased type.

**Best practice**<br/>
_When creating aliased types, prefer the type alias syntax over the typedef syntax._

### Using type aliases for platform independent coding

One of the uses for type aliases is that they can be used to hide platform specific details. On some platforms, an `int` is 2 bytes, and on other, it is 4 bytes. Thus, using `int` to store more than 2 bytes of information can be potentially dangerous when writing platform independent code.

Because `char`, `short`, `int`, and `long` give no indication of their size, it is fairly common for cross-platform programs to use type aliases to define aliases that include the type's size in bits. For example, `int8_t` would be an 8-bit signed integer, `int16_t` a 16-bit signed integer, and `int32_t` a 32-bit signed integer. Using type aliases in this manner helps prevent mistakes and makes it more clear about what kind of assumptions have been made about the size of the variable.

In order to make sure each aliased type resolves to a type of the right size, type aliases of this kind are typically used in conjunction with preprocessor directives:


` #ifndef INT_2_BYTES `  
` using int8_t = char; `  
` usint int16_t = int; `  
` usint int32_t = long; `  
` #else `  
` using int8_t = char; `  
` using int16_t = short; `  
` using int32_t = int; `  
` #endif `  

On machines where integers are only 2 bytes, INT_2_BYTES can be #defined, and the program will be compiled with the top set of type aliases. On machines where integers are 4 bytes, leaving INT_2_BYTES undefined will cause the bottom set of type aliases to be used. In this way, `int8_t` will resolve to a 1 byte integer, `int16_t` will resolve to a 2 bytes integer, and `int32_t` will resolve to a 4 byte integer using the combination of `char`, `short`, `int`, and `long` that is appropriate for the machine the program is being compiled on.

The fixed-width integers (such as `std::int_fast16_t` and `std::int_least32_t`) and `size_t` type are actually just type aliases to various fundamental types.

This is also why when you print an 8bit fixed-width integer usint `std::cout`, you're likely to get a character value. For example, `std::int_least8_t` is typically defined as a type alias for one of the char types. And char types print their values as ASCII characters rather than integer values.

### Using type aliases to make complex types simple

Types can get compilcated and lengthy to type:

` #include <string> `  
` #include <vector> `  
` #include <utility> `  

` bool hasDuplicates(std::vector<std::pair<std::string, int> > pairlist) `  
` { `  
&emsp;&emsp;&emsp;` // some code here `  
&emsp;&emsp;&emsp;` return false; `  
` } `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` std::vector<std::pair<std::string, int> > pairlist; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

Typing `std::vector<std::pair<std::string, int> >` everywhere you need to use that type is cumbersome and easy to type. It's much easier to use a type alias:

` using pairlist_t = std::vector<std::pair<std::string, int> >; `  

Type aliases allow you to take complex types and give them a simple name, which makes your code easier to read and saves typing. This is probably the best use for type aliases.

### Using type aliases for legibility

Type aliases can also help with code documentation and comprehension.

` int gradeTest(); `  

` using testScore_t = int; `  
` testScore_t gradeTest(); `  

The return type of `testScore_t` makes it a little more obvious that the function is returning a type that represents a test score.

Creating a type alias just to document the return type of a single function isn't worth it (use a comment instead). But if you have already created a type alias for other reasons, this can be a nice additional benefit.

### Using type aliases for easier code maintenance

Type aliases also allow you to change the underlying type of an object without having to change lots of code. For example, if you were using a `short` to hold a student's ID number, but then later decided you needed a `long` instead, you'd have to comb through lots of code and replace `short` with `long`. It would probably be difficult to figure out which objects of type `short` were being used to hold ID numbers and which were being used for other purposes.

However, if you use type aliases, then changing types becomes as simple as updating the type alias.

While this seems like a nice benefit, caution is necessary whenever a type is changed, as the behavior of the program may also change. This is especially true when changing the type of a type alias to a type in a different type family (e.g. an integer to a floating point value, or vice versa). The new type may have comparison or integer/floating point division issues, or other issues that the old type did not. If you change an existing type to some other type, your code should be thoroughly retested.

### Downsides and conclusion

While type aliases offer some benefit, they also introduce yet another identifier into your code that needs to be understood. If this isn't offset by some benefit to readability or comprehension, then the type alias is doing more harm than good.

A poorly utilized type alias can take a familiar type and hide it behind a custom name that needs to be looked up. In some cases (such as with smart pointers), obscuring the type information can also be harmful to understanding how the type should be expected to work.

For this reason, type aliases should be used primarily in cases where there is a clear benefit to code readability or code maintenance. Type aliases are most useful when they can be used in many places throughout your code, rather than in fewer places.

**Best practice**<br/>
_Use type aliases judiciously, when they provide a clear benefit to code readability or code maintenance._
