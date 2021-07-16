# Void

**void** means "no type". Consequently, variables cannot be defined with a type of void. 

Void is typically used in several different contexts.

### Functions that do not return a value

Most commonly, _void_ is used to indicate that a function does not return a value. If you use a return statement to try to return a value in such a function, a compile error will result.

### Deprecated: Functions that do not take parameters

In C, void is used as a way to indicate taht a function does not take any parameters:

` int getValue(void)  // void here means no parameters `  
` { `  
`    int x{}; `  
`    std::cin >> x; `  
`    return x; `  
` } `  

Although this will compile in C++ (for backward compatibility reasons), this use of keyword _void_ is considered deprecated in C++. 

**Best practice**
_Use an empty parameter list instead of void to indicate that a function has no parameters._


