# Part--Advanced Topics  

# Managed Attributes  

This chapter expands on the attribute interception techniques introduced earlier, introduces another, and employs them in a handful of larger examples.  

## Why Manage Attributes?

##    

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



## 参考：

learning python （python学习手册）