#include <iostream>
#include "constants.h"

double calculateHeight(double initialHeight, int seconds)
{
	double distanceFallen { myConstants::gravity * seconds * seconds / 2 };
	double heightNow { initialHeight - distanceFallen };

	return heightNow;
}

bool calculateAndPrintHeight(double initialHeight, int time)
{
	if(calculateHeight(initialHeight, time) <= 0)
	{
		std::cout << "The ball is on the ground.\n";
		return false;
	}
	
	std::cout << "At " << time << " seconds, the ball is at height: " 
		  << calculateHeight(initialHeight, time) << "\n";
	return true;
}

int main()
{
	std::cout << "Enter the initial height of the tower in meters: ";
	double initialHeight;
	std::cin >> initialHeight;
	
	int seconds{ 0 };
	while(calculateAndPrintHeight(initialHeight, seconds++));

	return 0;
}
