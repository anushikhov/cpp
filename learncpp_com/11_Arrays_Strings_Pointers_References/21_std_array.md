# An introduction to std::array

Although fixed and dynamic arrays are built right into the C++ language, they both have downsides. Fixed arrays decay into pointers, losing the array length information when they do, and dynamic arrays have messy deallocation issues and are challenging to resize without error.

To address these issues, the C++ standard library includes functionality that makes array management easier, `std::array` and `std::vector`. 

`std::array` provides fixed array functionality that won't decay when passed into a function. `std::array` is defined in the `<array>` header, inside the `std` namespace.

` #include <array> `  

` std::array<int, 3> myArray; // declare an integer array with length 3 `  

Just like the native implementation of fixed arrays, the length of a `std::array` must be known at compile time. 

`std::array` can be initialized using initializer lists or list initialization: 

` std::array<int, 5> myArray = { 9, 7, 5, 3, 1 }; // initializer list `  
` std::array<int, 5> myArray2 { 9, 7, 5, 3, 1 }; // list initialization `  

Unlike built-in fixed array, with `std::array` you can not omit the array length when providing an initializer: 

However, since C++17, it is allowed to omit the type and size. THey can only be ommitted together, but ot one or the other, and only if the array is explicitly initialized.

` std::array myArray { 9, 7, 5, 3, 1 }; // the type is deduced to std::array<int, 5> `  
` std::array myArray2 { 9, 7, 5, 3, 1 }; // the type is deduced to std::array<double, 2> `  

Favor the syntax without type and size at the declaration, unless your compiler is not C++17 capable.

Since C++20, it is possible to specify the element type but omit the array length. This makes creation of `std::array` a little more like creation of C-style arrays. To create an array with a specific type and deduced size, we use the `std::to_array` function:  

` auto myArray1{ std::to_array<int, 5>({ 9, 7, 5, 3, 1 }) }; // specify type and size `  
` auto myArray2{ std::to_array<int>({ 9, 7, 5, 3, 1 }) }; // specify type only, deduce size `  
` auto myArray3{ std::to_array({ 9, 7, 5, 3, 1 }) }; // deduce type and size `  

Unfortunately, `std::to_array` is more exprensive than creating a `std::array` directly, because it actually copies all elements from a C-style array to a `std::array`. For this reason, `std::to_array` should be avoided when the array is created many times (e.g. in a loop).

You can also assign values to the array using an initializer list:

` std::array<int, 5> myArray; `  
` myArray = { 0, 1, 2, 3, 4 }; `  
` myArray = { 9, 8, 7 }; // element 3 and 4 are set to zero `  
` myArray = { 0, 1, 2, 3, 4, 5 }; // not allowed, too many elements in initializer list `  

Accessing `std::array` values using the subscript operator:

` std::cout << myArray[1] << '\n'; `  
` myArray[2] = 6; `  

Just like built-in fixed arrays, the subscript operator does not do any bounds-checking. If an invalid index if provided, bad things will probably happen.

`std::array` supports a second form of array element access (the `at()` function) tha does bounds checking: 

` std::array myArray { 9, 7, 5, 3, 1 }; `  
` myArray.at(1) = 6; // array element 1 is valid, sets array element 1 to value 6 `  
` myArray.at(9) = 10; // array element 9 is invalid, will throw an error `  

In the above example, the call to `myArray.at(1) checks to ensure the index 1 is valid, and because it is, it returns a reference to array element 1. We then assign the value of 6 to this. However, the call to `myArray.at(9) fails with `std::out_of_range` exception. Because it does bounds checking, `at()` is slower (but safer) than `operator[]`.

`std::array` will clean up after itself when it goes out of scope, so there's no need to do any kind of manual cleanup. 

## Size and sorting

The `size()` function can be used to retrieve the length of the `std::array`:

` std::array myArray { 9.0, 7.2, 5.4, 3.6, 1.8 }; `  
` std::cout << "length: " << myArray.size() << '\n'; `  

