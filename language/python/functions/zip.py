def zip([iterable, ...]):
This function returns a list of tuples, where the i-th tuple contains the i-th eleme-
nt from each of the argument sequences or iterables. 

>>> x = [1, 2, 3]
>>> y = [4, 5, 6]
>>> zipped = zip(x, y)
>>> zipped
[(1, 4), (2, 5), (3, 6)]
>>> x2, y2 = zip(*zipped)
>>> x == list(x2) and y == list(y2)
True


http://www.cnblogs.com/frydsh/archive/2012/07/10/2585370.html

1.示例1：

复制代码
x = [1, 2, 3]

y = [4, 5, 6]

z = [7, 8, 9]

xyz = zip(x, y, z)

print xyz
复制代码
运行的结果是：

[(1, 4, 7), (2, 5, 8), (3, 6, 9)]

从这个结果可以看出zip函数的基本运作方式。

2.示例2：

x = [1, 2, 3]
y = [4, 5, 6, 7]
xy = zip(x, y)
print xy
运行的结果是：

[(1, 4), (2, 5), (3, 6)]

从这个结果可以看出zip函数的长度处理方式。

3.示例3：

x = [1, 2, 3]
x = zip(x)
print x
运行的结果是：

[(1,), (2,), (3,)]

从这个结果可以看出zip函数在只有一个参数时运作的方式。

4.示例4：

x = zip()
print x
运行的结果是：

[]

从这个结果可以看出zip函数在没有参数时运作的方式。

5.示例5：

复制代码
x = [1, 2, 3]

y = [4, 5, 6]

z = [7, 8, 9]

xyz = zip(x, y, z)

u = zip(*xyz)

print u
复制代码
运行的结果是：

[(1, 2, 3), (4, 5, 6), (7, 8, 9)]

一般认为这是一个unzip的过程，它的运行机制是这样的：

在运行zip(*xyz)之前，xyz的值是：[(1, 4, 7), (2, 5, 8), (3, 6, 9)]

那么，zip(*xyz) 等价于 zip((1, 4, 7), (2, 5, 8), (3, 6, 9))

所以，运行结果是：[(1, 2, 3), (4, 5, 6), (7, 8, 9)]

注：在函数调用中使用*list/tuple的方式表示将list/tuple分开，作为位置参数传递给对应函数（前提是对应函数支持不定个数的位置参数）

6.示例6：

x = [1, 2, 3]
r = zip(* [x] * 3)
print r
运行的结果是：

[(1, 1, 1), (2, 2, 2), (3, 3, 3)]

它的运行机制是这样的：

[x]生成一个列表的列表，它只有一个元素x

[x] * 3生成一个列表的列表，它有3个元素，[x, x, x]

zip(* [x] * 3)的意思就明确了，zip(x, x, x)