# Chars

The **char** data type was designed to hold a character. A **character** can be a single letter, number, symbol, or whitespace.

The char data type is an integral type, meaning the underlying value is stored as an integer. Similar to how a Boolean value 0 is interpreted as false and non-zero is interpreted as true, the integer stored by a char variable is interpreted as an ASCII character.

**ASCII** stands for American Standard Code for Information Interchange, and it defines a particular way to represent English characters (plus a few other symbols) as numbers between 0 and 127 (called an ASCII code or code point). For example, ASCII code 97 is interpreted as the character 'a'.

Character literals are always placed between single quotes.

Here's a full table of ASCII characters:
![ASCII characters](https://raw.githubusercontent.com/anushikhov/cpp/master/learncpp_com/4_Fundamental_Data_Types/img/ascii.png)

Codes 0-31 are called the unprintable chars, and they're mostly used to do formatting and control printers. Most of these are obsolete now.

Codes 32-127 are called the printable characters, and they represent the letters, number characters, and punctuation that most computers use to display basic English text.

char variables can be initialized either with character literals or integers (but this should be avoided if possible).

**Be careful not to mix up character numbers with integer numbers. Character numbers are intended to be used when we want to represent numbers as text, rather than as numbers to apply mathematical operations to.**

When using std::cout to print a char, std::cout outputs the char variable as an ASCII character.

The fixed-width integer int8_t is usually treated the same as a signed char in C++, so it will generally print a char instead of an integer.

### Printing chars as integers via type casting

If we want to output a char as a number instead of a character, we have to tell std::cout to print the char as if it were an integer. 

A **type case** creates a value of one type from a value of another type. To convert between fundamental data types, we use a type cast called a **static cast**.

` static_cast<new_type>(expression) `  

static_cast takes the value from an expression as input, and converts it into whatever fundamental type new_type represents.

**Whenever you see C++ syntax (excluding the preprocessor) that makes use of angled brackets, the thing between the angled brackets will most likely be a type. This is typically how C++ deals with concepts that need a parameterizable type.**

The parameter to static_cast evaluates as an expression. When we pass in a variable, that variable is evaluated to produce its value, which is then converted to the new type. The variable is not affected by casting its value to a new type.

Static casting doesn't do any range checking, so if you cast a large integer into a char, you'll overflow your char.


## char size, range, and default sign

char is defined by C++ to always be 1 byte in size. 

By default, a char may be signed or unsigned (though it's usually signed). If you're using chars to hold ASCII characters, you don't need to specify a sign (since both signed and unsigned chars can hold values between 0 and 127).

If you're using a char to hold small integers (something you should not do unless you're explicitly optimizing for space), you should always specify whether it is signed or unsigned. A signed char can hold a number between -128 and 127. An unsigned char can hold a number between 0 and 255.


**Always put stand-alone chars in single quotes. This helps the compiler optimize more effectively.**


wchar_t should be avoided in almost all cases (except when interfacing with the Windows API). Its size is implementation defined, and is not reliable. It has largely been deprecated.

**The term "deprecated" means "still supported, but no longer recommended for use, because it has been replaced by something better or is no longer considered safe."**

Much like ASCII maps the integers 0-127 to American English characters, other character encoding standards exist to map integers (of varying sizes) to characters in other languages. The most well-known mapping outside of ASCII is the Unicode standard, which maps over 110,000 integers to characters in many different languages. Because Unicode contains so many code points, a single Unicode code point needs 32-bits to represent a character (called UTF-32). However, Unicode characters can also be encoded using multiple 16-bit or 8-bit characters (called UTF-16 and UTF-8 respectively).

char16_t and char32_t were added to C++11 to provide explicit support for 16-bit and 32-bit Unicode characters. char8_t has been added in C++20.

You won't need to use char8_t, char16_t, or char32_t unless you're planning on making your programs Unicode compatible.

