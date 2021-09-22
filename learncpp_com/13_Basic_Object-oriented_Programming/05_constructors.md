# Constructors  

When all members of a class (or struct) are public, we can use **aggregate initialization** to initialize the class (or struct) directly using list-initialization. However, as soon as we make any member variable private, we're no longer able to initialize classes in this way. It does make sense: if you can't directly access a variable (because it's private), you shouldn't be able to directly initialize it.

We initialize a class with private member variables through constructors.

A **constructor** is a special kind of class member function that is automatically called when an object of that class is created. Constructors are typically used to initialize member variables of the class to appropriate user-provided values, or to do any setup steps necessary for the class to be used (e.g. open a file or database).

After a constructor executes, the object should be in a well-defined, usable state.

Unlike normal member functions, constructors have specific rules for how they must be named:

1. Constructors must have the same name as the class (with the same capitalization)  
1. Constructors have no return type (not even void)  

Here is an example of a class that has a default constructor:  

` #include <iostream> `  

` class Fraction `  
` { `  
` private: `  
&emsp;&emsp;&emsp;` int m_numerator {}; `  
&emsp;&emsp;&emsp;` int m_denominator {}; `  

` public: `  
&emsp;&emsp;&emsp;` Fraction() // default constructor `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` m_numerator = 0; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` m_denominator = 1; `  
&emsp;&emsp;&emsp;` } `  

&emsp;&emsp;&emsp;` int getNumerator() { return m_numerator; } `  
&emsp;&emsp;&emsp;` int getDenominator() { return m_denominator; } `  
&emsp;&emsp;&emsp;` double getValue() { return static_cast<double>(m_numerator) / m_denominatori; } `  
` }; `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` Fraction frac {}; // calls Fraction() default constructor `  
&emsp;&emsp;&emsp;` std::cout << frac.getNumerator() << '/' << frac.getDenominator() << '\n'; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

When the line `Fraction frac{};` executes, the compiler will see that we're instantiating an object of type Fraction with no arguments. It then performs value-initialization of `frac`, that is, the default constructor gets called. Although technically incorrect, this is often called **default initialization**. In this case, the default constructor will be called immediately after memory has been allocated and cleared for the object. The default constructor rusn just like a normal function (assigning the values 0 to `m_numerator` and 1 to `m_denominator`).

### List-initialization  

We can initialize class object using list-initialization:

` Fraction frac {}; // List-initialization with empty set of braces (leads to value-initialization) `  

We can also initialize class objects using default-initialization:

` Fraction frac; // Default-initialization, calls default constructor `  

For the most part, default- and list-initialization of a class object results in the same outcome: the default constructor is called.

Many programmers favor default-initialization over list-initialization for class objects. This is because when using value-initialization, the compiler may zero-initialize the class members before calling the default constructor in certain cases, which is slightly inefficient. 

However, favoring default-initialization also comes with a downside: you have to know whether a type will initialize itself, i.e. it is a class-type and all members have an initializer, or there is a default-constructor that initializes all member variables. If you see a defined variable without an initializer, you have to think about whether that's a mistake or not (depending on what type of object it is).

While you might be able to initialize all members in the classes you write, it's not feasible to read the definitions of all classes you use to make sure they do the same.

Favoring value initialization for class objects is simple, consistent, and can help in catching errors.

**Best practice**  
_Favor list-initialization over default-initialization for class objects._  

### Direct- and list-initialization using constructors with parameters  

Constructors can also be declared with parameters. 

` #include <cassert> `  

` class Fraction `  
` { `  
` private: `  
&emsp;&emsp;&emsp;` int m_numerator {}; `  
&emsp;&emsp;&emsp;` int m_denominator {}; `  

