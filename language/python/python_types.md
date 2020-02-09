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

This isn’t typical Python code, but it does work—a starts out as an integer, then becomes a string, and finally becomes a floating-point number. However, that’s not really what’s happening. In Python, things work more simply. Names have no types; as stated earlier, types live with objects, not names. In the preceding listing, we’ve simply changed a to reference different objects. 

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

The second command causes Python to create the variable b; the variable a is being used and not assigned here, so it is replaced with the object it references (3), and b is made to reference that object. The net effect is that the variables a and b wind up referencing the same object (that is, pointing to the same chunk of memory). This scenario in Python—with multiple names referencing the same object—is usually called a shared reference (and sometimes just a shared object).   

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



# String Fundamentals

### String Literals  

• Single quotes: 'spa"m'
• Double quotes: "spa'm"
• Triple quotes: '''... spam ...''', """... spam ..."""
• Escape sequences: "s\tp\na\0m"
• Raw strings: r"C:\new\test.spm"
• Bytes literals in 3.X and 2.6+ : b'sp\x01am'
• Unicode literals in 2.X and 3.3+: u'eggs\u0020spam'  

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

## Unicode and Byte Strings

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



