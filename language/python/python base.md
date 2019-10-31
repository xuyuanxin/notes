

# 函数

一个函数就是将一些语句集合在一起的部件，函数可以在程序中重复调用。函数是为了代码最大程度的重用和最小化代码冗余而提供的最基本的程序结构。

## 创建函数（def 语句）

### 函数创建

Def语句创建一个函数对象并将其赋值给一个变量。Def语句的一般格式如下：

```python
def name(arg1, arg2,... argN):
    statements...
    return value
```

Def语句首行定义了函数名（name），并在括号里包含了0个或多个参数（有时称为形参）。有个一代码块紧随其后，构成了函数的主体，每当调用函数时均会执行这些语句。函数主体一般包含一个return语句，可以出现在函数主体的任何地方，表示函数调用的结束，并讲结果返回至调用处。一个没有返回值的函数自动返回none对象。

### 函数调用

Python的Def语句是一个可执行的语句：当他运行的时候，他创建一个新的函数对象并将其赋值给一个变量名。在Def运行之后，可以在程序中通过在函数名后增加括号调用或运行这个函数。括号中包括一个或多个对象参数，这些参数将会传递（赋值）给函数头部的参数名。

```python
>>> def times(x, y): # Create and assign function
...    return x * y # Body executed when called
...
>>> times(2, 4)  # Arguments in parentheses
8
>>> x = times(3.14, 4) 
>>> x 
12.56
>>> times('Ni', 4) # Functions are "typeless"，函数多态性说明 todo
'NiNiNiNi'
```

### 进一步说明

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

## 作用域

Python中的变量名在第一次赋值时已经创建，并且必须经过赋值后才能够使用。Python创建、改变或查找变量名都是在所谓的命名空间（一个保存变了名的地方）中进行的。Python将一个变量名被赋值的地点关联为一个特定的命名空间，代码中给一个变量赋值的地方决定了这个变量将存在于哪个命名空间，也就是它可见的范围。

- Local(function)，本地作用域(函数)：每次对函数的调用都创建了一个新的本地作用域。一个函数内部的任何类型的赋值都会吧一个名称划定为本地的（声明为global的除外）。这包括=语句、import中的模块名称、def中的函数名称、函数参数名称等。
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



全局变量

- 全局变量是位于模块文件内部的顶层的变量名

- 全局变量如果是在函数内被赋值的话，必须经过声明

- 全局变量名在函数的内部不经过声明也可以被引用



## 参考：

learning python （python学习手册）