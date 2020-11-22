# Part Types and Operations

# Introducing Python Object Types  

As we’ll see, everything is an object in a Python script. Even simple numbers qualify, with values (e.g., 99), and supported operations (addition, subtraction, and so on).  

## The Python Conceptual Hierarchy  

From a more concrete perspective, Python programs can be decomposed into modules, statements, expressions, and objects, as follows:

1. Programs are composed of modules.

2. Modules contain statements.

3. Statements contain expressions.

4. Expressions create and process objects. 


## Why Use Built-in Types?  

- Built-in objects make programs easy to write.   
- Built-in objects are components of extensions.  
- Built-in objects are often more efficient than custom data structures.  
- Built-in objects are a standard part of the language.  

## Python’s Core Data Types  

Table 4-1. Built-in objects preview

| Object type                  | Example literals/creation                              |
| ---------------------------- | ------------------------------------------------------ |
| Numbers                      | 1234, 3.1415, 3+4j, 0b111, Decimal(), Fraction()       |
| Strings                      | 'spam', "Bob's", b'a\x01c', u'sp\xc4m'                 |
| Lists                        | [1, [2, 'three'], 4.5], list(range(10))                |
| Dictionaries                 | {'food': 'spam', 'taste': 'yum'}, dict(hours=10)       |
| Tuples                       | (1, 'spam', 4, 'U'), tuple('spam'), namedtuple         |
| Files                        | open('eggs.txt'), open(r'C:\ham.bin', 'wb')            |
| Sets                         | set('abc'), {'a', 'b', 'c'}                            |
| Other core types             | Booleans, types, None                                  |
| Program unit types           | Functions, modules, classes (Part IV, Part V, Part VI) |
| Implementation-related types | Comp                                                   |

Table 4-1 previews Python’s built-in object types and some of the syntax used to code their literals—that is, the expressions that generate these objects. In this book, the term literal simply means an expression whose syntax generates an object—sometimes also called a constant.  

We usually call the other object types in Table 4-1 core data types, though, because they are effectively built into the Python language—that is, there is specific expression syntax for generating most of them.   

## Numbers

```python
>>> 123 + 222 # Integer addition
345
>>> 1.5 * 4 # Floating-point multiplication
6.0
>>> 2 ** 100 # 2 to the power 100, again
1267650600228229401496703205376
```

You can, for instance, compute 2 to the power 1,000,000 as an integer in Python, but you probably shouldn’t try to print the result—with more than 300,000 digits, you may be waiting awhile!

```python
>>> len(str(2 ** 1000000)) # How many digits in a really BIG number?
301030
```

On Pythons prior to 2.7 and 3.1, once you start experimenting with floating-point numbers, you’re likely to stumble across something that may look a bit odd at first glance:  

```python
>>> 3.1415 * 2 # repr: as code (Pythons < 2.7 and 3.1)
6.2830000000000004
>>> print(3.1415 * 2) # str: user-friendly
6.283
```

The first result isn’t a bug; it’s a display issue. It turns out that there are two ways to print every object in Python—with full precision (as in the first result shown here), and in a user-friendly form (as in the second). Formally, the first form is known as an object’s as-code repr, and the second is its user-friendly str. 

Better yet, upgrade to Python 2.7 and the latest 3.X, where floating-point numbers display themselves more intelligently, usually with fewer extraneous digits

```python
>>> 3.1415 * 2 # repr: as code (Pythons >= 2.7 and 3.1)
6.283
```

## String

Strings are used to record both textual information (your name, for instance) as well as arbitrary collections of bytes (such as an image file’s contents). They are our first example of what in Python we call a sequence—a positionally ordered collection of other objects. Sequences maintain a left-to-right order among the items they contain: their items are stored and fetched by their relative positions. Strictly speaking, strings
are sequences of one-character strings; other, more general sequence types include lists and tuples, covered later.  

### Sequence Operations  

As sequences, strings support operations that assume a positional ordering among items. For example, if we have a four-character string coded inside quotes (usually of the single variety), we can verify its length with the built-in len function and fetch its components with indexing expressions:  

```python
>>> S = 'Spam' # Make a 4-character string, and assign it to a name
>>> len(S) # Length
4
>>> S[0] # The first item in S, indexing by zero-based position
'S'
>>> S[1] # The second item from the left
'p'
>>> S[-1] # The last item from the end in S
'm'
>>> S[-2] # The second-to-last item from the end
'a
>>> S[len(S)-1] # Negative indexing, the hard way
'm
```

Notice that we can use an arbitrary expression in the square brackets, not just a hardcoded number litera —anywhere that Python expects a value, we can use a literal, a variable, or any expression we wish. 

sequences also support a more general form of indexing known as slicing, which is a way to extract an entire section (slice) in a single step. 

```python
>>> S # A 4-character string
'Spam'
>>> S[1:3] # Slice of S from offsets 1 through 2 (not 3)
'pa'
>>> S[1:] # Everything past the first (1:len(S))
'pam'
>>> S # S itself hasn't changed
'Spam'
>>> S[0:3] # Everything but the last
'Spa'
>>> S[:3] # Same as S[0:3]
'Spa'
>>> S[:-1] # Everything but the last again, but simpler (0:-1)
'Spa'
>>> S[:] # All of S as a top-level copy (0:len(S))
'Spam'

>>> S
'Spam'
>>> S + 'xyz' # Concatenation
'Spamxyz'
>>> S # S is unchanged
'Spam'
>>> S * 8 # Repetition
'SpamSpamSpamSpamSpamSpamSpamSpam'
```

### Immutability  

strings are immutable in Python—they cannot be changed in place after they are created.   

```python
>>> S
'Spam'
>>> S[0] = 'z' # Immutable objects cannot be changed
...error text omitted...
TypeError: 'str' object does not support item assignment
>>> S = 'z' + S[1:] # But we can run expressions to make new objects
>>> S
'zpam'
```

### Type-Specific Methods

In addition to generic sequence operations, though, strings also have operations all their own, available as methods—functions that are attached to and act upon a specific object, which are triggered with a call expression.  

```python
>>> S = 'Spam'
>>> S.find('pa') # Find the offset of a substring in S
1
>>> S
'Spam'
>>> S.replace('pa', 'XYZ') # Replace occurrences of a string in S with another
'SXYZm'
>>> S
'Spam'
```

```python
>>> line = 'aaa,bbb,ccccc,dd'
>>> line.split(',') # Split on a delimiter into a list of substrings
['aaa', 'bbb', 'ccccc', 'dd']
>>> S = 'spam'
>>> S.upper() # Upper- and lowercase conversions
'SPAM'
>>> S.isalpha() # Content tests: isalpha, isdigit, etc.
True
>>> line = 'aaa,bbb,ccccc,dd\n'
>>> line.rstrip() # Remove whitespace characters on the right side
'aaa,bbb,ccccc,dd'
>>> line.rstrip().split(',') # Combine two operations
['aaa', 'bbb', 'ccccc', 'dd']

>>> '%s, eggs, and %s' % ('spam', 'SPAM!') # Formatting expression (all)
'spam, eggs, and SPAM!'
>>> '{0}, eggs, and {1}'.format('spam', 'SPAM!') # Formatting method (2.6+, 3.0+)
'spam, eggs, and SPAM!'
>>> '{}, eggs, and {}'.format('spam', 'SPAM!') # Numbers optional (2.7+, 3.1+)
'spam, eggs, and SPAM!'

>>> '{:,.2f}'.format(296999.2567) # Separators, decimal digits
'296,999.26'
>>> '%.2f | %+05d' % (3.14159, −42) # Digits, padding, signs
'3.14 | −0042'
```

### Getting Help  

For more details, you can always call the built-in dir function. This function lists variables assigned in the caller’s scope when called with no argument; more usefully, it returns a list of all the attributes available for any object passed to it.  

```python
>>> dir(S)
['__add__', '__class__', '__contains__', '__delattr__', '__dir__', '__doc__',
'__eq__', '__format__', '__ge__', '__getattribute__', '__getitem__',
'__getnewargs__', '__gt__', '__hash__', '__init__', '__iter__', '__le__',
'__len__', '__lt__', '__mod__', '__mul__', '__ne__', '__new__', '__reduce__',
'__reduce_ex__', '__repr__', '__rmod__', '__rmul__', '__setattr__', '__sizeof__',
'__str__', '__subclasshook__', 'capitalize', 'casefold', 'center', 'count',
'encode', 'endswith', 'expandtabs', 'find', 'format', 'format_map', 'index',
'isalnum', 'isalpha', 'isdecimal', 'isdigit', 'isidentifier', 'islower',
'isnumeric', 'isprintable', 'isspace', 'istitle', 'isupper', 'join', 'ljust',
'lower', 'lstrip', 'maketrans', 'partition', 'replace', 'rfind', 'rindex',
'rjust', 'rpartition', 'rsplit', 'rstrip', 'split', 'splitlines', 'startswith',
'strip', 'swapcase', 'title', 'translate', 'upper', 'zfill']
```

The dir function simply gives the methods’ names. To ask what they do, you can pass them to the help function:  

```python
>>> help(S.replace)
Help on built-in function replace:
replace(...)
S.replace(old, new[, count]) -> str
Return a copy of S with all occurrences of substring
old replaced by new. If the optional argument count is
given, only the first count occurrences are replaced.
```

### Other Ways to Code Strings  

Python also provides a variety of ways for us to code strings, which we’ll explore in greater depth later. For instance, special characters can be represented as backslash escape sequences, which Python displays in \xNN hexadecimal escape notation, unless they represent printable characters:  

