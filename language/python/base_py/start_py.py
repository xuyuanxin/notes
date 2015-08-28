>>> 2 + 2
>>> 1/2
0
>>> 1.0 / 2.0
0.5
>>> 1/2.0
0.5
>>> 1./2
0.5
>>> from __future__ import division
>>> 1 / 2
0.5
>>> 1 // 2
0
>>> 1.0 // 2.0 # The double slash consistently performs integer division, even with floats:
0.0

''' 
----> Large Integers
A long (or long integer) is written just like an ordinary integer but with an L at t-
he end. (You can, in theory, use a lowercase l as well, but that looks all too much -
like the digit 1, so I¡¯d advise against it.)

----> print
In Python 3.0, @print is a function, which means you need to write 
    print(42) 
instead of 
    print 42

----> Getting Input from the User
>>> x = input("x: ")
x: 34
>>> y = input("y: ")
y: 42
>>> print x * y
1428

----> import
we import a module with import, and then use the functions from that module by writi-
ng module.function. 
>>> import math
>>> math.floor(32.9)
32.0
If you are sure that you won¡¯t import more than one function with a given name (from different modules), you might not want to write the module name each time you call the function.
Then you can use a variant of the import command:
>>> from math import sqrt
>>> sqrt(9)
3.0
After using from module import function, you can use the function without its module
prefix.

----> string
>>> "Hello, world!"
'Hello, world!'
>>> 'Hello, world!'
'Hello, world!'
>>> "Let's go!"
"Let's go!"
>>> '"Hello, world!" she said'
'"Hello, world!" she said'
>>> 'Let's go!'
SyntaxError: invalid syntax
>>> 'Let\'s go!'
"Let's go!"
>>> "\"Hello, world!\" she said"
'"Hello, world!" she said'

Throughout these examples, you have probably noticed that all the strings printed ou-
t by Python are still quoted. That¡¯s because it prints out the value as it might be -
written in Python code, not how you would like it to look for the user. If you use  -
print, however, the result is different:
>>> "Hello, world!"
'Hello, world!'
>>> 10000L
10000L
>>> print "Hello, world!"
Hello, world!
>>> print 10000L
10000
>>> "Hello, world!"
'Hello, world!'
>>> 10000L
10000L
>>> print "Hello, world!"
Hello, world!
>>> print 10000L
10000
'''


----> input vs. raw_input
Now you know what "Hello, " + name + "!" means. But what about raw_input? Isn¡¯t input
good enough? Let¡¯s try it. Enter the following in a separate script file:
name = input("What is your name? ")
print "Hello, " + name + "!"
This is a perfectly valid program, but as you will soon see, it¡¯s a bit impractical. Let¡¯s try
to run it:
What is your name? Gumby
Traceback (most recent call last):
File "C:/python/test.py", line 2, in ?
name = input("What is your name? ")
File "<string>", line 0, in ?
NameError: name 'Gumby' is not defined
The problem is that input assumes that what you enter is a valid Python expression (it¡¯s
more or less the inverse of repr). If you write your name as a string, that¡¯s no problem:
What is your name? "Gumby"
Hello, Gumby!
However, it¡¯s just a bit too much to ask that users write their name in quotes like this.
Therefore, we use raw_input, which treats all input as raw data and puts it into a string:
>>> input("Enter a number: ")
Enter a number: 3
3
>>> raw_input("Enter a number: ")
Enter a number: 3
'3'
Unless you have a special need for input, you should probably use raw_input.

----> Long Strings
If you want to write a really long string, one that spans several lines, you can use triple quotes
instead of ordinary quotes:
print '''This is a very long string.
It continues here.
And it's not over yet.
"Hello, world!"
Still here.'''
You can also use triple double quotes, """like this""". Note that because of the distinctive
enclosing quotes, both single and double quotes are allowed inside, without being backslashescaped.


tip:
Ordinary strings can also span several lines. If the last character on a line is a backslash, the line
break itself is ¡°escaped¡± and ignored. For example:
print "Hello, \
world!"
would print out Hello, world!. The same goes for expressions and statements in general:
>>> 1 + 2 + \
4 + 5
12
>>> print \
'Hello, world'
Hello, world

----> Raw Strings
>>> path = 'C:\nowhere'
>>> path
'C:\nowhere'
This looks correct, until you print it and discover the flaw:
>>> print path
C:
owhere

>>> print 'C:\\nowhere'
C:\nowhere
This is just fine. But for long paths, you wind up with a lot of backslashes:
path = 'C:\\Program Files\\fnord\\foo\\bar\\baz\\frozz\\bozz'
Raw strings are useful in such cases. They don¡¯t treat the backslash as a special character
at all. Every character you put into a raw string stays the way you wrote it:
>>> print r'C:\nowhere'
C:\nowhere
>>> print r'C:\Program Files\fnord\foo\bar\baz\frozz\bozz'
C:\Program Files\fnord\foo\bar\baz\frozz\bozz
As you can see, raw strings are prefixed with an r. It would seem that you can put anything
inside a raw string, and that is almost true. Quotes must be escaped as usual, although that
means that you get a backslash in your final string, too:
>>> print r'Let\'s go!'
Let\'s go!

If the last character (before the final quote) is an unescaped backslash, Python won¡¯t
know whether or not to end the string:
>>> print r"This is illegal\"
SyntaxError: invalid token
A simple way of doing that is the following:
>>> print r'C:\Program Files\foo\bar' '\\'
C:\Program Files\foo\bar\
Note that you can use both single and double quotes with raw strings. Even triple-quoted
strings can be raw.

----> Unicode Strings
Normal strings in Python are stored internally as 8-bit ASCII, while
Unicode strings are stored as 16-bit Unicode. This allows for a more varied set of characters,
including special characters from most languages in the world. I¡¯ll restrict my treatment of
Unicode strings to the following:
>>> u'Hello, world!'
u'Hello, world!'
As you can see, Unicode strings use the prefix u, just as raw strings use the prefix r.

Note 
    In Python 3.0, all strings will be Unicode strings.

