# External linkage

Internal linkage limits the use of an identifier to a single file. 

An identifier with **external linkage** can be seen and used both from the file in which it is defined, and from other code files (via a forward declaration). In this sense, identifiers with external linkage are truly "global" in that they can be used anywhere in a program.

Functions have external linkage by default. You can call a function defined in one file from another file.

In order to call a function defined in another file, you must place a `forward declaration` for the function in any other files wishing to use the function. The forward declaration tells the compiler about the existence of the function, and the linker connects the function calls to the actual function definition.

Global variables with external linkage are sometimes called **external variables**. To make a global variable external (and thus accessible by other files), we can use the `extern` keyword to do so. 

` int g_x { x }; // non-constant global variables are external by default `  
` extern const int g_y { 3 }; // const globals can be defined as extern, making them external `  
` extern constexpr int g_z { 3 }; // constexpr globals can be defined as extern, making them external (but this is useless) `  

Non-const global variables are external by default (if used, the extern keyword will be ignored).

To actaully use an external global variable that has been defined in another file, you also must place a forward declaration for the global variable in any other files wishing to use the variable. For variables, creating a forward declaration is also done via the extern keyword (with no initialization value).

The `extern` keyword has different meanings in different contexts. In some contexts, extern means "give the variable external linkage". In other contexts, `extern` means "this is a forward declaration for an external variable that is defined somewhere else".

**If you want to define an uninitialized non-const global variable, do not use the extern keyword, otherwise C++ will think you're trying to make a forward declaration for the variable.**

**Although constexpr variables can be given external linkage via the extern keyword, they can not be forward declared, so there is no value in giving them external linkage.**

Function forward declarations don't need the extern keyword -- the compiler is able to tell whether you're defining a new function or making a forward declaration based on whether you supply a function body or not. Variables forward declarations do need the extern keyword to help differentiate variables definitions from variable forward declarations (they look otherwise identical).

` int g_x; // variable definition (can have initializer if desired) `  
` extern int g_x; // forward declaration (no initializer) `  

` extern const int g_y { 1 }; // variable definition (const requires initializers) `  
` extern const int g_y; // forward declaration (no initializer) `  

The terms "file scope" and "global scope" tend to cause confusion, and this is partly due to the way they are informally used. Technically, in C++, all global variables have "file scope", and the linkage property controls whether they can be used in other files or not.

However, informally, the term "file scope" is more often applied to global variables with internal linkage, and "global scope" to global variables with external linkage (since they can be used across the whole program, with the appropriate forward declarations).  

...  

` // External global variable definitions `  
` int g_x; // defines non-initialized external global variable (zero initialized by default) `  
` extern const int g_x{ 1 }; // defines initialized const external global varaible `  
` extern constexpr int g_x{ 2 }; // defines initialized constexpr external global variable `  

` // Forward declarations `  
` extern int g_y; // forward declaration for non-constant global variable `  
` extern const int g_y; // forward declaration for const global variable `  
` extern constexpr int g_y; // not allowe: constexpr variables can't be forward declared `  

...  

Scope determines where a variable is accessible. 
Duration determines where a variable is created and destroyed.
Linkage determines whether the variable can be exported to another file or not.

Global variables have global scope (aka, file scope), which means they can be accessed from the point of declaration to the end of the file in which they are declared.

Global variables have static duration, which means they are created when the program is started, and destroyed when it ends.

Global variables can have either internal or external linkage,  via the static and extern keywords respectively.
