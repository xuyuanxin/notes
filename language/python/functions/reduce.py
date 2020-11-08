﻿

格式：reduce( func, seq[, init] )

reduce函数即为化简，它是这样一个过程：每次迭代，将上一次的迭代结果（第一次时为init的元素，如没有init则为seq的第一个元素）与下一个元素一同执行一个二元的func函数。在reduce函数中，init是可选的，如果使用，则作为第一次迭代的第一个元素使用。

简单来说，可以用这样一个形象化的式子来说明：
reduce( func, [1, 2,3] ) = func( func(1, 2), 3)

################################################################################
#reduce把一个函数作用在一个序列[x1, x2, x3...]上，这个函数必须接收两个参数，
#reduce把结果继续和序列的下一个元素做累积计算，其效果就是：
#reduce(f, [x1, x2, x3, x4]) = f(f(f(x1, x2), x3), x4)

#例1 比方说对一个序列求和，就可以用reduce实现： 
>>> def add(x, y):
...     return x + y
...
>>> reduce(add, [1, 3, 5, 7, 9])
25

#例2 把序列[1, 3, 5, 7, 9]变换成整数13579
>>> def fn(x, y):
...     return x * 10 + y
...
>>> reduce(fn, [1, 3, 5, 7, 9])
13579

#例3 结合map
>>> def fn(x, y):
...     return x * 10 + y
...
>>> def char2num(s):
...     return {'0': 0, '1': 1, '2': 2, '3': 3, '4': 4, '5': 5, '6': 6, '7': 7, '8': 8, '9': 9}[s]
...
>>> reduce(fn, map(char2num, '13579'))
13579

#例4 整理成一个str2int的函数就是：
def str2int(s):
    def fn(x, y):
        return x * 10 + y
    def char2num(s):
        return {'0': 0, '1': 1, '2': 2, '3': 3, '4': 4, '5': 5, '6': 6, '7': 7, '8': 8, '9': 9}[s]
    return reduce(fn, map(char2num, s))
	
#例5 还可以用lambda函数进一步简化成：
def char2num(s):
    return {'0': 0, '1': 1, '2': 2, '3': 3, '4': 4, '5': 5, '6': 6, '7': 7, '8': 8, '9': 9}[s]

def str2int(s):
    return reduce(lambda x,y: x*10+y, map(char2num, s))
#也就是说，假设Python没有提供int()函数，你完全可以自己写一个把字符串转化为整数
#的函数，而且只需要几行代码！
