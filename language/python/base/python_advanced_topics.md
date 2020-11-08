# Part--Advanced Topics  

# Unicode and Byte Strings  

As we’ll see, the advanced string representation story has diverged in recent versions of Python:

- Python 3.X provides an alternative string type for binary data, and supports Unicode text (including ASCII) in its normal string type.
- Python 2.X provides an alternative string type for non-ASCII Unicode text, and supports both simple text and binary data in its normal string type. 

## String Changes in 3.X

## String Basics

Before we look at any code, let’s begin with a general overview of Python’s string model. To understand why 3.X changed the way it did on this front, we have to start with a brief look at how characters are actually represented in computers—both when encoded in files and when stored in memory.    

### Character Encoding Schemes

**Character sets** are standards that assign integer codes to individual characters so they can be represented in computer memory. The ASCII standard, for example, was created in the U.S., and it defines many U.S. programmers’ notion of text strings. ASCII defines character codes from 0 through 127 and allows each character to be stored in one 8- bit byte, only 7 bits of which are actually used.

```python
>>> ord('a') # 'a' is a byte with binary value 97 in ASCII (and others)
97
>>> hex(97)
'0x61'
>>> chr(97) # Binary value 97 stands for character 'a'
'a'
```

Sometimes one byte per character isn’t enough, though. To accommodate special characters, some standards use all the possible values in an 8-bit byte, 0 through 255, to represent characters, and assign the values 128 through 255 (outside ASCII’s range) to special characters. 

One such standard, known as the Latin-1 character set, is widely used in Western Europe. In Latin-1, character codes above 127 are assigned to accented and otherwise special characters. The character assigned to byte value 196, for example, is a specially marked non-ASCII character:  

```python
>>> 0xC4
196
>>> chr(196) # Python 3.X result form shown
'Ä'
```

Still, some alphabets define so many characters that it is impossible to represent each of them as one byte. Unicode allows more flexibility. Unicode text is sometimes referred to as “wide-character” strings, because characters may be represented with multiple bytes if needed. Unicode is typically used in internationalized programs, to represent European, Asian, and other non-English character sets that have more characters than 8-bit bytes can represent.  

To store such rich text in computer memory, we say that characters are translated to and from raw bytes using an encoding—the rules for translating a string of Unicode characters to a sequence of bytes, and extracting a string from a sequence of bytes. More procedurally, this translation back and forth between bytes and strings is defined by two terms: 

- Encoding is the process of translating a string of characters into its raw bytes form,
  according to a desired encoding name.
- Decoding is the process of translating a raw string of bytes into its character string
  form, according to its encoding name.   

That is, we encode from string to raw bytes, and decode from raw bytes to string. To scripts, decoded strings are just characters in memory, but may be encoded into a variety of byte string representations when stored on files, transferred over networks, embedded in documents and databases, and so on.

The widely used UTF-8 encoding, for example, allows a wide range of characters to be represented by employing a variable-sized number of bytes scheme. Character codes less than 128 are represented as a single byte; codes between 128 and 0x7ff (2047) are turned into 2 bytes, where each byte has a value between 128 and 255; and codes above 0x7ff are turned into 3- or 4-byte sequences having values between 128 and 255. 

Other encodings allow for richer character sets in different ways. UTF-16 and UTF-32, for example, format text with a fixed-size 2 and 4 bytes per each character scheme, respectively, even for characters that could otherwise fit in a single byte. 

To see this for yourself, run a string’s encode method, which gives its encoded bytestring format under a named scheme—a two-character ASCII string is 2 bytes in ASCII, Latin-1, and UTF-8, but it’s much wider in UTF-16 and UTF-32, and includes header bytes:

```python
>>> S = 'ni'
>>> S.encode('ascii'), S.encode('latin1'), S.encode('utf8')
(b'ni', b'ni', b'ni')
>>> S.encode('utf16'), len(S.encode('utf16'))
(b'\xff\xfen\x00i\x00', 6)
>>> S.encode('utf32'), len(S.encode('utf32'))
(b'\xff\xfe\x00\x00n\x00\x00\x00i\x00\x00\x00', 12)
```

### How Python Stores Strings in Memory  

In memory, Python always stores decoded text strings in an encoding-neutral format, which may or may not use multiple bytes for each character.  The key point here, though, is that encoding pertains mostly to files and transfers. Once loaded into a Python string, text in memory has no notion of an “encoding,” and is
simply a sequence of Unicode characters (a.k.a. code points) stored generically.   

### Python’s String Types  

Python 2.X has a general string type for representing binary data and simple 8-bit text like ASCII, along with a specific type for representing richer Unicode text:  

- str for representing 8-bit text and binary data
- unicode for representing decoded Unicode text  

The str string type in 2.X is used for text that can be represented with 8-bit bytes (including ASCII and Latin-1), as well as binary data that represents absolute byte values.  

By contrast, Python 3.X comes with three string object types—one for textual data and two for binary data:  

- str for representing decoded Unicode text (including ASCII)
- bytes for representing binary data (including encoded text)
- bytearray, a mutable flavor of the bytes type  

### Text and Binary Files  

## Coding Basic Strings  

### Python 3.X String Literals  

Python 3.X string objects originate when you call a built-in function such as str or bytes, read a file created by calling open, or code literal syntax in your script. More formally, in 3.X all the current string literal forms—'xxx', "xxx", and triplequoted blocks—generate a str; adding a b or B just before any of them creates a bytes instead. This new b'...' bytes literal is similar in form to the r'...' raw string used to suppress backslash escapes. Consider the following, run in 3.X: 

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

Python 2.X’s u'xxx' and U'xxx' Unicode string literal forms were removed in Python 3.0 because they were deemed redundant—normal strings are Unicode in 3.X. To aid both forward and backward compatibility, though, they are available again as of 3.3, where they are treated as normal str strings:  