Because `std::array` does not decay to a pointer when passed to a function, the `size()` function will work even if you call it from within a function:

` #include <array> `  
` #include <iostream> `  

` void printLength(const std::array<double, 5> &myArray) `  
` { `  
&emsp;&emsp;&emsp;` std::cout << "length: " << myArray.size() << '\n'; `  
` } `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` std::array myArray { 9.0, 7.2, 5.4, 3.6, 1.8 }; `  

&emsp;&emsp;&emsp;` printLength(myArray); `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

Note that the standard library uses the term "size" to mean the array length -- do not get this confused with the results of `sizeof()` on a native fixed array, which returns the actual size of the array in memory (the size of an element multiplied by the array length).

Also note that we passed `std::array` by (const) reference. This is to prevent the compiler from making a copy of the `std::array` when the `std::array` was passed to the function (for performance reasons).

**Best practice**<br/> 
_Always pass `std::array` by reference or `const` reference._  

Because the length is always known, range-based for-loops work with `std::array`:  

` std::array myArray{ 9, 7, 5, 3, 1 }; `  

` for(int element : myArray) `  
&emsp;&emsp;&emsp;` std::cout << element << ' '; `  

You can sort `std::array` using `std::sort`, which lives in the `<algorithm>` header:  

` #include <algorithm> `  
` #include <array> `  
` #include <iostream> `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` std::array myArray{ 7, 3, 1, 9, 5 }; `  
&emsp;&emsp;&emsp;` std::sort(myArray.begin(), myArray.end()); // sort the array forwards `  
&emsp;&emsp;&emsp;` // std::sort(myArray.rbegin(), myArray.rend()); // sort the array backward `  

&emsp;&emsp;&emsp;` for(int element : myArray) `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << element << ' '; `  

&emsp;&emsp;&emsp;` std::cout << '\n'; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

The sorting function uses iterators.

## Passing std::array of different lengths to a function

With a `std::array`, the element type and array length are part of the type information. Therefore, when we use a `std::array` as a function parameter, we have to specify the element type and array length:

` #include <array> `  
` #include <iostream> `  

` void printArray(const std::array<int, 5> &myArray) `  
` { `  
&emsp;&emsp;&emsp;` for(auto element : myArray) `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << element << ' '; `  
&emsp;&emsp;&emsp;` std::cout << '\n'; `  
` } `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` std::array MyArray5{ 9.0, 7.2, 5.4, 3.6, 1.8 }; `  
&emsp;&emsp;&emsp;` printArray(myArray5); `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

The down side is that this limits our function to only handling arrays of this specific type and length. 

If we want to have our function handle arrays of different element types or lengths, we'd have to create a copy of the function for each different element type and/or array length we want to use. That's a lot of duplication. Fortunately, we can have C++ do this for us, using templates. We can create a template function that parameterizes part or all of the type information, and then C++ will use that template to create "real" functions (with actual types) as needed.  

` template <typename T, std::size_t size> // parameterize the element type and size `  
` void printArray(const std::array<T, size> &myArray) `  
` { `  
&emsp;&emsp;&emsp;` for(auto element : myArray) `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << element << ' '; `  
&emsp;&emsp;&emsp;` std::cout << '\n'; `  
` } `  

## Manually indexing std::array via size_type

` #include <iostream> `  
` #include <array> `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` std::array myArray{ 7, 3, 1, 9, 5 }; `  


&emsp;&emsp;&emsp;` for(int i{ 0 }; i < myArray.size(); ++i) `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << myArray[i] << ' '; `  

&emsp;&emsp;&emsp;` std::cout << '\n'; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

The `size()` function and array index parameter to `operator[]` use a type called `size_type`, which is defined by the C++ standard as an unsigned integral type. The loop counter variable is a signed int. Therefor both the comparison `i < myArray.size()` and the array index `myArray[i]` have type mismatches.

