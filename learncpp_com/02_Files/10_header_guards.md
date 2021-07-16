# Header guards

#### The duplicate definition problem

Variables or function identifier can only have one definition (the one definition rule). Thus, a program that defines a variable identifier or a function more than once will cause a compile error.

With header files, it's quite easy to end up in a situation where a definition in a header file gets included more than once. This can happen when a header file #includes another header file (which is common).


### Header guards

We can avoid the above problem via a mechanism called a **header guard** (also called an **include guard**). Header guards are conditional compilation directives that take the following form:
` #ifndef SOME_UNIQUE_NAME_HERE `  
` #define SOME_UNIQUE_NAME_HERE `  

` // your declarations (and certain types of definitions) here `  

` #endif `  

When this header is #included, the preprocessor checks whether SOME_UNIQUE_NAME_HERE has been previously defined. If this is the first time we're including the header, SOME_UNIQUE_NAME_HERE will not have been defined. Consequently, it #defines COME_UNIQUE_NAME_HERE and includes the contents of the file. If the header is included again into the same file, SOME_UNIQUE_NAME_HERE will already have been defined from the first time the contents of the header were included, and the contents of the header will be ignored (thanks to the #ifndef).

**All of your header files should have header guards on them. By convention the name is set to the full filename of the header file, typed in all caps, using underscores for spaces or punctuation.**

Even the standard library headers use header guards. 

In large programs, it's possible to have two separate header files (included from different directories) that end up having the same filename (e.g. directoryA/config.h and directoryB/config.h). If only the filename is used for the include guard (e.g. CONFIG_H), these two files may end up using the same guard name. If that happens, any file that includes (directly or indirectly) both config.h files will not receive the contents of the include file to be included second. This will probably cause a compilation error.

Because of this possibility for guard name conflicts, many developers recommend using a more complex/unique name in your header guards. Some good suggestions are a naming convention of < PROJECT >\_< PATH >\_< FILE >\_H, < FILE >\_< LARGE RANDOM NUMBER >\_H, or < FILE >\_< CREATION DATE >\_H

#### Header guards do not prevent a header from being included once into different code files

The goal of header guards is to prevent a code file from receiving more than one copy of a guarded header. By design, header guards do not prevent a given header file from being included (once) into separate code files. This can also cause unexpected problems. You you include the same header file which contains a function definition into two source files, you will get a linker error. The best way to work around this issue is simply to put the function definition in one of the .cpp files so that the header just contains a forward declaration.

Generally you should not include function definitions into your headers. There are quite a few cases where it's necessary to put non-function definitions in a header files. For example, **user-defined types are typically defined in header files, so the definition can be propagated out to the code files that need to use them. Without a header guard, your code files can end up with multiple identical copies of these definitions, which will cause a duplicate definition compilation error.**


### #pragma once

Many compilers support a simpler; alternate form of header guards using the #pragma directive:

` #pragma once `  
` // your code here `  

\#pragma once serves the same purpose as header guards, and has the added benefit of being shorter and less error-prone. Howeverit is not an official part of the C++ language, and not all compilers support it. For compatibility purposes stick to traditional header guards. They aren't much more work and they're guaranteed to be supported on all compliant compilers.

...

Header guards are designed to ensure that the contents of a given header file are not copied more than once into any single file, in order to prevent duplicate definitions.

Even if your header file is composed of all declarations it's still a best practice to include header guards.
Header guards do not prevent the contents of a header file from being copied (once) into separate project files. This is a good thing, because we often need to reference the contents of a given header from different project files.

...
add.h

` #ifndef ADD_H `  
` #define ADD_H `  

` int add(int x, int y); `  

` #endif `
