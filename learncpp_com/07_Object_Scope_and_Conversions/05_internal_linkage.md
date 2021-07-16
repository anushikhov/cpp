# Internal linkage

An identifier's linkage determines whether other declarations of that name refer to the same object or not.

Local variables have no linkage.

Global variables and function identifiers can have either internal linkage or external linkage.

An identifier with **internal linkage** can be seen and used within a single file, but it is not accessible from other files (i.e. it is not exposed to the linker). This means that if two files have identically named identifiers with internal linkage, those identifiers will be treated as independent.

Global variables with internal linkage are sometimes called **internal variables**.

To make a non-constant global variable internal, we use the static keyword.

const and constexpr global variables have internal linkage by default (and thus don't need the static keyword -- if it is used, it will be ignored).

The use of the `static` keyword is an example of a **storage class specifier**, which sets both the name's linkage and its storage duration (but not its scope). The most commonly used storage class specifiers are `static`, `extern`, and `mutable`.  The term _storage class specifier_ is moslty used in technical documentation.

The ODR says that an object or function cannot have more than one definition, either within a file or a program. However, it's worth noting that internal objects (and functions) that are defined in different files are considered to be independent entities (even if their names and types are identical), so there is no violation of the ODR. Each internal object only has one definition.

Because linkage is a property of an identifier (not of a variable), function identifiers have the same linkage property that variable identifiers do. Functions default to external linkage, but can be set to internal linkage via the static keyword.

` static int g_x;          // defines non-initialized internal global variable (zero initialized by default) `  
` static int g_x{ 1 };     // defines initialized internal global variable `  
` const int g_y { 2 };     // defines initialized internal global const variable `  
` constexpr int g_y { 3 }; // defines initialized internal global constexpr variable `  
` static int foo() {};     // defines internal function `  
