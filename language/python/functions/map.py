
def map(function, iterable, ...):
  '''
  apply() filter() map() reduce()
  '''
  pass
  

'''
http://www.pythoner.com/46.html   Python函数式编程——map()、reduce()





#map()函数接收两个参数，一个是函数，一个是序列，map将传入的函数依次作用到序列的
#每个元素，并把结果作为新的list返回。

#举例说明，比如我们有一个函数f(x)=x2，要把这个函数作用在一个list [1, 2, 3, 4, 5,
# 6, 7, 8, 9]上，就可以用map()实现如下：
>>> def f(x):
...     return x * x
...
>>> map(f, [1, 2, 3, 4, 5, 6, 7, 8, 9])
[1, 4, 9, 16, 25, 36, 49, 64, 81]
#请注意我们定义的函数f。当我们写f时，指的是函数对象本身，当我们写f(1)时，指的是
#调用f函数，并传入参数1，期待返回结果1。

#因此，map()传入的第一个参数是f，即函数对象本身。

#像map()函数这种能够接收函数作为参数的函数，称之为高阶函数(Higher-order function)。


http://my.oschina.net/zyzzy/blog/115096
MapReduce的设计灵感来自于函数式编程，这里不打算提MapReduce，就拿python中的map()函数来学习一下。

文档中的介绍在这里：

map(function, iterable, ...)

Apply function to every item of iterable and return a list of the results. If additional iterable arguments are passed, function must take that many arguments and is applied to the items from all iterables in parallel. If one iterable is shorter than another it is assumed to be extended withNoneitems. If function isNone, the identity function is assumed; if there are multiple arguments, map() returns a list consisting of tuples containing the corresponding items from all iterables (a kind of transpose operation). The iterable arguments may be a sequence or any iterable object; the result is always a list.

一点一点看：

1、对可迭代函数'iterable'中的每一个元素应用‘function’方法，将结果作为list返回。

来个例子：

?
1
2
3
4
5
6
>>> def add100(x):
...     return x+100
... 
>>> hh = [11,22,33]
>>> map(add100,hh)
[111, 122, 133]
就像文档中说的：对hh中的元素做了add100，返回了结果的list。

2、如果给出了额外的可迭代参数，则对每个可迭代参数中的元素‘并行’的应用‘function’。（翻译的不好，这里的关键是‘并行’）

?
1
2
3
4
5
6
7
8
>>> def abc(a, b, c):
...     return a*10000 + b*100 + c
... 
>>> list1 = [11,22,33]
>>> list2 = [44,55,66]
>>> list3 = [77,88,99]
>>> map(abc,list1,list2,list3)
[114477, 225588, 336699]
看到并行的效果了吧！在每个list中，取出了下标相同的元素，执行了abc()。

3、如果'function'给出的是‘None’，自动假定一个‘identity’函数（这个‘identity’不知道怎么解释，看例子吧）

?
1
2
3
4
5
6
7
8
>>> list1 = [11,22,33]
>>> map(None,list1)
[11, 22, 33]
>>> list1 = [11,22,33]
>>> list2 = [44,55,66]
>>> list3 = [77,88,99]
>>> map(None,list1,list2,list3)
[(11, 44, 77), (22, 55, 88), (33, 66, 99)]
用语言解释好像有点拗口  ，例子应该很容易理解。

介绍到这里应该差不多了吧！不过还有东西可以挖掘：

stackoverflow上有人说可以这样理解map()：

?
1
2
3
4
5
map(f, iterable)
 
基本上等于：
 
[f(x) for x in iterable]
赶快试一下：

?
1
2
3
4
5
6
7
8
9
>>> def add100(x):
...     return x + 100
... 
>>> list1 = [11,22,33]
>>> map(add100,list1)
[101, 102, 103]
 
>>> [add100(i) for i in list1]
[101, 102, 103]
哦，输出结果一样。原来map()就是列表推导式啊！要是这样想就错了：这里只是表面现象！再来个例子看看：

?
1
2
3
4
5
6
7
8
>>> def abc(a, b, c):
...     return a*10000 + b*100 + c
... 
>>> list1 = [11,22,33]
>>> list2 = [44,55,66]
>>> list3 = [77,88,99]
>>> map(abc,list1,list2,list3)
[114477, 225588, 336699]
这个例子我们在上面看过了，若是用列表推导应该怎么写呢？我想是这样的：

?
1
[abc(a,b,c) for a in list1 for b in list2 for c in list3]
但是看到结果，发现根本不是这么回事：

?
1
[114477, 114488, 114499, 115577, 115588, 115599, 116677, 116688, 116699, 224477, 224488, 224499, 225577, 225588, 225599, 226677, 226688, 226699, 334477, 334488, 334499, 335577, 335588, 335599, 336677, 336688, 336699]
这便是上面列表推导的结果。怎么会这么多？当然了列表推导可以这么写：

?
1
2
3
4
5
6
result = []
 
for a in list1:
    for b in list2:
        for c in list3:
            result.append(abc(abc))
原来如此，若是将三个list看做矩阵的话：
11
22
33
44
55
66
77
88
99
map()只做了列上面的运算，而列表推导（也就是嵌套for循环）做了笛卡尔乘积。

OK，就写到这里。仅个人理解，如有差错请指正，多谢！

上面的例子有些来自于这里：

http://infohost.nmt.edu/tcc/help/pubs/python/web/map-function.html

http://stackoverflow.com/questions/10973766/understanding-the-map-function-python
'''
