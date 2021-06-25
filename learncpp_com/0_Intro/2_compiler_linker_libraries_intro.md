# Introduction to the compiler, linker, and libraries

The C++ compiler checks your code to make sure it follows the rules of the C++ language. If it doesn't, the compiler will give you and error to help pinpoint what needs fixing. The compilation process will be aborted until the error is fixed. If there are no syntax errors it will translate the C++ source code into a machine language file called an object file.

The linker takes all the object files and combines them into a single executable program, links library files and makes sure all cross-file dependencies are resolved properly. 
If the linker is unable to connect a reference to something with its definition, you'll get a linker error, and the linking process will abort.

A library file is a collection of precompiled code that has been "packaged up" for reuse in other programs.

For complex projects, some development environments use a makefile, which is a file that describes how to build a program (e.g. which files to compile and link, or otherwise process in various ways). 
