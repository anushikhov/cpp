// Let's pretend we're writing a card game.

// A deck of cards has 52 unique cards (13 card ranks of 4 suits).
// Create enumerations for the card ranks (2, 3, 4, 5, 6, 7, 8, 9, 10, Jack, Queen, King, Ace)
// and suits (clubs, diamonds, hearts, spades). Those enumerators will not be used to index arrays.

enum class CardRank
{
	rank_2,
	rank_3, 
	rank_4,
	rank_5,
	rank_6,
	rank_7,
	rank_8,
	rank_9,
	rank_10,
	rank_jack,
	rank_queen,
	rank_king,
	rank_ace,

	max_ranks
};

enum class CardSuit
{
	club,
	diamond,
	heart,
	spade,

	max_suits
};


// Each card will be represented by a struct named Card that contains a rank and a suit. Create the struct.

struct Card
{
	CardRank rank{};
	CardSuit suit{};
};


// Create a printCard() function that takes a const Card reference as a parameter
// and prints the card rank and suit as a 2-letter code (e.g. the jack of spades would print as JS).

#include <iostream>

void printCard(const Card& card)
{
	switch(card.rank)
	{
		case CardRank::rank_2:      std::cout << '2';   break;
		case CardRank::rank_3:      std::cout << '3';   break;
		case CardRank::rank_4:      std::cout << '4';   break;
		case CardRank::rank_5:      std::cout << '5';   break;
		case CardRank::rank_6:      std::cout << '6';   break;
		case CardRank::rank_7:      std::cout << '7';   break;
		case CardRank::rank_8:      std::cout << '8';   break;
		case CardRank::rank_9:      std::cout << '9';   break;
		case CardRank::rank_10:     std::cout << 'T';   break;
		case CardRank::rank_jack:   std::cout << 'J';   break;
		case CardRank::rank_queen:  std::cout << 'Q';   break;
		case CardRank::rank_king:   std::cout << 'K';   break;
		case CardRank::rank_ace:    std::cout << 'A';   break;
		default:
		    std::cout << '?';
		    break;
	}

	switch(card.suit)
	{
		case CardSuit::club:        std::cout << 'C';   break;
		case CardSuit::diamond:     std::cout << 'D';   break;
		case CardSuit::heart:       std::cout << 'H';   break;
		case CardSuit::spade:       std::cout << 'S';   break;
		default:
		    std::cout << '?';
		    break;
	}
}

// A deck of cards has 52 cards. Create an array (using std::array) to represent the deck of cards,
// and initialize it with one of each card. Do this in a function named createDeck and call createDeck from main.
// createDeck should return the deck to main.
// Use static_cast if you need to convert an integer into an enumerated type.

#include <array>

using deck_type = std::array<Card, 52>;
using index_type = deck_type::size_type;

deck_type createDeck()
{
	deck_type deck{};

	index_type index{ 0 };

	for(int suit{ 0 }; suit < static_cast<int>(CardSuit::max_suits); ++suit)
	{
		for(int rank{ 0 }; rank < static_cast<int>(CardRank::max_ranks); ++rank)
		{
			deck[index].suit = static_cast<CardSuit>(suit);
			deck[index].rank = static_cast<CardRank>(rank);
			++index;
		}
	}

	return deck;
}


// Write a function named printDeck() that takes the deck as a const reference parameter
// and prints the cards in the deck. Use a range-based for-loop. 

void printDeck(const deck_type& deck)
{
	for(const auto& card : deck)
	{
		printCard(card);
		std::cout << ' ';
	}

	std::cout << '\n';
}


// Write a function named shuffleDeck to shuffle the deck of cards using std::shuffle. 
// Update your main function to shuffle the deck and print out the shuffled deck.

#include <algorithm>
#include <ctime>
#include <random>

void shuffleDeck(deck_type& deck)
{
	static std::mt19937 mt{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };

	std::shuffle(deck.begin(), deck.end(), mt);
}

// Write a function named getCardValue() that returns the value of a Card
// (e.g. a 2 is worth 2, a ten, jack, queen, or king is worth 10. Assume an Ace is worth 11).

#include <cassert>

int getCardValue(const Card& card)
{
	switch(card.rank)
	{
		case CardRank::rank_2:      return 2;
		case CardRank::rank_3:      return 3;
		case CardRank::rank_4:      return 4;
		case CardRank::rank_5:      return 5;
		case CardRank::rank_6:      return 6;
		case CardRank::rank_7:      return 7;
		case CardRank::rank_8:      return 8;
		case CardRank::rank_9:      return 9;
		case CardRank::rank_10:  
		case CardRank::rank_jack:
		case CardRank::rank_queen: 
		case CardRank::rank_king:   return 10;
		case CardRank::rank_ace:    return 11;
		default:
	          assert(false && "should never happen");
		  return 0;
	}
}

int main()
{
	auto deck{ createDeck() };
	
	shuffleDeck(deck);

	printDeck(deck);

	return 0;
}
