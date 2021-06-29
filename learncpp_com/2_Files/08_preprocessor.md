# Introduction to the preprocessor

#### Translation and the preprocessor

Prior to compilation, the code file goes through a phase known as **translation**. Many things happen in the translation phase to get your code ready to be compiled. A code file with translations applied to it is called a **translation unit**.

The most noteworthy of the translation phases involves the preprocessor. The **preprocessor** is best thought of as a separate program that manipulates the text in each code file.

When the preprocessor runs, it scans through the code file (from top to bottom), looking for preprocessor directives. **Preprocessor directives** (often just called _directives_) are insturctions that start with a # symbol and end with a newline (NOT a semicolon). These directives tell the preprocessor to perform specific particular text manipulation tasks. The preprocessor does not understand C++ syntax - instead, the directives have their own syntax (which in some cases resembles C++ syntax, and in other cases, not so much).

The output of the preprocessor goes through several more translation phases, and then is compiled. The preprocessor does not modify the original code files in any way -- rather, all text changes made by the preprocessor happen temporarily in-memory each time the code file is compiled.

_Using directives_ are not preprocessor directives (and thus are not processed by the preprocessor). So while the term _directive_ usually means a preprocessor directive, this is not always the case.

##### Includes

When you _#include_ a file, the preprocessor replaces the #include directive with the contents of the included file. The included contents are then preprocessed (along with the rest of the file), and then compiled.

##### Macro defines

The #define directive can be used to create a macro. In C++, a **macro** is a rule that defines how input text is converted into replacement output text.

There are two basic types of macros: _object-like_ macros, and _function-like_ macros.

_Funtion-like macros_ act like functions, and serve a similar purpose. Their use is generally considered dangerous, and almost anything they can do can be done by a normal function.

_Object-like macros_ can be defined in one of two ways:

#define identifier
#define identifier substitution_text


###### Object-like macros without substitution text

` #define USE_YEN `  

Any further occurrence of the identifier is removed and replaced by nothing. 

Unlike object-like macros with substitution text, macros of this form are generally considered acceptable to use.

###### Object-like macros with substitution text

When the preprocessor encounters this directive, any further occurence of the identifier is replaced by _substitution_text_. The identifier is traditionally typed in all capital letters, using underscores to represent spaces.

` #include <iostream `  
` #define MY_NAME "Alex" `  
` int main() `  
` { `  
`    std::cout << "My name is: " << MY_NAME; `  
`    return 0; `  
` } `  

The preprocessor converts the above into the following:

` // The contents of iostream are inserted here `  
` int main() `  
` { `  
`    std::cout << "My name is: " << "Alex"; `  
`    return 0; `  
` } `

Object-like macros were used as a cheaper alternative to constant variables. They should only be seen in legacy code anymore.


##### Conditional compilation

The **conditional compilation preprocessor directives** allow you to specify under what conditions something will or won't compile. There are quite a few different conditional compilation directives, we'll cover onthe the three the most used by far: #ifdef, #ifndef, #endif.

The _#ifdef_ preprocessor directive allows the preprocessor to check whether an identifier has been previously #defined. If so, the code between the #ifdef and matching #endif is compiled. If not, the code is ignored.

#ifndef is the opposite of #ifdef, in that it allows you to check whether an identifier has NOT been #defined yet.

In place of #ifdef PRINT_BOB and #ifndef PRINT_BOB, you'll also see #if defined(PRINT_BOB) and #if !defined(PRINT_BOB). These do the same, but use a slightly more C++-style syntax.


##### #if 0

One more common use of conditional compilation involves using _#if 0_ to exclude a block of code from being compiled (as if it were inside a comment block).

**This provides a convenient way to "comment out" code that contains multi-line comments.**


##### Object-like macros don't affect other preprocessor directives

**Macros only cause text substitution for normal code. Other preprocessor commands are ignored.**

In actuality, the output of the preprocessor contains no directives at all -- they are all resolved/stripped out before compilation, because the compiler wouldn't know what to do with them.


##### The scope of defines

**Directives are resolved before compilation, from top to bottom on a file-by-file basis.**

Although, techically there is no difference, for general readability, you'll want to #define identifiers outside of functions.

Once the preprocessor has finished, all defined identifiers from that file are discarded. This means that directives are only valid from the point of definition to the end of the file in which they are defined. Directives defined in one code file do not have impact on other code files in the same project.
