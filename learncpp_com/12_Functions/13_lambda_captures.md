# Lambda captures

## Capture clauses and capture by value  

` #include <algorithm> `  
` #include <array> `  
` #include <iostream> `  
` #include <string_view> `  

` int main() `  
` { `   
&emsp;&emsp;&emsp;` std::array<std::string_view, 4> arr{ "apple", "banana", "walnut", "lemon" }; `  

&emsp;&emsp;&emsp;` auto found{ std::find_if(arr.begin(), arr.end(), `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` [](std::string_view str() `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` return (str.find("nut") != std::string_view::npos); `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` }) }; `  

&emsp;&emsp;&emsp;` if(found == arr.end()) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << "No nuts\n"; `  
&emsp;&emsp;&emsp;` } `  
&emsp;&emsp;&emsp;` else `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << "Found " << *found << '\n'; `  
&emsp;&emsp;&emsp;` } `  

&emsp;&emsp;&emsp;` return 0; `   
` } `  

Let's modify the example and let the user pick a substring to search for.

` #include <algorithm> `  
` #include <array> `  
` #include <iostream> `  
` #include <string_view> `  

` int main() `  
` { `   
&emsp;&emsp;&emsp;` std::array<std::string_view, 4> arr{ "apple", "banana", "walnut", "lemon" }; `  

&emsp;&emsp;&emsp;` // Ask the user what to search for. `  
&emsp;&emsp;&emsp;` std::cout << "search for: "; `  

&emsp;&emsp;&emsp;` std::string search{}; `  
&emsp;&emsp;&emsp;` std::cin >> search; `  

&emsp;&emsp;&emsp;` auto found{ std::find_if(arr.begin(), arr.end(), `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` [](std::string_view str() `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` return (str.find(search) != std::string_view::npos); // error: search not accessible in this scope `   
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` }) }; `  

&emsp;&emsp;&emsp;` if(found == arr.end()) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << "No nuts\n"; `  
&emsp;&emsp;&emsp;` } `  
&emsp;&emsp;&emsp;` else `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << "Found " << *found << '\n'; `  
&emsp;&emsp;&emsp;` } `  

&emsp;&emsp;&emsp;` return 0; `   
` } `  

This code won't compile. Unlike nested blocks, where any identifier defined in an outer block is accessible in the scope of the nested block, lambdas can only access specific kinds of identifiers: global identifiers, entities that are known at compile time, and entities with static storage duration. `search` fulfills none of these requirements, so the lambda can't see it. That's what the capture clause is there for.

## The capture clause  

The **capture clause** is used to (indirectly) give a lambda access to variables available in the surrounding scope that it normally would not have access to. All we need to do is list the entities we want to access from within the lambda as part of the capture clause:

` #include <algorithm> `  
` #include <array> `  
` #include <iostream> `  
` #include <string_view> `  

` int main() `  
` { `   
&emsp;&emsp;&emsp;` std::array<std::string_view, 4> arr{ "apple", "banana", "walnut", "lemon" }; `  

&emsp;&emsp;&emsp;` // Ask the user what to search for. `  
&emsp;&emsp;&emsp;` std::cout << "search for: "; `  

&emsp;&emsp;&emsp;` std::string search{}; `  
&emsp;&emsp;&emsp;` std::cin >> search; `  

&emsp;&emsp;&emsp;` // Capture @search `  
&emsp;&emsp;&emsp;` auto found{ std::find_if(arr.begin(), arr.end(), `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` [search](std::string_view str() `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` return (str.find(search) != std::string_view::npos);  `   
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` }) }; `  

