# Enumerated types

C++ contains capabilities that allow programmers to create their own data types. These data types are called **user-defined data types**.

The simplest user-defined data type is the enumerated type. An **enumerated type** (also called an **enumeration** or **enum**) is a data type where every possible value is defined as a symbolic constant (called an **enumerator**). Enumerations are defined via the **enum** keyword.

` enum Color `  
` { `  
&emsp;&emsp;&emsp;` color_white, `  
&emsp;&emsp;&emsp;` color_black, `  
&emsp;&emsp;&emsp;` color_blue, `  
&emsp;&emsp;&emsp;` color_violet, `  
&emsp;&emsp;&emsp;` color_red, `  
&emsp;&emsp;&emsp;` color_teal, `  
&emsp;&emsp;&emsp;` color_pink, `  
&emsp;&emsp;&emsp;` color_yellow `  
` }; `

` Color magic = color_violet; `  
` Color room( color_white ); `  
` Color sharingan( color_red ); `  

Defining an enumeration (or any user-defined data type) does not allocate any memory. When a variable of the enumerated type is defined, memory is allocated for that variable at that time.

Providing a name for an enumerator is optional, but common. Enums without a name are sometimes called anonymous enums. Enumeration names are often named starting with a capital letter.

Enumerators must be given names, and typically use the same name style as constant variables. Sometimes enumerators are named in ALL_CAPS, but doing so is discouraged, because it risks collisions with preprocessor macro names.

Because enumerators are placed into the same namespace as the enumeration, an enumerator name can't be used in multiple enumerations within the same namespace. 

Consequently, it's common to prefix enumerators with a standard prefix like animal_ or color_, both to prevent naming conflicts and for code documentation purposes.

Each enumerator is automatically assined an integer value based on its position in the enumeration list. By default, the first enumerator is assigned the integer value 0, and each subsequent enumerator has a value one greater than the previous enumerator. 

It is possible to explicitly define the value of enumerator. These integer values can be positive or negative and can share the same value as other enumerators. Any non-defined enumerators are given a value one greater than the previous enumerator.

Multiple enumerators can be assigned the same value, when this happens, they become interchangeable. Although C++ allows it, assigning the same value to two enumerators in the same enumeration should generally be avoided.

**Best practice**<br/>
_Don't assign specific values to your enumerators._

**Best practice**<br/>
_Don't assign the same value to two enumerators in the same enumeration unless there's a very good reason._


## Enum type evaluation and input/output

Because enumerated values evaluate to integers, they can be assigned to integer variables. This means they can also be output (as integers), since std::cout knows how to output integers.

` int mypet( animal_dog }; `  
` std::cout << animal_dog; // evaluates to integer before being passed to std::cout `  

The compiler will not implicitly convert an integer to an enumerated value. The following will produce a compiler error:

` Animal animal{ 5 }; `  

However, you can force it to do so via a `static_cast`:

` Color color{ static_cast<Color>(5) }; // but don't `  

The compiler also will not let you input an enum using `std::cin`.

` Color color{}; `  
` std::cin >> color; // will cause compile error `  

One workaround is to read in an integer, and use a `static_cast` to force the compiler to put an integer value into an enumerated type: 

` int inputColor{}; `  
` std::cin >> inputColor; `  

` Color color{ static_cast<Color>(inputColor) }; `  

Each enumerated type is considered a distinct type. Consequently, trying to assign enumerators from one enum type to another enum type will cause a compiler error:

` Animal animal{ color_blue }; // will cause a compile error `  

If you want to use a different integer type for enumerators, for example to save bandwidth when networking an enumerator, you can specify it at the enum declaration.

` enum Color : std::uint_least8_t `  
` { `  
&emsp;&emsp;&emsp;` color_while, `  
&emsp;&emsp;&emsp;` // ... `  
` } `  

Since enumerators aren't usually used for arithmetic or comparisons, it's safe to use an unsigned integer. We also need to specify the enum base when we want to forward declare an enum.

` enum Color; // error `  
` enum Color : int; // the right way `  

` // Because Color was forward declared with a fixed base, `  
` // we need to specify the base again at the definition. `  
` enum Color : int `  
` { `  
&emsp;&emsp;&emsp;` color_white, `  
&emsp;&emsp;&emsp;` // ... `  
` } `  

