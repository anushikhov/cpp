# User-defined namespaces and the name resolutoin operator

A naming collision occurs when two identical identifiers are introduced into the same scope, and the compiler can't disambiguate which one to use. When this happens, compiler or linker will produce an error because they do not have enough information to resolve the ambiguity. As programs become larger, the number of identifiers increases linearly, which in turn causes the probability of a naming collision occurring to increase exponentially.

## Defining your own namespaces

C++ allows us to define our own namespaces via the `namespace` keyword. Namespaces that you create for your own declarations are called **user-defined namespaces**.

Namespace identifiers are typically non-capitalized.

` namespace foo `  
` { `  
&emsp;&emsp;&emsp;` int doSomething(int x, int y) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` return x + y; `  
&emsp;&emsp;&emsp;` } `  
` } `  

To indicate the namespace we want to use a function from, we need to either make use of the scope resolution operator or the using statements.

## Accessing a namespace with the scope resolutoin operator (::)

The best way to tell the compiler to look in a particular namespace for an identifier is to use the **scope resolutoin operator (::)**. The scope resolution operator tells the compiler that the identifier specified by the righ-hand operand should be looked for in the scope of the left-hand operand.

## Using the scope resolution operator with no name prefix

The scope resolution operator can also be used in front of an identifier without providing a namespace. In such a case, the identifier is looked for in the global namespace.

## Identifier resolution from within a namespace

If an identifier inside a namespace is used and no scope resolution is provided, the compiler will first try to find a matching declaration in that same namespace. If no matching identifier is found, the compiler will then check each containing namespace in sequence to see if a match is found, with the global namespace being checked last.

We can make use of the scope resolution operator with no namespace to explicitly call the global version of an identifier.

## Multiple namespace blocks are allowed

It's legal to declare namespace blocks in multiple locations (either across multiple files, or multiple places within the same file). All declarations within the namespace are considered part of the namespace.

The standard library makes extensive use of this feature, as each standard library header file contains its declarations inside a namespace std block contained within that header file. Otherwise the entire standard library would have to be defined in a single header file.

This capability also means you could add your own functionality to the std namespace. Doing so causes undefined behavior most of the time, because the std namespace has a special rule, prohibiting extension from user code.

**Do not add custom functionality to the std namespace.**

When you separate your code into multiple files, you'll have to use a namespace in the header and source file.

## Nested namespaces

Namespaces can be nested inside other namespaces.

` #include <iostream> `  

` namespace foo `  
` { `  
&emsp;&emsp;&emsp;` namespace goo `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` int add(int x, int y) `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` return x + y; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` } `  
&emsp;&emsp;&emsp;` } `  
` } `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` std::cout << foo::goo::add(1, 2) << '\n'; `  
&emsp;&emsp;&emsp;` return 0; `  
` } `  

Since C++17, nested namespaces can also be declared like so:

` #include <iostream> `  

` namespace foo::goo `  
` { `  
&emsp;&emsp;&emsp;` int add(int x, int y) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` return x + y; `  
&emsp;&emsp;&emsp;` } `  
` } `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` std::cout << foo::goo::add(1, 2) << '\n'; `  
&emsp;&emsp;&emsp;` return 0; `  
` } `  

## Namespace aliases

C++ allows you to create **namespace aliases**, which allow us to temporarily shorten a long sequence of namespaces into something shorter:

` namespace active = foo::goo; `  

One nice advantage of namespace aliases: If you ever want to move the functionality within ` foo::goo ` to a different place, you can just update the ` active ` alieas to reflect the new destination, rather than having to find/replace every instance of ` foo::goo `.

Namespaces in C++ were not originally designed as a way to implement an information hierarchy -- they were designed primarily as a mechanism for preventing naming collisions. As evidence of this, note that the entirety of the standard library lives under the singular namespace std:: (with some nested namespaces used for newer library features).

In general, you should avoid deeply nested namespaces.

## When you should use namespaces

In applications, namespaces can be used to separate application-specific code from code that might be reusable later (e.g. math functions). 

When you write a library or code that you want to distribute to others, always place your code inside a namespace. The code your library is used in may not follow best practices -- in such a case, if your library's declarations aren't in a namespace, there's an elevated chance for naming conflicts to occur. As an additional advantage, placing library code inside a namespace also allows the user to see the contents of your library by using their editor's auto-complete and suggestion feature.
