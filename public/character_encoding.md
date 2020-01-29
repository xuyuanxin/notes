# 字符编码

## ASCII

原始的ASCII标准定义了从0到127的字符，128到255的编码并没有被制定ASCII标准的人所规定，其它国家的人趁这个机会开始使用128到255范围内的编码来表达自己语言中的字符。ASCII码的问题在于尽管所有人都在0-127号字符的使用上达成了一致，但对于128-255号字符却有很多很多不同的解释。与此同时，在亚洲有更让人头疼的问题。亚洲语言有更多的字符和字形需要被存储。一 个字节已经不够用了，所以他们开始使用两个字节来存储字符。这被称作DBCS(双字节编码方案)。

## Unicode
应该提出一种标准方案来展示世界上所有语言中的所有字符，出于这个目的，Unicode诞生了。Unicode就像一个电话本，标记着字符和数字之间的映射关系。理论上每种语言中的每种字符都被Unicode协会指定了一个数字。Unicode只是一个用来映射字符和数字的标准。它对支持字符的数量没有限制，也不要求字符必须占两个，三个或者其它任意数量的字节。Unicode字符是怎样被编码成内存中的字节这是另外的话题, 它是被UTF(Unicode Transformation Formats)定义的。

## UTF
两个最流行的Unicode编码方案是UTF-8和UTF-16。在UTF-8中, 0-127号的字符用1个字节来表示, 使用和US-ASCII相同的编码. 这意味着1980年代写的文档用UTF-8打开一点问题都没有. 只有128号及以上的字符才用2个,3个或者4个字节来表示.因此, UTF-8被称作可变长度编码. UTF-16它使用2个或者4个字节来存储字符. 

## 字节序标记(BOM)
如果你经常要在高低字节序的系统间转换文档，并且希望区分字节序，还有一种奇怪的约定，被称作BOM。BOM是一个设计得很巧妙的字符，用来放在文档的开头告诉阅读器该文档的字节序。在UTF-16中，它是通过在第一个字节放置FE FF来实现的。在不同字节序的文档中，它会被显示成FF FE或者FE FF，清楚的把这篇文档的字节序告诉了解释器。

## 二进制流
二进制流到屏幕字符的过程：二进制流->根据编码方式解码出码点->根据unicode码点解释出字符->系统渲染绘出这个字符。文本字符保存到计算机上的过程：输入字符->根据字符找到对应码点->根据编码方式把码点编码成二进制流->保存二进制流到硬盘 

## UCS
通用字符集(Universal Character Set, UCS)是由ISO制定的ISO 10646(或称ISO/IEC 10646)标准所定义的标准字符集。UCS-2用两个字节编码，UCS-4用4个字节编码。UCS-4根据最高位为0的最高字节分成2^7=128个group。每个group再根据次高字节分为256个平面 (plane)。每个平面根据第3个字节分为256行(row)。每行有256个码位(cell)。group 0的平面0被称作BMP(Basic Multilingual Plane)。如果UCS-4的前两个字节为全零，那么将UCS-4的BMP去掉前面的两个零字节就得到了UCS-2。每个平面有2^16=65536个码位。Unicode计划使用了17个平面，一共有17×65536=1114112个码位。在Unicode 5.0.0版本中，已定义的码位只有238605个，分布在平面0，平面1，平面2，平面14，平面15，平面16。其中平面15和平面16上只是定义了两个各占65534个码位的专用区(Private Use Area)，分别是0xF0000-0xFFFFD和0x100000-0x10FFFD。所谓专用区，就是保留给大家放自定义字符的区域，可以简写为PUA。

