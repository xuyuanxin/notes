'''
Python入门笔记(23)：模块   http://www.cnblogs.com/BeginMan/p/3183656.html


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