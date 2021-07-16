# Bit manipulation with bitwise operators and bit masks

## Bit masks

A **bit mask** is a predefined set of bits that is used to select which specific bits will be modified by subsequent operations.

A bit mask blocks the bitwise operators from touching bits we don't want modified, and allows access to the ones we do want modified.

### Defining bit masks in C++14

The simplest set of bit masks is to define one bit mask for each bit position. We use 0s to mask out the bits we don't care about, and 1s to denote the bits we want modified.

Although bit masks can be literals, they're often defined as symbolic constants so they can be given a meaningful name and easily reused.

Because C++14 supports binary literals, defining these bit masks is easy:

` #include <cstdint> `  

` constexpr std::uint_fast8_t mask0{ 0b0000'0001 }; // represents bit 0 `  
` constexpr std::uint_fast8_t mask1{ 0b0000'0010 }; // represents bit 1 `
...
` constexpr std::uint_fast8_t mask7{ 0b1000'0000 }; // represents bit 7 `  

### Defining bit masks in C++11 or earlier

Because C++11 doesn't support binary literals, we have to use other methods to set the symbolic constants. There are two good methods for doing this. More common is to use hexadecimals.

` constexpr std::uint_fast8_t mask0{ 0x1 }; // hex for 0000 0001 `  
` constexpr std::uint_fast8_t mask1{ 0x2 }; // hex for 0000 0010 `  
` constexpr std::uint_fast8_t mask3{ 0x4 }; // hex for 0000 0100 `  
...
` constexpr std::uint_fast8_t mask7{ 0x80 }; // hex for 1000 0000 `  

This can be a little hard to read. One way to make it easier is to use the left-shift operator to shift a bit into the proper location:

` constexpr std::uint_fast8_t mask0{ 1 << 0 }; // 0000 0001 `  
` constexpr std::uint_fast8_t mask1{ 1 << 1 }; // 0000 0010 `  
...
` constexpr std::uint_fast8_t mask7{ 1 << 7 }; // 1000 0000 `  

### Testing a bit

We can use bit the set of bit masks in conjunction with a bit flag variable to manipulate bit flags.

To determine if a git is on or off, we use bitwise AND in conjunction with the bit mask for the appropriate bit:

` #include <cstdint> `  
` #include <iostream> `<br/><br/>
` int main() `  
` { `  
&emsp;&emsp;&emsp;` constexpr std::uint_fast8_t mask0{ 0b0000'0001 }; `  
&emsp;&emsp;&emsp;` constexpr std::uint_fast8_t mask1{ 0b0000'0010 }; `  
&emsp;&emsp;&emsp;` constexpr std::uint_fast8_t mask2{ 0b0000'0100 }; `  
&emsp;&emsp;&emsp;` constexpr std::uint_fast8_t mask3{ 0b0000'1000 }; `  
&emsp;&emsp;&emsp;` constexpr std::uint_fast8_t mask4{ 0b0001'0000 }; `  
&emsp;&emsp;&emsp;` constexpr std::uint_fast8_t mask5{ 0b0010'0000 }; `  
&emsp;&emsp;&emsp;` constexpr std::uint_fast8_t mask6{ 0b0100'0000 }; `  
&emsp;&emsp;&emsp;` constexpr std::uint_fast8_t mask7( 0b1000'0000 }; `<br/><br/>
&emsp;&emsp;&emsp;` std::uint_fast8_t flags{ 0b0000'0101 }; // 8 bits in size means room for 8 flags `<br/><br/>
&emsp;&emsp;&emsp;` std::cout << "bit 0 is " << ((flags & mask0) ? "on\n" : "off\n"); `  
&emsp;&emsp;&emsp;` std::cout << "bit 1 is " << ((flags & mask1) ? "on\n" : "off\n"); `<br/><br/>
&emsp;&emsp;&emsp;` return 0; `  
` } `  

### Setting a bit

To set (turn on) a bit, we use bitwise OR equals (operator |=) in conjunction with the bit mask for the appropriate bit:  

