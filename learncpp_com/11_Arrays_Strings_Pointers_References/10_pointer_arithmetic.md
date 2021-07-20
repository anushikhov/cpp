# Pointer arithmetic and array indexing

## Pointer arithmetic

The C++ language allows you to perform integer addition or subtraction operations on pointers. If `ptr` points to an integer, `ptr + 1` is the address of the next integer in memory after `ptr`. `ptr - 1` is the address of the previous integer before `ptr`.

`ptr + 1` does not return the memory address after `ptr`, but the memory address of the next object of the type that `ptr` points to. If `ptr` points to an integer (assuming 4 bytes), `ptr + 3` means 3 integers (12 bytes) after `ptr`. If `ptr` points to a `char`, which is always 1 byte, `ptr + 3` means 3 chars (3 bytes) after `ptr`.

When calculating the result of a pointer arithmetic expression, the compiler always multiplies the integer operand by the size of the object being pointed to. This is called **scaling**.


## Arrays are laid out sequentially in memory

By using the address-of operator (&), we can determine that arrays are laid out sequentially in memory. That is, elements 0, 1, 2, 3, ... are all adjacent to each other, in order.

## Pointer arithmetic, arrays, and the magic behind indexing

Arrays are laid out sequentially in memory. A fixed array can decay into a pointer that points to the first element (element 0) of the array. Adding 1 to a pointer return the memory address of the next object of that type in memory. Therefore, we might conclude that adding 1 to an array should point to the second element (element 1) of the array. 

` #include <iostream> `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` int array[]{ 9, 7, 5, 3, 1 }; `  

&emsp;&emsp;&emsp;` std::cout << &array[1] << '\n'; // print memory address of array element 1 `  
&emsp;&emsp;&emsp;` std::cout << array+1 << '\n'; // print memory address of array pointer + 1 `  

&emsp;&emsp;&emsp;` std::cout << array[1] << '\n'; // prints 7 `  
&emsp;&emsp;&emsp;` std::cout << *(array+1) << '\n'; // prints 7 `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

When performing indirection through the result of pointer arithmetic, parenthesis are necessary to ensure the operator precedence is correct, since operator\* has higher precedence than operator+.

When the compiler sees the subscript operator ([]), it actually translates that into a pointer addition and indirection. Generalizing, `array[n]` is the same as `*(array + n)`, where n is an integer. The subscipt operator [] is there both to look nice and for ease of use.

## Using a pointer to iterate through an array

We can use a pointer and pointer arithmetic to loop through an array. Although not commonly done this way (using subscripts is generally easier to read and less error prone), the following example goes to show it is possible:  

` #include <iostream> `  
` #include <iterator> `  

` bool isVowerl(char ch) `  
` { `  
&emsp;&emsp;&emsp;` switch(ch) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` case 'A': `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` case 'a': `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` case 'E': `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` case 'e': `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` case 'I': `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` case 'i': `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` case 'O': `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` case 'o': `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` case 'U': `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` case 'u': `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` return true; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` default: `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` return false; `  
&emsp;&emsp;&emsp;` } `  
` } `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` char name[]{ "Mollie" }; `  
&emsp;&emsp;&emsp;` int arrayLength{ static_cast<int>(std::size(name)) }; `  
&emsp;&emsp;&emsp;` int numVowels{ 0 }; `  

&emsp;&emsp;&emsp;` for(char* ptr{ name }; ptr != (name + arrayLength); ++ptr) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` if(isVowel(*ptr)) `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` ++numVowels; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` } `  
&emsp;&emsp;&emsp;` } `  

&emsp;&emsp;&emsp;` std::cout << name << " has " << numVowels << " vowels.\n"; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

Because counting elements is common, the algorithms library offers `std::count_if`, which counts elements that fulfill a condition. We can replace the `for` loop with a call to `std::count_if`:

` auto numVowerls{ std::count_if(std::begin(name), std::end(name), isVowel) }; `  

`std::begin` returns an iterator (pointer) to the first element, while `std::end` returns an iterator to the element that would be one after the last. The iterator returned by `std::end` is only used as a marker, accessing it causes undefined behavior, because it doesn't point to a real element.

`std::begin` and `std::end` only work on arrays with a known size. If the array decayed to a pointer, we can calculate being and end manually.

` // nameLength is the number of elements in the array. `  
` std::count_if(name, name + namelength, isVowel); `  

` // Don't do this, accessing invalid indexes causes undefined behavior. `  
` // std::count_if(name, &name[nameLength], isVowel); `  

We're calculating `name + namelength`, not `name + namelength - 1`, because we don't want the last element, but the pseudo-element one past the last.

Calculating begin and end of an array like this works for all algorithms that need a begin and end argument.

...   

The subscript operator ([]) is identical to an addition and an indirection, the operands can be swapped. 

` arr[2] `  
` // same as `  
` *(arr + 2) `  
` // same as `  
` *(2 + arr) `  
` // same as `  
` 2[arr] `  

It's an interesting observation, but don't use this syntax in real code. This only works for the built-in subscript operator. 
