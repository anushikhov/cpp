# Random number generation

Computers are generally incapable of generating random numbers. Instead, they must simulate randomness, which is most often done using pseudo-random number generators.

A **pseudo-random number generator (PRNG)** is a program that takes a starting number (called a **seed**), and performs mathematical operations on it to transform it into some other number that appears to be unrelated to the seed. It then takes that generated number and performs the same mathematical operation on it to transform it into a new number that appears unrelated to the number it was generated from. By continually applying the algorithm to the last generated number, it can generate a series of new numbers that will appear to be random if the algorithm is complex enough.

**Best practice**<br/>
_You should only seed your random number generators once. Seeding them more than once will cause the results to be less random or not random at all._

Here's a short program that effectively illustrates the principle of a PRNG:

` #include <iostream> `  

` unsigned int PRNG() `  
` { `  
&emsp;&emsp;&emsp;` static unsigned int seed{ 5323 }; `  
&emsp;&emsp;&emsp;` seed = 8253729 * seed + 2396403; `  

&emsp;&emsp;&emsp;` return seed % 32768; `  
` } `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` for(int count{ 1 }; count <= 100; ++count) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << PRNG() << '\t'; `  

&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` if(count % 5 == 0) `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << '\n'; `  
&emsp;&emsp;&emsp;` } `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  


## Generating random numbers in C++

C (and by extension C++) comes with a built-in pseudo-random number generator. It is implemented as two separate functions that live in the cstdlib header:

`std::srand()` sets the initial seed value to a value that is passed in by the caller. `std::srand()` should only be called once at the beginning of your program. This is usually done at the top of main().

`std::rand()` generates the next random number in the sequence. That number will be a pseudo-random integer between 0 and RAND_MAX, a constant in cstdlib that is typically set to 32767.

` #include <iostream> `  
` #include <cstdlib> `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` std::srand(5323); // set initial seed value to 5323`  

&emsp;&emsp;&emsp;` // Due to a flaw in some compilers, we need to call std::rand() once here to get better random numbers `  
&emsp;&emsp;&emsp;` std::rand(); `  

&emsp;&emsp;&emsp;` for(int count{ 1 }; cout <= 100; ++count) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << std::rand() << '\t'; `  

&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` if(cout % 5 == 0) `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << '\n'; `  
&emsp;&emsp;&emsp;` } `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  


## PRNG sequences and seeding

If you run the std::rand() sample program above multiple times, you will note that it prints the same result every time. This means that while each number in the sequence is seemingly random with regards to the previous ones, the entire sequence is not random. And that means the program ends up totally predictable (the same inputs lead to the same outputs every time). There are cases where this can be useful or even desired (e.g. you want a scientific simulation to be repeatable). But often, this is not what is desired. If you're writing a game of hi-lo, you don't want the program picking the same numbers each time.

Each number in a PRNG sequence is generated from the prvious number, in a deterministic way. Thus, given any starting seed number, PRNGs will always generate the same sequence of numbers from that seed as a result. We are getting the same sequence because our starting seed number is always 5323.

In order to make our entire sequence randomized, we need some way to pick a seed that's not a fixed number. The first answer that probably comes to mind is that we need a random number! That's a good thought, but if we need a random number to generate random numbers, then we're in a catch-22. It turns out, we really don't need our seed to be a random number -- we just need to pick something that changes each time the program is run. Then we can use our PRNG to generate a unique sequence of pseudo-random numbers from that seed.

The commonly accepted method for doing this is to enlist the system clock. Each time the user runs the program, the time will be different. If we use this time value as our seed, then our program will generate a different sequnce of numbers each time it is run.

C comes with a function called `std::time()` that returns the number of seconds since midnight on Jan 1, 1970. To use it, we merely need to include the `ctime` header, and then initialize `std::srand()` with a call to `std::time(nullptr)`. 

` #include <iostream> `  
` #include <cstdlib> `  
` #include <ctime> `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` std::srand(static_cast<unsigned int>(std::time(nullptr))); `  

&emsp;&emsp;&emsp;` for(int count{ 1 }; count <= 100; ++count) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << std::rand() << '\t'; `  