` #include <cstdint> `  
` #include <iostream> `<br/><br/>
` int main() `  
` { `  
&emsp;&emsp;&emsp;` constexpr std::uint_fast8_t mask0{ 0b0000'0001 }; `  
&emsp;&emsp;&emsp;` constexpr std::uint_fast8_t mask1{ 0b0000'0010 }; `  
&emsp;&emsp;&emsp;` constexpr std::uint_fast8_t mask2{ 0b0000'0100 }; `  
&emsp;&emsp;&emsp;` constexpr std::uint_fast8_t mask3{ 0b0000'1000 }; `  
&emsp;&emsp;&emsp;` constexpr std::uint_fast8_t mask4{ 0b0001'0000 }; `  
&emsp;&emsp;&emsp;` constexpr std::uint_fast8_t mask5{ 0b0010'0000 }; `  
&emsp;&emsp;&emsp;` constexpr std::uint_fast8_t mask6{ 0b0100'0000 }; `  
&emsp;&emsp;&emsp;` constexpr std::uint_fast8_t mask7{ 0b1000'0000 }; `<br/><br/>
&emsp;&emsp;&emsp;` std::uint_fast8_t flags{ 0b0000'0101 }; `<br/><br/>
&emsp;&emsp;&emsp;` std::cout << "bit 1 is " << ((flags & mask) ? "on\n" : "off\n"); `<br/><br/>
&emsp;&emsp;&emsp;` flags |= mask1; `<br/><br/>
&emsp;&emsp;&emsp;` std::cout << "bit 1 is " << ((flags & mask1) ? "on\n" : "off\n"); `<br/><br/>
&emsp;&emsp;&emsp;` return 0; `  
` } `  

We can also turn on multiple bits at the same time using Bitwise OR:

` flags |= (mask4 | mask5);

### Resetting a bit

To clear a bit (turn off), we use Bitwise AND and Bitwise NOT together:

` #include <cstdint> `  
` #include <iostream> `<br/><br/>
` int main() `  
` { `  
&emsp;&emsp;&emsp;` constexpr std::uint_fast8_t mask0{ 0b0000'0001 }; `  
&emsp;&emsp;&emsp;` constexpr std::uint_fast8_t mask1{ 0b0000'0010 }; `  
&emsp;&emsp;&emsp;` constexpr std::uint_fast8_t mask2{ 0b0000'0100 }; `  
&emsp;&emsp;&emsp;` constexpr std::uint_fast8_t mask3{ 0b0000'1000 }; `  
&emsp;&emsp;&emsp;` constexpr std::uint_fast8_t mask4{ 0b0001'0000 }; `  
&emsp;&emsp;&emsp;` constexpr std::uint_fast8_t mask5{ 0b0010'0000 }; `  
&emsp;&emsp;&emsp;` constexpr std::uint_fast8_t mask6{ 0b0100'0000 }; `  
&emsp;&emsp;&emsp;` constexpr std::uint_fast8_t mask7{ 0b1000'0000 }; `<br/><br/>
&emsp;&emsp;&emsp;` std::uint_fast8_t flags{ 0b0000'0101 }; `<br/><br/>
&emsp;&emsp;&emsp;` std::cout << "bit 2 is " << ((flags & mask2) ? "on\n" : "off\n"); `<br/><br/>
&emsp;&emsp;&emsp;` flags &= ~mask2; `<br/><br/>
&emsp;&emsp;&emsp;` std::cout << "bit 2 is " << ((flags & mask2) ? "on\n" : "off\n"); `<br/><br/>
&emsp;&emsp;&emsp;` return 0; `  
` } `  

We can turn off multiple bits at the same time:

` flags &= ~(mask4 | mask5); `  

### Flipping a bit

To toggle a bit state, we use Bitwise XOR:

` #include <cstdint> `
` #include <iostream> `<br/><br/>
` int main() `  
` { `  
&emsp;&emsp;&emsp;` constexpr std::uint_fast8_t mask0{ 0b0000'0001 }; `  
&emsp;&emsp;&emsp;` constexpr std::uint_fast8_t mask1{ 0b0000'0010 }; `  
&emsp;&emsp;&emsp;` constexpr std::uint_fast8_t mask2{ 0b0000'0100 }; `  
&emsp;&emsp;&emsp;` constexpr std::uint_fast8_t mask3{ 0b0000'1000 }; `  
&emsp;&emsp;&emsp;` constexpr std::uint_fast8_t mask4{ 0b0001'0000 }; `  
&emsp;&emsp;&emsp;` constexpr std::uint_fast8_t mask5{ 0b0010'0000 }; `
&emsp;&emsp;&emsp;` constexpr std::uint_fast8_t mask6{ 0b0100'0000 }; `  
&emsp;&emsp;&emsp;` constexpr std::uint_fast8_t mask7{ 0b1000'0000 }; `<br/><br/>
&emsp;&emsp;&emsp;` std::uint_fast8_t flags{ 0b0000'0101 }; `<br/><br/>
&emsp;&emsp;&emsp;` std::cout << "bit 2 is " << ((flags & mask2) ? "on\n" : "off\n"; `<br/><br/>
&emsp;&emsp;&emsp;` flags ^= mask2; `<br/><br/>
&emsp;&emsp;&emsp;` std::cout << "bit 2 is " << ((flags & mask2) ? "on\n" : "off\n"; ` <br/><br/>
&emsp;&emsp;&emsp;` return 0; `  
` } `  

