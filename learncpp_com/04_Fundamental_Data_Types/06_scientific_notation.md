# Introduction to scientific notation

**Scientific notation** is a useful shorthand for writing lengthy numbers in a concise manner. Understanding scientific notation will help you understand how floating point numbers work and what their limitations are.

Numbers in scientific notation take the following form: _significand_ x 10^exponent. For example, in the scientific notation 1.2 x 10^4, 1.2 is the significand and 4 is the exponent. Since 10^4 evaluates to 10,000, 1.2 x 10^4 evaluates to 12,000.

By convention, numbers in scientific notation are written with one digit before the decimal point, and the rest of the digits afterward.

Scientific notation has the added benefit of making it easier to compare the magnitude of two really large or really small numbers simply by comparing the exponent.

Because it can be hard to type or display exponents in C++, we use the letter 'e' (or sometimes 'E') to represent the "times 10 to the power of" part of the equation. For example, 1.2 x 10^4 would be written as 1.2e4 .

For numbers smaller than 1, the exponent can be negative. The number 5e-2 is equivalent to 5 * 10^-2, which is 5 / 10^2, or 0.05.

### How to convert numbers to scientific notation

Use the following procedure:

* Your exponent starts at zero
* Slide the decimal so there is only one non-zero digit to the left of the decimal.
     * Each place you slide the decimal to the left increases the exponent by 1
     * Each place you slide the decimal to the right decreases the exponent by 1
* Trim off any leading zeros (on the left end of the significand)
* Trim off any trailing zeros (on the right end of the significand) only if the original number had no decimal point. We're assuming they're not significant unless otherwise specified.

e.g.

42030 -- 4.203e4 ( 4 significant digits )
0.0078900 -- 7.8900e-3 ( 5 significant digits )
600.410 -- 6.00410e2 ( 6 significant digits )

The digits in the significand (the part before the 'e') are called the **significant digits**. The number of significant digits defines a number's **precision**. The more digits in the significand, the more precise the number is.


## Precision and trailing zeros after the decimal

In standard scientific notation, we prefer to keep trailing zeros after a decimal point, because those digits impact useful information about the precision of the number.


