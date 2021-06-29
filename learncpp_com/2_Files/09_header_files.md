# Header files

### Headers, and their purpose

C++ code files (with a .cpp extension) are not the only files commonly seen in C++ programs. The other type of file is called a **header file**. Header files usually have a .h extension, but you will occasionally see them with a .hpp extension or no extension at all. The primary purpose of a header file is to propagate declarations to code files.

**Header files allow us to put declarations in one location and then import them wherever we need them. This can save a lot of typing in multi-file programs.**

**When you #include a file, the content of the included file is inserted at the point of inclusion. This provides a useful way to pull in declarations from another file.**

Header files typically only contain function and variable declarations, not function and variable definitions (otherwise a violation of the _one definition rule_ could result), std::cout is forward declared in the iostream header, but defined as part of the C++ standard library, which is automatically linked into your program during the linker phase.

!(iostream header file)[https://raw.githubusercontent.com/anushikhov/cpp/main/2_Files/img/header.png]

**Best practice**
_Header files should generally not contain function and variable definitions, so as not to violate the one definition rule. An exception is made for specific constants._


### Writing your own header files

Manually adding forward declarations for every function you want to use that lives in another file can get tedious quickly. We can write header files to avoid this. Header files only consist of two parts:

1. A _header guard_
1. The actual content of the header file, which should be the forward declarations for all of the identifiers we want other files to be able to see.

**Best practice**
_Use a .h suffix when naming your header files._

Header files are often paired with code files, with the header file providing forward declarations for the corresponding code file.

**Best practice**
_If a header file is paired with a code file, they should both have the same base name._

In order to use our header files in our source files, we need to #include them using quotes, not angle brackets.


### Including a header in the corresponding source file

Including the header in the source file increases forward compatibility. It's very likely that in the future, you'll add more functions or modify existing ones in a way that they need to know about the existence of each other.

If you need an include in a header, you probably need it for a function declaration. This means that you'll also need the same include in the source file. This would lead to you having a copy of your header's includes in your source file. **By including your header in your source file, the source file has access to everything the header had access to.**

**In library development, including your header in your source file can even help to catch errors early.**

**Best practice**
_When writing a source file, include the corresponding header (if one exists), even if you don't need it yet._


#### Angled brackets vs double quotes

It's possible that a header file with the same filename might exist in multiple directories. Our use of angled brackets vs double quotes helps give the compiler a clue as to where it should look for header files.

When we use angled brackets, we're telling the preprocessor that this is a header file we didn't write ourselves. The compiler will search for the header only in the directories specified by the include directories. The include directories are configured as part of your project/IDE settings/compiler settings, and typically default to the directories containing the header files that come with your compiler and/or OS. The compiler will not search for the header file in your project's source code directory.

When we use double-quotes, we're telling the preprocessor that this is a header file that we wrote. The compiler will first search for the header file in the current directory. If it can't find a matching header there, it will then search the include directories.

**Use double quotes to include header files that you've written to are expected to be found in the current directory. Use angled brackets to include headers that come with your compiler, OS, or third-party libraries you've installed elsewhere on your system.**


#### Why doesn't iostream have a .h extension?

Standard library header files don't have the .h extension.

When C++ was first created, all of the files in the standard runtime library ended in a .h suffix. When the language was standardized by the ANSI committee, they decided to move all of the functionality in the standard library into the std namespace to help avoid naming conflicts with user-defined identifiers. However, this presented a problem: if they moved all the functionality into the std namespace, noen of the old programs (that included iostream.h) would work anymore. To work around this issue, a new set of header files was introduced that use the same names but lack the .h extension. These new header files have all their functionality inside the std namespace. This way, older programs that include #include <iostream.h> do not need to be rewritte, and newer programs can #include <iostream>.

In addition, many of the libraries inherited from C taht are still useful in C++ were given a _c_ prefix (e.g. _stdlib.h_ became _cstdlib_). The functionality from these libraries was also moved into the std namespace to help avoid naming conflicts.

**Best practice**
_When including a header file from the standard library, use the no extension version (without the .h) if it exists. User-defined headers should still use a .h extension._


#### Including header files from other directories

One bad way to include header files from other directories is to include a relative path to the header file you want to include as part of the #include line. The downside of this approach is that it requires you to reflect your directory structure in your code. If you ever update your directory structure, your code won't work anymore.

A better method is to tell your compiler or IDE that you have a bunch of header files in some other location, so that it will look there when it can't find them in the current directory. This can generally be done by setting an _include path_ or _search directory_ in your IDE project settings.

Using g++/clang++, you can use the -I option to specify an alternative include directory.

` g++ -o main -I/source/includes main.cpp `  

The nice thing about this approach is that if you ever change your directory structure, you only have to change a single compiler or IDE setting instead of every code file.


#### Headers may include other headers

It's common that a header file will need a declaration or definition that lives in a different header file. Because of this, header files will often #include other header files.

When your code file #includes the first header file, you'll also get any other header files that the first header file includes (and any header files those include, and so on). These additional header files are sometimes called **"transitive includes"**, as they're included implicitly rather than explicitly.

The contents of these transitive includes are available for use in your code file. However, you should not rely on the content of headers that are included transitively. The implementation of header files may change over time, or be different across different systems. If that happens, your code may only compile on certain systems, or may compile now but not in the future. This is easily avoided by explicitly including all of the header files the content of your code file requires.

**Best practice**
_Each file shoudl explicitly #include all of the header files it needs to compile. Do not rely on headers included transitively from other headers._

Unfortunately, there is no easy way to detect when your code file is accidently relying on content of a header file that has been included by another header file.


#### The #include order of header files

If your header files are written properly and #include everything they need, the order of inclusion shouldn't matter. However, including your header files in a certain order can help surface mistakes where your header files may not include everything they need.

**Best practice**
_Order your #includes as follows: your own user-defined headers first, then 3rd party library headers, then standard library headers, with the headers in each section sorted alphabetically._

That way, if one of your user-defined headers is missing an #include for a 3rd party library or standard library header; it's more likely to cause a compile error so you can fix it.


## Header file best practices

* Always include header guards
* Do not define variables and functions in header files (global constants are an exception).
* Give your header files the same name as the source files they're associated with.
* Each header file should have a specific job, and be as independent as possible.
* Be mindful of which headers you need to explicitly include for the functionality that you are using in your code files.
* Every header you write should compile on its own (it should #include every dependency it needs).
* Only #include what you need.
* Do not #include .cpp files.
