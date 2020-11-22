# PART--Functions and Generators



# Function Basics

In simple terms, a function is a device that groups a set of statements so they can be run more than once in a program—a packaged procedure invoked by name.  Functions are also the most basic program structure Python provides for maximizing code reuse, and lead us to the larger notions of program design.   

Table 16-1 previews the primary function-related tools we’ll study in this part of the book—a set that includes call expressions, two ways to make functions (def and lambda), two ways to manage scope visibility (global and nonlocal), and two ways to send results back to callers (return and yield).  

Table 16-1. Function-related statements and expressions 

| Statement or expression | Examples                                                     |
| ----------------------- | ------------------------------------------------------------ |
| Call expressions        | myfunc('spam', 'eggs', meat=ham, *rest)                      |
| def                     | def printer(messge): <br/>    print('Hello ' + message)      |
| return                  | def adder(a, b=1, *c): <br/>    return a + b + c[0]          |
| global                  | x = 'old'<br/>def changer():<br/>    global x; <br/>    x = 'new' |
| nonlocal (3.X)          |                                                              |
| yield                   | def squares(x): <br/>    for i in range(x): yield i ** 2     |
| lambda                  | `funcs = [lambda x: x**2, lambda x: x**3]`                   |

一个函数就是将一些语句集合在一起的部件，函数可以在程序中重复调用。函数是为了代码最大程度的重用和最小化代码冗余而提供的最基本的程序结构。

## Why Use Functions 

As a brief introduction, functions serve two primary development roles:

- Maximizing code reuse and minimizing redundancy  
- Procedural decomposition   

## Coding Functions

Here is a brief introduction to the main concepts behind Python functions, all of which we will study in this part of the book:  

- def is executable code. 
- def creates an object and assigns it to a name. 
- lambda creates an object but returns it as a result. 
- return sends a result object back to the caller. 
- yield sends a result object back to the caller, but remembers where it left off. 
- global declares module-level variables that are to be assigned. 
- nonlocal declares enclosing function variables that are to be assigned. 
- Arguments are passed by assignment (object reference). 
- Arguments are passed by position, unless you say otherwise. 
- Arguments, return values, and variables are not declared. 

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

# Scopes

This chapter moves on to present the details behind Python’s scopes—the places where variables are defined and looked up. Like module files, scopes help prevent name clashes across your program’s code: names defined in one program unit don’t interfere with names in another.

## Python Scope Basics  

When you use a name in a program,  Python creates, changes, or looks up the name in what is known as a **namespace**—a place where names live. Python uses the location of the assignment of a name to associate it with (i.e., bind it to) a particular namespace. In other words, the place where you assign a name in your source code determines the namespace it will live in, and hence its scope of visibility.    

Besides packaging code for reuse, functions add an extra namespace layer to your programs to minimize the potential for collisions among variables of the same name—by default, all names assigned inside a function are associated with that function’s namespace, and no other. This rule means that:  

- Names assigned inside a def can only be seen by the code within that def. You cannot even refer to such names from outside the function.  
- Names assigned inside a def do not clash with variables outside the def, even if the same names are used elsewhere.   

Variables may be assigned in three different places, corresponding to three different scopes:

- If a variable is assigned inside a def, it is local to that function.
- If a variable is assigned in an enclosing def, it is nonlocal to nested functions.
- If a variable is assigned outside all defs, it is global to the entire file.  

### Scope Details 

Functions define a local scope and modules define a global scope with the following properties:  

- **The enclosing module is a global scope.** Each module is a global scope—that is, a namespace in which variables created (assigned) at the top level of the module file live. Global variables become attributes of a module object to the outside world after imports but can also be used as simple variables within the module file itself  
- **The global scope spans a single file only.** Don’t be fooled by the word “global” here—names at the top level of a file are global to code within that single file only. There is really no notion of a single, all-encompassing global file-based scope in Python.  When you hear “global” in Python, think “module.”  
- **Assigned names are local unless declared global or nonlocal.** By default, all the names assigned inside a function definition are put in the local scope (the namespace associated with the function call). If you need to assign a name that lives at the top level of the module enclosing the function, you can do so by declaring it in a global statement inside the function. If you need to assign a name that lives in an enclosing def, as of Python 3.X you can do so by declaring it in a nonlocal statement.  
- **All other names are enclosing function locals, globals, or built-ins.** Names not assigned a value in the function definition are assumed to be enclosing scope locals, defined in a physically surrounding def statement; globals that live in the enclosing module’s namespace; or built-ins in the predefined built-ins module Python provides.  
- **Each call to a function creates a new local scope.** Every time you call a function, you create a new local scope—that is, a namespace in which the names created inside that function will usually live. You can think of each def statement (and lambda expression) as defining a new local scope, but the local scope actually corresponds to a function call.   

