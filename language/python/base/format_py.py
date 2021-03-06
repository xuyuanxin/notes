'''                                                                                  |
在Python中，采用的格式化方式和C语言是一致的，用%实现，举例如下：

>>> 'Hello, %s' % 'world'
'Hello, world'
>>> 'Hi, %s, you have $%d.' % ('Michael', 1000000)
'Hi, Michael, you have $1000000.'                                                    |
                                                                                     |
%运算符就是用来格式化字符串的。在字符串内部，%s表示用字符串替换，%d表示用整数替换，有|
几个%?占位符，后面就跟几个变量或者值，顺序要对应好。如果只有一个%?，括号可以省略。常 |
见的占位符有：                                                                       |
#%d	  整数
#%f	  浮点数
#%s	  字符串
#%x	  十六进制整数

格式化整数和浮点数还可以指定是否补0和整数与小数的位数：
>>> '%2d-%02d' % (3, 1)
' 3-01'
>>> '%.2f' % 3.1415926
'3.14'
#如果你不太确定应该用什么，%s永远起作用，它会把任何数据类型转换为字符串：
>>> 'Age: %s. Gender: %s' % (25, True)
'Age: 25. Gender: True'
#对于Unicode字符串，用法完全一样，但最好确保替换的字符串也是Unicode字符串：
>>> u'Hi, %s' % u'Michael'
u'Hi, Michael'
#有些时候，字符串里面的%是一个普通字符怎么办？这个时候就需要转义，用%%来表示一个%：
>>> 'growth rate: %d %%' % 7
'growth rate: 7 %'

#由于历史遗留问题，Python 2.x版本虽然支持Unicode，但在语法上需要'xxx'和u'xxx'两种字
#符串表示方式。Python当然也支持其他编码方式，比如把Unicode编码成GB2312：
>>> u'中文'.encode('gb2312')
'\xd6\xd0\xce\xc4'
#但这种方式纯属自找麻烦，如果没有特殊业务要求，请牢记仅使用Unicode和UTF-8这两种编码方式。
#在Python 3.x版本中，把'xxx'和u'xxx'统一成Unicode编码，即写不写前缀u都是一样的，而以
#字节形式表示的字符串则必须加上b前缀：b'xxx'。
#格式化字符串的时候，可以用Python的交互式命令行测试，方便快捷。







'''