```python
>>> S = 'A\nB\tC' # \n is end-of-line, \t is tab
>>> len(S) # Each stands for just one character
5
>>> ord('\n') # \n is a byte with the binary value 10 in ASCII
10
>>> S = 'A\0B\0C' # \0, a binary zero byte, does not terminate string
>>> len(S)
5
>>> S # Non-printables are displayed as \xNN hex escapes
'a\x00B\x00C'
```

### Unicode Strings  

In Python 3.X, the normal str string handles Unicode text (including ASCII, which is just a simple kind of Unicode); a distinct bytes string type represents raw byte values(including media and encoded text); and 2.X Unicode literals are supported in 3.3 and later for 2.X compatibility (they are treated the same as normal 3.X str strings):  

```python
>>> 'sp\xc4m' # 3.X: normal str strings are Unicode text
'spÄm'
>>> b'a\x01c' # bytes strings are byte-based data
b'a\x01c'
>>> u'sp\u00c4m' # The 2.X Unicode literal works in 3.3+: just str
'spÄm'
```

In Python 2.X, the normal str string handles both 8-bit character strings (including ASCII text) and raw byte values; a distinct unicode string type represents Unicode text; and 3.X bytes literals are supported in 2.6 and later for 3.X compatibility (they are treated the same as normal 2.X str strings):

```python
>>> print u'sp\xc4m' # 2.X: Unicode strings are a distinct type
spÄm
>>> 'a\x01c' # Normal str strings contain byte-based text/data
'a\x01c'
>>> b'a\x01c' # The 3.X bytes literal works in 2.6+: just str
'a\x01c'
```

Formally, in both 2.X and 3.X, non-Unicode strings are sequences of 8-bit bytes that print with ASCII characters when possible, and Unicode strings are sequences of ***Unicode code points***—identifying numbers for characters, which do not necessarily map to single bytes when encoded to files or stored in memory. In fact, the notion of bytes doesn’t apply to Unicode: some encodings include character code points too large for a byte, and even simple 7-bit ASCII text is not stored one byte per character under some encodings and memory storage schemes:

```python
>>> 'spam' # Characters may be 1, 2, or 4 bytes in memory
'spam'
>>> 'spam'.encode('utf8') # Encoded to 4 bytes in UTF-8 in files
b'spam'
>>> 'spam'.encode('utf16') # But encoded to 10 bytes in UTF-16
b'\xff\xfes\x00p\x00a\x00m\x00'
```

## Files

File objects are Python code’s main interface to external files on your computer. Rather, to create a file object, you call the built-in open function, passing in an external filename and an optional processing mode as strings.  

```python
>>> f = open('data.txt', 'w') # Make a new file in output mode ('w' is write)
>>> f.write('Hello\n') # Write strings of characters to it
6
>>> f.write('world\n') # Return number of items written in Python 3.X
6
>>> f.close() # Close to flush output buffers to disk
```

A file’s contents are always a string in your script, regardless of the type of data the file contains:

```python
>>> f = open('data.txt') # 'r' (read) is the default processing mode
>>> text = f.read() # Read entire file into a string
>>> text
'Hello\nworld\n'
>>> print(text) # print interprets control characters
Hello
world
>>> text.split() # File content is always a string
['Hello', 'world']
```

As we’ll see later, though, the best way to read a file today is to not read it at all—files provide an iterator that automatically reads line by line in for loops and other contexts:

```python
>>> for line in open('data.txt'): print(line)
```

### Binary Bytes Files

Python 3.X draws a sharp distinction between text and binary data in files: text files represent content as normal str strings and perform Unicode encoding and decoding automatically when writing and reading data, while binary files represent content as a special bytes string and allow you to access file content unaltered.  

For example, binary files are useful for processing media, accessing data created by C programs, and so on. To illustrate, Python’s struct module can both create and unpack packed binary data—raw bytes that record values that are not Python objects—to be written to a file in binary mode.   

```python
>>> import struct
>>> packed = struct.pack('>i4sh', 7, b'spam', 8) # Create packed binary data
>>> packed # 10 bytes, not objects or text
b'\x00\x00\x00\x07spam\x00\x08'
>>>
>>> file = open('data.bin', 'wb') # Open binary output file
>>> file.write(packed) # Write packed binary data
10
>>> file.close()
>>> data = open('data.bin', 'rb').read() # Open/read binary data file
>>> data # 10 bytes, unaltered
b'\x00\x00\x00\x07spam\x00\x08'
>>> data[4:8] # Slice bytes in the middle
b'spam'
>>> list(data) # A sequence of 8-bit bytes
[0, 0, 0, 7, 115, 112, 97, 109, 0, 8]
>>> struct.unpack('>i4sh', data) # Unpack into objects again
(7, b'spam', 8)
```

# Numeric Types

In Python, data takes the form of objects—either built-in objects that Python provides, or objects we create
using Python tools and other languages such as C. In fact, objects are the basis of every Python program you will ever write.

## Numeric Type Basics

In Python, numbers are not really a single object type, but a category of similar types. Python supports the usual numeric types (integers and floating points), as well as literals for creating numbers and expressions for processing them. In addition, Python provides more advanced numeric programming support and objects for more advanced work. A complete inventory of Python’s numeric toolbox includes:

- Integer and floating-point objects
- Complex number objects
- Decimal: fixed-precision objects
- Fraction: rational number objects
- Sets: collections with numeric operations
- Booleans: true and false
- Built-in functions and modules: round, math, random, etc.
- Expressions; unlimited integer precision; bitwise operations; hex, octal, and binary formats
- Third-party extensions: vectors, libraries, visualization, plotting, etc. 

### Numeric Literals

Table 5-1 shows what Python’s numeric types look like when written out in a program as literals or constructor function calls.  

Table 5-1. Numeric literals and constructors

| Literal                             | Interpretation                                |
| ----------------------------------- | --------------------------------------------- |
| 1234, -24, 0, 99999999999999        | Integers (unlimited size)                     |
| 1.23, 1., 3.14e-10, 4E210, 4.0e+210 | Floating-point numbers                        |
| 0o177, 0x9ff, 0b101010              | Octal, hex, and binary literals in 3.X        |
| 0177, 0o177, 0x9ff, 0b101010        | Octal, octal, hex, and binary literals in 2.X |
| 3+4j, 3.0+4.0j, 3J                  | Complex number literals                       |
| set('spam'), {1, 2, 3, 4}           | Sets: 2.X and 3.X construction forms          |
| Decimal('1.0'), Fraction(1, 3)      | Decimal and fraction extension types          |
| bool(X), True, False                | Boolean type and constants                    |

### Built-in Numeric Tools  

Python provides a set of tools for processing number objects:  

- Expression operators: +, -, *, /, >>, **, &, etc.
- Built-in mathematical functions: pow, abs, round, int, hex, bin, etc.
- Utility modules: random, math, etc.  

### Python Expression Operators 

## Numbers in Action

### Variables and Basic Expressions    

```python
% python
>>> a = 3 # Name created: not declared ahead of time
>>> b = 4
>>> a + 1, a − 1 # Addition (3 + 1), subtraction (3 − 1)
(4, 2)
>>> b * 3, b / 2 # Multiplication (4 * 3), division (4 / 2)
(12, 2.0)
>>> a % 2, b ** 2 # Modulus (remainder), power (4 ** 2)
(1, 16)
>>> 2 + 4.0, 2.0 ** b # Mixed-type conversions
(6.0, 16.0)
```

### Numeric Display Formats  

```python
>>> b / (2.0 + a) # Pythons <= 2.6: echoes give more (or fewer) digits
0.80000000000000004
>>> print(b / (2.0 + a)) # But print rounds off digits
0.8

# the following are all run in Python 3.3, and may vary slightly in older versions
>>> num = 1 / 3.0
>>> num # Auto-echoes
0.3333333333333333
>>> print(num) # Print explicitly
0.3333333333333333
>>> '%e' % num # String formatting expression
'3.333333e-01'
>>> '%4.2f' % num # Alternative floating-point format
'0.33'
>>> '{0:4.2f}'.format(num) # String formatting method: Python 2.6, 3.0, and later
'0.33'
```

### Comparisons: Normal and Chained

```python
>>> 1 < 2 # Less than
True
>>> 2.0 >= 1 # Greater than or equal: mixed-type 1 converted to 1.0
True
>>> 2.0 == 2.0 # Equal value
True
>>> 2.0 != 2.0 # Not equal value
False
```

Interestingly, Python also allows us to chain multiple comparisons together to perform range tests. Chained comparisons are a sort of shorthand for larger Boolean expressions. 

```python
>>> X = 2
>>> Y = 4
>>> Z = 6

>>> X < Y < Z # Chained comparisons: range tests
True
>>> X < Y and Y < Z
True

>>> X < Y > Z
False
>>> X < Y and Y > Z
False
>>> 1 < 2 < 3.0 < 4
True
>>> 1 > 2 > 3.0 > 4
False
```

```python
>>> 1.1 + 2.2 == 3.3 # Shouldn't this be True?...
False
>>> 1.1 + 2.2 # Close to 3.3, but not exactly: limited precision
3.3000000000000003
>>> int(1.1 + 2.2) == int(3.3) # OK if convert: see also round, floor, trunc ahead
True # Decimals and fractions (ahead) may help here too
```

This stems from the fact that floating-point numbers cannot represent some values exactly due to their limited number of bits—a fundamental issue in numeric programming not unique to Python, which we’ll learn more about later when we meet decimals and fractions, tools that can address such limitations.  

### Division: Classic, Floor, and True 

- X / Y: Classic and true division. In Python 2.X, this operator performs classic division, truncating results for integers, and keeping remainders (i.e., fractional parts) for floating-point numbers. In Python 3.X, it performs true division, always keeping remainders in floating-point results, regardless of types.
- X // Y: Floor division. Added in Python 2.2 and available in both Python 2.X and 3.X, this operator always truncates fractional remainders down to their floor, regardless of types. Its result type depends on the types of its operands.  