### Name Resolution: The LEGB Rule

The LEGB scope lookup rule. When a variable is referenced, Python searches for it in this order: in the local scope, in any enclosing functions’ local scopes, in the global scope, and finally in the built-in scope. The first occurrence wins. The place in your code where a variable is assigned usually determines its scope. In Python 3.X, nonlocal declarations can also force names to be mapped to enclosing function scopes, whether assigned or not.  

- Local(function)，本地作用域(函数)：每次对函数的调用都创建了一个新的本地作用域。一个函数内部的任何类型的赋值都会把一个名称划定为本地的（声明为global的除外）。这包括=语句、import中的模块名称、def中的函数名称、函数参数名称等。
- Enclosing function locals：names in the local scope of any all enclosing functions(def or lambda), from inner to outer
- Global(module)，全局作用域：每个模块都是一个全局作用域（也就是说，一个创建于模块文件顶层的变量的命名空间）。全局作用域的作用范围仅限于单个文件，Python中没有基于一个单个的、无所不包的情景文件的全局作用域。
- Built-in(Python)：Names preassigned in built-in names module:open, range, SyntaxError...

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
  X is global because it’s assigned at the top level of the module file; it can be referenced inside the function as a simple unqualified variable without being declared global. func is global for the same reason; the def statement assigns a function object to the name func at the top level of the module.
- Local names: Y, Z
  Y and Z are local to the function (and exist only while the function runs) because they are both assigned values in the function definition: Z by virtue of the = statement, and Y because arguments are always passed by assignment.

### The Built-in Scope  

The built-in scope is implemented as a standard library module named builtins in 3.X, but that name itself is not placed in the built-in scope, so you have to import it in order to inspect it. Once you do, you can run a dir call to see which names are predefined. In Python 3.3 (see ahead for 2.X usage):  

```python
>>> import builtins
>>> dir(builtins)
['ArithmeticError', 'AssertionError', 'AttributeError', 'BaseException',
'BlockingIOError', 'BrokenPipeError', 'BufferError', 'BytesWarning',
...many more names omitted...
'ord', 'pow', 'print', 'property', 'quit', 'range', 'repr', 'reversed',
'round', 'set', 'setattr', 'slice', 'sorted', 'staticmethod', 'str', 'sum',
'super', 'tuple', 'type', 'vars', 'zip']
```

Because Python automatically searches this module last in its LEGB lookup, you get all the names in this list “for free”—that is, you can use them without importing any modules. Thus, there are really two ways to refer to a built-in function—by taking advantage of the LEGB rule, or by manually importing the builtins module:  

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

## The global Statement  

The global statement and its nonlocal 3.X cousin are the only things that are remotely like declaration statements in Python. They are not type or size declarations, though; they are namespace declarations.   

- Global names are variables assigned at the top level of the enclosing module file.
- Global names must be declared only if they are assigned within a function.
- Global names may be referenced within a function without being declared.

The global statement consists of the keyword global, followed by one or more names separated by commas. All the listed names will be mapped to the enclosing module’s scope when assigned or referenced within the function body.  In other words,  global allows us to change names that live outside a def at the top level of a module file.  

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

We’ve added a global declaration to the example here, such that the X inside the def now refers to the X outside the def; Here, x, y, and z are all globals inside the function all_global. y and z are global because
they aren’t assigned in the function; Notice that y and z are not declared global; Python’s LEGB lookup rule finds them in the module automatically.    

### Other Ways to Access Globals  

```python
# thismod.py
var = 99 # Global variable == module attribute

def local():
    var = 0 # Change local var

def glob1():
    global var # Declare global (normal)
    var += 1 # Change global var

def glob2():
    var = 0 # Change local var
    import thismod # Import myself
    thismod.var += 1 # Change global var

def glob3():
    var = 0 # Change local var
    import sys # Import system table
    glob = sys.modules['thismod'] # Get module object (or use __name__)
    glob.var += 1 # Change global var

def test():
    print(var)
    local(); glob1(); glob2(); glob3()
    print(var)
```

