'''
http://www.liaoxuefeng.com/wiki/001374738125095c955c1e6d8bb493182103fac9270762a000/001386832284796780f5db7b5744bf9989f8d845ef77712000 
循序渐进学Python 9.异常处理 http://www.cnblogs.com/IPrograming/p/Python_error_handler.html


----> What Is an Exception?
To represent exceptional conditions, Python uses exception objects. When it encounte-
rs an error, it raises an exception. If such an exception object is not handled (or -
caught), the program terminates with a so-called traceback (an error message):
>>> 1/0
Traceback (most recent call last):
File "<stdin>", line 1, in ?
ZeroDivisionError: integer division or modulo by zero

each exception is an instance of some class (in this case ZeroDivisionError), and th-
ese instances may be raised and caught in various ways, allowing you to trap the err-
or and do something about it instead of just letting the entire program fail.


----> Catching Exceptions
--------------------------------------------
try:
    x = input('Enter the first number: ')
    y = input('Enter the second number: ')
    print x/y
except ZeroDivisionError:
    print "The second number can't be zero!"
except TypeError:
    print "That wasn't a number, was it?"

try:
    x = input('Enter the first number: ')
    y = input('Enter the second number: ')
    print x/y
except (ZeroDivisionError, TypeError, NameError):
    print 'Your numbers were bogus...'	
--------------------------------------------
Exceptions propagate out of functions to where they’re called, and if they’re not ca-
ught there either, the exceptions will "bubble up" to the top level of the program. -
This means that you can use try/except to catch exceptions that are raised in other -
people’s functions. 

--------------------------------------------
try:
    print 'try...'
    r = 10 / 0
    print 'result:', r
except ZeroDivisionError, e:
    print 'except:', e
finally:
    print 'finally...'
print 'END'
--------------------------------------------                                         |
当我们认为某些代码可能会出错时，就可以用try来运行这段代码，如果执行出错，则后续代码不|
会继续执行，而是直接跳转至错误处理代码，即except语句块，执行完except后，如果有finally|
语句块，则执行finally语句块，至此，执行完毕。上面的代码在计算10 / 0时会产生一个除法运|
算错误。可以有多个except来捕获不同类型的错误：                                       |
--------------------------------------------
try:
    print 'try...'
    r = 10 / int('a')
    print 'result:', r
except ValueError, e:
    print 'ValueError:', e
except ZeroDivisionError, e:
    print 'ZeroDivisionError:', e
finally:
    print 'finally...'
print 'END'
--------------------------------------------                                         |
int()函数可能会抛出ValueError，所以我们用一个except捕获ValueError，用另一个except捕获|
ZeroDivisionError。此外，如果没有错误发生，可以在except语句块后面加一个else，当没有错|
误发生时，会自动执行else语句：                                                       |
--------------------------------------------  
try:
    print 'try...'
    r = 10 / int('a')
    print 'result:', r
except ValueError, e:
    print 'ValueError:', e
except ZeroDivisionError, e:
    print 'ZeroDivisionError:', e
else:
    print 'no error!'
finally:
    print 'finally...'
print 'END'
--------------------------------------------                                         |
Python的错误其实也是class，所有的错误类型都继承自BaseException，所以在使用except时需 |
要注意的是，它不但捕获该类型的错误，还把其子类也“一网打尽”。比如：                   |

try:
    foo()
except StandardError, e:
    print 'StandardError'
except ValueError, e:
    print 'ValueError'
                                                                                     |
第二个except永远也捕获不到ValueError，因为ValueError是StandardError的子类，如果有，也|
被第一个except给捕获了。Python所有的错误都是从BaseException类派生的，常见的错误类型和|
继承关系看这里：                                                                     |
https://docs.python.org/2/library/exceptions.html#exception-hierarchy                |
                                                                                     |
使用try...except捕获错误还有一个巨大的好处，就是可以跨越多层调用，比如函数main()调用 |
foo()，foo()调用bar()，结果bar()出错了，这时，只要main()捕获到了，就可以处理：       |

def foo(s):
    return 10 / int(s)

def bar(s):
    return foo(s) * 2

def main():
    try:
        bar('0')
    except StandardError, e:
        print 'Error!'
    finally:
        print 'finally...'
                                                                                     |
也就是说，不需要在每个可能出错的地方去捕获错误，只要在合适的层次去捕获错误就可以了。 |
这样一来，就大大减少了写try...except...finally的麻烦。如果错误没有被捕获，它就会一直 |
往上抛，最后被Python解释器捕获，打印一个错误信息，然后程序退出。来看看err.py：       |

err.py (an example)
 -------------------------------------------- 
 # err.py:                            0
 def foo(s):                         # 1
     return 10 / int(s)

 def bar(s):
     return foo(s) * 2
 
 def main():
     bar('0')

 main()                             # 11
 -------------------------------------------- 
 执行，结果如下：
 $ python err.py
 Traceback (most recent call last):
   File "err.py", line 11, in <module>
     main()
   File "err.py", line 9, in main
     bar('0')
   File "err.py", line 6, in bar
     return foo(s) * 2
   File "err.py", line 3, in foo
     return 10 / int(s)
 ZeroDivisionError: integer division or modulo by zero
                                                                                      |
 出错并不可怕，可怕的是不知道哪里出错了。解读错误信息是定位错误的关键。我们从上往下可 |
 以看到整个错误的调用函数链：
 
 错误信息第1行：
 Traceback (most recent call last):
 告诉我们这是错误的跟踪信息。
 
 第2行：
   File "err.py", line 11, in <module>
     main()
 调用main()出错了，在代码文件err.py的第11行代码，但原因是第9行：
 
   File "err.py", line 9, in main
     bar('0')
 调用bar('0')出错了，在代码文件err.py的第9行代码，但原因是第6行：
 
   File "err.py", line 6, in bar
     return foo(s) * 2
 原因是return foo(s) * 2这个语句出错了，但这还不是最终原因，继续往下看：
 
   File "err.py", line 3, in foo
     return 10 / int(s)
 原因是return 10 / int(s)这个语句出错了，这是错误产生的源头，因为下面打印了：
 
 ZeroDivisionError: integer division or modulo by zero                                |
 根据错误类型ZeroDivisionError，我们判断，int(s)本身并没有出错，但是int(s)返回0，在计 |
 算10 / 0时出错，至此，找到错误源头。

----> 记录错误
                                                                                      |
 如果不捕获错误，自然可以让Python解释器来打印出错误堆栈，但程序也被结束了。既然我们能 |
 捕获错误，就可以把错误堆栈打印出来，然后分析错误原因，同时，让程序继续执行下去。     |
 Python内置的logging模块可以非常容易地记录错误信息：                                  |
 -------------------------------------------- 
 # err.py
 import logging 
 
 def foo(s):
     return 10 / int(s)
 
 def bar(s):
     return foo(s) * 2
 
 def main():
     try:
         bar('0')
     except StandardError, e:
         logging.exception(e)
 
 main()
 print 'END'
 -------------------------------------------- 
 
 同样是出错，但程序打印完错误信息后会继续执行，并正常退出：
 
 $ python err.py
 ERROR:root:integer division or modulo by zero
 Traceback (most recent call last):
   File "err.py", line 12, in main
     bar('0')
   File "err.py", line 8, in bar
     return foo(s) * 2
   File "err.py", line 5, in foo
     return 10 / int(s)
 ZeroDivisionError: integer division or modulo by zero
 END
 
 通过配置，logging还可以把错误记录到日志文件里，方便事后排查。
                                                                                     |
																					 
----> 抛出错误                                                                       |
 exception_rasie_eg.py

----> 最后，我们来看另一种错误处理的方式：
 -------------------------------------------- 
 # err.py
 def foo(s):
     n = int(s)
     return 10 / n
 
 def bar(s):
     try:
         return foo(s) * 2
     except StandardError, e:
         print 'Error!'
         raise
 
 def main():
     bar('0')
 
 main()
 -------------------------------------------- 
                                                                                      |
 在bar()函数中，我们明明已经捕获了错误，但是，打印一个Error!后，又把错误通过raise语句 |
 抛出去了，这不有病么？ 其实这种错误处理方式不但没病，而且相当常见。捕获错误目的只是记|
 录一下，便于后续追踪。但是，由于当前函数不知道应该怎么处理该错误，所以，最恰当的方式 |
 是继续往上抛，让顶层调用者去处理。raise语句如果不带参数，就会把当前错误原样抛出。此外|
 ，在except中raise一个Error，还可以把一种类型的错误转化成另一种类型：                 |
 
 try:
     10 / 0
 except ZeroDivisionError:
     raise ValueError('input error!')

 只要是合理的转换逻辑就可以，但是，决不应该把一个IOError转换成毫不相干的ValueError。

'''

