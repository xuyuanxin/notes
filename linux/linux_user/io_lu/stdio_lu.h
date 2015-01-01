/*******************************************************************************
---->FILE
When we open a stream, the standard I/O function @fopen returns a pointer to a 
FILE object. This object is normally a structure that contains all the information
required by the standard I/O library to manage the stream: the file descriptor 
used for actual I/O, a pointer to a buffer for the stream, the size of the buffer,
acount of the number of characters currently in the buffer, an error flag, and 
the like.
To reference the stream, we pass its FILE pointer as an argument to each standard
I/O  function.

---->流和FILE对象
文件I/O都是针对文件描述符的，标准I/O是围绕流(stream)进行的。
When we open or create a file with the standardI/O library, we say that we have 
associated a stream with the file.

---->流与文件描述符
文件描述符:
如果我们用fd表示，该fd可以是open、pipe、dup、dup2和creat等调用返回的结果，在linux
系统中，设备也是以文件的形式存在，要对该设备进行操作就必须先打开这个文件，打开这个
文件就会，就会获得这个文件描述符，它是个很小的正整数，它是一个索引值，指向内核为每
一个进程所维护的该进程打开文件的记录表。文件描述符的优点：兼容POSIX标准，许多Linux
和UNIX系统调用都依赖于它。文件描述符的缺点：不能移植到UNIX以外的系统上去，也不直观。
fd只是一个索引.

文件指针:
C语言中使用的是文件指针而不是文件描述符做为I/O的句柄."文件指针(file pointer)"指
向进程用户区中的一个被称为FILE结构的数据结构。FILE结构包括一个缓冲区和一个文件描
述符值.而文件描述符值是文件描述符表中的一个索引.从某种意义上说文件指针就是句柄的
句柄。

---->流的定向 stream's orientation
A stream's orientation determines whether the characters that are read and written 
are single byte or multibyte. Initially,when a stream is created, it has no 
orientation. If a multibyte I/O function (see<wchar.h>) is used on a stream 
without orientation, the stream's orientation is set to wide oriented. If a byte 
I/O function is used on a stream without  orientation, the stream's orientation 
is set to byte oriented.Only two functions can change the orientation once set. 
The freopen function  will clear a stream’s orientation; the fwide function can 
be used to set a stream's orientation.
*/

/*三个默认打开的流
Three streams are predefined and automatically available to a process: standard 
input, standard output, and standard error.These streams refer to the same files 
as the file descriptors STDIN_FILENO, STDOUT_FILENO,and STDERR_FILENO,respectively.
These three standard I/O streams are referenced through the predefined file 
pointers stdin, stdout,and stderr. The file pointers are defined in the<stdio.h> 
header.
*/
#define stdin  /*Standard input  标准输入*/
#define stdout /*Standard output 标准输出*/
#define stderr /*Standard error  标准错误*/

/*
---->缓冲
The goal of the buffering provided by the standardI/O library is to use the minimum
number of read and write calls. Also, this library tries to do its buffering 
automatically for each I/O stream, obviating the need for the application to
worry about it.

---->三种类型的缓冲
1 全缓冲 Fully buffered 磁盘文件常用
  In this case, actual I/O takes place when the standard I/O buffer is filled. 
Files residing on disk are normally fully buffered by the standard I/O library.
The buffer used is usually obtained by one of the standard I/O functions calling 
@malloc the first time I/O is performed on a stream.
  The term flush describes the writing of a standardI/O buffer.A buffer can be 
flushed automatically by the standard I/O routines, such as when a buffer fills, 
or we can call the function @fflush to flush a stream. Unfortunately, in the UNIX
environment,flush means two different things. In terms of the standard I/O library,
it means writing out the contents of a buffer,which may be partially filled. In 
terms of the terminal driver,such as the @tcflush function,it means to discard 
the data that's already stored in a buffer.

2 行缓冲 Line buffered 终端显示常用
  写了一行之后才进行实际的I/O操作。缓冲行的长度是固定的，写满了(此时可能还没到一
  行的结束)也进行I/O操作。
  
3 不带缓冲 Unbuffered
  The standardI/O library does not buffer the	characters. If we write 15  
  characters with the standardI/O @fputs function, for example, we expect 
  these 15 characters to be output as soon as possible, probably with the
  @write function.
  
  The standard error stream, for example, is normally unbuffered so that any 
error messages are displayed as quickly as possible, regardless of whether they
contain a newline.

---->ISO C requires the following buffering characteristics:
1 Standard input and standard output are fully buffered, if and only if they do 
  not refer to an interactive device.
2 Standard error is never fully buffered.

  This, however,doesn't tell us whether standard input and standard output are
unbuffered or line buffered if they refer to an interactive device and whether 
standard error should be unbuffered or line buffered. Most implementations 
default  to  the following types of buffering:
1 Standarderror is always unbuffered.
2 All other streams are line buffered if they refer to a terminal device; 
  otherwise,they are fully buffered.
  The four platforms discussed in this book follow these conventions for 
  standard I/O buffering:standard error is unbuffered, streams open to terminal 
  devices areline buffered, and all other streams are fully buffered.

----> 暂未理解
Be aware that if we allocate a standardI/O buffer as an automatic variable within a
function, we have to close the stream beforereturning from the function. (We’ll discuss
this point further in Section 7.8.) Also, some implementations use part of the buffer for
internal  bookkeeping,  so  the  actual  number  of  bytes  of  data  that  can  be  stored  in  the
buffer can be less thansize.Ingeneral, we should let the system choose the buffer size
and  automatically  allocate  the  buffer.When  we  do  this,  the  standardI/O  library
automatically releases the buffer when we close the stream.

********************************************************************************
---->文件使用方式
文件使用方式由r,w,a,t,b，+六个字符拼成，各字符的含义是：
r : read 读
w : write 写
a : append 追加
t : text 文本文件，可省略不写
b : binary 二进制文件
+ : 读和写

凡用“r”打开一个文件时，该文件必须已经存在，且只能从该文件读出。
用“w”打开的文件只能向该文件写入。若打开的文件不存在，则以指定的文件名建立该文件，
若打开的文件已经存在，则将该文件删去，重建一个新文件。
若要向一个已存在的文件追加新的信息，只能用“a”方式打开文件。但此时该文件必须是存
在的，否则将会出错。
把一个文本文件读入内存时，要将ASCII码转换成二进制码，而把文件以文本方式写入磁盘时，
也要把二进制码转换成ASCII码，因此文本文件的读写要花费较多的转换时间。对二进制文件
的读写不存在这种转换。

