

# PART--Functions and Generators

# Function Basics

一个函数就是将一些语句集合在一起的部件，函数可以在程序中重复调用。函数是为了代码最大程度的重用和最小化代码冗余而提供的最基本的程序结构。

## Why Use Functions 

As a brief introduction, functions serve two primary development roles:

- Maximizing code reuse and minimizing redundancy  
- Procedural decomposition   

## Coding Functions

### def Statements  

Def语句创建一个函数对象并将其赋值给一个变量。Def语句的一般格式如下：

```python
def name(arg1, arg2,... argN):
    statements...
    return value
```

Def语句首行定义了函数名（name），并在括号里包含了0个或多个参数（有时称为形参）。有个一代码块紧随其后，构成了函数的主体，每当调用函数时均会执行这些语句。函数主体一般包含一个return语句，可以出现在函数主体的任何地方，表示函数调用的结束，并讲结果返回至调用处。一个没有返回值的函数自动返回none对象。

### def Executes at Runtime  

Python的Def语句是一个可执行的语句：当他运行的时候，他创建一个新的函数对象并将其赋值给一个变量名。在Def运行之后，可以在程序中通过在函数名后增加括号调用或运行这个函数。括号中包括一个或多个对象参数，这些参数将会传递（赋值）给函数头部的参数名。

```python
>>> def times(x, y): # Create and assign function
...    return x * y  # Body executed when called
...
>>> times(2, 4)      # Arguments in parentheses
8
>>> x = times(3.14, 4) 
>>> x 
12.56
>>> times('Ni', 4)    # Functions are "typeless"，函数多态性说明 todo
'NiNiNiNi'
```

Def语句可以出现在任何一语句可以出现的地方，甚至是嵌套在其他语句中。以下代码段是合法的：

```python
if test:
    def func(): # Define func this way
        ...
else:
    def func(): # Or else this way
        ...
...
func() # Call the version selected and built
```

因为函数定义是实时发生的，函数名没有特别之处，关键在于函数名所引用的那个对象。

```python
othername = func # Assign function object
othername() # Call func again  
```

这里，将函数赋值给一个不同的变量，并通过新的变量名进行了调用。除了调用以外，函数允许任意的属性附加到记录信息以供随后使用：

```python
def func(): ... # Create function object
func() # Call object
func.attr = value # Attach attributes 
```

# 作用域

Python中的变量名在第一次赋值时已经创建，并且必须经过赋值后才能够使用。Python创建、改变或查找变量名都是在所谓的命名空间（一个保存变了名的地方）中进行的。Python将一个变量名被赋值的地点关联为一个特定的命名空间，代码中给一个变量赋值的地方决定了这个变量将存在于哪个命名空间，也就是它可见的范围。

- Local(function)，本地作用域(函数)：每次对函数的调用都创建了一个新的本地作用域。一个函数内部的任何类型的赋值都会把一个名称划定为本地的（声明为global的除外）。这包括=语句、import中的模块名称、def中的函数名称、函数参数名称等。
- Enclosing function locals：names in the local scope of any all enclosing functions(def or lambda), from inner to outer
- Global(module)，全局作用域：每个模块都是一个全局作用域（也就是说，一个创建于模块文件顶层的变量的命名空间）。全局作用域的作用范围仅限于单个文件，Python中没有基于一个单个的、无所不包的情景文件的全局作用域。
- Built-in(Python)：Names preassigned in built-in names module:open, range, SyntaxError...

LEGB作用域查找原则：当引用一个变量时，Python按以下顺序依次进行查找，从本地变量中，在任意上层函数的作用域，在全局作用域，最后在内置作用域中查找。第一个能够完成查找的就算成功。

- 赋值的变量名除非声明为全局变量或非本地变量，否则均为本地变量。
- 所有其他的变量名都可以归纳为本地、全局或者内置的。

在交互模式运行的代码实际上真的输入到一个叫做__main__的内置模块中，这个模块就像一个模块文件一样工作。因此，交互模式也在一个模块中创建名称，并由此遵守常规的作用域规则。

```python
# Global scope
X = 99         # X and func assigned in module: global

def func(Y):   # Y and Z assigned in function: locals
    # Local scope
    Z = X + Y  # X is a global
    return Z
func(1)        # func in module: result=100


```

