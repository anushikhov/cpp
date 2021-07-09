# Scope, duration, linkage summary

## Scope

An identifier's scope determines where the identifier can be accessed within the source code.
* Variable's with block scope/local scope can only be accessed within the block in which they are declared (including nested blocks. This includes:  
&emsp;&emsp;&emsp; * local variables  
&emsp;&emsp;&emsp; * function parameters  
&emsp;&emsp;&emsp; * user defined type definitions (such as enums and classes) declared inside a block  

* Variables and functions with global scope/file scope can be accessed from the point of declaration until the end of the file. This includes:  
&emsp;&emsp;&emsp; * global variables   
&emsp;&emsp;&emsp; * functions   
&emsp;&emsp;&emsp; * user-defined type definitions (such as enums and classes) declared inside a namespace or in the global scope

## Duration

A variable's duration determines when it is created and destroyed:
* Variables with automatic duration are created at the point of definition, and destroyed when the block they are part of is exited. This includes:  
&emsp;&emsp;&emsp; * local variables  
&emsp;&emsp;&emsp; * function parameters  

* Variables with static duration are created when the program begins and destroyed when the program ends. This includes:  
&emsp;&emsp;&emsp; * global variables  
&emsp;&emsp;&emsp; * static local variables  

* Variables with dynamic duration are created and destroyed by programmer request. This includes:  
&emsp;&emsp;&emsp; * dynamically allocated variables  

## Linkage summary

An identifier's linkage determines whether multiple declarations of an identifier refer to the same identifier or not.
* An identifier with no linkage means the identifier only refers to itself. This includes:  
&emsp;&emsp;&emsp; * local variables  
&emsp;&emsp;&emsp; * user-defined type definitions (such as enums and classes) declared inside a block  

* An identifier with internal linkage can be accessed anywhere within the file it is declared. This includes:  
&emsp;&emsp;&emsp; * static global variables (initialized or uninitialized)
&emsp;&emsp;&emsp; * static functions  
&emsp;&emsp;&emsp; * const global variables  
&emsp;&emsp;&emsp; * functions declared inside an unnamed namespace  
&emsp;&emsp;&emsp; * user-defined type definitions (such as enums and classes) declared inside an unnamed namespace  
* An identifier with external linkage can be accessed anywhere within the file it is declared, or other files (via a forward declaration). This includes:  
&emsp;&emsp;&emsp;` * functions  
&emsp;&emsp;&emsp;` * non-const global variables (initialized or uninitialized)  
&emsp;&emsp;&emsp;` * extern const global variables  
&emsp;&emsp;&emsp;` * inline const global variables  
&emsp;&emsp;&emsp;` * user-defined type definitions (such as enums and classes) declared inside a namespace or in the global scope  

Identifiers with external linkage will generally cause a duplicate definition linker error if the definitions are compiled into more than one .cpp file (due to violating the one-definition rule). There are some exceptions to this rule (for types, templates, and inline functions and variables).

Functions have external linkage by default. They can be made internal by using the static keyword.

## Variable scope, duration, linkage

![Variable scope, duration, linkage summary chart](https://raw.githubusercontent.com/anushikhov/cpp/master/learncpp_com/7_Object_Scope_and_Conversions/img/var_scope_duration_linkage.png)  

## Forward declaration

A forward declaration can be used to access a function or variable in another file. The scope of the declared variable is as per usual (file scope for globals, block scope for locals).

![Forward declarations](https://raw.githubusercontent.com/anushikhov/cpp/master/learncpp_com/7_Object_Scope_and_Conversions/img/forward_declarations.png)  

## Storage class specifiers

When used as part of an identifier declaration, the `static` and `extern` keywords are called **storage class specifiers**. In this context, they set the storage duration and linkage of the identifier.

C++ supports 4 active storage class specifiers: extern, static, thread_local, mutable.

![Stroage class specifiers](https://raw.githubusercontent.com/anushikhov/cpp/master/learncpp_com/7_Object_Scope_and_Conversions/img/storage_class_specifiers.png)  

The term _storage class specifier_ is typically only used in formal documentation.

