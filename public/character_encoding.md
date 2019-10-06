# ASCII
原始的ASCII标准定义了从0到127的字符，128到255的编码并没有被制定ASCII标准的人所规定，其它国家的人趁这个机会开始使用128到255范围内的编码来表达自己语言中的字符。ASCII码的问题在于尽管所有人都在0-127号字符的使用上达成了一致，但对于128-255号字符却有很多很多不同的解释。与此同时，在亚洲有更让人头疼的问题。亚洲语言有更多的字符和字形需要被存储。一 个字节已经不够用了，所以他们开始使用两个字节来存储字符。这被称作DBCS(双字节编码方案)。

# Unicode
应该提出一种标准方案来展示世界上所有语言中的所有字符，出于这个目的，Unicode诞生了。Unicode就像一个电话本，标记着字符和数字之间的映射关系。理论上每种语言中的每种字符都被Unicode协会指定了一个数字。Unicode只是一个用来映射字符和数字的标准。它对支持字符的数量没有限制，也不要求字符必须占两个，三个或者其它任意数量的字节。Unicode字符是怎样被编码成内存中的字节这是另外的话题, 它是被UTF(Unicode Transformation Formats)定义的。

# UTF
两个最流行的Unicode编码方案是UTF-8和UTF-16。在UTF-8中, 0-127号的字符用1个字节来表示, 使用和US-ASCII相同的编码. 这意味着1980年代写的文档用UTF-8打开一点问题都没有. 只有128号及以上的字符才用2个,3个或者4个字节来表示.因此, UTF-8被称作可变长度编码. UTF-16它使用2个或者4个字节来存储字符. 

# 字节序标记(BOM)
如果你经常要在高低字节序的系统间转换文档，并且希望区分字节序，还有一种奇怪的约定，被称作BOM。BOM是一个设计得很巧妙的字符，用来放在文档的开头告诉阅读器该文档的字节序。在UTF-16中，它是通过在第一个字节放置FE FF来实现的。在不同字节序的文档中，它会被显示成FF FE或者FE FF，清楚的把这篇文档的字节序告诉了解释器。

# 二进制流
二进制流到屏幕字符的过程：二进制流->根据编码方式解码出码点->根据unicode码点解释出字符->系统渲染绘出这个字符。文本字符保存到计算机上的过程：输入字符->根据字符找到对应码点->根据编码方式把码点编码成二进制流->保存二进制流到硬盘 

# UCS
通用字符集(Universal Character Set, UCS)是由ISO制定的ISO 10646(或称ISO/IEC 10646)标准所定义的标准字符集。UCS-2用两个字节编码，UCS-4用4个字节编码。UCS-4根据最高位为0的最高字节分成2^7=128个group。每个group再根据次高字节分为256个平面 (plane)。每个平面根据第3个字节分为256行(row)。每行有256个码位(cell)。group 0的平面0被称作BMP(Basic Multilingual Plane)。如果UCS-4的前两个字节为全零，那么将UCS-4的BMP去掉前面的两个零字节就得到了UCS-2。每个平面有2^16=65536个码位。Unicode计划使用了17个平面，一共有17×65536=1114112个码位。在Unicode 5.0.0版本中，已定义的码位只有238605个，分布在平面0，平面1，平面2，平面14，平面15，平面16。其中平面15和平面16上只是定义了两个各占65534个码位的专用区(Private Use Area)，分别是0xF0000-0xFFFFD和0x100000-0x10FFFD。所谓专用区，就是保留给大家放自定义字符的区域，可以简写为PUA。

# 码位和编码位置
[code point or code position](http://en.wikipedia.org/wiki/Code_point), In character encoding terminology, a code point or code position is any of the numerical values that make up the code space. Many code points represent single characters but they can also have other meanings, such as for formatting.

For example, the character encoding scheme ASCII comprises 128 code points in the range 0x0 to 0x7F, Extended ASCII comprises 256 code points in the range 0x0 to 0xFF, and Unicode comprises 1,114,112 code points in the range 0x0 to 0x10FFFF. The Unicode code space is divided into seventeen planes (the basic multilingual plane, and 16 supplementary planes), each with 65,536 (= 2^16) code points. Thus the total size of the Unicode code space is 17 × 65,536 = 1,114,112. 

# 缩略语
DBCS   Double Byte Charecter Set 双字节字符集
Ascii     American Standard Code for Information Interchange，美国信息互换标准代码 
UCS     Universal Multiple-Octet Coded Character Set，简称 UCS, 俗称 "UNICODE". 
BOM     byte-order mark 字节序标记 
BMP     Basic Multilingual Plane

# 参考
[字符集和字符编码(Charset & Encoding)](http://www.cnblogs.com/skynet/archive/2011/05/03/2035105.html)
[学点编码知识又不会死：Unicode的流言终结者和编码大揭秘](http://www.freebuf.com/articles/others-articles/25623.html) 
[趣谈unicode，ansi，utf-8，unicode big endian这些编码有什么区别](http://www.freebuf.com/articles/others-articles/25623.html)