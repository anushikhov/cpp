// Write a short program to simulate a ball being dropped off of a tower.
// To start, the user should be asked for the height of the tower in meters. 
// Assume normal gravity (9.8 m/s^2), and that the ball has no initial velocity.
// Have the program output the height of the ball above the ground after 0, 1, 2, 3, 4, and 5 seconds.
// The ball should not go underneath the ground (height 0).
// Use a function to calculate the height of the ball after x seconds.
// The function can calculate how far the ball has fallen after x seconds using the following formula:
// distance fallen = gravity_constant * x_seconds^2 / 2

#include <iostream>

// gets height from user and returns it
double getTowerHeight()
{
	std::cout << "Enter the height of the tower in meters: ";
	double towerHeight{};
	std::cin >> towerHeight;

	return towerHeight;
}

// calculates and returns ball height from the ground after given seconds
double calculateBallHeight(double towerHeight, int seconds)
{
	constexpr double gravity = 9.8;
	// using formulat: [ s = u * t + (a * t^2) / 2 ], here u(initial velocity) = 0
	double ballHeight = towerHeight - (gravity * seconds * seconds) / 2;
	
	return ballHeight;
}

// prints ball height every second
void printBallHeight(double ballHeight, int seconds)
{
	if(ballHeight > 0)
		std::cout << "At " << seconds << " seconds, the ball is at height: " << ballHeight << " meters\n";
	else
		std::cout << "At " << seconds << " seconds, the ball is on the ground.\n";
}

// calculates and prints ball height every second
void calculateAndPrintBallHeight(double towerHeight, int seconds)
{
	double ballHeight{ calculateBallHeight(towerHeight, seconds) };

	printBallHeight(ballHeight, seconds);
}

int main()
{
	const double towerHeight{ getTowerHeight() };
        
	calculateAndPrintBallHeight(towerHeight, 0);
	calculateAndPrintBallHeight(towerHeight, 1);
	calculateAndPrintBallHeight(towerHeight, 2);
	calculateAndPrintBallHeight(towerHeight, 3);
	calculateAndPrintBallHeight(towerHeight, 4);
	calculateAndPrintBallHeight(towerHeight, 5);

	return 0;
}
