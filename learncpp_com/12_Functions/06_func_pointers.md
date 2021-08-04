# Function pointers  

Pointer is a variable that holds the address of another variable. Function pointers are similar, except that instead of pointing to variables, they point to functions.

` int foo() `  
` { `  
&emsp;&emsp;&emsp;` return 5; `  
` } `  

Identifier foo is the functin's name. Functions have their own l-value function type -- in this case, a function type that returns an integer and takes no parameters. Much like variables, functions live at an assigned address in memory. 

When a function is called (via the () operator), execution jumps to the address of the function being called.

` std::cout << foo; `  

If you miss the parenthesis when calling the function, depending on how your compiler converts the function pointer to another type for printing it  will likely output the address of the function pointer.

If your machine doesn't print the function's address, you may be able to force it to do so by converting the function to a void pointer and printing that:

` #include <iostream> `  

` int foo() // code starts at memory address 0x002717f0 `  
` { `  
&emsp;&emsp;&emsp;` return 5; `  
` } `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` std::cout << reinterpret_cast<void*>(foo) << '\n'; // Tell C++ to interpret function foo as a valid pointer `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

Just like it is possible to declare a non-constant pointer to a normal variable, it's also possible to declare a non-constant pointer to a function.

### Pointers to functions  

The syntax for creating a non-const function pointer is one of the ugliest things you'll ever see in C++:  

` // fcnPtr is a pointer to a function that takes no arguments and returns an integer `  
` int (*fcnPtr)(); `  

In the above snippet, `fctPtr` is a pointer to a function that has no parameters and returns an integer. `fctPtr` can point to any function that matches this type.

The parenthesis around `\*fcnPtr` are necessary for precedence reasons, as `int *fctPtr()` would be interpreted as a forwards declaration for a function named `fctPtr` that takes no parameters and returns a pointer to an integer.

To make a const function pointer, the const goes after the asterisk:  

` int (*const fcnPtr)(); `  

If you put the const before the int, then that would indicate the function being pointed to would return a const int.


### Assigning a function to a function pointer  

Function pointers can be initialized with a function (and non-const function pointers can be assigned a function). In the above example, we have used `foo` directly, and it has been converted to a function pointer. Like with pointers to variables, we can also use `&foo` to get a function pointer to `foo`. 

` int foo() `  
` { `  
&emsp;&emsp;&emsp;` return 5; `  
` } `  

` int goo() `  
` { `  
&emsp;&emsp;&emsp;` return 6; `  
` } `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` int (*fcnPtr)(){ &foo }; // fcnPtr points to function foo `  
&emsp;&emsp;&emsp;` fcnPtr = &goo; // fcnPtr now points to function foo `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

One common mistake is to do this:

` fcnPtr = goo(); `  

This would actually assign the return value from a call to function `goo()` to `fcnPtr`, which isn't what we want. We want `fcnPtr` to be assigned the address of function `goo`, not the return value from function `goo()`. So no parenthesis are needed.

Note that the type (parameters and return type) of the function pointer must match the type of the function. 

` // function prototypes `  
` int foo(); `  
` double goo(); `  
` int hoo(int x); `  

` // function pointer assignments `  
` int (*fcnPtr1)(){ &foo }; // okay `  
` int (*fcnPtr2)(){ &goo }; // wrong -- return types don't match `  
` double (*fcnPtr4)(){ &goo }; // okay `  
` fcnPtr1 = &hoo; // wrong -- fcnPtr1 has no parameters, but hoo() does `  
` int (*fcnPtr3)(int){ &hoo }; // okay `  

Unlike fundamental types, C++ will implicitly convert a function into a function pointer if needed (so you don't need to use the address-of operator (&) to get the function's address). However, it will not implicitly convert function pointers to void pointers, or vice-versa.

### Calling a function using a function pointer

The other primary thing you can do with a function pointer is use it to actually call the function. There are two ways to do this. The first is via explicit dereference:

` int foo(int x) `  
` { `  
&emsp;&emsp;&emsp;` return x; `  
` } `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` int (*fcnPtr)(int){ &foo }; // initialize fcnPtr with function foo `  
&emsp;&emsp;&emsp;` (*fcnPtr)(5); // call function foo(5) through fcnPtr. `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

The second way is via implicit dereference:

` int foo(int x) `  
` { `  
&emsp;&emsp;&emsp;` return x; `  
` } `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` int (*fcnPtr)(int){ &foo }; // Initialize fcnPtr with function foo `  
&emsp;&emsp;&emsp;` fcnPtr(5); // call function foo(5) through fcnPtr. `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

The implicit dereference method looks just like a normal function call -- which is what you'd expect, since normal function names are pointers to functions anyway. However, some older compilers do not support the implicit dereference method, but all modern compilers should.

