bytearray([source [, encoding [, errors]]])
说明：bytearray([source [, encoding [, errors]]])返回一个byte数组。Bytearray类型是一个可变的序列，并且序列中的元素的取值范围为 [0 ,255]。

参数source: 

如果source为整数，则返回一个长度为source的初始化数组；

如果source为字符串，则按照指定的encoding将字符串转换为字节序列；

如果source为可迭代类型，则元素必须为[0 ,255]中的整数；

如果source为与buffer接口一致的对象，则此对象也可以被用于初始化bytearray.。

示例：
>>> a = bytearray(3) 
>>> a
bytearray(b'\x00\x00\x00')
>>> a[0]
0
>>> a[1]
0
>>> a[2]
0
>>> b = bytearray("abc")
>>> b
bytearray(b'abc')
>>> b[0]
97 
>>> b[1]
98
>>> b[2]
99
>>> c = bytearray([1, 2, 3])
>>> c
bytearray(b'\x01\x02\x03')
>>> c[0]
1
>>> c[1]
2
>>> c[2]
3
>>> d = bytearray(buffer("abc"))
>>> d
bytearray(b'abc')
>>> d[0]
97
>>> d[1]
98
>>> d[2]
99















