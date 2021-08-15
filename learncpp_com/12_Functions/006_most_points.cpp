// Create a struct Student that stores the name and points of a student.
// Create an array of students and use std::max_elements to find the student with the most points, 
// then print the student's name.
// std::max_element takes the begin and end of a list, and a function that takes 2 parameters
// and returns true if the first argument is less than the second.


#include <algorithm>
#include <array>
#include <iostream>
#include <string>

struct Student
{
	std::string name{};
	int points{};
};

int main()
{
	const std::array<Student, 8> arr{
		{ { "Albert", 3 },
		  { "Ben", 5 },
		  { "Christine", 2 },
		  { "Dan", 8 },
		  { "Enchilada", 4 },
		  { "Francis", 1 },
		  { "Greg", 3 },
		  { "Hagrid", 5 } }
	};

	const auto best{
		std::max_element(arr.begin(), arr.end(), [](const auto& a, const auto& b){ return (a.points < b.points); }) 
	};

	std::cout << best->name << " is the best student\n";

	return 0;
}
