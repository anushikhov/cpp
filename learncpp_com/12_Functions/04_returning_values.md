# Returning values by value, reference, and address

Returning values from a function to its caller by value, address, or reference works almost exactly the same way as passing arguments to a function does. All of the same upsides and downsides for each method are present. The primary difference between the two is simply that the direction of data flow is reversed. However, there is one more added bit of complexity -- because local variables in a function go out of scope and are destroyed when the function returns, we need to consider the effect of this on each return type.

### Return by value  

Return by value is the simplest and safest return type to use. When a value is returned by value, a copy of that variable is returned to the caller. As with pass by value, you can return by value literals, variables, or expressions, which makes return by value very flexible.  

Another advantage of return by value is that you can return variables (or expressions) that involve local variables declared within the function without having to worry about scoping issues. Because the variables are evaluated before the function returns, and a copy of the value is returned to the caller, there are no problems when the function's variable goes out of scope at the end of the function. 

Return by value is the most appropriate when returning variables that were declared inside the function, or for returning function arguments that were passed by value. However, like pass by value, return by value is slow for structs and large classes.

When to use return by value:

* When returning variables that were declared inside the function  
* When returning function arguments that were passed by value  

When not to use return by value:  

* When returning a built-in array or pointer (use return by address)  
* When returning a large struct or class (use return by reference)  

### Return by address

