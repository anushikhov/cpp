// Create a short program asking the user for two integer inputs and a mathematical operation ('+', '-', '*', '/').
// Ensure the user enters a valid operation.

// Write functions named add(), substract(), multiply(), and divide(). 
// These should take two integer parameters and return an integer.

// Create a type alias named ArithmeticFunction for a pointer to a function that takes two integer parameters
// and returns an integer. Use std::function.

// Write a function named getArithmeticFunction() that takes an operator character
// and returns the appropriate function as a function pointer.

// Modify your main() function to call getArithmeticFunction(). 
// Call the return value from that function with your inputs and print the result.

#include <functional>
#include <iostream>


int getInteger()
{
	std::cout << "Enter an integer: ";
	int x{};
	std::cin >> x;

	return x; 
}

char getOperation()
{
	char op{};

	do
	{
		std::cout << "Enter an operation ('+', '-', '*', '/'): ";
		std::cin >> op;
	}
	while(op != '+' && op != '-' && op != '*' && op != '/');

	return op;
}

int add(int x, int y)
{
	return x + y;
}

int subtract(int x, int y)
{
	return x - y;
}

int multiply(int x, int y)
{
	return x * y;
}

int divide(int x, int y)
{
	return x / y;
}

using ArithmeticFunction = std::function<int(int, int)>;

ArithmeticFunction getArithmeticFunction(char op)
{
	switch(op)
	{
		case '+':   return &add;
		case '-':   return &subtract;
		case '*':   return &multiply;
		case '/':   return &divide;
	}
}

int main()
{
	int x{ getInteger() };
	char op{ getOperation() };
	int y{ getInteger() };

	ArithmeticFunction fcn{ getArithmeticFunction(op) };
	std::cout << x << ' ' << op << ' ' << y << " = " << fcn(x, y) << '\n';

	return 0;
}

