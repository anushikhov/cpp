# Programs with multiple code files

As programs get larger, it is common to split them into multiple files for organization and reusability purposes.

When you compile your program, you'll need to include all of the relevant code files on the compile line.

` clang++ main.cpp add.cpp -o main `  

The compiler compiles each file individually. It does not know about the contents of other code files, or remember anything it has seen from previously compiled code files.This limited visibility and short memory is intentional, so that files may have functions or variables that have the same names without conflicting with each other.

When the compiler compiles a multi-file program, it may compile the files in any order. It compiles each file individually, with no knowledge of what is in other files.
