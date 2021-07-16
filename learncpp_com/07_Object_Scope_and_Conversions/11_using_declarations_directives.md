# Using declarations and using directives

## Qualified and unqualified names

A **qualified name** is a name that includes an associated scope. Most often, names are qualified with a namespace using the scope resolution operator (::). 

` std::cout // identifier cout is qualified by namespace std `  
` ::foo // identifier foo is qualified by the global namespace `  

A name can also be qualified by a class name using the scope resolution operator (::), or by a class object using the member selection operator (. or ->).

` class C; // some class `  
` C::s_member; // s_member is qualified by class C `  
` obj.x; // x is qualified by class object obj `  
` ptr->y; // y is qualified by pointer to class object ptr `  

An **unqualified name** is a name that does not include a scoping qualifier. For example, cout and x are unqualified names, as they do not include an associated scope.


## Using declarations

A **using declaration** allows us to use an unqualified name (with no scope) as an alias for a qualified name.

` #include <iostream> `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` using std::cout; // this using declaration tells the compiler that cout should resolve to std::cout `  
&emsp;&emsp;&emsp;` cout << "Hello world!"; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

If you are using cout many times inside of a function, a using declaration can make your code more readable. You will need a separate using declaration for each name (e.g. one for std::cout, one for std::cin, etc...).

Although this method is less explicit than using the std:: prefix, it's generally considered safe and acceptable (when used inside a function).

## Using directives

A **using directive** imports all of the identifiers from a namespace into the scope of the using directive.

` #include <iostream> `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` using namespace std; `  
&emsp;&emsp;&emsp;` cout << "Hello world!"; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

The using directive `using namespace std;` tells the compiler to import all of the names from the std namespace into the current scope. When we then use unqualified identifier cout, it will resolve to the imported std::cout.

Using directives are the solution that was provided for old pre-namespace codebases that used unqualified names for standard library functionality. Rather than having to manually update every unqualified name to a qualified name (which was risky), a single using directive (of `using namespace std;`) could be placed at the top of each file, and all of the names that had been moved to the std namespace could still be used unqualified.

## Problems with using directives

However, for modern C++ code, using directives offer little benefit (saving some typing) compared to the risk.

Because using directives import all of the names from a namespace (potentially including lots of names you'll never use), the possibility for naming collisons to occur increases significantly (especially if you import the std namespace).

Even if a using directive does not cause naming collisions today, they make code more vulnerable to future collisions. For example, if your code includes a using directive for some library that is then updated, all of the new names introduced in the updated library are now candidates for naming collisions with your existing code.

There is a more insidious problem that can occur as well. The updated library may introduce a function that not only has the same name, but is actually a better match for some function call. In such a case, the compiler may decide to prefer the new function instead, and the behavior of your program will change unexpectedly.

## The scope of using declarations and directives

If a using declaration or using directive is used within a block, the names are applicable to just that block (it follows normal block scoping rules).

If a using declaration or using directive is used in the global namespace, the names are applicable to the entire rest of the file (they have file scope).

Once a using statement has been declared, there's no way to cancel or replace it with a different using statement within the scope in which it was declared.

The best you can do is intentionally limit the scope of the using statement from the outset using the block scoping rules.

Of course, all of this headache can be avoided by explicitly using the scope resolution operator (::) in the first place.

## Best practices for using statements

Modern C++ doesn't really have a place for using directives. They increase the chance for naming collisions now and in the future, and can cause more insidious problems. Although many textbooks and tutorials use them liberally, using directives are best avoided altogether.

Using declarations are generally considered safe to use inside blocks. Limit their use in the global namespace of a code file, and never use them in the global namespace of a header file.

**Best practice**<br/>
_Prefer explicit namespaces over using statements. Avoid using directives altogether. Using declarations are okay to use inside blocks._

