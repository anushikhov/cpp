# Introduction to function parameters and arguments

A **function parameter** is a variable used in a function. Function parameters work almost identically to variables defined inside the function, but with one difference: they are always initialized with a value provided by the caller of the function.

Function parameters are defined in the function declaratoin by placing them in between the parenthesis after the function identifier, with multiple parameters being separated by commas.

An **argument** is a value that is passed from the caller to the function when a function call is made.

Multiple arguments are also separated by commas.

When a function is called, all of the parameters of the function are created as variables, and the value of each of the arguments is copied into the matching parameters. This process is called **pass by value**.

The number of arguments must generally match the number of function parameters, or the compiler will throw an error. 

**The C++ specification does not define whether arguments are matched with parameters in left to right order or right to left order. When copying values, order is of no consequence. However, if the arguments are function calls, then this can be problematic:**

` someFunction(a(), b()); // a() or b() may be called first`

If the architecture evaluates left to right, a() will be called before b(). If the architecture evaluation right to left, b() will be called before a(). This may or may not be of consequence, depending on what a() and b() do.

If it is important that one argument evaluate first, you should explicitly define the order of execution, like so:

` int avar{ a() }; // a() will always be called first `  
` int bvar{ b() }; // b() will always  be called second `  

` someFunction(avar, bvar); // it doesn't matter whether avar or bvar are copied first because they are just values`  

**The C++ specification does not define whether function calls evaluate arguments left to right or right to left. Take care not to make function calls where argument order matters.**

By using both parameters and a return value, we can create functions that take data as input; do some calculation with it, and return the value to the caller.

Function parameters and return values are the key mechanisms by which functions can be written in a reusable way, as it allows us to write functions that can perform tasks and return retrieved or calculated results back to the caller without knowing what the specific inputs or outputs are ahead of time.
