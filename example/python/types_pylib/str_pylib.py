#!/usr/bin/env python
#coding=utf-8
# Filename: str_pylib.py
#####################################################################################
#字符串也是对象，同样具有方法。这些方法可以完成包括检验一部分字符串和去除空格在内的各
#种工作。

#你在程序中使用的字符串都是str类的对象。这个类的一些有用的方法会在下面这个例子中说明。
#如果要了解这些方法的完整列表，请参见help(str)。

name = 'Swaroop' # This is a string object 

if name.startswith('Swa'):
    print 'Yes, the string starts with "Swa"'

if 'a' in name:
    print 'Yes, it contains the string "a"'

if name.find('war') != -1:
    print 'Yes, it contains the string "war"'

delimiter = '_*_'
mylist = ['Brazil', 'Russia', 'India', 'China']
print delimiter.join(mylist) 
#这里，我们看到使用了许多字符串方法。startwith方法是用来测试字符串是否以给定字符串开
#始。in操作符用来检验一个给定字符串是否为另一个字符串的一部分。

#find方法用来找出给定字符串在另一个字符串中的位置，或者返回-1以表示找不到子字符串。
#str类也有以一个作为分隔符的字符串join序列的项目的整洁的方法，它返回一个生成的大字符
#串。

#output:
#Yes, the string starts with "Swa"
#Yes, it contains the string "a"
#Yes, it contains the string "war"
#Brazil_*_Russia_*_India_*_China 




#!/usr/bin/python



'''
5
5
-1
2
2
-1
'''
str = "this is really a string example....wow!!!";
str = "is";

print str.rfind(str);
print str.rfind(str, 0, 10);
print str.rfind(str, 10, 0);

print str.find(str);
print str.find(str, 0, 10);
print str.find(str, 10, 0);
