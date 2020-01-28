# Modules and Packages

## Modules: The Big Picture  

Python module—the highest-level program organization unit, which packages program code and data for reuse, and provides selfcontained namespaces that minimize variable name clashes across your programs.  Each file is a module, and modules import other modules to use the names they define.  Modules are processed with two statements and one important function:

- import: Lets a client (importer) fetch a module as a whole
- from: Allows clients to fetch particular names from a module
- imp.reload (reload in 2.X):Provides a way to reload a module’s code without stopping Python  

Besides serving as the highest organizational structure, modules (and module packages) are also the highest level of code reuse in Python.  

### Why Use Modules?

All the names defined at the top level of a module file become attributes of the imported module object. Python’s modules allow us to link individual files into a larger program system. More specifically, modules have at least three roles:  

- Code reuse  
- System namespace partitioning  
- Implementing shared services or data  

### Python Program Architecture  

At a base level, a Python program consists of text files containing Python statements, with one main top-level file, and zero or more supplemental files known as modules.  

The top-level (a.k.a. script) file contains the main flow of control of your program—this is the file you run to launch your application. The module files are libraries of tools used to collect components used by the top-level file, and possibly elsewhere. Top-level files use tools defined in module files, and modules use tools defined in other modules.  

![python_module_01](F:\mygit\notes\language\python\images\python_module_01.PNG)

```python
def spam(text): # File b.py
    print(text, 'spam')
```

```python
import b # File a.py
b.spam('gumby') # Prints "gumby spam"
```

The code import b roughly means: Load the file b.py (unless it’s already loaded), and give me access to all its attributes through the name b.  

- import (and, as you’ll see later, from) statements execute and load other files on request.   
- import statements are executed at runtime;  
- import statement serves two purposes: it identifies the external file to be loaded, but it also becomes a variable assigned to the loaded module.  

Similarly, objects defined by a module are also created at runtime, as the import is executing: import literally runs statements in the target file one at a time to create its contents. Along the way, every name assigned at the top-level of the file becomes an attribute of the module, accessible to importers.  The code b.spam means: Fetch the value of the name spam that lives within the object b.  

### How Imports Work

In Python, imports are not just textual insertions of one file into another. They are really runtime operations that perform three distinct steps the first time a program imports a given file:

1. Find the module’s file: Python uses a standard module search path and known file types to locate the module file corresponding to an import statement.  

2. Compile it to byte code (if needed).

   After finding a source code file, Python next compiles it to byte code, if necessary.  If the byte code file is older than the source file (i.e., if you’ve changed the source) or was created by a different Python version, Python automatically regenerates the byte code when the program is run. In addition, if Python finds only a byte code file on the search path and no source, it simply loads the byte code directly;  only imported files leave behind .pyc files on your machine.  

3. Run the module’s code to build the objects it defines.  

   The final step of an import operation executes the byte code of the module. All statements in the file are run in turn, from top to bottom, and any assignments made to names during this step generate attributes of the resulting module object. For instance, def statements in a file are run at import time to create functions and assign attributes within the module to those functions. The functions can then be called later in the program by the file’s importers.

   Because this last import step actually runs the file’s code, if any top-level code in a module file does real work, you’ll see its results at import time. For example, top-level print statements in a module show output when the file is imported. Function def statements simply define objects for later use.  

   If you need to import a file again after it has already been loaded (for example, to support dynamic end-user customizations), you have to force the issue with an imp.reload call—a tool we’ll meet in the next chapter.  

### pycache /todo

### The Module Search Path

Roughly, Python’s module search path is composed of the concatenation of these major components, some of which are preset for you and some of which you can tailor to tell Python where to look:  

1. Home directory (automatic)

   Python first looks for the imported file in the home directory. The meaning of this entry depends on how you are running the code. When you’re running a program,  this entry is the directory containing your program’s top-level script file. When you’re working interactively, this entry is the directory in which you are working ( i.e., the current working directory).

2. PYTHONPATH directories (configurable)

   Next, Python searches all directories listed in your PYTHONPATH environment variable setting, from left to right. For instance, on Windows, you might use your Control Panel’s System icon to set PYTHONPATH to a list of directories separated by semicolons, like this:

   ```python
   c:\pycode\utilities;d:\pycode\package1
   ```

   Or you might instead create a text file called C:\Python33\pydirs.pth, which  looks like this:

   ```python
   c:\pycode\utilities
   d:\pycode\package1
   ```

3. Standard library directories (automatic)

   Next, Python automatically searches the directories where the standard library modules are installed on your machine. Because these are always searched, they normally do not need to be added to your PYTHONPATH or included in path files ( discussed next)