`size_type` is not a global type (like `int` or `std::size_t`). Rather, it's defined inside the definition of `std::array` (C++ allows nested types). This means when we want to use `size_type`, we have to prefix it with the full array type (think of `std::array` acting as a namespace in this regard). For the above example, the full-prefixed type of `size_type` would be `std::array<int, 5>::size_typei`.  

Therefore, the correct way to write the above code is as follows:  

` #include <array> `  
` #include <iostream> `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` std::array myArray{ 7, 3, 1, 9, 5 }; `  

&emsp;&emsp;&emsp;` // std::array<int, 5>::size_type is the return type of size() `  
&emsp;&emsp;&emsp;` for(std::array<int, 5>::size_type i{ 0 }; i < myArray.size(); ++i) `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << myArray[i] << ' '; `  

&emsp;&emsp;&emsp;` std::cout << '\n'; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

That is not very readable. Fortunately, `std::array::size_type` is just an alias for std::size_t, so we can use that instead.

` #include <array> `  
` #include <cstddef> `  
` #include <iostream> `  

` int main() ` 
` { `  
&emsp;&emsp;&emsp;` std::array myArray{ 7, 3, 1, 9, 5 }; `  

&emsp;&emsp;&emsp;` for(std::size_t i{ 0 }; i < myArray.size(), ++i) `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << myArray[i] << ' '; `  

&emsp;&emsp;&emsp;` std::cout << '\n'; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

A better solution is to avoid manual indexing of `std::array` in the first place. Instead, use range-based for-loops (or iterators) if possible.

Keep in in mind that unsigned integers wrap around when you reach their limits. A common mistake is to decrement an index that is 0 already, causing a wrap-around to the maximum value.

A working reverse for-loop for unsigned integers takes an odd shapte:

` #include <array> `  
` #include <iostream> `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` std::array myArray{ 7, 3, 1, 9, 5 }; `  

&emsp;&emsp;&emsp;` for(auto i{ myArray.size() }; i-- > 0; ) `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << myArray[i] << ' '; `  

&emsp;&emsp;&emsp;` std::cout << '\n'; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

Suddenly we decrement the index in the condition, and we use the postfix -- operator. The condition runs before every iteration, including the first. In the first iteration, `i` is `myArray.size() - 1`, because `i` was decremented in the condition. When `i` is 0 and about to wrap around, the condition is no longer true and loop stops. `i` actually wraps around when we do `i--` for the last time, but it's not used afterwards.

## Array of struct

Every type that can be used in a regular array can be used in a `std::array`.

` #include <array> `  
` #include <iostream> `  

` struct House `  
` { `  
&emsp;&emsp;&emsp;` int number{}; `  
&emsp;&emsp;&emsp;` int stories{}; `  
&emsp;&emsp;&emsp;` int roomsPerStory{}; `  
` }; `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` std::array<House, 3> houses{}; `  

&emsp;&emsp;&emsp;` houses[0] = { 13, 4, 30 }; `  
&emsp;&emsp;&emsp;` houses[1] = { 14, 3, 10 }; `  
&emsp;&emsp;&emsp;` houses[2] = { 15, 3, 40 }; `  

&emsp;&emsp;&emsp;` for(const auto& house : houses) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << "House number " << house.number `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` << " has " << (house.stories * house.roomsPerStory) `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` << " rooms\n"; `  
&emsp;&emsp;&emsp;` } `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

However, things get a little weirs when we try to initialize the array:  

` // Doesn't work `  
` std::array<House, 3> houses{ `  
&emsp;&emsp;&emsp;` { 13, 4, 30 }, `  
&emsp;&emsp;&emsp;` { 14, 3, 10 }, `  
&emsp;&emsp;&emsp;` { 15, 3, 40 } `  
` }; `  

Although we can initialize `std::array` like this if its elements are simple types, like `int` or `std::string`, it doesn't work with types that need multiple values to be created. 

`std::array` is an aggregate type, just like `House`. There is no special function for the creation of a `std::array`. Rather, its internal array gets initialized like any other member variable of a `struct`.

