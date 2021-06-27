# Uninitialized variables and undefined behavior

C/C++ does not initialize most variables to a given value (such as zero) automatically. Thus, when a variable is assigned a memory location by the compiler, the default value of that variable is whatever (garbage) value happens to already be in that memory location. 

A variable that has not been given a **known value** (usually through initialization or assignment) is called an **unitialized variable**.

The terms "initialized" and "uninitialized" are not strictly opposites. Uninitialized means the object has not been given a known value (through any means, including assignment). Therefore, an object that is not initialized but is then assigned a value is no longer _uninitialized_ (because it has been given a known value).

* Initialization = The object is given a known value at the point of definition.
* Assignment = The object is given a known value beyond the point of definition.
* Uninitialized = The object has not been given a known value yet.

The lack of initialization is a performance optimization inherited from C, back when computers were slow.

For now, you should always initialize your variable because the cost of doing so is miniscule compared to the benefit. Once you are more comfortable with the language, there may be certain cases where you omit the initialization for optimization purposes. But this should always be done selectively and intentionally.

Using the values of uninitialized variables can lead to unexpected results.

Some compilers will initialize the contents of memory to some preset value when you're using a debug build configuration. This will not happen when using a release build configuration.

Most compilers will attempt to detect if a variable is being used without being given a value. If they are able to detect this, they will generally issue a compile-time error.

### Undefined behavior

**Undefined behavior** (often abbreviated **UB**) is the result of executing code whose behavior is not well-defined by the C++ language.

Code implementing undefined behavior may exhibit any of the following symptoms:
* Produces different results every time it is run
* Consistently produces the same incorrect resuls
* Behaves inconsistently (sometimes produces the correct result, sometimes not)
* Seems like its working but produces incorrect results later in the program
* The program crashes, either immediately or later
* Works on some compilers but not on others
* Works until you change some other seemingly unrelated code

Or, **your code may actually produce the correct behavior anyway**. 

The nature of undefined behavior is that you never quite know what you're going to get.

**Take care to avoid all situations that result in undefined behavior, such as using uninitialized variables.**

 Sometimes compiler authors take liberties with the language requirements when those requirements may be more restrictive than needed. Your programs can exhibit undefined behavior but still produce the needed result. Your compiler may simply be not following the standard. You can avoid this by turning off compiler extensions.

Undefined behavior is the result of executing code whose behavior is not well defined by the language. The result can be almost anything, including something that behaves correctly.
