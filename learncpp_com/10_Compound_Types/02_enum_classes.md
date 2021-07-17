# Enum classes

Although enumerated types are distinct types in C++, they are not type safe. With standard enumerators, there's no way to prevent comparing enumerators from different enumerations.

C++11 defines a new concept, the **enum class** (also called a **scoped enumeration**), which makes enumerations both strongly typed and strongly scoped. To make an enum class, we use the keyword class after the enum keyword.

` #include <iostream> `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` enum class Color `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` red, `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` blue `  
&emsp;&emsp;&emsp;` }; `  

&emsp;&emsp;&emsp;` enum class Fruit `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` banana, `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` apple `  
&emsp;&emsp;&emsp;` }; `  

&emsp;&emsp;&emsp;` Color color{ Color::red }; `  
&emsp;&emsp;&emsp;` Fruit fruit{ Fruit::banana }; `  

&emsp;&emsp;&emsp;` if(color == fruit) // compile error here `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << "color and fruit are equal\n"; `  
&emsp;&emsp;&emsp;` else `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << "color and fruit are not equal\n"; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

With normal enumerations, enumerators are placed in the same scope as the enumeration itself, so you can typically access enumerators directly. However, with enum classes, the strong scoping rules mean that all enumerators are considered part of the enumeration, so you have to use a scope qualifier to access the enumerator. This helps keep name pollution and the potential for name conflicts down.

Because the enumerators are part of the enum class, there's no need to prefix the enumerator names (e.g. it's okay to name them "red" instead of "color_red", since Color::color_red is redundant).

The strong typing rules mean that each enum class is considered a unique type. This means that the compiler will not implicitly compare enumerators from different enumerations. If you do so, the compiler will throw an error.

You can compare enumerators from within the same enum class (since they are of the same type).

With enum classes, the compiler will no longer implicitly convert enumerator values to integers. You can explicitly convert an enum class enumerator to an integer by using a static_cast to int.

There's little reason to use normal enumerated types instead of enum classes.

Note that the class keyword, along with the static keyword, is one of the most overloaded keywords in C++, and can have different meaning depending on context. Although enum classes use the class keyword, they aren't considered "classes" in the traditional C++ sense. 

Also, "enum struct" is equivalent to "enum class", but this usage is not recommended and is not common.
