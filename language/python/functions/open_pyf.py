

    
def open(name[, mode[, buffering]]):
    '''
    @name:
	   relative or absolute/full pathname
    @mode:
      'r' Read mode (defaults)
      'w' Write mode
      'a' Append mode
      'b' Binary mode (added to other mode)
      '+' Read/write mode (added to other mode)
      The '+' can be added to any of the other modes to indicate that both reading a-
	  nd writing is allowed. The 'b' mode changes the way the file is handled. Gener-
	  ally, Python assumes that you are dealing with text files (containing characte-
	  rs). 
	  
	  Any file opened with mode 'r' or 'U' must exist. Any file opened with 'w'  will 
	  be truncated first if it exists, and then the file is (re)created. Any file op-
	  ened with 'a' will be opened for append. All writes to files opened with 'a' w-
	  ill be from end-of-file, even if you seek elsewhere during access. If the  file 
	  does not exist, it will be created, making it the same as if you opened the fi-
	  le in 'w' mode. 
	  
	  'b' is antiquated on all Unix systems that are POSIX-compliant (including Linux
	  ) because they treat all files as binary files, including text files. 
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

    File Mode    Operation
    r            Open for read
    rU or U      Open for read with universal NEWLINE support (PEP 278)
    w            Open for write (truncate if necessary)
    a            Open for append (always works from EOF, create if necessary)
    r+           Open for read and write
    w+           Open for read and write (see w above)
    a+           Open for read and write (see a above)
    rb           Open for binary read
    wb           Open for binary write (see w above)
    ab           Open for binary append (see a above)
    rb+          Open for binary read and write (see r+ above)
    wb+          Open for binary read and write (see w+ above)
    ab+          Open for binary read and write (see a+ above)
    '''

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
    