We can flip multiple bits simultaneously:

` flags ^= (mask4 | mask5); `  


## Bit masks and std::bitset

std::bitset supports the full set of bitwise operators. So even though it's easier to use the functions (test, set, reset, and flip) to modify individual bits, you can use bitwise operators and bit masks if you want.

The functions only allow you to modify individual bits. The bitwise operators allow you to modify multiple bits at once.

` #include <cstdint> `  
` #include <bitset> `  
` #include <iostream> `<br/><br/>
` int main() `  
` { `  
&emsp;&emsp;&emsp;` constexpr std::bitset<8> mask0{ 0b0000'0001 }; `  
&emsp;&emsp;&emsp;` constexpr std::bitset<8> mask1{ 0b0000'0010 }; `  
&emsp;&emsp;&emsp;` constexpr std::bitset<8> mask2{ 0b0000'0100 }; `  
&emsp;&emsp;&emsp;` constexpr std::bitset<8> mask3{ 0b0000'1000 }; `  
&emsp;&emsp;&emsp;` constexpr std::bitset<8> mask4{ 0b0001'0000 }; `  
&emsp;&emsp;&emsp;` constexpr std::bitset<8> mask5{ 0b0010'0000 }; `  
&emsp;&emsp;&emsp;` constexpr std::bitset<8> mask6{ 0b0100'0000 }; `  
&emsp;&emsp;&emsp;` constexpr std::bitset<8> mask7{ 0b1000'0000 }; `<br/><br/>
&emsp;&emsp;&emsp;` std::bitset<8> flags{ 0b0000'0101 }; `<br/><br/>
&emsp;&emsp;&emsp;` std::cout << "bit 1 is " << (flags.test(1) ? "on\n" : "off\n"); `  
&emsp;&emsp;&emsp;` std::cout << "bit 2 is " << (flags.test(2) ? "on\n" : "off\n"); `<br/><br/>
&emsp;&emsp;&emsp;` flags ^= (mask1 | mask2); `<br/><br/>
&emsp;&emsp;&emsp;` std::cout << "bit 1 is " << (flags.test(1) ? "on\n" : "off\n"); `  
&emsp;&emsp;&emsp;` std::cout << "bit 2 is " << (flags.test(2) ? "on\n" : "off\n"); `<br/><br/>
&emsp;&emsp;&emsp;` flags |= (mask1 | mask2); `<br/><br/>
&emsp;&emsp;&emsp;` std::cout << "bit 1 is " << (flags.test(1) ? "on\n" : "off\n"); `  
&emsp;&emsp;&emsp;` std::cout << "bit 2 is " << (flags.test(2) ? "on\n" : "off\n"); `<br/><br/>
&emsp;&emsp;&emsp;` flags &= ~(mask1 | mask2); `<br/><br/>
&emsp;&emsp;&emsp;` std::cout << "bit 1 is " << (flags.test(1) ? "on\n" : "off\n"); `  
&emsp;&emsp;&emsp;` std::cout << "bit 2 is " << (flags.test(2) ? "on\n" : "off\n"); `<br/><br/>
&emsp;&emsp;&emsp;` return 0; `  
` } `  

### Making bit masks meaningful

A best practice is to give your bit masks useful names as a way to document the meaning of the bit flags.

` #include <cstdint> `  
` #include <iostream> `<br/><br/>
` int main() `  
` { `  
&emsp;&emsp;&emsp;` constexpr std::uint_fast8_t isHungry{ 1 << 0 }; `  
&emsp;&emsp;&emsp;` constexpr std::uint_fast8_t isSad{ 1 << 1 }; `  
&emsp;&emsp;&emsp;` constexpr std::uint_fast8_t isMad{ 1 << 2 }; `  
&emsp;&emsp;&emsp;` constexpr std::uint_fast8_t isHappy{ 1 << 3 }; `  
&emsp;&emsp;&emsp;` constexpr std::uint_fast8_t isLaughing{ 1 << 4 }; `  
&emsp;&emsp;&emsp;` constexpr std::uint_fast8_t isAsleep{ 1 << 5 }; `  
&emsp;&emsp;&emsp;` constexpr std::uint_fast8_t isDead{ 1 << 6 }; `  
&emsp;&emsp;&emsp;` constexpr std::uint_fast8_t isCrying{ 1 << 7 }; `<br/><br/>
&emsp;&emsp;&emsp;` std::uint_fast8_t me{}; `  
&emsp;&emsp;&emsp;` me |= (isHappy | isLaughing); `  
&emsp;&emsp;&emsp;` me &= ~isLaughing; `<br/><br/>
&emsp;&emsp;&emsp;` std::cout << "I am happy? " << static_cast<bool>(me & isHappy) << '\n'; `  
&emsp;&emsp;&emsp;` std::cout << "I am laughing? " << static_cast<bool>(me & isLaughing) << '\n'; `<br/><br/>
&emsp;&emsp;&emsp;` return 0; `  
` } `

