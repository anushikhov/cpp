# Structs

C++ allows us to create our own user-defined aggregate data types. An **aggregate data type** is a data type that groups multiple individual variables together. One of the simplest aggregate data types is the struct. A **struct** (short for structure) allows us to group variables of mixed data types together into a single unit.

Here's an example of a struct declaration:

` struct Employee `  
` { `  
&emsp;&emsp;&emsp;` int id{}; `  
&emsp;&emsp;&emsp;` int age{}; `  
&emsp;&emsp;&emsp;` double wage{}; `  
` }; `  

This is just a declaration and no memory is allocated at this time. 

By convention, struct names start with a capital letter to distinguish them from variable names. 

The variables that are part of the struct are called **members** (or fields). 

In order to use the Employee struct, we simply declare a variable of type Employee:

` Employee mia{}; `  
` Employee frank{}; `  

As with normal variables, defining a struct variable allocates memory for that variable. 

In order to access the individual members, we use the **member selection operator** (.):

` Employee mia{}; `  
` mia.id = 31415; `
` mia.age = 27; `  
` mia.wage = 4.669; `  

As with normal variables, struct member variables are not initialized, and will typically contain junk. We must initialize them manually.

Struct member variables act just like normal variables, so it is possible to do normal operations on them:

` int totalAge { mia.age + frank.age }; `  

` if( mia.wage > frank.wage ) `  
&emsp;&emsp;&emsp;` std::cout << "Mia makes more than Frank.\n"; `  

` frank.wage += 1.4; `  

` ++mia.age; `  

C++ supports a faster way to initialize structs using an **initializer list**. This allows you to initialize some or all the members of a struct at declaration time.

` struct Employee `  
` { `  
&emsp;&emsp;&emsp;` int id{}; `  
&emsp;&emsp;&emsp;` int age{}; `  
&emsp;&emsp;&emsp;` double wage{}; `  
` }; `  

` Employee mia{ 1, 32, 700000000.0 }; `  
` Employee frank{ 3, 26 }; `  

If the initializer list does not contain an initializer for some elements, those elements are initialized to a default value (that generally corresponds to the zero state for that type). 

It's possible to give non-static (normal) struct members a default value:

` struct Rectangle `  
` { `  
&emsp;&emsp;&emsp;` double length{ 1.0 }; `  
&emsp;&emsp;&emsp;` double width{ 1.0 }; `  
` }; `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` Rectangle x{}; // length = 1.0, width = 1.0 `  

&emsp;&emsp;&emsp;` x.length = 2.0; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

If both non-static member initializer and list-linitialization are provided, the list-initialization takes precedence.

You can assign values to structs members using an initializer list:

` struct Employee `  
` { `  
&emsp;&emsp;&emsp;` int id{}; `  
&emsp;&emsp;&emsp;` int age{}; `  
&emsp;&emsp;&emsp;` double wage{}; `  
` }; `  

` Employee mia{}; `  

` mia = { 1, 32, 7000000.0 }; `  
` // This is the same as `  
` mia = Employee{ 1, 32, 7000000.0 }; `  

` // It's also possible to copy all members from one variable to another `  
` Employee emma{ mia }; `  

A big advantage of using structs over individual variables is that we can pass the entire struct to a function that needs to work with the members:

` #include <iostream> `  

` struct Employee `  
` { `  
&emsp;&emsp;&emsp;` int id{}; `  
&emsp;&emsp;&emsp;` int age{}; `  
&emsp;&emsp;&emsp;` double wage{}; `  
` }; `  

` void printInformation(Employee employee) `  
` { `  
&emsp;&emsp;&emsp;` std::cout << "ID:   " << employee.id << '\n'; `  
&emsp;&emsp;&emsp;` std::cout << "Age:  " << employee.age << '\n'; `  
&emsp;&emsp;&emsp;` std::cout << "Wage: " << employee.wage << '\n'; `  
` } `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` Employee mia { 14, 32, 24.15 }; `   
&emsp;&emsp;&emsp;` Employee frank { 15, 28, 18.27 }; `  

&emsp;&emsp;&emsp;` printInformation(mia); `  

&emsp;&emsp;&emsp;` std::cout << '\n'; `  

&emsp;&emsp;&emsp;` printInformation(frank); `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

A function can also return a struct, which is one of the few ways to have a function return multiple variables.

` #include <iostream> `  

` struct Point3d `  
` { `  
&emsp;&emsp;&emsp;` double x{}; `  
&emsp;&emsp;&emsp;` double y{}; `  
&emsp;&emsp;&emsp;` double z{}; `  
` }; `  

` Point3d getZeroPoint() `  
` { `  
&emsp;&emsp;&emsp;` Point3d temp { 0.0, 0.0, 0.0 }; `  
&emsp;&emsp;&emsp;` return temp; `  
` } `  

` Point3d getZeroPoint2() `  
` { `  
&emsp;&emsp;&emsp;` return { 0.0, 0.0, 0.0 }; `  
` } `  

` Point32 gerZeroPoint3() `  
` { `  
&emsp;&emsp;&emsp;` return {}; `  
` } `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` Point3d zero{ getZeroPoint() }; `  

&emsp;&emsp;&emsp;` if(zero.x == 0.0 && zero.y == 0.0 && zero.z == 0.0) `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << "The point is zero\n"; `  
&emsp;&emsp;&emsp;` else `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << "The point is not zero\n"; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

Structs can contain other structs:

` struct Employee `  
` { `  
&emsp;&emsp;&emsp;` int id{}; `  
&emsp;&emsp;&emsp;` int age{}; `  
&emsp;&emsp;&emsp;` double wage{}; `  
` }; `  

` struct Company `  
` { `  
&emsp;&emsp;&emsp;` Employee CEO{}; `  
&emsp;&emsp;&emsp;` int numberOfEmployees{}; `  
` }; `  

` Company myCompany; `  

In this case, if we wanted to know what the CEO's salary was, we simply use the member selection operator twice: myCompany.CEO.wage;

This selects the CEO member from myCompany, and then selects the wage member from within CEO.

The nested initializer lists can be used for nested structs:

` struct Employee `  
` { `  
&emsp;&emsp;&emsp;` int id; `  
&emsp;&emsp;&emsp;` int age; `  
&emsp;&emsp;&emsp;` double wage; `  
` }; `  

` struct Company `  
` { `   
&emsp;&emsp;&emsp;` Employee CEO; `  
&emsp;&emsp;&emsp;` int numberOfEmployees; `  
` }; `  

` Company myCompany{{ 1, 42, 700000.0 }, 5 }; `  

### Struct size and data structure alignment

Typically, the size of a struct is the sum of the size of all its members, but not always!

We can use the `sizeof` operator to find out the size of a struct.

We can only say that the size of a struct will be at least as large as the size of all the variables it contains. But it could be larger. For performance reasons, the compiler will sometimes add gaps into structures (this is called **padding**).

### Accessing structs across multiple files

Because struct declarations do not take any memory, if you want to share a struct declaration across multiple files, put the struct declaration in a header file, and `#include` that header file anywhere you need it.

Struct variables are subject to the same rules as normal variables. Consequently, to make a struct variable accessible across multiple files, you can use the `extern` keyword in the declaration in the header and define the variable in a source file.

Classes are built on top of structs. The structs introduced above are sometimes called **plain old data structs** (or POD structs) since the members are all data (variable) members.
