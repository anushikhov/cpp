# Configuring your compiler: Build configuration

A build configuration (also called a build target) is a collection of project settings that determine how your IDE will build your project. 

The build configuration typically includes things like what the executable will be named, what directories the IDE will look in for other code and library files, whether to keep or strip out debugging information, how much to have the compiler optimize your program, etc.

The debug configuration is designed to help you debug your program. It turns off all optimizations, and includes debugging information, which makes your programs larger and slower, but much easier to debug. 

The release configuration is designed to be used when releasing your program to the public. It is optimized for size and performance, and doesn't contain the extra debugging information. 

Because the release configuration includes all optimizations, this mode is also useful for testing the performance of your code.

You'll rarely have a reason to, but you can also create your own custom build configurations.

**Best practice**
*Use the debug build configuration when developing your programs. When you're ready to release your executable to others, or want to test performance, use the release build configuration.*


# Configuring your compiler: Compiler extensions

Many compilers implement their own changes to the language. These compiler-specific behaviors are called **compiler extensions**.

Writing a program that makes use of a compiler extension allows you to write programs that are incompatible with the C++ standard. Programs using non-standard extensions generally will not compile on other compilers.

Compiler extensios are often enabled by default. 

**Best practice**
_Disable compiler extensions to ensure your programs (and coding practices) remain compliant with C++ standards and will work on any system._

`clang++ x.cpp -o x -pedantic-errors`


# Configuring your compiler: Warning and error levels

If you have done something that definitely violates the rules of the language, during compilation the compiler willemit an **error**.

The compiler may find code that seems like it might be in error, but the compiler can't be sure. In such cases, the compiler may opt to issue a **warning**.

Warning do not halt compilation, but are notices to the programmer that something seems amiss.

**Best practice**
_Don't let warnings pile up. Resolve them as you encounter them (as if they were errors)._

In rare cases, it may be necessary to explicitly tell the compiler to not generate a particular warning for the line of code in question. C++ does not support an official way to do this, but many individual compilers offer solutions to temporarily disable warnings.

By default, most compilers will only generate warnings about the most obvious issues. However, you can request your compiler be more assertive about providing warning for things it finds strange.

**Best practice**
_Turn your warning levels up to the maximum, especially while you are learning. It will help you identify possible issues._

`clang++ x.cpp -o x -Wall -Weffc++ -Wextra -Wsign-conversion`


## Treat warnings as errors

It is also possible to tell the compiler to treat all warnings as if they were errors (in which case, the compiler will halt compilation if it finds any warnings). This is a good way to enforce the recommendation that you should fix all warnings.

`clang++ x.cpp -o x -Werror`


# Configuring your compiler: Choosing a language standard

Generally, a compiler will pick a standard to default to(often _not_ the most recent language standard). 

If you wish to use a different standard, you'll have to configure your IDE/compiler to do so. These settings are applied to the active project only. You need to set them again when you create a new project.

The language standards are named after the years in which they are finalized (e.g. C++17 was finalized in 2017).

However, when a new language standard is being agreed upon, it's not clear in what year the finalization will take place. Consequently, in-progress language standards are given code names, which are then replaced by the actual names upon finalization of the standard.

Here's a mapping of code names to the final names:
* c++1x = C++11
* c++1y = C++14
* c++1z = C++17
* c++1a = C++20

`clang++ x.cpp -o x -std=c++2a`

