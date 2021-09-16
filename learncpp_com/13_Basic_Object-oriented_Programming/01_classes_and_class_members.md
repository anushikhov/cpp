# Classes and class members

One of C++'s more useful features is the ability to define your own data types that better correspond to the problem being solved, such as enumerated types and structs.

Here's an example of a struct used to hold a date:

` struct DateStruct `  
` { `  
&emsp;&emsp;&emsp;` int year{}; `  
&emsp;&emsp;&emsp;` int month{}; `  
&emsp;&emsp;&emsp;` int day{}; `  
` }; `  

Enumerated types and data-only structs (structs that only contain variables) represent the traditional non-object-oriented programming world, as they can only hold data. We can create and initialize this struct as follows:

` DateStruct today { 2021, 09, 10 }; // uniform initialization `  

If we want to print the date to the screen, we write a function to do this.

` #include <iostream> `  

` struct DateStruct `  
` { `  
&emsp;&emsp;&emsp;` int year{}; `  
&emsp;&emsp;&emsp;` int month{}; `  
&emsp;&emsp;&emsp;` int day{}; `  
` }; `  

` void print(const DateStruct &date) `  
` { `  
&emsp;&emsp;&emsp;` std::cout << date.year << '\' << date.month << '\' << date.day; `  
` } `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` DateStruct today { 2020, 10, 14 }; `  

&emsp;&emsp;&emsp;` today.day = 16; `  

&emsp;&emsp;&emsp;` print(today); `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  


## Classes 

In the world of OOP, we often want our types to not only hold data, but provide functions to work with the data as well. In C++, this is typically done via the **class** keyword. The class keyword defines a new user-defined type called a class.

In C++, classes and structs are essentially the same. In fact, the following struct and class are effectively identical:

` struct DateStruct `  
` { `  
&emsp;&emsp;&emsp;` int year{}; `  
&emsp;&emsp;&emsp;` int month{}; `  
&emsp;&emsp;&emsp;` int day{}; `  
` }; `  

` class DateClass `  
` { `  
` public: `  
&emsp;&emsp;&emsp;` int m_year{}; `  
&emsp;&emsp;&emsp;` int m_month{}; `  
&emsp;&emsp;&emsp;` int m_day{}; `  
` }; `  

Just like a struct declaration, a class declaration does not allocate any memory. It only defines what the class looks like.

Class (and struct) definitions are like a blueprint -- they describe what the resulting object will look like, but they do not actually create the object. To actually create an object of the class, a variable of that class type must be defined:

` DateClass today { 2020, 10, 14 }; // declare a variable of class DateClass `  

Initialize the member variables of a class at the point of declaration.

## Member functions

In addition to holding data, classes (and structs) can also contain functions. Functions defined inside of a class are called **member functions** (or sometimes **methods**). Member functions can be defined inside or outside of the class definition. 

` class DateClass `  
` { `  
` public: `  
&emsp;&emsp;&emsp;` int m_year{}; `  
&emsp;&emsp;&emsp;` int m_month{}; `  
&emsp;&emsp;&emsp;` int m_day{}; `  

&emsp;&emsp;&emsp;` void print() `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << m_year << '/' << m_month << '/' << m_day; `  
&emsp;&emsp;&emsp;` } `  
` }; `  

Just like members of a struct, members of a class are accessed using the member selector operator (.):

` #include <iostream> `  

` class DateClass `  
` { `  
` public: `  
&emsp;&emsp;&emsp;` int m_year{}: `  
&emsp;&emsp;&emsp;` int m_month{}; `  
&emsp;&emsp;&emsp;` int m_day{}; `  

&emsp;&emsp;&emsp;` void print() `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << m_year << '/' << m_month << '/' << m_day; `  
&emsp;&emsp;&emsp;` } `  
` }; `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` DateClass today { 2020, 10, 14 }; `  

&emsp;&emsp;&emsp;` today.m_day = 16; `  

&emsp;&emsp;&emsp;` today.print(); `  

&emsp;&emsp;&emsp;` return 0; `   
` } `  

All member function calls must be associated with an object of the class.

The associated object is essentially implicitly passed to the member function. For this reason, it is often called **the implicit object**.

With non-member functions, we have to pass data to the function to work with. With member functions, we can assume we always have an implicit object of the class to work with. With member functions, we can assume we always have an implicit object of the class to work with.

Using the "m_" prefix for member variables helps distinguish member variables from function parameters or local variables inside member functions. This is useful for several reasons. First, when we see an assignment to a variable with the "m_" prefix, we know that we are changing the state of the class instance. Second, unlike function parameters or local variables, which are declared within the function, member variables are declared in the class definition. Consequently, if we want to know how a variable with the "m_" prefix is declared, we know that we should look in the class definition instead of within the function.

By convention, class names should begin with an upper-case letter.

Here's another example of a class:

` #include <iostream> `  
` #include <string> `  

