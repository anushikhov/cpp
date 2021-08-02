# Passing arguments by address

**Passing an argument by address** involves passing the address of the argument variable rather than the argument variable itself. Because the argument is an address, the function parameter must be a pointer. The function can then dereference the pointer to access or change the value being pointed to.

Pass by address is typically used with pointers, which most often are used to point to built-in arrays. Fixed arrays decay into pointers when passed to a function, so we have to pass the length as a separate parameter.

It is always a good idea to ensure parameters passed by address are not null pointers before dereferencing them. Dereferencing a null pointer will typically cause the program to crash. 

` #include <iostream> `  

` void printArray(const int* array, int length) `  
` { ` 
&emsp;&emsp;&emsp;` if(!array) `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` return; `  
 
&emsp;&emsp;&emsp;` for(int index{ 0 }; index < length; ++index) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << array[index] << ' '; `  
&emsp;&emsp;&emsp;` } `  
` } `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` int array[6]{ 6, 5, 4, 3, 2, 1 }; `  
&emsp;&emsp;&emsp;` printArray(array, 6); `  
` } `  

### Addresses are actually passed by value

**When you pass a pointer to a function, the pointer's value (the address it points to) is copied from the argument to the function's parameter. In other words, it's passed by value. If you change the function parameter's value, you are only changing a copy. Consequently, the original pointer argument will not be changed.**

` #include <iostream> `  

` void setToNull(int* tempPtr) `  
` { `  
&emsp;&emsp;&emsp;` // we're making tempPtr point at something else, not changing the value that tempPtr points to. `  
&emsp;&emsp;&emsp;` tempPtr = nullptr; // use 0 instead if not C++11 `  
` } `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` int five{ 5 }; `  
&emsp;&emsp;&emsp;` int* ptr{ &five }; `  

&emsp;&emsp;&emsp;` std::cout << *ptr; `  

&emsp;&emsp;&emsp;` setToNull(ptr); `  

&emsp;&emsp;&emsp;` // ptr is still set to the address of five `  

&emsp;&emsp;&emsp;` if(ptr) `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << *ptr; `  
&emsp;&emsp;&emsp;` else `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << " ptr is null"; `  

&emsp;&emsp;&emsp;` return 0; `  
` } ` 

`tempPtr` receives a copy of the address that `ptr` is holding. Even though we change `tempPtr` to point at something else (nullptr), this does not change the value that `ptr` points to.

Note that **even though the address itself is passed by value, you can still dereference that address to change the argument's value**.

* When passing an argument by address, the function parameter variable receives a copy of the address from the argument. At this point, the function parameter and the argument both point to the same value.
* If the function parameter is then dereferenced to change the value being pointed to, that will impact the value the argument is pointing to, since both the function parameter and argument are pointing to the same value.
* If the function parameter is assigned a different address, that will not impact the argument, since the function parameter is a copy, and changing the copy won't impact the original. After changing the function parameter's address, the function parameter and argument will point to different values, so dereferencing the parameter and changing the value will no longer affect the value pointed to by the argument.

` #include <iostream> `  

` void setToSix(int* tempPtr) `  
` { `  
&emsp;&emsp;&emsp;` *tempPtr = 6; `  
` } `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` int five{ 5 }; `  
&emsp;&emsp;&emsp;` int* ptr{ &five }; `  

&emsp;&emsp;&emsp;` std::cout << *ptr; `  

&emsp;&emsp;&emsp;` setToSix(ptr); `  

&emsp;&emsp;&emsp;` // tempPtr changed the value being pointed to to 6, so ptr is now pointing to the value 6 `  

&emsp;&emsp;&emsp;` if(ptr) `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << *ptr; `  
&emsp;&emsp;&emsp;` else `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << " ptr is null"; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

### Passing addresses by reference

To change the address an argument points to from within the function, we need to pass the address by reference.

` #include <iostream> `  

` void setToNull(int*& tempPtr) `  
` { `  
&emsp;&emsp;&emsp;` tempPtr = nullptr; `  
` } `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` int five{ 5 }; `  
&emsp;&emsp;&emsp;` int* ptr{ &five }; `  


&emsp;&emsp;&emsp;` std::cout << *ptr; `  

&emsp;&emsp;&emsp;` setToNull(ptr); `  

&emsp;&emsp;&emsp;` // ptr has now been changed to null `  

&emsp;&emsp;&emsp;` if(ptr) `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << *ptr; `  
&emsp;&emsp;&emsp;` else `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << " ptr is null"; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

### There is only pass by value

References are typically implemented by the compiler as pointers. This means that behind the scenes, pass by reference is essentially just a pass by address (with access to the reference doing an implicit dereference). And pass by address is actually just passing an address by value. Therefore, we can conclude that C++ really passes everything by value. The properties of pass by address (and reference) come solely from the fact that we can dereference the passed address to change the argument, which we can not do with a normal value parameter.

### Pass by address makes modifiable parameters explicit

` int foo1(int x); // pass by value `  
` int foo2(int& x); // pass by reference `  
` int foo3(int* x); // pass by address `  

` int i {}; `  

` foo1(i); // can't modify i `  
` foo2(i); // can modify i `  
` foo3(&i); // can modify i `  

It's not obvious from the call to foo2() that the function can modify variable i. For this reason, some guides recommend passing all modifiable arguments by address, so that it's more obvious from an existing function call that an argument could be modified.

However, this comes with its own set of downsides: the caller might think they can pass in nullptr when they aren't supposed to, and you now have to rigorously check for null pointers.

We lean towards the recommendation of passing non-optional modifiable parameters by reference. Even better, avoid modifiable parameters altogether.


### Pros and cons of pass by address

Advantages of passing by address:

* Pass by address allows a function to change the value of the argument, which is sometimes useful. Otherwise, const can be used to guarantee the function won't change the argument. (However, if you want to do this with a non-pointer, you should use pass by reference instead).  
* Because a copy of the argument is not made, it is fast, even when used with large structs or classes.  
* We can return multiple values from a function  via out parameters.  

Disadvantages of passing by address:

* Because literals (excepting C-style string literals) and expressions do not have addresses, pointer arguments must be normal variables.  
* All values must be checked to see whether they are null. Trying to dereference a null value will result in a crash. It is easy to forget to do this.
* Because dereferencing a pointer is slower than accessing a value directly, accessing arguments passed by address is slower than accessing arguments passed by value.  

When to use pass by address:  

* When passing built-in arrays (if it is okay that they'll decay into a pointer).  
* When passing a pointer and nullptr is a valid argument logically.  

When not to use pass by address:  

* When passing a pointer and nullptr is not a valid argument logically (use pass by reference).  
* When passing structs or classes (use pass by reference).  
* When passing fundamental types (use pass by value).  

Pass by address and pass by reference have almost identical advantages and disadvantages. Because pass by reference is generally safer than pass by address, pass by reference should be preferred in most cases.  

**Best practice**<br/>
_Prefer pass by reference to pass by address whenever applicable._