4. .pth path file directories (configurable)

   Next, a lesser-used feature of Python allows users to add directories to the module search path by simply listing them, one per line, in a text file whose name ends with a .pth suffix (for "path"). These path configuration files are a somewhat advanced installation-related feature; In short, text files of directory names dropped in an appropriate directory can serve roughly the same role as the PYTHONPATH environment variable setting. For instance, if you’re running Windows and Python 3.3, a file named myconfig.pth may be placed at the top level of the Python install directory (C:\Python33) or in the sitepackages subdirectory of the standard library there (C:\Python33\Lib\site-packages) to extend the module search path. On Unix-like systems, this file might be
   located in usr/local/lib/python3.3/site-packages or /usr/local/lib/site-python instead.  

5. The Lib\site-packages directory of third-party extensions (automatic)

   Finally, Python automatically adds the site-packages subdirectory of its standard library to the module search path. By convention, this is the place that most thirdparty extensions are installed, often automatically by the distutils utility described in an upcoming sidebar. Because their install directory is always part of the module search path, clients can import the modules of such extensions without any path settings.  

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

## Module Coding Basics

### Module Creation

To define a module, simply use your text editor to type some Python code into a text file, and save it with a “.py” extension; any such file is automatically considered a Python module. All the names assigned at the top level of the module become its attributes. 

For instance, if you type the following def into a file called module1.py and import it, you create a module object with one attribute--the name printer, which happens to be a reference to a function object:

```python
def printer(x): # Module attribute
    print(x)
```

It is also possible to create a Python module by writing code in an external language such as C, C++, and others (e.g., Java, in the Jython implementation of the language). Such modules are called extension modules, and they are generally used to wrap up external libraries for use in Python scripts. When imported by Python code, extension modules look and feel the same as modules coded as Python source code files--they are accessed with import statements, and they provide functions and objects as module attributes. Extension modules are beyond the scope of this book; see Python’s standard manuals or advanced texts such as Programming Python for more details.

### Module Usage

####  The import Statement

In the first example, the name module1 serves two different purposes--it identifies an external file to be loaded, and it becomes a variable in the script, which references the module object after the file is loaded:

```python
>>> import module1 # Get module as a whole (one or more)
>>> module1.printer('Hello world!') # Qualify to get names
Hello world!
```

The import statement simply lists one or more names of modules to load, separated by commas. Because it gives a name that refers to the whole module object, we  must go through the module name to fetch its attributes (e.g., module1.printer).

####  The from Statement

By contrast, because from copies specific names from one file over to another scope, it allows us to use the copied names directly in the script without going through the module (e.g., printer):

```python
>>> from module1 import printer # Copy out a variable (one or more)
>>> printer('Hello world!') # No need to qualify name
Hello world!
```

This form of from allows us to list one or more names to be copied out, separated by commas. We can use it directly instead of naming the enclosing module. In fact, we must; from doesn’t assign the name of the module itself. As you’ll see in more detail later, the from statement is really just a  minor extension to the import statement--it imports the module file as usual  ( running the full three-step procedure of the preceding chapter ), but adds an extra step that copies one or more names (not objects) out of the file. The entire file is loaded, but you’re given names for more direct access to its parts.  

#### The from * Statement

Finally, the next example uses a special form of from: when we use a * instead of specific names, we get copies of all names assigned at the top level of the referenced module. Here again, we can then use the copied name printer in our script without going through the module name:

```python
>>> from module1 import * # Copy out _all_ variables
>>> printer('Hello world!')
Hello world!
```

Technically, both import and from statements invoke the same import operation; the from * form simply adds an extra step that copies all the names in the module into the importing scope. 

Just like def, import and from are executable statements, not compile-time declarations. They may be nested in if tests, to select among options; appear in function defs, to be loaded only on calls (subject to the preceding note); be used in try statements, to provide defaults; and so on.  Also, like def, the import and from are implicit assignments:

- import assigns an entire module object to a single name.
- from assigns one or more names to objects of the same names in another module.

To illustrate, consider the following file, small.py:

```python
x = 1
y = [1, 2]
```

When importing with from, we copy names to the importer’s scope that initially share objects referenced by the module’s names:

```python
% python
>>> from small import x, y # Copy two names out
>>> x = 42 # Changes local x only
>>> y[0] = 42 # Changes shared mutable in place
```

Here, x is not a shared mutable object, but y is. The names y in the importer and the importee both reference the same list object, so changing it from one place changes it in the other:

```python
>>> import small # Get module name (from doesn't)
>>> small.x # Small's x is not my x
1
>>> small.y # But we share a changed mutable
[42, 2]
```

