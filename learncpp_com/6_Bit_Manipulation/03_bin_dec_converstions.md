# Converting between binary and decimal

## Converting binary to decimal

0101'1110 = (0 * 128) + (1 * 64) + (0 * 32) + (1 * 16) + (1 * 8) + (1 * 4) + (1 * 2) + (0 * 1) = 94

## Method 1 for converting decimal to binary

Continually divide by 2, write down the remainders. The binary number is constructed at the end from remainders, from the bottom up.

148 / 2 = 74 r0  
74  / 2 = 37 r0  
37  / 2 = 18 r1  
18  / 2 = 9  r0  
9   / 2 = 4  r1  
4   / 2 = 2  r0  
2   / 2 = 1  r0  
1   / 2 = 0  r1  

1001'0100

## Method 2 for converting decimal to binary

148 = (1 * 128) + (0 * 64) + (0 * 32) + (1 * 16) + (0 * 8) + (1 * 4) + (0 * 2) + (0 * 1) = 1001'0100

## Adding in binary

0 + 0 = 0  
0 + 1 = 1  
1 + 0 = 1  
1 + 1 = 0, carry a 1 over to the next column  

## Signed numbers and two's complement

Signed integers are typically stored using **two's complement**. In two's complement, the leftmost (most significant) bit is used as the sign bit. A 0 sign bit means the number is positive, and a 1 sign bit means the number is negative.

Positive signed numbers are represented  in binary just like positive unsigned numbers (with the sign bit set to 0).

Negative signed numbers are represented in binary as the bitwise inverse of the positive number, plus 1.

## Converting decimal to binary (two's complement)

-5

The binary representation of 5: 0000'0101  
Invert all of the bits:         1111'1010  
Add 1:                          1111'1011  

If a negative value was simply represented as the inverse of the positive number, 0 would have two representations: 0000'0000 (positive zero) and 1111'1111 (negative zero). By adding 1, 1111'1111 intentionally overflows and becomes 0000'0000. This prevents 0 from having two representations, and simplifies some of the internal logic needed to do arithmetic with negative numbers.

## Converting binary (two's complement) to decimal

To convert a two's complement binary number back into decimal, first look at the sign bit.

If the sign bit is 0, just convert the number as shown for unsigned numbers above.

If the sign bit is 1, then we invert the bits, add 1, then convert to decimal, then make that decimal number negative (because the sign bit was originally negative).

1001'1110  
0110'0001  
0110'0010  
64 + 32 + 2 = 98  
-98  

The type of the variable determines both how a variable's value is encoded into binary, and decoded back into a value.