&emsp;&emsp;&emsp;` if(found == arr.end()) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << "No nuts\n"; `  
&emsp;&emsp;&emsp;` } `  
&emsp;&emsp;&emsp;` else `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << "Found " << *found << '\n'; `  
&emsp;&emsp;&emsp;` } `  

&emsp;&emsp;&emsp;` return 0; `   
` } `  

The user can now search for an element of the array.

## So how do captures actually work?  

While it might look lambda in the example above is directly accessing the value of `main`'s `search` variable, this is not the case. Lambdas might look like nested blocks, but they work slightly differently (and the distinction is important).

When a lambda definition is executed, for each variable that the lambda captures, a clone of that variable is made (with an identical name) inside the lambda. These cloned variables are initialized from the outer scope variables of the same name at this point.

Thus, in the above example, when the lambda object is created, the lambda gets its own cloned variable named `search`. This cloned `search` has the same value as `main`'s `search`, so it behaves like we're accessing `main`'s `search`, but we're not. 

While these cloned variables have the same name, they don't necessarily have the same type as the original variable.

**The captured variables of a lambda are clones of the outer scope variable, not the actual variable.**

Lambdas are objects, called **functors** that can be called like functions. When the compiler encounters a lambda definition, it creates a custom object definition for the lambda. Each captured variable becomes a data member of the object. At runtime, when the lambda definition is encountered, the lambda object is instantiated, and the members of the lambda are initialized at that point.

## Captures default to const value  

By default, variables are captured by `const value`. This means when the lambda is created, the lambda captures a constant copy of the outer scope variable, which means that the lambda is not allowed to modify them. 

` #include <iostream> `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` int ammo{ 10 }; `   

&emsp;&emsp;&emsp;` // Define a lambda and store it in a variable called "shoot" `   
&emsp;&emsp;&emsp;` auto shoot{ `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` [ammo]() { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` // Illegal, ammo was captured as a const copy. `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` --ammo; `   

&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << "Pew! " << ammo << " shot(s) left.\n"; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` } `  
&emsp;&emsp;&emsp;` }; `  

&emsp;&emsp;&emsp;` shoot(); `  

&emsp;&emsp;&emsp;` std::cout << ammo << " shot(s) left\n"; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

When we capture `ammo`, a new `const` variable with the same name and value is created in the lambda. We can't modify it, because it is `const`, which causes a compile error.

## Mutable capture by value  

To allow modifications of variables that were captured by value, we can mark the lambda as `mutable`. The **mutable** keyword in this context removes the `const` qualification from all variables captured by value.

` #include <iostream> `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` int ammo{ 10 }; `   

&emsp;&emsp;&emsp;` auto shoot{ `  
&emsp;&emsp;&emsp;` // Added mutable after the parameter list `   
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` [ammo]() mutable { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` // We are allowed to modify ammo now `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` --ammo; `   

&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << "Pew! " << ammo << " shot(s) left.\n"; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` } `  
&emsp;&emsp;&emsp;` }; `  

&emsp;&emsp;&emsp;` shoot(); `  
&emsp;&emsp;&emsp;` shoot(); `  

&emsp;&emsp;&emsp;` std::cout << ammo << " shot(s) left\n"; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

While this now compiles, there's still a logic error. When the lambda was called, the lambda captured a copy of `ammo`. When the lambda decremented `ammo`, it decremented its own copy, not the original value.

The value of `ammo` is preserved across calls to the lambda.

**Because captured variables are members of the lambda object, their values are persisted across multiple calls to the lambda.**

## Capture by reference  

Much like functions can change the value of arguments passed by reference, we can also capture variables by reference to allow lambda to affect the value of the argument.

To capture a variable by reference, we prepend an ampersand (&) to the variable name in the capture. Unlike variables that are captured by value, variables that are captured by reference are non-const, unless the variable they're capturing is `const`. Capture by reference should be preferred over capture by value whenever you would normally prefer passing an argument to a function by reference (e.g. for non-fundamental types).

` #include <iostream> `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` int ammo{ 10 }; `   

&emsp;&emsp;&emsp;` auto shoot{ `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` [&ammo]() mutable { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` // Changes to ammo will affect main's ammo `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` --ammo; `   