```python
>>> import thismod
>>> thismod.test()
99
102
>>> thismod.var
102
```

## Scopes and Nested Functions

However, it’s time to take a deeper look at the letter E in the LEGB lookup rule. The E layer was added in Python 2.2; it takes the form of the local scopes of any and all enclosing function’s local scopes. Enclosing scopes are sometimes also called statically nested scopes.  

### Nested Scope Details  

With the addition of nested function scopes, variable lookup rules become slightly more complex. Within a function: 

- A reference (X) looks for the name X first in the current local scope (function); then in the local scopes of any lexically enclosing functions in your source code, from inner to outer; then in the current global scope (the module file); and finally in the built-in scope (the module builtins). global declarations make the search begin in the global (module file) scope instead.
- An assignment (X = value) creates or changes the name X in the current local scope, by default. If X is declared global within the function, the assignment creates or changes the name X in the enclosing module’s scope instead. If, on the other hand, X is declared nonlocal within the function in 3.X (only), the assignment changes the name X in the closest enclosing function’s local scope.  

```python
X = 99           # Global scope name: not used
def f1():
    X = 88       # Enclosing def local
    def f2():
        print(X) # Reference made in nested def
    f2()         
f1()             # Prints 88: enclosing def local
```

Here, the nested def runs while a call to the function f1 is running; it generates a function and assigns it to the name f2, a local variable within f1’s local scope. In a sense, f2 is a temporary function that lives only during the execution of (and is visible only to code in) the enclosing f1.

But notice what happens inside f2: when it prints the variable X, it refers to the X that lives in the enclosing f1 function’s local scope. Because functions can access names in all physically enclosing def statements, the X in f2 is automatically mapped to the X in f1, by the LEGB lookup rule.

This enclosing scope lookup works even if the enclosing function has already returned. For example, the following code defines a function that makes and returns another function, and represents a more common usage pattern:  

```python
def f1():
    X = 88
    def f2():
        print(X) # Remembers X in enclosing def scope
    return f2    # Return f2 but don't call it
action = f1()    # Make, return function
action()         # Call it now: prints 88
```

### Factory Functions: Closures  

Factory functions (a.k.a. closures) are sometimes used by programs that need to generate event handlers on the fly in response to conditions at runtime.  For instance, imagine a GUI that must define actions according to user inputs that cannot be anticipated when the GUI is built.  In such cases, we need a function that creates and returns another function, with information that may vary per function made.    

To illustrate this in simple terms, consider the following function 

```python
>>> def maker(N):
        def action(X): # Make and return action
            return X ** N # action retains N from enclosing scope
        return action
```

This defines an outer function that simply generates and returns a nested function, without calling it.

```python
>>> f = maker(2) # Pass 2 to argument N
>>> f
<function maker.<locals>.action at 0x0000000002A4A158>
>>> f(3) # Pass 3 to X, N remembers 2: 3 ** 2
9
>>> f(4) # 4 ** 2
16
```

Perhaps the most unusual part of this, though, is that the nested function remembers integer 2, the value of the variable N in maker, even though maker has returned and exited by the time we call action. In effect, N from the enclosing local scope is retained as state information attached to the generated action, which is why we get back its argument squared when it is later called  

Just as important, if we now call the outer function again, we get back a new nested function with different state information attached. That is, we get the argument cubed instead of squared when calling the new function, but the original still squares as before:  

```python
>>> g = maker(3) # g remembers 3, f remembers 2
>>> g(4) # 4 ** 3
64
>>> f(4) # 4 ** 2
16
```

This works because each call to a factory function like this gets its own set of state information. In our case, the function we assign to name g remembers 3, and f remembers 2, because each has its own state information retained by the variable N in maker.  

On the other hand, enclosing scopes are often employed by the lambda function-creation expressions，because they are expressions, they are almost always nested within a def. For example, a lambda would serve in place of a def in our example:  

```python
>>> def maker(N):
        return lambda X: X ** N # lambda functions retain state too
>>> h = maker(3)
>>> h(4) # 4 ** 3 again
64
```

### Nested scopes, defaults, and lambdas  

```python
>>> def makeActions():
acts = []
for i in range(5): # Tries to remember each i
acts.append(lambda x: i ** x) # But all remember same last i!
return acts
>>> acts = makeActions()
>>> acts[0]
<function makeActions.<locals>.<lambda> at 0x0000000002A4A400>
```