` public: `  
&emsp;&emsp;&emsp;` Fraction() `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` m_numerator = 0; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` m_denominator = 1; `  
&emsp;&emsp;&emsp;` } `  

&emsp;&emsp;&emsp;` Fraction(int numerator, int denominator=1) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` assert(denominator != 0); `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` m_numerator = numerator; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` m_denominator = denominator; `  
&emsp;&emsp;&emsp;` } `  

&emsp;&emsp;&emsp;` int getNumerator() { return m_numerator; }  `  
&emsp;&emsp;&emsp;` int getDenominator() { return m_denominator;  `  
&emsp;&emsp;&emsp;` double getValue() { return static_cast<double>(m_numerator) / m_denominator; } `  
` }; `  

The two constructors can coexist peacefully in the same class due to function overloading. In fact, you can define as many constructors as you want, so long as each has a unique signature (number and type of parameters).

We can use the constructors via list or direct initialization.

**Best practice**  
_Favor brace initialization to initialize class objects._  

### Copy initialization using equals with classes  

Much like with fundamental variables, it's also possible to initialize classes using copy initialization:  

` Fraction six = Fraction{ 6 }; // Copy initialize a Fraction, will call Fraction(6, 1) `  
` Fraction seven = 7; // The compiler will try to find a way to convert 7 to a Fraction, which will invoke the Fraction(7, 1) constructor. `  

However, avoid this form of initialization with classes, as it may be less efficient. Although direct-initialization, list-initialization, and copy-initialization all work identically with fundamental types, copy-initialization does not work the same with classes (though the end-result is often the same).

### Reducing constructors

In the above two-constructor declaration of the Fraction class, the default constructor is actually somewhat redundant. We could simplify the class as follows:

` #include <cassert> `  

` class Fraction `  
` { `  
` private: `  
&emsp;&emsp;&emsp;` int m_numerator {}; `  
&emsp;&emsp;&emsp;` int m_denominator {}; `  

` public: `  
&emsp;&emsp;&emsp;` // Default constructor `   
&emsp;&emsp;&emsp;` Fraction(int numerator=0, int denominator=1) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` assert(denominator != 0); `  
 
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` m_numerator = numerator; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` m_denominator = denominator; `   
&emsp;&emsp;&emsp;` } `  

&emsp;&emsp;&emsp;` int getNumerator() { return m_numerator; } `  
&emsp;&emsp;&emsp;` int getDenominator() { return m_denominator; } `  
&emsp;&emsp;&emsp;` double getValue() { return static_cast<double>(m_numerator) / m_denominator; } `  
` }; `  

Although this constructor is still a default constructor, it has now been defined in a way that it can accept one or two user-provided values as well. 

` Fraction zero; // will call Fraction(0, 1) `  
` Fraction zero{}; // will call Fraction(0, 1) `  
` Fraction six{ 6 }; // will call Fraction(6, 1) `  
` Fraction fiveThirds{ 5, 3 }; // will call Fraction(5, 3) `  

When implementing your constructors, consider how you might keep the number of constructors down through smart defaulting of values. 

### A reminder about default parameters

The rules around defining and calling functions that have default parameters apply to constructors too. To recap, when defining a function with default parameters, all default parameters, must follow any non-default parameters, i.e. there cannot be non-defaulted parameters after a defaulted parameter.

This may produce unexpected results for classes that have multiple default parameters of different types.

` class Something `  
` { `  
` public: `  
&emsp;&emsp;&emsp;` // Default constructor `   
&emsp;&emsp;&emsp;` // Allows us to construct a Something(int, double), Something(int), or Something()  `  
&emsp;&emsp;&emsp;` Something(int n = 0, double d = 1.2) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;` } `  
` }; `  

` int main() `  
` { `   
&emsp;&emsp;&emsp;` Something s1 { 1, 4.2 }; // calls Something(int, double) `   
&emsp;&emsp;&emsp;` Something s2 { 1 }; // calls Something(int, double) `  
&emsp;&emsp;&emsp;` Something s3 {}; // calls Something(int, double) `  

&emsp;&emsp;&emsp;` Something s4 { 2.4 }; // will not compile, as there's no constructor to handle Something(double) `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

With `s4`, we've attempted to construct a `Something` by providing only a `double`. This won't compile, as the rules for how arguments much with default parameters won't allow us to skip a on-rightmost parameter (in this case, the leftmost int parameter).

If we want to be able to construct a `Something` with only a `double`, we'll need to add a second (non-default) constructor:

` class Something `  
` { `  
` public: `  
&emsp;&emsp;&emsp;` // Default constructor `   
&emsp;&emsp;&emsp;` // Allows us to construct a Something(int, double), Something(int), or Something() `  
&emsp;&emsp;&emsp;` Something(int n = 0, double d = 1.2) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;` } `  
 
&emsp;&emsp;&emsp;` Something(double d) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;` } `   
` }; `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` Something s1 { 1, 2.4 }; // calls Something(int, double) `  
&emsp;&emsp;&emsp;` Something s2 { 1 }; // calls Something(int, double) `  
&emsp;&emsp;&emsp;` Something s3 {}; // calls Something(int, double) `  

