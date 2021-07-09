# Unnamed and inline namespaces

## Unnamed (anonymous) namespaces

An **unnamed namespace** (also called an **anonymous namespace**) is a namespace that is defined without a name, like so:  

` #include <iostream> `  

` namespace `  
` { `  
&emsp;&emsp;&emsp;` void doSomething() `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << "v1\n"; `  
&emsp;&emsp;&emsp;` } `  
` } `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` doSomething(); // we can call doSomthing() without a namespace prefix `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

All content declared in an unnamed namespace is treated as if it is part of the parent namespace. So even though function doSomething is defined in the unnamed namespace, the function itself is accessible from the parent namespace (which in this case is the global namespace), which is why we can call doSomething from main without any qualifiers.

This might make unnamed namespaces seem useles. But the other effect of unnamed namespaces is that all identifiers inside an unnamed namespace are treated as if they had internal linkage, which means that the content of an unnamed namespace can't be seen outside of the file in which the unnamed namespace is defined.

For functions, this is effectively the same as defining all functions in the unnamed namespace as static functions.

Unnamed namespaces are typically used when you have a lot of content that you want to ensure stays local to a given file, as it's easier to cluster such content in an unnamed namespace than individually make all declarations as static.

Unnamed namespaces will also keep user-defined types local to the file, something for which there is no alternative equivalent mechanism to do.

## Inline namespaces

An **inline namespace** is a namespace that is typically used to version content. Much like an unnamed namespace, anything declared inside an inline namespace is considered part of the parent namespace. However, inline namespaces don't give everything internal linkage.

To define an inline namespace, we use the `inline` keyword:

` #include <iostream> `  

` inline namespace v1 `  
` { `  
&emsp;&emsp;&emsp;` void doSomething() `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << "v1\n"; `  
&emsp;&emsp;&emsp;` } `  
` } `  

` namespace v1 `  
` { `  
&emsp;&emsp;&emsp;` void doSomething() `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << "v1\n"; `  
&emsp;&emsp;&emsp;` } `  
` } ` 

` int main() `  
` { `  
&emsp;&emsp;&emsp;` v1::doSomething(); `  
&emsp;&emsp;&emsp;` v2::doSomething(); `  

&emsp;&emsp;&emsp;` doSomething(); `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

This preserves the function of existing programs while allowing newer programs to take advantage of newer/better versions.

Alternatively, you can use the inline keyword to push the newer version.
