# Numeric conversions

**Numeric conversion** cover additional type conversions not covered by the numeric promotion rules.

There are five basic types of numeric conversions.

1. Converting an integral type to any other integral type (excluding integral promotions)
1. Converting a floating point type to any other floating point type (excluding floating point promotions)
1. Converting a floating point type to any integral type
1. Converting an integral type to any floating point type
1. Converting an integral type or a floating point type to a bool


## Narrowing conversions

Unlike a numeric promotion (which is always safe), a numeric conversion may (or  may not) result in the loss of data or precision.

Some numeric conversions are always safe (such as `int` to `long`, or `int` to `double`). Other numeric conversions, such as `double` to `int`, may result in the loss of data (depending on the specific value being converted and/or the range of the underlying types).

A **narrowing conversion** is a numeric conversion that may result in the loss of data. Such narrowing conversions include:

* From a floating point type to an integral type
* From a wider floating point type to a narrower floating point type, unless the value being converted is constexpr and is in range of the destination type (even if it can not be represented exactly)
* From an integer to a floating point type, unless the value being converted is constexpr and is in range of the destination type and can be converted back into the original type without data loss
* From a wider integer type to a narrower integer type, unless the value being converted is constexpr and after integral promotion will fit into the destination type

Your compiler will usually issue a warning (or an error) when it determines that an implicit narrowing conversion is required.

**Compilers will often not warn when converting a signed int to an unsigned int, or vice-versa, even though these are narrowing conversion. Be extra careful of inadvertent conversions between these types (particularly when passing an argument to a function taking a parameter of the opposite sign).**

**Best practice**<br/>
_Avoid narrowing conversions whenever possible. If you do need to perform one, use_ `static_cast` _to make it an explicit conversion._


### Brace initialization disallows narrowing conversions

Narrowing conversions are strictly disallowed when using brace initialization (which is one of the primary reasons this initialization form is preferred).

### More on numeric conversions

In all cases, converting a value into a type whose range doesn't support that value will lead to results that are probably unexpected.

Converting from a larger integral or floating point type to a smaller type from the same family will generally work so long as the value fits in the range of the smaller type. In case of floating point values, some rounding may occur due to a loss of precision in the smaller type. 

Converting from an integer to a floating point number generally works as long as the value fits within the range of the floating point type.

Converting from a floating point to an integer works as long as the value fits within the range of the integer, but any fractional values are lost.
