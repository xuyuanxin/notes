
--> comments
 As with most scripting and Unix-shell languages, the hash or pound ( # ) sign signa-
 ls that a comment begins from the # and continues until the end of the line.
 >>> # one comment
 ... print 'Hello World!' # another comment
 Hello World!
 
 -->--> documentation strings
  There are special comments called documentation strings, or "doc strings" for shor-
  t. You can add a "comment" at the beginning of a module, class, or function  string 
  that serves as a doc string, a feature familiar to Java programmers:

  def foo():
    "This is a doc string."
    return True
  
  Unlike regular comments, however, doc strings can be accessed at runtime and be us-
  ed to automatically generate documentation.

--> operators
  xx
  
--> variables and Assignments
 variable are simply identifier names with an alphabetic first character—"alphabetic" 
 meaning upper or lowercase letters, including the underscore ( _ ). Any additional -
 characters may be alphanumeric or underscore. 

 Python is case-sensitive, meaning that the identifier "cAsE" is different from     -
 "CaSe."

 Python is dynamically typed, meaning that no pre-declaration of a variable or its t-
 ype is necessary. The type (and value) are initialized on assignment.

 Assignments are performed using the equal sign.
 >>> counter = 0
 >>> miles = 1000.0
 >>> name = 'Bob'

 Python also supports "augmented assignment", statements that both refer to and assi-
 gn values to variables. You can take the following expression . . .
 n = n * 10
 . . . and use this shortcut instead:
 n *= 10

 Python does not support increment and decrement operators like the ones in C: n++ o-
 r --n. Because + and - are also unary operators, Python will interpret --n as      -
 -(-n) == n, and the same is true for ++n.
 
 -->--> Assignment Operator
  The equal sign ( = ) is the main Python assignment operator.
  
  anInt = -12
  aString = 'cart'
  aFloat = -3.1415 * (5.0 ** 2)
  anotherString = 'shop' + 'ping'
  aList = [3.14e10, '2nd elmt of a list', 8.82-4.371j]
  
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

 -->--> Augmented Assignment
  Beginning in Python 2.0, the equal sign can be combined with an arithmetic operati-
  on and the resulting value reassigned to the existing variable. Known as  augmented 
  assignment, statements such as . .

  x = x + 1
  . . . can now be written as . . .
  x += 1

  +=  -=  *=  /=  %=  **=  <<=  >>=  &=  ^=  |=
  
  >>> m = 12
  >>> m %= 7
  >>> m
  5
  >>> m **= 2
  >>> m
  25
  >>> aList = [123, 'xyz']
  >>> aList += [45.6e7]
  >>> aList
  [123, 'xyz', 456000000.0]
 
 -->--> Multiple Assignment
  >>> x = y = z = 1
  >>> x
  1
  >>> y
  1
  >>> z
  1
  
  In the above example, an integer object (with the value 1) is created, and x, y,  -
  and z are all assigned the same reference to that object. This is the process of a-
  ssigning a single object to multiple variables. It is also possible in Python to a-
  ssign multiple objects to multiple variables.
  
  Another way of assigning multiple variables is using what we shall call the       -
  "multuple assignment". This is not an official Python term, but we use "multuple" -
  here because when assigning variables this way, the objects on both sides of the e-
  qual sign are tuples, a Python standard type we introduced in Section 2.8.
  
  >>> x, y, z = 1, 2, 'a string'
  >>> x  
  1
  >>> y
  2
  >>> z
  'a string'
  
  In the above example, two integer objects (with values 1 and 2) and one string obj-
  ect are assigned to x, y, and z respectively. Parentheses are normally used to den-
  ote tuples, and although they are optional, we recommend them anywhere they make t-
  he code easier to read:

  >>> (x, y, z) = (1, 2, 'a string')
  
  One interesting side effect of Python’s "multuple" assignment is that we no  longer 
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

--> numbers
 Python supports five basic numerical types, three of which are integer types.
 
 -->--> int (signed integers)
  long (long integers)
  bool (Boolean values)
  
  Moving forward, ints and longs are in the process of becoming unified into a single 
  integer type. Beginning in version 2.3, overflow errors are no longer reported— the 
  result is automagically converted to a long. In Python 3, there is no distinction -
  as both int and long have been unified into a single integer type, and the "L" will 
  no longer be valid Python syntax.
  
  Boolean values are a special case of integer. Although represented by the constant-
  s True and False, if put in a numeric context such as addition with other numbers , 
  True is treated as the integer with value 1, and False has a value of 0.
  
  -->--> float (floating point real numbers)
  
  -->--> complex (complex numbers)

--> strings
 Strings in Python are identified as a contiguous set of characters in between quota-
 tion marks. Python allows for either pairs of single or double quotes. Triple quotes 
 (three consecutive single or double quotes) can be used to escape special character-
 s. Subsets of strings can be taken using the index ( [ ] ) and slice ( [ : ] ) oper-
 ators, which work with indexes starting at 0 in the beginning of the string and wor-
 king their way from -1 at the end. The plus ( + ) sign is the string concatenation -
 operator, and the asterisk ( * ) is the repetition operator. 

--> Statements and Syntax
 Hash mark ( # ) indicates Python comments
 NEWLINE ( \n ) is the standard line separator (one statement per line)
 Backslash ( \ ) continues a line
 Semicolon ( ; ) joins two statements on a line
 Colon ( : ) separates a header line from its suite
 Statements (code blocks) grouped as suites
 Suites delimited via indentation
 Python files organized as modules
 
--> Identifiers
 Identifiers are the set of valid strings that are allowed as names in a computer la-
 nguage. 
 
 1 First character must be a letter or underscore ( _ )
 2 Any additional characters can be alphanumeric or underscore
 3 Case-sensitive
 
 -->--> Python Keywords
  and as assert break
  class continue def del
  elif else except exec
  finally for from global
  if import in is
  lambda not or pass
  print raise return try
  while with yield None
  
 -->--> Built-ins
  In addition to keywords, Python has a set of "built-in" names available at any lev-
  el of Python code that are either set and/or used by the interpreter. Although  not 
  keywords, built-ins should be treated as "reserved for the system" and not used for 
  any other purpose. 
  
  built-ins are members of the __builtins__ module, which is automatically imported -
  by the interpreter before your program begins or before you are given the >>> prom-
  pt in the interactive interpreter. 
  
 -->--> Special Underscore Identifiers
  Python designates (even more) special variables with underscores both prefixed  and 
  suffixed. Here is a summary of the special underscore usage in Python:
 
  1 _xxx      Do not import with 'from module import *'
  2 __xxx__   System-defined name
  3 __xxx     Request private name mangling in classes


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
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  




















