# Bitwise operators

C++ provides 6 bitwise operators for bit manipulation:
![Bitwise operators](https://raw.githubuser.com/anushikhov/cpp/master/learn_cpp/6_Bitwise_Operators/img/bitwise_ops.png)  


## Bitwise left shift (<<) and bitwise right shift (>>) operators

The **bitwise left shift** (<<) operator shifts bits to the left. 

New bits shifted in from the right side receive the value 0. Bits that are shifted off the end of the binary number are lost forever.

0011 << 1 is 0110
0011 << 2 is 1100
0011 << 3 is 1000

The **bitwise right shift** (>>) operator shifts bits to the right.

1100 >> 1 is 0110
1100 >> 2 is 0011
1100 >> 3 is 0001

` #include <bitset> `  
` #include <iostream> `<br/><br/>
` int main() `  
` { `  
&emsp;&emsp;&emsp;` std::bitset<4> x { 0b1100 }; `<br/><br/>
&emsp;&emsp;&emsp;` std::cout << x << '\n'; `  
&emsp;&emsp;&emsp;` std::cout << (x >> 1) << '\n'; `
&emsp;&emsp;&emsp;` std::cout << (x << 1) << '\n'; `<br/><br/>
&emsp;&emsp;&emsp;` return 0; `  
` } `  

The results of applying the bitwise shift operator to a signed integer are compiler dependent prior to C++20. 

**Prior to C++20, don't shift a signed integer (and even then, it's probably still better to use unsigned).**

std::cout has **overloaded** (provided an alternate definition for) operator<< that does console output rather than bit shifting.

When the compiler sees that the left operand of operator<< is std::cout, it knows that it should call the version of operator<< that std::cout overloaded to do output. If the left operand is an integral type, then operator<< knows it should do its usual bit-shifting behavior. The same applies for operator>>.

**If you are using operator << for both output and left shift, parenthesization is required.**

` #include <bitset> `  
` #include <iostream> `<br/><br/>
` int main() `  
` { `  
&emsp;&emsp;&emsp;` std::bitset<4> x{ 0b0110 }; `<br/><br/>
&emsp;&emsp;&emsp;` std::cout << x << 1 << '\n'; // print value of x (0110), then the literal 1 `  
&emsp;&emsp;&emsp;` std::cout << (x << 1) << '\n'; // print x left shifted by 1 (1100) `<br/><br/>
&emsp;&emsp;&emsp;` return 0; `  
` } `  


## Bitwise NOT

The **bitwise NOT** operator (~) simply flips each bit from a 0 to a 1, or vice versa.

The result of a bitwise NOT is dependent on what size your data type is.

Flipping 4 bits:
~0100 is 1011

Flipping 8 bits:
~0000 0100 is 1111 1011

` #include <bitset> `  
` #include <iostream> `<br/><br/>
` int main() `  
` { `  
&emsp;&emsp;&emsp;` std::cout << std::bitset<4>{ ~0b0100u } << ' ' << std::bitset<8>{ ~0b0100u }; `<br/><br/>
&emsp;&emsp;&emsp;` return 0; `  
` } `  


## Bitwise OR and bitwise AND

` #include <bitset> `  
` #include <iostream> `<br/><br/>
` int main() `  
` { `  
&emsp;&emsp;&emsp;` std::cout << (std::bitset<4>{ 0b0111 } | std::bitset<4>{ 0b0011 } | std::bitset<4>{ 0b001 }); `  &emsp;&emsp;&emsp;` std::cout << (std::bitset<4>{ 0b0111 } & std::bitset<4>{ 0b0011 } & std::bitset<4>{ 0b001 }); `<br/><br/>
` return 0; `  
` } `  


## Bitwise XOR

The **bitwise XOR (^)**, also known as **exclusive or** evaluates to true (1) if one and only one of its operands is true. If neither or both are true, it evaluates to 0. In the case of compound XOR expressions, If there are an even number of 1 bits (in a column), the result is 0, if there are an odd number of 1 bits in a column, the result is 1.


## Bitwise assignment operators

Similar to the arithmetic assignment operators, C++ provides bitwise assignment operators in order to facilitate easy modification of variables.

![Bitwise assignment operators](https://raw.githubusercontent.com/anushikhov/cpp/master/learncpp_com/6_Bit_Manipulation/img/bitwise_assignment_ops.png)

For example, instead of writing x = x >> 1;, you can write x >>= 1;. 
