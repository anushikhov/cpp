# Function overload differentiation

Overloaded functions tha are not properly differentiated will cause the compiler to issue a compile error.

To differentiate an overload function, ensure each overloaded function has a different set (number and/or type) of parameters.

![Overload differentiation](https://raw.githubusercontent.com/anushikhov/cpp/master/learcpp_com/9_Type_Conversion_and_Function_Overloading/img/overload_differentiation.png)  

A function's return type is not used to differentiate overloaded functions.

For member functions, additional function-level qualifiers are also considered:

![Member function overload](https://raw.githubusercontent.com/anushikhov/cpp/master/learncpp_com/9_Type_Conversion_and_Function_Overloading/img/member_function_overload.png)  

As an example, a const member function can be differentiated from an otherwise identical non-const member function (even if they share the same set of parameters).


## Overloading based on number of parameters

An overloaded function is differentiated so long as each overloaded function has a different number of parameters.


## Overloading based on type of parameters

A function can also be differentiated so long as each overloaded function's set of parameter types are distinct.

Because type aliases (or typedefs) are not distinct types, overloaded functions using type aliases are not distinct from overloads using the aliased type.

For parameters passed by value, the const qualifier is also not considered.

Ellipsis parameters are considered to be a unique tupe of parameter.

` void foo(int x, int y); `  
` void foo(int x, ...); `  


## The return type of a function is not considered for differentiation

A function's return type is not considered when differentiating overloaded functions.

This was an intentional choice, as it ensures the behavior of a function call can be determined independently from the rest of the expression, making understanding complex expressions much simpler. Put another way, we can always determine which version of a function will be called based solely on the arguments in the function call. If return values were used for differentiation, then we wouldn't have an easy syntactic way to tell which overload of a functoin was being called -- we'd also have to understand how the return value was being used, which requires a lot more analysis.


## Name mangling

When the compiler compiles a function, it performs **name mangling**, which means the compiled name of the function is altered ("mangled") based on various criteria, such as the number and type of parameters, so that the linker has unique names to work with.

For example, some function with prototype `int fcn()` might compile to name `__fcn_v`, whereas `int fcn(int)` might compile to name `__fcn_i`. So while in the source code, two overloaded functions share a name, in compiled code, the names are actually unique.

There is no standardization on how names should be mangled, so different compilers will produce different mangled names.
