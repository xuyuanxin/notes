
def file(name[, mode[, buffering]]):
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
    pass
    
    
def open(name[, mode[, buffering]]):
    '''
    @mode:
      'r' Read mode
      'w' Write mode
      'a' Append mode
      'b' Binary mode (added to other mode)
      '+' Read/write mode (added to other mode)
      Explicitly specifying read mode has the same effect as not supplying a mode st-
      ring at all. The write mode enables you to write to the file. The '+' can be a-
      dded to any of the other modes to indicate that both reading and writing is al-
      lowed. The 'b' mode changes the way the file is handled. Generally, Python ass-
	  umes that you are dealing with text files (containing characters). 
    @buffering
      If the parameter is 0 (or False), input/output (I/O) is unbuffered (all reads -
	  and writes go directly from/to the disk); if it is 1 (or True), I/O is buffere-
	  d (meaning that Python may use memory instead of disk space to make things go -
	  faster, and only update when you use flush or close). Larger numbers indicate -
	  the buffer size (in bytes), while –1 (or any negative number) sets the buffer -
	  size to the default.
	 
    You can open files with the @open function. The @open function takes a file  name 
    as its only mandatory argument, and returns a file object. If the file cannot  be 
    opened(file doesn’t exist, for example), IOError is raised. 
    '''