As with constant variables, enumerated types show up in the debugger, making them more useful than #defined values in this regard.

Trying to print an enumerated value using std::cout results in the integer value of the enumerator being printed. To print the enumerator itself as text, we can write a function and use an if or switch statement to do so.


## Enum allocation and forward declaration

Enum types are considered part of the integer family of types, and it's up to the compiler to determine how much memory to allocate for an enum variable. The C++ standard says the enum size needs to be large enough to represent all of the enumerator values. Most often, it will make enum variables the same size as a standard int.

Because the compiler needs to know how much memory to allocate for an enumeration, you can only forward declare them when you also specify a fixed base. Because defining an enumeration does not allocate any memory, if an enumeration is needed in multiple files, it is fine to define the enumeration in a header, and #include that header wherever needed.


## What are enumerators useful for?

Enumerated types are useful for code documentation and readability purposes when you need to represent a specific, predefined set of states.

For example, old functions sometimes return integers to the caller to represent error codes when something went wrong inside the function. Typically, small negative numbers are used to represent different possible error codes.
For example:

` int readFileContents() `  
` { `  
&emsp;&emsp;&emsp;` if (!openFile()) `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` return -1; `  
&emsp;&emsp;&emsp;` if (!readFile()) `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` return -2; `  
&emsp;&emsp;&emsp;` if (!parseFile()) `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` return -3; `  

&emsp;&emsp;&emsp; ` return 0; `  
` } `   

However, using magic numbers like this isn't very descriptive. An alternative method would be through use of an enumerated type:

` enum ParseResult `  
` { `  
&emsp;&emsp;&emsp;` success, `   
&emsp;&emsp;&emsp;` error_opening_file, `  
&emsp;&emsp;&emsp;` error_reading_file, `  
&emsp;&emsp;&emsp;` error_parsing_file `  
` }; `  

` ParseResult readFileContents() `  
` { `  
&emsp;&emsp;&emsp;` if (!openFile()) `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` return error_opening_file; `  
&emsp;&emsp;&emsp;` if (!readFile()) `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` return error_reading_file; `  
&emsp;&emsp;&emsp;` if (!parseFile()) `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` return error_parsing_file; `  

&emsp;&emsp;&emsp;` return success; `  
` } `  

This is much easier to read and understand than using magic number return values. Furthermore, the caller can test the function's return value against the appropriate enumerator, which is easier to understand than testing the return result for a specific integer value.

` if (readFileContents() == success) `  
` { `  
&emsp;&emsp;&emsp;` // do something `  
` } `  
` else `  
` { `  
&emsp;&emsp;&emsp;` // print error message `  
` } `  

Enumerated types are best used when defining a set of related identifiers. For example, let's say you were writing a game where the player can carry one item, but that item can be several different types. You could do this:

` #include <iostream> `  
` #include <string> `  

` enum ItemType `  
` { `  
&emsp;&emsp;&emsp;` itemtype_sword, `  
&emsp;&emsp;&emsp;` itemtype_torch, `  
&emsp;&emsp;&emsp;` itemtype_potion `  
` }; `  

` std::string getItemName(ItemType itemType) `  
` { `  
&emsp;&emsp;&emsp;` switch (itemType) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` case itemtype_sword: `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` return "Sword"; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` case itemtype_torch: `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` return "Torch"; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` case itemtype_potion: `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` return "Potion"; `  
&emsp;&emsp;&emsp;` } `  

&emsp;&emsp;&emsp;` return "???"; `
` } `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` ItemType itemType{ itemtype_torch }; `  

&emsp;&emsp;&emsp;` std::cout << "You are carrying a " << getItemName(itemType) << '\n'; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

Or alternatively, if you were writing a function to sort a bunch of values:

` enum SortType `  
` { `  
&emsp;&emsp;&emsp;` sorttype_forward, `  
&emsp;&emsp;&emsp;` sorttype_backwards `  
` }; `  

` void sortData(SortType type) `  
` { `  
&emsp;&emsp;&emsp;` if (type == sorttype_forward) `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; ` // sort data in forward order `  
&emsp;&emsp;&emsp;` if (type == sorttype_backwards) `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` // sort data in backwards order `  
` } `  

Many languages use enumerations to define Booleans. A Boolean is essentially just an enumeration with 2 enumerators: false and true. However, **in C++, true and false are defined as keywords instead of enumerators.**
