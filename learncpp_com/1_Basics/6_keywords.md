# Keywords and naming identifiers

C++ reserves a set of 92 words (as of C++20) for its own use. These words are called **keywords** (or reserved words), and each of these keywords has a special meaning within the C++ language.

Here is a list of all the C++ keywords (through C++20):

![C++ Reserved Keywords](https://raw.githubusercontent.com/anushikhov/cpp/main/1_Basics/img/keywords.png)

C++ also defines special identifiers: _override, final, import,_ and _module_. These have a specific meaning when used in certain contexts but are not reserved.

Along with a set of operators, these keywords and special identifiers define the entire language of C++ (preprocessor commands excluded).

### Identifier naming rules

The name of the variable (or function, type, or other kind of item) is called an identifier.

There are a few rules that must be followed when naming identifiers:
* The identifier can not be a keyword.
* The identifier can only be composed of letters, numbers, and the underscore character.
* The identifier must begin with a letter or an underscore.
* C++ is case sensitive.

#### Identifier naming best practices

* It is a convention in C++ that variable names should begin with a lowercase letter.
* Most often, function names are also started with a lowercase letter.
* Identifer names that start with a capital letter are typically used for user-defined types (i.e. structs, classes, enumerations).
* If the variable or function name is multi-word, there are two common conventions: words separated by underscores, called snake_case, or intercapped (sometimes called camelCase). The C++ standard library uses the underscore method for both variables and functions. Sometimes you'll see a mix of the two: underscores used for variables and intercaps used for functions. 

**Best practice**
_When working in an existing program, use the conventions of that program (even if they don't conform to modern practices). Use modern best practices when you're writing new programs._

* Avoid naming your identifiers starting with an underscore, as these names are typically reserved for OS, library, and/or compiler use.
* Your identifiers should make clear what the value they are holding means (particularly if the units aren't obvious).
* A good rule of thumb is to make the length of an identifier proportional to how widely it is used. An identifier with a trivial use can have a short name (e.g. such as _i_). An identifier that is used more broadly (e.g. a function that is called from many places in program) should have a longer and more descriptive name.
* Avoid abbreviations. Although they reduce the time you need to write your code, they make your code harder to read. Even if the abbreviation is unambiguous, it takes the reader a moment to figure out what you meant.
* A clarifying comment can go a long way.

`// holds number of chars in a piece of text -- including whitespace and punctuation`  
`int numberOfChars;`