This doesn’t quite work, though—because the enclosing scope variable is looked up when the nested functions are later called, they all effectively remember the same value: the value the loop variable had on the last loop iteration. That is, when we pass a power argument of 2 in each of the following calls, we get back 4 to the power of 2 for each function in the list, because i is the same in all of them—4:  

```python
>>> acts[0](2) # All are 4 ** 2, 4=value of last i
16
>>> acts[1](2) # This should be 1 ** 2 (1)
16
>>> acts[2](2) # This should be 2 ** 2 (4)
16
>>> acts[4](2) # Only this should be 4 ** 2 (16)
16
```

This is the one case where we still have to explicitly retain enclosing scope values with default arguments, rather than enclosing scope references. That is, to make this sort of code work, we must pass in the current value of the enclosing scope’s variable with a default. Because defaults are evaluated when the nested function is created (not when it’s later called), each remembers its own value for i:

```python
>>> def makeActions():
acts = []
for i in range(5): # Use defaults instead
acts.append(lambda x, i=i: i ** x) # Remember current i
return acts
>>> acts = makeActions()
>>> acts[0](2) # 0 ** 2
0
>>> acts[1](2) # 1 ** 2
1
>>> acts[2](2) # 2 ** 2
4
>>> acts[4](2) # 4 ** 2
16
```

## The nonlocal Statement in 3.X  

### nonlocal Basics  

Python 3.X introduces a new nonlocal statement, which has meaning only inside a function:  

```python
def func():
    nonlocal name1, name2, ... # OK here
>>> nonlocal X
SyntaxError: nonlocal declaration not allowed at module level
```

This statement allows a nested function to change one or more names defined in a syntactically enclosing function’s scope.  

Besides allowing names in enclosing defs to be changed, the nonlocal statement also forces the issue for references—much like the global statement, nonlocal causes searches for the names listed in the statement to begin in the enclosing defs’ scopes, not in the local scope of the declaring function. That is, nonlocal also means “skip my local scope entirely.”  

In fact, the names listed in a nonlocal must have been previously defined in an enclosing def when the nonlocal is reached, or an error is raised.  

Changing a name in an enclosing def’s scope is not allowed by default, though; this is the normal case in 2.X as well:  

```python
>>> def tester(start):
        state = start
    def nested(label):
        print(label, state)
        state += 1 # Cannot change by default (never in 2.X)
    return nested

>>> F = tester(0)
>>> F('spam')
UnboundLocalError: local variable 'state' referenced before assignment
```

Using nonlocal for changes. Now, under 3.X, if we declare state in the tester scope as nonlocal within nested, we get to change it inside the nested function, too.   

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

First, unlike the global statement, nonlocal names really must have previously been assigned in an enclosing def’s scope when a nonlocal is evaluated, or else you’ll get an error

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

Second, nonlocal restricts the scope lookup to just enclosing defs; nonlocals are not looked up in the enclosing module’s global scope or the built-in scope outside all defs, even if they are already there:  

```python
>>> spam = 99
>>> def tester():
        def nested():
        nonlocal spam # Must be in a def, not the module!
        print('Current=', spam)
        spam += 1
    return nested
SyntaxError: no binding for nonlocal 'spam' found
```

# Arguments  

This chapter continues the function story by studying the concepts in Python argument passing—the way that objects are sent to functions as inputs. As we’ll see, arguments (a.k.a. parameters) are assigned to names in a function, but they have more to do with object references than with variable scopes.  

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

![python_function_01](.\images\python_function_01.PNG)

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

As we’ve just seen, arguments are always passed by assignment in Python; names in the def header are assigned to passed-in objects.   

By default, arguments are matched by position, from left to right, and you must pass exactly as many arguments as there are argument names in the function header. However, you can also specify matching by name, provide default values, and use collectors for extra arguments.  

### Argument Matching Basics  /todo

### Argument Matching Syntax

Table 18-1. Function argument-matching forms Syntax Location Interpretation

