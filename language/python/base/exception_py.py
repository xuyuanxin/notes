'''
http://www.liaoxuefeng.com/wiki/001374738125095c955c1e6d8bb493182103fac9270762a000/001386832284796780f5db7b5744bf9989f8d845ef77712000 
ѭ�򽥽�ѧPython 9.�쳣���� http://www.cnblogs.com/IPrograming/p/Python_error_handler.html


----> Detecting and Handling Exceptions
 Exceptions can be detected by incorporating them as part of a @try statement. Any c-
 ode suite of a try statement will be monitored for exceptions. There are two main f-
 orms of the try statement: try-except and try-finally.
 -----------------------------------------------------
 try:
     try_suite
 except Exception1:
     suite_for_Exception1
 except (Exception2, Exception3, Exception4):
     suite_for_Exceptions_2_3_and_4
 except Exception5, Argument5:
     suite_for_Exception5_plus_argument
 except (Exception6, Exception7), Argument67:
     suite_for_Exceptions6_and_7_plus_argument
 except:
     suite_for_all_other_exceptions
 else:
     no_exceptions_detected_suite
 finally:
     always_execute_suite
 -----------------------------------------------------

 ----> try-except Statement
  |try:
  |    try_suite # watch for exceptions here
  |except Exception[, reason]:
  |    except_suite # exception-handling code
  |except (Exc1[, Exc2[, ... ExcN]])[, reason]:
  |    suite_for_exceptions_Exc1_to_ExcN
  The remaining code in the try suite from the point of the exception is never reach-
  ed (hence never executed). Once an exception is raised, the race is on to decide on 
  the continuing flow of control. The remaining code is skipped, and the search for a 
  handler begins. If one is found, the program continues in the handler. If the sear-
  ch is exhausted without finding an appropriate handler, the exception is then prop-
  agated to the caller��s level for handling, meaning the stack frame immediately pre-
  ceding the current one. If there is no handler at the next higher level, the excep-
  tion is yet again propagated to its caller. If the top level is reached without  an 
  appropriate handler, the exception is considered unhandled, and the Python interpr-
  eter will display the traceback and exit. 
  |def safe_float(obj):
  |    try:
  |        retval = float(obj)
  |    except ValueError:
  |        retval = 'could not convert non-number to float'
  |    except TypeError:
  |        retval = 'object type cannot be converted to float'
  |    return retval
  Running the code above with erroneous input, we get the following:
  >>> safe_float('xyz')
  'could not convert non-number to float'
  >>> safe_float(())
  'argument must be a string'
  >>> safe_float(200L)
  200.0
  >>> safe_float(45.67000)
  45.67 

  Catching All Exceptions 
  our code will look like this:
  |try:
  |    :
  |except Exception, e:
  |    # error occurred, log 'e', etc.
  Less preferred is the bare except clause:
  |try:
  |    :
  |except:
  |    # error occurred, etc. 
  One aspect of catching all exceptions that you need to be aware of is that there a-
  re several exceptions that are not due to an error condition. These two  exceptions 
  are SystemExit and KeyboardInterrupt. SystemExit is for when the current Python ap-
  plication wants to quit, and KeyboardInterrupt is when a user presses CTRL-C (^C) -
  to terminate Python. 
  |try:
  |    :
  |except (KeyboardInterupt, SystemExit):
  |    # user wants to quit
  |    raise # reraise back to caller
  |except Exception:
  |    # handle real errors
 
 ----> "Exceptional Arguments" 
  an exception may have an argument or reason passed along to the exception handler -
  when they are raised. Although reasons for exceptions are optional, the standard  -
  built-in exceptions do provide at least one argument, an error string indicating t-
  he cause of the exception.
  ------------------------------------------------------------
  # single exception
  except Exception[, reason]:
      suite_for_Exception_with_Argument
  # multiple exceptions
  except (Exception1, Exception2, ..., ExceptionN)[, reason]:
      suite_for_Exception1_to_ExceptionN_with_Argument
  ------------------------------------------------------------
  reason is a class instance containing diagnostic information from the code  raising 
  the exception. The exception arguments themselves go into a tuple that is stored as 
  an attribute of the class instance, an instance of the exception class from which -
  it was instantiated. In the first alternate syntax above, @reason is an instance of 
  the Exception class.

  The example below is when an invalid object is passed to the float() built-in func-
  tion, resulting in a TypeError exception:
  
  >>> try:
  ...     float(['float() does not', 'like lists', 2])
  ... except TypeError, diag:# capture diagnostic info
  ...     pass
  ...
  >>> type(diag)
  <class 'exceptions.TypeError'>
  >>>
  >>> print diag
  float() argument must be a string or a number
  
  The first thing we did was cause an exception to be raised from within the try sta-
  tement. Then we passed cleanly through by ignoring but saving the error informatio-
  n. Calling the type() built-in function, we were able to confirm that our exception 
  was indeed an instance of the TypeError exception class. Finally, we displayed  the 
  error by calling print with our diagnostic exception argument.
  To obtain more information regarding the exception,we can use the special __class__ 
  instance attribute, which identifies which class an instance was instantiated from. 
  Class objects also have attributes, such as a documentation string and a string na-
  me that further illuminate the error type:
  
  >>> diag # exception instance object
  <exceptions.TypeError instance at 8121378>
  >>> diag.__class__ # exception class object
  <class exceptions.TypeError at 80f6d50>
  >>> diag.__class__.__doc__ # exception class documentation string
  'Inappropriate argument type.'
  >>> diag.__class__.__name__ # exception class name
  'TypeError'
 ----> else Clause
  The else clause executes if no exceptions were detected in the preceding try suite.
  All code within the @try suite must have completed successfully (i.e., concluded w-
  ith no exceptions raised) before any code in the @else suite begins execution. Here 
  is a short example in Python pseudocode:
 ----> finally Clause
   A @finally clause is one where its suite or block of code is executed regardless -
   of whether an exception occurred or whether it was caught (or not). You may use  a 
   @finally clause with @try by itself or with try-except (with or without an @else -
   clause).

  try-finally Statement
  An alternative is to use @finally alone with @try. The try-finally statement diffe-
  rs from its try-except brethren in that it is not used to handle exceptions. Inste-
  ad it is used to maintain consistent behavior regardless of whether or not excepti-
  ons occur. We know that the @finally suite executes regardless of an exception bei-
  ng triggered within the @try suite.

----> raise  
 The raise statement allows the programmer to force a specified exception to occur. -
 For example:
 >>> raise NameError('HiThere')
 Traceback (most recent call last):
   File "<stdin>", line 1, in ?
 NameError: HiThere
 
 The sole argument to raise indicates the exception to be raised. This must be either 
 an exception instance or an exception class (a class that derives from Exception).

 If you need to determine whether an exception was raised but don��t intend to  handle 
 it, a simpler form of the raise statement allows you to re-raise the exception:
 >>> try:
 ...     raise NameError('HiThere')
 ... except NameError:
 ...     print 'An exception flew by!'
 ...     raise
 ...
 An exception flew by!
  Traceback (most recent call last):
   File "<stdin>", line 2, in ?
 NameError: HiThere


 
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
Exceptions propagate out of functions to where they��re called, and if they��re not ca-
ught there either, the exceptions will "bubble up" to the top level of the program. -
This means that you can use try/except to catch exceptions that are raised in other -
people��s functions. 

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
��������ΪĳЩ������ܻ����ʱ���Ϳ�����try��������δ��룬���ִ�г�����������벻|
�����ִ�У�����ֱ����ת����������룬��except���飬ִ����except�������finally|
���飬��ִ��finally���飬���ˣ�ִ����ϡ�����Ĵ����ڼ���10 / 0ʱ�����һ��������|
����󡣿����ж��except������ͬ���͵Ĵ���                                       |
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
int()�������ܻ��׳�ValueError������������һ��except����ValueError������һ��except����|
ZeroDivisionError�����⣬���û�д�������������except��������һ��else����û�д�|
����ʱ�����Զ�ִ��else��䣺                                                       |
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
Python�Ĵ�����ʵҲ��class�����еĴ������Ͷ��̳���BaseException��������ʹ��exceptʱ�� |
Ҫע����ǣ���������������͵Ĵ��󣬻���������Ҳ��һ���򾡡������磺                   |

try:
    foo()
except StandardError, e:
    print 'StandardError'
except ValueError, e:
    print 'ValueError'
                                                                                     |
�ڶ���except��ԶҲ���񲻵�ValueError����ΪValueError��StandardError�����࣬����У�Ҳ|
����һ��except�������ˡ�Python���еĴ����Ǵ�BaseException�������ģ������Ĵ������ͺ�|
�̳й�ϵ�����                                                                     |
https://docs.python.org/2/library/exceptions.html#exception-hierarchy                |
                                                                                     |
ʹ��try...except���������һ���޴�ĺô������ǿ��Կ�Խ�����ã����纯��main()���� |
foo()��foo()����bar()�����bar()�����ˣ���ʱ��ֻҪmain()�����ˣ��Ϳ��Դ���       |

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
Ҳ����˵������Ҫ��ÿ�����ܳ���ĵط�ȥ�������ֻҪ�ں��ʵĲ��ȥ�������Ϳ����ˡ� |
����һ�����ʹ�������дtry...except...finally���鷳���������û�б��������ͻ�һֱ |
�����ף����Python���������񣬴�ӡһ��������Ϣ��Ȼ������˳���������err.py��       |

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
 ִ�У�������£�
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
 ���������£����µ��ǲ�֪����������ˡ����������Ϣ�Ƕ�λ����Ĺؼ������Ǵ������¿� |
 �Կ�����������ĵ��ú�������
 
 ������Ϣ��1�У�
 Traceback (most recent call last):
 �����������Ǵ���ĸ�����Ϣ��
 
 ��2�У�
   File "err.py", line 11, in <module>
     main()
 ����main()�����ˣ��ڴ����ļ�err.py�ĵ�11�д��룬��ԭ���ǵ�9�У�
 
   File "err.py", line 9, in main
     bar('0')
 ����bar('0')�����ˣ��ڴ����ļ�err.py�ĵ�9�д��룬��ԭ���ǵ�6�У�
 
   File "err.py", line 6, in bar
     return foo(s) * 2
 ԭ����return foo(s) * 2����������ˣ����⻹��������ԭ�򣬼������¿���
 
   File "err.py", line 3, in foo
     return 10 / int(s)
 ԭ����return 10 / int(s)����������ˣ����Ǵ��������Դͷ����Ϊ�����ӡ�ˣ�
 
 ZeroDivisionError: integer division or modulo by zero                                |
 ���ݴ�������ZeroDivisionError�������жϣ�int(s)����û�г�������int(s)����0���ڼ� |
 ��10 / 0ʱ�������ˣ��ҵ�����Դͷ��

----> ��¼����
                                                                                      |
 ��������������Ȼ������Python����������ӡ�������ջ��������Ҳ�������ˡ���Ȼ������ |
 ������󣬾Ϳ��԰Ѵ����ջ��ӡ������Ȼ���������ԭ��ͬʱ���ó������ִ����ȥ��     |
 Python���õ�loggingģ����Էǳ����׵ؼ�¼������Ϣ��                                  |
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
 
 ͬ���ǳ����������ӡ�������Ϣ������ִ�У��������˳���
 
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
 
 ͨ�����ã�logging�����԰Ѵ����¼����־�ļ�������º��Ų顣
                                                                                     |
																					 
----> �׳�����                                                                       |
 exception_rasie_eg.py

----> �������������һ�ִ�����ķ�ʽ��
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
 ��bar()�����У����������Ѿ������˴��󣬵��ǣ���ӡһ��Error!���ְѴ���ͨ��raise��� |
 �׳�ȥ�ˣ��ⲻ�в�ô�� ��ʵ���ִ�����ʽ����û���������൱�������������Ŀ��ֻ�Ǽ�|
 ¼һ�£����ں���׷�١����ǣ����ڵ�ǰ������֪��Ӧ����ô����ô������ԣ���ǡ���ķ�ʽ |
 �Ǽ��������ף��ö��������ȥ����raise�����������������ͻ�ѵ�ǰ����ԭ���׳�������|
 ����except��raiseһ��Error�������԰�һ�����͵Ĵ���ת������һ�����ͣ�                 |
 
 try:
     10 / 0
 except ZeroDivisionError:
     raise ValueError('input error!')

 ֻҪ�Ǻ����ת���߼��Ϳ��ԣ����ǣ�����Ӧ�ð�һ��IOErrorת���ɺ�����ɵ�ValueError��

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




