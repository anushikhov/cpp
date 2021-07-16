# std::cin and handling invalid input

As you write programs, you should always consider how users will (unintentionally or otherwise) misuse your programs. A well-written program will anticipate how users will misuse it, and either handle those cases gracefully or prevent them from happening in the first place (if possible) A program that handles error cases well is said to be **robust**.


## std::cin, buffers, and extraction

When the user enters input in response to an extraction operation, that data is placed in a buffer inside of std::cin. A **buffer** (also called a data buffer) is simply a piece of memory set aside for storing data temporarily while it's moved from one place to another. In this case, the buffer is used to hold user input while it's waiting to be extracted to variables.

When the extraction operator is used, the following procedure happens:

* If there is data already in the input buffer, that data is used for extraction.
* If the input buffer contains no data, the user is asked to input data for extraction (this is the case most of the time). When the user hits enter, a '\n' character will be placed in the input buffer.
* operator>> extracts as much data from the input buffer as it can into the variable (ignoring any leading whitespace characters, such as spaces, tabs, or '\n').
* Any data that can not be extracted is left in the input buffer for the next extraction.

Extraction succeeds if at least one character is extracted from the input buffer. Any unextracted input is left in the input buffer for future extractions.

Extraction fails if the input data does not match the type of the variable being extracted to.


## Validating input

The process of checking whether user input conforms to what the program is expecting is called **input validation**.

There are three basic ways to do input validation:

* Inline (as the user types)   
&emsp;&emsp;&emsp; * Prevent the user from typing invalid input in the first place.    
* Pose-entry (after the user types)   
&emsp;&emsp;&emsp; * Let the user enter whatever they want into a string, then validate whether the string is correct, and if so, covert the string to the final variable format.   
&emsp;&emsp;&emsp; * Let the user enter whatever they want, let std::cin and operator>> try to extract it, and handle the error cases.    

Some graphical user interfaces and advanced text interfaces will let you validate input as the user enters it (character by character). Generally speaking, the programmer provides a validation function that accepts the input the uas has entered so far and returns true if the input is valid, and false otherwise. This function is called every time the user presses a key. If the validation function returns true, they key the user just pressed is accepted. If the validation function returns false, the character the user just input is discarded (and not shown on the screen). Using this method, you can ensure that any input the user enters is guaranteed to be valid, because any invalid keystrokes are discovered and discarded immediately. std::cin does not support this style of validation.

Since strings do not have any restrictions on what characters can be entered, extraction is guaranteed to succeed (though std::cin stops extraction at the first non-leading whitespace character). Once a string is entered, the program can then parse the string to see if it is valid or not. However, parsing strings and converting string input to other types (e.g. numbers) can be challenging, so this is only done in rare cases.

Most often, we let the user enter whatever they want, have std::cin and operator>> try to extract it, and deal with the failout if it fails. 


## Types of invalid text input

We can generally separate input text errors into four types:

* Input extraction succeeds but the input is meaningless to the program .
* Input extraction succeeds but the user enters additional input.
* Input extraction fails.
* Input extraction succeeds but the user overflows a numeric value.

To make our programs robust, whenever we ask the user for input, we ideally should determine whether each of the above can possibly occur, and if so, write code to handle those cases.

### Error case 1: Extraction succeeds but the input is meaningless

The solution here is to do input validation. This usually consists of 3 steps:

1. Check whether the user's input was what you were expecting.
1. If so, return the value to the caller.
1. If not, tell the user something when wrong and have them try again.

` char getOperator() `  
` { `  
&emsp;&emsp;&emsp;` while(true) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << "Enter one of the following: +, -, *, or /: "; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` char operation(); `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cin >> operation; `  

&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` switch(operation) `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` case '+': `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` case '-': `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` case '*': `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` case '/': `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` return operation; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` default: `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << "The input is invalid. Try again.\n"; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` } `  
&emsp;&emsp;&emsp;` } `  
` } `  

We're using a while loop to continuously loop until the user provides valid input. If they don't, we ask them to try again until they either give us valid input, shutdown the program, or destroy their computer.

### Error case 2: Extraction succeeds but with extraneous input

To ignore entered extraneous characters:

` std::cin.ignore(100, '\n'); // clear up to 100 characters out of the buffer, or until a '\n' character is removed `  

This call would remove up to 100 characters.

To ignore all characters up to the next '\n', we can pass ` std::numeric_limits<std::streamsize>::max() ` to ` std::cin.ignore() `. 

` std::numeric_limits<std::streamsize>::max() ` returns the largest value that can be stored in a variable of type ` std::streamsize `. 

Passing this value to ` std::cin.ignore() ` causes it to disable the count check.

