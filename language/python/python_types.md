# Types and Operations

## Introducing Python Object Types  

### String

Strings are used to record both textual information (your name, for instance) as well as arbitrary collections of bytes (such as an image file’s contents).   

#### Sequence Operations  

As sequences, strings support operations that assume a positional ordering among items. For example, if we have a four-character string coded inside quotes (usually of the single variety), we can verify its length with the built-in len function and fetch its components with indexing expressions:  

```python
>>> S = 'Spam' # Make a 4-character string, and assign it to a name
>>> len(S) # Length
4
>>> S[0] # The first item in S, indexing by zero-based position
'S'
>>> S[1] # The second item from the left
'p
```

#### Other Ways to Code Strings  

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

#### Unicode Strings  



## String Fundamentals

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



