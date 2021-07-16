# Function templates

## Introduction to C++ templates

In C++, the template system was designed to simplify the process of creating functions (or classes) that are able to work with different data types.

Instead of manually creating a bunch of mostly-identical functions or classes (one for each set of different types), we instead create a single template. Just like a normal definition, a **template** describes what a function or class looks like. Unlike a normal definition (where all types must be specified), in a template we can use one or more placeholder types. A placeholder type represents some type that is not known at the time the template is written, but that will be provided later.

Once a template is defined, the compiler can use the template to generate as many overloaded functions (or classes) as needed, each using different actual types.

The end result is the same -- we end up with a bunch of mostly-identical functions or classes (one for each set of different types). But we only have to create and maintain a single template, and the compiler does all the hard work for us.

**The compiler can use a single template to generate a family of related functions or classes, each using a different set of types.**

Because the actual types aren't determined until the template is used in a program (not when the template is written), the author of the template doesn't have to try to anticipate all of the actual types that might be used. This means template code can be used with types that didn't even exist when the template was written. C++ standard library is full of template code.

**Templates can work with types that didn't even exist when the template was written. This helps make template code both flexible and future proof.**  


## Function templates

A **function template** is a function-like definition that is used to generate one or more overloaded functions, each with a different set of actual types. 

When creating a function template, we use placeholder types (also called **template types**) for any parameter types, return types, or types used in the function body that we want to be specified later.

### Creating a templated max function

` int max(int x, int y) `  
` { `  
&emsp;&emsp;&emsp;` return (x > y) ? x : y; `  
` } `  

To create a function template, we're to do two things: First, we need to replace specific types with template types. It's common to use single capital letters (starting with T) to represent template types. Second, we need to tell the compiler that this is a function template, and that T is a template type. This is done using what is called a **template parameter declaration**:

` template <typename T> // this is the template parameter declaration `  
` T max(T x, T y)  // this is the function template definition for max<T> `  
` { `  
&emsp;&emsp;&emsp;` return (x > y) ? x : y; `  
` } `  

**Best practice**<br/>
_Use a single capital letter (starting with T) to name your template types (e.g. T, U, V, etc...)._  

When declaring templates, we start with the keyword `template`, which tells the compiler that we're creating a template. Next, we specify all of the template types that our template will use inside angled brackets (<>). For each template type, we use the keyword `typename` or `class`, followed by the name of the template type (e.g. T).

Each template function (or template class) needs its own template parameter declaration.

There is no difference between the `typename` and `class` keywords in this context. You will often see people use the `class` keyword since it was introduced into the language earlier. However, we prefer the newer `typename` keyword, because it makes it clearer that the template type can be replaced by any type (such as a fundamental type), not just class types.

Because the function template has one template type named T, we refer to it as max<T>.
