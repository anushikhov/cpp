#include <iostream>
#include <stack>

void printStack(std::stack<int> stack)

{
	std::cout << "( ";
	while (!stack.empty())
	{
		std::cout << stack.top() << ' ';
		stack.pop();
	}
	std::cout << ")\n";
}

int main()
{
	std::stack<int> stack;

	printStack(stack);

	stack.push(5);
	stack.push(2);
	printStack(stack);

	stack.pop();
	printStack(stack);

	stack = {};
	printStack(stack);

	return 0;
}
