# Configuring your compiler: Build configuration

A build configuration (also called a build target) is a collection of project settings that determine how your IDE will build your project. 

The build configuration typically includes things like what the executable will be named, what directories the IDE will look in for other code and library files, whether to keep or strip out debugging information, how much to have the compiler optimize your program, etc.

The debug configuration is designed to help you debug your program. It turns off all optimizations, and includes debugging information, which makes your programs larger and slower, but much easier to debug. 

The release configuration is designed to be used when releasing your program to the public. It is optimized for size and performance, and doesn't contain the extra debugging information. 

Because the release configuration includes all optimizations, this mode is also useful for testing the performance of your code.

You'll rarely have a reason to, but you can also create your own custom build configurations.

**Best practice**
*Use the debug build configuration when developing your programs. When you're ready to release your executable to others, or want to test performance, use the release build configuration.*


