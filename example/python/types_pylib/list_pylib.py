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