To ignore everything up to a and including the next '\n' character, we call:

` std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); `  

Because this line is quite long for what it does, it's handly to wrap it in a function which can be called in place of ` std::cin.ignore() `.

` #include <limits> // for std::numeric_limits `  

` void ignoreLine() `  
` { `  
&emsp;&emsp;&emsp;` std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); `  
` } `  

Since the last character the user entered must be a '\n', we can tell `std::cin` to ignore buffered characters until it finds a newline character (which is removed as well).

### Error case 3: Extraction fails

When the user enters an invalid input, it is left in the buffer and `std::cin` goes into "failure mode". Once in "failure mode", future requests for input extraction will sirently fail. The  program simply runs to the end and then terminates.

We can detect whether an extraction has failed and fix it:

` if(std::cin.fail()) `  
` { `  
&emsp;&emsp;&emsp;` std::cin.clear(); `  
&emsp;&emsp;&emsp;` ignoreLine(); `  
` } `  

Integrating that into a function:

` double getDouble() `  
` { `  
&emsp;&emsp;&emsp;` while(true) `   
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << "Enter a double value: "; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` double x{}; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cin >> x; `  

&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` if(std::cin.fail()) `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cin.clear(); `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` ignoreLine(); `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` } `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` else `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` ignoreLine(); `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` return x; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` } `  
&emsp;&emsp;&emsp;` } `  
` } `  

Prior to C++11, a failed extraction would not modify the variable being extracted to. This means that if a variable was uninitialized, it would stay uninitialized in the failed extraction case. However, as of C++11, a failed extration due to invalid input will cause the variable to be zero-initialized, i.e. the variable is set ot 0, 0.0, "", or whatever value 0 converts to for that type.

### Error case 4: Extraction succeeds but the user overflows a numerica value

In this case, `std::cin` goes immediately into "failure mode", but also assigned the closest in-range value to the variable. Additional inputs are skipped, leaving other variables zero-initialized. This case can be handled the same was as a filed extraction.

As of C++11, an out-of-range failed extraction will cause the variable to be set to the closest in-range value.


## Putting it all together

` #include <iostream> `  
` #include <limits> `  

` void ignoreLine() `  
` { `  
&emsp;&emsp;&emsp;` std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); `  
` } `  

` double getDouble() `  
` { `  
&emsp;&emsp;&emsp;` while(true) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << "Enter a double value: "; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` double x{}; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cin >> x; `  

&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` if(std::cin.fail()) `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cin.clear(); `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` ignoreLine(); `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << "Invalid input. Please try again.\n"; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` } `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` else `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` ignoreLine(); `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` return x; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` } `  
&emsp;&emsp;&emsp;` } `  
` } `  

` char getOperator() `  
` { `  
&emsp;&emsp;&emsp;` while(true) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << "Enter one of the following: +, -, *, or /: "; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` char operation{}; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cin >> operation; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` ignoreLine(); `  

&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` switch(operation) `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` case '+': `    
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` case '-': `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` case '*': `    
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` case '/': `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` return operation; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` default: `    
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << Invalip input. Please try again.\n"; `    
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` } `  
&emsp;&emsp;&emsp;` } `  
` } `  

` void printResult(double x, char operation, double y) `  
` { `  
&emsp;&emsp;&emsp;` switch(operation) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` case '+': `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << x << " + " << y << " is " << x + y << '\n'; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` break; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` case '-': `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << x << " - " << y << " is " << x - y << '\n'; `   
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` break; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` case '*': `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << x << " * " << y << " is " << x * y << '\n'; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` break; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` case '/': `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << x << " / " << y << " is " << x / y << '\n'; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` break; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` default: `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cerr << "Something went wrong: printResult() got an invalid operator.\n"; `  
&emsp;&emsp;&emsp;` } `  
` } `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` double x{ getDouble() }; `  
&emsp;&emsp;&emsp;` char operation{ getOperator() }; `  
&emsp;&emsp;&emsp;` double y{ getDouble() }; `  

&emsp;&emsp;&emsp;` printResult(x, operation, y); `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  


## Conclusion

As you write your programs, consider how users will misuse your program, especially around text input. For each point of text intput, consider:

* Could extraction fail?
* Could the user enter more input than expected?
* Could the user enter meaningless input?
* Could the user overflow an input?

You can use if statements and boolean logic to test whether input is expected and meaningful.

The following code will clear any extraneous input:

` std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); `  

The following code will test for and fix failed extractions or overflow: 

` if(std::cin.fail()) `  
` { `  
&emsp;&emsp;&emsp;` std::cin.clear(); `  
&emsp;&emsp;&emsp;` std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); `  
` } `  

Use loops to ask the user to re-enter input if the original input was invalid.
