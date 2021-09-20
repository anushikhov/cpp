#include <array>
#include <cassert>
#include <iostream>

class Stack
{
private:
	using container_type = std::array<int, 10>;
	using size_type = container_type::size_type;

	container_type m_array {};
	size_type m_next{ 0 };

public:
	void reset()
	{
		m_next = 0;
	}

	bool push(int value)
	{
		if(m_next == m_array.size())
		{
			return false;
		}

		m_array[m_next++] = value;

		return true;
	}

	int pop()
	{
		assert(m_next > 0 && "Can not pop empty stack");

		return m_array[--m_next];
	}

	void print()
	{
		std::cout << "( ";
		for (size_type i{ 0 }; i < m_next; ++i)
		{
			std::cout << m_array[i] << ' ';
		}
		std::cout << ")\n";
	}
};

int main()
{
	Stack stack;

	stack.print();

	stack.push(5);
	stack.push(3);
	stack.push(8);
	stack.print();

	stack.pop();
	stack.print();

	stack.reset();
	stack.print();

	return 0;
}