Here are the two operators at work in 3.X and 2.X—the first operation in each set is the crucial difference between the lines that may impact code: 

```python
C:\code> C:\Python33\python
>>>
>>> 10 / 4 # Differs in 3.X: keeps remainder
2.5
>>> 10 / 4.0 # Same in 3.X: keeps remainder
2.5
>>> 10 // 4 # Same in 3.X: truncates remainder
2
>>> 10 // 4.0 # Same in 3.X: truncates to floor
2.0

C:\code> C:\Python27\python
>>>
>>> 10 / 4 # This might break on porting to 3.X!
2
>>> 10 / 4.0
2.5
>>> 10 // 4 # Use this in 2.X if truncation needed
2
>>> 10 // 4.0
2.0
```

One subtlety: the // operator is informally called truncating division, but it’s more accurate to refer to it as floor division—it truncates the result down to its floor, which means the closest whole number below the true result. 

```python
>>> import math
>>> math.floor(2.5) # Closest number below value
2
>>> math.floor(-2.5)
-3
>>> math.trunc(2.5) # Truncate fractional part (toward zero)
2
>>> math.trunc(-2.5)
-2
```

```python
C:\code> c:\python33\python
>>> 5 / 2, 5 / −2
(2.5, −2.5)
>>> 5 // 2, 5 // −2 # Truncates to floor: rounds to first lower integer
(2, −3) # 2.5 becomes 2, −2.5 becomes −3
>>> 5 / 2.0, 5 / −2.0
(2.5, −2.5)
>>> 5 // 2.0, 5 // −2.0 # Ditto for floats, though result is float too
(2.0, −3.0)
```

The 2.X case is similar, but / results differ again:

```python
C:code> c:\python27\python
>>> 5 / 2, 5 / −2 # Differs in 3.X
(2, −3)
>>> 5 // 2, 5 // −2 # This and the rest are the same in 2.X and 3.X
(2, −3)
>>> 5 / 2.0, 5 / −2.0
(2.5, −2.5)
>>> 5 // 2.0, 5 // −2.0
(2.0, −3.0)
```

```python
C:\code> c:\python33\python
>>> import math
>>> 5 / −2 # Keep remainder
−2.5
>>> 5 // −2 # Floor below result
-3
>>> math.trunc(5 / −2) # Truncate instead of floor (same as int())
−2
C:\code> c:\python27\python
>>> import math
>>> 5 / float(−2) # Remainder in 2.X
−2.5
>>> 5 / −2, 5 // −2 # Floor in 2.X
(−3, −3)
>>> math.trunc(5 / float(−2)) # Truncate in 2.X
−2
```

As a wrap-up, if you are using 3.X, here is the short story on division operators for reference:  

```python
>>> (5 / 2), (5 / 2.0), (5 / −2.0), (5 / −2) # 3.X true division
(2.5, 2.5, −2.5, −2.5)
>>> (5 // 2), (5 // 2.0), (5 // −2.0), (5 // −2) # 3.X floor division
(2, 2.0, −3.0, −3)
>>> (9 / 3), (9.0 / 3), (9 // 3), (9 // 3.0) # Both
(3.0, 3.0, 3, 3.0)
```

For 2.X readers, division works as follows (the three bold outputs of integer division differ from 3.X):  

```python
>>> (5 / 2), (5 / 2.0), (5 / −2.0), (5 / −2) # 2.X classic division (differs)
(2, 2.5, −2.5, −3)
>>> (5 // 2), (5 // 2.0), (5 // −2.0), (5 // −2) # 2.X floor division (same)
(2, 2.0, −3.0, −3)
>>> (9 / 3), (9.0 / 3), (9 // 3), (9 // 3.0) # Both
(3, 3.0, 3, 3.0)
```

### Integer Precision

Python 3.X integers support unlimited size:  

```python
>>> 999999999999999999999999999999 + 1 # 3.X
1000000000000000000000000000000
```

Python 2.X has a separate type for long integers, but it automatically converts any number too large to store in a normal integer to this type. Hence, you don’t need to code any special syntax to use longs, and the only way you can tell that you’re using 2.X longs is that they print with a trailing “L”:

```python
>>> 999999999999999999999999999999 + 1 # 2.X
1000000000000000000000000000000L
```

### Complex Numbers

```python
>>> 1j * 1J
(-1+0j)
>>> 2 + 1j * 3
(2+3j)
>>> (2 + 1j) * 3
(6+3j)
```

### Hex, Octal, Binary: Literals and Conversions

Keep in mind that these literals are simply an alternative syntax for specifying the value of an integer object. For example, the following literals coded in Python 3.X or 2.X produce normal integers with the specified values in all three bases. In memory, an integer’s value is the same, regardless of the base we use to specify it:    

```python
>>> 0o1, 0o20, 0o377 # Octal literals: base 8, digits 0-7 (3.X, 2.6+)
(1, 16, 255)
>>> 0x01, 0x10, 0xFF # Hex literals: base 16, digits 0-9/A-F (3.X, 2.X)
(1, 16, 255)
>>> 0b1, 0b10000, 0b11111111 # Binary literals: base 2, digits 0-1 (3.X, 2.6+)
(1, 16, 255)
```

Python prints integer values in decimal (base 10) by default but provides built-in functions that allow you to convert integers to other bases’ digit strings  

```python
>>> oct(64), hex(64), bin(64) # Numbers=>digit strings
('0o100', '0x40', '0b1000000')
```

The oct function converts decimal to octal, hex to hexadecimal, and bin to binary. To go the other way, the built-in int function converts a string of digits to an integer, and an optional second argument lets you specify the numeric base

```python
>>> 64, 0o100, 0x40, 0b1000000 # Digits=>numbers in scripts and strings
(64, 64, 64, 64)
>>> int('64'), int('100', 8), int('40', 16), int('1000000', 2)
(64, 64, 64, 64)
>>> int('0x40', 16), int('0b1000000', 2) # Literal forms supported too
(64, 64)
```

The eval function, which you’ll meet later in this book, treats strings as though they were Python code. Therefore, it has a similar effect, but usually runs more slowly—it actually compiles and runs the string as a piece of a program, and it assumes the string being run comes from a trusted source

```python
>>> eval('64'), eval('0o100'), eval('0x40'), eval('0b1000000')
(64, 64, 64, 64)
```

Finally, you can also convert integers to base-specific strings with string formatting method calls and expressions, which return just digits, not Python literal strings:

```python
>>> '{0:o}, {1:x}, {2:b}'.format(64, 64, 64) # Numbers=>digits, 2.6+
'100, 40, 1000000'
>>> '%o, %x, %x, %X' % (64, 64, 255, 255) # Similar, in all Pythons
'100, 40, ff, FF'
```

### Bitwise Operations

```python
>>> x = 1 # 1 decimal is 0001 in bits
>>> x << 2 # Shift left 2 bits: 0100
4
>>> x | 2 # Bitwise OR (either bit=1): 0011
3
>>> x & 1 # Bitwise AND (both bits=1): 0001
1

>>> X = 0b0001 # Binary literals
>>> X << 2 # Shift left
4
>>> bin(X << 2) # Binary digits string
'0b100'
>>> bin(X | 0b010) # Bitwise OR: either
'0b11'
>>> bin(X & 0b1) # Bitwise AND: both
'0b1'

>>> X = 99
>>> bin(X), X.bit_length(), len(bin(X)) - 2
('0b1100011', 7, 7)
>>> bin(256), (256).bit_length(), len(bin(256)) - 2
('0b100000000', 9, 9)
```

### Other Built-in Numeric Tools

```python
>>> import math
>>> math.pi, math.e # Common constants
(3.141592653589793, 2.718281828459045)
>>> math.sin(2 * math.pi / 180) # Sine, tangent, cosine
0.03489949670250097
>>> math.sqrt(144), math.sqrt(2) # Square root
(12.0, 1.4142135623730951)
>>> pow(2, 4), 2 ** 4, 2.0 ** 4.0 # Exponentiation (power)
(16, 16, 16.0)
>>> abs(-42.0), sum((1, 2, 3, 4)) # Absolute value, summation
(42.0, 10)
>>> min(3, 1, 2, 4), max(3, 1, 2, 4) # Minimum, maximum
(1, 4)

>>> math.floor(2.567), math.floor(-2.567) # Floor (next-lower integer)
(2, −3)
>>> math.trunc(2.567), math.trunc(−2.567) # Truncate (drop decimal digits)
(2, −2)
>>> int(2.567), int(−2.567) # Truncate (integer conversion)
(2, −2)
>>> round(2.567), round(2.467), round(2.567, 2) # Round (Python 3.X version)

(3, 2, 2.57)
>>> '%.1f' % 2.567, '{0:.2f}'.format(2.567) # Round for display (Chapter 7)
('2.6', '2.57')

>>> (1 / 3.0), round(1 / 3.0, 2), ('%.2f' % (1 / 3.0))
(0.3333333333333333, 0.33, '0.33')
```

there are three ways to compute square roots in Python: using a module function, an expression, or a built-in function

```python
>>> import math
>>> math.sqrt(144) # Module
12.0
>>> 144 ** .5 # Expression
12.0
>>> pow(144, .5) # Built-in
12.0
>>> math.sqrt(1234567890) # Larger numbers
35136.41828644462
>>> 1234567890 ** .5
35136.41828644462
>>> pow(1234567890, .5)
35136.41828644462
```