```python
C:\code> C:\python33\python
>>> U = u'spam' # 2.X Unicode literal accepted in 3.3+
>>> type(U) # It is just str, but is backward compatible
<class 'str'>
>>> U
'spam'
>>> U[0]
's'
>>> list(U)
['s', 'p', 'a', 'm']
```

### String Type Conversions    

Although Python 2.X allowed str and unicode type objects to be mixed in expressions (when the str contained only 7-bit ASCII text), 3.X draws a much sharper distinction —str and bytes type objects never mix automatically in expressions and never are converted to one another automatically when passed to functions. A function that expects an argument to be a str object won’t generally accept a bytes, and vice versa.  

Because of this, Python 3.X basically requires that you commit to one type or the other, or perform manual, explicit conversions when needed:  

- str.encode() and bytes(S, encoding) translate a string to its raw bytes form and create an encoded bytes from a decoded str in the process.
- bytes.decode() and str(B, encoding) translate raw bytes into its string form and create a decoded str from an encoded bytes in the process.  

These encode and decode methods (as well as file objects, described in the next section) use either a default encoding for your platform or an explicitly passed-in encoding name. For example, in Python 3.X:  

```python
>>> S = 'eggs'
>>> S.encode() # str->bytes: encode text into raw bytes
b'eggs'
>>> bytes(S, encoding='ascii') # str->bytes, alternative
b'eggs'

>>> B = b'spam'
>>> B.decode() # bytes->str: decode raw bytes into text
'spam'
>>> str(B, encoding='ascii') # bytes->str, alternative
'spam'
```

Two cautions here. First of all, your platform’s default encoding is available in the sys module, but the encoding argument to bytes is not optional, even though it is in str.encode (and bytes.decode).

Second, although calls to str do not require the encoding argument like bytes does, leaving it off in str calls does not mean that it defaults—instead, a str call without an encoding returns the bytes object’s print string, not its str converted form (this is usually not what you’ll want!). Assuming B and S are still as in the prior listing:

```python
>>> import sys
>>> sys.platform # Underlying platform
'win32'
>>> sys.getdefaultencoding() # Default encoding for str here
'utf-8'
>>> bytes(S)
TypeError: string argument without an encoding
>>> str(B) # str without encoding
"b'spam'" # A print string, not conversion!
>>> len(str(B))
7
>>> len(str(B, encoding='ascii')) # Use encoding to convert to str
4
```



# Managed Attributes  

This chapter expands on the attribute interception techniques introduced earlier, introduces another, and employs them in a handful of larger examples.  

## Why Manage Attributes?

##   Properties

The property protocol allows us to route a specific attribute’s get, set, and delete operations to functions or methods we provide, enabling us to insert code to be run automatically on attribute access, intercept attribute deletions, and provide documentation for the attributes if desired.  

Properties are created with the property built-in and are assigned to class attributes, just like method functions. Accordingly, they are inherited by subclasses and instances, like any other class attributes.  

### The Basics

A property is created by assigning the result of a built-in function to a class attribute:  

```python
attribute = property(fget, fset, fdel, doc)
```

all default to None if not passed. For the first three, this None means that the corresponding operation is not supported, and attempting it will raise an AttributeError exception automatically.  When these arguments are used, we pass fget a function for intercepting attribute fetches, fset a function for assignments, and fdel a function for attribute deletions. The doc argument receives a documentation string for the attribute, if desired; otherwise, the property copies the docstring of the fget function, which as usual defaults to None.  

This built-in property call returns a property object, which we assign to the name of the attribute to be managed in the class scope, where it will be inherited by every instance.  

### A First Example 

```python
class Person: # Add (object) in 2.X
    def __init__(self, name):
        self._name = name
    def getName(self):
        print('fetch...')
        return self._name
    def setName(self, value):
        print('change...')
        self._name = value
    def delName(self):
        print('remove...')
        del self._name
    name = property(getName, setName, delName, "name property docs")

bob = Person('Bob Smith') # bob has a managed attribute
print(bob.name) # Runs getName
bob.name = 'Robert Smith' # Runs setName
print(bob.name)
del bob.name # Runs delName
print('-'*20)
sue = Person('Sue Jones') # sue inherits property too
print(sue.name)
print(Person.name.__doc__) # Or help(Person.name)
```

This particular property doesn’t do much—it simply intercepts and traces an attribute—but it serves to demonstrate the protocol. When this code is run, two instances inherit the property, just as they would any other attribute attached to their class. However, their attribute accesses are caught:  

```python
c:\code> py −3 prop-person.py
fetch...
Bob Smith
change...
fetch...
Robert Smith
remove...
--------------------
fetch...
Sue Jones
name property docs
```

Like all class attributes, properties are inherited by both instances and lower subclasses. If we change our example as follows, for instance:  

```python
class Super:
    ...the original Person class code...
    name = property(getName, setName, delName, 'name property docs')
class Person(Super):
    pass # Properties are inherited (class attrs)

bob = Person('Bob Smith')
...rest unchanged...
```

the output is the same—the Person subclass inherits the name property from Super, and the bob instance gets it from Person. In terms of inheritance, properties work the same as normal methods; because they have access to the self instance argument, they can access instance state information and methods irrespective of subclass depth, as the next section further demonstrates.  

### Computed Attributes

The example in the prior section simply traces attribute accesses. Usually, though, properties do much more—computing the value of an attribute dynamically when fetched, for example. The following example illustrates:   

```python
class PropSquare:
    def __init__(self, start):
        self.value = start
    def getX(self): # On attr fetch
        return self.value ** 2
    def setX(self, value): # On attr assign
        self.value = value
    X = property(getX, setX) # No delete or docs

P = PropSquare(3) # Two instances of class with property
Q = PropSquare(32) # Each has different state information
print(P.X) # 3 ** 2
P.X = 4
print(P.X) # 4 ** 2
print(Q.X) # 32 ** 2 (1024)
```