## 码位和编码位置
[code point or code position](http://en.wikipedia.org/wiki/Code_point), In character encoding terminology, a code point or code position is any of the numerical values that make up the code space. Many code points represent single characters but they can also have other meanings, such as for formatting.

For example, the character encoding scheme ASCII comprises 128 code points in the range 0x0 to 0x7F, Extended ASCII comprises 256 code points in the range 0x0 to 0xFF, and Unicode comprises 1,114,112 code points in the range 0x0 to 0x10FFFF. The Unicode code space is divided into seventeen planes (the basic multilingual plane, and 16 supplementary planes), each with 65,536 (= 2^16) code points. Thus the total size of the Unicode code space is 17 × 65,536 = 1,114,112. 

## 缩略语
DBCS   Double Byte Charecter Set 双字节字符集
Ascii     American Standard Code for Information Interchange，美国信息互换标准代码 
UCS     Universal Multiple-Octet Coded Character Set，简称 UCS, 俗称 "UNICODE". 
BOM     byte-order mark 字节序标记 
BMP     Basic Multilingual Plane



## 字符编码

我们已经讲过了，字符串也是一种数据类型，但是，字符串比较特殊的是还有一个编码问题。

因为计算机只能处理数字，如果要处理文本，就必须先把文本转换为数字才能处理。最早的计算机在设计时采用8个比特（bit）作为一个字节（byte），所以，一个字节能表示的最大的整数就是255（二进制11111111=十进制255），如果要表示更大的整数，就必须用更多的字节。比如两个字节可以表示的最大整数是`65535`，4个字节可以表示的最大整数是`4294967295`。

由于计算机是美国人发明的，因此，最早只有127个字符被编码到计算机里，也就是大小写英文字母、数字和一些符号，这个编码表被称为`ASCII`编码，比如大写字母`A`的编码是`65`，小写字母`z`的编码是`122`。

但是要处理中文显然一个字节是不够的，至少需要两个字节，而且还不能和ASCII编码冲突，所以，中国制定了`GB2312`编码，用来把中文编进去。

你可以想得到的是，全世界有上百种语言，日本把日文编到`Shift_JIS`里，韩国把韩文编到`Euc-kr`里，各国有各国的标准，就会不可避免地出现冲突，结果就是，在多语言混合的文本中，显示出来会有乱码。

因此，Unicode应运而生。Unicode把所有语言都统一到一套编码里，这样就不会再有乱码问题了。

Unicode标准也在不断发展，但最常用的是用两个字节表示一个字符（如果要用到非常偏僻的字符，就需要4个字节）。现代操作系统和大多数编程语言都直接支持Unicode。

现在，捋一捋ASCII编码和Unicode编码的区别：ASCII编码是1个字节，而Unicode编码通常是2个字节。

字母`A`用ASCII编码是十进制的`65`，二进制的`01000001`；

字符`0`用ASCII编码是十进制的`48`，二进制的`00110000`，注意字符`'0'`和整数`0`是不同的；

汉字`中`已经超出了ASCII编码的范围，用Unicode编码是十进制的`20013`，二进制的`01001110 00101101`。

你可以猜测，如果把ASCII编码的`A`用Unicode编码，只需要在前面补0就可以，因此，`A`的Unicode编码是`00000000 01000001`。

新的问题又出现了：如果统一成Unicode编码，乱码问题从此消失了。但是，如果你写的文本基本上全部是英文的话，用Unicode编码比ASCII编码需要多一倍的存储空间，在存储和传输上就十分不划算。

所以，本着节约的精神，又出现了把Unicode编码转化为“可变长编码”的`UTF-8`编码。UTF-8编码把一个Unicode字符根据不同的数字大小编码成1-6个字节，常用的英文字母被编码成1个字节，汉字通常是3个字节，只有很生僻的字符才会被编码成4-6个字节。如果你要传输的文本包含大量英文字符，用UTF-8编码就能节省空间：

| 字符 | ASCII    | Unicode           | UTF-8                      |
| :--- | :------- | :---------------- | :------------------------- |
| A    | 01000001 | 00000000 01000001 | 01000001                   |
| 中   | x        | 01001110 00101101 | 11100100 10111000 10101101 |

从上面的表格还可以发现，UTF-8编码有一个额外的好处，就是ASCII编码实际上可以被看成是UTF-8编码的一部分，所以，大量只支持ASCII编码的历史遗留软件可以在UTF-8编码下继续工作。

搞清楚了ASCII、Unicode和UTF-8的关系，我们就可以总结一下现在计算机系统通用的字符编码工作方式：

在计算机内存中，统一使用Unicode编码，当需要保存到硬盘或者需要传输的时候，就转换为UTF-8编码。

用记事本编辑的时候，从文件读取的UTF-8字符被转换为Unicode字符到内存里，编辑完成后，保存的时候再把Unicode转换为UTF-8保存到文件：

![rw-file-utf-8](https://www.liaoxuefeng.com/files/attachments/923923787018816/0)

浏览网页的时候，服务器会把动态生成的Unicode内容转换为UTF-8再传输到浏览器：

![web-utf-8](https://www.liaoxuefeng.com/files/attachments/923923759189600/0)

所以你看到很多网页的源码上会有类似``的信息，表示该网页正是用的UTF-8编码。

### Python的字符串

搞清楚了令人头疼的字符编码问题后，我们再来研究Python的字符串。

在最新的Python 3版本中，字符串是以Unicode编码的，也就是说，Python的字符串支持多语言，例如：

```
>>> print('包含中文的str')
包含中文的str
```

对于单个字符的编码，Python提供了`ord()`函数获取字符的整数表示，`chr()`函数把编码转换为对应的字符：

```
>>> ord('A')
65
>>> ord('中')
20013
>>> chr(66)
'B'
>>> chr(25991)
'文'
```

如果知道字符的整数编码，还可以用十六进制这么写`str`：

```
>>> '\u4e2d\u6587'
'中文'
```

两种写法完全是等价的。

由于Python的字符串类型是`str`，在内存中以Unicode表示，一个字符对应若干个字节。如果要在网络上传输，或者保存到磁盘上，就需要把`str`变为以字节为单位的`bytes`。

Python对`bytes`类型的数据用带`b`前缀的单引号或双引号表示：

```
x = b'ABC'
```

要注意区分`'ABC'`和`b'ABC'`，前者是`str`，后者虽然内容显示得和前者一样，但`bytes`的每个字符都只占用一个字节。

以Unicode表示的`str`通过`encode()`方法可以编码为指定的`bytes`，例如：

```
>>> 'ABC'.encode('ascii')
b'ABC'
>>> '中文'.encode('utf-8')
b'\xe4\xb8\xad\xe6\x96\x87'
>>> '中文'.encode('ascii')
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
UnicodeEncodeError: 'ascii' codec can't encode characters in position 0-1: ordinal not in range(128)
```

纯英文的`str`可以用`ASCII`编码为`bytes`，内容是一样的，含有中文的`str`可以用`UTF-8`编码为`bytes`。含有中文的`str`无法用`ASCII`编码，因为中文编码的范围超过了`ASCII`编码的范围，Python会报错。

在`bytes`中，无法显示为ASCII字符的字节，用`\x##`显示。

反过来，如果我们从网络或磁盘上读取了字节流，那么读到的数据就是`bytes`。要把`bytes`变为`str`，就需要用`decode()`方法：

```
>>> b'ABC'.decode('ascii')
'ABC'
>>> b'\xe4\xb8\xad\xe6\x96\x87'.decode('utf-8')
'中文'
```

如果`bytes`中包含无法解码的字节，`decode()`方法会报错：

```
>>> b'\xe4\xb8\xad\xff'.decode('utf-8')
Traceback (most recent call last):
  ...
UnicodeDecodeError: 'utf-8' codec can't decode byte 0xff in position 3: invalid start byte
```

如果`bytes`中只有一小部分无效的字节，可以传入`errors='ignore'`忽略错误的字节：

```
>>> b'\xe4\xb8\xad\xff'.decode('utf-8', errors='ignore')
'中'
```

要计算`str`包含多少个字符，可以用`len()`函数：

```
>>> len('ABC')
3
>>> len('中文')
2
```

`len()`函数计算的是`str`的字符数，如果换成`bytes`，`len()`函数就计算字节数：

```
>>> len(b'ABC')
3
>>> len(b'\xe4\xb8\xad\xe6\x96\x87')
6
>>> len('中文'.encode('utf-8'))
6
```

可见，1个中文字符经过UTF-8编码后通常会占用3个字节，而1个英文字符只占用1个字节。



## 参考

[字符集和字符编码(Charset & Encoding)](http://www.cnblogs.com/skynet/archive/2011/05/03/2035105.html)

[学点编码知识又不会死：Unicode的流言终结者和编码大揭秘](http://www.freebuf.com/articles/others-articles/25623.html) 

[趣谈unicode，ansi，utf-8，unicode big endian这些编码有什么区别](http://www.freebuf.com/articles/others-articles/25623.html)

# CSV

逗号分隔值（Comma-Separated Values，CSV，有时也称为字符分隔值，因为分隔字符也可以不 是逗号），其文件以纯文本形式存储表格数据（数字和文本）。纯文本意味着该文件是一个字符序列，不含必须像二进制数字那样被解读的数据。CSV文件由任意数目的记录组成，记录间以某种换行符分隔；每条记录由字段组成，字段间的分隔符是其它字符或字符串，最常见的是逗号或|制表符。通常，所有记录都有完全相同的字段序列。CSV文件格式的通用标准并不存在，但是在RFC 4180中有基础性的描述。使用的字符编码同样没有被指定，但是7-bitASCII是最基本的通用编码。

## libSVM的数据格式

`Label 1:value 2:value ….`
`<label> <index1>:<value1> <index2>:<value2> ...`

<label> 是训练数据集的目标值，对于分类，它是标识某类的整数(支持多个类)；对于回归，是任意实数。
<index> 是以1开始的整数，可以是不连续的；
<Value> 就是要训练的数据，从分类的角度来说就是特征值，数据之间用空格隔开

比如: -15 1:0.708 2:1056 3:-0.3333。需要注意的是，如果特征值为0，特征冒号前面的(姑且称做序号)可以不连续。如：-15 1:0.708 3:-0.3333。表明第2个特征值为0，从编程的角度来说，这样做可以减少内存的使用。

# 缩略语

control : ctrl
e.g. 拉丁语缩写。exempli gratia的缩写，意思是"for example"（举例），
i.e. 拉丁语缩写。id est的缩写，意思是"that is"（即）。
etc  等等及其他；诸如此类
ISBN: International Standard Book Number, a unique book identifier
ECS: Elastic Cloud Server  弹性云服务器	

## Math	

curly braces     {}    大括号
parentheses      ()	
semicolons       ;
colons           :
angle brackets   <>
comma            ,     逗号



