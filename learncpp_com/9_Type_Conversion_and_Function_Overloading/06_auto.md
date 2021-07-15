# Type deduction for objects using the auto keyword

## Type deduction for initialized variables

**Type deduction** (also sometimes called **type inference**) is a feature that allows the compiler to deduce the type of an object from the object's initializer. To use type deduction, the `auto` keyword is used in place of the variable's type:

` auto d{ 5.0 }; `  

We can even use type deduction when our initializer is a function call:

` auto sum { add (5, 6) }; `  

Type deduction will not work for objects that do not have initializers or empty initializers.

### Type deduction drops const qualifiers

In most cases, type deduction will drop the `const` qualifier from deduced types. 

` const int x { 5 }; `  
` auto y { x }; `  

Type deduction deduces the type as `int`, not `const int`.

If you want a deduced type to be `const`, you can use the `const` keyword in conjunction with the `auto` keyword.

**Type deduction will not drop the `const` qualifier for pointers to const values, such as types deduced from C-style string literals.**

### Type deduction drops references

Type deduction will also drop references.

` int x{ 5 }; `  
` int& y{ x }; `  
` auto z{ y }; `  

You can ensure a deduced type is a reference type by using `auto&` instead of `auto`.

` auto& y{ x }; `  

You can also deduce a const reference by using `const auto&`.

### Type deduction benefits and downsides

Type deduction is not only convenient, but also has a number of other benefits.

* If two or more variables are defined on sequential lines, the names will be lined up, increasing readability.
* It can help avoid unintentionally leaving variables uninitialized.
* There will be no unintended performance-impacting conversions.

Type deduction also has a few downsides.

* Obscures an object's type information in the code. Although a good IDE should be able to show you the deduced type (e.g. when hovering a variable), it's still a bit easier to make type-based mistakes when using type deduction.
* If the type of an initializer changes, the type of a variable using type deduction will also change, perhaps unexpectedly.
* Because type deduction drops references, if you use "auto" when you should be using "auto&", your code may not perform as well, or may even not work correctly.

Overall, the modern consensus is that type deduction is generally safe to use for objects, and that doing so can help make your code more readable by de-emphasizing type information so the logic of your code stands out better.

**Best practice**<br/>
_Use type deduction for your variables, unless you need to commit to a specific type._


