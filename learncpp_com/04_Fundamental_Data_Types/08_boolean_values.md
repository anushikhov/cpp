# Boolean values

Boolean variables are variables that can have only two possible values: true, and false. The type is called Boolean after the name of its inventor, George Boole, and is properly capitalized in the English language.

To declare a Boolean variable, we use the keyword **bool**.

Just as the unary operator (-) can be used to make an integer negative, the logical NOT operator (!) can be used to flip a Boolean value from _true_ to _false_, or vice versa.

Because Booleans actually store integers, they are considered an integral type.

When we print Boolean values with std::cout, std::cout prints 0 for _false_, and 1 for _true_.

You can use _std::boolalpha_, to print "true" or "false" instead of 0 or 1.

` #include <iostream> `  
` `  
` int main() `  
` { `  
`    std::cout << true << '\n'; `  
`    std::cout << false << '\n'; `  
` `  
`    std::cout << std::boolalpha; // print bools as true or false `  
` `  
`    std::cout << true << '\n'; `  
`    std::cout << false << '\n'; `  
` `  
`    return 0; `  
` } `  

You can use _std::noboolalpha_ to turn it back off.

## Integer to Boolean conversion

You cannot initialize a Boolean with an integer using uniform initialization. However, in any context where an integer can be converted to a Boolean, the integer 0 is converted to false, and any other integer is converted to true.

std::cin only accepts two inputs for boolean variables: 0 and 1 (not true or false). Any other inputs will cause std::cin to silently fail. A failed input will also zero-out the variable.

To make std::cin accept "false" and "true" as inputs, the std::boolalpha option has to be enabled. However, when std::boolalpha is enabled, "0" and "1" will no longer be treated as booleans.

## Boolean return values

Boolean values are often used as the return values for functions that check whether something is true or not. Such functions are typically named starting with the word _is_ (e.g. isEqual) or _has_ (e.g. hasCommonDivisor).
