# Additional algorithms to be used

`std::reduce` applies a function, by default the + operator, to all elements in a list, resulting in a single value. When we use the + operator, the result is the sum of all elements in the list. 

There's also `std::accumulate` for the same purpose, but it cannot be parallelized, because it applies the function left-to-right. `std::reduce` segments the list, which means that the function is applied in an unknown order, allowing the operation to be parallelized. If we want to sum up a list, we don't care about the order and we use `std::reduce`.  

`std::reduce` is currently not fully implemented in all major standard libraries.

`std::shuffle` takes a list and randomly re-orders its elements. 

` #include <algorithm> // std::shuffle `  
` #include <array> `  
` #include <ctime> `  
` #include <iostream> `  
` #include <numeric> // std::reduce `  
` #include <random> `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` std::array arr{ 1, 2, 3, 4 }; `  

&emsp;&emsp;&emsp;` std::cout << std::reduce(arr.begin(), arr.end()) << '\n'; // 10 `  

&emsp;&emsp;&emsp;` // 0 is the initial value of the result: 0 + (((1 + 2) + 3) + 4). `  
&emsp;&emsp;&emsp;` std::cout << std::accumulate(arr.begin(), arr.end(), 0) <<'\n'; //10 `  

&emsp;&emsp;&emsp;` std::mt19937 mt{ static_cast<std::mt19937::result_type>(std::time(nullptr)) }; `  
&emsp;&emsp;&emsp;` std::shuffle(arr.begin(), arr.end(), mt); `  

&emsp;&emsp;&emsp;` for(int i : arr) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << i << ' '; `  
&emsp;&emsp;&emsp;` } `  

&emsp;&emsp;&emsp;` std::cout << '\n'; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  