Default parameters will not work for functions called through function pointers. Default parameters are resolved at compile-time (that is, if you don't supply an argument for a defaulted parameter, the compiler substitutes one in for you when the code is compiled). However, function pointers are resolved at run-time. Consequently, default parameters can not be resolved when making a function call with a function pointer. You'll explicitly have to pass in values for any defaulted parameters in this case.

### Passing functions as arguments to other functions

One of the most useful things to do with function pointers is pass a function as an argument to another function. Functions used as arguments to another function are sometimes called **callback functions**.

Consider a case where you are writing a function to perform a task (such as sorting an array), but you want the user to be able to define how a particular part of that task will be performed (such as whether the array is sorted in ascending or descending order). 

Many comparison-based sorting algorithms work on a similar concept: the sorting algorithm iterates through a list of numbers, does comparisons on pairs of numbers, and reorders the numbers based on the results of those comparisons. Consequently, by varying the comparison, we can change the way the algorithm sorts without affecting the rest of the sorting code.

Here's the previously introduced selection sort routine: 

` #include <utility> // for std::swap `  

` void selectionSort(int *array, int size) `  
` { ` 
&emsp;&emsp;&emsp;` for(int startIndex{ 0 }; startIndex < (size - 1); ++startIndex) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` int smallestIndex{ startIndex }; `  

&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` for(int currentIndex{ startIndex + 1 }; currentIndex < size; ++currentIndex) `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` if(array[smallestIndex] > array[currentIndex]) `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` smallestIndex = currentIndex; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` } `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` } `  

&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::swap(array[startIndex], array[smallestIndex]); `  

&emsp;&emsp;&emsp;` } `  
` } `  

Let's replace that comparison with a function to do the comparison. Because our comparison function is going to compare two integers and return a boolean value to indicate whether the elements should be swapped, it will look something like this:  

` bool ascending(int x, int y) `  
` { `  
&emsp;&emsp;&emsp;` return x > y; // swap if the first element is greater than the second `  
` } `  

Here's the selection sort routine using the ascending() function to do the comparison:

` #include <utility> `  

` void selectionSort(int *array, int size) `  
` { `  
&emsp;&emsp;&emsp;` for(int startIndex{ 0 }; startIndex < (size - 1); ++startIndex) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` int smallestIndex{ startIndex }; `  

&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` for(int currentIndex{ startIndex + 1 }; currentIndex < size; ++currentIndex) `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` if(ascending(array[smallestIndex], array[currentIndex])) `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` smallestIndex = currentIndex; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` } `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` } `  

&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::swap(array[startIndex], array[smallestIndex]); `  

&emsp;&emsp;&emsp;` } `  
` } `  

Now, in order to let the caller decide how the sorting will be done, instead of using our own hard-coded comparison function, we'll allow the caller to provide their own sorting function. This is done via a function pointer.

Because the caller's comparison function is going to compare two integers and return a boolean value, a pointer to such a function would look something like this:  

` bool (*comparisonFcn)(int, int); `  

We'll allow the caller to pass our sort routine a pointer to their desired comparison function as the third parameter, and then we'll use the caller's function to do the comparison.

Here's a full example of a selection sort that uses a function pointer parameter to do a user-defined comparison, along with an example of how to call it:

` #include <utility> `  
` #include <iostream> `  

` void selectionSort(int *array, int size, bool (*comparisonFcn)(int, int)) `  
` { `  
&emsp;&emsp;&emsp;` for(int startIndex{ 0 }; startIndex < (size - 1); ++startIndex) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` int bestIndex{ startIndex }; `  

&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` for(int currentIndex{ startIndex + 1 }; currentIndex < size; ++currentIndex) `   
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` if(comparisonFcn(array[bestIndex], array[currentIndex])) `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` bestIndex = currentIndex; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` } `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` } `  