| Synax                   | Location | Interpretation                                               |
| ----------------------- | -------- | ------------------------------------------------------------ |
| func(value)             | Caller   | Normal argument: matched by position                         |
| func(name=value)        | Caller   | Keyword argument: matched by name                            |
| func(*iterable)         | Caller   | Pass all objects in iterable as individual positional arguments |
| func(**dict)            | Caller   | Pass all key/value pairs in dict as individual keyword arguments |
| def func(name)          | Function | Normal argument: matches any passed value by position or name |
| def func(name=value)    | Function | Default argument value, if not passed in the call            |
| def func(*name)         | Function | Matches and collects remaining positional arguments in a tuple |
| def func(**name)        | Function | Matches and collects remaining keyword arguments in a dictionary |
| def func(*other, name)  | Function | Arguments that must be passed by keyword only in calls (3.X) |
| def func(*, name=value) | Function | Arguments that must be passed by keyword only in calls (3.X) |

### The Gritty Details

In both the call and header, the `**args` form must appear last if present.  The steps that Python internally carries out to match arguments before assignment can roughly be described as follows:

1. Assign nonkeyword arguments by position.
2. Assign keyword arguments by matching names.
3. Assign extra nonkeyword arguments to *name tuple.
4. Assign extra keyword arguments to **name dictionary.
5. Assign default values to unassigned arguments in header. 

After this, Python checks to make sure each argument is passed just one value; if not, an error is raised. When all matching is complete, Python assigns argument names to the objects passed to them.  

### Keyword and Default Examples  

If you don’t use any special matching syntax, Python matches names by position from left to right. Here, we pass by position—a is matched to 1, b is matched to 2, and so on.

```python
>>> def f(a, b, c): print(a, b, c)
>>> f(1, 2, 3)
1 2 3
```

#### Keywords  

Keyword arguments allow us to match by name, instead of by position. 

```python
>>> f(c=3, b=2, a=1)
1 2 3

>>> f(1, c=3, b=2) # a gets 1 by position, b and c passed by name
1 2 3
```

Python matches the name c in the call to the argument named c in the function definition’s header, and then passes the value 3 to that argument.  **All positionals are matched first from left to right in the header, before keywords are matched by name.**

#### Defaults  

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

When we call this function, we must provide a value for @a, either by position or by keyword; however, providing values for @b and @c is optional. If we don’t pass values to @b and @c, they default to 2 and 3, respectively. If we pass two values, only @c gets its default, and with three values, no defaults are used.

#### Combining keywords and defaults

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

### Arbitrary Arguments Examples  

The last two matching extensions, * and **, are designed to support functions that take any number of arguments.   

#### Headers: Collecting arguments  

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

#### Calls: Unpacking arguments

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

### Python 3.X Keyword-Only Arguments  

Python 3.X generalizes the ordering rules in function headers to allow us to specify keyword-only arguments—arguments that must be passed by keyword only and will never be filled in by a positional argument.   

Syntactically, keyword-only arguments are coded as named arguments that may appear after *args in the arguments list. All such arguments must be passed using keyword syntax in the call.   

```python
>>> def kwonly(a, *b, c):
        print(a, b, c)
>>> kwonly(1, 2, c=3)
1 (2,) 3
>>> kwonly(a=1, c=3)
1 () 3
>>> kwonly(1, 2, 3)
TypeError: kwonly() missing 1 required keyword-only argument: 'c'  
```

In the next function, a may be passed by position or name again, but b and c must be keywords, and no extra positionals are allowed:  

```python
>>> def kwonly(a, *, b, c):
        print(a, b, c)
>>> kwonly(1, c=3, b=2)
1 2 3
>>> kwonly(c=3, b=2, a=1)
1 2 3
>>> kwonly(1, 2, 3)
TypeError: kwonly() takes 1 positional argument but 3 were given
>>> kwonly(1)
TypeError: kwonly() missing 2 required keyword-only arguments: 'b' and 'c' 
        
>>> def kwonly(a, *, b=1, c, d=2):
        print(a, b, c, d)
>>> kwonly(3, c=4)
3 1 4 2
>>> kwonly(3, c=4, b=5)
3 5 4 2
>>> kwonly(3)
TypeError: kwonly() missing 1 required keyword-only argument: 'c'
>>> kwonly(1, 2, 3)
TypeError: kwonly() takes 1 positional argument but 3 were given
```

Finally, note that keyword-only arguments must be specified after a single star, not two —named arguments cannot appear after the `**args` arbitrary keywords form, and a ** can’t appear by itself in the arguments list.   