&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << "Pew! " << ammo << " shot(s) left.\n"; `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` } `  
&emsp;&emsp;&emsp;` }; `  

&emsp;&emsp;&emsp;` shoot(); `  

&emsp;&emsp;&emsp;` std::cout << ammo << " shot(s) left\n"; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

Let's use a reference capture to count how many comparisons `std::sort` makes when it sorts an array.

` #include <algorithm> `  
` #include <array> `  
` #include <iostream> `  
` #include <string> `  

` struct Car `  
` { `  
&emsp;&emsp;&emsp;` std::string make{}; `  
&emsp;&emsp;&emsp;` std::string model{}; `  
` }; `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` std::array<Car, 3> cars{ { { "Volkswagen", "Golf" }, `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` { "Toyota", "Corolla" }, `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` { "Honda", "Civic" } } }; `  

&emsp;&emsp;&emsp;` int comparisons{ 0 }; `  

&emsp;&emsp;&emsp;` std::sort(cars.begin(), cars.end(), `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` // Capture @comparisons by reference. `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` [&comparisons](const auto& a, const auto& b) { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` // We captured comparisons by reference. We can modify it without "mutable". `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` ++comparisons; `  

&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` // Sort the cars by their make. `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` return (a.make < b.make); `  
&emsp;&emsp;&emsp;` }); `  

&emsp;&emsp;&emsp;` std::cout << "Comparisons: " << comparisons << '\n'; `  

&emsp;&emsp;&emsp;` for(const auto& car : cars) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << car.make << ' ' << car.model << '\n'; `  
&emsp;&emsp;&emsp;` } `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

## Capturing multiple variables  

Multiple variables can be captured by separating them with a comma. This can include a mix of variables captured by value or by reference:

` int health{ 33 }; `  
` int armor{ 100 }; `  
` std::vector<CEnemy> enemies{}; `  

` // Capture health and armor by value, and enemies by reference. `  
` [health, armor, &enemies](){}; `  

## Default captures  

We can enlist the compiler's help to auto-generate a list of variables we need to capture.

A **default capture** (also called a **capture-default**) captures all variables that are mentioned in the lambda. Variables not mentioned in the lambda are not captured if a default capture is used.

To capture all used variables by value, use a capture value of `=`.
To capture all used variables by reference, use a capture value of `&`.

Here's an example of using a default capture by value:

` #include <array> `  
` #include <iostream> `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` std::array areas{ 100, 25, 121, 40, 56 }; `  

&emsp;&emsp;&emsp;` int width{}; `  
&emsp;&emsp;&emsp;` int height{}; `  

&emsp;&emsp;&emsp;` std::cout << "Enter width and height: "; `  
&emsp;&emsp;&emsp;` std::cin >> width >> height; `  

&emsp;&emsp;&emsp;` auto found{ std::find_if(areas.begin(), areas.end(), `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` [=](int knownArea) { // will default capture width and height by value `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` return (width * height == known Area); // because they're mentioned here `  
&emsp;&emsp;&emsp;` }) }; `  

&emsp;&emsp;&emsp;` if(found == areas.end()) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << "I don't know this area: :(\n"; `  
&emsp;&emsp;&emsp;` } `  
&emsp;&emsp;&emsp;` else `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << "Area found :) \n"; `  
&emsp;&emsp;&emsp;` } `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

Default captures can be mixed with normal captures. We can capture some variables by value and others by reference, but each variable can only be captured once.

` int health{ 33 }; `  
` int armor{ 100 }; `  
` std::vector<CEnemy> enemies{}; `  

` // Capture health and armor by value, and enemies by reference. `  
` [health, armor, &enemies](){}; `  

` // Capture enemies by reference and everything else by value. `  
` [=, &enemies](){}; `  

` // Capture armor by value and everything else by reference. `  
` [&, armor](){}; `  

` // Illegal, we already said we want to capture everything by reference. `  
` [ &, &armor](){}; `  

` // Illegal, we already said we wanted to capture everything by value. `  
` [=, armor](){}; `  