```python
c:\code> py −3 prop-computed.py
9
16
1024
```

Notice that we’ve made two different instances—because property methods automatically receive a self argument, they have access to the state information stored in instances. In our case, this means the fetch computes the square of the subject instance’s own data.

## Coding Properties with Decorators  

```python
class Person:
    @property
    def name(self): ... # Rebinds: name = property(name)
```

When run, the decorated method is automatically passed to the first argument of the property built-in. This is really just alternative syntax for creating a property and rebinding the attribute name manually, but may be seen as more explicit in this role:  

```python
class Person:
    def name(self): ...
    name = property(name)
```

As of Python 2.6 and 3.0, property objects also have getter, setter, and deleter methods that assign the corresponding property accessor methods and return a copy of the property itself. We can use these to specify components of properties by decorating normal methods too, though the getter component is usually filled in automatically by the act of creating the property itself:

```python
class Person:
    def __init__(self, name):
        self._name = name
    @property
    def name(self): # name = property(name)
        "name property docs"
        print('fetch...')
        return self._name
    @name.setter
    def name(self, value): # name = name.setter(name)
        print('change...')
        self._name = value
    @name.deleter
    def name(self): # name = name.deleter(name)
        print('remove...')
        del self._name

bob = Person('Bob Smith') # bob has a managed attribute
print(bob.name) # Runs name getter (name 1)
bob.name = 'Robert Smith' # Runs name setter (name 2)
print(bob.name)
del bob.name # Runs name deleter (name 3)
print('-'*20)
sue = Person('Sue Jones') # sue inherits property too
print(sue.name)
print(Person.name.__doc__) # Or help(Person.name)
```

```python
c:\code> py −3 prop-person-deco.py
fetch...
Bob Smith
change...
fetch...
Robert Smith
remove...
--------------------
fetch...
Sue Jones
name property docs
```

  

# Decorators

This is a somewhat advanced topic, and decorator construction tends to be of more interest to tool builders than to application programmers. Still, given that decorators are becoming increasingly common in popular Python frameworks, a basic understanding can help demystify their role, even if you’re just a decorator user.    

## What’s a Decorator?  

Decoration is a way to specify management or augmentation code for functions and classes. Decorators themselves take the form of callable objects (e.g., functions) that process other callable objects. In short, decorators provide a way to insert automatically run code at the end of function and class definition statements--at the end of a def for function decorators, and at the end of a class for class decorators.  

## The Basics

### Function Decorators    

Function decorators have been available in Python since version 2.4. As we saw earlier in this book, they are largely just syntactic sugar that runs one function through another at the end of a def statement, and rebinds the original function name to the result.   

#### Usage  

The decorator is coded on a line just before the def statement that defines a function or method, and it consists of the @ symbol followed by a reference to a metafunction—a function (or other callable object) that manages another function.  

In terms of code, function decorators automatically map the following syntax:  

```python
@decorator # Decorate function
def F(arg):
    ...

F(99) # Call function
```

into this equivalent form, where decorator is a one-argument callable object that returns a callable object with the same number of arguments as F (in not F itself):

```python
def F(arg):
    ...
F = decorator(F) # Rebind function name to decorator result
F(99) # Essentially calls decorator(F)(99)
```

When the function F is later called, it’s actually calling the object returned by the decorator, which may be either another object that implements required wrapping logic, or the original function itself.  

#### Implementation

A decorator itself is a callable that returns a callable. That is, it returns the object to be called later when the decorated function is invoked through its original name—either a wrapper object to intercept later calls, or the original function augmented in some way. In fact, decorators can be any type of callable and return any type of callable.

For example  

```python
def decorator(F):
    # Process function F
    return F
    
@decorator
def func(): ... # func = decorator(func)
```

Because the original decorated function is assigned back to its name, this simply adds a post-creation step to function definition. 

In more typical use, to insert logic that intercepts later calls to a function, we might code a decorator to return a different object than the original function—a proxy for later calls:

```python
def decorator(F):
    # Save or use function F
    # Return a different callable: nested def, class with __call__, etc.

@decorator
def func(): ... # func = decorator(func)
```

This decorator is invoked at decoration time, and the callable it returns is invoked when the original function name is later called. The decorator itself receives the decorated function; the callable returned receives whatever arguments are later passed to the decorated function’s name. 

In skeleton terms, here’s one common coding pattern that captures this idea—the decorator returns a wrapper that retains the original function in an enclosing scope:  

```python
def decorator(F): # On @ decoration
    def wrapper(*args): # On wrapped function call
        # Use F and args
        # F(*args) calls original function
    return wrapper

@decorator # func = decorator(func)
def func(x, y): # func is passed to decorator's F
    ...

func(6, 7) # 6, 7 are passed to wrapper's *args
```

When the name func is later called, it really invokes the wrapper function returned by decorator; the wrapper function can then run the original func because it is still available in an enclosing scope.

To do the same with classes, we can overload the call operation and use instance attributes instead of enclosing scopes:

```python
class decorator:
    def __init__(self, func): # On @ decoration
        self.func = func
    def __call__(self, *args): # On wrapped function call
        # Use self.func and args
        # self.func(*args) calls original function

@decorator
def func(x, y): # func = decorator(func)
    ... # func is passed to __init__

func(6, 7) # 6, 7 are passed to __call__'s *args
```

### Class Decorators

Rather than wrapping individual functions or methods, though, class decorators are a way to manage classes, or wrap up instance construction calls with extra logic that manages or augments instances created from a class.  

the class decorator syntax:   

```python
@decorator # Decorate class
class C:
    ...
    
x = C(99) # Make an instance
```

is equivalent to the following—the class is automatically passed to the decorator function, and the decorator’s result is assigned back to the class name:

```python
class C:
    ...

C = decorator(C) # Rebind class name to decorator result
x = C(99) # Essentially calls decorator(C)(99)
```