&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` if(count % 5 == 0) `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << '\n'; `  
&emsp;&emsp;&emsp;` } `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

Now the program will generate a different sequence of random numbers every time.


## Generating random numbers between two arbitrary values

Generally, we do not want random numbers between 0 and RAND_MAX -- we want numbers between two other values. For example, if we're trying to simulate the user rolling a die, we want random numbers between 1 and 6.

Here's a short function that converts the result of rand() into the range:

` // Generate a random number between min and max (inclusive) `  
` // Assumes std::srand() has already been called `  
` // Assumes max - min <= RAND_MAX `  
` int getRandomNumber(int min, int max) `  
` { `  
&emsp;&emsp;&emsp;` static constexpr double fraction { 1.0 / (RAND_MAX + 1.0) }; // static used for efficiency, so we only calculate this value once `  
&emsp;&emsp;&emsp;` // evenly distribute the random number across the range `  
&emsp;&emsp;&emsp;` return min + static_cast<int>((max - min + 1) * (std::rand() * fraction)); `  
` } `  

1. We multiply the result from std::rand() by fraction. This converts the result of rand() to a floating point number between [0, 1). If rand() returns a 0, then 0 * fraction is still 0. If rand() returns RAND_MAX, then RAND_MAX * fraction is RAND_MAX / (RAND_MAX + 1), which is slightly less than 1. Any other number returned by rand() will be evenly distributed between these two points.

1. Next, we need to know how many numbers we can possibly return. In other words, how many numbers are between min (inclusive) and max (inclusive). This is simply (max - min + 1).

1. We multiply the prior two results together. If we had a floating point number between 0 (inclusive) and 1 (exclusive), and then we multiply be (max - min + 1), we now have a floating point number between 0 (inclusive) and (max - min + 1) (exclusive).

1. We cast the previous result to an integer. This removes any fractional component, leaving us with an integer result between 0 (inclusive) and (max - min) (inclusive).

1. Finally, we add min, which shifts our result to an integer between min (inclusive) and max (inclusive).

To simulate the roll of a die, we'd call getRandomNumber(1, 6). To pick a randomized digit, we'd call getRandomNumber(0, 9).

Let's consider what would happen if the above function looked like this instead:

` return min + (std::rand() % (max - min + 1)); `  

This method has a clear bias towards low results. By extension, most cases involving this algorithm will behave similarly.

Even though getRandomNumber() is a little more complicated than the modulus alternative, we advocate for the division method because it produces a less biased result.


## What is a good PRNG?

In order to be a good PRNG, the PRNG needs to exhibit a number of properties:

First, the PRNG should generate each number with approximately the same probability. This is called **distribution uniformity**. If some numbers are generated more often than others, the result of the program that uses the PRNG will be biased.

Second, the method by which the next number in the sequence is generated should not be obvious or predictable. For example, consider the following PRNG algorithm: num = num + 1. This PRNG is prefectly uniform, but it's not very useful as a sequence of random numbers.

Third, the PRNG should have a good dimensional distribution of numbers. This means it should return low numbers, middle numbers, and high numbers seemingly at random. A PRNG that returned all low numbers, then all high numbers may be uniform and non-predictable, but it's still going to lead to biased results, particularly if the number of random numbers you actually use is small.

Fourth, all PRNGs are periodic, which means that at some point the sequence of numbers generated will begin to repeat itself. The length of the sequence before a PRNG begins to repeat itself is known as the **period**.

PRNGs are deterministic -- given some set of input values, they will produce the same output values every time. This means that once the PRNG encounters a set of inputs it has used before, it will start producing the same sequence of outputs it has produced before -- resulting in a loop.

A good PRNG should have a long period for all seed numbers. Designing an algorithm that meets this property can be extremely difficult -- most PRNGs will have long periods for some seeds and short periods for others. If the user happens to pick a seed that has a short period, then the PRNG won't be doing a good job.

Despite the difficulty in designing algorithms that meet all of these criteria, a lot of research has been done in this area because of its importance to scientific computing.


## std::rand() is a mediocre PRNG

The algorithm used to implement `std::rand()` can vary from compiler to compiler, leading to results that may not be consistent across compilers. Most implementations of `rand()` use a **Linear Congruential Generator (LCG)** algorithm. The first example in the lesson is actually an LCG, though one with intentionally picked poor constants. LCGs tend to have shortcomings that make them not good choices for most kinds of problems.

One of the main shortcomings of `rand()` is that `RAND_MAX` is usually set to 32767 (essentially 15-bits). This means if you want to generate numbers over a larger range (e.g. 32-bit integers), `rand()` is not suitable. Also, `rand()` isn't good if you want to generate random floating point numbers (e.g. between 0.0 and 1.0), which is often useful when doing statistical modelling. Finally, `rand()` tends to have a relatively short period compared to other algorithms.

That said, `rand()` is perfectly suitable for programs in which a high-quality PRNG is not a necessity.

For applications where a high-quality PRNG is needed, use the **Mersenne Twister** (or one of its variants). Mersenne Twister was adopted into C++11.

