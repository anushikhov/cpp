# Constructor member iniitializer lists

Assigning values to const or reference member variables in the body of the constructor is not possible in some cases.

## Member initializer lists  

To solve this problem, C++ provides a method for initializing class member variables (rather than assigning values to them after they are created) via a **member initializer list** (often called a "member initialization list"). Do not confuse these with the similarly named initializer list that we can use to assign values to arrays.

Using an initialization list is almost identical to doing direct initialization or uniform initialization.

` class Something `  
` { `  
` private: `  
&emsp;&emsp;&emsp;` int m_value1 {}; `   
&emsp;&emsp;&emsp;` double m_value2 {}; `  
&emsp;&emsp;&emsp;` char m_value3 {}; `  

` public: `  
&emsp;&emsp;&emsp;` Something() : m_value1{ 1 }, m_value2{ 2.2 }, m_value3{ 'c' } // Initialize member variables `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;` // No need for assignment here `  
&emsp;&emsp;&emsp;` } `  

&emsp;&emsp;&emsp;` void print() `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << "Something(" << m_value1 << ", " << m_value2 << ", " << m_value3 << ")\n"; `  
&emsp;&emsp;&emsp;` } `  
` }; `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` Something something{}; `  
&emsp;&emsp;&emsp;` something.print(); `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

We no longer need to do the assignments in the constructor body, since the member initializer list replaces that functionality.

Of course, constructors are more useful when we allow the caller to pass in the initialization values:

` class Something `  
` { `  
` private: `  
&emsp;&emsp;&emsp;` int m_value1 {}; `   
&emsp;&emsp;&emsp;` double m_value2 {}; `  
&emsp;&emsp;&emsp;` char m_value3 {}; `  

` public: `  
&emsp;&emsp;&emsp;` Something(int value1, double value2, char value3='c') : m_value1{ value1 }, m_value2{ value2 }, m_value3{ value3 } // Directly initialize  member variables `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;` // No need for assignment here `  
&emsp;&emsp;&emsp;` } `  

&emsp;&emsp;&emsp;` void print() `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << "Something(" << m_value1 << ", " << m_value2 << ", " << m_value3 << ")\n"; `  
&emsp;&emsp;&emsp;` } `  
` }; `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` Something something{ 1, 2.2 }; `  
&emsp;&emsp;&emsp;` something.print(); `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

**Use member initializer lists to initialize your class member variables instead of assignment.**  

## Initializing array members with member initializer lists

Consider a class with an array member:

` class Something `  
` { `  
` private: `  
&emsp;&emsp;&emsp;` const int m_array[5]; `  
` }; `  

Prior to C++11, you can only zero an array member via a member initialization list:

` class Something `  
` { `  
` private: `  
&emsp;&emsp;&emsp;` const int m_array[5]; `  

` public: `  
&emsp;&emsp;&emsp;` Something(): m_array {} // zero the member array `  
&emsp;&emsp;&emsp;` { `   
&emsp;&emsp;&emsp;` } `  

` }; `  

However, since C++11, you can fully initialize a member array using uniform initialization: 

` class Something `  
` { `  
` private: `  
&emsp;&emsp;&emsp;` const int m_array[5]; `  

` public: `  
&emsp;&emsp;&emsp;` Something(): m_array { 1, 2, 3, 4, 5 } // uniform initialization to initialize the member array `   
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;` } `  
` }; `  

## Initializing member variables that are classes

A member initialization list can also be used to initialize members that are classes.

` #include <iostream> `  

` class A `  
` { `  
` public: `  
&emsp;&emsp;&emsp;` A(int x = 0) { std::cout << "A " << x << '\n'; } `  
` }; `  

` class B `  
` { `  
` private: `   
&emsp;&emsp;&emsp;` A m_a {}; `  
` public: `  
&emsp;&emsp;&emsp;` B(int y) : m_a{ y - 1 } // call A(int) constructor to initialize member m_a `   
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << "B " << y << '\n'; `   
&emsp;&emsp;&emsp;` } `  
` }; `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` B b{ 5 }; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

When variable b is constructed, the `B(int)` constructor is called with value 5. Before the body of the constructor executes, `m_a` is initialized, calling the `A(int)` constructor with value 4. This prints "A 4". Then control returns back to the `B` constructor, and the body of the `B` constructor executes, printing "B 5".

## Formatting your initializer lists

C++ gives you a lot of flexibility in how to format your initializer lists, and it's really up to you how you'd like to proceed. But here are some recommendations:

* If the initializer list fits on the same line as the function name, then it's fine to put everything on one line.  
* If the initializer list doesn't fit on the same line as the function name, then it should go indented on the next line.  
* If all of the initializers don't fit on a single line (or the initializers are non-trivial), then you can space them out, one per line.  

## Initializer list order  

Variables in the initializer list are not initialized in the order that they are specified in the initilizer list. Instead, they are intialized in the order in which they are declared in the class.

For best results, the following recommendations should be observed:
1. Don't initialize member variables in such a way that they are dependent upon other member variables being initialized first (in other words, ensure your member variables will properly initialize even if the initialization ordering is different).
1. Initialize variables in the initializer list in the same order in which they are declared in your class. This isn't strictly required so long as the prior recommendation has been followed, but your compiler may give you a warning if you don't do so.

...  

Member initializer lists allow us to initialize our members rather than assign values to them. This is the only way to initialize members that require values upon initialization, such as const or reference members, and it can be more performant than assigning values in the body of the constructor. Member initializer lists work both with fundamental types and members that are classes themselves.
