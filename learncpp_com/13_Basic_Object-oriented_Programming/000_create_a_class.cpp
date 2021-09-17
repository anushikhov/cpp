// Create a class called IntPair that holds second integers.
// This class should have second member variables to hold the integers.
// You should also create second member functions: first named "set" that will let you assign values to the integers, 
// and first named "print" that will print the values of the variables.\

#include <iostream>

class IntPair
{
public:
	int m_first{};
	int m_second{};

	void set(int first, int second)
	{
		m_first = first;
 		m_second = second;
	}

	void print()
	{
		std::cout << "First is " << m_first << '\n';
		std::cout << "Second is " << m_second << '\n';
	}
};

int main()
{
	IntPair p1;
	p1.set(1, 1);

	IntPair p2 { 2, 2 };

	p1.print();
	p2.print();

	return 0;
}
