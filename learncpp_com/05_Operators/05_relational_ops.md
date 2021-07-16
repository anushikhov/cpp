# Relational operators and floating point comparisons

**Relational operators** let you compare two values.

**Best practice**<br/>
_Don't add unnecessary == or != to conditions. It makes them harder to read without offering any additional value._

## Comparison of floating point values

If a high level of precision is required, comparing floating point values using any of the relational operators can be dangerous. This is because floating point values are not precise, and small rounding errors in the floating point operands may cause unexpected results.

When the less than and greater than operators (<, <=, >, and >=) are used with floating point values, they will usually produce the correct answer (only potentially failing when the operands are almost identical). Because of this, use of these operators with floating point operands can be acceptable, so long as the consequence of getting a wrong answer when the operands are similar is slight.

### Floating point equality

Because even the smallest rounding error will cause two floating point numbers to not be equal, operator== is at high risk for returning false when a true might be expected. Operator!= has the same kind of problem.

**Avoid using operator== and operator!= with floating point operands.**

The most common method of doing floating point equality involves using a function that looks to see if two numbers are almost the same. If they are "close enough", then we call them equal. The value used to represent "close enough" is traditionally called **epsilon**. Epsilon is generally defined as a small positive number (e.g. 0.00000001, sometimes written 1e-8).

New developers often try to write their own "close enough" function like this:

` #include <cmath>   // for std::abs() `  

` // epsilon is an absolute value `  
` bool isAlmostEqual(double a, double b, double epsilon) `  
` { `  
` // if the distance between a and b is less than epsilon, then a and b are "close enough" `  
&emsp;&emsp;&emsp;` return std::abs(a - b) <= epsilon; `  
` } `  

std::abs() is a function in the <cmath> header that returns the absolute value of its argument.

While this function can work, it's not great. An epsilon of 0.00001 is good for inputs around 1.0, too big for inputs around 0.0000001, and too small for inputs like 10,000. This means every time we call this function, we have to pick an epsilon that's appropriate for our inputs. If we know we're going to have to scale epsilon in proportion to our inputs, we might as well modify the function to do that for us.

Donald Knuth suggested the following method in his book "The Art of Computer Programming, Volume II: Seminumerical Algorithms":  

` #include <cmath>      // std::abs `  
` #include <algorithms> // std::max `  

` //return true if the difference between a and b is within epsilon percent of the larger of a and b `  
` bool approximatelyEqual(double a, double b, double epsilon) `  
` { `  
&emsp;&emsp;&emsp;` return (std::abs(a - b) <= (std::max(std::abs(a), std::abs(b)) * epsilon)); `  
` } `  

In this case, instead of epsilon being an absolute number, epsilon is now relative to the magnitude of a or b.

The algorithm chooses the larger of a and b (as a rough indicator of the overall magnitude of the numbers), and then multiplies it by epsilon. In this function, epsilon represents a percentage.

While the approximatelyEqual() function will work for most cases, it is not perfect, especially as the numbers approach zero. The math simply breaks down close to zero.

One way to avoid this is to use both an absolute epsilon (as we did in the first approach) and a relative epsilon (as we did in Knuth's approach).

` // return true if the difference between a and b is less than apsEpsilon,  `  
` // or within relEpsilon percent of the larger of a and b `  
` bool approximatelyEqualAbsRel(double a, double b, double absEpsilon, double relEpsilon) `  
` { `  
&emsp;&emsp;&emsp;` // Check if the numbers are really close -- needed when comparing numbers near zero. `  
&emsp;&emsp;&emsp;` double diff{ std::abs(a - b) }; `  
&emsp;&emsp;&emsp;` if (diff <= absEpsilon) `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` return true; `  
<br/>
&emsp;&emsp;&emsp;` // Otherwise fall back to Knuth's algorithm `  
&emsp;&emsp;&emsp;` return (diff <= (std::max(std::abs(a), std::abs(b)) * relEpsilon)); `  
` } `  

In this algorithm, we first check if a and b are close together in absolute terms, which handles the case where a and b are both close to zero. The absEpsilon parameter should be set to something very small (e.g. 1e-12). If that fails, then we fall back to Knuth's algorithms, using the relative epsilon.

