# Naming collisions and an introduction to namespaces

C++ requires that all identifiers be non-ambiguous. If two identical identifiers are introduced into the same program in a way that the compiler or linker can't tell them apart, the compiler or linker will produce an error. This error is generally referred to as a **naming collision** (or **naming conflict**).

Most naming collisions occur in two cases:
1. Two or more definitions for a function or global variable are introduced into separate files that are compiled into the same program. This will result in a linker error, as shown above.
1. Two or more definitions for a function or global variable are introduced into the same file (often via an #include). This will result in a compiler error.

As programs get larger and use more identifiers, the odds of a naming collision being introduced increases significantly. C++ provides plenty of mechanisms for avoiding naming collisions. Local scope, which keeps local variables defined inside functions from conflicting with each other is one such mechanism. 

Local scope doesn't work for function names. So how do we keep function names from conflicting with each other?

A **namespace** is a region that allows you to declare names inside of it for the purpose of disambiguation. The namespace provides a scope (called **namespace scope**) to the names declared inside of it -- which simply means that any name declared inside the namespace won't be mistaken for identical names in other scopes.

Within a namespace, all names must be unique, otherwise a naming collision will result.

Namespaces are often used to group related identifiers in a large project to help ensure they don't inadvertently collide with other identifiers. 


#### The global namespace

In C++, any name that is not defined inside a class, function, or a namespace is considered to be part of an implicitly defined namespace called the **global namespace** (sometimes also called **the global scope**).

#### The std namespace

When C++ was originally designed, all of the identifiers in the C++ standard library were available to be used without the _std::_ prefix (they were part of the global namespace). However, this meant that any identifier in the standard library could potentially conflict with any name you picked for your own identifiers (also defined in the global namespace). Code that was working might suddenly have a naming conflict when you #included a new file from the standard library. Or worse, programs that would compile under one version of C++ might not compile under a future version of C++, as new identifiers introduced into the standard library could have a naming conflict with already written code. So **C++ moved** :D all of the functionality in the standard library into a namespace named "std" (short for standard).

_std::cout_'s name is just _cout_, and _std_ is the name of the namespace that identifier _cout_ is part of. Because _cout_ is defined in the _std_ namespace, the name _cout_ won't conflict with any objects or functions named _cout_ that we create in the global namespace.

**When you use an identifier that is defined inside a namespace, you have to tell the compiler that the identifier lives inside the namespace.**

There are a few different ways to do this.


#### Explicit namespace qualifier std::

The **::** symbol is an operator called the **scope resolution operator**. The identifier to the left of the :: symbol identifies the namespace that the name to the right of the :: symbol is contained within. If no identifier to the left of the :: symbol is provided, the global namespace is assumed.

So when we say _std::cout_, we're saying "the _cout_ that lives in namespace _std_".

This is the safest way to use _cout_, because there's no ambiguity about which _cout_ we're referencing.

**Best practice**
_Use explicit namespace prefixes to access identifiers defined in a namespace._

#### Using namespace std (and why to avoid it)

Another way to access identifiers inside a namespace is to use a _using directive_ statement.

A **using directive** tells the compiler to check the specified namespace when trying to resolve an identifier that has no namespace prefix. 

**Avoid using directives (such as _using namespace std;_ at the top of your program. They violate the reason why namespaces where added in the first place.**