BaseException (6.1. Exception hierarchy. The class hierarchy for built-in exceptions is:
 +-- SystemExit
 +-- KeyboardInterrupt
 +-- GeneratorExit
 +-- Exception
      +-- StopIteration
      +-- StandardError
      |    +-- BufferError
      |    +-- ArithmeticError
      |    |    +-- FloatingPointError
      |    |    +-- OverflowError
      |    |    +-- ZeroDivisionError
      |    +-- AssertionError
      |    +-- AttributeError
      |    +-- EnvironmentError
      |    |    +-- IOError
      |    |    +-- OSError
      |    |         +-- WindowsError (Windows)
      |    |         +-- VMSError (VMS)
      |    +-- EOFError
      |    +-- ImportError
      |    +-- LookupError
      |    |    +-- IndexError
      |    |    +-- KeyError
      |    +-- MemoryError
      |    +-- NameError
      |    |    +-- UnboundLocalError
      |    +-- ReferenceError
      |    +-- RuntimeError
      |    |    +-- NotImplementedError
      |    +-- SyntaxError
      |    |    +-- IndentationError
      |    |         +-- TabError
      |    +-- SystemError
      |    +-- TypeError
      |    +-- ValueError
      |         +-- UnicodeError
      |              +-- UnicodeDecodeError
      |              +-- UnicodeEncodeError
      |              +-- UnicodeTranslateError
      +-- Warning
           +-- DeprecationWarning
           +-- PendingDeprecationWarning
           +-- RuntimeWarning
           +-- SyntaxWarning
           +-- UserWarning
           +-- FutureWarning
	   +-- ImportWarning
	   +-- UnicodeWarning
	   +-- BytesWarning




