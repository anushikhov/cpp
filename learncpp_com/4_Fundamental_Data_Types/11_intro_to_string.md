# An introduction to std::string

A **string** is a collection of sequential characters.

Strings are a compound type and are defined in the C++ standard library rather than as part of the core language.

To use strings in C++, we first need to #include the <string> header to bring in the declarations for std::string. Once that is done, we can define variables of type std::string.

Empty strings will print nothing:

` std::string empty{ }; `  
` std::cout << empty << '\n'; `  

When using operator>> to extract a string from cin, operator>> only returns characters up to the first whitespace it encounters. Any other characters are left inside std::cin, waiting for the next extraction.

## Use std::getline() to input text

To read a full line of input into a string, you're better off using the `std::getline()` function instead. std::getline() takes two parameters: the first is std::cin, and the second is your string variable.

` std::getline(std::cin >> std::ws, name); `  

Besides output manipulators, C++ also supports input manipulators (defined in the iomanip header), which alter the way that input is accepted. The std::ws input manipulator tells std::cin to ignore any leading whitespace. std::ws is not a function.

**Best practice**
_If using std::getline to read strings, use the std::ws input manipulator to ignore leading whitespace._

**Using the extraction operator(>>) with std::cin ignores leading whitespace. std::getline does not ignore leading whitespace unless you use input manipulator std::ws.**

To get a string's length, use the std::string's length() member function.
