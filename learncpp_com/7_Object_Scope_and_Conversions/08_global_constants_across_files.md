# Sharing global constants across multiple files (using inline variables)

In some applications, certain symoblic constants may need to be used throughout your code (not just in one location). These can include physics or mathematical constants that don't change or application-specific "tuning" values. Instead of redefining these constants in every file that needs them, it's better to declare them once in a central location and use them wherever needed. That way, if you ever need to change them, you only need to change them in one place, and those changes can be propagated out.

## Global constants as internal variables

Pre-C++17, the following is probably the most common:

1. Create a header file to hold these constants
1. Inside the header file, define a namespace
1. Add all your constants inside the namespace (make sure they're constexpr)
1. #include the header file wherever you need it 

constants.h 
 
` #ifndef CONSTANTS_H `  
` #define CONSTANTS_H `  

` namespace constants `  
` { `  
&emsp;&emsp;&emsp;` constexpr double pi { 3.14159 }; `  
&emsp;&emsp;&emsp;` constexpr double avogadro { 6.0221413e23 }; `  
&emsp;&emsp;&emsp;` constexpr double gravity { 9.8 }; `  
` } `  
` #endif `  

Then #include the header and use the scope resolution operator (::) with the namespace name to the left, and your variable name to the right in order to access your constants in .cpp files.

When this header gets #included into a .cpp file, each of these variables defined in the header will be copied into that code file at the point of inclusion. Because these variables live outside of a function, they're treated as global variables within the file they are included into, which is why you can use them anywhere in that file.

Because const globals have internal linkage, each .cpp file gets an independent version of the global variable that the linker can't see. In most cases, because these are const, the compiler will simply optimize the variable away.

The term "optimizing away" refers to any process where the compiler optimizes the performance of your program by removing things in a way that doesn't affect the output of your program. 

## Global constants as external variables

The above method has a few potential downsides.

While this is simple (and fine for smaller programs), every time constants.h gets #included into a different code file, each of these variables is copied into the including code file. Therefore, if constants.h gets included into 20 different code files, each of these variables is duplicated 20 times. Header guards won't stop this from happening, as they only prevent a header from being included more than once into a single including file, not from being included one time into multiple different code files. This introduces two challenges:

1. Changing a single constant value would require recompiling every file that includes the constants header, which can lead to lengthy rebuild times for larger projects.
1. If the constants are large in size and can't be optimized away, this can use a lot of memory.

One way to avoid these problems is by turning these constants into external variables, since we can then have a single variable (initialized once) that is shared across all files. In this method, we'll define the constants in a .cpp file (to ensure the definitions only exist in one place), and put forward declarations in the header (which will be included by other files).

We use const instead of constexpr in this method because constexpr variables can't be forward declared, even if they have external linkage.

constants.cpp  

` #include "constants.h" `  

` namespace constants `  
` { `  
&emsp;&emsp;&emsp;` // actual global variables `  
&emsp;&emsp;&emsp;` extern const double pi { 3.14159 }; `  
&emsp;&emsp;&emsp;` extern const double avogadro { 6.0221413e23 }; `  
&emsp;&emsp;&emsp;` extern const double gravity { 9.8 }; `  
` } `  

constants.h  

` #ifndef CONSTANTS_H `  
` #define CONSTANTS_H `  

` namespace constants `  
` { `  
&emsp;&emsp;&emsp;` extern const double pi; `  
&emsp;&emsp;&emsp;` extern const double avogadro; `  
&emsp;&emsp;&emsp;` extern const double gravity; `  
` } `  

` #endif `  

main.cpp  

` #include "constants.h" `  

` #include <iostream> `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` std::cout << "Enter a radius: "; `  
&emsp;&emsp;&emsp;` int radius{}; `  
&emsp;&emsp;&emsp;` std::cin >> radius; `  

&emsp;&emsp;&emsp;` std::cout << "The circumference is: " << 2.0 * radius * constants::pi << '\n'; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

Because global symbolic constants should be namespaced (to avoid naming conflicts with other identifiers in the global namespace), the use of a "g_" naming prefix is not necessary.

Now symbolic constants will get instantiated only once (in constants.cpp) instead of in each code file where constatns.h is #included, and all uses of these constants will be linked to the version instantiated in constants.cpp. Any changes made to constants.cpp will require recompiling only constants.cpp.

However, there are several downsides to this method too. First, these constants are now considered compile-time constants only within the file they are actually defined in (constants.cpp). In other files, the compiler will only see the forward declaration, which doesn't define a constant value (and must be resolved by the linker). This means in other files, these are treated as runtime constant values, not compile-time constants. Thus outside of constants.cpp, these varaiables can't be used anywhere that requires a compile-time constant. Second, because compile-time constants can typically be optimized more than runtime constants, the compiler may not be able to optimize these as much.

**In order for variables to be usable in compile-time contexts, such as array sizes, the compiler has to see the variable's definiton (not just a forward declaration).**

Because the compiler compiles each source file individually, it can only see variable definitions that appear in the source file being compiled (which includes any included headers). For this reason, constexpr variables cannot be separated into header and source file, they have to be defined in the header file.

Given the above downsides, prefer defining your constants in the header file. If you find that for some reason those constants are causing trouble, you can move some or all of them into a .cpp file as needed.

## Global constants as inline variables

C++17 introduced a new concept called inline variables. In C++, the term inline has evolved to mean "multiple definitions are allowed". Thus, an **inline variable** is one that is allowed to be defined in multiple files without violating the one definition rule. Inline global variables have external linkage by default.

Inline variables have two primary restrictions that must be obeyed:
1. All definitions of the inline variable must be identical (otherwise, undefined behavior will result).
1. The inline variable definition (not a forward declaration) must be present in any file that uses the variable.

The linker will consolidate all inline definitions of a variable into a single variable definition (thus meeting the one definition rule). This allows us to define variables in a header file and have them treated as if there was only one definition in a .cpp file somewhere. These variables also retain their constexpr-ness in all files in which they are included.

With this, we can go back to defining our globals in a header file without the downside of duplicated variables:

constants.h  

` #ifndef CONSTANTS_H `  
` #define CONSTANTS_H `  

` // define your own namespace to hold constants `  
` namespace constants `  
` { `  
&emsp;&emsp;&emsp;` inline constexpr double pi { 3.14159 }; `  
&emsp;&emsp;&emsp;` inline constexpr double avogadro { 6.0221413e23 }; `  
&emsp;&emsp;&emsp;` inline constexpr double gravity { 9.8 }; `  
` } `  

` #endif `  

main.cpp  

` #include "constants.h" `  

` #include <iostream> `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` std::cout << "Enter a radius: "; `  
&emsp;&emsp;&emsp;` int radius{}; `  
&emsp;&emsp;&emsp;` std::cin >> radius; `  

&emsp;&emsp;&emsp;` std::cout << "The circumference is: " << 2.0 * radius * constants::pi << '\n'; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

We can include constants.h into as many code files as we want, but these variables will only be instantiated once and shared across all code files.

**Best practice**<br/>
_If you need global constants and your compiler is C++17 capable, prefer defining inline constexpr global variables in a header file._ 