```python
>>> def kwonly(a, **pargs, b, c):
SyntaxError: invalid syntax
>>> def kwonly(a, **, b, c):
SyntaxError: invalid syntax  
    
>>> def f(a, *b, **d, c=6): print(a, b, c, d) # Keyword-only before **!
SyntaxError: invalid syntax
>>> def f(a, *b, c=6, **d): print(a, b, c, d) # Collect args in header
>>> f(1, 2, 3, x=4, y=5) # Default used
1 (2, 3) 6 {'y': 5, 'x': 4}
>>> f(1, 2, 3, x=4, y=5, c=7) # Override default
1 (2, 3) 7 {'y': 5, 'x': 4}
>>> f(1, 2, 3, c=7, x=4, y=5) # Anywhere in keywords
1 (2, 3) 7 {'y': 5, 'x': 4}
>>> def f(a, c=6, *b, **d): print(a, b, c, d) # c is not keyword-only here!
>>> f(1, 2, 3, x=4)
1 (3,) 2 {'x': 4}
```

In fact, similar ordering rules hold true in function calls: when keyword-only arguments are passed, they must appear before a `**args` form. The keyword-only argument can be coded either before or after the *args, though, and may be included in `**args`:

```python
>>> def f(a, *b, c=6, **d): print(a, b, c, d) # KW-only between * and **
>>> f(1, *(2, 3), **dict(x=4, y=5)) # Unpack args at call
1 (2, 3) 6 {'y': 5, 'x': 4}
>>> f(1, *(2, 3), **dict(x=4, y=5), c=7) # Keywords before **args!
SyntaxError: invalid syntax
>>> f(1, *(2, 3), c=7, **dict(x=4, y=5)) # Override default
1 (2, 3) 7 {'y': 5, 'x': 4}
>>> f(1, c=7, *(2, 3), **dict(x=4, y=5)) # After or before *
1 (2, 3) 7 {'y': 5, 'x': 4}
>>> f(1, *(2, 3), **dict(x=4, y=5, c=7)) # Keyword-only in **
1 (2, 3) 7 {'y': 5, 'x': 4}
```





# Advanced Function Topics  

This chapter introduces a collection of more advanced function-related topics: recursive functions, function attributes and annotations, the lambda expression, and functional programming tools such as map and filter.   

## Function Design Concepts  

When you start using functions in earnest, you’re faced with choices about how to glue components together—for instance, how to decompose a task into purposeful functions (known as cohesion), how your functions should communicate (called coupling), and so on. You also need to take into account concepts such as the size of your functions, because they directly impact code usability. Some of this falls into the category of structured analysis and design, but it applies to Python code as to any other.  

## Recursive Functions  

### Summation with Recursion 

```python
>>> def mysum(L):
        if not L:
            return 0
        else:
            return L[0] + mysum(L[1:]) # Call myself recursively
>>> mysum([1, 2, 3, 4, 5])
15
```

### Coding Alternatives  

```python
def mysum(L):
    return 0 if not L else L[0] + mysum(L[1:]) # Use ternary expression
def mysum(L):
    return L[0] if len(L) == 1 else L[0] + mysum(L[1:]) # Any type, assume one
def mysum(L):
    first, *rest = L
    return first if not rest else first + mysum(rest) # Use 3.X ext seq assign
```

The latter two of these fail for empty lists but allow for sequences of any object type that supports +, not just numbers:  

```python
>>> mysum([1]) # mysum([]) fails in last 2
1
>>> mysum([1, 2, 3, 4, 5])
15
>>> mysum(('s', 'p', 'a', 'm')) # But various types now work
'spam'
>>> mysum(['spam', 'ham', 'eggs'])
'spamhameggs
```

### Loop Statements Versus Recursion  

```python
>>> L = [1, 2, 3, 4, 5]
>>> sum = 0
>>> while L:
        sum += L[0]
        L = L[1:]
>>> sum
15

>>> L = [1, 2, 3, 4, 5]
>>> sum = 0
>>> for x in L: sum += x
>>> sum
15
```

## Function Objects: Attributes and Annotations

As we’ve seen in this part of the book, functions in Python are much more than code-generation specifications for a compiler—Python functions are full-blown objects, stored in pieces of memory all
their own. As such, they can be freely passed around a program and called indirectly. They also support operations that have little to do with calls at all—attribute storage and annotation.  

### Indirect Function Calls: “First Class” Objects  

。。。

### Function Introspection

Because they are objects, we can also process functions with normal object tools. For instance, once we make a function, we can call it as usual:  

