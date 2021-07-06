# Bit flags and bit manipulation via std::bitset

On modern computer architectures, the smallest addressable unit of memory is a byte. Since all objects need to have unique memory addresses, this means objects must be at least one byte in size. For Boolean values, this is a bit wasteful. If a variable must be at least a byte, and a byte is 8 bits, that means a Boolean is using 1 bit and leaving the other 7 unused. 

In some storage-intensive cases, it can be useful to "pack" 8 individual Boolean values into a single byte for storage efficiency purposes.

Doing these things requires that we can manipulate objects at the bit level. Modifying individual bits within an object is called **bit manipulation**.

Bit manipulation is also useful in encryption and compression algorithms.


## Bit flags

Instead of viewing objects as holding a single value, we can instead view them as a collection of individual bits. When individual bits of an object are used as Boolean values, the bits are called **bit flags**.

In computing, a flag is a value that acts as a signal for some function or process.

To define a set of bit flags, we'll typically use an unsigned integer of the appropriate size (8 bits, 16 bits, 32 bits, etc... depending on how many flags we have), or std::bitset.

` #include <bitset> // for std::bitset `<br/><br/>
` std::bitset<8> mybitset {}; // 8 bits in size means room for 8 flags `  

**Best practice**<br/>
_Bit manipulation is one of the few times when you should unambiguously use unsigned integers (or std::bitset)._

### Bit numbering and bit positions

Given a sequence of bits, we typically number the bits from right to left, starting with 0. Each number denotes a bit position.

` 76543210     Bit position `  
` 00000101     Bit sequence `  

### Manipulating bits via std::bitset

std::bitset provides 4 key functions that are useful for doing bit manipulation:

* test() allows us to query whether a bit is a 0 or 1
* set() allows us to turn a bit on (this will do nothing if the bit is already on)
* reset() allows us to turn a bit off (will do nothing if the bit is already off)
* flip() allows us to flip a bit value from 0 to a 1 or vice versa

Each of these functions takes the position of the bit we want to operate on as their only argument.

` #include <bitset> `  
` #include <iostream> `<br/><br/>
` int main() `  
` { `  
&emsp;&emsp;&emsp;` std::bitset<8> bits{ 0b0000'0101 }; `  
&emsp;&emsp;&emsp;` bits.set(3); `  
&emsp;&emsp;&emsp;` bits.flip(4); `  
&emsp;&emsp;&emsp;` bits.reset(4); `<br/><br/>
&emsp;&emsp;&emsp;` std::cout << "All the bits: " << bits << '\n'; `  
&emsp;&emsp;&emsp;` std::cout << "Bit 3 has value: " << bits.test(3) << '\n'; `  
&emsp;&emsp;&emsp;` std::cout << "Bit 4 has value: " << bits.test(4) << '\n'; `<br/><br/>
&emsp;&emsp;&emsp;` return 0; `  
` } `  
