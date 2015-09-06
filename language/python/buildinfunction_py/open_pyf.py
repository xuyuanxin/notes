'''
如何打开文件
handle=open(file_name,access_mode="r")
file_name变量包含我们希望打开的文件的字符串名称，access_mode 中的'r'表示读取，‘w’表示写入，'a'表示添加，其它可能用到的标实还有‘+’表示读写，‘b’表示2进制访问，如果未提供access_mode,默认为“r”.

如果open()成功，一个文件对象句柄会被返回。

filename=raw_input('enter file')
fobj=open(filename,'r')
for eachline in fobj:
    print eachline,
fobj.close()
#还记得 print 后面跟的“，”是什么意思吧，表示【每次打印都不换行，而是间隔空格】
'''
def file(name[, mode[, buffering]]):
    pass