#!/usr/bin/python
#coding=utf-8
# -*- coding: utf-8 -*-

def sayhi():
    print 'Hi, this is mymodule speaking.'

version = '0.1'

def test():
    print 'mymodule hello world!'

#当我们在命令行运行 module_myself_py 模块文件时，Python解释器把一个特殊变量__name__置
#为 __main__ ，而如果在其他地方导入该 module_myself_py 模块时，if判断将失败，因此，这
#种if测试可以让一个模块通过命令行运行时执行一些额外的代码，最常见的就是运行测试。
#我们可以用命令行运行 module_myself_py.py 看看效果：
#$ python module_myself_py.py
#mymodule hello world!
#如果启动Python交互环境，再导入 module_myself_py.py 模块：
#$ python
#Python 2.7.5 (default, Aug 25 2013, 00:04:04) 
#[GCC 4.2.1 Compatible Apple LLVM 5.0 (clang-500.0.68)] on darwin
#Type "help", "copyright", "credits" or "license" for more information.
#>>> import module_myself_py
#>>>
#导入时，没有打印，因为没有执行test()函数。
#调用module_myself_py.test()时，才能打印：
#>>> module_myself_py.test()
#mymodule hello world!	
if __name__=='__main__':
    test()
