# Arrays and loops

When a loop is used to access each array element in turn, this is often called **iterating** through the array.

` #include <iostream> `  
` #include <iterator> `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` constexpr int scores[]{84, 92, 76, 81, 56 }; `   
&emsp;&emsp;&emsp;` constexpr int numStudents{ static_cast<int>(std::size(scores)) }; `  

&emsp;&emsp;&emsp;` int maxScore{ 0 }; `  
&emsp;&emsp;&emsp;` for(int student{ 0 }; student < numStudents; ++student) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` if(scores[student] > maxScore) `   
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` { `   
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` maxScore = scores[student]; `   
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` } `   
&emsp;&emsp;&emsp;` } `  

&emsp;&emsp;&emsp;` std::cout << "The best score was " << maxScore << '\n'; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

Loops are typically used with arrays to do one of three things:
1. Calculate a value (e.g. average, total)  
1. Search for a value (e.g. highest, lowest)  
1. Reorganize the array (e.g. ascending, descending)

When calculating a value, a variable is typically used to hold an intermediate result that is used to calculate the final value.

When searching for a value, a variable is typically used to hold the best candidate value seen so far (or the array index of the best candidate).

Sorting an array typically involves nested loops.

When using loops with arrays, always double-check your loop conditions to make sure you do not introduce off-by-one errors.