```python
>>> import random
>>> random.random()
0.5566014960423105
>>> random.random() # Random floats, integers, choices, shuffles
0.051308506597373515
>>> random.randint(1, 10)
5
>>> random.randint(1, 10)
9

>>> random.choice(['Life of Brian', 'Holy Grail', 'Meaning of Life'])
'Holy Grail'
>>> random.choice(['Life of Brian', 'Holy Grail', 'Meaning of Life'])
'Life of Brian'
>>> suits = ['hearts', 'clubs', 'diamonds', 'spades']
>>> random.shuffle(suits)
>>> suits
['spades', 'hearts', 'diamonds', 'clubs']
>>> random.shuffle(suits)
>>> suits
['clubs', 'diamonds', 'hearts', 'spades']
```

## Other Numeric Types  

### Decimal Type

Functionally, decimals are like floating-point numbers, but they have a fixed number of decimal points. Hence, decimals are fixed-precision floating-point values. For example, with decimals, we can have a floating-point value that always retains just two decimal digits. 

```python
from decimal import Decimal
>>> Decimal('0.1') + Decimal('0.1') + Decimal('0.1') - Decimal('0.3')
Decimal('0.0')
>>> Decimal(0.1) + Decimal(0.1) + Decimal(0.1) - Decimal(0.3)
Decimal('2.775557561565156540423631668E-17')
>>> 0.1 + 0.1 + 0.1 - 0.3
5.551115123125783e-17
```

Other tools in the decimal module can be used to set the precision of all decimal numbers, arrange error handling, and more.  The precision is applied globally for all decimals created in the calling thread:   

```python
>>> import decimal
>>> decimal.Decimal(1) / decimal.Decimal(7) # Default: 28 digits
Decimal('0.1428571428571428571428571429')
>>> decimal.getcontext().prec = 4 # Fixed precision
>>> decimal.Decimal(1) / decimal.Decimal(7)
Decimal('0.1429')
>>> Decimal(0.1) + Decimal(0.1) + Decimal(0.1) - Decimal(0.3) # Closer to 0
Decimal('1.110E-17')

C:\code> C:\Python33\python
>>> import decimal
>>> decimal.Decimal('1.00') / decimal.Decimal('3.00')
Decimal('0.3333333333333333333333333333')
>>>
>>> with decimal.localcontext() as ctx:
... ctx.prec = 2
... decimal.Decimal('1.00') / decimal.Decimal('3.00')
...
Decimal('0.33')
>>>
>>> decimal.Decimal('1.00') / decimal.Decimal('3.00')
Decimal('0.3333333333333333333333333333')
```

### Fraction Type   

### Sets 

Besides decimals, Python 2.4 also introduced a new collection type, the set—an unordered collection of unique and immutable objects that supports operations corresponding to mathematical set theory.   

#### Set basics in Python 2.6 and earlier

To make a set object, pass in a sequence or other iterable object to the built-in set function:   

```python
>>> x = set('abcde')
>>> y = set('bdxyz')
```

notice that sets do not have a positional ordering, and so are not sequences—their order is arbitrary and may vary per Python release.

```python
>>> x
set(['a', 'c', 'b', 'e', 'd']) # Pythons <= 2.6 display format
```

```python
>>> x − y # Difference
set(['a', 'c', 'e'])
>>> x | y # Union
set(['a', 'c', 'b', 'e', 'd', 'y', 'x', 'z'])
>>> x & y # Intersection
set(['b', 'd'])
>>> x ^ y # Symmetric difference (XOR)
set(['a', 'c', 'e', 'y', 'x', 'z'])
>>> x > y, x < y # Superset, subset
(False, False)

>>> 'e' in x # Membership (sets)
True
>>> 'e' in 'Camelot', 22 in [11, 22, 33] # But works on other types too
(True, True)

>>> z = x.intersection(y) # Same as x & y
>>> z
set(['b', 'd'])
>>> z.add('SPAM') # Insert one item
>>> z
set(['b', 'd', 'SPAM'])
>>> z.update(set(['X', 'Y'])) # Merge: in-place union
>>> z
set(['Y', 'X', 'b', 'd', 'SPAM'])
>>> z.remove('b') # Delete one item
>>> z
set(['Y', 'X', 'd', 'SPAM'])

>>> for item in set('abc'): print(item * 3)
aaa
ccc
bbb

>>> S = set([1, 2, 3])
>>> S | set([3, 4]) # Expressions require both to be sets
set([1, 2, 3, 4])
>>> S | [3, 4]
TypeError: unsupported operand type(s) for |: 'set' and 'list'
>>> S.union([3, 4]) # But their methods allow any iterable
set([1, 2, 3, 4])
>>> S.intersection((1, 3, 5))
set([1, 3])
>>> S.issubset(range(-5, 5))
True
```

#### Set literals in Python 3.X and 2.7 

In 3.X and 2.7, the following are equivalent:  

```python
set([1, 2, 3, 4]) # Built-in call (all)
{1, 2, 3, 4} # Newer set literals (2.7, 3.X)
```

This syntax makes sense, given that sets are essentially like valueless dictionaries—because a set’s items are unordered, unique, and immutable, the items behave much like a dictionary’s keys. 

Here’s what sets look like in 3.X; it’s the same in 2.7, except that set results display with 2.X’s set([...]) notation, and item order may vary per version (which by definition is irrelevant in sets anyhow):

```python
C:\code> c:\python33\python
>>> set([1, 2, 3, 4]) # Built-in: same as in 2.6
{1, 2, 3, 4}
>>> set('spam') # Add all items in an iterable
{'s', 'a', 'p', 'm'}
>>> {1, 2, 3, 4} # Set literals: new in 3.X (and 2.7)
{1, 2, 3, 4}
>>> S = {'s', 'p', 'a', 'm'}
>>> S
{'s', 'a', 'p', 'm'}
>>> S.add('alot') # Methods work as before
>>> S
{'s', 'a', 'p', 'alot', 'm'}
```

All the set processing operations discussed in the prior section work the same in 3.X, but the result sets print differently:

```python
>>> S1 = {1, 2, 3, 4}
>>> S1 & {1, 3} # Intersection
{1, 3}
>>> {1, 5, 3, 6} | S1 # Union
{1, 2, 3, 4, 5, 6}
>>> S1 - {1, 3, 4} # Difference
{2}
>>> S1 > {1, 3} # Superset
True
```

Note that {} is still a dictionary in all Pythons. Empty sets must be created with the set built-in, and print the same way:

```python
>>> S1 - {1, 2, 3, 4} # Empty sets print differently
set()
>>> type({}) # Because {} is an empty dictionary
<class 'dict'>
>>> S = set() # Initialize an empty set
>>> S.add(1.23)
>>> S
{1.23}
```

As in Python 2.6 and earlier, sets created with 3.X/2.7 literals support the same methods, some of which allow general iterable operands that expressions do not:

```python
>>> {1, 2, 3} | {3, 4}
{1, 2, 3, 4}
>>> {1, 2, 3} | [3, 4]
TypeError: unsupported operand type(s) for |: 'set' and 'list'
>>> {1, 2, 3}.union([3, 4])
{1, 2, 3, 4}
>>> {1, 2, 3}.union({3, 4})
{1, 2, 3, 4}
>>> {1, 2, 3}.union(set([3, 4]))
{1, 2, 3, 4}
>>> {1, 2, 3}.intersection((1, 3, 5))
{1, 3}
>>> {1, 2, 3}.issubset(range(-5, 5))
True
```

#### Immutable constraints and frozen sets

Sets are powerful and flexible objects, but they do have one constraint in both 3.X and 2.X that you should keep in mind—largely because of their implementation, sets can only contain immutable (a.k.a. “hashable”) object types. Hence, lists and dictionaries cannot be embedded in sets, but tuples can if you need to store compound values. Tuples compare by their full values when used in set operations:

```python
>>> S
{1.23}
>>> S.add([1, 2, 3]) # Only immutable objects work in a set
TypeError: unhashable type: 'list'
>>> S.add({'a':1})
TypeError: unhashable type: 'dict'
>>> S.add((1, 2, 3))
>>> S # No list or dict, but tuple OK
{1.23, (1, 2, 3)}
>>> S | {(4, 5, 6), (1, 2, 3)} # Union: same as S.union(...)
{1.23, (4, 5, 6), (1, 2, 3)}
>>> (1, 2, 3) in S # Membership: by complete values
True
>>> (1, 4, 3) in S
False
```

Sets themselves are mutable too, and so cannot be nested in other sets directly; if you need to store a set inside another set, the frozenset built-in call works just like set but creates an immutable set that cannot change and thus can be embedded in other sets.

#### Set comprehensions in Python 3.X and 2.7

Here is a set comprehension in 3.3 (again, result display and order differs in 2.7):

```python
>>> {x ** 2 for x in [1, 2, 3, 4]} # 3.X/2.7 set comprehension
{16, 1, 4, 9}
```

As for list comprehensions, we get back pretty much what this expression says: “Give me a new set containing X squared, for every X in a list.” Comprehensions can also iterate across other kinds of objects, such as strings (the first of the following examples illustrates the comprehension-based way to make a set from an existing iterable):

```python
>>> {x for x in 'spam'} # Same as: set('spam')
{'m', 's', 'p', 'a'}
>>> {c * 4 for c in 'spam'} # Set of collected expression results
{'pppp', 'aaaa', 'ssss', 'mmmm'}
>>> {c * 4 for c in 'spamham'}
{'pppp', 'aaaa', 'hhhh', 'ssss', 'mmmm'}
>>> S = {c * 4 for c in 'spam'}
>>> S | {'mmmm', 'xxxx'}
{'pppp', 'xxxx', 'mmmm', 'aaaa', 'ssss'}
>>> S & {'mmmm', 'xxxx'}
{'mmmm'}
```

#### Why sets?

