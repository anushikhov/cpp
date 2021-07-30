// Pretend you're writing a game where the player can hold 3 types of items: health potions, torches, and arrows. 
// Create an enum to identify the different types of items,
// and an std::array to store the number of each item the player is carrying.
// (The enumerators are used as indexes of the array.)
// The player should start with 2 health potions, 5 torches, and 10 arrows.
// Write a function called countTotalItems() that returns how many items the player has in total.
// Have your main() function print the output of countTotalItems() as well as the number of torches.

#include <array>
#include <numeric>
#include <iostream>

enum ItemTypes
{
	item_health_potion,
	item_torch,
	item_arrow,
	max_items
};

using inventory_t = std::array<int, ItemTypes::max_items>;

int countTotalItems(const inventory_t& items)
{
	return std::reduce(items.begin(), items.end());
}

int main()
{
	inventory_t items{ 2, 5, 10 };

	std::cout << "The player has " << countTotalItems(items) << " item(s) in total.\n\n";

	std::cout << items[ItemTypes::item_health_potion] << " health potion(s)\n";
	std::cout << items[ItemTypes::item_torch] << " torch(es)\n";
	std::cout << items[ItemTypes::item_arrow] << " arrow(s)\n";

	return 0;
}