&emsp;&emsp;&emsp;` Something s4 { 2.4 }; // calls Something(double) `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

### An implicitly generated default constructor  

If your class has no constructors, C++ will automatically generate a public default constructor for you. This is sometimes called an **implicit constructor** (or implicitly generated constructor).

When the generated default constructor is called, members will still be initialized if they have non-static member initializers.

If a class has any other constructors, the implicitly generated constructor will not be provided.

If your class has another constructor and you want to allow default construction, you can either add default arguments to every parameter of a constructor with parameters, or explicitly define a default constructor.

There's a third option as well: you can use the `default` keyword to tell the compiler to create a default constructor.

` class Date `  
` { `  
` private: `  
&emsp;&emsp;&emsp;` int m_year { 1900 }; `   
&emsp;&emsp;&emsp;` int m_month { 1 }; `  
&emsp;&emsp;&emsp;` int m_day { 1 }; `  

` public: `  
&emsp;&emsp;&emsp;` // Tell the compiler to create a default constructor, even if there are other user provided constructors. `   
&emsp;&emsp;&emsp;`  Date() = default; `  

&emsp;&emsp;&emsp;` Date(int year, int month, int day) // normal non-default constructor `  
&emsp;&emsp;&emsp;` { `   
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` m_year = year; `   
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` m_month = month; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` m_day = day; `   
&emsp;&emsp;&emsp;` } `  
` }; `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` Date date{}; // date is initialized to Jan 1st, 1900 `  
&emsp;&emsp;&emsp;` Date today{ 2021, 10, 14 }; // today is initialized to Oct 14th, 2021 `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

Using `=default` is longer than writing a constructor with an empty body, but expresses better what your intentions are (to create a default constructor), and it's safer, because it can zero-initialize members even if they have not been initialized at their declaration. `=default` also works for other special constructors.

**Best practice**  
_If you have constructors in your `class` and need a default constructor that does nothing (e.g. because all your members are initialized using non-static member initialization, use `=default`._  

## Classes containing classes  

A class may contain other classes as member variables. By default, when the outer class is constructed, the member variables will have their default constructors called. This happens before the body of the constructor executes.

` #include <iostream> `  

` class A `  
` { `  
` public: `  
&emsp;&emsp;&emsp;` A() { std::cout << "A\n"; } `  
` }; `  

` class B `  
` { `  
` private: `  
&emsp;&emsp;&emsp;` A m_a; // B contains A as a member variable `  

` public: `  
&emsp;&emsp;&emsp;` B() { std::cout << "B\n"; } `  
` }; `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` B b; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

This prints: 

` A `  

` B `  

When variable `b` is constructed, the `B()` constructor is called. Before the body of the constructor executes, `m_a` is initialized, calling the `class A` default constructor. This prints "A". Then control returns back to the `B` constructor, and the body of the B constructor executes.

This makes snese as the `B()` constructor may want to use variable `m_a` -- so `m_a` had better be initialized first. 

The difference to the last example in the previous section is that `m_a` is a class-type. **class-type members get initialized even if we don't explicitly initialize them**.

### Constructor notes  

Constructors don't create the objects. The compiler sets up the memory allocation for the object prior to the constructor call. 

Constructors serve two purposes. First, constructors determine who is allowed to create an object. That is, an object of a class can only be created if a matching constructor can be found.

Second, constructors can be used to initialize objects. Whether the constructor actually does an initialization is up to the programmer. It's syntactically valid to have a constructor that does no initialization at all (the constructor still serves the purpose of allowing the object to be created, as per the above).

However, much like it is a best practice to initialize all local variables, it's also a best practice to initialize all member variables on creation of the object. This can be done via a constructor or via non-static member initialization.

**Best practice**  
_Always initialize all member variables in your objects._  

Constructors are only intended to be used for initialization when the object is created. You should not try to call a constructor to re-initialize an existing object. While it may compile, the results will not be what you intended (instead, the compiler will create a temporary object and then discard it).