```python
>>> L = [1, 2, 1, 3, 2, 4, 5]
>>> set(L)
{1, 2, 3, 4, 5}
>>> L = list(set(L)) # Remove duplicates
>>> L
[1, 2, 3, 4, 5]
>>> list(set(['yy', 'cc', 'aa', 'xx', 'dd', 'aa'])) # But order may change
['cc', 'xx', 'yy', 'dd', 'aa']
```

```python
>>> L1, L2 = [1, 3, 5, 2, 4], [2, 5, 3, 4, 1]
>>> L1 == L2 # Order matters in sequences
False
>>> set(L1) == set(L2) # Order-neutral equality
True
>>> sorted(L1) == sorted(L2) # Similar but results ordered
True
>>> 'spam' == 'asmp', set('spam') == set('asmp'), sorted('spam') == sorted('asmp')
(False, True, True)
```

### Booleans

Python today has an explicit Boolean data type called bool, with the values True and False available as preassigned built-in names. Internally, the names True and False are instances of bool, which is in turn just a subclass (in the objectoriented sense) of the built-in integer type int. True and False behave exactly like the integers 1 and 0, except that they have customized printing logic—they print themselves as the words True and False, instead of the digits 1 and 0. bool accomplishes this by redefining str and repr string formats for its two objects.

Because True is just the integer 1 with a custom display format, True + 4 yields integer 5 in Python!  

```python
>>> type(True)
<class 'bool'>
>>> isinstance(True, int)
True
>>> True == 1 # Same value
True
>>> True is 1 # But a different object: see the next chapter
False
>>> True or False # Same as: 1 or 0
True
>>> True + 4 # (Hmmm)
5
```



# The Dynamic Typing Interlude  

## The Case of the Missing Declaration Statements 

In Python, types are determined automatically at runtime, not in response to declarations in your code. This means that you never declare variables ahead of time (a concept that is perhaps simpler to grasp if you keep in mind that it all boils down to variables, objects, and the links between them).

### Variables, Objects, and References

```python
a = 3
```

- Variable creation. A variable (i.e., name), like @a, is created when your code first assigns it a value.
- Variable types. A variable never has any type information or constraints associated with it. The notion of type lives with objects, not names.
- Variable use. When a variable appears in an expression, it is immediately replaced with the object that it currently refers to, whatever that may be.

In sum, variables are created when assigned, can reference any type of object, and must be assigned before they are referenced.

For example, when we say this to assign a variable a value:

```python
a = 3 # Assign a name to an object
```

at least conceptually, Python will perform three distinct steps to carry out the request. These steps reflect the operation of all assignments in the Python language:

1. Create an object to represent the value 3.
2. Create the variable a, if it does not yet exist.
3. Link the variable a to the new object 3.

As sketched, variables and objects are stored in different parts of memory and are associated by links
(the link is shown as a pointer in the figure). Variables always link to objects and never to other variables, but larger objects may link to other objects (for instance, a list object has links to the objects it contains).

These links from variables to objects are called references in Python—that is, a reference is a kind of association, implemented as a pointer in memory. Whenever the variables are later used (i.e., referenced), Python automatically follows the variable-to-object links. This is all simpler than the terminology may imply. In concrete terms:

- Variables are entries in a system table, with spaces for links to objects.
- Objects are pieces of allocated memory, with enough space to represent the values for which they stand.
- References are automatically followed pointers from variables to objects.

At least conceptually, each time you generate a new value in your script by running an expression, Python creates a new object (i.e., a chunk of memory) to represent that value. Technically speaking, objects have more structure than just enough space to represent their values. Each object also has two standard header fields: a type designator used to mark the type of the object, and a reference counter used to determine when it’s OK to reclaim the object.

### Types Live with Objects, Not Variables  

```python
>>> a = 3 # It's an integer
>>> a = 'spam' # Now it's a string
>>> a = 1.23 # Now it's a floating point
```

@a starts out as an integer, then becomes a string, and finally becomes a floating-point number. However, that’s not really what’s happening. In Python, things work more simply. Names have no types; as stated earlier, types live with objects, not names. In the preceding listing, we’ve simply changed @a to reference different objects. 

Objects, on the other hand, know what type they are—each object contains a header field that tags the object with its type. The integer object 3, for example, will contain the value 3, plus a designator that tells Python that the object is an integer (strictly speaking, a pointer to an object called int, the name of the integer type). The type designator of the 'spam' string object points to the string type (called str) instead. Because objects know their types, variables don’t have to.

### Objects Are Garbage-Collected

after the following statements, what happens to the object 3?

```python
>>> a = 3
>>> a = 'spam'
```

The answer is that in Python, whenever a name is assigned to a new object, the space held by the prior object is reclaimed if it is not referenced by any other name or object. This automatic reclamation of objects’ space is known as garbage collection.

## Shared References

Now let’s introduce another variable into our interaction and watch what happens to its names and objects:

```python
>>> a = 3
>>> b = a  
```

The second command causes Python to create the variable @b; the variable @a is being used and not assigned here, so it is replaced with the object it references (3), and @b is made to reference that object. The net effect is that the variables @a and @b wind up referencing the same object (that is, pointing to the same chunk of memory). This scenario in Python—with multiple names referencing the same object—is usually called a shared reference (and sometimes just a shared object).   

### Shared References and In-Place Changes

As you’ll see later in this part’s chapters, there are objects and operations that perform in-place object changes—Python’s mutable types, including lists, dictionaries, and sets. For instance, an assignment to an offset in a list actually changes the list object itself in place, rather than generating a brand-new list object.  

```python
>>> L1 = [2, 3, 4] # A mutable object
>>> L2 = L1 # Make a reference to the same object
>>> L1[0] = 24 # An in-place change
>>> L1 # L1 is different
[24, 3, 4]
>>> L2 # But so is L2!
[24, 3, 4]
```

### Shared References and Equality

```python
>>> L = [1, 2, 3]
>>> M = L # M and L reference the same object
>>> L == M # Same values
True
>>> L is M # Same objects
True

>>> L = [1, 2, 3]
>>> M = [1, 2, 3] # M and L reference different objects
>>> L == M # Same values
True
>>> L is M # Different objects
False
```

The first technique here, the == operator, tests whether the two referenced objects have the same values; this is the method almost always used for equality checks in Python. The second method, the is operator, instead tests for object identity—it returns True only if both names point to the exact same object.

```python
>>> X = 42
>>> Y = 42 # Should be two different objects
>>> X == Y
True
>>> X is Y # Same object anyhow: caching at work!
True
```

In this interaction, X and Y should be == (same value), but not is (same object) because we ran two different literal expressions (42). Because small integers and strings are cached and reused, though, is tells us they reference the same single object.

```python
>>> import sys
>>> sys.getrefcount(1) # 647 pointers to this shared piece of memory
647
```

## Dynamic Typing Is Everywhere  

###  

# String Fundamentals

Python string—an ordered collection of characters used to store and represent text- and bytes-based information.   

## This Chapter’s Scope

- In Python 3.X there are three string types: str is used for Unicode text (including ASCII), bytes is used for binary data (including encoded text), and bytearray is a mutable variant of bytes. Files work in two modes: text, which represents content as str and implements Unicode encodings, and binary, which deals in raw bytes and does no data translation.  
- In Python 2.X, unicode strings represent Unicode text, str strings handle both 8-bit text and binary data, and bytearray is available in 2.6 and later as a back-port from 3.X. Normal files’ content is simply bytes represented as str, but a codecs module opens Unicode text files, handles encodings, and represents content as unicode objects  

Despite such version differences, if and when you do need to care about Unicode you’ll find that it is a relatively minor extension—once text is in memory, it’s a Python string of characters that supports all the basics we’ll study in this chapter. In fact, the primary distinction of Unicode often lies in the translation (a.k.a. encoding) step required to move it to and from files. Beyond that, it’s largely just string processing.  

For this chapter, we’ll focus on the basic string type and its operations. As you’ll find, the techniques we’ll study here also apply directly to the more advanced string types in Python’s toolset.  

## String Basics

  

### String Literals  

- Single quotes: 'spa"m'
- Double quotes: "spa'm"
- Triple quotes: '''... spam ...''', """... spam ..."""
- Escape sequences: "s\tp\na\0m"
- Raw strings: r"C:\new\test.spm"
- Bytes literals in 3.X and 2.6+ : b'sp\x01am'
- Unicode literals in 2.X and 3.3+: u'eggs\u0020spam'  

#### Single- and Double-Quoted Strings Are the Same. 

That is, string literals can be written enclosed in either two single or two double quotes--the two forms work the same and return the same type of object. For example, the following two strings are identical, once coded:  

```python
>>> 'shrubbery', "shrubbery"
('shrubbery', 'shrubbery')

# Adding commas between these strings would result in a tuple, not a string.
>>> 'knight"s', "knight's" 
('knight"s', "knight's")

>>> title = "Meaning " 'of' " Life" # Implicit concatenation
>>> title
'Meaning of Life'
```

The reason for supporting both is that it allows you to embed a quote character of the other variety inside a string without escaping it with a backslash. You may embed a single-quote character in a string enclosed in double-quote characters, and vice versa.

Note that the comma is important here. Without it, Python automatically concatenates adjacent string literals in any expression, although it is almost as simple to add a + operator between them to invoke concatenation explicitly.

#### Escape Sequences Represent Special Characters

This is representative of a general pattern in strings: backslashes are used to introduce special character codings known as escape sequences. Escape sequences let us embed characters in strings that cannot easily be typed on a keyboard. The character \, and one or more characters following it in the string literal,
are replaced with a single character in the resulting string object, which has the binary value specified by the escape sequence. For example, here is a five-character string that embeds a newline and a tab:  