` class Employee `  
` { `  
` public: `  
&emsp;&emsp;&emsp;` std::string m_name{}; `  
&emsp;&emsp;&emsp;` int m_id{}; `  
&emsp;&emsp;&emsp;` double m_wage{}; `  

&emsp;&emsp;&emsp;` void print() `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << "Name: " << m_name << " Id: " << m_id << " Wage: $" << m_wage << '\n'; `  
&emsp;&emsp;&emsp;` } `  
` }; `   

` int main() `  
` { `  
&emsp;&emsp;&emsp;` Employee alex{ "Alex", 1, 25.00 }; `  
&emsp;&emsp;&emsp;` Employee joe{ "Joe", 2, 22.25 }; `  

&emsp;&emsp;&emsp;` alex.print(); `  
&emsp;&emsp;&emsp;` joe.print(); `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

With normal non-member functions, a function cannot call a function that is defined "below" it (without a forward declaration). With member functions, this limitation doesn't apply:

` class foo `  
` { `  
` public: `  
&emsp;&emsp;&emsp;` void x() { y(); } `  

&emsp;&emsp;&emsp;` void y() {}: `  
` }; `  

## Member types

In addition to member variables and member functions, classes can have **member types** or **nested types** (including type aliases). 

In the following example, we're creating a calculator where we can swiftly change the type of number it's using if we ever need to.

` #include <iostream> `  
` #include <vector> `  

` class Calculator `  
` { `  
` public: `  
&emsp;&emsp;&emsp;` using number_type = int; `  

&emsp;&emps;&emsp;` std::vector<number_type> m_resultHistory{}; `  

&emsp;&emsp;&emsp;` number_type add(number_type a, number_type b) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` auto result{ a + b }; `  

&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` m_resultHistory.push_back(result); `  

&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` return result; `  
&emsp;&emsp;&emsp;` } `  
` }; `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` Calculator calculator; `  

&emsp;&emsp;&emsp;` std::cout << calculator.add(3, 4) << '\n'; `  
&emsp;&emsp;&emsp;` std::cout << calculator.add(99, 24) << '\n'; `  

&emsp;&emsp;&emsp;` for(Calculator::number_type result : calculator.m_resultHistory) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << result << '\n'; `  
&emsp;&emsp;&emsp;` } `  

&emsp;&emsp;&emsp;` return 0; `  

` } `  

In such a context, the class name effectively acts like a namespace for the nested type. From inside the class, we only need reference `number_type`. From outside the class, we can access the type via `Calculator::number_type`.

When we decide that an `int` no longer fulfills our needs and we want to use a `double`, we only need to update the type alias, rather than having to replace every occurrence of `int` with `double`.

Type alias members make code easier to maintain and can reduce typing. Template classes often make use of type alias members. You've already seen this as `std::vector::size_type`, where `size_type` is an alias for an unsigned integer.

We used a "\_t" suffix for type aliases. For member type aliases, a "\_type" or no suffix at all is more common.

Nested types cannot be forward declared. Generally, nested types should only be used when the nested type is used exclusively within that class. 

Since classes are types, it's possible to nest classes inside other classes.

## A note about structs in C++

In C, structs can only hold data, and do not have associated member functions. In C++, after designing classes (using the class keyword), Bjarne Stroustrup spent some amount of time considering whether structs (which were inherited from C) should be granted the ability to have member functions. Upon consideration, he determined that they should, in part to have a unified ruleset for both. So the above programs could have used `struct` instead of the `class` keyword.

Many developers feel this was the incorrect decision to be made, as it can lead to dangerous assumptions. For example, it's fair to assume a class will clean up after itself (e.g. a class that allocates memory will deallocate it before being destroyed), but it's not safe to assume a struct will.

**Best practice**</br></br>
_Use the struct keyword for data-only structures. Use the class keyword for objects that have both data and functions._  

C++ standard library is full of classes that have been created for your benefit. `std::string`, `std::vector`, and `std::array` are all class types. So when you create an object of any of these types, you're instantiating a class object. And when you call a function using these objects, you're calling a member function.

` #include <string> `  
` #include <array> `  
` #include <vector> `  
` #include <iostream> `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` std::string s { "Hi" }; // instantiate a string class object `   
&emsp;&emsp;&emsp;` std::array<int, 3> a { 1, 2, 3 }; // instantiate an array class object `  
&emsp;&emsp;&emsp;` std::vector<double> v { 1.1, 2.2, 3.3 }; // instantiate a vector class object `  

&emsp;&emsp;&emsp;` std::cout << "length: " << s.length() << '\n'; // call a member function `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  
