http://zhoutall.com/archives/325


理解Python中的with…as…语法
Posted in python - 22 五月, 2013 - 2 Comments
使用语言的好特性，而不是那些糟糕的特性————不知道谁说的

好久不学习python的语法了，上次去面试，和面试官聊到了python中的with-as statement（也称context manager），挺感兴趣的，这两天学习了一番，收获颇丰在此分享。

先说明一个常见问题，文件打开：

1
2
3
4
5
6
7
try:
    f = open('xxx')
    do something
except:
    do something
finally:
    f.close()
其实我个人不止一次在网上看到有这么写的了，这个是错的。
首先正确的如下：

1
2
3
4
5
6
7
8
9
10
11
try:
    f = open('xxx')
except:
    print 'fail to open'
    exit(-1)
try:
    do something
except:
    do something
finally:
    f.close()
很麻烦不是么，但正确的方法就是这么写。
我们为什么要写finally，是因为防止程序抛出异常最后不能关闭文件，但是需要关闭文件有一个前提就是文件已经打开了。
在第一段错误代码中，如果异常发生在f=open(‘xxx’)的时候，比如文件不存在，立马就可以知道执行f.close()是没有意义的。改正后的解决方案就是第二段代码。

好了言归正转，开始讨论with语法。

首先我们从下面这个问题谈起，try-finally的语法结构：

1
2
3
4
5
set things up
try:
    do something
finally:
    tear things down
这东西是个常见结构，比如文件打开，set things up就表示f=open('xxx')，tear things down就表示f.close()。在比如像多线程锁，资源请求，最终都有一个释放的需求。Try…finally结构保证了tear things down这一段永远都会执行，即使上面do something得工作没有完全执行。

如果经常用这种结构，我们首先可以采取一个较为优雅的办法，封装！

1
2
3
4
5
6
7
8
9
10
11
def controlled_execution(callback):
    set things up
    try:
        callback(thing)
    finally:
        tear things down
 
def my_function(thing):
    do something
 
controlled_execution(my_function)
封装是一个支持代码重用的好办法，但是这个办法很dirty，特别是当do something中有修改一些local variables的时候（变成函数调用，少不了带来变量作用域上的麻烦）。

另一个办法是使用生成器，但是只需要生成一次数据，我们用for-in结构去调用他：

1
2
3
4
5
6
7
8
9
def controlled_execution():
    set things up
    try:
        yield thing
    finally:
        tear things down
         
for thing in controlled_execution():
    do something with thing
因为thing只有一个，所以yield语句只需要执行一次。当然，从代码可读性也就是优雅的角度来说这简直是糟糕透了。我们在确定for循环只执行一次的情况下依然使用了for循环，这代码给不知道的人看一定很难理解这里的循环是什么个道理。

最终的python-dev团队的解决方案。（python 2.5以后增加了with表达式的语法）

1
2
3
4
5
6
7
8
9
class controlled_execution:
    def __enter__(self):
        set things up
        return thing
    def __exit__(self, type, value, traceback):
        tear things down
         
with controlled_execution() as thing:
        do something
在这里，python使用了with-as的语法。当python执行这一句时，会调用__enter__函数，然后把该函数return的值传给as后指定的变量。之后，python会执行下面do something的语句块。最后不论在该语句块出现了什么异常，都会在离开时执行__exit__。
另外，__exit__除了用于tear things down，还可以进行异常的监控和处理，注意后几个参数。要跳过一个异常，只需要返回该函数True即可。下面的样例代码跳过了所有的TypeError，而让其他异常正常抛出。

1
2
def __exit__(self, type, value, traceback):
    return isinstance(value, TypeError)
在python2.5及以后，file对象已经写好了__enter__和__exit__函数，我们可以这样测试：

1
2
3
4
5
6
7
8
9
10
11
12
>>> f = open("x.txt")
>>> f
<open file 'x.txt', mode 'r' at 0x00AE82F0>
>>> f.__enter__()
<open file 'x.txt', mode 'r' at 0x00AE82F0>
>>> f.read(1)
'X'
>>> f.__exit__(None, None, None)
>>> f.read(1)
Traceback (most recent call last):
    File "<stdin>", line 1, in <module>
ValueError: I/O operation on closed file
之后，我们如果要打开文件并保证最后关闭他，只需要这么做：

1
2
3
with open("x.txt") as f:
    data = f.read()
    do something with data
如果有多个项，我们可以这么写：

1
2
with open("x.txt") as f1, open('xxx.txt') as f2:
    do something with f1,f2
上文说了__exit__函数可以进行部分异常的处理，如果我们不在这个函数中处理异常，他会正常抛出，这时候我们可以这样写（python 2.7及以上版本，之前的版本参考使用contextlib.nested这个库函数）：

1
2
3
4
5
try:
    with open( "a.txt" ) as f :
        do something
except xxxError:
    do something about exception
总之，with-as表达式极大的简化了每次写finally的工作，这对保持代码的优雅性是有极大帮助的。

感谢以下参考资料：
stackoverflow: Catching an exception while using a Python ‘with’ statement
Understanding Python’s “with” statement
python docs:
http://docs.python.org/2/reference/compound_stmts.html#with
http://docs.python.org/2/reference/datamodel.html#context-managers
http://docs.python.org/2/library/contextlib.html#contextlib.nested