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


In the Unicode standard, code points are written in hexadecimal and prefixed with U+, 
such as U+0041 for the code point of the Latin letter A. Unicode has code points that 
are grouped into 17 code planes. The first code plane , called the basic multilingual 
plane, consists of the "classic" Unicode characters with code points U+0000 to U+FFFF
. Sixteen additional planes, with code points U+10000 to U+10FFFF, hold the suppleme-
ntary characters.
The UTF-16 encoding represents all Unicode code points in a variable-length code. The
characters in the basic multilingual plane are represented as 16-bit values, called -
code units. The supplementary characters are encoded as consecutive pairs of code un-
its. Each of the values in such an encoding pair falls into a range of 2048 unused v-
alues of the basic multilingual plane, called the surrogates area (U+D800 to U+DBFF -
for the first code unit, U+DC00 to U+DFFF for the second code unit). This is rather -
clever, because you can immediately tell whether a code unit encodes a single charac-
ter or it is the first or second part of a supplementary character. For example , the 
mathematical symbol for the set of integers  ZZ has code point U+1D56B and is encoded 
by the two code units U+D835 and U+DD6B. (See http://en.wikipedia.org/wiki/UTF-16 for 
a description of the encoding algorithm.)
In Java, the char type describes a code unit in the UTF-16 encoding. Our strong reco-
mmendation is not to use the char type in your programs unless you are actually mani-
pulating UTF-16 code units. You are almost always better off treating strings as abs-
tract data types.



----> Variables
In Java, every variable has a type. You declare a variable by placing the type first, 
followed by the name of the variable. Here are some examples:
double salary;
int vacationDays;
long earthPopulation;
boolean done;
Notice the semicolon at the end of each declaration. The semicolon is necessary beca-
use a declaration is a complete Java statement.

----> variable name
A variable name must begin with a letter and must be a sequence of letters or digits. 
Note that the terms "letter" and "digit" are much broader in Java than in most langu-
ages. A letter is defined as 'A'¨C'Z', 'a'¨C'z', '_', '$',or any Unicode character that 
denotes a letter in a language. For example, Greek speakers could use a ¦Ð. Similarly, 
digits are '0'¨C'9' and any Unicode characters that denote a digit in a language. Sym-
bols like '+' cannot be used inside variable names, nor can spaces. All characters in 
the name of a variable are significant and case is also significant. The length of  a 
variable name is essentially unlimited.

If you are really curious as to what Unicode characters are "letters" as far as  Java 
is concerned , you can use the isJavaIdentifierStart and isJavaIdentifierPart methods 
in the Character class to check. Even though $ is a valid Java letter, you should not 
use it in your own code. It is intended for names that are generated by the Java com-
piler and other tools. You also cannot use a Java reserved word for a variable name. 

You can have multiple declarations on a single line:
int i, j; // both are integers
However, we don¡¯t recommend this style. If you declare each variable separately, your
programs are easier to read.

----> Initializing Variables
After you declare a variable, you must explicitly initialize it by means of an assig-
nment statement. For example, the Java compiler flags the following sequence of stat-
ements as an error:
int vacationDays;
System.out.println(vacationDays); // ERROR--variable not initialized

You assign to a previously declared variable by using the variable name on the left, 
an equal sign (=), and then some Java expression with an appropriate value on the ri-
ght.
int vacationDays;
vacationDays = 12;
You can both declare and initialize a variable on the same line. For example:
int vacationDays = 12;
Finally, in Java you can put declarations anywhere in your code. For example, the fo-
llowing is valid code in Java:
double salary = 65000.0;
System.out.println(salary);
int vacationDays = 12; // OK to declare a variable here
In Java, it is considered good style to declare variables as closely as possible to -
the point where they are first used.

C and C++ distinguish between the declaration and definition of a variable. For exam-
ple,
int i = 10;
is a definition, whereas
extern int i;
is a declaration. In Java, no declarations are separate from definitions.

----> Constants
In Java, you use the keyword final to denote a constant . The keyword final indicates 
that you can assign to the variable once, and then its value is set once and for all. 
It is customary to name constants in all uppercase. It is probably more common in Ja-
va to create a constant  so it¡¯s available to multiple methods inside a single class. 
These are usually called class constants. Set up a class constant with the keywords -
static final. Here is an example of using a class constant:

public class Constants2
{
    public static final double CM_PER_INCH = 2.54;
    public static void main(String[] args)
    {
        double paperWidth = 8.5;
        double paperHeight = 11;
        System.out.println("Paper size in centimeters: "
        + paperWidth * CM_PER_INCH + " by " + paperHeight * CM_PER_INCH);
    }
}

Note that the definition of the class constant appears outside the main method. Thus, 
the constant can also be used in other methods of the same class. Furthermore, if the 
constant is declared, as in our example, public, methods of other classes can also u-
se it. in our example, as Constants2.CM_PER_INCH.




*/