Returning by address involves returning the address of a variable to the caller. Similar to pass by address, return by address can only return the address of a variable, not a literal or an expression (which don't have addresses). Because return by address just copies an address from the function to the caller, return by address is fast.

However, return by address has one additional downside that return by value doesn't -- if you try to return the address of a variable local to the function, your program will exhibit undefined behavior. 

` int* doubleValue(int x) `  
` { `  
&emsp;&emsp;&emsp;` int value{ x * 2 }; `  
&emsp;&emsp;&emsp;` return &value; // return value by address here `  
` } // value destroyed here `  

`value` is destroyed here, just after its address is returned to the caller. The end result is that the caller ends up with the address of non-allocated memory (a dangling pointer), which will cause problems if used. 

Return by address was often used to return dynamically allocated memory to the caller:  

` int* allocateArray(int size) `  
` { `  
&emsp;&emsp;&emsp;` return new int[size]; `  
` } `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` int *array{ allocateArray(25) }; `  

&emsp;&emsp;&emsp;` // do stuff with array `  

&emsp;&emsp;&emsp;` delete[] array; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

This works because dynamically allocated memory is not destoryed at the end of the block in which it is allocated, so that memory will still exist when the address is returned back to the caller. Keeping track of manual allocations can be difficult. Separating the allocation and deletion into different functions makes it even harder to understand who's responsible for deleting the resource or if the resource needs to be deleted at all. Smart pointers and types that clean up after themselves should be used instead of manual allocations.

When to use return by address:

* When returning dynamically allocated memory and you can't use a type that handles allocations for you  
* When returning function arguments that were passed by address  

When not to use return by address:  

* When returning variables that were declared inside the function or parameters that were passed by value (use return by value)  
* When returning a large struct or class that was passed by reference (use return by reference)  

### Return by reference  

Similar to return by address, values returned by reference must be variables (you should not return a reference to a literal or an expression that resolves to a temporary value, as those will go out of scope at the end of the function and you'll end up returning dangling reference). When a variable is returned by reference, a reference to the variable is passed back to the caller. The caller can then use this reference to continue modifying the variable, which can be useful at times. Return by reference is also fast, which can be useful when returning structs and classes.

However, just like return by address, you should not return local variables by reference. 

` int& doubleValue(int x) `  
` { `  
&emsp;&emsp;&emsp;` int value{ x * 2 }; `  
&emsp;&emsp;&emsp;` return value; // return a reference to value here `  
` } // value is destroyed here `  

In the above program, the program is returning a reference to a value that will be destroyed when the function returns. This would mean the caller receives a reference to garbage. Fortunately, the compiler will probably give a warning or an error if you try to do this.


Return by reference is typically used to return arguments passed by reference to the function back to the caller. 

` #include <array> `  
` #include <iostream> `  

` // Returns a reference to the index element of array `  
` int& getElement(std::array<int, 25>& array, int index) `  
` { `  
&emsp;&emsp;&emsp;` // we know that array[index] will not be destroyed when we return to the caller `  
&emsp;&emsp;&emsp;` // (since the caller passed in the array in the first place) `  
&emsp;&emsp;&emsp;` // so it's okay to return it by reference `  

&emsp;&emsp;&emsp;` return array[index]; `  
` } `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` std::array<int, 25> array; `   

&emsp;&emsp;&emsp;` // Set the element of array with index 10 to the value 5 `  
&emsp;&emsp;&emsp;` getElement(array, 10) = 5; `  

&emsp;&emsp;&emsp;` std::cout << array[10] << '\n'; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

When we call `getElement(array, 10)`, `getElement()` returns a reference to the array element with index 10. `main()` then uses this reference to assign that element the value 5.

This is somewhat of a contrived example (because you can access array[10] directly), with classes you will find a lot more uses for returning values by reference.

When to use return by reference:  

* When returning a reference parameter  
* When returning a member of an object that was passed into the function by reference or address  
* When returning a large struct or class that will not be destroyed at the end of the function (e.g. one that was passed in by reference)  

When not to use return by reference:  

* When returning variables that were declared inside the function or parameter that were passed by value (use return by value)
* When returning a built-in array or pointer value (use return by address)  

### Mixing return references and values

Although a function may return a value or a reference, the caller may or may not assign the result to a variable or reference accordingly.

` int returnByValue() `  
` { `  
&emsp;&emsp;&emsp;` return 5; `  
` } `  

` int& returnByReference() `  
` { `  
&emsp;&emsp;&emsp;` static int x{ 5 }; `  
&emsp;&emsp;&emsp;` return x; `  
` } `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` int giana{ returnByReference() }; // ok, treated as return by value `  
&emsp;&emsp;&emsp;` int& ref{ returnByValue() }; // compile error -- since the value is an r-value, and an r-value cannot bind to a non-const reference `  
&emsp;&emsp;&emsp;` const int& cref{ returnByValue() }; // ok, the lifetime of the return value is extended to the lifetime of cref `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

In the first case, we're assigning a reference return value to a non-reference variable. Because `giana` isn't a reference, the return value is copied into `giana`, as if `returnByReference()` had returned by value.

In the second case, we're trying to initialize reference ref with the copy of the return value returned by `returnByValue()`. However, because the value being returned doesn't have an address (it's an r-value), this will cause a compile error.

In the thrid case, we're trying to initialize const reference cref with the copy of the return value returned by `returnByValue()`. Because `const` references can bind to r-values, there's no problem here. Normally, r-values expire at the end of the expression in which they are created -- however, when bound to a `const` reference, the lifetime of the r-value (in this case, the return value of the function) is extended to match the lifetime of the reference (in this case, cref).  

### Lifetime extension doesn't save dangling references

` const int& returnByReference() `  
` { `  
&emsp;&emsp;&emsp;` return 5; `  
` } `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` const int& ref { returnByReference() }; // runtime error `  
` } `  

`returnByReference()` is returning a const reference to a value that will go out of scope when the function ends. It will result in a dangling reference. However, assigning a value to a const reference can extend the lifetime of that value. In this case, 5 goes out of scope first, then the reference to 5 is copied back to the caller, and then ref extends the lifetime of the now-dangling reference.

` const int returnByValue() `  
` { `  
&emsp;&emsp;&emsp;` return 5; `  
` } `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` const int& ref{ returnByValue() }; // we're extending the lifetime of the copy passed back to main `  
` } `  

In this case, the literal value 5 is first copied back into the scope of the caller (main), and then ref extends the lifetime of that copy.

### Returning multiple values

C++ doesn't contain a direct method for passing multiple values back to the caller. While you can sometimes restructure your code in such a way that you can pass back each data item separately (e.g. instead of having a single function return two values, have two functions each return a single value), this can be cumbersome and unintuitive.

There are several indirect methods that can be used.

Out parameters provide one method for passing multiple bits of data back to the caller. We don't recommend this method.

A second method involves using a data-only struct:

` #include <iostream> `  

` struct S `  
` { `  
&emsp;&emsp;&emsp;` int m_x; `  
&emsp;&emsp;&emsp;` double m_y; `  
` }; `  

` S returnStruct() `  
` { `  
&emsp;&emsp;&emsp;` S s; `  
&emsp;&emsp;&emsp;` s.m_x = 5; `  
&emsp;&emsp;&emsp;` s.m_y = 6.7; `  

&emsp;&emsp;&emsp;` return s; `  
` } `  

` int main() `  
` { `   
&emsp;&emsp;&emsp;` S s{ returnStruct() }; `  
&emsp;&emsp;&emsp;` std::cout << s.m_x << ' ' << x.m_y << '\n'; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

A third way is to use `std::tuple`. A tuple is a sequence of elements that may be different types, where the type of each element must be explicitly specified.  

Here's an example that returns a tuple, and uses `std::get` to get the nth element of the tuple (counting from 0):  

` #include <tuple> `  
` #include <iostream> `  

` std::tuple<int, double> returnTuple() // return a tuple that contains an int and a double `  
` { `  
&emsp;&emsp;&emsp;` return { 5, 6, 7 }; `  
` } `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` std::tuple s{ returnTuple() }; `  
&emsp;&emsp;&emsp;` std::cout << std::get<0>(s) << ' ' << std::get<1>(s) << '\n'; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

This works identically to the prior example.

You can also use `std::tie` to unpack the tuple into predefined variables, like so: 

` #include <tuple> `  
` #include <iostream> `  

` std::tuple<int, double> returnTuple() `  
` { `  
&emsp;&emsp;&emsp;` return { 5, 6.7 }; `  
` } `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` int a; `  
&emsp;&emsp;&emsp;` int b; `   
&emsp;&emsp;&emsp;` std::tie(a, b) = returnTuple(); `  

&emsp;&emsp;&emsp;` std::cout << a << ' ' << b << '\n'; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

As of C++17, a structured binding declaration can be used to simplify splitting multiple returned values into separate variables.

` #include <tuple> `  
` #include <iostream> `  

` std::tuple<int, double> returnTuple() `  
` { `  
&emsp;&emsp;&emsp;` return { 5, 6.7 }; `  
` } `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` auto [a, b]{ returnTuple() }; // used structured binding declaration to put results of tuple in variable a and b `  
&emsp;&emsp;&emsp;` std::cout << a << ' ' << '\n'; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

Using a struct is a better option than a tuple if you're using the struct in multiple places. However, for cases where you're just packaging up these values to return and there would be no reuse from defining a new struct, a tuple is a bit clearer since it doesn't introduce a new user-defined data type.

...  

Most of the time, return by value, will be sufficient for your needs. It's also the most flexible and safest way to return information to the caller. However, return by reference or address can also be useful, particularly when working with dynamically allocated classes or structs. When using return by reference or address, make sure you are not returning a reference to, or the address of, a variable that will go out of scope when the function returns.

