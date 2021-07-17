// You are running a website, and you are trying to keep track of how much money you make per day from advertising.
// Declare an advertising struct that keeps track of how many ads you've shown to readers,
// what percentage of ads were clicked on by users,
// and how much money you earned on average from each ad that was clicked.
// Read in values for each of these fields from the user.
// Pass the advertising struct to a function that prints each of the values,
// and then calculates how much you made for that day.

#include <iostream>

struct Advertising
{
	int adsShown{};
	double percentageClicked{};
	double averageEarnedPerClick{};
};

double calculateMoneyEarned(Advertising ad)
{
	return ad.adsShown * (ad.percentageClicked / 100) * ad.averageEarnedPerClick;
}

Advertising getValues()
{
	Advertising ad{};
	
	std::cout << "Enter the number of ads shown to readers: ";
	std::cin >> ad.adsShown;

	std::cout << "Enter the percentage of ads that were clicked on by the users: ";
	std::cin >> ad.percentageClicked;

	std::cout << "Enter the average amount of money earned from each ad that was clicked: ";
	std::cin >> ad.averageEarnedPerClick;

	return ad;
}

void printMoneyEarned(Advertising ad)
{
	std::cout << "\nNumber of ads shown: " << ad.adsShown << '\n'
		  << "Click through rate: "  << ad.percentageClicked << '\n'  
		  << "Average earnings per click: $" << ad.averageEarnedPerClick << '\n' 
		  << "Total earnings: $" << calculateMoneyEarned(ad) << '\n';

}

int main()
{
	Advertising ad{ getValues() };

	printMoneyEarned(ad);

	return 0;
}
