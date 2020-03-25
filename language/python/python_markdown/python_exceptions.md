# Part VII Exceptions and Tools  

# Exception Basics  

- try/except: Catch and recover from exceptions raised by Python, or by you.
- try/finally: Perform cleanup actions, whether exceptions occur or not.
- raise: Trigger an exception manually in your code.
- assert: Conditionally trigger an exception in your code.
- with/as: Implement context managers in Python 2.6, 3.0, and later (optional in 2.5).  

## Exceptions: The Short Story  

Compared to some other core language topics we’ve met in this book, exceptions are a fairly lightweight tool in Python. Because they are so simple, let’s jump right into some code.  

### User-Defined Exceptions  

User-defined exceptions are coded with classes, which inherit from a built-in exception class: usually
the class named Exception:  

```python
>>> class AlreadyGotOne(Exception): pass # User-defined exception

>>> def grail():
        raise AlreadyGotOne() # Raise an instance
        
>>> try:
...     grail()
... except AlreadyGotOne: # Catch class name
...     print('got exception')
...
got exception
>>>
```

They can also customize their error message text displayed if they’re not caught:  

```python
>>> class Career(Exception):
        def __str__(self): return 'So I became a waiter...'
        
>>> raise Career()
Traceback (most recent call last):
File "<stdin>", line 1, in <module>
__main__.Career: So I became a waiter...
>>>
```

# Exception Coding Details  

In the prior chapter we took a quick look at exception-related statements in action. Here, we’re going to dig a bit deeper—this chapter provides a more formal introduction to exception processing syntax in Python.  

## The try/except/else Statement  

Syntactically, the try is a compound, multipart statement. It starts with a try header line, followed by a block of (usually) indented statements; then one or more except clauses that identify exceptions to be caught and blocks to process them; and an optional else clause and block at the end.  For reference, here’s the general and most complete format in Python 3.X:

```python
try:
    statements # Run this main action first
except name1:
    statements # Run if name1 is raised during try block
except (name2, name3):
    statements # Run if any of these exceptions occur
except name4 as var:
    statements # Run if name4 is raised, assign instance raised to var
except:
    statements # Run for all other exceptions raised
else:
    statements # Run if no exception was raised during try block
```

### How try Statements Work    

