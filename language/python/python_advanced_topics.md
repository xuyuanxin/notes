# Part--Advanced Topics  

# Decorators

This is a somewhat advanced topic, and decorator construction tends to be of more interest to tool builders than to application programmers. Still, given that decorators are becoming increasingly common in popular Python frameworks, a basic understanding can help demystify their role, even if you’re just a decorator user.    

## What’s a Decorator?  

Decoration is a way to specify management or augmentation code for functions and classes. Decorators themselves take the form of callable objects (e.g., functions) that process other callable objects. In short, decorators provide a way to insert automatically run code at the end of function and class definition statements--at the end of a def for function decorators, and at the end of a class for class decorators.  

## The Basics

### Function Decorators    

Function decorators have been available in Python since version 2.4. As we saw earlier in this book, they are largely just syntactic sugar that runs one function through another at the end of a def statement, and rebinds the original function name to the result.   

#### Usage  

## Coding Function Decorators

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



## 参考：

learning python （python学习手册）