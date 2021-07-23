# Member selection with pointers and references

It is common to have either a pointer or a reference to a struct (or class).

You can select the member of a struct using the **member selection operator (.)**:

` struct Person `  
` { `  
&emsp;&emsp;&emsp;` int age{}; `  
&emsp;&emsp;&emsp;` double weight{}; `  
` }; `  

` Person person{}; `  

` person.age = 5; `  

This syntax also works for references: 

` Person& ref{ person }; `  
` ref.age = 5; `  

However, with a pointer, you need to use the arrow operator:

` Person* ptr{ &person }; `  
` ptr->age = 5; `  

The arrow operator does the same as an indirection followed by the (.) member selection operator: 

` (*ptr).age = 5; `  
` ptr->age = 5; `  

Note that indirection through the pointer must be enclosed in parentheses, because the member selection operator has a higher precedence than the indirection operator.

The arrow operator is not only easier to type, but is also much less prone to errors because the indirection is implicitly done for you, so there are no precedence issues to worry about. Consequently, when doing member access through a pointer, always use the -> operator instead of the . operator.

**Best practice**<br/> 
_When using a pointer to access the value of a member, use operator-> instead of operator. (the . operator)._

The member selection operator is always applied to the currently selected variable. If you have a mix of pointer and normal member variables, you can see member selections where . and -> are mixed.

` #include <iostream> `  
` #include <string> `  

` struct Paw `  
` { `  
&emsp;&emsp;&emsp;` int claws{}; `  
` } `  

` struct Animal `  
` { `  
&emsp;&emsp;&emsp;` std::string name{}; `  
&emsp;&emsp;&emsp;` Paw paw{}; `  
` } `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` Animal puma{ "Puma", { 5 } }; `  

&emsp;&emsp;&emsp;` Animal* pointy{ &puma }; `  

&emsp;&emsp;&emsp;` // pointy is a pointer, use -> `  
&emsp;&emsp;&emsp;` // paw is not a pointer, use . `  
&emsp;&emsp;&emsp;` std::cout << pointy->paw.claws << '\n'; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  
