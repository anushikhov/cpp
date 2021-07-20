# An introduction to std::string_view

C-style strings are fast, but they're not as easy to use and safe as `std::string`. But `std::string` has some of its own downsides, particularly when it comes to `const` strings.

Because `std::string` is designed to be modifiable, each `std::string` must contain its own copy of the string, so that a given `std::string` can be modified without affecting any other `std::string` object.

This holds true for const `std::string`, even though they can't be modified.

C++17 introduces another way of using strings, `std::string_view`, which lives in the `<string_view>` header.

Unlike `std::string`, which keeps its own copy of the string, `std::string_view` provides a view of a string that is defined elsewhere.

` #include <iostream> `  
` #include <string_view> `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` std::string_view text{ "hello" }; // view the text "hello", which is stored in the binary `  
&emsp;&emsp;&emsp;` std::string_view str{ text }; // view of the same "hello" `  
&emsp;&emsp;&emsp;` std::string_view more{ str}; // view of the same "hello" `  

&emsp;&emsp;&emsp;` std::cout << text << ' ' << str << ' ' << more << '\n'; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

The string "hello" is stored in the binary and is not allocated at run-time, `text` is only a view onto the string "hello", so no copy has to be created.

`std::string_view` is not only fast, but has many of the functions that we know from `std::string`.

` #include <iostream> `  
` #include <string_view> `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` std::string_view str{ "Trains are fast!" }; `  

&emsp;&emsp;&emsp;` std::cout << str.length() << '\n'; // 16 `  
&emsp;&emsp;&emsp;` std::cout << str.substr(0, str.find(' ')) << '\n'; // Trains `  
&emsp;&emsp;&emsp;` std::cout << (str == "Trains are fast!") << '\n'; // 1 `  

&emsp;&emsp;&emsp;` // Since C++20 `  
&emsp;&emsp;&emsp;` std::cout << str.starts_with("Boats") << '\n'; // 0 `  
&emsp;&emsp;&emsp;` std::cout << str.ends_with("fast!") << '\n'; // 1 `  

&emsp;&emsp;&emsp;` std::cout << str << '\n'; // Trains are fast! `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

Because `std::string_view` doesn't create a copy of the string, if we change the viewed string, the changes are reflected in the `std::string_view`.

` #include <iostream> `  
` #include <string_view> `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` char arr[]{ "Gold" }; `  
&emsp;&emsp;&emsp;` std::string_view str{ arr }; `  

&emsp;&emsp;&emsp;` std::cout << str << '\n'; // Gold `  

&emsp;&emsp;&emsp;` // Change 'd' to 'f' in arr `  
&emsp;&emsp;&emsp;` arr[3] = 'f'; `  

&emsp;&emsp;&emsp;` std::cout << str << '\n'; // Golf `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

When you use a `std::string_view`, it's best to avoid modifications to the underlying string for the remainder of the `std::string_view`'s life to prevent confusion and errors.

**Best practice**<br/>
_Use std::string_view instead of C-style strings._<br/>
_Prefer std::string_view over std::string for read-only strings, unless you already have a std::string._


## View modification functions

`std::string_view` contains functions that let us manipulate the view of the string. This allows us to change the view without modifying the viewed string.

The functions for this are `remove_prefix`, which removes characters from the left side of the view, and `remove_suffix`, which removes characters from the right side of the view.

` #include <iostream> `  
` #include <string_view> `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` std::string_view str{ "Peach" }; `  

&emsp;&emsp;&emsp;` std::cout << str << '\n'; `  

&emsp;&emsp;&emsp;` // Ignore the first character `  
&emsp;&emsp;&emsp;` str.remove_prefix(1); `  

&emsp;&emsp;&emsp;` std::cout << str << '\n'; `  

&emsp;&emsp;&emsp;` // Ignore the last 2 characters `  
&emsp;&emsp;&emsp;` str.remove_suffix(2); `  

&emsp;&emsp;&emsp;` std::cout << str << '\n'; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

### std::string_view words with non-null-terminated strings

Unlike C-style strings and `std::string`, `std::string_view` doesn't use null terminators to mark the end of the string. Rather, it knows where the string ends because it keeps track of its length.

` #include <iostream> `  
` #include <iterator> `  
` #include <string_view> `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` // No null-terminator. `  
&emsp;&emsp;&emsp;` char vowels[]{ 'a', 'e', 'i', 'o', 'u' }; `  

&emsp;&emsp;&emsp;` // vowels isn't null-terminated. We need to pass the length manually. `  
&emsp;&emsp;&emsp;` // Because vowels is an array, we can use std::size to get its length. `  
&emsp;&emsp;&emsp;` std::string_view str{ vowels, std::size(vowels) }; `  

