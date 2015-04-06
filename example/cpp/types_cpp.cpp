/*-----------------------------------------------------------------------------------
Types are fundamental to any program: They tell us what our data mean and what opera-
tions we can perform on those data. When the type of a variable named v is T, we oft-
en say that "v has type T" or, interchangeably, that "v is a T".


----> Primitive Built-in Types
C++ defines a set of primitive types that include the arithmetic types  and a special 
type named void. The arithmetic types represent characters, integers, boolean values, 
and floating-point numbers. The void type has no associated values and can be used in 
only a few circumstances , most commonly as the return type for functions that do not 
return a value. The arithmetic types are divided into two categories : integral types 
(which include character and boolean types) and floating-point types.

The size of (that is, the number of bits in) the arithmetic types varies across mach-
ines. The standard guarantees minimum sizes as listed in Table 2.1. However,compilers 
are allowed to use larger sizes for these types. 

-------------------------------------------------------------------------------------
                   Table 2.1 C++ Arithmetic Types
-------------------------------------------------------------------------------------
Tpye        | Meaning                           | Minimum Size 
------------|-----------------------------------|------------------------------------
bool        | boolean                           | NA
char        | character                         | 8bits
wchar_t     | wide character                    | 16bits
char16_t    | Unicode character                 | 16bits
char32_t    | Unicode character                 | 32bits
short       | short interger                    | 16bits
int         | interger                          | 16bits
long        | long interger                     | 32bits
long long   | long interger                     | 64bits
float       | single-precision floating-point   | 6 significant digits
double      | double-precision floating-point   | 10 significant digits
long double | extended-precision floating-point | 10 significant digits
------------|-----------------------------------|------------------------------------

bool
    The bool type represents the truth values true and false.

wchar_t char16_t char32_t
   wchar_t type is guaranteed to be large enough to hold any character in the machin-
   e's largest extended character set. The types char16_t and char32_t are intended -
   for Unicode characters. (Unicode is a standard for representing characters used in 
   essentially any natural language.)

float 
    Typically, float are represented in one word (32 bits), doubles in two words ( 64 
    bits), and long doubles in either three or four words (96 or 128 bits). The float 
    and double types typically yield about 7 and 16 significant digits, respectively. 
    The type long double is often used as a way to accommodate special-purpose float-
    ing-point hardware ; its precision is more likely to vary from one implementation 
    to another.   


------------------------------------------------------------------------------------- 
Signed and Unsigned Types
------------------------------------------------------------------------------------- 
Except for bool and the extended character types, the integral types may be signed or 
unsigned. The types int, short, long, and long long are all signed. We obtain the co-
rresponding unsigned type by adding unsigned to the type, such as unsigned long . The 
type unsigned int may be abbreviated as unsigned.

char is signed on some machines and unsigned on others. If you need a tiny integer, -
explicitly specify either signed char or unsigned char.

---->
Integer literals that begin with 0 (zero) are interpreted as octal . Those that begin
with either 0x or 0X are interpreted as hexadecimal. For example, we can write the v-
alue 20 in any of the following three ways: 20 024 0x14.

By default, decimal literals are signed whereas octal and hexadecimal literals can be 
either signed or unsigned types. A decimal literal has the smallest type of int, long, 
or long long(i.e., the first type in this list) in which the literal's value fits. O-
ctal and hexadecimal literals have the smallest type of int, unsigned int, long, uns-
igned long, long long, or unsigned long long in which the literal's value fits. It is 
an error to use a literal that is too large to fit in the largest related type. There 
are no literals of type short.

---->
Although integer literals may be stored in signed types, technically speaking, the v-
alue of a decimal literal is never a negative number. If we write what appears to be 
a negative decimal literal, for example, -42, the minus sign is not part of the lit-
eral. The minus sign is an operator that negates the value of its (literal) operand.

Floating-point literals include either a decimal point or an exponent specified using
scientific notation. Using scientific notation, the exponent is indicated by either E 
or e: 3.14159  3.14159E0  0.  0e0  .001. By default,floating-point literals have type 
double. We can override the default using a suffix from Table 2.2.

----> Character and Character String Literals
A character enclosed within single quotes is a literal of type char. Zero or more ch-
aracters enclosed in double quotation marks is a string literal:
'a' // character literal
"Hello World!" // string literal
The compiler appends a null character ('\0') to every string literal. 
Two string literals that appear adjacent to one another and that are separated only -
by spaces, tabs, or newlines are concatenated into a single literal. 
// multiline string literal
std::cout << "a really, really long string literal "
             "that spans two lines" << std::endl;

----> Boolean and Pointer Literals
The words true and false are literals of type bool:
bool test = false;
The word nullptr is a pointer literal.


Table 2.2. Specifying the Type of a Literal
Character and Character String Literals
------------------------------------------------+
Prefix | Meaning                     | Type     |
-------|-----------------------------|----------|
u      | Unicode 16 character        | char16_t |
U      | Unicode 32 character        | char32_t |
L      | wide character              | wchar_t  |
u8     | utf-8(string literals only) | char     |
------------------------------------------------+
Integer Literals
------------------------+
Suffix   | Minimum Type |
---------|--------------|
u or U   | unsigned     | 
l or L   | long         |
ll or LL | long long    |
------------------------+
Floating-Point Literals
---------------------+
Suffix | Type        |
-------|-------------|
f or F | float       |
l or L | long double |
---------------------+

We can override the default type of an integer, floating- point, or character literal
by supplying a suffix or prefix as listed in Table 2.2.
L'a'      // wide character literal, type is wchar_t
u8"hi!"   // utf-8 string literal (utf-8 encodes a Unicode character in 8 bits)
42ULL     // unsigned integer literal, type is unsigned long long
1E-3F     // single-precision floating-point literal, type is float
3.14159L  // extended-precision floating-point literal, type is long double

We can independently specify the signedness and size of an integral literal. If the -
suffix contains a U, then the literal has an unsigned type, so a decimal, octal, or -
hexadecimal literal with a U suffix has the smallest type of unsigned int, unsigned -
long, or unsigned long long in which the literal's value fits. If the suffix contains 
an L, then the literal's type will be at least long; if the suffix contains LL , then 
the literal's type will be either long long or unsigned long long. We can combine U -
with either L or LL. For example, a literal with a suffix of UL will be either unsig-
ned long or unsigned long long, depending on whether its value fits in unsigned long.


----> Escape Sequences
newline          \n   horizontal tab  \t    alert (bell)  \a
vertical tab     \v   backspace       \b    double quote  \"
backslash        \\   question mark   \?    single quote  \'
carriage return  \r   formfeed        \f

We use an escape sequence as if it were a single character

We can also write a generalized escape sequence, which is \x followed by  one or more 
hexadecimal digits or a \ followed by one, two, or three octal digits. The value rep-
resents the numerical value of the character. Some examples (assuming the Latin-1 ch-
aracter set):
\7 (bell)   \12 (newline)   \40 (blank)
\0 (null)   \115 ('M')      \x4d ('M')

Note that if a \ is followed by more than three octal digits, only the first three a-
re associated with the \. For example, "\1234" represents two characters: the charac-
ter represented by the octal value 123 and the character 4. In contrast, \x uses up -
all the hex digits following it; "\x1234" represents a single, 16-bit character comp-
osed from the bits corresponding to these four hexadecimal digits. Because most mach-
ines have 8-bit chars, such values are unlikely to be useful. 


-----------------------------------------------------------------------------------*/