```python
>>> def func(a):
        b = 'spam'
        return b * a
>>> func(8)
'spamspamspamspamspamspamspamspam'
```

But the call expression is just one operation defined to work on function objects. We can also inspect their attributes generically:

```python
>>> func.__name__
'func'
>>> dir(func)
['__annotations__', '__call__', '__class__', '__closure__', '__code__',
...more omitted: 34 total...
'__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__']

>>> func.__code__
<code object func at 0x00000000021A6030, file "<stdin>", line 1>
>>> dir(func.__code__)
['__class__', '__delattr__', '__dir__', '__doc__', '__eq__', '__format__', '__ge__',
...more omitted: 37 total...
'co_argcount', 'co_cellvars', 'co_code', 'co_consts', 'co_filename',
'co_firstlineno', 'co_flags', 'co_freevars', 'co_kwonlyargcount', 'co_lnotab',
'co_name', 'co_names', 'co_nlocals', 'co_stacksize', 'co_varnames']
>>> func.__code__.co_varnames
('a', 'b')
>>> func.__code__.co_argcount
1
```

### Function Attributes  

Function objects are not limited to the system-defined attributes listed in the prior section, though.  As we learned in Chapter 17, it’s been possible to attach arbitrary userdefined attributes to them as well since Python 2.1:  

```python
>>> func
<function func at 0x000000000296A1E0>
>>> func.count = 0
>>> func.count += 1
>>> func.count
1
>>> func.handles = 'Button-Press'
>>> func.handles
'Button-Press'
>>> dir(func)
['__annotations__', '__call__', '__class__', '__closure__', '__code__',
...and more: in 3.X all others have double underscores so your names won't clash...
__str__', '__subclasshook__', 'count', 'handles']
```

Python’s own implementation-related data stored on functions follows naming conventions that prevent them from clashing with the more arbitrary attribute names you might assign yourself. In 3.X, all function internals’ names have leading and trailing double underscores (`“__X__”`); 2.X follows the same scheme, but also assigns some names that begin with “func_X”:  

```python
c:\code> py −3
>>> def f(): pass
>>> dir(f)
...run on your own to see...
>>> len(dir(f))
34
>>> [x for x in dir(f) if not x.startswith('__')]
[]
c:\code> py −2
>>> def f(): pass
>>> dir(f)
...run on your own to see...
>>> len(dir(f))
31
>>> [x for x in dir(f) if not x.startswith('__')]
['func_closure', 'func_code', 'func_defaults', 'func_dict', 'func_doc',
'func_globals', 'func_name']
```

### Function Annotations in 3.X

In Python 3.X (but not 2.X), it’s also possible to attach annotation information—arbitrary user-defined data about a function’s arguments and result—to a function object. Python provides special syntax for specifying annotations, but it doesn’t do anything with them itself; annotations are completely optional, and when present are simply attached to the function object’s `__annotations__` attribute for use by other tools.  

Syntactically, function annotations are coded in def header lines, as arbitrary expressions associated with arguments and return values. For arguments, they appear after a colon immediately following the argument’s name; for return values, they are written after a -> following the arguments list. This code, for example 

```python
>>> def func(a: 'spam', b: (1, 10), c: float) -> int:
        return a + b + c
>>> func(1, 2, 3)
6
```

Calls to an annotated function work as usual, but when annotations are present Python collects them in a dictionary and attaches it to the function object itself.   

```python
>>> func.__annotations__
{'c': <class 'float'>, 'b': (1, 10), 'a': 'spam', 'return': <class 'int'>}

>>> def func(a: 'spam', b, c: 99):
        return a + b + c
>>> func(1, 2, 3)
6
>>> func.__annotations__
{'c': 99, 'a': 'spam'}
>>> for arg in func.__annotations__:
        print(arg, '=>', func.__annotations__[arg])
c => 99
a => spam

>>> def func(a: 'spam' = 4, b: (1, 10) = 5, c: float = 6) -> int:
        return a + b + c
>>> func(1, 2, 3)
6
>>> func() # 4 + 5 + 6 (all defaults)
15
>>> func(1, c=10) # 1 + 5 + 10 (keywords work normally)
16
>>> func.__annotations__
{'c': <class 'float'>, 'b': (1, 10), 'a': 'spam', 'return': <class 'int'>}
```

## Anonymous Functions: lambda  