&emsp;&emsp;&emsp;` std::cout << str << '\n'; // This is safe. std::cout knows how to print std;:string_views. `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  


## Ownership issues

Being only a view, a `std::string_view`'s lifetime is independent of that of the string it is viewing. If the viewed string goes out of scope, `std::string_view` has nothing to observe and accessing it causes undefined behavior.

The same can happen when we create a `std::string_view` from a `std::string` and modify the `std::string`. Modifying a `std::string` can cause its internal string to die and be replaced with a new one in a different place. The `std::string_view` will still look at where the old string was, but it's not there anymore.

**Make sure that the underlying string viewed with a `std::string_view` does not go out of scope and isn't modified while using the `std::string_view`.**


## Convertina a std::string_view to a std::string

An `std::string_view` will not implicitly convert to `std::string`, but can be explicitly converted:

` #include <iostream> `  
` #include <string> `  
` #include <string_view> `  

` void print(std::string s) `  
` { `  
&emsp;&emsp;&emsp;` std::cout << s << '\n'; `  
` } `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` std::string_view sv{ "balloon" }; `  

&emsp;&emsp;&emsp;` sv.remove_suffix(3); `  

&emsp;&emsp;&emsp;` // print(sv); // compile error: won't implicitly convert `  

&emsp;&emsp;&emsp;` std::string str{ sv }; // okay `  

&emsp;&emsp;&emsp;` print(str); // okay `  

&emsp;&emsp;&emsp;` print(static_cast<std::string>(sv)); // okay `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  


## Converting a std::string_view to a C-style string

Some old functions (such as the old `strlen` function) still expect C-style strings. To convert a `std::string_view` to a C-style string, we can do so by first converting to a `std::string`:

` #include <cstring> `  
` #include <iostream> `  
` #include <string> `  
` #include <string_view> `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` std::string_view sv{ "balloon" }; `  

&emsp;&emsp;&emsp;` sv.remove_suffix(3); `  

&emsp;&emsp;&emsp;` // Create a std::string from the std::string_view `  
&emsp;&emsp;&emsp;` std::string stv{ sv }; `  

&emsp;&emsp;&emsp;` // Get the null-terminated C-style string. `  
&emsp;&emsp;&emsp;` const char* szNullTerminated{ str.c_str() }; `  

&emsp;&emsp;&emsp;` // Pass the null-terminated string to the function that we want to use. `  
&emsp;&emsp;&emsp;` std::cout << str << " has " << std::strlen(szNullTerminated) << " letter(s)\n"; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

However, creating a `std::string` every time we want to pass a `std::string_view` as a C-style string is expensive, so this should be avoided if possible.


## The data() function

The string being viewed by a `std::string_view` can be accessed by using the `data()` function, which returns a C-style string. This provides fast access to the string being viewed (as a C-string). But it should also only be used if the `std::string_view`'s view hasn't been modified (e.g. by `remove_prefix` or `remove_suffix`) and the string being viewed is null-terminated.

In the following example, `std::strlen` doesn't know what a `std::string_view` is, so we need to pass it `str.data()`:

` #include <cstring> `  
` #include <iostream> `  
` #include <string_view> `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` std::string_view str{ "balloon" }; `  

&emsp;&emsp;&emsp;` std::cout << str << '\n'; `  

&emsp;&emsp;&emsp;` std::cout << std::strlen(str.data()) << '\n'; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

When a `std::string_view` has been modified, `data()` doesn't always do what we'd like it to.

**Only use `std::string_view::data()` if the `std::string_view`'s view hasn't been modified and the string being viewed is null-terminated. Using `std::string_view::data()` of a non-null-terminated string can cause undefined behavior.**


## Incomplete implementation

Being a relatively recent feature, `std::string_view` isn't implemented as well as it could be.

` std::string s{ "hello" }; `  
` std::string_view v{ "world" }; `  

` // Doesn't work, however there's no reason for this. They will probably be supported in a future C++ version. `  
` std::cout << (s + v) << '\n'; `  
` std::cout << (v + s) << '\n'; `  

` // Potentially unsafe, or not what we want, because we're treating the std::string_view as a C-style string. `  
` std::cout << (s + v.data()) << '\n'; `  
` std::cout << (v.data() + s) << '\n'; `  

` // Ok, but ugly and wasteful because we have to construct a new std::string. `  
` std::cout << (s + std::string{ v }) << '\n'; `  
` std::cout << (std::string{ v } + s) << '\n'; `  
` std::cout << (s + static_cast<std::string>(v)) << '\n'; `  
` std::cout << (static_cast<std::string>(v) + s) << '\n'; `
