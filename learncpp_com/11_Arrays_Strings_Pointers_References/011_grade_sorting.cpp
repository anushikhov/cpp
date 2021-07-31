// Write the following program: Create a struct that holds a student's first name and grade (on a scale of 0-100).
// Ask the user how many students they want to enter.
// Create a std::vector to hold all of the students.
// Then prompt the user for each name and grade.
// Once the user has entered all the names and grade pairs, sort the list by grade (highest first).
// Then print all the names and grades in sorted order.

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

struct Student
{
	std::string name{};
	int grade{};
};

int getStudentCount()
{
	int number{};
	do
	{
		std::cout << "Enter the number of students: ";
		std::cin >> number;
	} while(number <= 0);

	return number;
}

std::vector<Student> getStudents()
{
	using vector_type = std::vector<Student>;

	int studentCount { getStudentCount() };

	vector_type students(static_cast<vector_type::size_type>(studentCount));

	int studentNumber{ 1 };

	for(auto& student : students)
	{
		std::cout << "\nEnter name #" << studentNumber << ": ";
		std::cin >> student.name;

		std::cout << "Enter grade #" << studentNumber << ": ";
		std::cin >> student.grade;

		++studentNumber;
	}

	return students;
}

bool compareGrades(const Student& a, const Student& b)
{
	return (a.grade > b.grade);
}

int main()
{
	auto students{ getStudents() };

	std::sort(students.begin(), students.end(), compareGrades);

	std::cout << '\n';

	for(const auto& student : students)
	{
		std::cout << student.name << " got a grade of " << student.grade << '\n';
	}

	return 0;
}