The net effect is that calling the class name later to create an instance winds up triggering the callable returned by the decorator, which may or may not call the original class itself.

For example, to simply manage a class just after it is created, return the original class itself:  

```python
def decorator(C):
    # Process class C
    return C

@decorator
class C: ... # C = decorator(C)
```

To instead insert a wrapper layer that intercepts later instance creation calls, return a different callable object:

```python
def decorator(C):
    # Save or use class C
    # Return a different callable: nested def, class with __call__, etc.

@decorator
class C: ... # C = decorator(C)
```

The callable returned by such a class decorator typically creates and returns a new instance of the original class, augmented in some way to manage its interface. For example, the following inserts an object that intercepts undefined attributes of a class instance:

```python
def decorator(cls): # On @ decoration
    class Wrapper:
        def __init__(self, *args): # On instance creation
            self.wrapped = cls(*args)
        def __getattr__(self, name): # On attribute fetch
            return getattr(self.wrapped, name)
    return Wrapper
    
@decorator
class C: # C = decorator(C)
    def __init__(self, x, y): # Run by Wrapper.__init__
        self.attr = 'spam'

x = C(6, 7) # Really calls Wrapper(6, 7)
print(x.attr) # Runs Wrapper.__getattr__, prints "spam"
```

## Coding Function Decorators

This section presents a handful of function decorators at work, and the next shows class decorators in action.  

### Tracing Calls 

The following defines and applies a function decorator that counts the number of calls made to the
decorated function and prints a trace message for each call: 

```python
# File decorator1.py
class tracer:
    def __init__(self, func): # On @ decoration: save original func
        self.calls = 0
        self.func = func
    def __call__(self, *args): # On later calls: run original func
        self.calls += 1
        print('call %s to %s' % (self.calls, self.func.__name__))
        self.func(*args)

@tracer
def spam(a, b, c): # spam = tracer(spam)
    print(a + b + c) # Wraps spam in a decorator object
```

```python
>>> from decorator1 import spam
>>> spam(1, 2, 3) # Really calls the tracer wrapper object
call 1 to spam
6
>>> spam('a', 'b', 'c') # Invokes __call__ in class
call 2 to spam
abc
>>> spam.calls # Number calls in wrapper state information
2
>>> spam
<decorator1.tracer object at 0x02D9A730>
```

When run, the tracer class saves away the decorated function, and intercepts later calls to it, in order to add a layer of logic that counts and prints each call. Notice how the total number of calls shows up as an attribute of the decorated function—spam is really an instance of the tracer class when decorated

Consider a nondecorator equivalent such as the following:

```python
calls = 0
def tracer(func, *args):
    global calls
    calls += 1
    print('call %s to %s' % (calls, func.__name__))
    func(*args)

def spam(a, b, c):
    print(a, b, c)

>>> spam(1, 2, 3) # Normal nontraced call: accidental?
1 2 3

>>> tracer(spam, 1, 2, 3) # Special traced call without decorators
call 1 to spam
1 2 3
```

### Decorator State Retention Options  

Function decorators have a variety of options for retaining state information provided at decoration time,
for use during the actual function call. They generally need to support multiple decorated objects and multiple calls, but there are a number of ways to implement these goals: instance attributes, global variables, nonlocal closure variables, and function attributes can all be used for retaining state. 

#### Class instance attributes   

```python
class tracer: # State via instance attributes
    def __init__(self, func): # On @ decorator
        self.calls = 0 # Save func for later call
        self.func = func
    def __call__(self, *args, **kwargs): # On call to original function
        self.calls += 1
        print('call %s to %s' % (self.calls, self.func.__name__))
        return self.func(*args, **kwargs)

@tracer
def spam(a, b, c): # Same as: spam = tracer(spam)
    print(a + b + c) # Triggers tracer.__init__

@tracer
def eggs(x, y): # Same as: eggs = tracer(eggs)
    print(x ** y) # Wraps eggs in a tracer object

spam(1, 2, 3) # Really calls tracer instance: runs tracer.__call__
spam(a=4, b=5, c=6) # spam is an instance attribute
eggs(2, 16) # Really calls tracer instance, self.func is eggs
eggs(4, y=4) # self.calls is per-decoration here
```

Like the original, this uses class instance attributes to save state explicitly. Both the wrapped function and the calls counter are per-instance information—each decoration gets its own copy.  notice how the spam and eggs functions each have their own calls counter, because each decoration creates a new class instance:    

```python
c:\code> python decorator2.py
call 1 to spam
6
call 2 to spam
15
call 1 to eggs
65536
call 2 to eggs
256
```

#### Enclosing scopes and globals

Closure functions—with enclosing def scope references and nested defs—can often achieve the same effect, especially for static data like the decorated original function.  

```python
calls = 0
def tracer(func): # State via enclosing scope and global
    def wrapper(*args, **kwargs): # Instead of class attributes
        global calls # calls is global, not per-function
        calls += 1
        print('call %s to %s' % (calls, func.__name__))
        return func(*args, **kwargs)
    return wrapper

@tracer
def spam(a, b, c): # Same as: spam = tracer(spam)
    print(a + b + c)

@tracer
def eggs(x, y): # Same as: eggs = tracer(eggs)
    print(x ** y)

spam(1, 2, 3) # Really calls wrapper, assigned to spam
spam(a=4, b=5, c=6) # wrapper calls spam
eggs(2, 16) # Really calls wrapper, assigned to eggs
eggs(4, y=4) # Global calls is not per-decoration here!
```

Unlike class instance attributes, global counters are cross-program, not per-function—the counter is incremented for any traced function call. 

```python
c:\code> python decorator3.py
call 1 to spam
6
call 2 to spam
15
call 3 to eggs
65536
call 4 to eggs
256
```

####  Enclosing scopes and nonlocals     

