#!/usr/bin/env python
#coding=utf-8
# Filename: tuple_pylib.py
#####################################################################################注释
#元组
#元组和列表十分类似，只不过元组和字符串一样是 不可变的 即你不能修改元组。元组通过圆括
#号中用逗号分割的项目定义。元组通常用在使语句或用户定义的函数能够安全地采用一组值的时
#候，即被使用的元组的值不会改变。

zoo = ('wolf', 'elephant', 'penguin')
print 'Number of animals in the zoo is', len(zoo)

new_zoo = ('monkey', 'dolphin', zoo)
print 'Number of animals in the new zoo is', len(new_zoo)
print 'All animals in new zoo are', new_zoo

#索引 运算符。
#我们使用new_zoo[2]来访问new_zoo中的第三个项目。我们使用new_zoo[2][2]来访问new_zoo元
#组的第三个项目的第三个项目。
print 'Animals brought from old zoo are', new_zoo[2]
print 'Last animal brought from old zoo is', new_zoo[2][2] 

#含有0个或1个项目的元组。
#一个空的元组由一对空的圆括号组成，如myempty = ()。然而，含有单个元素的元组就不那么简
#单了。你必须在第一个（唯一一个）项目后跟一个逗号，这样Python才能区分元组和表达式中一
#个带圆括号的对象。即如果你想要的是一个包含项目1的元组的时候，你应该指明
#            singleton = (1 , )。
