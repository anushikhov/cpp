# Const, constexpr, and symbolic constants

It is sometimes useful to define variables with values that can not be changed. For example, consider the gravity of Earth (near the surface): 9.8 meters/second^2. This isn't likely to change any time soon (and if it does, you've likely got bigger problems than learning C++). Defining this value as a constant helps ensure that this value isn't accidentally changed.

To make a variable constant, simply put the `const` keyword either before or after the variable type, like so:

` const double gravity { 9.8 }; // preferred use of const before type `  
` double const gravity { 9.8 }; // okay, but not preferred `  

**Const variables must be initialized when you define them, and then that value can not be changed via assignment.**

Const variables can be initialized from other variables (including non-const ones).

Const can also be used with function parameters. Making a function parameter const enlists the compiler's help to ensure that the parameter's value is not changed inside the function.


## Runtime vs compile-time constants

C++ actually has two different kinds of constants.

**Runtine constants** are constants whose initialization values can only be resolved at runtime.

**Compile-time constants** are constants whose initialization values can be determined at compile-time (when your program is compiling). 

Compile-time constants enable the compiler to perform optimizations that aren't available with runtime constants. For example, whenever gravity is used, the compiler can simply substitute the identifier gravity with the literal double 9.8.

When you declare a const variable, the compiler will implicitly keep track of whether it's a runtime or compile-time constant. In most cases, this doesn't matter, but there are a few odd cases where C++ requires a compile-time constant instead of a run-time constant.


## constexpr

To help provide more specificity, C++11 introduced the keyword **constexpr**, which ensures that a constant must be a compile-time constant.

**Best practice**
_Any variable that should not be modifiable after initialization and whose initializer is known at compile-time shoudl be declared as constexpr._
_Any variable that should not be modifiable after initialization and whose initializer is not known at compile-time should be declared as const._

### Naming your const variables

Some programmers prefer to use all upper-case names for const variables. Others use normal variable names with a 'k' prefix. However, we will use normal variable naming conventions, which is more common. Const variables act exactly like normal variables in every case except that they can not be assigned to, so there's no particular reason they need to be denoted as special.

## Symbolic constants

Use symbolic constants instead of magic numbers. A **symbolic constant** is a name given to a constant literal value. There are two ways to declare symbolic constants in C++. One of them is good, and one of them is not.

### Bad: Using object-like macros with a substition parameter as symbolic constants

Object-like macros have two forms -- one that doesn't take a substitution parameter (generally used for conditional compilation), and one that does have a substitution parameter. Whenever the preprocessor encounters the directive, any further occurrence of _identifier_ is replaced by _substition\_text_. The identifier is traditionally typed in all capital letters, using underscores to represent spaces.

` #define MAX_STUDENTS_PER_CLASS 30 `  
` int max_students { numClassrooms * MAX_STUDENTS_PER_CLASS }; `  

When you compile your code, the preprocessor replaces all instances of MAX_STUDENTS_PER_CLASS with the literal value 30, which is then compiled into your executable.

This is much more intuitive than using a magic number because it provides context for what the program is trying to do, even without a comment and if required we only need to change the value in one place.

However, there are at least three major problems with this:

1. Because macros are resolved by the preprocessor, all occurrences of the macro are replaced with the defined value just prior to compilation. If you are debugging your code, you won't see the actual value, you'll only see the name of the symbolic constant. And because these #defined values are not variables, you cannot add a watch in the debugger to see their values. If you want to know the value, you'll have to find the definition which could be in a different file. This can make your programs harder to debug.

1. Macros can conflict with normal code. 

1. Macros don't follow normal scoping rules, which means in rare cases a macro defined in one part of a program can conflict with code written in another part of the program that it wasn't supposed to interact with.

**Avoid using #define to create symbolic constants macros.**

### A better solution: Use constexpr variables

A better way to create symbolic constants is through the use of constexpr variables. Because these are just normal variables, they are watchable in the debugger, have normal scoping, and avoid other weird behaviors.

**Best practice**
_Use constexpr variables to provide a name and context for your magic numbers._