```python
def tracer(func): # State via enclosing scope and nonlocal
    calls = 0 # Instead of class attrs or global
    def wrapper(*args, **kwargs): # calls is per-function, not global
        nonlocal calls
        calls += 1
        print('call %s to %s' % (calls, func.__name__))
        return func(*args, **kwargs)
    return wrapper

@tracer
def spam(a, b, c): # Same as: spam = tracer(spam)
    print(a + b + c)

@tracer
def eggs(x, y): # Same as: eggs = tracer(eggs)
    print(x ** y)

spam(1, 2, 3) # Really calls wrapper, bound to func
spam(a=4, b=5, c=6) # wrapper calls spam
eggs(2, 16) # Really calls wrapper, bound to eggs
eggs(4, y=4) # Nonlocal calls _is_ per-decoration here
```

Now, because enclosing scope variables are not cross-program globals, each wrapped function gets its own counter again, just as for classes and attributes. Here’s the new output when run under 3.X:  

```python
c:\code> py −3 decorator4.py
call 1 to spam
6
call 2 to spam
15
call 1 to eggs
65536
call 2 to eggs
256
```

#### Function attributes

The following works the same as the preceding nonlocal version because the counter is again per-decoratedfunction, but it also runs in Python 2.X: 

```python
def tracer(func): # State via enclosing scope and func attr
    def wrapper(*args, **kwargs): # calls is per-function, not global
        wrapper.calls += 1
        print('call %s to %s' % (wrapper.calls, func.__name__))
        return func(*args, **kwargs)
    wrapper.calls = 0
    return wrapper

@tracer
def spam(a, b, c): # Same as: spam = tracer(spam)
    print(a + b + c)

@tracer
def eggs(x, y): # Same as: eggs = tracer(eggs)
    print(x ** y)

spam(1, 2, 3) # Really calls wrapper, assigned to spam
spam(a=4, b=5, c=6) # wrapper calls spam
eggs(2, 16) # Really calls wrapper, assigned to eggs
eggs(4, y=4) # wrapper.calls _is_ per-decoration here
```

As we learned in Chapter 17, this works only because the name wrapper is retained in the enclosing tracer function’s scope. When we later increment wrapper.calls, we are not changing the name wrapper itself, so no nonlocal declaration is required. This version runs in either Python line:  

```python
c:\code> py −2 decorator5.py
...same output as prior version, but works on 2.X too...
```

## Coding Class Decorators  

So far we’ve been coding function decorators to manage function calls, but as we’ve seen, decorators have been extended to work on classes too as of Python 2.6 and 3.0. As described earlier, while similar in concept to function decorators, class decorators are applied to classes instead—they may be used either to manage classes themselves, or to intercept instance creation calls in order to manage instances.  

### Singleton Classes   

```python
# 3.X and 2.X: global table
instances = {}
def singleton(aClass): # On @ decoration
    def onCall(*args, **kwargs): # On instance creation
        if aClass not in instances: # One dict entry per class
            instances[aClass] = aClass(*args, **kwargs)
        return instances[aClass]
    return onCall
```

To use this, decorate the classes for which you want to enforce a single-instance model (for reference, all the code in this section is in the file singletons.py):

```python
@singleton # Person = singleton(Person)
class Person: # Rebinds Person to onCall
    def __init__(self, name, hours, rate): # onCall remembers Person
        self.name = name
        self.hours = hours
        self.rate = rate
    def pay(self):
        return self.hours * self.rate

@singleton # Spam = singleton(Spam)
class Spam: # Rebinds Spam to onCall
    def __init__(self, val): # onCall remembers Spam
        self.attr = val

bob = Person('Bob', 40, 10) # Really calls onCall
print(bob.name, bob.pay())
sue = Person('Sue', 50, 20) # Same, single object
print(sue.name, sue.pay())
X = Spam(val=42) # One Person, one Spam
Y = Spam(99)
print(X.attr, Y.attr)
```

Now, when the Person or Spam class is later used to create an instance, the wrapping logic layer provided by the decorator routes instance construction calls to onCall, which in turn ensures a single instance per class, regardless of how many construction calls are made. Here’s this code’s output (2.X prints extra tuple parentheses):  

```python
c:\code> python singletons.py
Bob 400
Bob 400
42 42
```

Interestingly, you can code a more self-contained solution here if you’re able to use the nonlocal statement (available in Python 3.X only) to change enclosing scope names, as described earlier—the following alternative achieves an identical effect, by using one enclosing scope per class, instead of one global table entry per class.

```python
# 3.X only: nonlocal
def singleton(aClass): # On @ decoration
    instance = None
    def onCall(*args, **kwargs): # On instance creation
        nonlocal instance # 3.X and later nonlocal
        if instance == None:
            instance = aClass(*args, **kwargs) # One scope per class
        return instance
    return onCall
```

In either Python 3.X or 2.X (2.6 and later), you can also code a self-contained solution with either function attributes or a class instead. The first of the following codes the former, leveraging the fact that there will be one onCall function per decoration—the object namespace serves the same role as an enclosing scope. The second uses one instance per decoration, rather than an enclosing scope, function object, or global table.

```python
# 3.X and 2.X: func attrs, classes (alternative codings)
def singleton(aClass): # On @ decoration
    def onCall(*args, **kwargs): # On instance creation
        if onCall.instance == None:
            onCall.instance = aClass(*args, **kwargs) # One function per class
        return onCall.instance
    onCall.instance = None
    return onCall

class singleton:
    def __init__(self, aClass): # On @ decoration
        self.aClass = aClass
        self.instance = None
    def __call__(self, *args, **kwargs): # On instance creation
        if self.instance == None:
            self.instance = self.aClass(*args, **kwargs) # One instance per class
        return self.instance
```

### Tracing Object Interfaces

