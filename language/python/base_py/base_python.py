introduction
setup

operators
types
file_io
function
module
class
namespace

object






--> primary prompt, secondary prompt
 In all interactive examples, you will see the Python primary ( >>> ) and secondary -
 ( ... ) prompts. The primary prompt is a way for the interpreter to let you know th-
 at it is expecting the next Python statement, while the secondary prompt indicates -
 that the interpreter is waiting for additional input to complete the current statem-
 ent.
 
 
Functions that do not explicitly
return a value by the programmer automatically return None

--> print
 





----> 模块和包
 module_py.py

----> 命令空间
 在python模块中讲述

----> 文件操作
 文件基本概念放在 file_objects_py.py
 关于python文件操作 http://www.cnblogs.com/rollenholt/archive/2012/04/23/2466179.html

 fileinput: Iterate over lines from multiple input streams

 file_io_py.py

----> 文件系统
 os
 os.path

----> 多线程
 thread_pylib_eg.py

 
--> 基础知识
 在python程序里面我们经常需要对文件进行操作，Windows下的文件目录路径使用反斜杠“\”来分隔。但是，和大多数语言一样，Python代码里面，反斜杠“\”是转义符，例如“\n”表示回车、“\t”表示制表符等等。这样，如果继续用windows习惯使用“\”表示文件路径，就会产生歧义。
      例如：“c:\test.txt”这表示c盘根目录下的一个文件，还是表示一个字符串呢？因为“\t”也可以解释为制表符。如果让我们人来判断，这当然是一个很简单的问题。但是机器就无法做出正确的判断了，只有没有歧义的代码机器才会正确执行。
      解决办法，采用下面任何一种书写形式均可：
使用斜杠“/”: "c:/test.txt"… 不用反斜杠就没法产生歧义了 
将反斜杠符号转义: "c:\\test.txt"… 因为反斜杠是转义符，所以两个"\\"就表示一个反斜杠符号 
使用Python的raw string: r"c:\test.txt" … python下在字符串前面加上字母r，表示后面是一个原始字符串raw string，不过raw string主要是为正则表达式而不是windows路径设计的，所以这种做法尽量少用，可能会出问题。 
 
 
 
 
PEP
 http://legacy.python.org/dev/peps/

universal newlines
    A manner of interpreting text streams in which all of the following are recogniz-
	ed as ending a line: the Unix end-of-line convention '\n', the Windows convention 
	'\r\n', and the old Macintosh convention '\r'. See PEP 278 and PEP 3116, as  well 
	as str.splitlines() for an additional use.

http://www.zhihu.com/question/20670869   工厂函数






? Hash mark ( # ) indicates Python comments
? NEWLINE ( \n ) is the standard line separator (one statement per line)
? Backslash ( \ ) continues a line
? Semicolon ( ; ) joins two statements on a line
? Colon ( : ) separates a header line from its suite
? Statements (code blocks) grouped as suites

Suites delimited via indentation
Code that is not indented, i.e., the highest level of code, is considered the  “main” 
portion of the script.

? Python files organized as modules

--> None
 None是一个特殊的常量。
 None和False不同。
 None不是0。
 None不是空字符串。
 None和任何其他的数据类型比较永远返回False。
 None有自己的数据类型NoneType。
 你可以将None复制给任何变量，但是你不能创建其他NoneType对象。
 >>> type(None)  
 <class 'NoneType'>
 >>> None == 0
 False  
 >>> None == ''  
 False  
 >>> None == None  
 True  
 >>> None == False  
 False  

variable assignment
  The equal sign ( = ) is the main Python assignment operator. (The others are augme-
  nted assignment operator)
  anInt = -12
  In Python, objects are referenced, so on assignment, a reference (not a value) to -
  an object is what is being assigned, whether the object was just created or was a -
  pre-existing object. 
  Also, if you are familiar with C, you know that assignments are treated as express-
  ions. This is not the case in Python, where assignments do not have inherent value-
  s. Statements such as the following are invalid in Python:
  >>> x = 1
  >>> y = (x = x + 1) # assignments not expressions!
  File "<stdin>", line 1
  y = (x = x + 1)
  ^
  SyntaxError: invalid syntax
  Chaining together assignments is okay, though (more on this later):
  >>> y = x = x + 1
  >>> x, y
  (2, 2)  
  
  Augmented Assignment
  Beginning in Python 2.0, the equal sign can be combined with an arithmetic operati-
  on and the resulting value reassigned to the existing variable. Known as  augmented 
  assignment, statements such as . . .
  x = x + 1
  . . . can now be written as . . .
  x += 1
  Python does not support pre-/post-increment nor pre-/post-decrement operators  such 
  as x++ or --x.
  
  Multiple Assignment
  >>> x = y = z = 1
  >>> x
  1
  >>> y
  1
  >>> z
  1
  In the above example, an integer object (with the value 1) is created, and x, y, a-
  nd z are all assigned the same reference to that object. This is the process of as-
  signing a single object to multiple variables. It is also possible in Python to as-
  sign multiple objects to multiple variables.
  
  “Multuple” Assignment
  Another way of assigning multiple variables is using what we shall call the “multu-
  ple” assignment. This is not an official Python term, but we use “multuple” here b-
  ecause when assigning variables this way, the objects on both sides of the equal s-
  ign are tuples
  >>> x, y, z = 1, 2, 'a string'
  >>> x
  1
  >>> y
  2
  >>> z
  'a string'
  Parentheses are normally used to denote tuples, and although they are optional,  we 
  recommend them anywhere they make the code easier to read:
  >>> (x, y, z) = (1, 2, 'a string')
  
  One interesting side effect of Python’s “multuple” assignment is that we no  longer 
  need a temporary variable to swap the values of two variables.
  # swapping variables in Python
  >>> x, y = 1, 2
  >>> x
  1
  >>> y
  2
  >>> x, y = y, x
  >>> x
  2
  >>> y
  1
  Obviously, Python performs evaluation before making assignments.

Identifiers  
  Identifiers are the set of valid strings that are allowed as names in a computer l-
  anguage. The rules for Python identifier strings are like most other high-level pr-
  ogramming languages that come from the C world:
  ? First character must be a letter or underscore ( _ )
  ? Any additional characters can be alphanumeric or underscore
  ? Case-sensitive
  
  Keywords
  Built-ins
  
  Special Underscore Identifiers
  ? _xxx Do not import with 'from module import *'
  ? __xxx__ System-defined name
  ? __xxx Request private name mangling in classes
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  




















