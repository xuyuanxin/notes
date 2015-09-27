#_*_coding:UTF-8_*_
'''
http://www.cnblogs.com/coser/archive/2011/12/17/2291160.html


'''

import struct
import binascii
import ctypes

'''                                                                                  |
代码中，首先定义了一个元组数据，包含int、string、float三种数据类型，然后定义了struct |
对象，并制定了format‘I3sf’，I 表示int，3s表示三个字符长度的字符串，f 表示 float。最后|
通过struct的pack和unpack进行打包和解包。通过输出结果可以发现，value被pack之后，转化为|
了一段二进制字节串，而unpack可以把该字节串再转换回一个元组，但是值得注意的是对于float|
的精度发生了改变，这是由一些比如操作系统等客观因素所决定的。打包之后的数据所占用的字 |
节数与C语言中的struct十分相似。                                                      |
输出：
Original values: (1, 'abc', 2.7) 
Format string : I3sf 
Uses : 12 bytes 
Packed Value : 0100000061626300cdcc2c40 
Unpacked Type : <type 'tuple'>  Value: (1, 'abc', 2.700000047683716)
'''
values = (1, 'abc', 2.7)
s = struct.Struct('I3sf')
packed_data = s.pack(*values)
unpacked_data = s.unpack(packed_data)
 
print 'Original values:', values
print 'Format string :', s.format
print 'Uses :', s.size, 'bytes'
print 'Packed Value :', binascii.hexlify(packed_data)
print 'Unpacked Type :', type(unpacked_data), ' Value:', unpacked_data


'''                                                                                  |
pack方法都是对输入数据进行操作后重新创建了一个内存空间用于返回，也就是说我们每次pack |
都会在内存中分配出相应的内存资源，这有时是一种很大的性能浪费。struct模块还提供了     |
pack_into() 和 unpack_from()的方法用来解决这样的问题，也就是对一个已经提前分配好的   |
buffer进行字节的填充，而不会每次都产生一个新对象对字节进行存储。                     |
输出：
Before : 000000000000000000000000 
After pack: 0100000061626300cdcc2c40 
After unpack: (1, 'abc', 2.700000047683716) 
'''
values = (1, 'abc', 2.7)
s = struct.Struct('I3sf')
prebuffer = ctypes.create_string_buffer(s.size)
print 'Before :',binascii.hexlify(prebuffer)
s.pack_into(prebuffer,0,*values)
print 'After pack:',binascii.hexlify(prebuffer)
unpacked = s.unpack_from(prebuffer,0)
print 'After unpack:',unpacked

'''                                                                                  |
pack_into和unpack_from方法均是对string buffer对象进行操作，并提供了offset参数，用户可|
以通过指定相应的offset，使相应的处理变得更加灵活。例如，我们可以把多个对象pack到一个 |
buffer里面，然后通过指定不同的offset进行unpack：                                     |
输出：
Before : 0000000000000000000000000000000000000000 
After pack: 0100000061626300cdcc2c406465666765000000 
(1, 'abc', 2.700000047683716) 
('defg', 101)
'''
values1 = (1, 'abc', 2.7)
values2 = ('defg',101)
s1 = struct.Struct('I3sf')
s2 = struct.Struct('4sI')
 
prebuffer = ctypes.create_string_buffer(s1.size+s2.size)
print 'Before :',binascii.hexlify(prebuffer)
s1.pack_into(prebuffer,0,*values1)
s2.pack_into(prebuffer,s1.size,*values2)
print 'After pack:',binascii.hexlify(prebuffer)
print s1.unpack_from(prebuffer,0)
print s2.unpack_from(prebuffer,s1.size)