Besides the def statement, Python also provides an expression form that generates function objects. Like def, this expression creates a function to be called later, but it returns the function instead of assigning it to a name. This is why lambdas are sometimes known as anonymous (i.e., unnamed) functions. In practice, they are often used as a way to inline a function definition, or to defer execution of a piece of code.

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

### Why Use lambda?  

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

### How (Not) to Obfuscate Your Python Code  

# Comprehensions and Generations

## List Comprehensions and Functional Tools    

In short, list comprehensions apply an arbitrary expression to items in an iterable, rather than applying a function.  

### List Comprehensions Versus map

```python
>>> res = list(map(ord, 'spam')) # Apply function to sequence (or other)
>>> res
[115, 112, 97, 109]

>>> res = [ord(x) for x in 'spam'] # Apply expression to sequence (or other)
>>> res
[115, 112, 97, 109]
```

List comprehensions collect the results of applying an arbitrary expression to an iterable of values and return them in a new list. Syntactically, list comprehensions are enclosed in square brackets—to remind you that they construct lists. In their simple form, within the brackets you code an expression that names a variable followed by what looks like a for loop header that names the same variable. Python then collects the expression’s results for each iteration of the implied loop.  

### Adding Tests and Nested Loops: filter  

```python
>>> [x ** 2 for x in range(10) if x % 2 == 0]
[0, 4, 16, 36, 64]
```

This time, we collect the squares of the even numbers from 0 through 9: the for loop skips numbers for which the attached if clause on the right is false, and the expression on the left computes the squares. The equivalent map call would require a lot more work on our part—we would have to combine filter selections with map iteration, making for a noticeably more complex expression:  

```python
>>> list( map((lambda x: x**2), filter((lambda x: x % 2 == 0), range(10))) )
[0, 4, 16, 36, 64]
```

The general structure of list comprehensions looks like this:

```python
[ expression for target1 in iterable1 if condition1
             for target2 in iterable2 if condition2 ...
             for targetN in iterableN if conditionN ]  
```

```python
>>> [x + y for x in 'spam' for y in 'SPAM']
['sS', 'sP', 'sA', 'sM', 'pS', 'pP', 'pA', 'pM',
'aS', 'aP', 'aA', 'aM', 'mS', 'mP', 'mA', 'mM']

>>> [x + y + z for x in 'spam' if x in 'sm'
               for y in 'SPAM' if y in ('P', 'A')
               for z in '123' if z > '1']
['sP2', 'sP3', 'sA2', 'sA3', 'mP2', 'mP3', 'mA2', 'mA3']
```

## Generator Functions and Expressions  

todo

### Generator Functions: yield Versus return

Generator functions are like normal functions in most respects, and in fact are coded with normal def statements. However, when created, they are compiled specially into an object that supports the iteration protocol. And when called, they don’t return a result: they return a result generator that can appear in any iteration context. 

#### Generator functions in action  

The following code defines a generator function that can be used to generate the squares of a series of numbers over time:  

```python
>>> def gensquares(N):
        for i in range(N):
            yield i ** 2 # Resume here later
```

This function yields a value, and so returns to its caller, each time through the loop; when it is resumed, its prior state is restored, including the last values of its variables i and N, and control picks up again immediately after the yield statement. For example, when it’s used in the body of a for loop, the first iteration starts the function and gets its first result; thereafter, control returns to the function after its yield statement each time through the loop:  

```python
>>> for i in gensquares(5): # Resume the function
        print(i, end=' : ') # Print last yielded value
0 : 1 : 4 : 9 : 16 :
>>>
```

To end the generation of values, functions either use a return statement with no value or simply allow control to fall off the end of the function body.  

```python
>>> x = gensquares(4)
>>> x
<generator object gensquares at 0x000000000292CA68>
```

You get back a generator object that supports the iteration protocol we met in Chapter 14—the generator function was compiled to return this automatically. The returned generator object in turn has a `__next__` method that starts the function or resumes it from where it last yielded a value, and raises a StopIteration exception when the end of the series of values is reached and the function returns. For convenience, the
next(X) built-in calls an object’s X.`__next__`() method for us in 3.X (and X.next() in 2.X):  

```python
>>> next(x) # Same as x.__next__() in 3.X
0
>>> next(x) # Use x.next() or next() in 2.X
1
>>> next(x)
4
>>> next(x)
9
>>> next(x)
Traceback (most recent call last):
File "<stdin>", line 1, in <module>
StopIteration
```



# 参考：

learning python （python学习手册）















