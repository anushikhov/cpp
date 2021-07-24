# For-each loops

` #include <iostream> `  
` #include <iterator> `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` constexpr int scores[]{ 84, 92, 76, 81, 56 }; `  
&emsp;&emsp;&emsp;` constexpr int numStudents{ std::size(scores) }; `  

&emsp;&emsp;&emsp;` int maxScores{ 0 }; `  
&emsp;&emsp;&emsp;` for(int student{ 0 }; student < numStudents; ++student) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` if(scores[student] > maxSxore) `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` { `   
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` maxScore = scores[student]; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` } `  
&emsp;&emsp;&emsp;` } `  

&emsp;&emsp;&emsp;` std::cout << "The best score was " << maxScore << '\n'; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

While for loops provide a convenient and flexible way to iterate through an array, they are also easy to mess up and prone to off-by-one errors.

There's a simpler and safer type of loop called a **for-each** loop (also called a **range-based for-loop**) for cases where we want to iterate through every element in an array (or other list-type structure).

## For-each loops

The for-each statement has a syntax that looks like this:  

` for (element_declaration: array) `  
&emsp;&emsp;&emsp;` statement; `  

When this statement encountered, the loop will iterate through each element in array, assigning the value of the current array element to the variable declared in element_declaration. For best results, element_declaration should have the same type as the array elements, otherwise type conversion will occur.

` #include <iostream> `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` constexpr int fibonacci[]{ 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89 }; `  
&emsp;&emsp;&emsp;` for(int number : fibonacci) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << number << ' '; `  
&emsp;&emsp;&emsp;` } `  

&emsp;&emsp;&emsp;` std::cout << '\n'; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

When the for loop executes, the variable `number` is set to the value of the first element. The program executes the statement, which prints 0. Then the for loop executes again, and `number` is set to the value of the second number. The loop continues to iterate through each of the numbers in turn, executing the statement for each one, until there are no elements left in the array to iterate over. At that point, the loop terminates, and the program continues execution (returning 0 to the operating system). Note that variable `number` is not an array index. It's assinged the value of the array element for the current loop iteration.

## For each loops and the auto keyword

Because element_declaration should have the same type as the array elements, this is an ideal case in which to use the `auto` keyword, and let C++ deduce the type of the array elements for us.

## For each loops and references

In the following for-each example, our element declarations are declared by value:

` std::string array[]{ "an", "likes", "strawberry", "ice-cream" }; `  
` for(auto element: array) `  
` { `  
&emsp;&emsp;&emsp;` std::cout << element << ' '; `  
` } `  

This means each array element iterated over will be copied into variable element. Copying array elements can be expensive, and most of the time we really just want to refer to the original element. Fortunately, we can use references for this: 

` std::string array[]{ "an", "likes", "strawberry", "ice-cream"}; `  
` for(auto& element: array) `  
` { `  
&emsp;&emsp;&emsp;` std::cout << element << ' '; `  
` } `  

`element` will be a reference to the currently iterated array element, avoiding having to make a copy. Also any changes to element will affect the array being iterated over, something not possible if element is a normal variable.

It is a good idea to make your reference `const` if you're intending to use it in a read-only fashion:

` std::string array[]{ "an", "likes", "strawberry", "ice-cream" }; `  
` for(const auto& element: array) `  
` { `  
&emsp;&emsp;&emsp;` std::cout << element << ' '; `  
` } `  

**Best practice**<br/> 
_In for-each loops element declarations, if your elements are non-fundamental types, use references or const references for performance reasons._

## Rewriting the max scores example using a for-each loop

` #include <iostream> `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` constexpr int scores[]{ 84, 92, 76, 81, 56 }; `  
&emsp;&emsp;&emsp;` int maxScore{ 0 }; `  

&emsp;&emsp;&emsp;` for(auto score : scores) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` if(score > maxScore) `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` maxScore = score; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` } `  
&emsp;&emsp;&emsp;` } `  

&emsp;&emsp;&emsp;` std::cout << "The best score was " << maxScore << '\n'; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

We no longer have to manually subscript the array or get its size. We can access the array element directly through variable score. The array has to have size information. An array that decayed to a pointer cannot be used in a for-each loop.

## For-each loops and non-arrays

For-each loops don't only work with fixed arrays, they work with many kinds of list-like structures, such as vectors (e.g. `std::vector`), linked lists, trees, and maps. For-each loops provide flexible and generic way to iterate through more than just arrays.

` include <iostream> `  
` include <vector> `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` std::vector fibonacci{ 0, 1, 1, 2, 3, 5, 8, 13, 21 ,34, 55, 89 }; `  
&emsp;&emsp;&emsp;` // Before C++17 `  
&emsp;&emsp;&emsp;` // std::vector<int> fibonacci{ 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89 }; `  

&emsp;&emsp;&emsp;` for(auto number : fibonacci) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << number << ' '; `  
&emsp;&emsp;&emsp;` } `  

&emsp;&emsp;&emsp;` std::cout << '\n'; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

## For-each doesn't work with pointers to an array

In order to iterate through the array, for-each needs to know how big the array is, which means knowing the array size. Because arrays that have decayed into a pointer do no know their size, for-each loops will not work with them. 
` #include <iostream> `  

` int sumArray(const int array[]) // array is a pointer `  
` { `  
&emsp;&emsp;&emsp;` int sum{ 0 }; `  

&emsp;&emsp;&emsp;` for(auto number : array) // compile error, the size of array isn't known `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` sum += number; `  
&emsp;&emsp;&emsp;` } `  

&emsp;&emsp;&emsp;` return sum; `  
` } `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` constexpr int array[]{ 9, 7, 5, 3, 1 }; `  

&emsp;&emsp;&emsp;` std::cout << sumArray(array) << '\n'; // array decays into a pointer here `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

Similarly, dynamic arrays won't work with for-each loops for the same reason.

## Index of the current element  

For-each loops do not provide a direct way to get the array index of the current element. This is because many of the structures that for-each loops can be used with (such as linked lists) are not directly indexable.

Since C++20, range-based for-loops can be used with an **init-statement** just like the init-statement in if-statements. We can use the init-statement to create a manual index counter without polluting the function in which the for-loop is placed. 

The init-statement is palced right before the loop variable:

` for (init-statement; element_declaration : array) `  
&emsp;&emsp;&emsp;` statement; `  

In the following code, we have two arrays which are correlated by index. For example, the student with the name at `names[3]` has a score of `scores[3]`. Whenever a student with a new high score is found, we print their name and difference in points to the previous high score.

` #include <iostream> `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` std::string names[]{ "Alex", "Betty", "Caroline", "Dave", "Emily" }; `  

&emsp;&emsp;&emsp;` constexpr int scores[]{ 84, 92, 76, 81, 56 }; `  
&emsp;&emsp;&emsp;` int maxScore{ 0 }; `  

&emsp;&emsp;&emsp;` for(int i{ 0 }; auto score : scores) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` if(score > maxScore) `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` { `   
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << names[i] << " beat the previous best score of " << maxScore << " by " << (score - maxScore) << " points!\n"; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` maxScore = score; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` } `  
 
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` ++i; `   
&emsp;&emsp;&emsp;` } `  

&emsp;&emsp;&emsp;` std::cout << "The best score was " << maxScore << '\n'; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

The `int i{ 0 };` is the init-statement , it only gets executed once when the loop starts. At the end of each iteration, we increment `i`, similar to a normal for-loop. However, if we were to use `continue` inside the loop, the `++i` would get skipped, leading to unexpected results. If yo use `continue`, you need to make sure that `i` gets incremented before the `continue` is encountered.

Before C++20, the index variable `i` had to be declared outside of the loop, which could lead to name conflicts when we wanted to define another variable named `i` later in the function.

...  

For-each loops provide a superior syntax for iterating through an array when we need to access all of the array elements in forwards sequential order. It should be preferred over the standard for loop in the cases where it can be used. To prevent making copies of each element, the element declaration should ideally be a reference.
