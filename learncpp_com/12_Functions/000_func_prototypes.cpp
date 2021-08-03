// Write function prototypes for each of the following functions. 
// Use the most appropriate parameter and return types (by value, by address, or by reference),
// including use of const where appropriate.

// A function named sumTo() that takes an integer parameter 
// and returns the sum of all the numbers between 1 and the input number.

int sumTo(int value);

// A function named printEmployeeName() that takes an Employee struct as input.

void printEmployeeName(const Employee& employee);

// A function named minmax() that takes two integers as input 
// and returns back to the caller the smaller and larger number in a std::pair. 
// A std::pair works identical to a std::tuple but stores exactly two elements.

std::pair<int, int> minmax( int x, int y);

// A function named getIndexOfLargestValue() that takes an integer array(as a std::vector), 
// and returns the index of the largest element in the array.

std::size_t getIndexOfLargestValue(const std::vector<int>& array);

// A function named getElement() that takes an array of std::string (as a std::vector) 
// and an index and returns the array element at that index (not a copy).
// Assume the index is valid, and the return value is const.


const std::string& getElement(const std::vector<std::string>& array, std::size_t index);


// std::minmax and std::max_element are standard functions.