- Global names: X, func
  X is global because it’s assigned at the top level of the module file; it can be referenced inside the function as a simple unqualified variable without being declaredglobal. func is global for the same reason; the def statement assigns a function object to the name func at the top level of the module.
- Local names: Y, Z
  Y and Z are local to the function (and exist only while the function runs) because they are both assigned values in the function definition: Z by virtue of the = statement, and Y because arguments are always passed by assignment.

## 内置作用域

内置作用域是通过一个名为\__builtin__的标准库模块来实现的，这个变量名自身并没有放入内置作用域内，必须导入这个文件才能够使用它。

```python
>>> import builtins
>>> dir(builtins)
['ArithmeticError', 'AssertionError', 'AttributeError', 'BaseException',
'BlockingIOError', 'BrokenPipeError', 'BufferError', 'BytesWarning',
Python Scope Basics | 491...many more names omitted...
'ord', 'pow', 'print', 'property', 'quit', 'range', 'repr', 'reversed',
'round', 'set', 'setattr', 'slice', 'sorted', 'staticmethod', 'str', 'sum',
'super', 'tuple', 'type', 'vars', 'zip']
```

这个列表中的变量名组成了Python中的内置作用域。Python最后将自动搜索这个模块，我们能够使用这些变量名而不需要导入任何模块，也可以手动导入\__builtin__模块。

```python
>>> zip # The normal way
<class 'zip'>
>>> import builtins # The hard way: for customizations
>>> builtins.zip
<class 'zip'>
>>> zip is builtins.zip # Same object, different lookups
True
```

本地作用域的变量名可能会覆盖在全局作用域和内置作用域的有着相同变量名的变量，而全局变量名有可能覆盖内置的变量名。

```python
def hider():
    open = 'spam' # Local variable, hides built-in here
    ...
    open('data.txt') # Error: this no longer opens a file in this scope!
```

函数也能够简单地使用本地变量名隐藏同名的全局变量。

```python
X = 88 # Global X
def func():
    X = 99 # Local X: hides global, but we want this here
func()
print(X) # Prints 88: unchanged
```

## 作用域和嵌套函数

在增加了嵌套的函数作用域后，变量的查找法复杂了一些。  Within a function:

- A reference (X) looks for the name X first in the current local scope (function); then in the local scopes of any lexically enclosing functions in your source code, from inner to outer; then in the current global scope (the module file); and finally in the built-in scope (the module builtins). global declarations make the search begin in the global (module file) scope instead.
- An assignment (X = value) creates or changes the name X in the current local scope, by default. If X is declared global within the function, the assignment creates or changes the name X in the enclosing module’s scope instead. If, on the other hand, X is declared nonlocal within the function in 3.X (only), the assignment changes the name X in the closest enclosing function’s local scope.  

```python
X = 99           # Global scope name: not used
def f1():
    X = 88       # Enclosing def local
    def f2():
        print(X) # Reference made in nested def
    f2()         # 实际测试此处不打印，why？
f1()             # Prints 88: enclosing def local
```

嵌套的def在函数f1调用时运行，这个def生成一个函数，并将其赋值给变量f2，f2是f1的本地作用域内的一个本地变量。在此情况下，f2是一个临时函数，仅在f1内部执行的过程中存在，并且只对f1中的代码可见。在f2内部，当打印变量x时，x引用了存在于函数f1整个本地作用域内的变量x的值。因为函数能够在整改def声明内获取变量名，通过LEGB查找法则，f2内的x自动映射到了f1的x。

```python
def f1():
    X = 88
    def f2():
        print(X) # Remembers X in enclosing def scope
    return f2    # Return f2 but don't call it
action = f1()    # Make, return function
action()         # Call it now: prints 88
```

在这个代码中，f2运行时在f1运行后发生的，f2记住了在f1中嵌套作用域中的x，尽管f1已经不处于激活状态。这种行为有时也叫做闭合（closure）或者工厂函数--一个能够记住嵌套作用域的变量值得函数。

## global语句

global语句是一个命名空间的声明，它告诉Python函数打算生产一个或多个全局变量名。也就是说，存在于整个模块内部作用域（命名空间）的变量名。global语句其后跟着一个或多个逗号分开的变量名。

```python
X = 88 # Global X
def func():
    global X
    X = 99 # Global X: outside def
func()
print(X) # Prints 99

y, z = 1, 2 # Global variables in module
def all_global():
   global x # Declare globals assigned
   x = y + z # No need to declare y, z: LEGB rule
```