The same example implemented with std::bitset:
 
` #include <bitset> `  
` #include <iostream> `<br/><br/>
` int main() `  
` { `  
&emsp;&emsp;&emsp;` constexpr std::bitset<8> isHungry{ 0b0000'0001 }; `  
&emsp;&emsp;&emsp;` constexpr std::bitset<8> isSad{ 0b0000'0010 }; `  
&emsp;&emsp;&emsp;` constexpr std::bitset<8> isMad{ 0b0000'0100 }; `  
&emsp;&emsp;&emsp;` constexpr std::bitset<8> isHappy{ 0b0000'1000 }; `  
&emsp;&emsp;&emsp;` constexpr std::bitset<8> isLaughing{ 0b0001'0000 }; `  
&emsp;&emsp;&emsp;` constexpr std::bitset<8> isAsleep{ 0b0010'0000 }; `  
&emsp;&emsp;&emsp;` constexpr std::bitset<8> isDead{ 0b0100'0000 }; `  
&emsp;&emsp;&emsp;` constexpr std::bitset<8> isCrying{ 0b1000'0000 }; `<br/><br/>
&emsp;&emsp;&emsp;` std::bitset<8> me{}; `  
&emsp;&emsp;&emsp;` me |= (isHappy | isLaughing); `  
&emsp;&emsp;&emsp;` me &= ~isLaughing; `<br/><br/>
&emsp;&emsp;&emsp;` std::cout << "I am happy? " << (me & isHappy).any() << '\n'; `  
&emsp;&emsp;&emsp;` std::cout << "I am laughing? " << (me & isLaughing).any() << '\n'; `<br/><br/>
&emsp;&emsp;&emsp;` return 0; `  
` } `

If you want to use bit masks rather than positional indexes, you'll have to use Bitwise AND to query bits.

The any() function returns true if any bits are set, and false otherwise.

### When are bit flags most useful

The above examples don't actually save any memory. Bit flags make the most sense when you have identical flag variables.

For most programs, the amount of memory using bit flags saved is not worth the added complexity. But in programs where there are tens of thousands or even millions of similar objects, using bit flags can reduce memory use substantially. It's a useful optimization to have in your toolkit if you need it.

There's another case where bit flags and bit masks can make sense. Imagine you had a function that could take any combination of 32 different options. One way to write that function would be to use 32 individual Boolean parameters. Instead, you could define the function using bit flags like this:

` void someFunction(std::bitset<32> options); `  

Then you could use bit flags to pass in only the options you wanted: 

` someFunction(option10 | option32); `  

This is much more readable and is likely to be more performant as well, since it only involves 2 operations (one Bitwise OR and one parameter copy).

This is one of the reasons OpenGL, a well regarded 3d graphic library, opted to use bit flag parameters instead of many consecutive Boolean parameters.

Here's a sample function call from OpenGL:

` glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the color and the depth buffer `  

GL_COLOR_BUFFER_BIT and GL_DEPTH_BUFFER_BIT are bit masks defined in gl2.h as follows:

` #define GL_DEPTH_BUFFER_BIT     0x00000100 `  
` #define GL_STENCIL_BUFFER_BIT   0x00000400 `  
` #define GL_COLOR_BUFFER_BIT     0x00004000 `

### Bit masks involving multiple bits

Although bit masks often are used to select a single bit, they can also be used to select multiple bits.

Color display devices are composed of millions of pixels, each of which can display a dot of color. THe dot of color is composed from three beams of light: red, green, blue (RGB). By varying the intensity of the colors, any color on the color spectrum can be made. Typically, the amount of R, G, and B for a given pixel is represented by an 8-bit unsigned integer. In addition, a 4th value called A "alpha" is used and it controls how transparent the color is. If A = 0, the color is fully transparent. If A = 255, the color is opaque.

R, G, B, and A are normally stored as a single 32-bit integer, with 8 bits used for each component: 

![32-bit RGBA value](https://raw.githubusercontent.com/anushikhov/cpp/master/learncpp_com/6_Bit_Manipulation/img/rgba.png)  

...  

* To query bit states, use bitwise AND.
* To set bits (turn on), use bitwise OR.
* To clear bits (turn off), use bitwise AND with bitwise NOT.
* To flip bit states, use bitwise XOR
