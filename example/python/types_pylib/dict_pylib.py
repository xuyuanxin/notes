#!/usr/bin/python
#coding=utf-8
# -*- coding: utf-8 -*-
#####################################################################################
#Python内置了字典：dict的支持，dict全称dictionary，在其他语言中也称为map，使用键-值（
#key-value）存储，具有极快的查找速度。
#举个例子，假设要根据同学的名字查找对应的成绩，如果用dict实现，只需要一个“名字”-“成绩”
#的对照表，直接根据名字查找成绩，无论这个表有多大，查找速度都不会变慢。用Python写一个
#dict 如下：
mydict = {'a': 1, 'b': 2} #定义并初始化
print mydict #{'a': 1, 'b': 2}

mydict['c'] = 2 #添加一个key
print mydict #{'a': 1, 'c': 2, 'b': 2}

mydict.pop('a') #删除一个key
print mydict

if 'b' in mydict:
    print 'b in mydict'

#通过dict提供的get方法，如果key不存在，可以返回None，或者自己指定的value：
#注意：返回None的时候Python的交互式命令行不显示结果。
print mydict.get('f')
print mydict.get('f',-1)
