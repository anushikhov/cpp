// Set the article as viewed, check if the article was deleted, clear the article as a favorite.

#include <bitset>
#include <cstdint>
#include <iostream>

int main()
{
	constexpr std::uint_fast8_t option_viewed{ 0x01 };
	constexpr std::uint_fast8_t option_edited{ 0x02 };
	constexpr std::uint_fast8_t option_favorited{ 0x04 };
	constexpr std::uint_fast8_t option_shared{ 0x08 };
	constexpr std::uint_fast8_t option_deleted{ 0x10 };

	std::uint_fast8_t myArticleFlags{ option_favorited };

	myArticleFlags |= option_viewed;

	std::cout << std::bitset<8>{ myArticleFlags } << '\n';

	std::cout << ((myArticleFlags & option_deleted) ? "deleted\n" : "not deleted\n");

	myArticleFlags &= ~option_favorited;

	return 0;
}