` // Illegal, armor appears twice. `  
` [armor, &health, &armor](){}; `  

` // Illegal, the default capture has to be the first element in the capture group. `   
` [armor, &](){}; `  

## Defining new variables in the lambda-capture  

Sometimes we want to capture a variable with a slight modification or declare a new variable that is only visible in the scope of the lambda. We can do so by defining a variable in the lambda-capture without specifying its type.

` #include <array> `  
` #include <iostream> `  
` #include algorithm> `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` std::array areas{ 100, 25, 121, 40, 56 }; `  

&emsp;&emsp;&emsp;` int width{}; `  
&emsp;&emsp;&emsp;` int height{}; `  

&emsp;&emsp;&emsp;` std::cout << "Enter width and height: "; `  
&emsp;&emsp;&emsp;` std::cin >> width >> height; `  

&emsp;&emsp;&emsp;` // We store areas, but the user entered width and height. `  
&emsp;&emsp;&emsp;` // We need to calculate the area before we can search for it. `  
&emsp;&emsp;&emsp;` auto found{ std::find_if(areas.begin(), areas.end(), `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` // Declare a new variable that's visible only to the lambda. `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` // The type of userArea is automatically deduced to int. `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` [userArea{ width * height }](int knownArea) { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` return (userArea == knownArea); `   
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` }) }; `  

&emsp;&emsp;&emsp;` if(found == areas.end()) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << "I don't know this area :(\n"; `  
&emsp;&emsp;&emsp;` } `  
&emsp;&emsp;&emsp;` else `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << "Area found :)\n"; `  
&emsp;&emsp;&emsp;` } `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

`userArea` will only be calculated once when the lambda is defined. The calculated area is stored in the lambda object and is the same for every call. If a lambda is mutable and modifies a variable that was defined in the capture, the original value will be overridden. 

**Best practice**  
_Only initialize variables in the capture if their value is short and their type is obvious. Otherwise it's best to define the variable outside of the lambda and capture it._  

## Dangling captured variables  

Variables are captured at the point where the lambda is defined. If a variable captured by reference dies before the lambda, the lambda will be left holding a dangling reference.

` #include <iostream> `  
` #include <string> `  

` // returns a lambda `  
` auto makeWalrus(const std::string& name) `  
` { `  
&emsp;&emsp;&emsp;` // Capture name by reference and return the lambda. `   
&emsp;&emsp;&emsp;` return [&](){ `   
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << "I am a walrus, my name is " << name << '\n'; // Undefined behavior `  
&emsp;&emsp;&emsp;` }; `  
` } `  

` int main() `  
` { `   
&emsp;&emsp;&emsp;` // Create a new walrus whose name is Roofus. `   
&emsp;&emsp;&emsp;` // sayName is the lambda returned by makeWalrus. `  
&emsp;&emsp;&emsp;` auto sayName{ makeWalrus("Roofus") }; `  

&emsp;&emsp;&emsp;` // Call the lambda function that makeWalrus returned. `  
&emsp;&emsp;&emsp;`  sayName(); `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

The call to `makeWalrus` creates a temporary `std::string` from the string literal "Roofus". The lambda in `makeWalrus` captures the temporary string by reference. The temporary string dies when `makeWalrus` returns, but the lambda still references it. Then when we call `sayName`, the dangling reference is accessed, causing undefined behavior.

This also happens if `name` is passed to `makeWalrus` by value. The variable `name` still dies at the end of `makeWalrus`, and the lambda is left holding a dangling reference.

**Be extra careful when you capture variables by reference, especially with a default reference capture. The captured variable must outlive the lambda.**  

If we want the captured `name` to be valid when the lambda is used, we need to capture it by value instead (either explicitly or using a default capture by value).

## Unintended copies of mutable lambdas  

Because lambdas are objects, they can be copied. In some cases, this can cause problems. 

` #include <iostream> `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` int i{ 0 }; `  

