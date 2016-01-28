
>>> print "%s is number %d!" % ("Python", 1)
Python is number 1!

>>> myString = 'Hello World!'
>>> print myString
Hello World!

The print statement can also redirect output to a file. Debugging in 2.0, the >> sym-
bols precede a valid file, such as these 2 examples, one to standard error and the o-
ther to a log file:
  import sys
  print >> sys.stderr, 'Fatal error: invalid input!'

  logfile = open('/tmp/mylog.txt', 'a')
  print >> logfile, 'Fatal error: invalid input!'
  logfile.close()



  

print is changing to a function [print()] in Python 3.0. This is a significant chang-
e, so starting in Python 2.6, you can start coding against the new function by addin-
g this special import statement:
  from __future__ import print_function
The syntax of the new function is:
  print(*args, sep=' ', end='\n', file=None)
For example:
  print('Fatal error: invalid input!', file=sys.stderr)
  
  
