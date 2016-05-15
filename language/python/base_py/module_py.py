'''
Python入门笔记(23)：模块   http://www.cnblogs.com/BeginMan/p/3183656.html

--> Python module
 Python module, the highest-level program organization unit, which packages program -
 code and data for reuse, and provides selfcontained namespaces that minimize variab-
 le name clashes across your programs. In concrete terms, modules typically correspo-
 nd to Python program files. Each file is a module, and modules import other  modules 
 to use the names they define. 
 
 the central concepts of Python modules, imports, and object attributes.

--> Why Use Modules?
 In short, modules provide an easy way to organize components into a system by servi-
 ng as self-contained packages of variables known as namespaces. All the names defin-
 ed at the top level of a module file become attributes of the imported module objec-
 t. As we saw in the last part of this book, imports give access to names in a modul-
 e’s global scope. That is, the module file’s global scope morphs into the module ob-
 ject’s attribute namespace when it is imported. 

-->
 Load the file b.py (unless it’s already loaded), and give me access to all its attributes
 through the name b.
 To satisfy such goals, import (and, as you’ll see later, from) statements execute and load
 other files on request. More formally, in Python, cross-file module linking is not resolved until such import statements are executed at runtime; their net effect is to assign
 module names—simple variables like b—to loaded module objects. In fact, the module
 name used in an import statement serves two purposes: it identifies the external file to
 be loaded, but it also becomes a variable assigned to the loaded module.

--> How Imports Work
 Some C programmers like to compare the Python module import operation to a C       -
 #include, but they really shouldn’t—in Python, imports are not just textual inserti-
 ons of one file into another. They are really runtime operations that perform  three 
 distinct steps the first time a program imports a given file:
 1. Find the module’s file.
 2. Compile it to byte code (if needed).
 3. Run the module’s code to build the objects it defines.

 Python storing loaded modules in a table named sys.modules and checking there at the 
 start of an import operation. If the module is not present, a three-step process be-
 gins.

 The final step of an import operation executes the byte code of the module. All sta-
 tements in the file are run in turn, from top to bottom, and any assignments made to
 names during this step generate attributes of the resulting module object. This is -
 how the tools defined by the module’s code are created. For instance, def statements 
 in a file are run at import time to create functions and assign attributes within t-
 he module to those functions. The functions can then be called later in the  program 
 by the file’s importers. Because this last import step actually runs the file’s cod-
 e, if any top-level code in a module file does real work, you’ll see its results  at 
 import time. 

-->The Module Search Path
 -->--> Home directory (automatic)
  Python first looks for the imported file in the home directory. The meaning of this
  entry depends on how you are running the code. When you’re running a program,  this 
  entry is the directory containing your program’s top-level script file. When you’re 
  working interactively, this entry is the directory in which you are working ( i.e., 
  the current working directory).
 -->--> PYTHONPATH directories (configurable)
  Next, Python searches all directories listed in your PYTHONPATH environment variab-
  le setting, from left to right (assuming you have set this at all: it’s not  preset 
  for you).
  
  For instance, on Windows, you might use your Control Panel’s System icon to set   -
  PYTHONPATH to a list of directories separated by semicolons, like this:
  c:\pycode\utilities;d:\pycode\package1
  Or you might instead create a text file called C:\Python33\pydirs.pth, which  looks 
  like this:
  c:\pycode\utilities
  d:\pycode\package1
 -->--> Standard library directories (automatic)
  Next, Python automatically searches the directories where the standard library mod-
  ules are installed on your machine. Because these are always searched, they normal-
  ly do not need to be added to your PYTHONPATH or included in path files ( discussed 
  next)
 -->--> .pth path file directories (configurable)
  Next, a lesser-used feature of Python allows users to add directories to the module
  search path by simply listing them, one per line, in a text file whose name ends w-
  ith a .pth suffix (for "path"). These path configuration files are a somewhat adva-
  nced installation-related feature; In short, text files of directory names  dropped 
  in an appropriate directory can serve roughly the same role as the PYTHONPATH envi-
  ronment variable setting.
 -->--> The Lib\site-packages directory of third-party extensions (automatic)
  Finally, Python automatically adds the site-packages subdirectory of its standard -
  library to the module search path.

 -->--> The sys.path List
  If you want to see how the module search path is truly configured on your machine ,
  you can always inspect the path as Python knows it by printing the built-in       -
  sys.path list (that is, the path attribute of the standard library module sys).   -
  sys.path is the module search path. Python configures it at program startup, autom-
  atically merging the home directory of the top-level file (or an empty string to d-
  esignate the current working directory), any PYTHONPATH directories, the contents -
  of any .pth file paths you’ve created, and all the standard library directories. T-
  he result is a list of directory name strings that Python searches on each import -
  of a new file. 

 -->--> Module File Selection
  For example, an import statement of the form import b might today load or resolve -
  to:
  • A source code file named b.py
  • A byte code file named b.pyc
  • An optimized byte code file named b.pyo (a less common format)
  • A directory named b, for package imports (described in Chapter 24)
  • A compiled extension module, coded in C, C++, or another language, and dynamical-
    ly linked when imported (e.g., b.so on Linux, or b.dll or b.pyd on Cygwin and Wi-
	ndows)
  • A compiled built-in module coded in C and statically linked into Python
  • A ZIP file component that is automatically extracted when imported
  • An in-memory image, for frozen executables
  • A Java class, in the Jython version of Python
  • A .NET component, in the IronPython version of Python
  
  Saying import b gets whatever module b is, according to your module search path, a-
  nd b.attr fetches an item in the module, be it a Python variable or a linked-in C -
  function. Some standard modules we will use in this book are actually coded in C, -
  not Python; because they look just like Python-coded module files, their clients d-
  on’t have to care.
  
--> Module Creation
 To define a module, simply use your text editor to type some Python code into a text
 file, and save it with a ".py" extension; any such file is automatically  considered 
 a Python module. All the names assigned at the top level of the module become its a-
 ttributes (names associated with the module object) and are exported for clients  to 
 use--they morph from variable to module object attribute automatically.

 For instance, if you type the following def into a file called module1.py and import 
 it, you create a module object with one attribute--the name printer, which happens -
 to be a reference to a function object:
 
 def printer(x): # Module attribute module1.py
     print(x)

 Because module names become variable names inside a Python program (without the .py)
 , they should also follow the normal variable name rules outlined in Chapter 11. For 
 instance, you can create a module file named if.py, but you cannot import it becaus-
 e if is a reserved word, when you try to run import if, you’ll get a syntax error.

 -->--> Other Kinds of Modules (extension modules)
  As mentioned in the preceding chapter, it is also possible to create a Python modu-
  le by writing code in an external language such as C, C++, and others ( e.g., Java, 
  in the Jython implementation of the language). Such modules are called extension m-
  odules, and they are generally used to wrap up external libraries for use in Python 
  scripts. When imported by Python code, extension modules look and feel the same  as 
  modules coded as Python source code files--they are accessed with import statement-
  s, and they provide functions and objects as module attributes. 
  
--> Module Usage
 -->--> The import Statement
  In the first example, the name module1 serves two different purposes--it identifies 
  an external file to be loaded, and it becomes a variable in the script, which refe-
  rences the module object after the file is loaded:
  >>> import module1 # Get module as a whole (one or more)
  >>> module1.printer('Hello world!') # Qualify to get names
  Hello world!
  The import statement simply lists one or more names of modules to load, separated -
  by commas. Because it gives a name that refers to the whole module object, we  must 
  go through the module name to fetch its attributes (e.g., module1.printer).
 -->--> The from Statement
  By contrast, because from copies specific names from one file over to another scop-
  e, it allows us to use the copied names directly in the script without going throu-
  gh the module (e.g., printer):
  >>> from module1 import printer # Copy out a variable (one or more)
  >>> printer('Hello world!') # No need to qualify name
  Hello world!
  This form of from allows us to list one or more names to be copied out, separated -
  by commas. Here, it has the same effect as the prior example, but because the impo-
  rted name is copied into the scope where the from statement appears, using that na-
  me in the script requires less typing--we can use it directly instead of naming the 
  enclosing module. In fact, we must; from doesn’t assign the name of the module its-
  elf. As you’ll see in more detail later, the from statement is really just a  minor 
  extension to the import statement--it imports the module file as usual (running the 
  full three-step procedure of the preceding chapter), but adds an extra step that c-
  opies one or more names (not objects) out of the file. The entire file is loaded, -
  but you’re given names for more direct access to its parts.  
 -->--> The from * Statement
  Finally, the next example uses a special form of from: when we use a * instead of -
  specific names, we get copies of all names assigned at the top level of the refere-
  nced module. Note that only * works in this context; you can’t use pattern matching 
  to select a subset of names.
  
--> Module Packages  
 -->--> Package Import Basics
  At a base level, package imports are straightforward--in the place where you have -
  been naming a simple file in your import statements, you can instead list a path of 
  names separated by periods:
    import dir1.dir2.mod
  The same goes for from statements:
    from dir1.dir2.mod import x
  The "dotted" path in these statements is assumed to correspond to a path through t-
  he directory hierarchy on your computer, leading to the file mod.py (or similar; t-
  he extension may vary). That is, the preceding statements indicate that on your ma-
  chine there is a directory dir1, which has a subdirectory dir2, which contains a m-
  odule file mod.py (or similar).
  
  Furthermore, these imports imply that dir1 resides within some container  directory
  dir0, which is a component of the normal Python module search path. In other words,
  these two import statements imply a directory structure that looks something like -
  this (shown with Windows backslash separators):
    dir0\dir1\dir2\mod.py # Or mod.pyc, mod.so, etc.
  The container directory dir0 needs to be added to your module search path unless  -
  it’s the home directory of the top-level file, exactly as if dir1 were a simple mo-
  dule file. More formally, the leftmost component in a package import path is  still 
  relative to a directory included in the sys.path module search path list we explor-
  ed in Chapter 22. 
  
 -->--> Package __init__.py Files
  If you choose to use package imports, there is one more constraint you must follow: 
  at least until Python 3.3, each directory named within the path of a package      -
  @import statement must contain a file named __init__.py, or your package imports w-
  ill fail. That is, in the example we’ve been using, both dir1 and dir2 must contain 
  a file called __init__.py; the container directory dir0 does not require such a fi-
  le because it’s not listed in the @import statement itself.
  
  Package initialization file roles:
  1 Package initialization. The first time a Python program imports through a direct-
  ory, it automatically runs all the code in the directory’s __init__.py file.
  2 Module usability declarations. Package __init__.py files are also partly  present 
  to declare that a directory is a Python package. 
  3 Module namespace initialization. In the package import model, the directory paths 
  in your script become real nested object paths after an import. For instance, in t-
  he preceding example, after the import the expression dir1.dir2 works and returns a 
  module object whose namespace contains all the names assigned by dir2’s __init__.py 
  initialization file. Such files provide a namespace for module objects created  for 
  directories, which would otherwise have no real associated module file.
  4 from * statement behavior. As an advanced feature, you can use __all__ lists in -
  __init__.py files to define what is exported when a directory is imported with  the 
  from * statement form. 
  
  -->--> Package Import Example
   # dir1\__init__.py
   print('dir1 init')
   x = 1
   
   # dir1\dir2\__init__.py
   print('dir2 init')
   y = 2
   
   # dir1\dir2\mod.py
   print('in mod.py')
   z = 3
   
   
   C:\code> python # Run in dir1's container directory
   >>> import dir1.dir2.mod # First imports run init files
   dir1 init
   dir2 init
   in mod.py
   >>>
   >>> import dir1.dir2.mod # Later imports do not
   >>> dir1.x
   1
   >>> dir1.dir2.y
   2
   >>> dir1.dir2.mod.z
   3
   >>> dir2.mod
   NameError: name 'dir2' is not defined
   >>> mod.z
   NameError: name 'mod' is not defined
   
   C:\code> python
   >>> from dir1.dir2 import mod # Code path here only
   dir1 init
   dir2 init
   in mod.py
   >>> mod.z # Don't repeat path
   3
   >>> from dir1.dir2.mod import z
   >>> z
   3
   >>> import dir1.dir2.mod as mod # Use shorter name (see Chapter 25)
   >>> mod.z
   3
   >>> from dir1.dir2.mod import z as modz # Ditto if names clash (see Chapter 25)
   >>> modz
   3
  
 
 
 -->--> Package Relative Imports
  Imports with dots: In both Python 3.X and 2.X, you can use leading dots in @from s-
  tatements’ module names to indicate that imports should be relative-only to the co-
  ntaining package--such imports will search for modules inside the package directory 
  only and will not look for same-named modules located elsewhere on the import sear-
  ch path (sys.path). The net effect is that package modules override outside module-
  s.
  Imports without dots: In Python 2.X, normal imports in a package’s code without le-
  ading dots currently default to a relative-then-absolute search path order--that is
  , they search the package’s own directory first. However, in Python 3.X, normal im-
  ports within a package are absolute-only by default--in the absence of any  special 
  dot syntax, imports skip the containing package itself and look elsewhere on the  -
  sys.path search path.
  
  >>> from __future__ import absolute_import  # Use 3.X relative import model in 2.X
  
  If present, this statement enables the Python 3.X absolute-only search path change. 
  In 3.X, and in 2.X when enabled, an import without a leading dot in the module nam-
  e always causes Python to skip the relative components of the module import  search 
  path and look instead in the absolute directories that sys.path contains. 
  
  In effect, the "." in a relative import is taken to stand for the package directory 
  containing the file in which the import appears. An additional leading dot performs 
  the relative import starting from the parent of the current package. For example:
  
  |--A
  |  |--B
  |     |--C <----
  |     |--D
  |        |--X
  |  |--E
  |     |--X
  
  code located in some module A.B.C can use any of these forms:
  >>> from . import D # Imports A.B.D (. means A.B)
  >>> from .. import E # Imports A.E (.. means A)
  >>> from .D import X # Imports A.B.D.X (. means A.B)
  >>> from ..E import X # Imports A.E.X (.. means A)
  
  -->-->--> The Scope of Relative Imports
   Relative imports apply to imports within packages only. Keep in mind that this fe-
   ature’s module search path change applies only to import statements within  module 
   files used as part of a package--that is, intrapackage imports. Normal imports  in 
   files not used as part of a package still work exactly as described earlier, auto-
   matically searching the directory containing the top-level script first.
   Relative imports apply to the @from statement only. Also remember that this featu-
   re’s new syntax applies only to @from statements, not @import statements. It’s de-
   tected by the fact that the module name in a @from begins with one or more dots (-
   periods). Module names that contain embedded dots but don’t have a leading dot are 
   package imports, not relative imports.
   
  -->-->--> Module Lookup Rules Summary
   With packages and relative imports, the module search story in Python 3.X that  we
   have seen so far can be summarized as follows:
   1 Basic modules with simple names (e.g., A) are located by searching each directo-
   ry on the sys.path list, from left to right. 
   2 Packages are simply directories of Python modules with a special __init__.py fi-
   le, which enables A.B.C directory path syntax in imports. In an import of A.B.C, -
   for example, the directory named A is located relative to the normal module import
   search of sys.path, B is another package subdirectory within A, and C is a  module
   or other importable item within B.
   3 Within a package’s files,normal import and from statements use the same sys.path 
   search rule as imports elsewhere. Imports in packages using from statements and l-
   eading dots, however, are relative to the package; that is, only the package dire-
   ctory is checked, and the normal sys.path lookup is not used.
   
   Python 2.X works the same, except that normal imports without dots also automatic-
   ally search the package directory first before proceeding on to sys.path. In  sum, 
   Python imports select between relative (in the containing directory) and  absolute 
   (in a directory on sys.path) resolutions as follows:
    Dotted imports: from . import m
      Are relative-only in both 2.X and 3.X
    Nondotted imports: import m, from m import x
      Are relative-then-absolute in 2.X, and absolute-only in 3.X
  
  
  
  
  
  
----> What Are Modules?
 Modules are a means to organize Python code, and packages help you organize modules. 
 A module allows you to logically organize your Python code. When code gets to be la-
 rge enough, the tendency is to break it up into organized pieces that can still int-
 eract with one another at a functioning level. These pieces generally have attribut-
 es that have some relation to one another, perhaps a single class with its member d-
 ata variables and methods, or maybe a group of related, yet independently  operating 
 functions. These pieces should be shared, so Python allows a module the ability to -
 "bring in" and use attributes from other modules to take advantage of work that  has 
 been done, maximizing code reusability. This process of associating attributes  from 
 other modules with your module is called importing. In a nutshell, modules are     -
 self-contained and organized pieces of Python code that can be shared.

----> Modules and Files
 If modules represent a logical way to organize your Python code, then files are a w-
 ay to physically organize modules. To that end, each file is considered an individu-
 al module, and vice versa. The filename of a module is the module name appended with 
 the.py file extension.

----> Search Path and Path Search
 The process of importing a module requires a process called a path search. This is -
 the procedure of checking "predefined areas" of the file system to look for your   -
 mymodule.py file in order to load the mymodule module. These predefined areas are no 
 more than a set of directories that are part of your Python search path. 
 
 A default search path is automatically defined either in the compilation or install-
 ation process. This search path may be modified in one of two places.
 One is the PYTHONPATH environment variable set in the shell or commandline interpre-
 ter that invokes. 
 Once the interpreter has started, you can access the path itself, which is stored in 
 the sys module as the sys.path variable. If you know of a module you want to import, 
 yet its directory is not in the search path, by all means use the list’s append() m-
 ethod to add it to the path, like so:
 > sys.path.append('/home/wesc/py/lib')
 
 To find out what modules have been successfully imported (and loaded) as well as fr-
 om where, take a look at sys.modules. sys.modules is a dictionary where the keys are 
 the module names with their physical location as the values. Finally,  site-packages
 is where third-party or external modules or packages are installed
 
----> Namespaces versus Variable Scope
 A namespace is a mapping of names (identifiers) to objects. The process of adding  a 
 name to a namespace consists of binding the identifier to the object (and increasing 
 the reference count to the object by one). The Python Language Reference also inclu-
 des the following definitions: "changing the mapping of a name is called rebinding -
 [, and] removing a name is unbinding."

 there are either two or three active namespaces at any given time during  execution. 
 These three namespaces are the local, global, and built-ins namespaces, but local  -
 name-spaces come and go during execution, hence the "two or three" we just alluded -
 to. The names accessible from these namespaces are dependent on their loading order, 
 or the order in which the namespaces are brought into the system.
 
 The Python interpreter loads the built-ins namespace first. This consists of the na-
 mes in the __builtins__ module. Then the global namespace for the executing module -
 is loaded, which then becomes the active namespace when the module begins execution. 
 Thus we have our two active namespaces. When a function call is made during executi-
 on, the third, a local, namespace is created. We can use the globals() and  locals() 
 built-in functions to tell us which names are in which namespaces.
  
 ---->  __builtins__
  The __builtins__ module consists of a set of built-in names for the built-ins name-
  space. Most, if not all, of these names come from the __builtin__ module, which  is 
  a module of the built-in functions, exceptions, and other attributes. In standard -
  Python execution, __builtins__ contains all the names from __builtin__. 

 ----> Namespaces versus Variable Scope
  Namespaces are purely mappings between names and objects, but scope dictates how, -
  or rather where, one can access these names based on the physical location from wi-
  thin your code. Notice that each of the namespaces is a self-contained unit. But l-
  ooking at the namespaces from the scoping point of view, things appear different. -
  All names within the local namespace are within my local scope. Any name outside my 
  local scope is in my global scope. Our final thought to you in this section is, wh-
  en it comes to namespaces, ask yourself the question, "Does it have it?" And for v-
  ariable scope, ask, "Can I see it?"

 ----> Name Lookup, Scoping, and Overriding
  When accessing an attribute, the interpreter must find it in one of the three name-
  spaces. The search begins with the local namespace. If the attribute is not found -
  there, then the global namespace is searched. If that is also unsuccessful, the fi-
  nal frontier is the built-ins namespace. If the exhaustive search fails, you get t-
  he familiar:
  >>> foo
  Traceback (innermost last):
  File "<stdin>", line 1, in ?
  NameError: foo

  overriding
  names found in the local namespace will hide access to objects in the global or   -
  built-ins namespaces. This is the process whereby names may be taken out of scope -
  because a more local namespace contains a name.
  
 ----> Namespaces for Free!
  One of Python’s most useful features is the ability to get a namespace almost anyw-
  here you need a place to put things. 
  |class MyUltimatePythonStorageDevice(object):
  |    pass
  |bag = MyUltimatePythonStorageDevice()
  |bag.x = 100
  |bag.y = 200
  |bag.version = 0.1
  |bag.completed = False

----> What are variables, really? 
 What are variables, really? You can think of them as names referring to values.  So, 
 after the assignment x = 1, the name x refers to the value 1. It’s almost like usin-
 g dictionaries, where keys refer to values, except that you’re using an  “invisible” 
 dictionary. Actually, this isn’t far from the truth. There is a built-in function c-
 alled vars, which returns this dictionary:
 >>> x = 1
 >>> scope = vars()
 >>> scope['x']
 1
 >>> scope['x'] += 1
 >>> x
 2
 This sort of “invisible dictionary” is called a namespace or scope. So, how many na-
 mespaces are there? In addition to the global scope, each function call creates a n-
 ew one:
 >>> def foo(): x = 42
 ...
 >>> x = 1
 >>> foo()
 >>> x
 1
 Here foo changes (rebinds) the variable x, but when you look at it in the end, it h-
 asn’t changed after all. That’s because when you call foo, a new namespace is creat-
 ed, which is used for the block inside foo. The assignment x = 42 is performed in t-
 his inner scope (the local namespace), and therefore it doesn’t affect the x in  the 
 outer (global) scope. 
 
 But what if you want to access the global variables inside a function? As long as y-
 ou only want to read the value of the variable (that is, you don’t want to rebind i-
 t), there is generally no problem:
 >>> def combine(parameter): print parameter + external
 ...
 >>> external = 'berry'
 >>> combine('Shrub')
 Shrubberry
 Reading the value of global variables is not a problem in general, but one thing ma-
 y make it problematic. If a local variable or parameter exists with the same name as 
 the global variable you want to access, you can’t do it directly. The global variab-
 le is shadowed by the local one.
 
 If needed, you can still gain access to the global variable by using the function g-
 lobals, a close relative of vars, which returns a dictionary with the global variab-
 les. (locals returns a dictionary with the local variables.)
 >>> def combine(parameter):
 print parameter + globals()['parameter']
 ...
 >>> parameter = 'berry'
 >>> combine('Shrub')
 Shrubberry 
 
 Rebinding global variables (making them refer to some new value) is another  matter. 
 If you assign a value to a variable inside a function, it automatically becomes loc-
 al unless you tell Python otherwise. And how do you think you can tell it to make  a 
 variable global?
 >>> x = 1
 >>> def change_global():
       global x
       x = x + 1
 >>> change_global()
 >>> x
 2

 To specifically reference a named global variable, one must use the @global stateme-
 nt. The syntax for global is:
 global var1[, var2[, ... varN]]]
 
----> The import Statement
 Importing a module requires the use of the import statement, whose syntax is:
 > import module1
 > import module2
 > :
 > import moduleN
 It is also possible to import multiple modules on the same line like this ...
 > import module1[, module2[,... moduleN]]  # not preferred form

 When this statement is encountered by the interpreter, the module is imported if fo-
 und in the search path. Scoping rules apply, so if imported from the top level of  a 
 module, it has global scope; if imported from a function, it has local scope. When a 
 module is imported the first time, it is loaded and executed.

 Module ordering for import statements
 1 Python Standard Library modules
 2 Python third party modules
 3 Application-specific modules
 
 The from-import Statement
 It is possible to import specific module elements into your own module. By this,  we 
 really mean importing specific names from the module into the current namespace. For 
 this purpose, we can use the from-import statement, whose syntax is:
 > from module import name1[, name2[,... nameN]]

 Extended Import Statement (as)
 > import Tkinter as tk
 > from cgi import FieldStorage as form

----> 
 One effect of loading a module is that the imported module is “executed,”
 that is, the top-level portion of the imported module is directly executed.
 This usually includes setting up of global variables as well as performing the
 class and function declarations. If there is a check for __name__ to do more
 on direct script invocation, that is executed, too.Of course, this type of execution may or may not be the desired effect. If
 not, you will have to put as much code as possible into functions. 

 A module is loaded only once, regardless of the number of times it is
 imported. This prevents the module “execution” from happening over and
 over again if multiple imports occur. 
 
 Calling from-import brings the name into the current namespace, meaning
 that you do not use the attribute/dotted notation to access the module identifier. For example, to access a variable named var in module module that
 was imported with:
 from module import var
 we would use “var” by itself. There is no need to reference the module since
 you imported var into your namespace. It is also possible to import all the
 names from the module into the current namespace using the following
 from-import statement:
 from module import *

 CORE STYLE: Restrict your use of “from module import *”
 In practice, using from module import * is considered poor style
 because it “pollutes” the current namespace and has the potential of
 overriding names in the current namespace; however, it is extremely
 convenient if a module has many variables that are often accessed, or if
 the module has a very long name.
 We recommend using this form in only two situations. The first is where the
 target module has many attributes that would make it inconvenient to type
 in the module name over and over again. Two prime examples of this are
 the Tkinter (Python/Tk) and NumPy (Numeric Python) modules, and
 perhaps the socket module. The other place where it is acceptable to use
 from module import * is within the interactive interpreter, to save on
 the amount of typing.

 Names Imported into Importer’s Scope
 Another side effect of importing just names from modules is that those
 names are now part of the local namespace. A side effect is possibly hiding or
 overriding an existing object or built-in with the same name. Also, changes to
 the variable affect only the local copy and not the original in the imported
 module’s namespace. In other words, the binding is now local rather than
 across namespaces.
 Here we present the code to two modules: an importer, impter.py, and
 an importee, imptee.py. Currently, impter.py uses the from-import
 statement, which creates only local bindings.
 #############
 # imptee.py #
 #############
 foo = 'abc'
 def show():
 print 'foo from imptee:', foo
 #############
 # impter.py #
 #############
 from imptee import foo, show
 show()
 foo = 123
 print 'foo from impter:', foo
 show()
 Upon running the importer, we discover that the importee’s view of its foo
 variable has not changed even though we modified it in the importer.
 foo from imptee: abc
 foo from impter: 123
 foo from imptee: abc
 The only solution is to use import and fully qualified identifier names
 using the attribute/dotted notation.
 #############
 # impter.py #
 #############
 import imptee
 imptee.show()
 imptee.foo = 123
 print 'foo from impter:', imptee.foo
 imptee.show()
 Once we make the update and change our references accordingly, we now
 have achieved the desired effect.
 foo from imptee: abc
 foo from impter: 123
 foo from imptee: 123 

----> package
 包（Package）可以看成模块的集合，只要一个文件夹下面有个__init__.py文件，那么这个文件|
 夹就可以看做是一个包。包下面的文件夹还可以成为包（子包）。更进一步，多个较小的包可以|
 聚合成一个较大的包，通过包这种结构，方便了类的管理和维护，也方便了用户的使用。包导入|
 的过程和模块的基本一致，只是导入包的时候会执行此包目录下的__init__.py而不是模块里面 |
 的语句了。另外，如果只是单纯的导入包，而包的__init__.py中又没有明确的其他初始化操作 |
 ，那么此包下面的模块是不会自动导入的。                                              |
 
 |-- PA
 |  |-- __init__.py
 |  |-- wave.py
 |  |-- PB1
 |  |  |-- __init__.py
 |  |  |-- pb1_m.py
 |  |-- PB2
 |  |  |-- __init__.py
 |  |  |-- pb2_m.py
 
 __init__.py都为空，如果有以下程序：

 > import sys
 > import PA.wave  #1
 > import PA.PB1   #2
 > import PA.PB1.pb1_m as m1  #3
 > import PA.PB2.pb2_m #4
 > PA.wave.getName() #5
 > m1.getName() #6
 > PA.PB2.pb2_m.getName() #7
                                                                                     |
 当执行#1后                                                                          |
  sys.modules会同时存在PA、PA.wave两个模块，此时可以调用PA.wave的任何类或函数了。但不|
  能调用PA.PB1(2)下的任何模块。当前Local中有了PA名字。                               |
 当执行#2后，
  只是将PA.PB1载入内存，sys.modules中会有PA、PA.wave、PA.PB1三个模块，但是PA.PB1下的 |
  任何模块都没有自动载入内存，此时如果直接执行PA.PB1.pb1_m.getName()则会出错，因为   |
  PA.PB1中并没有pb1_m。当前Local中还是只有PA名字，并没有PA.PB1名字。                 |
 当执行#3后，
  会将PA.PB1下的pb1_m载入内存，sys.modules中会有PA、PA.wave、PA.PB1、PA.PB1.pb1_m四个|
  模块，此时可以执行PA.PB1.pb1_m.getName()了。由于使用了as，当前Local中除了PA名字，另|
  外添加了m1作为PA.PB1.pb1_m的别名。
 当执行#4后，
  会将PA.PB2、PA.PB2.pb2_m载入内存，sys.modules中会有PA、PA.wave、PA.PB1、           |
  PA.PB1.pb1_m、PA.PB2、PA.PB2.pb2_m六个模块。当前Local中还是只有PA、m1。
 下面的#5，#6，#7都是可以正确运行的。
 注意的是：如果PA.PB2.pb2_m想导入PA.PB1.pb1_m、PA.wave是可以直接成功的。最好是采用明 |
 确的导入路径，对于./..相对导入路径还是不推荐用。
 
 A package is a hierarchical file directory structure that defines a single Python a-
 pplication environment that consists of modules and subpackages. Packages were added 
 to Python 1.5 to aid with a variety of problems including:
 
 1 Adding hierarchical organization to flat namespace
 2 Allowing developers to group related modules
 3 Allowing distributors to ship directories vs. bunch of files
 4 Helping resolve conflicting module names

 Along with classes and modules, packages use the familiar attribute/dotted attribut-
 e notation to access their elements. Importing modules within packages use the stan-
 dard import and from-import statements.

 For our package examples, we will assume the directory structure below:

 Phone/
     __init__.py
     common_util.py
     Voicedta/
         __init__.py
         Pots.py
         Isdn.py
     Fax/
         __init__.py
         G3.py
     Mobile/
         __init__.py
         Analog.py
         Digital.py
     Pager/
         __init__.py
         Numeric.py

 Phone is a top-level package and Voicedta, etc., are subpackages. Import subpackages 
 by using import like this:

 > import Phone.Mobile.Analog
 > Phone.Mobile.Analog.dial()
 
 Alternatively, you can use from-import in a variety of ways:

 > from Phone import Mobile
 > Mobile.Analog.dial('555-1212')

 > from Phone.Mobile import Analog
 > Analog.dial('555-1212')

 > from Phone.Mobile.Analog import dial
 > dial('555-1212')

 In our above directory structure hierarchy, we observe a number of __init__.py file-
 s. These are initializer modules that are required when using from-import to  import 
 subpackages but they can be empty if not used. Quite often, developers forget to add 
 __init__.py files to their package directories, so starting in Python 2.5, this tri-
 ggers an ImportWarning message. However, it is silently ignored unless the -Wd opti-
 on is given when launching the interpreter.
 
 Using from-import with Packages
 Packages also support the from-import all statement:
 > from package.module import *
 However, such a statement is dependent on the operating system’s filesystem for Pyt-
 hon to determine which files to import. Thus the __all__ variable in __init__.py  is 
 required. This variable contains all the module names that should be imported when -
 the above statement is invoked if there is such a thing. It consists of a list of m-
 odule names as strings.
 
 Absolute Import Relative Import
 all imports are now classified as absolute, meaning that names must be packages or -
 modules accessible via the Python path (sys.path or PYTHONPATH). Because the @import 
 statements are always absolute, relative imports only apply to from-import statemen-
 ts.
 The following will either still work in older versions of Python, generate a warnin-
 g, or will not work in more contemporary versions of Python:
 > import Analog
 > from Analog import dial
 This is due to the absolute import limitation. You have to use either the absolute -
 or relative imports. Below are some valid imports:
 > from Phone.Mobile.Analog import dial
 > from .Analog import dial
 > from ..common_util import setup
 > from ..Fax import G3.dial
 
----> __init__.py
 http://www.cnblogs.com/BeginMan/p/3183629.html                                      |
 python的每个模块的包中，都有一个__init__.py文件，有了这个文件，我们才能导入这个目录 |
 下的module。那么，__init__.py还有什么别的功能呢？其实，__init__.py里面还是可以有内容|
 的，我们在导入一个包时，实际上导入了它的__init__.py文件。我们可以再__init__.py文件中|
 再导入其他的包，或者模块。
 [python]
 import readers 
 import writers 
 import commands 
 import users 
 import meta 
 import auth 
 import admin 
                                                                                     |
 这样，当我们导入这个包的时候，__init__.py文件自动运行。帮我们导入了这么多个模块，我 |
 们就不需要将所有的import语句写在一个文件里了，也可以减少代码量。不需要一个个去导入  |
 module了。

 __init__.py 中还有一个重要的变量，叫做 __all__。我们有时会使出一招“全部导入”，也就是|
 这样：
 > from PackageName import *
 这时 import 就会把注册在包 __init__.py 文件中 __all__ 列表中的子模块和子包导入到当前|
 作用域中来。比如：
 +----#文件 __init__.py
 |__all__ = ["Module1", "Module2", "subPackage1", "subPackage2"]

 如：在一个包里有foo.py、__init__.py
 +----#__init__.py
 |import os
 |import datetime
 +----#foo.py
 |from __init__ import *
 |print datetime.datetime.now() 
 则输出：2013-07-11 11:34:41.250000

python中sys.path使用
时间 2014-02-27 18:14:44  CSDN博客
原文  http://blog.csdn.net/magicharvey/article/details/20063437
主题 Python Linux
sys模块包含了与python解释器和它的环境有关的函数，这个你可以通过dir(sys)来查看他里面的方法和成员属性。

下面的两个方法可以将模块路径加到当前模块扫描的路径里：

sys.path.append('你的模块的名称')。

sys.path.insert(0,'模块的名称')

永久添加路径到sys.path中，方式有三，如下：

1）将写好的py文件放到 /usr/lib/python2.6/site-packages 目录下 

2) 在 /usr/lib/python2.6/site-packages 下面新建一个.pth 文件(以pth作为后缀名) 

将模块的路径写进去，一行一个路径，如： vim pythonmodule.pth

/home/liu/shell/config

/home/liu/shell/base 

3) 使用PYTHONPATH环境变量

export PYTHONPATH=$PYTHONPATH:/home/liu/shell/config

A standard installation includes a set of modules called the standard library. 

----> modules
 import module_name # 导入模块

 the code in the module is executed when you import it. However, if you try to import 
 it again, nothing happens. Because modules aren’t really meant to do things (such as
 printing text) when they’re imported. They are mostly meant to define things, such -
 as variables, functions, classes, and so on. And because you need to define things -
 only once,importing a module several times has the same effect as importing it once.

 When you import a module, you may notice that a new file appears. The file with  the 
 .pyc extension is a (platform-independent) processed ("compiled") Python file that -
 has been translated to a format that Python can handle more efficiently. If you imp-
 ort the same module later, Python will import the .pyc file rather than the .py fil-
 e, unless the .py file has changed; in that case, a new .pyc file is generated. Del-
 eting the .pyc file does no harm (as long as there is an equivalent .py file availa-
 ble),  a new one is created when needed.
 
 WHY ONLY ONCE?
 |# hello.py
 |print "Hello, world!"
 The import-only-once behavior is a substantial optimization in most cases, and it c-
 an be very important in one special case: if two modules import each other. In  many 
 cases, you may write two modules that need to access functions and classes from each 
 other to function properly. For example, you may have created two modules—clientdb and billing—containing
 code for a client database and a billing system, respectively. Your client database may contain calls to your
 billing system (for example, automatically sending a bill to a client every month), while the billing system probably needs to access functionality from your client database to do the billing correctly.
 If each module could be imported several times, you would end up with a problem here. The module
 clientdb would import billing, which again imports clientdb, which . . . you get the picture. You get an
 endless loop of imports (endless recursion, remember?). However, because nothing happens the second time
 you import the module, the loop is broken.
 If you insist on reloading your module, you can use the built-in function reload. It takes a single argument (the module you want to reload) and returns the reloaded module. This may be useful if you have made
 changes to your module and want those changes reflected in your program while it is running. To reload the
 simple hello module (containing only a print statement), I would use the following:
 >>> hello = reload(hello)
 Hello, world!
 Here, I assume that hello has already been imported (once). By assigning the result of reload to
 hello, I have replaced the previous version with the reloaded one. As you can see from the printed greeting,
 I am really importing the module here.
 If you’ve created an object x by instantiating the class Foo from the module bar, and you then reload
 bar, the object x refers to will not be re-created in any way. x will still be an instance of the old version of Foo
 (from the old version of bar). If, instead, you want x to be based on the new Foo from the reloaded module,
 you will need to create it anew.
 Note that the reload function has disappeared in Python 3.0. While you can achieve similar functionality
 using exec, the best thing in most cases is simply to stay away from module reloading.

 # hello2.py
 def hello():
     print "Hello, world!"
 You can then import it like this:
 >>> import hello2
 The module is then executed, which means that the function hello is defined in the -
 scope of the module, so you can access the function like this:
 >>> hello2.hello()
 Hello, world!
 Any name defined in the global scope of the module will be available in the same manner. 

 ----> Adding Test Code in a Module
 |# hello3.py
 |def hello():
 |  print "Hello, world!"
 |# A test:
 |hello()
 >>> import hello3
 Hello, world!
 >>> hello3.hello()
 Hello, world!
 This is not what you want. The key to avoiding it is "telling" the module whether  -
 it’s being run as a program on its own or being imported into another program. To do 
 that, you need the variable __name__:
 >>> __name__
 '__main__'
 >>> hello3.__name__
 'hello3'
 As you can see, in the "main program" (including the interactive prompt of the inte-
 rpreter), the variable __name__ has the value '__main__'. In an imported module,  it 
 is set to the name of that module. 
 +---------------------------------------
 |# hello4.py
 |def hello():
 |    print "Hello, world!"
 |def test():
 |    hello()
 |if __name__ == '__main__': test()
 +---------------------------------------
 in the "main program" (including the interactive prompt of the interpreter), the va-
 riable __name__ has the value '__main__'. In an imported module, it is set to the n-
 ame of that module.

 ----> Putting Your Module in the Right Place
 the list of directories (the so-called search path) can be found in the @path varia-
 ble in the @sys module.
 >>> import sys, pprint
 >>> sys.path.append('c:/python')
 >>> pprint.pprint(sys.path)
 ['C:\\Python25\\Lib\\idlelib',
 'C:\\WINDOWS\\system32\\python25.zip',
 'C:\\Python25',
 'C:\\Python25\\DLLs',
 'C:\\Python25\\lib',
 'C:\\Python25\\lib\\plat-win',
 'C:\\Python25\\lib\\lib-tk',
 'C:\\Python25\\lib\\site-packages']
 The point is that each of these strings provides a place to put modules if you  want 
 your interpreter to find them. Even though all these will work, the site-packages d-
 irectory is the best choice because it’s meant for this sort of thing. 

 ----> Telling the Interpreter Where to Look
 one way of doing this is to edit sys.path, but that is not a common way to do it. T-
 he standard method is to include your module directory (or directories) in the envi-
 ronment variable PYTHONPATH.
 |export PYTHONPATH=$PYTHONPATH:~/python  # linux
 |set PYTHONPATH=%PYTHONPATH%;C:\python   # windows

 ----> Naming Your Module
 As you may have noticed, the file that contains the code of a module must be given -
 the same name as the module, with an additional .py file name extension. In Windows,
 you can use the file name extension .pyw instead.

----> Packages
 To structure your modules, you can group them into packages. A package is  basically 
 just another type of module. The interesting thing about them is that they can cont-
 ain other modules. While a module is stored in a file ( with the file name extension  
 .py), a package is a directory. To make Python treat it as a package, it must conta-
 in a file (module) named __init__.py. The contents of this file will be the contents
 of the package, if you import it as if it were a plain module. For example, if you -
 had a package named @constants, and the file constants/__init__.py contains the sta-
 tement 
 |PI = 3.14
 you would be able to do the following:
 >>> import constants
 >>> print constants.PI

 To put modules inside a package, simply put the module files inside the package dir-
 ectory. For example, if you wanted a package called @drawing, which contained one m-
 odule called @shapes and one called @colors, you would need the files and directori-
 es (UNIX pathnames) shown in Table 10-1.
 ------------------------------------------------------------------------------------
 ~/python/                               # Directory in PYTHONPATH
 ~/python/drawing/                       # Package directory (drawing package)
 ~/python/drawing/__init__.py            # Package code (drawing module)
 ~/python/drawing/colors.py              # colors module
 ~/python/drawing/shapes.py              # shapes module
 ------------------------------------------------------------------------------------
 With this setup, the following statements are all legal:
 |import drawing              # (1) Imports the drawing package
 |import drawing.colors       # (2) Imports the colors module
 |from drawing import shapes  # (3) Imports the shapes module
 After the first statement, the contents of the __init__ module in drawing would be -
 available; the shapes and colors modules, however, would not be. After the second s-
 tatement, the colors module would be available, but only under its full name,      -
 drawing.colors. After the third statement, the shapes module would be available, un-
 der its short name (that is, simply shapes). Note that these statements are just ex-
 amples. There is no need, for example, to import the package itself before importing 
 one of its modules as I have done here. The second statement could very well be exe-
 cuted on its own, as could the third. You may nest packages inside each other.

--------> Exploring Modules
----> Using dir
>>> import copy
>>> [n for n in dir(copy) if not n.startswith('_')]
['Error', 'PyStringMap', 'copy', 'deepcopy', 'dispatch_table', 'error', 'name', 't']

----> The __all__ Variable
>>> copy.__all__
['Error', 'copy', 'deepcopy']
__all__ defines the public interface of the module. More specifically, it tells the -
interpreter what it means to import all the names from this module. So if you use th-
is:
from copy import *
you get only the four functions listed in the __all__ variable. 

----> Getting Help with help
>>> help(copy.copy)
>>> print copy.copy.__doc__

----> Documentation
A natural source for information about a module is, of course, its documentation. 
>>> print range.__doc__
range([start,] stop[, step]) -> list of integers

----> Use the Source
Where would you find it? One solution would be to examine sys.path again and actuall-
y look for it yourself, just like the interpreter does. A faster way is to examine t-
he module’s __file__ property:
>>> print copy.__file__    # C:\Python24\lib\copy.py
Note that some modules don’t have any Python source you can read. They may be built -
into the interpreter (such as the sys module) or they may be written in the C progra-
mming language.








pym: python modules





tldextract
https://github.com/john-kurkowski/tldextract
https://pypi.python.org/pypi/tldextract

'''



