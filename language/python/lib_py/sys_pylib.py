'''
28. Python Runtime Services
28.1. sys — System-specific parameters and functions


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