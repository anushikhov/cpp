# More debugging tactics

We offered some criticisms of using statements to print debug text. We can mitigate some of these issues through the following basic techniques:

### Conditionalizing your debugging code

You can use preprocessor directives to make your debugging statements conditional.

You can enable debugging simply by commenting/uncommenting #define SOME_UNIQUE_NAME_HERE. This allows us to reuse previously added debug statements and then just disable them when we're done with them, rather than having to actually remove them from the code. If this were a multifile program, the #define would go in a aheader file that's included into all code files so we can comment/uncomment the #define in a single location and have it propagate to all code files.

This addresses the issue with having to remove debug statements and the risk in doing so, but at the cost of even more code clutter.

Another downside of this approach is that if you make a type or forget to include the header into a code file, some or all of the dubugging for that file may not be enabled. So although this is better than the unconditionalized version, there's sill room to improve.

### Using a logger

An alternative approach to conditionalized debugging via the preprocessor is to send your debugging information to a log file. A **log file** is a file (normally stored on disk) that records events that occur in software. The process of writing information to a log file is called **logging**. Most applications and operating systems write log files that can be used to help diagnose issues that occur.

Log files have a few advantages. Because the information written to a log file is separated from your program's output, you can avoid the clutter caused by mingling your normal output and debug output. Log files can also be easily sent to other people for diagnosis -- so if someone using your software has an issue, you can ask them to send you the log file, and it might help give you a clue where the issue is.

While you can write your own code to create log file and send output to them, you're better off using one of the many existing third-party logging tools available.

E.g. you can make use of the **plog** logger. Plog is implemented as a set of header files, so it's easy to include anywhere you need it, and it's lightweight and easy to use.

` #include <iostream> `  
` #include <plog/Log.h> // Step 1: include the logger headers `  
` #include <plog/Initializers/RollingFileInitializer.h> `  

` int getUserInput() `  
` { `  
`    LOGD << "getUserInput() called"; // LOGD is defined by the plog library `  

`    std::cout << "Enter a number: "; `  
`    int x{}; `  
`    std::cin >> x; `  
`    return x; `  
` } `  

` int main() `  
` { `  
`    plog::init(plog::debug, "Logfile.txt"); // Step 2: initialize the logger `  

`    LOGD << "main() called"; // Step 3: Output to the log as if you were writing to the console `  

`   int x{ getUserInput() }; `  
`   std::cout << "You entered: " << x; `  

`   return 0; `  
` } `

How you include, initialize, and use a logger will vary depending on the specific logger you select.

With plog, logging can be temporarily disabled by changing the init statement to the following:
` plog:: init(plog::none , "Logfile.txt"); // plog::none eliminates writing of most messages, essentially turning logging off `  


