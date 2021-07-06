// A bitwise rotation is like a bitwise shift, except that any bits shifted off one end are added back to the other end.
// For example, 0b1001 << 1 would be 0b0010, but a left rotate by 1 would result in 0b0011 instead.
// Implement a function that does a left rotate on a std::bitset<4>.
// Use test() and set().


#include <bitset>
#include <iostream>

std::bitset<4> rotl(std::bitset<4> bits)
{
	if(bits.test(3))
		return (bits << 1).set(0);
	return bits << 1;
}

int main()
{
	std::bitset<4> bits1{ 0b0001 };
	std::cout << rotl(bits1) << '\n';

	std::bitset<4> bits2{ 0b1001 };
	std::cout << rotl(bits2) << '\n';

	return 0;
}