### Debugging programs that use random numbers

When debugging programs that use random numbers, it's a useful technique to set the random seed (via `std::srand`) to a specific value that causes the erroneous behavior to occur. This will ensure your program generates the same results each time, making debugging easier. Once you've found the error, you can seed using the system clock again to start generating randomized results again.


## Better random numbers using Mersenne Twister

C++11 added a ton of random number generation functionality to the C++ standard libarary, including the Mersenne Twister algorithm, as well as generators for different kinds of random distributions (uniform, normal, Poisson, etc...). This is accessed via the <random> header.

Here's a short example showing how to generate random numbers in C++11 using Mersenne Twister:

` #include <iostream> `  
` #include <random> `  
` #include <ctime> `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` // Initialize mersenne twister with a random seed based on the system clock once at system startup`  
&emsp;&emsp;&emsp;` std::mt19937 mersenne{ static_cast<std::mt19937::result_type>(std::time(nullptr)) }; `  

&emsp;&emsp;&emsp;` // Create a reusable random number generator that generates uniform numbers between 1 and 6 `  
&emsp;&emsp;&emsp;` std::uniform_int_distribution die{ 1, 6 }; `  

&emsp;&emsp;&emsp;` for(int count{ 1 }; count <= 48; ++count) `  
&emsp;&emsp;&emsp;` { `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << die(mersenne) << '\t'; `  

&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` if(count % 6 == 0) `  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;` std::cout << '\n'; `  
&emsp;&emsp;&emsp;` } `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

Before C++17, you need to add empty brackets to create die after the type `std::uniform_int_distribution<> die{ 1, 6 };`  

Mersenne Twister generates random 32-bit unsigned integers (not 15-bit integers like `std::rand()`), giving a lot more range. There's also a version (`std::mt19937_64`) for generating 64-bit unsigned integers.

### Random number across multiple functions

The above examples create a random generator for use within a single function. What happens if we want to use a random number generator in multiple functions?

Although you can create a static local `std::mt19937` variable in each function that needs it (static so that it only gets seeded once), it's a little overkill to have every function that needs a random number generator seed and maintain its own local generator. A better option in most cases is to create a global random number generator (inside a namespace). You should generally avoid non-const global variables, however this is an exception. Also, `std::rand()` and `std::srand()` access a global object, so there's precedent for this.

` #include <iostream> `  
` #include <random> `  
` #include <ctime> `  

` namespace MyRandom `  
` { `  
&emsp;&emsp;&emsp;` std::mt19937 mersenne{ static_cast<std::mt19937::result_type>(std::time(nullptr)) }; `  
` } `  

` int getRandomNumber(int min, int max) `  
` { `  
&emsp;&emsp;&emsp;` std::uniform_int_distribution die{ min, max }; `  

&emsp;&emsp;&emsp;` return die(MyRandom::mersenne); `  
` } `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` std::cout << getRandomNumber(1, 6)  << '\n'; `  
&emsp;&emsp;&emsp;` std::cout << getRandomNumber(1, 10) << '\n'; `  
&emsp;&emsp;&emsp;` std::cout << getRandomNumber(1, 20) << '\n'; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  


## Using a random library

A perhaps better solution is to use a 3rd party library that handles all of this stuff for you, such as the header-only ![Effolkronium's random library](https://github.com/effolkronium/random). You simply add the header to your project, `#include` it , and then you can start generating random numbers vai `Random::get(min, max)`:  

` #include <iostream> `  
` #include "random.hpp" `  

` // Get base random alias which is auto seeded and has static API and internal state `  
` using Random = effolkronium::random_static; `  

` int main() `  
` { `  
&emsp;&emsp;&emsp;` std::cout << Random::get(1, 6)  << '\n'; `  
&emsp;&emsp;&emsp;` std::cout << Random::get(1, 10) << '\n'; `  
&emsp;&emsp;&emsp;` std::cout << Random::get(1, 20) << '\n'; `  

&emsp;&emsp;&emsp;` return 0; `  
` } `  

...  

The implementation of `rand()` in Visual Studio and a few other compilers has a flaw -- the first random number generated doesn't change much for similar seed values. The solution here, and a good rule of thumb in general, is to discard the first random number generated from the random number generator.

If your random number generator is generating the same number every time you ask it for a random number, then you are probably either reseeding the random number generator before generating a random number, or you're creating a new random generator for each random number. 

For random results, you should only seed a random number generator once (generally at program initialization for `std::srand()`, or the point of creation for other random number generators), and then use that same random number generator for each successive random number generated.

Remember to make random number generators `static` or declare them outside of the function.