```python
#The two characters \n stand for a single character—the binary value of the newline character in your character set (in ASCII, character code 10). Similarly, the sequence \t is replaced with the tab character.  
>>> s = 'a\nb\tc'
>>> s
'a\nb\tc'

>>> print(s)
a
b c

#the built-in len function—it returns the actual number of characters in a string, regardless of how it is coded or displayed:
>>> len(s)
5

#Some escape sequences allow you to embed absolute binary values into the characters of a string. For instance, here’s a five-character string that embeds two characters with binary zero values (coded as octal escapes of one digit):
>>> s = 'a\0b\0c'
>>> s
'a\x00b\x00c'
>>> len(s)
5
```

In Python, a zero (null) character like this does not terminate a string the way a “null byte” typically does in C. Instead, Python keeps both the string’s length and text in memory. In fact, no character terminates a string in Python. Here’s a string that is all absolute binary escape codes--a binary 1 and 2 (coded in octal), followed by a binary 3 (coded in hexadecimal):   

```python
>>> s = '\001\002\x03'
>>> s
'\x01\x02\x03'
>>> len(s)
3

>>> x = "C:\py\code" # Keeps \ literally (and displays it as \\)
>>> x
'C:\\py\\code'
>>> len(x)
10
```

Notice that Python displays nonprintable characters in hex, regardless of how they were specified.  if Python does not recognize the character after a \ as being a valid escape code, it simply keeps the backslash in the resulting string.

#### Raw Strings Suppress Escapes

```python
myfile = open('C:\new\text.dat', 'w')
```

thinking that they will open a file called text.dat in the directory C:\new. The problem here is that \n is taken to stand for a newline character, and \t is replaced with a tab. In effect, the call tries to open a file named C:(newline)ew(tab)ext.dat, with usually lessthan-stellar results.  

If the letter r (uppercase or lowercase) appears just before the opening quote of a string, it turns off the escape mechanism.  Therefore, to fix the filename problem, just remember to add the letter r on Windows:

```python
myfile = open(r'C:\new\text.dat', 'w')
```

Alternatively, because two backslashes are really an escape sequence for one backslash, you can keep your backslashes by simply doubling them up:

```python
myfile = open('C:\\new\\text.dat', 'w')  
```

In fact, Python itself sometimes uses this doubling scheme when it prints strings with embedded backslashes:  

```python
>>> path = r'C:\new\text.dat'
>>> path # Show as Python code
'C:\\new\\text.dat'
>>> print(path) # User-friendly format
C:\new\text.dat
>>> len(path) # String length
15
```

#### Triple Quotes Code Multiline Block Strings 

Python also has a triple-quoted string literal format, sometimes called a block string, that is a syntactic convenience for coding multiline text data. This form begins with three quotes (of either the single or double variety), is followed by any number of lines of text, and is closed with the same triple-quote sequence that opened it.   

```python
>>> mantra = """Always look
... on the bright
... side of life."""
>>>
>>> mantra
'Always look\n on the bright\nside of life.'

>>> print(mantra)
Always look
on the bright
side of life.
```

In fact, triple-quoted strings will retain all the enclosed text, including any to the right of your code that you might intend as comments.  

```python
>>> menu = """spam # comments here added to string!
... eggs # ditto
... """
>>> menu
'spam # comments here added to string!\neggs # ditto\n'
>>> menu = (
... "spam\n" # comments here ignored
... "eggs\n" # but newlines not automatic
... )
>>> menu
'spam\neggs\n'
```

Triple-quoted strings are also commonly used for documentation strings, which are string literals that are taken as comments when they appear at specific points in your file (more on these later in the book).   

If you wish to turn off a few lines of code and run your script again, simply put three quotes above
and below them, like this:

```python
X = 1
"""
import os # Disable this code temporarily
print(os.getcwd())
"""
Y = 2  
```

## Strings in Action  

### Basic Operations 

```python
% python
>>> len('abc') # Length: number of items
3
>>> 'abc' + 'def' # Concatenation: a new string
'abcdef'
>>> 'Ni!' * 4 # Repetition: like "Ni!" + "Ni!" + ...
'Ni!Ni!Ni!Ni!'

>>> print('------- ...more... ---') # 80 dashes, the hard way
>>> print('-' * 80) # 80 dashes, the easy way

>>> myjob = "hacker"
>>> for c in myjob: print(c, end=' ') # Step through items, print each (3.X form)
...
h a c k e r
>>> "k" in myjob # Found
True
>>> "z" in myjob # Not found
False
>>> 'spam' in 'abcspamdef' # Substring search, no position returned
True
```

### Indexing and Slicing 

Because strings are defined as ordered collections of characters, we can access their components by position. Offsets and slices: positive offsets start from the left end (offset 0 is the first item), and negatives count back from the right end (offset -1 is the last item). Either kind of offset can be used to give positions in indexing and slicing operations.  

```python
>>> S = 'spam'
>>> S[0], S[−2] # Indexing from front or end
('s', 'a')
>>> S[1:3], S[1:], S[:−1] # Slicing: extract a section
('pa', 'pam', 'spa')
```

Here’s a summary of the details for reference:  

Indexing (S[i]) fetches components at offsets:

- The first item is at offset 0.
- Negative indexes mean to count backward from the end or right.
- S[0] fetches the first item.
- S[-2] fetches the second item from the end (like S[len(S)-2]).

Slicing (S[i:j]) extracts contiguous sections of sequences:  

- The upper bound is noninclusive.
- Slice boundaries default to 0 and the sequence length, if omitted.
- S[1:3] fetches items at offsets 1 up to but not including 3.
- S[1:] fetches items at offset 1 through the end (the sequence length).
- S[:3] fetches items at offset 0 up to but not including 3.
- S[:-1] fetches items at offset 0 up to but not including the last item.
- S[:] fetches items at offsets 0 through the end—making a top-level copy of S.    

Extended slicing (S[i:j:k]) accepts a step (or stride) k, which defaults to +1:

- Allows for skipping items and reversing order—see the next section.  

```python
>>> S = 'abcdefghijklmnop'
>>> S[1:10:2] # Skipping items
'bdfhj'
>>> S[::2]
'acegikmo'

>>> S = 'hello'
>>> S[::−1] # Reversing items
'olleh'
```

"hello"[::−1] returns the new string "olleh"—the first two bounds default to 0 and the length of the sequence, as before, and a stride of −1 indicates that the slice should go from right to left instead of the usual left to right. The effect, therefore, is to reverse the sequence.

With a negative stride, the meanings of the first two bounds are essentially reversed. That is, the slice S[5:1:−1] fetches the items from 2 to 5, in reverse order (the result contains items from offsets 5, 4, 3, and 2):

```python
>>> S = 'abcedfg'
>>> S[5:1:−1] # Bounds roles differ
'fdec'
```

### String Conversion Tools

```python
>>> int("42"), str(42) # Convert from/to string
(42, '42')
>>> repr(42) # Convert to as-code string
'42'
```

The repr function also converts an object to its string representation, but returns the object as a string of code that can be rerun to recreate the object.

For strings, the result has quotes around it if displayed with a print statement, which differs in form between Python lines:

```python
>>> print(str('spam'), repr('spam')) # 2.X: print str('spam'), repr('spam')
spam 'spam'
>>> str('spam'), repr('spam') # Raw interactive echo displays
('spam', "'spam'")
```

@ord function—this returns the actual binary value used to represent the corresponding character in memory. The @chr function performs the inverse operation, taking an integer code and converting it to the corresponding character:

```python
>>> ord('s')
115
>>> chr(115)
's'

>>> int('1101', 2) # Convert binary to integer: built-in
13
>>> bin(13) # Convert integer to binary: built-in
'0b1101'
```

## String Methods 

### str.strip([chars])

Return a copy of the string with the leading and trailing characters removed. The *chars* argument is a string specifying the set of characters to be removed. If omitted or `None`, the *chars* argument defaults to removing whitespace. The *chars* argument is not a prefix or suffix; rather, all combinations of its values are stripped:

```python
>>> '   spacious   '.strip()
'spacious'
>>> 'www.example.com'.strip('cmowz.')
'example'
```

The outermost leading and trailing *chars* argument values are stripped from the string. Characters are removed from the leading end until reaching a string character that is not contained in the set of characters in *chars*. A similar action takes place on the trailing end. For example:

```python
>>> comment_string = '#....... Section 3.2.1 Issue #32 .......'
>>> comment_string.strip('.#! ')
'Section 3.2.1 Issue #32'
```



## String Formatting Expressions

Python also provides a more advanced way to combine string processing tasks—string formatting allows us to perform multiple type-specific substitutions on a string in a single step.  

- String formatting expressions: '...%s...' % (values)  
- String formatting method calls: '...{}...'.format(values)  

### Formatting Expression Basics

To format strings:  

- On the left of the % operator, provide a format string containing one or more embedded conversion targets, each of which starts with a % (e.g., %d).  
- On the right of the % operator, provide the object (or objects, embedded in a tuple) that you want Python to insert into the format string on the left in place of the conversion target (or targets).  

```python
>>> 'That is %d %s bird!' % (1, 'dead') # Format expression
That is 1 dead bird!
>>> exclamation = 'Ni'
>>> 'The knights who say %s!' % exclamation # String substitution
'The knights who say Ni!'
>>> '%d %s %g you' % (1, 'spam', 4.0) # Type-specific substitutions
'1 spam 4 you'
>>> '%s -- %s -- %s' % (42, 3.14159, [1, 2, 3]) # All types match a %s target
'42 -- 3.14159 -- [1, 2, 3]'
```

Note that when you’re inserting more than one value, you need to group the values on the right in parentheses (i.e., put them in a tuple).

### Advanced Formatting Expression Syntax