&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::swap(array[startIndex], array[bestIndex]); `  
&emsp;&emsp;&emsp;` } `  
` } `  

` bool ascending(int x, int y) `  
` { `  
&emsp;&emsp;&emsp;` return x > y; `  
` } `  

` bool descending(int x, int y) `  
` { `  
&emsp;&emsp;&emsp;` return x < y; `  
` } `  

` void printArray(int *array, int size) `  
` { `  
&emsp;&emsp;&emsp;` for(int index{ 0 }; index < size; ++index) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << array[index] << ' '; `  
&emsp;&emsp;&emsp;` } `  

&emsp;&emsp;&emsp;` std::cout << '\n'; `  
` } `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` int array[9]{ 3, 7, 9, 5, 6, 1, 8, 2, 4 }; `  

&emsp;&emsp;&emsp;` selectionSort(array, 9, descending); `  
&emsp;&emsp;&emsp;` printArray(array, 9); `  

&emsp;&emsp;&emsp;` selectionSort(array, 9, ascending); `  
&emsp;&emsp;&emsp;` printArray(array, 9); `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

We've given the caller the ability to control how selection sort does its job.

The caller can even define their own comparison functions:

` bool evensFirst(int x, int y) `  
` { `  
&emsp;&emsp;&emsp;` // if x is even and y is odd, x goes first (no swap needed) `  
&emsp;&emsp;&emsp;` if((x % 2 == 0) && !(y % 2 == 0)) `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` return false; `  

&emsp;&emsp;&emsp;` // if x is odd and y is even, y goes first (swap needed) `  
&emsp;&emsp;&emsp;` if(!(x % 2 == 0) && (y % 2 == 0)) `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` return true; `  

&emsp;&emsp;&emsp;` // otherwise sort in ascending order `  
&emsp;&emsp;&emsp;` return ascending(x, y); `  
` } `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` int array[9]{ 3, 7, 9, 5, 6, 1, 8, 2, 4 }; `  

&emsp;&emsp;&emsp;` selectionSort(array, 9, evensFirst); `  
&emsp;&emsp;&emsp;` printArray(array, 9); `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

Using a function pointer in this context provides a nice way to allow a caller to "hook" their own functionality into something you've previously written and tested, which helps facilitate code reuse. Previously, if you wanted to sort one array in descending order and another in ascending order, you'd need multiple versions of the sort routine. Now you can have one version that can sort any way the caller desires.

Note: if a function parameter is of a function type, it will be converted to a pointer to the function type. This means:  

` void selectionSort(int *array, int size, bool (*comparisonFcn)(int, int)) `  

can be equivalently written as:

` void selectionSort(int *array, int size, bool comparisonFcn(int, int)) `  

This only works for function parameters, not stand-alone function pointers, and so is of somewhat limited use.


### Providing default functions

If you're going to allow the caller to pass in a function as a parameter, it can often be useful to provide some standard functions for the caller to use for their convenience. For example, in the selection sort example above, providing the ascending() and descending() function along with the selectionSort() function would make the caller's life easier, as they wouldn't have to rewrite ascending() or descending() every time they want to use them.

You can even set one of these as a default parameter:

` // Default the sort to ascending sort `  
` void selectionSort(int *array, int size, bool (*comparisonFcn)(int, int) = ascending); `  

In this case, as long as the user calls `selectionSort` normally (not through a function pointer), the `comparisonFcn` parameter will default to ascending. 

### Making function pointers prettier with type aliases

Type aliases can be used to make pointers to functions look more like regular variables:

` using ValidateFunction = bool(*)(int, int); `  

This defines a type alias called "ValidateFunction" that is a pointer to a function that takes two ints and returns a bool.

Now instead of doing this:

` bool validate(int x, int y, bool (*fcnPtr)(int, int)); `  

You can do this:  

` bool validate(int x, int y, ValidateFunction pfcn); // clean `  

### Using std::function

An alternate method of defining and storing function pointers is to use `std::function`, which is part of the standard library `<functional>` header. To define a function pointer using this method, declare a `std::function` object like so: 

` #include <functional> `  
` bool validate(int x, int y, std::function<bool(int, int)> fcn); // std::function method that returns a bool and takes two int parameters `  

Both the return type and parameters go inside angled brackets, with the parameters inside parenthesis. If there are no parameters, the parentheses can be left empty. Although this reads a little more verbosely, it's also more explicit, as it makes it clear what the return type and parameters expected are (whereas the typedef method obscures them).

Updating our earlier example with `std::function`:

` #include <functional> `  
` #include <iostream> `  

` int foo() `  
` { `  
&emsp;&emsp;&emsp;` return 5; `  
` } `  

` int goo() `  
` { `  
&emsp;&emsp;&emsp;` return 6; `  
` } `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` std::function<int()> fcnPtr{ &foo }; // declare function pointer that returns an int and takes no parameters `  
&emsp;&emsp;&emsp;` fcnPtr = &goo; // fcnPtr now points to function goo `  
&emsp;&emsp;&emsp;` std::cout << fcnPtr() << '\n'; // call the function just like normal `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

This has a cleaner syntax. The downside is that all of the details about the function's parameters types and return type are hidden, so it's easier to make a mistake when making a call with the function, or using its return value.

...  

Function pointers are useful primarily when you want to store functions in an array (or other structure), or when you need to pass a function to another function. Because the native syntax to declare function pointers is ugly and error prone, we recommend using `std::function`. In places where a function pointer type is only used once (e.g. a single parameter or return value), `std::function` can be used directly. In places where a function pointer type is used multiple times, a type alias to `std::function` is a better choice (to prevent repeating yourself).

