struct iovec {
  void   *iov_base;   /* starting address of buffer */
  size_t  iov_len;    /* size of buffer */
};

#define IOV_MAX  /* 1024 */




/*
---->不带缓冲I/O unbuffered I/O
与标准I/O相对照,术语不带缓冲指每个read和write都调用内核中的一个系统调用.
这些不带缓冲的I/O不是ISO C的组成部分,但它们是POSIX.1的组成部分.

---->文件描述符
A file descriptor is a non-negative integer. To the kernel, all open files are 
referred to by file descriptors. 
file descriptor 0 STDIN_FILENO  with the standard input of a process, 
file descriptor 1 STDOUT_FILENO with the standard output 
file descriptor 2 STDERR_FILENO with the standard error.

---->当前文件偏移量 current file offset
每个打开的文件都有一个与其相关联的当前文件偏移量,通常是一个非负整数,用以度量从
文件开始处计算的字节数。通常,文件的当前偏移量应当是一个非负整数,但是,某些设备也
可能允许负的偏移量。但对于普通文件，则其偏移量必须是非负值。

---->描述符集
通常是一个整数数组，其中每个整数中的每一个bit位对应一个描述符。
假设使用32位整数，数组的第一个元素对应于描述符0~31，第二个元素对应于描述符32~63，以此类推。
fd_set
void FD_ZERO(fd_set *fdset);         clear all bits in fdset
void FD_SET(int fd, fd_set *fdset);  turn on the bit for fd in fdset
void FD_CLR(int fd, fd_set *fdset);  turn off the bit for fd in fdset
int FD_ISSET(int fd, fd_set *fdset); is the bit for fd on in fdset
 
---->current file offset
通常是一个非负整数，用以度量从文件开始处计算的字节数。

---->文件共享 file sharing
The kernel uses three data structures to represent an open file, and the relationships
among them determine the effect one process has on another with regard to file sharing.
1 entry in the process table
  在进程表中记录着每个进程打开的文件，每个文件占一个表项，表项中记录的是文件描述符和指向文件表的指针
  (a)  The file descriptor flags (close-on-exec)
  (b)  A pointer to a file table entry
2 file table
  The kernel maintains a file table for all open files. Each file table entry contains
  (a) The file status flags for the  file, such as read, write, append, sync, and nonblocking;
  (b) The current file offset
  (c) A pointer to the v-node table entry for the file
3 v-node
  Each open file (or device) has a v-node structurethat contains information 
  about the type of file and pointers to functions that operate on the file. 
  v-node also contains the i-node for the file. This information is read from
  disk when the file is opened, so that all the pertinent information about the
  file is readily available. For example, the i-node contains the owner of the 
  file, the size of the file, pointers to wherethe actual data blocks for the 
  file are located on disk, and so on.


  
+-----------------------------------------------+
|              process table entry              |   进程表  记录每个进程打开的文件
|------------------------------------------------
|    fd0   | file descriptor flags  |   pointer |   file descriptor flags 和 pointer 称为一个表项
|------------------------------------------------
|    fd1   | file descriptor flags  |   pointer |   file descriptor flags  
|------------------------------------------------  
|    fd2   | file descriptor flags  |   pointer |   pointer指向 文件表(file table entry)
|------------------------------------------------ 
|    ...   | file descriptor flags  |   pointer |  
+-----------------------------------------------+  

+----------------------+
|   file table entry   |    文件表(file table entry) 进程每个打开的文件对应一个文件表
+----------------------+
|   file status flags  |    如果多个进程打开同一个文件，每个进程都有自己的文件表 
|-----------------------
|  current file offset |
|-----------------------  
|    v-node pointer    |
+----------------------+  


+----------------------+
|  v-node table entry  |    v节点 进程每个打开的文件对应一个
+----------------------+
|  v-node information  |    如果多个进程打开同一个文件，共用一个v节点
|-----------------------
|         v_data       |
+----------------------+  

It is possible for more than one file descriptor entry to point to the same 
file table entry, as we'll see when we discuss the dup function. This also 
happens after a fork when the parent and the child share the same file table 
entry for each open descriptor 

Given these data structures, we now need to be more specific about what happens
with certain operations that we've already described.
1 After each writeis complete, the current file offset in the file table entry 
  is incremented by the number of bytes written. If this causes the current 
  file offset to exceed the current file size, the current file size in the 
  i-node table entry is set to the current file offset .
2 If a file is opened with the O_APPEND flag, a corresponding flag is set in 
  the file status flags of the file table entry.Each time a write is performed 
  for a file with this append flag set, the current file offset in the file 
  table entry is first set to the current file size from the i-node table entry.
  This forces every write to be appended to the current end of file.
3 If a file is positioned to its current end of file using lseek,all that happens 
  is the current file offset in the file table entry is set to the current file 
  size from the i-node table entry.(Note that this is not the same as if the file 
  was opened with the O_APPEND flag)
4 The lseek function modifies only the current file offset in the file table entry.
  No I/O takes place.


----> atomic operations
In general, the term atomic operation refers to an operation that might be composed
of multiple steps. If the operation is performed atomically, either all the steps are
performed (on success) or none are performed (on failure). It must not be possible for
only a subset of the steps to be performed. 

Assume that two independent processes, A and B, are appending to the same file.Each has opened the file but without the O_APPEND flag.
Each process has its own file table entry,but they sharea single v-node table entry.Assume that process A does the lseek and that this 
sets the current offset for the file for process A to byte offset 1,500 (the current end of file). Then the kernel switches processes, 
and B continues running. Process B then does the lseek,which sets the current offset for the file for process B to byte offset 1,500 
also (the current end of file). Then B calls write,which increments B's current file offset for the file to 1,600. Because the file’s 
size has been extended, the kernel also updates the current file size in the v-node to 1,600. Then the kernel switches processes and A 
resumes. When A calls write,the data is written starting at the current file offset for A, which is byte offset 1,500. This overwrites 
the data that B wrote to the file.

---->缓存
Traditional implementations of the UNIX System have a buffer cache or page cache in the kernel through which most disk I/O passes. 
When we write data to a file, the data is normally copied by the kernel into one of its buffers and queued for writing to disk at
some later time. This is called delayed write. The kernel eventually writes all the delayed-write blocks to disk, normally when it
needs to reuse the buffer for some other disk block. To ensure consistency of the file system on disk with the contents of the buffer 
cache, the sync, fsync,and fdatasync functions are provided.

---->I/O多路转接 I/O multiplexing
先构造一张有关描述符的列表,然后调用一个函数,直到这些描述符中的一个已经准备好进行I/O时,该函数才返回.在返回时它告诉进程哪些描述符已经准备好可以进行I/O

---->存储映射I/O 
使一个磁盘文件与存储空间中的一个缓冲区相映射.当从缓冲区读取数据就相当于读取文件中的相应字节。将数据存入缓冲区则相应字节就自动地写入文件。
这样就可以在不使用read和write的情况下执行I/O。
fork之后子进程继承存储映射区

---->Interruptibility of select and poll
When the automatic restarting of interrupted system calls was introduced with
4.2BSD(Section 10.5), the @select function was never restarted. This 
characteristic continues with most systems even if the SA_RESTART option is 
specified. But under SVR4, if SA_RESTART was specified, even @select and @poll 
were automatically restarted. To prevent this from catching us when we port 
software to systems derived from SVR4,we'll always use the signal_intr 
function (Figure 10.19) if the signal could interrupt a call to @select or @poll