At least conceptually, a from statement like this one:

```python
from module import name1, name2 # Copy these two names out (only)
```

is equivalent to this statement sequence:

```python
import module # Fetch the module object
name1 = module.name1 # Copy names out by assignment
name2 = module.name2
del module # Get rid of the module name
```

Like all assignments, the from statement creates new variables in the importer, which initially refer to objects of the same names in the imported file. Only the names are copied out, though, not the objects they reference, and not the name of the module itself. When we use the from * form of this statement (from module import *), the equivalence is the same, but all the top-level names in the module are copied over to the importing scope this way.  

## Module Packages  

In addition to a module name, an import can name a directory path. A directory of Python code is said to be a package, so such imports are known as package imports. In effect, a package import turns a directory on your computer into another Python namespace, with attributes corresponding to the subdirectories and module files that the directory contains  

### Package Import Basics  

```python
import dir1.dir2.mod  
from dir1.dir2.mod import x  
```

The “dotted” path in these statements is assumed to correspond to a path through the directory hierarchy on your computer, leading to the file mod.py. That is, the preceding statements indicate that on your machine there is a directory dir1, which has a subdirectory dir2, which contains a module file mod.py (or similar) . Furthermore, these imports imply that dir1 resides within some container directory dir0, which is a component of the normal Python module search path.   

```python
dir0\dir1\dir2\mod.py # Or mod.pyc, mod.so, etc.
```

### Package `__init__.py` Files  

If you choose to use package imports, there is one more constraint you must follow: at least until Python 3.3, each directory named within the path of a package import statement must contain a file named `__init__.py`, or your package imports will fail. More formally, for a directory structure such as this:

```python
dir0\dir1\dir2\mod.py
```

and an import statement of the form:

```python
import dir1.dir2.mod
```

the following rules apply:

- dir1 and dir2 both must contain an __init__.py file.
- dir0, the container, does not require an __init__.py file; this file will simply be ignored if present.
- dir0, not dir0\dir1, must be listed on the module search path sys.path.  

The net effect is that this example’s directory structure should be as follows, with indentation designating directory nesting:

```python
dir0\ # Container on module search path
    dir1\  
        __init__.py
    dir2\
        __init__.py
        mod.py
```

The `__init__.py` files can contain Python code, just like normal module files. Their names are special because their code is run automatically the first time a Python program imports a directory, and thus serves primarily as a hook for performing initialization steps required by the package. These files can also be completely empty, though, and sometimes have additional roles--as the next section explains.

### Package Import Example

The following three files are coded in a directory dir1 and its subdirectory dir2—comments give the pathnames of these files:  

```python
# dir1\__init__.py
print('dir1 init')
x = 1

# dir1\dir2\__init__.py
print('dir2 init')
y = 2  

# dir1\dir2\mod.py
print('in mod.py')
z = 3  
```

Here, dir1 will be either an immediate subdirectory of the one we’re working in (i.e., the home directory), or an immediate subdirectory of a directory that is listed on the module search path (technically, on sys.path). Either way, dir1’s container does not need an `__init__.py` file.  

import statements run each directory’s initialization file the first time that directory is traversed, as Python descends the path;   

```python
C:\code> python # Run in dir1's container directory
>>> import dir1.dir2.mod # First imports run init files
dir1 init
dir2 init
in mod.py
>>>
>>> import dir1.dir2.mod # Later imports do not
>>> from imp import reload # from needed in 3.X only
>>> reload(dir1)
dir1 init
<module 'dir1' from '.\\dir1\\__init__.py'>
>>>
>>> reload(dir1.dir2)
dir2 init
<module 'dir1.dir2' from '.\\dir1\\dir2\\__init__.py'>
```

Once imported, the path in your import statement becomes a nested object path in your script. Here, mod is an object nested in the object dir2, which in turn is nested in the object dir1:

```python
>>> dir1
<module 'dir1' from '.\\dir1\\__init__.py'>
>>> dir1.dir2
<module 'dir1.dir2' from '.\\dir1\\dir2\\__init__.py'>
>>> dir1.dir2.mod
<module 'dir1.dir2.mod' from '.\\dir1\\dir2\\mod.py'>

>>> dir1.x
1
>>> dir1.dir2.y
2
>>> dir1.dir2.mod.z
3
```

If you try to access dir2 or mod directly, you’ll get an error:  

```python
>>> dir2.mod
NameError: name 'dir2' is not defined
>>> mod.z
NameError: name 'mod' is not defined
```

It’s often more convenient, therefore, to use the from statement with packages to avoid retyping the paths at each access.   

```python
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
```









## 参考：

learning python （python学习手册）



