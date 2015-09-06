'''
file()内建函数它的功能等于open(),但是可以看出，他是个文件工厂(生成文件对象)，类似于int()生成整型对象，dict()生成字典对象


file(	filename[, mode[, bufsize]])

file()函数是2.2中新增的函数，它与open()函数一样，相当于open()的别名，不过比open()更直观一些。


读出一个文件的内容很简单：



text = file(filename).read()


这里我省略了模式(mode)参数，它缺省为’r'。


现在 Python 已经支持三种主要平台的回车符：’\n’是Unix的换行符、’r'是Macintosh的换行符、’\r\n’是Windows的换行符。那么在打开文件时使用’U'或’rU’模式就可以同时支持这三种换行符。


如果要对文件进行一行行的处理，有多种方法：



先一次性将文本行读到一个列表中，再对列表进行处理


lines = file(filename).readlines()
for line in lines:
    print line



使用文件对象的readline()方法进行一行行的处理


f = file(filename)
while True:
    line = f.readline()
    if line:
        print line
    else:
        break



还有就是2.3中的新方法，在for循环中直接使用文件对象


for line in file(filename):
    print line


这是因为文件对象中增加了迭代功能。


注意：上面读出的每一行都带有回车符，因此在某些情况下你可能需要将它们去掉。

'''
def file(name[, mode[, buffering]]):
    pass