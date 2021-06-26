# Introduction to iostream: cout, cin, and endl

The **input/output library** (io library) is part of the C++ standard library that deals with basic input and output. 

To use the functionality defined within the _iostream_ library, we need to include the _iostream_ header at the top of any code file that uses the content defined in _iostream_.

The _iostream_ library contains a few predefined variables. One of the most useful is **std::cout**, which allows us to send data to the console to be printed as text, _cout_ stands for "character output".

We use _std::cout_, along with the **insertion operator (<<)**, to send output to the console to be printed.

To print more than one thing on the same line, the insertion operator (<<) can be used multiple times in a single statement to concatenate (link together) multiple pieces of output.

` std::cout << "x is equal to: " << x;`

Separate output statements don't result in separate lines of output on the console.

If we want to print separate lines of output to the console, we need to tell the console when to move the cursor to the next line.

One way to do that is to use _std::endl_. When output with _std::cout_, _std::endl_ prints a newline character to the console (causing the cursor to go to the start of the next line).

Using _std::endl_ can be a bit inefficient, as it actually does two jobs: it moves the cursor to the next line, and it "flushes" the output (makes sure that it shows up on the screen immediately).

_std::cout_ flushes output anyway (and if it doesn't, it usually doesn't matter), so having _std::endl_ flush is rarely important.

Use of the '\n' character is typically preferred instead. 

The '\n' character moves the cursor to the next line, but doesn't do the redundant flush, so it performs better.

The '\n' character also tends to be easier to read since it's both shorter and can be embedded into existing text.

When '\n' is used by itself to move the cursor to the next line, the single quotes are needed.

**Best practice**
_Prefer_ \n _over std::endl when outputting text to the console._

_std::cin_ reads input from keyboard using the **extraction operator (>>)**. The input must be stored in a variable to be used.

` int x{ };
  std::cin >> x;`

You don't need to use '\n' when accepting input, as the user will need to press the _enter_ key to have their input accepted, and this will move the cursor to the next line.

It is also possible to input more than one value on a single line.

` int x{ };
  int y{ };
  std::cin >> x >> y;`
