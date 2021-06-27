# Whitespace and basic formatting

The C++ compiler generally ignores whitespace, with a few minor exceptions (when processing text literals). For this reason, we say that C++ is a whitespace-independent language.

One exception where the C++ compiler does pay attention to whitespace is inside quoted text.

`"Hello world!"`

is different than:

`"Hello     world!"`

and each prints out exactly as you'd expect. 

Newlines are not allowed in quoted text:

` std::cout << "Hello `  
`       world!"; // Not allowed!`

Quoted text separated by nothing but whitespace will be concatenated.

Another exception where the C++ compiler pays attention to whitespace is with // comments. Single-line comments only last to the end of the line.


### Basic formatting

The best styles are the ones that produce the most readable code, and provide the most consistency.

Recommendations for basic formatting:
* It's fine to use either tabs or spaces for indentation. Code taht is spaced using spaces will always look correct regardless of editor. In case you prefer tabs, set them to 4 spaces worth of indentation. Some IDEs default to 3 spaces of indentation, which is fine too.
* There are two acceptable styles for function braces. The Google C++ style guide recommends putting the opening curly brace on the same line as the statement. The justification for this is that it reduces the amount of vertical whitespace, so you can fit more code on a screen. More code on a screen makes the program easier to understand. Prefer the common alternative, where the opening brace appears on its own line. This enhances readability, and is less error prone.
* Each statement within curly braces should start one tab in from the opening brace of the function it belongs to.
* Lines should not be too long. Typically, 80 characters is the maximum length a line should be. If a line is going to be longer, it should be split (at a reasonable spot) into multiple lines. This can be done by indenting each subsequent line with an extra tab, or if the lines are similar, by aligning it with the line above (whichever is easier to read).

**Best practice**
_Your lines should be no longer than 80 chars in length._

* If a long line is split with an operator, the operator should be placed at the beginning of the next line, not the end of the current line. This helps make clearer that subsequent lines are continuations of the previous lines, and allows you to align the operators on the left, which makes for easier reading.
* Use whitespace to make your code easier to read by aligning values or comments or adding spacing between blocks of code.

**If you are working in someone else's code base, adopt their styles. It's better to favor consistency than your preferences.**

**Best practice**
_Using the automatic formatting feature is highly recommended to keep your code's formatting style consistent._

