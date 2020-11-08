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

### try Statement Clauses  

Formally, there may be any number of except clauses, but you can code else only if there is at least one except, and there can be only one else and one finally.  Table 34-1. try statement clause forms

- except: Catch all (or all other) exception types.
- except name: Catch a specific exception only.
- except name as value: Catch the listed exception and assign its instance.
- except (name1, name2): Catch any of the listed exceptions.
- except (name1, name2) as value: Catch any listed exception and assign its instance.
- else: Run if no exceptions are raised in the try block.
- finally: Always perform this block on exit.   

Here’s an example of multiple except clauses at work, which demonstrates just how specific your handlers can be:  

```python
try:
    action()
except NameError:
    ...
except IndexError:
    ...
except KeyError:
    ...
except (AttributeError, TypeError, SyntaxError):
    ...
else:
    ...
```

In this example, if an exception is raised while the call to the action function is running, Python returns to the try and searches for the first except that names the exception raised. It inspects the except clauses from top to bottom and left to right, and runs the statements under the first one that matches. If none match, the exception is propagated past this try. Note that the else runs only when no exception occurs in action—it does not run when an exception without a matching except is raised.  

If you really want a general “catchall” clause, an empty except does the trick:  

```python
try:
    action()
except NameError:
    ... # Handle NameError
except IndexError:
    ... # Handle IndexError
except:
    ... # Handle all other exceptions
else:
    ... # Handle the no-exception case
```

Empty excepts also raise some design issues, though. Although convenient, they may catch unexpected system exceptions unrelated to your code, and they may inadvertently intercept exceptions meant for another handler.   

### The try else Clause  

```python
try:
    ...run code...
except IndexError:
    ...handle exception...
else:
    ...no exception occurred...
```

## The try/finally Statement  

```python
try:
    statements # Run this action first
finally:
    statements # Always run this code on the way out
```

## The raise Statement  

Their general form is simple—a raise statement consists of the word raise, optionally followed by the class
to be raised or an instance of it:  

```python
raise instance # Raise instance of class
raise class # Make and raise instance of class: makes an instance
raise # Reraise the most recent exception
```

If we pass a class instead, Python calls the class with no constructor arguments, to create an instance to be raised; The last form reraises the most recently raised exception; it’s commonly used in exception handlers to propagate exceptions that have been caught.    

### Raising Exceptions  

With built-in exceptions, the following two forms are equivalent—both raise an instance of the exception class named, but the first creates the instance implicitly:  

```python
raise IndexError # Class (instance created)
raise IndexError() # Instance (created in statement)
```

because the raise statement accepts any kind of object reference, the following two examples raise IndexError just like the prior two:  

```python
exc = IndexError() # Create instance ahead of time
raise exc
excs = [IndexError, TypeError]
raise excs[0]
```

When an exception is raised, Python sends the raised instance along with the exception.

This model works the same for user-defined exceptions we code with classes—the following, for example, passes to the exception class constructor arguments that become available in the handler through the assigned instance:

```python
class MyExc(Exception): pass
    ...
raise MyExc('spam') # Exception class with constructor args
...
try:
    ...
except MyExc as X: # Instance attributes available in handler
    print(X.args)
```

### Scopes and try except Variables  

In Python 2.X, the exception reference variable name in an except clause is not localized to the clause itself, and is available after the associated block runs: 

```python
c:\code> py −2
>>> try:
...     1 / 0
... except Exception as X: # 2.X does not localize X either way
...     print X
...
integer division or modulo by zero
>>> X
ZeroDivisionError('integer division or modulo by zero',)
```

By contrast, Python 3.X localizes the exception reference name to the except block—the variable is not available after the block exits  

```python
c:\code> py −3
>>> try:
...     1 / 0
... except Exception, X:
SyntaxError: invalid syntax
>>> try:
...     1 / 0
... except Exception as X: # 3.X localizes 'as' names to except block
...     print(X)
...
division by zero
>>> X
NameError: name 'X' is not defined
```

Unlike compression loop variables, though, this variable is removed after the except block exits in 3.X.   

```python
>>> X = 99
>>> try:
...     1 / 0
... except Exception as X: # 3.X localizes _and_ removes on exit!
...     print(X)
...
division by zero
>>> X
NameError: name 'X' is not defined

>>> X = 99
>>> {X for X in 'spam'} # 2.X/3.X localizes only: not removed
{'s', 'a', 'p', 'm'}
>>> X
99
```

If you do need to reference the exception instance after the try statement, simply assign it to another name that won’t be automatically removed:

```python
>>> try:
...     1 / 0
... except Exception as X: # Python removes this reference
...     print(X)
... Saveit = X # Assign exc to retain exc if needed
...
division by zero
>>> X
NameError: name 'X' is not defined
>>> Saveit
ZeroDivisionError('division by zero',)
```

### Propagating Exceptions with raise  

```
>>> try:
...     raise IndexError('spam') # Exceptions remember arguments
... except IndexError:
...     print('propagating')
...     raise # Reraise most recent exception
...
propagating
Traceback (most recent call last):
  File "<stdin>", line 2, in <module>
IndexError: spam
```

Running a raise this way reraises the exception and propagates it to a higher handler.

### Python 3.X Exception Chaining: raise from  

Python 3.X (but not 2.X) also allows raise statements to have an optional from clause:  

```python
raise newexception from otherexception
```

When the from is used in an explicit raise request, the expression following from specifies another exception class or instance to attach to the __cause__ attribute of the new exception being raised. If the raised exception is not caught, Python prints both exceptions as part of the standard error message:  

```python
>>> try:
...     1 / 0
... except Exception as E:
...     raise TypeError('Bad') from E # Explicitly chained exceptions
...
Traceback (most recent call last):
  File "<stdin>", line 2, in <module>
ZeroDivisionError: division by zero
The above exception was the direct cause of the following exception:
Traceback (most recent call last):
  File "<stdin>", line 4, in <module>
TypeError: Bad
```

When an exception is raised implicitly by a program error inside an exception handler, a similar procedure is followed automatically: the previous exception is attached to the new exception’s `__context__` attribute and is again displayed in the standard error message if the exception goes uncaught:  

```python
>>> try:
...     1 / 0
... except:
...     badname # Implicitly chained exceptions
...
Traceback (most recent call last):
  File "<stdin>", line 2, in <module>
ZeroDivisionError: division by zero
    
During handling of the above exception, another exception occurred:
    
Traceback (most recent call last):
  File "<stdin>", line 4, in <module>
NameError: name 'badname' is not defined
```

In both cases, because the original exception objects thus attached to new exception objects may themselves have attached causes, the causality chain can be arbitrary long, and is displayed in full in error messages. That is, error messages might give more than two exceptions. The net effect in both explicit and implicit contexts is to allow programmers to know all exceptions involved, when one exception triggers another:  

```python
>>> try:
...     try:
...         raise IndexError()
...     except Exception as E:
...         raise TypeError() from E
... except Exception as E:
...     raise SyntaxError() from E
...
Traceback (most recent call last):
  File "<stdin>", line 3, in <module>
IndexError

The above exception was the direct cause of the following exception:
    
Traceback (most recent call last):
File "<stdin>", line 5, in <module>
  TypeError
    
The above exception was the direct cause of the following exception:
    
Traceback (most recent call last):
  File "<stdin>", line 7, in <module>
SyntaxError: None
```

## The assert Statement  