// The program asks the user to enter a 32-bit hex value, and extracts the 8-bit color values for R, G, B, and A.

#include <cstdint>
#include <iostream>

int main()
{
	constexpr std::uint_fast32_t redBits{ 0xFF000000 };
	constexpr std::uint_fast32_t greenBits{ 0x00FF0000 };
	constexpr std::uint_fast32_t blueBits { 0x0000FF00 };
	constexpr std::uint_fast32_t alphaBits { 0x000000FF };

	std::cout << "Enter a 32-bit RGBA color value in hexadecimal: ";
	std::uint_fast32_t pixel{};
	std::cin >> std::hex >> pixel;

	std::uint_fast8_t red{ static_cast<std::uint_fast8_t>((pixel & redBits) >> 24) };
	std::uint_fast8_t green{ static_cast<std::uint_fast8_t>((pixel & greenBits) >> 16) };
	std::uint_fast8_t blue{ static_cast<std::uint_fast8_t>((pixel & blueBits) >> 8) };
	std::uint_fast8_t alpha{ static_cast<std::uint_fast8_t>(pixel & alphaBits) };

	std::cout << "The color contains:\n";
	std::cout << std::hex;
	std::cout << static_cast<int>(red)   << " red\n";
	std::cout << static_cast<int>(blue)  << " blue\n";
	std::cout << static_cast<int>(green) << " green\n";
	std::cout << static_cast<int>(alpha) << " alpha\n";

	return 0;
}