Another common use case for class decorators augments the interface of each generated instance. Class decorators can essentially install on instances a wrapper or “proxy” logic layer that manages access to their interfaces in some way.  

For reference, here’s the original nondecorator delegation example, working on two built-in type objects:

```python
class Wrapper:
    def __init__(self, object):
        self.wrapped = object # Save object
    def __getattr__(self, attrname):
        print('Trace:', attrname) # Trace fetch
        return getattr(self.wrapped, attrname) # Delegate fetch

>>> x = Wrapper([1,2,3]) # Wrap a list
>>> x.append(4) # Delegate to list method
Trace: append
>>> x.wrapped # Print my member
[1, 2, 3, 4]
>>> x = Wrapper({"a": 1, "b": 2}) # Wrap a dictionary
>>> list(x.keys()) # Delegate to dictionary method
Trace: keys # Use list() in 3.X
['a', 'b']
```

In this code, the Wrapper class intercepts access to any of the wrapped object’s named attributes, prints a trace message, and uses the getattr built-in to pass off the request to the wrapped object. Specifically, it traces attribute accesses made outside the wrapped object’s class; accesses inside the wrapped object’s methods are not caught and run normally by design. This whole-interface model differs from the behavior of function decorators, which wrap up just one specific method.   

Class decorators provide an alternative and convenient way to code this `__getattr__` technique to wrap an entire interface.   

```python
def Tracer(aClass): # On @ decorator
    class Wrapper:
        def __init__(self, *args, **kargs): # On instance creation
            self.fetches = 0
            self.wrapped = aClass(*args, **kargs) # Use enclosing scope name
        def __getattr__(self, attrname):
            print('Trace: ' + attrname) # Catches all but own attrs
            self.fetches += 1
            return getattr(self.wrapped, attrname) # Delegate to wrapped obj
    return Wrapper

if __name__ == '__main__':
    @Tracer
    class Spam: # Spam = Tracer(Spam)
        def display(self): # Spam is rebound to Wrapper
            print('Spam!' * 8)
    @Tracer
    class Person: # Person = Tracer(Person)
        def __init__(self, name, hours, rate): # Wrapper remembers Person
            self.name = name
            self.hours = hours
            self.rate = rate
        def pay(self): # Accesses outside class traced
            return self.hours * self.rate # In-method accesses not traced

food = Spam() # Triggers Wrapper()
food.display() # Triggers __getattr__
print([food.fetches])

bob = Person('Bob', 40, 50) # bob is really a Wrapper
print(bob.name) # Wrapper embeds a Person
print(bob.pay())

print('')
sue = Person('Sue', rate=100, hours=60) # sue is a different Wrapper
print(sue.name) # with a different Person
print(sue.pay())

print(bob.name) # bob has different state
print(bob.pay())
print([bob.fetches, sue.fetches]) # Wrapper attrs not traced
```

In contrast, by intercepting instance creation calls, the class decorator here allows us to trace an entire
object interface—that is, accesses to any of the instance’s attributes.  

```python
c:\code> python interfacetracer.py
Trace: display
Spam!Spam!Spam!Spam!Spam!Spam!Spam!Spam!
[1]
Trace: name
Bob
Trace: pay
2000

Trace: name
Sue
Trace: pay
6000
Trace: name
Bob
Trace: pay
2000
[4, 2]    
```

Notice how there is one Wrapper class with state retention per decoration, generated by the nested class statement in the Tracer function, and how each instance gets its own fetches counter by virtue of generating a new Wrapper instance. As we’ll see ahead, orchestrating this is trickier than you may expect   

# Metaclasses  

In a sense, metaclasses simply extend the code-insertion model of decorators. As we learned in the prior chapter, function and class decorators allow us to intercept and augment function calls and class instance creation calls. In a similar spirit, metaclasses allow us to intercept and augment class creation—they provide an API for inserting extra logic to be run at the conclusion of a class statement, albeit in different ways than decorators. Accordingly, they provide a general protocol for managing class objects in a program.  

## To Metaclass or Not to Metaclass  

In other words, metaclasses are primarily intended for a subset of programmers building APIs and tools for others to use. In many (if not most) cases, they are probably not the best choice in applications work.  

Probably the reason for studying metaclasses most relevant to this book is that this topic can help demystify Python’s class mechanics in general. For instance, we’ll see that they are an intrinsic part of the language’s new-style inheritance model finally formalized in full here. Although you may or may not code or reuse them in your work, a cursory understanding of metaclasses can impart a deeper understanding of Python at large.   

### Increasing Levels of “Magic” 

However, in this book we’ve also seen a variety of tools that allow us to control Python’s behavior in generic ways, and that often have more to do with Python internals or tool building than with application -programming domains. As a review, and to help us place metaclasses in the tools spectrum:   

- Introspection attributes and tools  
- Operator overloading methods  
- Attribute interception methods  
- Class properties  
- Class attribute descriptors  
- Function and class decorators  
- Metaclasses  

As mentioned in this chapter’s introduction, metaclasses are a continuation of this story—they allow us to insert logic to be run automatically at the end of a class statement, when a class object is being created. Though strongly reminiscent of class decorators, the metaclass mechanism doesn’t rebind the class name to a decorator callable’s result, but rather routes creation of the class itself to specialized logic. 

### A Language of Hooks

In other words, metaclasses are ultimately just another way to define automatically run code. As we’ll see in this chapter, class decorators and metaclasses can often be used interchangeably as well. By way of preview:

- Although class decorators are often used to manage instances, they can also be used to manage classes instead, much like metaclasses.
- Similarly, while metaclasses are designed to augment class construction, they can also insert proxies to manage instances instead, much like class decorators. 

In fact, the main functional difference between these two tools is simply their place in the timing of class creation.  class decorators run after the decorated class has already been created. Thus, they are often used to add logic to be run at instance creation time.  metaclasses, by contrast, run during class creation to make and return the new client class. Therefore, they are often used for managing or augmenting classes themselves, and can even provide methods to process the classes that are created from them, via a direct instance relationship. 