这里，x、y和z都是all_global函数内的全局变量。y和z是全局变量，因为他们不是在函数内赋值的。x是全局变量，因为他通过global语句使自己明确地映射到了模块的作用域。注意x在函数运行前可能并不存在。

## nonlocal语句

Python3.0引入了一条新的nonlocal语句，他只在一个函数内有意义：

```python
def func():
​    nonlocal name1, name2, ...
```

这条语句允许一个嵌套函数来修改在一个语法嵌套函数的作用域中定义的一个或多个名称。nonlocal使得对该语句中列出的名称的查找从嵌套的def的作用域中开始，而不是从声明函数的本地作用域开始。

```python
>>> def tester(start):
        state = start # Each call gets its own state
        def nested(label):
            nonlocal state # Remembers state in enclosing scope
            print(label, state)
            state += 1 # Allowed to change it if nonlocal
        return nested
>>> F = tester(0)
>>> F('spam') # Increments state on each call
spam 0
>>> F('ham')
ham 1
>>> F('eggs')
eggs 2
>>> G = tester(42) # Make a new tester that starts at 42
>>> G('spam')
spam 42
>>> G('eggs') # My state information updated to 43
eggs 43
>>> F('bacon') # But F's is where it left off: at 3
bacon 3 # Each call has different state information
```

在Python3.0下，如果我们在nested中把tester作用域中的state声明为一个nonlocal，我们就可以在nested函数中修改它了。

```python
>>> def tester(start):
        def nested(label):
            nonlocal state # Nonlocals must already exist in enclosing def!
            state = 0
            print(label, state)
        return nested

SyntaxError: no binding for nonlocal 'state' found

>>> def tester(start):
        def nested(label):
            global state # Globals don't have to exist yet when declared
            state = 0    # This creates the name in the module now
            print(label, state)
    return nested
>>> F = tester(0)
>>> F('abc')
abc 0
>>> state
0
```

# Arguments  

## Argument-Passing Basics  

todo

### Arguments and Shared References