'''                                                                                  |
----> 1 模块                                                                         |
 模块最大的好处是大大提高了代码的可维护性。其次，编写代码不必从零开始。当一个模块编写|
 完毕，就可以被其他地方引用。我们在编写程序的时候，也经常引用其他模块，包括Python内置|
 的模块和来自第三方的模块。使用模块还可以避免函数名和变量名冲突。相同名字的函数和变量|
 完全可以分别存在不同的模块中，因此，我们自己在编写模块时，不必考虑名字会与其他模块冲|
 突。但是也要注意，尽量不要与内置函数名字冲突。如果不同的人编写的模块名相同怎么办？为|
 了避免模块名冲突，Python又引入了按目录来组织模块的方法，称为包（Package）。举个例子 |
 ，一个abc.py的文件就是一个名字叫abc的模块，一个xyz.py的文件就是一个名字叫xyz的模块。|
 现在，假设我们的abc和xyz这两个模块名字与其他模块冲突了，于是我们可以通过包来组织模块|
 ，避免冲突。方法是选择一个顶层包名，比如mycompany，按照如下目录存放：               |
 |mycompany
 |  __init__.py
 |  abc.py
 |  xyz.py                                                                           |
 引入了包以后，只要顶层的包名不与别人冲突，那所有模块都不会与别人冲突。现在，abc.py模|
 块的名字就变成了mycompany.abc，类似的，xyz.py的模块名变成了mycompany.xyz。请注意，每|
 一个包目录下面都会有一个__init__.py的文件，这个文件是必须存在的，否则，Python就把这 |
 个目录当成普通目录，而不是一个包。__init__.py可以是空文件，也可以有Python代码，因为 |
 __init__.py本身就是一个模块，而它的模块名就是mycompany。类似的，可以有多级目录，组成|
 多级层次的包结构。比如如下的目录结构：
 |mycompany-web
 |  |web
 |  |  |__init__.py
 |  |  |utils.py
 |  |  |www.py
 |  |__init__.py  
 |  |abc.py
 |  |utils.py
 |  |xyz.py                                                                          |
 文件www.py的模块名就是mycompany.web.www，两个文件utils.py的模块名分别是             |
 mycompany.utils和mycompany.web.utils。mycompany.web也是一个模块。                   |

----> 2 使用模块                                                                     |
 Python本身就内置了很多非常有用的模块，只要安装完毕，这些模块就可以立刻使用。

#我们以内建的sys模块为例，编写一个hello的模块：
#!/usr/bin/env python
# -*- coding: utf-8 -*-

' a test module '

__author__ = 'Michael Liao'

import sys

def test():
    args = sys.argv
    if len(args)==1:
        print 'Hello, world!'
    elif len(args)==2:
        print 'Hello, %s!' % args[1]
    else:
        print 'Too many arguments!'

if __name__=='__main__':
    test()
#第1行和第2行是标准注释，第1行注释可以让这个hello.py文件直接在Unix/Linux/Mac上运
#行，第2行注释表示.py文件本身使用标准UTF-8编码；
#第4行是一个字符串，表示模块的文档注释，任何模块代码的第一个字符串都被视为模块的
#文档注释；
#第6行使用__author__变量把作者写进去，这样当你公开源代码后别人就可以瞻仰你的大
#名；

#以上就是Python模块的标准文件模板，当然也可以全部删掉不写，但是，按标准办事肯定
#没错。

#后面开始就是真正的代码部分。
import sys
#导入sys模块后，我们就有了变量sys指向该模块，利用sys这个变量，就可以访问sys模块
#的所有功能。
#sys模块有一个argv变量，用list存储了命令行的所有参数。argv至少有一个元素，因为
#第一个参数永远是该.py文件的名称，例如：
#运行python hello.py获得的sys.argv就是['hello.py']；

#运行python hello.py Michael获得的sys.argv就是['hello.py', 'Michael]。

#最后，注意到这两行代码：

if __name__=='__main__':
    test()
#当我们在命令行运行hello模块文件时，Python解释器把一个特殊变量__name__置为
#__main__，而如果在其他地方导入该hello模块时，if判断将失败，因此，这种if测试可
#以让一个模块通过命令行运行时执行一些额外的代码，最常见的就是运行测试。
#我们可以用命令行运行hello.py看看效果：
$ python hello.py
Hello, world!
$ python hello.py Michael
Hello, Michael!
#如果启动Python交互环境，再导入hello模块：
$ python
Python 2.7.5 (default, Aug 25 2013, 00:04:04) 
[GCC 4.2.1 Compatible Apple LLVM 5.0 (clang-500.0.68)] on darwin
Type "help", "copyright", "credits" or "license" for more information.
>>> import hello
>>>
#导入时，没有打印Hello, word!，因为没有执行test()函数。
#调用hello.test()时，才能打印出Hello, word!：
>>> hello.test()
Hello, world!

#******************************************************************************# 
#-->-->-->-->-->-->-->-->-->            3 别名             <--<--<--<--<--<--<-#
#******************************************************************************#
#导入模块时，还可以使用别名，这样，可以在运行时根据当前环境选择最合适的模块。比
#如Python标准库一般会提供StringIO和cStringIO两个库，这两个库的接口和功能是一样的
#，但是cStringIO是C写的，速度更快，所以，你会经常看到这样的写法：
try:
    import cStringIO as StringIO
except ImportError: # 导入失败会捕获到ImportError
    import StringIO
#这样就可以优先导入cStringIO。如果有些平台不提供cStringIO，还可以降级使用
#StringIO。导入cStringIO时，用import ... as ...指定了别名StringIO，因此，后续代
#码引用StringIO即可正常工作。

#还有类似simplejson这样的库，在Python 2.6之前是独立的第三方库，从2.6开始内置，所
#以，会有这样的写法：
try:
    import json # python >= 2.6
except ImportError:
    import simplejson as json # python <= 2.5
#由于Python是动态语言，函数签名一致接口就一样，因此，无论导入哪个模块后续代码都
#能正常工作。
#******************************************************************************# 
#-->-->-->-->-->-->-->-->-->           3 作用域            <--<--<--<--<--<--<-#
#******************************************************************************#
#在一个模块中，我们可能会定义很多函数和变量，但有的函数和变量我们希望给别人使用，
#有的函数和变量我们希望仅仅在模块内部使用。在Python中，是通过_前缀来实现的。

#正常的函数和变量名是公开的（public），可以被直接引用，比如：abc，x123，PI等；
#类似__xxx__这样的变量是特殊变量，可以被直接引用，但是有特殊用途，比如上面的
#__author__，__name__就是特殊变量，hello模块定义的文档注释也可以用特殊变量
#__doc__访问，我们自己的变量一般不要用这种变量名；

#类似_xxx和__xxx这样的函数或变量就是非公开的（private），不应该被直接引用，比如
#_abc，__abc等；

#之所以我们说，private函数和变量“不应该”被直接引用，而不是“不能”被直接引用，是
#因为Python并没有一种方法可以完全限制访问private函数或变量，但是，从编程习惯上
#不应该引用private函数或变量。

#private函数或变量不应该被别人引用，那它们有什么用呢？请看例子：

def _private_1(name):
    return 'Hello, %s' % name

def _private_2(name):
    return 'Hi, %s' % name

def greeting(name):
    if len(name) > 3:
        return _private_1(name)
    else:
        return _private_2(name)

#我们在模块里公开greeting()函数，而把内部逻辑用private函数隐藏起来了，这样，调
#用greeting()函数不用关心内部的private函数细节，这也是一种非常有用的代码封装和
#抽象的方法，即：
#外部不需要引用的函数全部定义成private，只有外部需要引用的函数才定义为public。

#******************************************************************************# 
#-->-->-->-->-->-->-->-->-->       3 使用__future__        <--<--<--<--<--<--<-#
#******************************************************************************#
#Python的每个新版本都会增加一些新的功能，或者对原来的功能作一些改动。有些改动是
#不兼容旧版本的，也就是在当前版本运行正常的代码，到下一个版本运行就可能不正常了。

#从Python 2.7到Python 3.x就有不兼容的一些改动，比如2.x里的字符串用'xxx'表示str，
#Unicode字符串用u'xxx'表示unicode，而在3.x中，所有字符串都被视为unicode，因此，
#写u'xxx'和'xxx'是完全一致的，而在2.x中以'xxx'表示的str就必须写成b'xxx'，以此表
#示“二进制字符串”。

#要直接把代码升级到3.x是比较冒进的，因为有大量的改动需要测试。相反，可以在2.7版
#本中先在一部分代码中测试一些3.x的特性，如果没有问题，再移植到3.x不迟。

#Python提供了__future__模块，把下一个新版本的特性导入到当前版本，于是我们就可以
#在当前版本中测试一些新版本的特性。举例说明如下：

#为了适应Python 3.x的新的字符串的表示方法，在2.7版本的代码中，可以通过
#unicode_literals来使用Python 3.x的新的语法：

# still running on Python 2.7

from __future__ import unicode_literals

print '\'xxx\' is unicode?', isinstance('xxx', unicode)
print 'u\'xxx\' is unicode?', isinstance(u'xxx', unicode)
print '\'xxx\' is str?', isinstance('xxx', str)
print 'b\'xxx\' is str?', isinstance(b'xxx', str)
#注意到上面的代码仍然在Python 2.7下运行，但结果显示去掉前缀u的'a string'仍是一个
#unicode，而加上前缀b的b'a string'才变成了str：

$ python task.py
'xxx' is unicode? True
u'xxx' is unicode? True
'xxx' is str? False
b'xxx' is str? True
#类似的情况还有除法运算。在Python 2.x中，对于除法有两种情况，如果是整数相除，结
#果仍是整数，余数会被扔掉，这种除法叫“地板除”：
>>> 10 / 3
3
#要做精确除法，必须把其中一个数变成浮点数：

>>> 10.0 / 3
3.3333333333333335
#而在Python 3.x中，所有的除法都是精确除法，地板除用//表示：
$ python3
Python 3.3.2 (default, Jan 22 2014, 09:54:40) 
[GCC 4.2.1 Compatible Apple LLVM 5.0 (clang-500.2.79)] on darwin
Type "help", "copyright", "credits" or "license" for more information.
>>> 10 / 3
3.3333333333333335
>>> 10 // 3
3
#如果你想在Python 2.7的代码中直接使用Python 3.x的除法，可以通过__future__模块的
#division实现：
from __future__ import division
print '10 / 3 =', 10 / 3
print '10.0 / 3 =', 10.0 / 3
print '10 // 3 =', 10 // 3
#结果如下：
10 / 3 = 3.33333333333
10.0 / 3 = 3.33333333333
10 // 3 = 3
#由于Python是由社区推动的开源并且免费的开发语言，不受商业公司控制，因此，Python的
#改进往往比较激进，不兼容的情况时有发生。Python为了确保你能顺利过渡到新版本，特
#别提供了__future__模块，让你在旧的版本中试验新版本的一些特性。
'''