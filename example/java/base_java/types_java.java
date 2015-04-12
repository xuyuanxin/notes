/*-----------------------------------------------------------------------------------
Java is a strongly typed language.This means that every variable must have a declared
type. There are eight primitive types in Java. Four of them are integer types;two are 
floating-point number types; one is the character type char, used for code units in -
the Unicode encoding scheme; and one is a boolean type for truth values.


----> Integer Types
The integer types are for numbers without fractional parts. Negative values are allowed.
Java provides the four integer types:
int    4 bytes
short  2 bytes
long   8 bytes
byte   1 byte

Under Java, the ranges of the integer types do not depend on the machine on which you
will be running the Java code. 

Long integer numbers have a suffix L (for example, 4000000000L) . Hexadecimal numbers
have a prefix 0x (for example, 0xCAFE). Octal numbers have a prefix 0. For example, -
010 is 8. Starting with Java 7, you can write numbers in binary, with a prefix 0b. F-
or example, 0b1001 is 9. Also starting with Java 7, you can add underscores to number 
literals, such as 1_000_000 (or 0b1111_0100_0010_0100_0000) to denote one million. T-
he underscores are for human eyes only. The Java compiler simply removes them.

----> Floating-Point Types
The floating-point types denote numbers with fractional parts. The two floating-point 
types:
float  4 bytes  6~7 significant decimal digits
double 8 bytes  15 significant decimal digits

Numbers of type float have a suffix F (for example, 3.14F). Floating-point numbers w-
ithout an F suffix (such as 3.14) are always considered to be of type double. You can 
optionally supply the D suffix (for example, 3.14D).

All floating-point computations follow the IEEE 754 specification. In particular, th-
ere are three special floating-point values to denote overflows and errors:
1 Positive infinity
2 Negative infinity
3 NaN (not a number)
For example, the result of dividing a positive number by 0 is positive infinity. Com-
puting 0/0 or the square root of a negative number yields NaN.

----> The char Type

----> The boolean Type
The boolean type has two values, false and true. It is used for evaluating logical c-
onditions. You cannot convert between integers and boolean values.
-------------------------------------------------------------------------------------
----> Enumerated Types
An enumerated type has a finite number of named values. For example:
    enum Size { SMALL, MEDIUM, LARGE, EXTRA_LARGE };
Now you can declare variables of this type:
    Size s = Size.MEDIUM;
A variable of type Size can hold only one of the values listed in the type declarati-
on, or the special value null that indicates that the variable is not set to any val-
ue at all.

*/