Some of the format codes in the table provide alternative ways to format the same type; for instance, %e, %f, and %g provide alternative ways to format floating-point numbers.  

| Code                                                         | Meaning |
| ------------------------------------------------------------ | ------- |
| s String (or any object’s str(X) string)<br/>r Same as s, but uses repr, not str<br/>c Character (int or str)<br/>d Decimal (base-10 integer)<br/>i Integer<br/>u Same as d (obsolete: no longer unsigned)<br/>o Octal integer (base 8)<br/>x Hex integer (base 16)<br/>X Same as x, but with uppercase letters<br/>e Floating point with exponent, lowercase<br/>E Same as e, but uses uppercase letters<br/>f Floating-point decimal<br/>F Same as f, but uses uppercase letters<br/>g Floating-point e or f<br/>G Floating-point E or F<br/>% Literal % (coded as %%) |         |

The general structure of conversion targets looks like this:

```python
%[(keyname)][flags][width][.precision]typecode 
```

The type code characters in the first column of Table 7-4 show up at the end of this target string’s format. Between the % and the type code character, you can do any of the following:

- Provide a key name for indexing the dictionary used on the right side of the expression
- List flags that specify things like left justification (-), numeric sign (+), a blank before positive numbers and a – for negatives (a space), and zero fills (0)
- Give a total minimum field width for the substituted text
- Set the number of digits (precision) to display after a decimal point for floatingpoint numbers  

### Advanced Formatting Expression Examples  

```python
>>> x = 1234
>>> res = 'integers: ...%d...%−6d...%06d' % (x, x, x)
>>> res
'integers: ...1234...1234 ...001234'

>>> x = 1.23456789
>>> x # Shows more digits before 2.7 and 3.1
1.23456789
>>> '%e | %f | %g' % (x, x, x)
'1.234568e+00 | 1.234568 | 1.23457'
>>> '%E' % x
'1.234568E+00'

>>> '%−6.2f | %05.2f | %+06.1f' % (x, x, x)
'1.23 | 01.23 | +001.2'
>>> '%s' % x, str(x)
('1.23456789', '1.23456789')
```

When sizes are not known until runtime, you can use a computed width and precision by specifying them with a * in the format string to force their values to be taken from the next item in the inputs to the right of the % operator—the 4 in the tuple here gives precision:

```python
>>> '%f, %.2f, %.*f' % (1/3.0, 1/3.0, 4, 1/3.0)
'0.333333, 0.33, 0.3333'
```

### Dictionary-Based Formatting Expressions  

As a more advanced extension, string formatting also allows conversion targets on the left to refer to the keys in a dictionary coded on the right and fetch the corresponding values. This opens the door to using formatting as a sort of template tool.   

```python
>>> '%(qty)d more %(food)s' % {'qty': 1, 'food': 'spam'}
'1 more spam'
```

Here, the (qty) and (food) in the format string on the left refer to keys in the dictionary literal on the right and fetch their associated values.

## String Formatting Method Calls

As mentioned earlier, Python 2.6 and 3.0 introduced a new way to format strings that is seen by some as a bit more Python-specific.   

### Formatting Method Basics

The string object’s format method, available in Python 2.6, 2.7, and 3.X, is based on normal function call syntax, instead of an expression. Specifically, it uses the subject string as a template, and takes any number of arguments that represent values to be substituted according to the template.

Within the subject string, curly braces designate substitution targets and arguments to be inserted either by position (e.g., {1}), or keyword (e.g., {food}), or relative position in 2.7, 3.1, and later ({}).   

```python
>>> template = '{0}, {1} and {2}' # By position
>>> template.format('spam', 'ham', 'eggs')
'spam, ham and eggs'
>>> template = '{motto}, {pork} and {food}' # By keyword
>>> template.format(motto='spam', pork='ham', food='eggs')
'spam, ham and eggs'
>>> template = '{motto}, {0} and {food}' # By both
>>> template.format('ham', motto='spam', food='eggs')
'spam, ham and eggs'
>>> template = '{}, {} and {}' # By relative position
>>> template.format('spam', 'ham', 'eggs') # New in 3.1 and 2.7
'spam, ham and eggs'

>>> '{motto}, {0} and {food}'.format(42, motto=3.14, food=[1, 2])
'3.14, 42 and [1, 2]'

>>> X = '{motto}, {0} and {food}'.format(42, motto=3.14, food=[1, 2])
>>> X
'3.14, 42 and [1, 2]'
```

### Adding Keys, Attributes, and Offsets

For instance, format strings can name object attributes and dictionary keys—as in normal Python syntax, square brackets name dictionary keys and dots denote object attributes of an item referenced by position or keyword.  

```python
>>> import sys

>>> 'My {1[kind]} runs {0.platform}'.format(sys, {'kind': 'laptop'})
'My laptop runs win32'

>>> 'My {map[kind]} runs {sys.platform}'.format(sys=sys, map={'kind': 'laptop'})
'My laptop runs win32'

>>> somelist = list('SPAM')
>>> somelist
['S', 'P', 'A', 'M']
>>> 'first={0[0]}, third={0[2]}'.format(somelist)
'first=S, third=A'
```



# Lists and Dictionaries  

## Lists 

Python lists are:   

- Ordered collections of arbitrary objects  
- Accessed by offset  
- Variable-length, heterogeneous, and arbitrarily nestable  
- Of the category “mutable sequence”  
- Arrays of object references 

## Lists in Action 

### Basic List Operations

```python
% python
>>> len([1, 2, 3]) # Length
3
>>> [1, 2, 3] + [4, 5, 6] # Concatenation
[1, 2, 3, 4, 5, 6]
>>> ['Ni!'] * 4 # Repetition
['Ni!', 'Ni!', 'Ni!', 'Ni!']
```

### List Iteration and Comprehensions

```python
>>> 3 in [1, 2, 3] # Membership
True
>>> for x in [1, 2, 3]:
... print(x, end=' ') # Iteration (2.X uses: print x,)
...
1 2 3

>>> res = [c * 4 for c in 'SPAM'] # List comprehensions
>>> res
['SSSS', 'PPPP', 'AAAA', 'MMMM']

>>> res = []
>>> for c in 'SPAM': # List comprehension equivalent
... res.append(c * 4)
...
>>> res
['SSSS', 'PPPP', 'AAAA', 'MMMM']

>>> list(map(abs, [−1, −2, 0, 1, 2])) # Map a function across a sequence
[1, 2, 0, 1, 2]
```

### Indexing, Slicing, and Matrixes

```python
>>> L = ['spam', 'Spam', 'SPAM!']
>>> L[2] # Offsets start at zero
'SPAM!'
>>> L[−2] # Negative: count from the right
'Spam'
>>> L[1:] # Slicing fetches sections
['Spam', 'SPAM!']

>>> matrix = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
>>> matrix[1]
[4, 5, 6]
>>> matrix[1][1]
5
>>> matrix[2][0]
7
>>> matrix = [[1, 2, 3],
... [4, 5, 6],
... [7, 8, 9]]
>>> matrix[1][1]
5
```

### Index and slice assignments  

```python
>>> L = ['spam', 'Spam', 'SPAM!']
>>> L[1] = 'eggs' # Index assignment
>>> L
['spam', 'eggs', 'SPAM!']
>>> L[0:2] = ['eat', 'more'] # Slice assignment: delete+insert
>>> L # Replaces items 0,1
['eat', 'more', 'SPAM!']
```

Slice assignment, the last operation in the preceding example, replaces an entire section of a list in a single step. Because it can be a bit complex, it is perhaps best thought of as a combination of two steps:

1. Deletion. The slice you specify to the left of the = is deleted.
2. Insertion. The new items contained in the iterable object to the right of the = are inserted into the list on the left, at the place where the old slice was deleted.

```python
>>> L = [1, 2, 3]
>>> L[1:2] = [4, 5] # Replacement/insertion
>>> L
[1, 4, 5, 3]
>>> L[1:1] = [6, 7] # Insertion (replace nothing)
>>> L
[1, 6, 7, 4, 5, 3]
>>> L[1:2] = [] # Deletion (insert nothing)
>>> L
[1, 7, 4, 5, 3]

>>> L = [1]
>>> L[:0] = [2, 3, 4] # Insert all at :0, an empty slice at front
>>> L
[2, 3, 4, 1]
>>> L[len(L):] = [5, 6, 7] # Insert all at len(L):, an empty slice at end
>>> L
[2, 3, 4, 1, 5, 6, 7]
>>> L.extend([8, 9, 10]) # Insert all at end, named method
>>> L
[2, 3, 4, 1, 5, 6, 7, 8, 9, 10]
```

### List method calls

