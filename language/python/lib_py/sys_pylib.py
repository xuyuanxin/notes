'''
28. Python Runtime Services
28.1. sys — System-specific parameters and functions
'''

  def sys.getsizeof(object[, default]):
    '''
	Return the size of an object in bytes. The object can be any type of object. All built-in objects will return correct results, but this does not have to hold true for third-party extensions as it is implementation specific.

The default argument allows to define a value which will be returned if the object type does not provide means to retrieve the size and would cause a TypeError.

getsizeof calls the object’s sizeof method and adds an additional garbage collector overhead if the object is managed by the garbage collector.

    import sys

v = 1
print sys.getsizeof(v)

s = 'abc'
print sys.getsizeof(s)
	'''



This module provides access to some variables used or maintained by the interpreter -
and to functions that interact strongly with the interpreter. It is always available.



sys.argv
  The list of command line arguments passed to a Python script. argv[0] is the script 
  name (it is operating system dependent whether this is a full pathname or not).  If 
  the command was executed using the -c command line option to the interpreter,     -
  argv[0] is set to the string '-c'. If no script name was passed to the Python inte-
  rpreter, argv[0] is the empty string. To loop over the standard input, or the  list 
  of files given on the command line, see the fileinput module.
  • sys.argv is the list of command-line arguments
  • len(sys.argv) is the number of command-line arguments

sys.path
    A list of strings that specifies the search path for modules. Initialized from t-
	he environment variable PYTHONPATH, plus an installation-dependent default.

sys.argv
Sys.argv[]是用来获取命令行参数的，sys.argv[0]表示代码本身文件路径，所以参数从1开始，



