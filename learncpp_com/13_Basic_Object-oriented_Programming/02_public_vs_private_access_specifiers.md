# Public and private access specifiers

` struct DateStruct // members are public by default `  
` { `  
&emsp;&emsp;&emsp;` int month {}; // public by default, can be accessed by anyone `  
&emsp;&emsp;&emsp;` int day {}; `  
&emsp;&emsp;&emsp;` int year {}; `  
` }; `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` DateStruct date; `  
&emsp;&emsp;&emsp;` date.month = 10; `  
&emsp;&emsp;&emsp;` date.day = 14; `  
&emsp;&emsp;&emsp;` date.year = 2021; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `   

In the `main()` function of the example above, we declare a DateStruct and then we directly access its members in order to assign values to them. This works because all members of a struct are public members by default. **Public members** are members of a struct or class that can be accessed directly by anyone, including from code that exists outside the struct or class. In this case, function `main()` exists outside of the struct, but it can directly access members month, day, and year, because they are public members.

The code outside of a stuct or class is sometimes called **the public**: the public is only allowed to access the public members of a struct or class.

` class DateClass // members are private by default `  
` { `  
&emsp;&emsp;&emsp;` int m_month {}; // prviate by default, can only be accessed by other members `  
&emsp;&emsp;&emsp;` int m_day {}; `  
&emsp;&emsp;&emsp;` int m_year {}; `  
` }; `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` DateClass date; `  
&emsp;&emsp;&emsp;` date.m_month = 10; // error `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

If you were to compile this program, you would receive errors. This is because by default, all members of a class are private. **Private members** are members of a class that can only be accessed by other members of the class (not by the public). Because `main()` is not a member of DateClass, it does not have access to date's private members.

## Access specifiers

Although class members are private by default, we can make them public by using the public keyword.

` class DateClass // members are private by default `  
` { `  
` public: `  
&emsp;&emsp;&emsp;` int m_month {}; // prviate by default, can only be accessed by other members `  
&emsp;&emsp;&emsp;` int m_day {}; `  
&emsp;&emsp;&emsp;` int m_year {}; `  
` }; `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` DateClass date; `  
&emsp;&emsp;&emsp;` date.m_month = 10; `  
&emap;&emsp;&emsp;` date.m_day = 14; `  
&emsp;&emsp;&Emsp;` date.m_year = 2021;`  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

Because DateClass's members are now public, they can be accessed directly be `main()`.

The `public` keyword, along with the following colon, is called an access specifier. **Access specifiers** determine who has access to the members that follow the specifier. Each of the members "acquires" the access level of the previous access specifier (or, if none is provided, the default access specifier).

C++ provides 3 different access specifier keywords: public, private, and protected. Public and private are used to make the members that follow them public members or private members respectively. The third access specifier, protected, works much like private does. We will discuss the difference between the private and protected access specifier when we cover inheritance.

## Mixing access specifiers  

A class can (and almost always does) use multiple access specifiers to set the access levels of each of its members. There is no limit to the number of access specifiers you can use in a class.

In general, member variables are usually made private, and member functions are usually made public.

**Make member variables private, and member functions public, unless you have a good reason not to.**  

` #include <iostream> `  

` class DateClass `  
` { `  
&emsp;&emsp;&emsp;` int m_month {}; `  
&emsp;&emsp;&emsp;` int m_day {}; `  
&emsp;&emsp;&emsp;` int m_year {}; `  

` public: `  
&emsp;&emsp;&emsp;` void setDate(int month, int day, int year) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` m_month = month; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` m_day = day; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` m_year = year; `  
&emsp;&emsp;&emsp;` } `  

&emsp;&emsp;&emsp;` void print() `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << m_month << '/' << m_day << '/' << m_year; `  
&emsp;&emsp;&emsp;` } `  
` }; `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` DateClass date; `  
&emsp;&emsp;&emsp;` date.setDate(10, 14, 2021); `  
&emsp;&emsp;&emsp;` date.print() `  
&emsp;&emsp;&emsp;` std::cout << '\n'; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

The group of public members of a class are often referred to as a **public interface**. Because only public members can be accessed from outside of the class, the public interface defines how programs using the class will interact with the class.

Some programmers prefer to list private members first, because the public members typically use the private ones, so it makes sense to define the private ones first. However, a good counterargument is that users of the class don't care about the private members, so the public ones should come first. Either way is fine.

## Access control works on a per-class basis  

` #include <iostream> `  

` class DateClass ` 
` { `  
&emsp;&emsp;&emsp;` int m_month {}; `  
&emsp;&emsp;&emsp;` int m_day {}; `  
&emsp;&emsp;&emsp;` int m_year {}; `  

` public: `  
&emsp;&emsp;&emsp;` void setDate(int month, int day, int year) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` m_month = month; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` m_day = day; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` m_year = year; `  
&emsp;&emsp;&emsp;` } `  

&emsp;&emsp;&emsp;` void print() `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << m_month << '/' << m_day << '/' << m_year; `  
&emsp;&emsp;&emsp;` } `  

&emsp;&emsp;&emsp;` void copyFrom(const DateClass& d) `   
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` // Note that we can access the private members of d directly `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` m_month = d.m_month; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` m_day = d.m_day; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` m_year = d.m_year; `  
&emsp;&emsp;&emsp;` } `  
` }; `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` DateClass date; `  
&emsp;&emsp;&emsp;` date.setDate(10, 14, 2021); `  

&emsp;&emsp;&emsp;` DateClass copy {}; `  
&emsp;&emsp;&emsp;` copy.copyFrom(date); `  
&emsp;&emsp;&emsp;` copy.print(); `  
&emsp;&emsp;&emsp;` std::cout << '\n'; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

One nuance of C++ that is often missed or misunderstood is that access control works on a per-class basis, not on a per-object basis. **This means that when a function has access to the private members of a class, it can access the private members of any object of that class type that it can see.**  

In the above example, `copyFrom()` is a member of `DateClass`, which gives it access to the private members of `DateClass`. This means `copyFrom()` can not only directly access the private members of the implicit object it is operating on (copy), it also means it has direct access to the private members of `DateClass` parameter `d`. If parameter `d` were some other type, this would not be the case.

This can be particularly useful when we need to copy members from one object of a class to another object of the same class. 

## Structs vs classes revisited  

A class defaults its members to private. A struct defaults its members to public.

Structs inherit from other classes publicly and classes inherit privately. This point is practically irrelevant since you should never rely on the defaults anyway.
