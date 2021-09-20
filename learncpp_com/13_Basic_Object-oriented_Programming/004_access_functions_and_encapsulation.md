# Access functions and encapsulation

## Encapsulation

In object-oriented programming, **encapsulation** (also called **information hiding**) is the process of keeping the details about how an object is implemented hidden away from users of the object. Instead, users of the object access the object through a public interface. In this way users are able to use the object without having to understand how it is implemented.

In C++, we implement encapsulation via access specifiers. Typically, all member variables of the class are made private (hiding the implementation details), and most member functions are made public (exposing an interface for the user). Although requiring users of the class to use the public interface may seem more burdensome than providing public access to the member variables directly, doing so actually provides a large number of useful benefits that help encourage class re-usability and maintainability.

The word encapsulation is also sometimes used to refer to the packaging of data and functions that work on that data together. We prefer to just call that object-oriented programming.

## Benefit: encapsulated classes are easier to use and reduce the complexity of your programs  

With a fully encapsulated class, you only need to know what member functions are publicly available to use the class, what arguments they take, and what values they return. It doesn't matter how the class was implemented internally. For example, a class holding a list of names could have been implemented using a dynamic array of C-style strings, `std::array`, `std::vector`, `std::map`, `std::list`, or one of many other data structures. In order to use the class, you don't need to know (or care) which. This dramatically reduces the complexity of your programs, and also reduces mistakes. More than any other reason, this is the key advantage of encapsulation.

All of the classes in the C++ standard library are encapsulated.

## Benefit: encapsulated classes help protect your data and prevent misuse  

Global variables are dangerous because you don't have strict control over who has access to the global variable, or how they use it. Classes with public members suffer from the same problem, just on a smaller scale.

For example, let's say we were writing a string class. We might start out like this:

` class MyString `  
` { `  
&emsp;&emsp;&emsp;` char *m_string; // we'll dynamically allocate our string here `  
&emsp;&emsp;&emsp;` int m_length; // we need to keep track of the string length `  
` }; `  

These two variables have an intrinsic connection: `m_length` should always equal the length of the string held by `m_string` (this connection is called an **invariant**). If `m_length` were public, anybody could change the length of the string without changing `m_string` (or vice-versa). This would put the class into an inconsistent state, which could cause all sorts of bizarre problems. By making both `m_length` and `m_string` private, users are forced to use whatever public member functions are available to work with the class (and those member functions can ensure that `m_length` and `m_string` are always set appropriately.

We can also help protect the user from mistakes in using our class. Consider a class with a public array member variable:

` class IntArray `  
` { `  
` public: `  
&emsp;&emsp;&emsp;` int m_array[10]; `  
` }; `  

If users can access the array directly, they could subscript the array with an invalid index, producing unexpected results:

` int main() `  
` { `  
&emsp;&emsp;&emsp;` IntArray array; `  
&emsp;&emsp;&emsp;` array.m_array[16] = 2; // invalid array index, now we overwrote memory that we don't own `  
` } `  

However, if we make the array private, we can force the user to use a function that validates that the indes is valid first:

` #incldue <iostream> `  

` class IntArray `  
` { `  
` private: `  
&emsp;&emsp;&emsp;` int m_array[10]; // user cannot access this directly any more `  

` public: `  
&emsp;&emsp;&emsp;` void setValue(int index, int value) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` // If the index is invalid, do nothing `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` if (index < 0 || index >= std::size(m_array)) `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` return; `  

&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` m_array[index] = value; `  
&emsp;&emsp;&emsp;` } `  
` }; `  

In this way, we've protected the integrity of our program.

The `at()` functions of `std::array` and `std::vector` do something very similar.

## Benefit: encapsulated classes are easier to change  

Encapsulation gives us the ability to change how classes are implemented without breaking all of the programs that use them.

If gnomes snuch into your house at night and replaced the internals of your TV remote with a different (but compatible) technology, you probably wouldn't even notice!

## Benefit: encapsulated classes are easier to debug

Encapsulation helps you debug the program when something goes wrong. Often when a program does not work correctly, it is because one of our member variables has an incorrect value. If everyone is able to access the variable directly, tracking down which piece of code modified the variable can be difficult (it could be any of them, and you'll need to breakpoint them all to figure out which). However, if everybody has to call the same public function to modify a value, then you can simply breakpoint that function and watch as each caller changes the value until you see where it goes wrong.

## Access functions  

Depending on the class, it can be appropriate (in the context of what the class does) for us to be able to directly get or set the value of a private member variable.

An **access function** is a short public function whose job is to retrieve or change the value of a private member variable. 

Access functions typically come in two flavors: getters and setters. **Getters** (also sometimes called **accessors**) are functions that return the value of a private member variable. **Setters** (also sometimes called **mutators**) are functions that set the value of a private member variable.

` class Date `  
` { `  
` private: `  
&emsp;&emsp;&emsp;` int m_month; `  
&emsp;&emsp;&emsp;` int m_day; `  
&emsp;&emsp;&emsp;` int m_year; `  

` public: `  
&emsp;&emsp;&emsp;` int getMonth() { return m_month; } `  
&emsp;&emsp;&emsp;` void setMonth(int month) { m_month = month; } `  

&emsp;&emsp;&emsp;` int getDay() { return m_day; } `  
&emsp;&emsp;&emsp;` void setDay(int day) { m_day = day; } `  

&emsp;&emsp;&emsp;` int getYear() { return m_year; `  
&emsp;&emsp;&emsp;` void setYear(int year) { m_year = year; } `  
` }; `  

The Date class above is essentially an encapsulated data struct with a trivial implementation, and a user of the class might reasonably expect to be able to get or set the day, month, or year.

Getters should provide "read-only" access to data. Therefore, the best practice is that they should return by value or const reference (not by non-const reference). A getter that returns a non-const reference would allow the caller to modify the actual object being referenced, which violates the read-only nature of the getter (and violates encapsulation).

**Best practice**  
_Getters should return by value or const reference._  

### Access functions concerns  

There is a fair bit of discussion around in which cases access functions should be used or avoided. Although they don't violate encapsulation, some developers would argue that use of access functions violates good OOP class design.

As you create your classes, consider the following:  
* If nobody outside your class needs to access a member, don't provide access functions for that member.  
* If someone outside your class needs to access a member, think about whether you can expose a behavior or action instead (e.g. rather than a `setAlive(bool)` setter, implement a `kill()` function instead).  
* If you can't, consider wheter you can provide only a getter.  

...   

Encapsulation provides a lot of benefits for just a little bit of extra effort. The primary benefit is that encapsulation allows us to use a class without having to know how it was implemented. This makes it a lot easier to use classes we're not familiar with.