### The Downside of “Helper” Functions

To illustrate, suppose we want to automatically insert a method into a set of classes. Of course, we could do this with simple inheritance, if the subject method is known when we code the classes. In that case, we can simply code the method in a superclass and have all the classes in question inherit from it:  

```python
class Extras:
    def extra(self, args): # Normal inheritance: too static
        ...

class Client1(Extras): ... # Clients inherit extra methods
class Client2(Extras): ...
class Client3(Extras): ...

X = Client1() # Make an instance
X.extra() # Run the extra methods
```

```python
def extra(self, arg): ...
    def extras(Class): # Manager function: too manual
        if required():
        Class.extra = extra

class Client1: ...
extras(Client1)

class Client2: ...
extras(Client2)

class Client3: ...
extras(Client3)

X = Client1()
X.extra()
```

Although manager functions like this one can achieve our goal here, they still put a fairly heavy burden on class coders, who must understand the requirements and adhere to them in their code. It would be better if there was a simple way to enforce the augmentation in the subject classes, so that they don’t need to deal with the augmentation so explicitly, and would be less likely to forget to use it altogether. In other words, we’d like to be able to insert some code to run automatically at the end of a class statement, to augment the class.  

This is exactly what metaclasses do—by declaring a metaclass, we tell Python to route the creation of the class object to another class we provide:  

```python
def extra(self, arg): ...
    class Extras(type):
        def __init__(Class, classname, superclasses, attributedict):
            if required():
                Class.extra = extra

class Client1(metaclass=Extras): ... # Metaclass declaration only (3.X form)
class Client2(metaclass=Extras): ... # Client class is instance of meta
class Client3(metaclass=Extras): ...

X = Client1() # X is instance of Client1
X.extra()
```

Because Python invokes the metaclass automatically at the end of the class statement when the new class is created, it can augment, register, or otherwise manage the class as needed. 

### Metaclasses Versus Class Decorators: Round 1  

Having said that, it’s also important to note that the class decorators described in the preceding chapter sometimes overlap with metaclasses—in terms of both utility and benefit. Although they are often used for managing instances, class decorators can also augment classes, independent of any created instances.

That is, class decorators can apply extra logic to classes, not just instances, at class creation time:  

```python
def extra(self, arg): ...
    def extras(Class):
        if required():
            Class.extra = extra
    return Class

@extras
class Client1: ... # Client1 = extras(Client1)

@extras
class Client2: ... # Rebinds class independent of instances

@extras
class Client3: ...

X = Client1() # Makes instance of augmented class
X.extra() # X is instance of original Client1
```

Decorators essentially automate the prior example’s manual name rebinding here. Just as for metaclasses, because this decorator returns the original class, instances are made from it, not from a wrapper object. In fact, instance creation is not intercepted at all in this example. 

## The Metaclass Model

To understand metaclasses, you first need to understand a bit more about Python’s type model and what happens at the end of a class statement. As we’ll see here, the two are intimately related

### Classes Are Instances of type

So far in this book, we’ve done most of our work by making instances of built-in types like lists and strings, as well as instances of classes we code ourselves. As we’ve seen, instances of classes have some state information attributes of their own, but they also inherit behavioral attributes from the classes from which they are made. The same holds true for built-in types; list instances, for example, have values of their own, but they inherit methods from the list type.  

Really, there’s a hole in the model we’ve seen thus far: if instances are created from classes, what is it that creates our classes? It turns out that classes are instances of something, too:

- In Python 3.X, user-defined class objects are instances of the object named type, which is itself a class.
- In Python 2.X, new-style classes inherit from object, which is a subclass of type; classic classes are instances of type and are not created from a class. 

Recall that the type built-in returns the type of any object (which is itself an object) when called with a single argument. For built-in types like lists, the type of the instance is the built-in list type, but the type of the list type is the type **type** itself—the type object at the top of the hierarchy creates specific types, and specific types create instances.  

```python
C:\code> py −3 # In 3.X:
>>> type([]), type(type([])) # List instance is created from list class
(<class 'list'>, <class 'type'>) # List class is created from type class
>>> type(list), type(type) # Same, but with type names
(<class 'type'>, <class 'type'>) # Type of type is type: top of hierarchy
```

As it happens, the type/instance relationship holds true for user-defined classes as well: instances are created from classes, and classes are created from type. In Python 3.X, though, the notion of a “type” is merged with the notion of a “class.” In fact, the two are essentially synonyms—classes are types, and types are classes. That is: 

- Types are defined by classes that derive from type.
- User-defined classes are instances of type classes.
- User-defined classes are types that generate instances of their own.

For example, all user-defined classes in 3.X (and new-style classes in 2.X) are instances of the type class, and instance objects are instances of their classes; in fact, classes now have a `__class__` that links to type, just as an instance has a `__class__` that links to the class from which it was made:

```python
C:\code> py −3
>>> class C: pass # 3.X class object (new-style)
>>> X = C() # Class instance object
>>> type(X) # Instance is instance of class
<class '__main__.C'>
>>> X.__class__ # Instance's class
<class '__main__.C'>
>>> type(C) # Class is instance of type
<class 'type'>
>>> C.__class__ # Class's class is type
<class 'type'>
```

Notice especially the last two lines here—classes are instances of the type class, just as normal instances are instances of a user-defined class. This works the same for both built-ins and user-defined class types in 3.X.

### Metaclasses Are Subclasses of Type

And because classes are really instances of the type class,  creating classes from customized subclasses of type allows us to implement custom kinds of classes. In full detail, this all works out quite naturally—in 3.X, and in 2.X new-style classes: 

### Class Statement Protocol

