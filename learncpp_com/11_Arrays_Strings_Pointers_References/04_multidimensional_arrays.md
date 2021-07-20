# Multidimensional Arrays

The elements of an array can be of any data type, including arrays. An array of arrays is called a **multidimensional array**.

` int array[3][5]; // a 3-element array of 5-element arrays `  

Since we have 2 subscripts, this is a two-dimensional array.

In a two-dimensional array, it is convenient to think of the first (left) subscript as being the row, and the second (right) subscript as being the column. This is called **row-major** order.

To access the elements of a two-dimensional array, simply use two subscripts:

` array[2][3] = 7; `  

To initialize a two-dimensional array, it is easiest to use nested braces, with each set of numbers representing a row: 

` int array[3][5] `  
` { `  
&emsp;&emsp;&emsp;` { 1, 2, 3, 4, 5 }, `  
&emsp;&emsp;&emsp;` { 6, 7, 8, 9, 10 }, `  
&emsp;&emsp;&emsp;` { 11, 12, 13, 14, 15 } `  
` }; `  

Although some compilers will let you omit the inner braces, we highly recommend you include them anyway, both for readability purposes and because of the way that C++ will replace missing initializers with 0.

` int array[3][5] `  
` { `  
&emsp;&emsp;&emsp;` { 1, 2 }, // row 0 = 1, 2, 0, 0, 0 `  
&emsp;&emsp;&emsp;` { 6, 7, 8 }, // row 1 = 6, 7, 8, 0, 0 `  
&emsp;&emsp;&emsp;` { 11, 12, 13, 14 } // row 2 = 11, 12, 13, 14, 0 `  
` }; `  

Two-dimensional arrays with initializer lists can omit (only) the leftmost length specification: 

` int array[][5] `  
` { `  
&emsp;&emsp;&emsp;` { 1, 2, 3, 4, 5 }, `  
&emsp;&emsp;&emsp;` { 6, 7, 8, 9, 10 }, `  
&emsp;&emsp;&emsp;` { 11, 12, 13, 14, 15 } `  
` }; `  

The compiler can do the math to figure out what the array length is. However, the following is not allowed:

` int array[][] `  
` { `  
&emsp;&emsp;&emsp;` { 1, 2, 3, 4 }, `  
&emsp;&emsp;&emsp;` { 5, 6, 7, 8 } `  
` }; `  

Just like normal arrays, multidimensional arrays can still be initialized to 0 as follows:

` int array[3][5]{}; `  

Accessing all of the elements of a two-deimensional array required two loops: one for the row, and one for the column. Since two-dimensional arrays are typically accessed row by row, the row index is typically used as the outer loop.

` for(int row{ 0 }; row < numRows; ++row) `  
` { `  
&emsp;&emsp;&emsp;` for(int col{ 0 }; col < numCols; ++col) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << array[row][col]; `  
&emsp;&emsp;&emsp;` } `  
` } `  

Two dimensional arrays are commonly used in tile-based games, where each array element represents one tile. They're also used in 3d computer graphics (as matrices) in order to rotate, scale, and reflect shapes.

In C++11, for-each loops can also be used with multidimensional arrays. 


### Multidimensiona arrays larger than two dimensions

Multidimensional arrays may be larger than two dimensions:

` int array[5][4][3]; `  

Three-deimensional array are hard to initialize in any kind of intuitive way using initializer lists, so it's typically better to initialize the array to 0 and explicitly assign values using nested loops.

Accessing the element of a three-dimensional array is analogous to the two-dimensional case:

` std::cout << array[3][1][2]; `  


