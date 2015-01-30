#!/usr/bin/env python
#coding=utf-8
# Filename: list_pylib.py
#####################################################################################
#你可以增加或删除项目，我们说列表是 可变的 数据类型，即这种类型是可以被改变的。
# This is my shopping list
shoplist=['apple','mango','carrot','banana']

print 'I have',len(shoplist),'items to purchase.'

print 'These items are:', # Notice the comma at end of the line
for item in shoplist:
	print item,

print '\nI also have to buy rice.'
shoplist.append('rice')
print 'My shopping list is now',shoplist

print 'I will sort my list now'
shoplist.sort()
print 'Sorted shopping list is',shoplist

print 'The first item I will buy is',shoplist[0]
olditem=shoplist[0]
del shoplist[0]
print 'I bought the',olditem
print 'My shopping list is now',shoplist

print '-----------------> list init <-----------------------'
print '----> [[1] for i in range(3)]  = '
list1 = [[1] for i in range(3)]
print list1
print '----> [[1 for i in range(3)]]  = '
list2 = [[1 for i in range(3)]]
print list2
print '----> [[0 for i in range(n)] for i in range(m)] = '
list3 = [[1 for i in range(3)] for i in range(3)]
print list3

a = 0
for i in range(1, 1):  #[1,1)
    a = a+1
print 'a=',a

a = 0
for i in range(1, 2): #[1,2)
    a = a+1
	
print 'a=',a

################# 切片
L = ['Michael', 'Sarah', 'Tracy', 'Bob', 'Jack']
l2 = L[0:3]    #取前3个元素[0,3).
l3 = L[:3]     #如果第一个索引是0，还可以省略：
l4 = L[-2:]    #['Bob', 'Jack']
l5 = L[-2:-1]  #倒数第一个元素的索引是-1。['Bob']
print l2

#只写[:]就可以原样复制一个list：

#tuple也是一种list，唯一区别是tuple不可变。因此，tuple也可以用切片操作，只是操作的结
#果仍是tuple：
t1 = (0, 1, 2, 3, 4, 5)[:3]
print t1 #(0, 1, 2)
#字符串'xxx'或Unicode字符串u'xxx'也可以看成是一种list，每个元素就是一个字符。因字符串
#也可以用切片操作，只是操作结果仍是字符串：
str1 = 'ABCDEFG'[:3]
print str1 #'ABC'
str2 = 'ABCDEFG'[::2] #每2个取一个：
print str2 #'ACEG'

#对象与参考
#当你创建一个对象并给它赋一个变量的时候，这个变量仅仅 参考 那个对象，而不是表示这个对
#象本身！也就是说，变量名指向你计算机中存储那个对象的内存。这被称作名称到对象的绑定。

#一般说来，你不需要担心这个，只是在参考上有些细微的效果需要你注意。这会通过下面这个例
#子加以说明。
print 'Simple Assignment'
shoplist = ['apple', 'mango', 'carrot', 'banana']
mylist = shoplist # mylist is just another name pointing to the same object!

del shoplist[0]

print 'shoplist is', shoplist
print 'mylist is', mylist
# notice that both shoplist and mylist both print the same list without
# the 'apple' confirming that they point to the same object

print 'Copy by making a full slice'
mylist = shoplist[:] # make a copy by doing a full slice
del mylist[0] # remove first item

print 'shoplist is', shoplist
print 'mylist is', mylist
# notice that now the two lists are different 