To make this easier to understand, we'll implement a simple array type ourselves.

As of now, we cannot do this without having to access the `value` member. 

`struct Array `  
` { `  
&emsp;&emsp;&emsp;` int value[3]{}; `  
` } `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` Array array{ `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` 11, `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` 12, `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` 13 `  
` }; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

This works. So does `std::array` if we use it with `int` elements. When we instantiate a `struct`, we can initialize all of its members. If we try to crate an `Array` of `Houses`, we get an error.

` struct House `  
` { `  
&emsp;&emsp;&emsp;` int number{}; `  
&emsp;&emsp;&emsp;` int stories{}; `  
&emsp;&emsp;&emsp;` int roomsPerStory{}; `  
` }; `  

`struct Array`  
` { `  
&emsp;&emsp;&emsp;` House value[3]{}; `  
` }; `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` // If we try to initialize the array, we get an error. `  
&emsp;&emsp;&emsp;` Array houses{ `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` { 13, 4, 30 }; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` { 14, 3, 10 }; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` { 15, 3, 40 } `  
&emsp;&emsp;&emsp;` }; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

When we use braces inside of the initialization, the compiler will try to initialize one member of the `struct` for each pair of braces. Rather than initializing the `Array` like this: 

` Array houses{ `  
&emsp;&emsp;&emsp;` { 13, 4, 30 }; // value[0] `  
&emsp;&emsp;&emsp;` { 14, 3, 10 }; // value[1] `  
&emsp;&emsp;&emsp;` { 15, 3, 40 }  // value[2] `  
` };`  

The compiler tries to initialize the `Array` like this: 

` Array houses{ `  
&emsp;&emsp;&emsp;` { 13, 4, 30 }; // value `  
&emsp;&emsp;&emsp;` { 14, 3, 10 }; // ??? `  
&emsp;&emsp;&emsp;` { 15, 3, 40 }  // ??? `  
` };`  

The first pair of inner braces initializes `value`, because `value` is the first member of `Array`. Without the other two pairs of braces, there would be one house with number 13, 4 stories, and 30 rooms per story.

Remember that braces can be ommited during aggregate initialization: 

` struct S `  
` { `  
&emsp;&emsp;&emsp;` int arr[3]{}; `  
&emsp;&emsp;&emsp;` int i{}; `  
` }; `  

` // These two do the same `  
` S s1{ { 1, 2, 3 }, 4 }; `  
` S s2{ 1, 2, 3, 4 }; `  

To initialize all houses, we need to do so in the first pair of braces.

` Array houses { `  
&emsp;&emsp;&emsp;` { 13, 4, 30, 14, 3, 10, 15, 3, 40 }, // value `  
` }; `  

This works, but it's very confusing. So confusing that your compiler might even warn you about it. If we add braces around each element of the array, the initialization is a lot easier to read.

` #include <iostream> `  

` struct House `  
` { `  
&emsp;&emsp;&emsp;` int number{}; `  
&emsp;&emsp;&emsp;` int stories{}; `  
&emsp;&emsp;&emsp;` int roomsPerStory{}; `  
` }; `  

` struct Array `  
` { `  
&emsp;&emsp;&emsp;` House value[3]{}; `  
` }; `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` Array houses{ `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` { { 13, 4, 30 }, { 14, 3, 10 }, { 15, 3, 40 } } `  
&emsp;&emsp;&emsp;` }; `  

&emsp;&emsp;&emsp;` for(const auto& house : houses.value) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << "House number " << house.number `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` << " has " << (house.stories * house.roomsPerStory) `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` << " rooms\n"; `  
&emsp;&emsp;&emsp;` } `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

This is why you'll see an extra pair of braces in initialization of `std::array`.

`std::array` is a great replacement to built-in fixed arrays. It's efficient, in that it doesn't use any more memory than built-in fixed arrays.  

For any non-trivial array use, we recomment using `std::array` over built-in fixed arrays.
