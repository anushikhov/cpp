# Command line arguments

## The need for command line arguments

Many programs need some kind of input to work with. For example, let's say you were writing a program called Thumbnail that read in an image file, and then produced a thumbnail. How would Thumbnail know which images to read and process? The user has to have some way of telling the program which file to open. To do this, you might take this approach:

` // Program: Thumbnail `  
` #include <iostream> `  
` #include <string> `  

` int main() `  
` { `   
&emsp;&emsp;&emsp;` std::cout << "Please enter an image filename to create a thumbnail for: "; `  
&emsp;&emsp;&emsp;` std::string filename{}; `  
&emsp;&emsp;&emsp;` std::cin >> filename; `  

&emsp;&emsp;&emsp;` // open image file `  
&emsp;&emsp;&emsp;` // create thumbnail `  
&emsp;&emsp;&emsp;` // output thumbnail `  
` } `  

However, there is a potential problem with this approach. Every time the program is run, the program will wait for the user to enter input. This may not be a problem if you're manually running this program once from the command line. But it is problematic in other cases, such as when you want to run this program on many files, or have this program run by another program.

Consider the case where you want to create thumbnails for all the image files in a given directory. A good solution here would be to write a program that loops through each filename in the directory, calling Thumbnail once for each file.

Consider the case where you're running a website, and you want to have your website create a Thumbnail every time a user uploads an image to your website. This program isn't set up to accept input from the web, so how would the uploader enter a filename in this case? A good solution here would be to have your web server call Thumbnail automatically after upload.

In both of these cases, we really need a way for an external program to pass in the filename as input to our Thumbnail program when Thumbnail is launched, rather than having Thumbnail wait for the user to enter the filename after it has started.

**Command line arguments** are optional string arguments that are passed by the operating system to the program when it is launched. The program can then use them as input (or ignore them). Much like function parameters provide a way for a function to provide inputs to another function, command line arguments provide a way for people or programs to provide inputs to a program.


### Passing command line arguments

Executable programs can be run on the command line by invoking them by name. In order to pass caommand line arguments, we simply list the command line arguments after the executable name. A program can have multiple command line arguments, separated by spaces. 

If you are running your programs from an IDE, the IDE should provide a way to enter command line arguments.

### Using command line arguments  

Now that you know how to provide command line arguments to a program, the next step is to access them from within a C++ program. The new form of `main()` we use for this takes two arguments (named `argc` and `argv` by convention) as follows:

` int main( int argc, char *argv[]) `  

You will sometimes also see it written as:

` int main(int argc, char** argv) `  

Prefer the first representation, because it's intuitively easier to understand.

**argc** is an integer parameter containing a count of the number of arguments passed to the program (think: argc = argument count). `argc` will always be at least 1, because the first argument is always the name of the program itself. Each command line argument the user provides will cause `argc` to increase by 1.

**argv** is where the actual argument values are stored (think: argv = argument values, though the proper name is "argument vectors"). `argv` is really just an array of C-style strings. The length of this array is `argc`.

` #include <iostream> `  

` int main(int argc, char* argv[]) `  
` { `  
&emsp;&emsp;&emsp;` std::cout << "There are " << argc << " arguments:\n"; `  

&emsp;&emsp;&emsp;` // Loop through each argument and print its number and value `  
&emsp;&emsp;&emsp;` for(int count{ 0 }; count < argc; ++count) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << count << ' ' << argv[count] << '\n'; `  
&emsp;&emsp;&emsp;` } `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

Argument 0 is the path and name of the current program being run. The arguments that follow are the command line parameters we pass in.

### Dealing with numeric arguments   

Command line arguments are always passed as strings, even if the value provided is numeric in nature. To use a command line argument as a number, you must convert it from a string to a number. Unfortunately, C++ makes this a little more difficult than it should be.

The C++ way to do this follow: 

` #include <iostream> `  
` #include <sstream> // for std::stringstream `  
` #include <string> `  

` int main(int argc, char *argv[]) `  
` { `  
&emsp;&emsp;&emsp;` if(argc <= 1 ) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` // On some operating systems, argv[0] can end up as an empty string instead of the program's name. `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;`  // We'll conditionalize our response on whether argv[0] is empty or not. `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` if(argv[0]) `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << "Usage: " << argv[0] << " <number> " << '\n'; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` else `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << "Usage: <program name> <number>" << '\n'; `  

&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` return 1; `  
&emsp;&emsp;&emsp;` } `  

&emsp;&emsp;&emsp;` std::stringstream convert{ argv[1] }; // set up a stringstream variable named convert, `  
&emsp;&emsp;&emsp;` // initialized with the input from argv[1] `  

&emsp;&emsp;&emsp;` int myint{}; `  
&emsp;&emsp;&emsp;` if(!(convert >> myint)) // do the conversion `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` myint = 0; // if conversion fails, set myint to a default value `  

&emsp;&emsp;&emsp;` std::cout << "Got integer: " << myint << '\n'; `  

&emsp;&emsp;&emsp;` return 0; `   
` } `  

`std::stringstream` works much like `std::cin`. In this case, we're initializing it with the value of `argv[1]`, so that we can use operator>> to extract the value to an integer variable (the same as we would with `std::cin`).

### The OS parses command line arguments first  

When you type something at the command line (or run your program from the IDE), it is the operating system's responsibility to translate and route that request as appropriate. This not only involves running the executable, it also involves parsing any arguments to determine how they should be handled and passed to the application.

Generally, operating systems have special rules about how special characters like double quotes and backslashes are handled. 

Typically, strings passed in double quotes are considered to be part of the same string.

If you want to include a literal double quote, you have to backslash the double quote.

...  

Command line arguments provide a great way for users or other programs to pass input data into a program at startup. Consider making any input data that a program requires at startup to operate a command line parameter. If the command line isn't passed in, you can always detect that and ask the user for input. That way, your program can operate either way.
