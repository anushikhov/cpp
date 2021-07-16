# Forward declarations and definitions

**Best practice**
_When addressing compile errors in your programs, always resolve the first error produced first and then compile again._

A **forward declaration** allows us to tell the compiler about the existence of an identifier before actually defining the identifier.

In the case of functions, this allows us to tell the compiler about the existence of a function before we define the function's body. This way, when the compiler encounters a call to the function, it'll understand that we're making a function call, and can check to ensure we're calling the function correctly, even if it doesn't yet know how or where the function is defined.

To write a forward declaration for a function, we use a declaration statement called a **function prototype**. 

The function prototype consists of the function's return type, name, parameters; but no function body, terminated with a semicolon.

` int add(int x, int y);`  

Function prototypes do not need to specify the names of the parameters.

` int add(int, int); // valid function prototype `  

**Best practice**
_When defining function prototypes, keep the parameter names._

**If a forward declaration is made and the function is called, but the program never defines the function, the program will compile okay, but the linker will complain that it can't resolve the function call.**

Forward declarations can also be used with other identifiers in C++, such as variables and user-defined types. Variables and user-defined types have a different syntax for forward declarations.

A **definition** actually implements (for functions or types) or instantiates (for variables) the identifier.

**A definition is needed to satisfy the linker.**

If you use an identifier without providing a definition, the linker will error.

The **one definition rule** (or **ODR** for short) is a well-known rule in C++. It has three parts:

1. Within a given _file_, a function, object, type, or template can only have one definition.
1. Within a give _program_, an object or normal function can only have one definition.
1. Types, templates, inline functions, and variables are allowed to have identical definitions in different files. 

* **Violating part 1 of the ODR will cause the compiler to issue a redefinition error.**
* **Violating ODR part 2 will likely cause the linker to issue a redefinition error.**
* **Violating ODR part 3 will cause undefined behavior.**

**Functions that share an identifier but have different parameters (overloaded functions) are considered to be distinct function.**

A **declaration** is a statement that tells the compiler about the existence of an identifier and its type information.

A declaration is all that is needed to satisfy the compiler. This is why we can use a forward declaration to tell the compiler about an identifier that isn't actually defined until later.

In C++, all definitions also serve as declarations. In the case of variables, definition also serves as a declaration `int x;`. 

In most cases a definition serves our purposes, as it satisfies both the compiler and linker. We only need to provide an explicit declaration when we want to use an identifier before it has been defined.

The converse is not true; all declarations are not definitions. An example of this is the function prototype -- it satisfies the compiler, but not the linker. These declarations that are not definitions are called **pure declarations**. Other types of pure declarations include forward declarations for variables and type declarations.

The ODR doesn't apply to pure declarations (it's the _one definition rule_, not the _one declaration rule_), so you can have as many pure declarations for an identifier as you desire (although having more than one is redundant).

The term "declaration" is typically used to mean a "pure declaration", and "definition" is used to mean "a definition that also serves as a declaration". Thus, we'd typically call _int x;_ a definition, even though it is both a definition and a declaration.


A function prototype is a declaration statement that includes a function's name, return type, and parameters. It does not include the function body.

A forward declaration tells the compiler that an identifier exists before it is actually defined.