&emsp;&emsp;&emsp;` // Create a new lambda named count `  
&emsp;&emsp;&emsp;` auto count{ [i]() mutanble { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << ++i << '\n'; `  
&emsp;&emsp;&emsp;` } }; `  

&emsp;&emsp;&emsp;` count(); // invoke count `  

&emsp;&emsp;&emsp;` auto otherCount{ count }; // create a copy of count `  

&emsp;&emsp;&emsp;` // invoke both count and the copy `  
&emsp;&emsp;&emsp;` count(); `  
&emsp;&emsp;&emsp;` otherCount(); `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

Rather than printing 1, 2, 3, the code prints 1, and 2 twice. When we created `otherCount` as a copy of `count`, we created a copy of `count` in its current state. `count`'s `i` was 1, so `otherCount`'s `i` is 1 as well. Since `otherCount` is a copy of `count`, they each have their own `i`. 

Let's look at a slightly less obvious example:

` #include <iostream> `  
` #include <functional> `  

` void invoke(const std::function<void()>& fn) `  
` { `  
&emsp;&emsp;&emsp;` fn(); `  
` } `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` int i{ 0 }; `  

&emsp;&emsp;&emsp;` // Increments and prints its local copy of @i. `  
&emsp;&emsp;&emsp;` auto count{ [i]() mutable { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << ++i << '\n'; `  
&emsp;&emsp;&emsp;` } }; `  

&emsp;&emsp;&emsp;` invoke(count); `  
&emsp;&emsp;&emsp;` invoke(count); `  
&emsp;&emsp;&emsp;` invoke(count); `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

This exhibits the same problem as the prior example in a more obscure form. When `std::function` is created with a lambda, the `std::function` internally makes a copy of the lambda object. Thus, our call to `fn()` is actually being executed on the copy of our lambda, not the actual lambda.

If we need to pass a mutable, and want to avoid the possibility of inadvertent copies being made, there are two options. One option is to use a non-capturing lambda instead -- in the above case, we could remove the capture and track our state using a static local variable instead. But static local variables can be difficult to keep track of and make the code less readable. A better option is to prevent copies of lambda from being made in the first place. 

C++ provides a convenient type (as part of the <functional> header) called `std::reference_wrapper` that allows us to pass a normal type as if it were a reference. For even more convenience, a `std::reference_wrapper` can be created by using the `std::ref()` function. By wrapping our lambda in a `std::reference_wrapper`, whenever anybody tries to make a copy of our lambda, they'll make a copy of the reference instead, which will copy the reference rather than the actual object.

` #include <iostream> `  
` #include <functional> `  

` void invoke(const std::function<void()>& fn) `  
` { `  
&emsp;&emsp;&emsp;` fn(); `  
` } `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` int i{ 0 }; `  

&emsp;&emsp;&emsp;` // Increments and prints its local copy of @i. `  
&emsp;&emsp;&emsp;` auto count{ [i]() mutable { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << ++i << '\n'; `  
&emsp;&emsp;&emsp;` } }; `  

&emsp;&emsp;&emsp;` // std::ref(count) ensures count is treated like a reference `  
&emsp;&emsp;&emsp;` // thus, anything that tries to copy count will actually copy the reference `  
&emsp;&emsp;&emsp;` // ensuring that only one count exists `  
&emsp;&emsp;&emsp;` invoke(std::ref(count)); `  
&emsp;&emsp;&emsp;` invoke(std::ref(count)); `  
&emsp;&emsp;&emsp;` invoke(std::ref(count)); `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

Note that the output doesn't change even if `invoke` takes `fn` by value. `std::function` doesn't create a copy of the lambda if we create it with `std::ref`. 

**Standard library functions may copy function objects (reminder: lambdas are function objects). If you want to provide lambdas with mutable captured variables, pass them by reference using `std::ref`.**

**Best practice**  
_Try to avoid lambdas with states altogether. Stateless lambdas are easier to understand and don't suffer from the above issues, as well as more dangerous issues that arise when you add parallel execution._