```python
>>> L = ['eat', 'more', 'SPAM!']
>>> L.append('please') # Append method call: add item at end
>>> L
['eat', 'more', 'SPAM!', 'please']
>>> L.sort() # Sort list items ('S' < 'e')
>>> L
['SPAM!', 'eat', 'more', 'please'] 

>>> L = ['abc', 'ABD', 'aBe']
>>> L.sort() # Sort with mixed case
>>> L
['ABD', 'aBe', 'abc']
>>> L = ['abc', 'ABD', 'aBe']
>>> L.sort(key=str.lower) # Normalize to lowercase
>>> L
['abc', 'ABD', 'aBe']
>>>
>>> L = ['abc', 'ABD', 'aBe']
>>> L.sort(key=str.lower, reverse=True) # Change sort order
>>> L
['aBe', 'ABD', 'abc']

>>> L = ['abc', 'ABD', 'aBe']
>>> sorted(L, key=str.lower, reverse=True) # Sorting built-in
['aBe', 'ABD', 'abc']
>>> L = ['abc', 'ABD', 'aBe']
>>> sorted([x.lower() for x in L], reverse=True) # Pretransform items: differs!
['abe', 'abd', 'abc']

>>> L = [1, 2]
>>> L.extend([3, 4, 5]) # Add many items at end (like in-place +)
>>> L
[1, 2, 3, 4, 5]
>>> L.pop() # Delete and return last item (by default: −1)
5
>>> L
[1, 2, 3, 4]
>>> L.reverse() # In-place reversal method
>>> L
[4, 3, 2, 1]
>>> list(reversed(L)) # Reversal built-in with a result (iterator)
[1, 2, 3, 4]

>>> L = [1, 2]
>>> L.extend([3, 4, 5]) # Add many items at end (like in-place +)
>>> L
[1, 2, 3, 4, 5]
>>> L.pop() # Delete and return last item (by default: −1)
5
>>> L
[1, 2, 3, 4]
>>> L.reverse() # In-place reversal method
>>> L
[4, 3, 2, 1]
>>> list(reversed(L)) # Reversal built-in with a result (iterator)
[1, 2, 3, 4]

>>> L = ['spam', 'eggs', 'ham']
>>> L.index('eggs') # Index of an object (search/find)
1
>>> L.insert(1, 'toast') # Insert at position
>>> L
['spam', 'toast', 'eggs', 'ham']
>>> L.remove('eggs') # Delete by value
>>> L
['spam', 'toast', 'ham']
>>> L.pop(1) # Delete by position
'toast'
>>> L
['spam', 'ham']
>>> L.count('spam') # Number of occurrences
1

>>> L = ['spam', 'eggs', 'ham', 'toast']
>>> del L[0] # Delete one item
>>> L
['eggs', 'ham', 'toast']
>>> del L[1:] # Delete an entire section
>>> L # Same as L[1:] = []
['eggs']

>>> L = ['Already', 'got', 'one']
>>> L[1:] = []
>>> L
['Already']
>>> L[0] = []
>>> L
[[]]
```

## Dictionaries

Python dictionaries are 

- Accessed by key, not offset position  
- Unordered collections of arbitrary objects  
- Variable-length, heterogeneous, and arbitrarily nestable   
- Of the category “mutable mapping”  
- Tables of object references (hash tables) 

## Dictionaries in Action

### Basic Dictionary Operations

```python
% python
>>> D = {'spam': 2, 'ham': 1, 'eggs': 3} # Make a dictionary
>>> D['spam'] # Fetch a value by key
2
>>> D # Order is "scrambled"
{'eggs': 3, 'spam': 2, 'ham': 1}
```

Notice the end of this example—much like sets, the left-to-right order of keys in a dictionary will almost always be different from what you originally typed. This is on purpose: to implement fast key lookup (a.k.a. hashing), keys need to be reordered in memory.    

```python
>>> len(D) # Number of entries in dictionary
3
>>> 'ham' in D # Key membership test alternative
True
>>> list(D.keys()) # Create a new list of D's keys
['eggs', 'spam', 'ham']
```

### Changing Dictionaries in Place

```python
>>> D
{'eggs': 3, 'spam': 2, 'ham': 1}
>>> D['ham'] = ['grill', 'bake', 'fry'] # Change entry (value=list)
>>> D
{'eggs': 3, 'spam': 2, 'ham': ['grill', 'bake', 'fry']}
>>> del D['eggs'] # Delete entry
>>> D
{'spam': 2, 'ham': ['grill', 'bake', 'fry']}
>>> D['brunch'] = 'Bacon' # Add new entry
>>> D
{'brunch': 'Bacon', 'spam': 2, 'ham': ['grill', 'bake', 'fry']}  
```

### More Dictionary Methods

```python
>>> D = {'spam': 2, 'ham': 1, 'eggs': 3}
>>> list(D.values())
[3, 2, 1]
>>> list(D.items())
[('eggs', 3), ('spam', 2), ('ham', 1)]
```

Fetching a nonexistent key is normally an error, but the get method returns a default value—None, or a passed-in default—if the key doesn’t exist.   

```python
>>> D.get('spam') # A key that is there
2
>>> print(D.get('toast')) # A key that is missing
None
>>> D.get('toast', 88)
88

>>> D
{'eggs': 3, 'spam': 2, 'ham': 1}
>>> D2 = {'toast':4, 'muffin':5} # Lots of delicious scrambled order here
>>> D.update(D2)
>>> D
{'eggs': 3, 'muffin': 5, 'toast': 4, 'spam': 2, 'ham': 1}

# pop a dictionary by key
>>> D
{'eggs': 3, 'muffin': 5, 'toast': 4, 'spam': 2, 'ham': 1}
>>> D.pop('muffin')
5
>>> D.pop('toast') # Delete and return from a key
4
>>> D
{'eggs': 3, 'spam': 2, 'ham': 1}
```

# Tuples, Files, and Everything Else

This chapter rounds out our in-depth tour of the core object types in Python by exploring the tuple, a collection of other objects that cannot be changed, and the file, an interface to external files on your computer.

##  Tuples

- Ordered collections of arbitrary objects 
- Accessed by offset  
- Of the category “immutable sequence”  
- Fixed-length, heterogeneous, and arbitrarily nestable  
- Arrays of object references  

## Tuples in Action

```python
>>> (1, 2) + (3, 4) # Concatenation
(1, 2, 3, 4)
>>> (1, 2) * 4 # Repetition
(1, 2, 1, 2, 1, 2, 1, 2)
>>> T = (1, 2, 3, 4) # Indexing, slicing
>>> T[0], T[1:3]
(1, (2, 3))
```

Because parentheses can also enclose expressions (see Chapter 5), you need to do something special to tell Python when a single object in parentheses is a tuple object and not a simple expression.  

```python
>>> x = (40) # An integer!
>>> x
40
>>> y = (40,) # A tuple containing an integer
>>> y
(40,)

>>> T = ('cc', 'aa', 'dd', 'bb')
>>> tmp = list(T) # Make a list from a tuple's items
>>> tmp.sort() # Sort the list
>>> tmp
['aa', 'bb', 'cc', 'dd']
>>> T = tuple(tmp) # Make a tuple from the list's items
>>> T
('aa', 'bb', 'cc', 'dd')
>>> sorted(T) # Or use the sorted built-in, and save two steps
['aa', 'bb', 'cc', 'dd']

>>> T = (1, 2, 3, 2, 4, 2) # Tuple methods in 2.6, 3.0, and later
>>> T.index(2) # Offset of first appearance of 2
1
>>> T.index(2, 2) # Offset of appearance after offset 2
3
>>> T.count(2) # How many 2s are there?
3

>>> T = (1, [2, 3], 4)
>>> T[1] = 'spam' # This fails: can't change tuple itself
TypeError: object doesn't support item assignment
>>> T[1][0] = 'spam' # This works: can change mutables inside
>>> T
(1, ['spam', 3], 4)
```



# Unicode and Byte Strings

### String Base 

Character sets are standards that assign integer codes to individual characters so they can be represented in computer memory.  For example, the ASCII standard maps the character 'a' to the integer value 97 (0x61
in hex), which can be stored in a single byte in memory and files.  ASCII defines character codes from 0 through 127 and allows each character to be stored in one 8-bit byte, only 7 bits of which are actually used.  

```python
>>> ord('a') # 'a' is a byte with binary value 97 in ASCII (and others)
97
>>> hex(97)
'0x61'
>>> chr(97) # Binary value 97 stands for character 'a'
'a'
```

Still, some alphabets define so many characters that it is impossible to represent each of them as one byte. Unicode allows more flexibility.  Unicode is typically used in internationalized programs, to represent
European, Asian, and other non-English character sets that have more characters than 8-bit bytes can represent.

To store such rich text in computer memory, we say that characters are translated to and from raw bytes using an encoding—the rules for translating a string of Unicode characters to a sequence of bytes, and extracting a string from a sequence of bytes.

- Encoding is the process of translating a string of characters into its raw bytes form, according to a desired encoding name.
- Decoding is the process of translating a raw string of bytes into its character string form, according to its encoding name

That is, we encode from string to raw bytes, and decode from raw bytes to string. To scripts, decoded strings are just characters in memory, but may be encoded into a variety of byte string representations when stored on files, transferred over networks, embedded in documents and databases, and so on.

### Coding Basic Strings  

Python 3.X comes with three string object types--one for textual data and two for binary data:

- str for representing decoded Unicode text (including ASCII)
- bytes for representing binary data (including encoded text)
- bytearray, a mutable flavor of the bytes type  

Python 3.X string objects originate when you call a built-in function such as str or bytes, read a file created by calling open (described in the next section), or code literal syntax in your script.  

```python
C:\code> C:\python33\python
>>> B = b'spam' # 3.X bytes literal make a bytes object (8-bit bytes)
>>> S = 'eggs' # 3.X str literal makes a Unicode text string
>>> type(B), type(S)
(<class 'bytes'>, <class 'str'>)
>>> B # bytes: sequence of int, prints as character string
b'spam'
>>> S
'eggs'

>>> B[0], S[0] # Indexing returns an int for bytes, str for str
(115, 'e')
>>> B[1:], S[1:] # Slicing makes another bytes or str object
(b'pam', 'ggs')
>>> list(B), list(S)
([115, 112, 97, 109], ['e', 'g', 'g', 's']) # bytes is really 8-bit small ints

>>> B[0] = 'x' # Both are immutable
TypeError: 'bytes' object does not support item assignment
>>> S[0] = 'x'
TypeError: 'str' object does not support item assignment
    
>>> # bytes prefix works on single, double, triple quotes, raw
>>> B = B"""
... xxxx
... yyyy
... """
>>> B
b'\nxxxx\nyyyy\n'
```





## 参考：

learning python （python学习手册）



