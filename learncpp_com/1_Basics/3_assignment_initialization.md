# Variable assignment and initialization

#### Copy assignment

` int width;`

` width = 7;`

Copy assignment is named such because it copies the value on the right-hand side of the _=operator_ to the variable on the left-hand side of the operator.

The _=operator_ is called the **assignment operator**.


#### Initialization

` int width = 7; `

` int width( 7 ); `

` int width{ 7 }; `

#### Copy initialization

` int width = 7; `

For simple types like int, copy initialization is efficient. However, when types get more complex, copy initialization can be inefficient.


#### Direct initialization

` int width( 7 ); `

For simple data types like int, copy and direct initialization are essentially the same. For more complicated types, direct initialization tends to be more efficient than copy initialization.


#### List initialization

Direct initialization can't be used for all types of initialization (such as initializing an object with a list of data). 

To provide a more consistent initialization mechanism, there's **list initialization** (also called **uniform initialization** or **brace initialization**) that uses curly braces.

List initialization comes in three forms:

` int width{ 7 };    // direct list initialization (preferred)`

` int width = { 7 }; // copy list initialization`

` int width {};      // value initialization`

Direct and copy list initialization function almost identically, but the direct form is generally preferred.

List initialization has the added benefit of disallowing "narrowing" conversions. Conversions that can be done without potential data loss are allowed.

**Best practice**
_Favor initialization using braces whenever possible._


##### Value initialization and zero initialization

When a variable is initialized with empty braces, **value initialization** takes place. In most cases, **value initialization** will initialize the variable to zero (or empty, if that's more appropriate for a given type). In such cases where zeroing occurs, this is called **zero initialization**.

`int width{}; // zero initialization to value 0`

Use an explicit initialization value if you're actually using that value.
Use value initialization if the value is temporary and will be replaced.

**Best practice**
_Initialize your variables upon creation._

You may eventually find cases where you want to ignore this advice for a specific reason (e.g. a performance critical section of code that uses a lot of variables), and that's okay, as long as the choice is made deliberately.

##### Initializing multiple variables

You can initialize multiple variables defined on the same line:

` int a = 5, b = 6;   // copy initialization`

` int c( 1 ), d( 7 ); // direct initialization`

` int e{ 3 }, f{ 4 }; // list initialization `

Initialization gives a variable an initial value at the point when it is created.
Assignment gives a variable a value at some point after the variable is created.
