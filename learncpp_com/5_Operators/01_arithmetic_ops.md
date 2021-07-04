# Arithmetic operators

There are two unary arithmetics operators, plus (+), and minus (-).

The **unary minus** operator returns the operand multiplied by -1. The **unary plus** returns the value of the operand.

For best effect, both of these operators should be placed immediately preceding the operand. Generally you won't need the unary plus operator, since it is redundant. It was added largely to provide symmetry with the unary minus operator.

There are five binary arithmetic operators: addition, subtraction, multiplication, division, modulus (remainder).

The division operator has two different "modes".

If either (or both) of the operands are floating point values, the division operator performs floating point division. **Floating point division** returns a floating point value, and the fraction is kept. As with all floating point arithmetic operations, rounding errors may occur.

If both of the operands are integers, the division operator performs integer division instead. **Integer division** drops any fractions and returns an integer value.

We can use the _static\_cast<>_ operator to convert an integer to a floating point number so that we can do floating point division instead of integer division.

Trying to divide by 0 (or 0.0) will generally cause your program to crashm, as the results are mathematically undefined!

C++ provides five arithmetics assignment operators: addition assignment (+=), subtraction assignment (-=), multiplication assignment (\*=), division assignment (\=), modulus assignment (%=).

x = x + 4;

is equivalent to:

x += 4;