We’ve already learned that when Python reaches a class statement, it runs its nested block of code to create its attributes—all the names assigned at the top level of the nested code block generate attributes in the resulting class object. These names are usually method functions created by nested defs, but they can also be arbitrary attributes assigned to create class data shared by all instances. 

Technically speaking, Python follows a standard protocol to make this happen: at the end of a class statement, and after running all its nested code in a namespace dictionary corresponding to the class’s local scope, Python calls the type object to create the class object like this:  

```python
class = type(classname, superclasses, attributedict)
```

The type object in turn defines a `__call__` operator overloading method that runs two other methods when the type object is called: 

```python
type.__new__(typeclass, classname, superclasses, attributedict)
type.__init__(class, classname, superclasses, attributedict)
```

The `__new__` method creates and returns the new class object, and then the `__init__` method initializes the newly created object.   

For example, given a class definition like the following for Spam:  

```python
class Eggs: ... # Inherited names here

class Spam(Eggs): # Inherits from Eggs
    data = 1 # Class data attribute
    def meth(self, arg): # Class method attribute
        return self.data + arg
```

Python will internally run the nested code block to create two attributes of the class (data and meth), and then call the type object to generate the class object at the end of the class statement: 

```python
Spam = type('Spam', (Eggs,), {'data': 1, 'meth': meth, '__module__': '__main__'})
```

##  Declaring Metaclasses

As we’ve just seen, classes are created by the type class by default. To tell Python to create a class with a custom metaclass instead, you simply need to declare a metaclass to intercept the normal instance creation call in a user-defined class. How you do so depends on which Python version you are using.  

### Declaration in 3.X 

In Python 3.X, list the desired metaclass as a keyword argument in the class header:

```python
class Spam(metaclass=Meta): # 3.X version (only)
```

Inheritance superclasses can be listed in the header as well. In the following, for example, the new class Spam inherits from superclass Eggs, but is also an instance of and is created by metaclass Meta:

```python
class Spam(Eggs, metaclass=Meta): # Normal supers OK: must list first
```

In this form, superclasses must be listed before the metaclass; in effect, the ordering rules used for keyword arguments in function calls apply here.    

### Declaration in 2.X

### Metaclass Dispatch in Both 3.X and 2.X

When a specific metaclass is declared per the prior sections’ syntax, the call to create the class object run at the end of the class statement is modified to invoke the metaclass instead of the type default:

```python
class = Meta(classname, superclasses, attributedict)
```

And because the metaclass is a subclass of type, the type class’s `__call__` delegates the calls to create and initialize the new class object to the metaclass, if it defines custom versions of these methods:

```python
Meta.__new__(Meta, classname, superclasses, attributedict)
Meta.__init__(class, classname, superclasses, attributedict)    
```

If the metaclass defines its own versions of `__new__` or `__init__`, they will be invoked in turn during this call by the inherited type class’s `__call__` method, to create and initialize the new class. The net effect is to automatically run methods the metaclass provides, as part of the class construction process.    

## Coding Metaclasses

### A Basic Metaclass

```python
class Meta(type):
    def __new__(meta, classname, supers, classdict):
        # Run by inherited type.__call__
        return type.__new__(meta, classname, supers, classdict)
```

This metaclass doesn’t really do anything (we might as well let the default type class create the class), but it demonstrates the way a metaclass taps into the metaclass hook to customize—because the metaclass is called at the end of a class statement, and because the type object’s `__call__` dispatches to the `__new__` and `__init__` methods, code we provide in these methods can manage all the classes created from the metaclass.

```python
class MetaOne(type):
    def __new__(meta, classname, supers, classdict):
        print('In MetaOne.new:', meta, classname, supers, classdict, sep='\n...')
        return type.__new__(meta, classname, supers, classdict)

class Eggs:
    pass

print('making class')

class Spam(Eggs, metaclass=MetaOne): # Inherits from Eggs, instance of MetaOne
    data = 1 # Class data attribute
    def meth(self, arg): # Class method attribute
        return self.data + arg

print('making instance')
X = Spam()
print('data:', X.data, X.meth(2))
```

When this code is run with Python 3.X, notice how the metaclass is invoked at the end of the class statement, before we ever make an instance—metaclasses are for processing classes, and classes are for processing normal instances: 

```python
c:\code> py −3 metaclass1.py
making class
In MetaOne.new:
...<class '__main__.MetaOne'>
...Spam
...(<class '__main__.Eggs'>,)
...{'data': 1, 'meth': <function Spam.meth at 0x02A191E0>, '__module__': '__main__'}
making instance
data: 1 3
```

### Customizing Construction and Initialization

```python
class MetaTwo(type):
    def __new__(meta, classname, supers, classdict):
        print('In MetaTwo.new: ', classname, supers, classdict, sep='\n...')
        return type.__new__(meta, classname, supers, classdict)
    def __init__(Class, classname, supers, classdict):
        print('In MetaTwo.init:', classname, supers, classdict, sep='\n...')
        print('...init class object:', list(Class.__dict__.keys()))

class Eggs:
    pass

print('making class')

class Spam(Eggs, metaclass=MetaTwo): # Inherits from Eggs, instance of MetaTwo
    data = 1 # Class data attribute
    def meth(self, arg): # Class method attribute
        return self.data + arg

print('making instance')
X = Spam()
print('data:', X.data, X.meth(2))       
```

```python
c:\code> py −3 metaclass2.py
making class
In MetaTwo.new:
...Spam
...(<class '__main__.Eggs'>,)
...{'data': 1, 'meth': <function Spam.meth at 0x02967268>, '__module__': '__main__'}
In MetaTwo.init:
...Spam
...(<class '__main__.Eggs'>,)
...{'data': 1, 'meth': <function Spam.meth at 0x02967268>, '__module__': '__main__'}
...init class object: ['__qualname__', 'data', '__module__', 'meth', '__doc__']
making instance
data: 1 3
```



## 参考：

learning python （python学习手册）