参数在Python中总是通过赋值进行传递(arguments are always passed by assignment in Python），传入的对象赋值给了在def头部的变量名。函数参数在实际中只是Python赋值的另一个实例而已。因为引用是以指针的形式实现的，所有的参数实际上都是通过指针进行传递的。作为参数被传递的对象从来不自动拷贝。

```python
>>> def f(a): # @a is assigned to (references) the passed object
        a = 99 # Changes local variable @a only. 
>>> b = 88
>>> f(b) # a and b both reference same 88 initially
>>> print(b) # b is not changed
88
```

在使用f(b)调用函数的时候，变量a赋值了对象88。在函数中修改a对于调用函数的地方没有任何影响，它直接把本地变量a重置为一个完全不同的对象。

```python
>>> def changer(a, b): # Arguments assigned references to objects
        a = 2 # Changes local name's value only
        b[0] = 'spam' # Changes shared object in place
>>> X = 1
>>> L = [1, 2] # Caller:
>>> changer(X, L) # Pass immutable and mutable objects
>>> X, L # X is unchanged, L is different!
(1, ['spam', 2])
```

当参数传递列表和字典这样的可修改对象时，需要注意。changer中的第二条赋值语句没有修改b，修改的时b当前所引用的对象的一部分。名称L也没有改变，它仍然引用同样的、修改后的对象（这个对象在函数调用时被修改了）。

![python_function_01](F:\mygit\notes\language\python\images\python_function_01.PNG)

### Avoiding Mutable Argument Changes  

Arguments are normally passed to functions by reference because that is what we normally want. It means we can pass large objects around our programs without making multiple copies along the way, and we can easily update these objects as we go.   

If we don’t want in-place changes within functions to impact objects we pass to them, though, we can simply make explicit copies of mutable objects  

```python
L = [1, 2]
changer(X, L[:]) # Pass a copy, so our 'L' does not change
```

We can also copy within the function itself, if we never want to change passed-in objects, regardless of how the function is called:

```python
def changer(a, b):
    b = b[:] # Copy input list so we don't impact caller
    a = 2
    b[0] = 'spam' # Changes our list copy only

L = [1, 2]
changer(X, tuple(L)) # Pass a tuple, so changes are errors
```

### Simulating Output Parameters and Multiple Results  

because return can send back any sort of object, it can return multiple values by packaging them in a tuple or other collection type.  

```python
>>> def multiple(x, y):
        x = 2 # Changes local names only
        y = [3, 4]
        return x, y # Return multiple new values in a tuple
>>> X = 1
>>> L = [1, 2]
>>> X, L = multiple(X, L) # Assign results to caller's names
>>> X, L
(2, [3, 4])
```

It looks like the code is returning two values here, but it’s really just one—a two-item tuple with the optional surrounding parentheses omitted. After the call returns, we can use tuple assignment to unpack the parts of the returned tuple.   

## Special Argument-Matching Modes  

By default, arguments are matched by position, from left to right, and you must pass exactly as many arguments as there are argument names in the function header. However, you can also specify matching by name, provide default values, and use collectors for extra arguments.  

### Argument Matching Basics  /todo

### Argument Matching Syntax /todo

## Keyword and Default Examples  

If you don’t use any special matching syntax, Python matches names by position from left to right  If you don’t use any special matching syntax, Python matches names by position from left to right. Here, we pass by position—a is matched to 1, b is matched to 2, and so on.

```python
>>> def f(a, b, c): print(a, b, c)
>>> f(1, 2, 3)
1 2 3
```

### Keywords  

Keyword arguments allow us to match by name, instead of by position. 

```python
>>> f(c=3, b=2, a=1)
1 2 3

>>> f(1, c=3, b=2) # a gets 1 by position, b and c passed by name
1 2 3
```

Python matches the name c in the call to the argument named c in the function definition’s header, and then passes the value 3 to that argument.  All positionals are matched first from left to right in the header, before keywords are matched by name.

### Defaults  

In short, defaults allow us to make selected function arguments optional; if not passed a value, the argument is assigned its default before the function runs.   

```python
>>> def f(a, b=2, c=3): print(a, b, c) # a required, b and c optional
    
>>> f(1) # Use defaults
1 2 3
>>> f(a=1)
1 2 3

>>> f(1, 4) # Override defaults
1 4 3
>>> f(1, 4, 5)
1 4 5

>>> f(1, c=6) # Choose defaults
1 2 6
```

When we call this function, we must provide a value for a, either by position or by keyword; however, providing values for b and c is optional. If we don’t pass values to b and c, they default to 2 and 3, respectively. If we pass two values, only c gets its default, and with three values, no defaults are used.

### Combining keywords and defaults

```python
def func(spam, eggs, toast=0, ham=0): # First 2 required
    print((spam, eggs, toast, ham))
func(1, 2) # Output: (1, 2, 0, 0)
func(1, ham=1, eggs=0) # Output: (1, 0, 0, 1)
func(spam=1, eggs=0) # Output: (1, 0, 0, 0)
func(toast=1, eggs=2, spam=3) # Output: (3, 2, 1, 0)
func(1, 2, 3, 4) # Output: (1, 2, 3, 4)
```

Notice again that when keyword arguments are used in the call, the order in which the arguments are listed doesn’t matter; Python matches by name, not by position. The caller must supply values for spam and eggs, but they can be matched by position or by name. Again, keep in mind that the form name=value means different things in the call and the def: a keyword in the call and a default in the header.  

## Arbitrary Arguments Examples  

### Headers: Collecting arguments  

The first use, in the function definition, collects unmatched positional arguments into a tuple:  

```python
>>> def f(*args): print(args)
```

When this function is called, Python collects all the positional arguments into a new tuple and assigns the variable args to that tuple. Because it is a normal tuple object, it can be indexed, stepped through with a for loop, and so on:  

```python
>>> f()
()
>>> f(1)
(1,)
>>> f(1, 2, 3, 4)
(1, 2, 3, 4)
```

The ** feature is similar, but it only works for keyword arguments—it collects them into a new dictionary, which can then be processed with normal dictionary tools.   

```python
>>> def f(**args): print(args)
>>> f()
{}
>>> f(a=1, b=2)
{'a': 1, 'b': 2}
```

Finally, function headers can combine normal arguments, the *, and the ** to implement wildly flexible call signatures. For instance, in the following, 1 is passed to a by position, 2 and 3 are collected into the pargs positional tuple, and x and y wind up in the kargs keyword dictionary:  

```python
>>> def f(a, *pargs, **kargs): print(a, pargs, kargs)
>>> f(1, 2, 3, x=1, y=2)
1 (2, 3) {'y': 2, 'x': 1}
```

### Calls: Unpacking arguments

In all recent Python releases, we can use the * syntax when we call a function, too. In this context, its meaning is the inverse of its meaning in the function definition—it unpacks a collection of arguments, rather than building a collection of arguments.   

```python
>>> def func(a, b, c, d): print(a, b, c, d)
>>> args = (1, 2)
>>> args += (3, 4)
>>> func(*args) # Same as func(1, 2, 3, 4)
1 2 3 4  
```

Similarly, the ** syntax in a function call unpacks a dictionary of key/value pairs into separate keyword arguments:

```python
>>> args = {'a': 1, 'b': 2, 'c': 3}
>>> args['d'] = 4 
>>> func(**args) # Same as func(a=1, b=2, c=3, d=4)
1 2 3 4
```

Again, we can combine normal, positional, and keyword arguments in the call in very flexible ways:
```python
>>> func(*(1, 2), **{'d': 4, 'c': 3}) # Same as func(1, 2, d=4, c=3)
1 2 3 4
>>> func(1, *(2, 3), **{'d': 4}) # Same as func(1, 2, 3, d=4)
1 2 3 4
>>> func(1, c=3, *(2,), **{'d': 4}) # Same as func(1, 2, c=3, d=4)
1 2 3 4
>>> func(1, *(2, 3), d=4) # Same as func(1, 2, 3, d=4)
1 2 3 4
>>> func(1, *(2,), c=3, **{'d':4}) # Same as func(1, 2, c=3, d=4)
1 2 3 4
```

# Advanced Function Topics  

## Anonymous Functions: lambda  

Besides the def statement, Python also provides an expression form that generates function objects. Because of its similarity to a tool in the Lisp language, it’s called lambda. Like def, this expression creates a function to be called later, but it returns the function instead of assigning it to a name. This is why lambdas are sometimes known as anonymous (i.e., unnamed) functions. In practice, they are often used as a way to
inline a function definition, or to defer execution of a piece of code.

### lambda Basics

The lambda’s general form is the keyword lambda, followed by one or more arguments, followed by an expression after a colon:

```python
lambda argument1, argument2,... argumentN : expression using arguments  
```

- lambda is an expression, not a statement. As an expression, lambda returns a value (a new function) that can optionally be assigned a name. In contrast, the def statement always assigns the new function to the name in the header, instead of returning it as a result.    
- lambda’s body is a single expression, not a block of statements. Because it is limited to an expression, a lambda is less general than a def—you can only squeeze so much logic into a lambda body without using statements such as if.     

```python
>>> def func(x, y, z): return x + y + z
>>> func(2, 3, 4)
9

>>> f = lambda x, y, z: x + y + z
>>> f(2, 3, 4)
9

>>> x = (lambda a="fee", b="fie", c="foe": a + b + c)
>>> x("wee")
'weefiefoe'

>>> def knights():
title = 'Sir'
action = (lambda x: title + ' ' + x) # Title in enclosing def scope
return action # Return a function object
>>> act = knights()
>>> msg = act('robin') # 'robin' passed to x
>>> msg
'Sir robin'
>>> act # act: a function, not its result
<function knights.<locals>.<lambda> at 0x00000000029CA488>
```

lambda is also commonly used to code jump tables, which are lists or dictionaries of actions to be performed on demand. For example:

```python
L = [lambda x: x ** 2, # Inline function definition
lambda x: x ** 3,
lambda x: x ** 4] # A list of three callable functions
for f in L:
print(f(2)) # Prints 4, 8, 16
print(L[0](3)) # Prints 9
```

```python
>>> key = 'got'
>>> {'already': (lambda: 2 + 2),
'got': (lambda: 2 * 4),
'one': (lambda: 2 ** 6)}[key]()
8  
```

Here, when Python makes the temporary dictionary, each of the nested lambdas generates and leaves behind a function to be called later. Indexing by key fetches one of those functions, and parentheses force the fetched function to be called. When coded this way, a dictionary becomes a more general multiway branching tool than what I could fully show you in Chapter 12’s coverage of if statements





# 参考：

learning python （python学习手册）















