struct iovec {
  void   *iov_base;   /* starting address of buffer */
  size_t  iov_len;    /* size of buffer */
};

#define IOV_MAX  /* 1024 */


/*
FD_CLOEXEC
    It sets the close-on-exec flag for the file descriptor, which causes the file de-
    scriptor to be automatically (and atomically ) closed when any of the exec-family 
    functions succeed.

*/
#define FD_CLOEXEC


/*-------------------------------- @fcntl @cmd --------------------------------------
 F_DUPFD
    Duplicate the file descriptor @fd. The new file descriptor is returned as the va-
    lue of the function. It is the lowest-numbered descriptor that is not already op-
    en, and that is greater than or equal to the third argument. The new descriptor -
    shares the same file table entry as @fd. But the new descriptor has its own set -
    of file descriptor flags, and its FD_CLOEXEC file descriptor flag is cleared. (T-
    his means that the descriptor is left open across an @exec)
 F_DUPFD_CLOEXEC  
    Duplicate the file descriptor and set the FD_CLOEXEC file descriptor flag associ-
    ated with the new descriptor. Returns the new file descriptor.
 F_GETFD 
    Return the file descriptor flags for @fd as the value of the function. Currently,
    only one file descriptor flag is defined: the FD_CLOEXEC flag.
 F_SETFD 
    Set the file descriptor flags for @fd. The new flag value is set from the third -
    argument (taken as an integer).
 F_GETOWN
    Get the process ID or process group ID currently receiving the  SIGIO and  SIGURG 
    signals.
 F_SETOWN
    Set the process ID or process group ID to receive the SIGIO and SIGURG signals. A 
    positive arg specifies a  process ID. A  negative arg implies a process  group ID 
    equal to the absolute value of arg.
**---------------------------------------------------------------------------------*/
#define F_DUPFD  /**/
#define F_DUPFD_CLOEXEC /**/
#define F_GETFD  /**/
#define F_SETFD  /**/

#define F_GETOWN 
#define F_SETOWN
#define F_SETFL /* Set the file status flags to the value of the third argument(taken 
as an integer). The only flags that can be changed are O_APPEND, O_NONBLOCK,O_SYNC, 
O_DSYNC, O_RSYNC, O_FSYNC, and O_ASYNC.*/
#define F_GETFL /*Return the file status flags for fd as the value of the function. 
			File status flag    Description
			O_RDONLY            open for reading only
			O_WRONLY            open for writing only
			O_RDWR              open for reading and writing
			O_EXEC              open for execute only
			O_SEARCH            open directory for searching only
			O_APPEND            append on each write
			O_NONBLOCK          nonblocking mode
			O_SYNC              wait for writes to complete (data and attributes)
			O_DSYNC             wait for writes to complete (data only)
			O_RSYNC             synchronize reads and writes
			O_FSYNC             wait for writes to complete (FreeBSD and Mac OS X only)
			O_ASYNC             asynchronous I/O (FreeBSD and Mac OS X only)
Unfortunately,the five access-mode flags(O_RDONLY,O_WRONLY,O_RDWR,O_EXEC,and O_SEARCH) 
are not separate bits that can be tested. ( the first three often have the values 0, 1,
and 2,respectively,for historical reasons.Also,these five values are mutually exclusive; 
a file can have only one of them enabled.) Therefore,we must first use the O_ACCMODE mask 
to obtain the access-mode bits and then compare the result against any of the five values.*/

#define	O_ACCMODE /*<0003>：读写文件操作时，用于取出flag的低2位*/





/*If the file exists and if it is successfully opened for either write-only or
read–write, truncate its length to 0.*/

/************************************************************************************
           File status flags used for open() and fcntl() are as follows:
*************************************************************************************
 O_RDONLY
    Open for reading only
 O_WRONLY
    Open for writing only
 O_RDWR
    Most implementations define O_RDONLY as 0, O_WRONLY as 1, and O_RDWR as 2, for 
    compatibility with older programs.
 O_EXEC
    Open for execute only.
 O_EXCL  
    Generate an error if O_CREAT is also specified and the file already exists. This 
    test for whether the file already exists and the creation of the file if it doe-
    sn't exist is an atomic operation. 
 O_SEARCH
    One and only one of the previous five constants must be specified. The following
    constants are optional:
 O_CREAT  
    Create the file if it doesn't exist. This option requires a third argument to the 
    open function (a fourth argument to the openat function)— the mode,which specifies 
    the access permission bits of the new file.
 O_NONBLOCK
    If path refers to a FIFO, a block special file, or a character special file,this 
    option sets the nonblocking mode for both the opening of the file and subsequent 
    I/O.
************************************************************************************/
#define O_RDONLY  0
#define O_WRONLY  1 
#define O_RDWR    2

#define O_APPEND /*Append to the end of file on each write.By default, 
"current file offset" is initialized to 0 when a file is opened, unless the 
O_APPEND option is specified.*/
#define O_CLOEXEC /*Set the FD_CLOEXEC file descriptor flag.*/
#define	O_CREAT  
#define O_EXEC	  /* Open for execute only.*/
#define O_EXCL
#define	O_NONBLOCK 

#define O_SEARCH  /*Open for search only (applies to directories).*/
#define	O_TRUNC /*If the file exists and if it is successfully opened for 
either write-only or read–write, truncate its length to 0.*/

/*
The purpose of theO_SEARCHconstant is to evaluate search permissions at the time
adirectory	is	opened. Further  operations  using	the  directory’s  file  descriptor  will
not  reevaluate  permission  to  search  the  directory.None  of  the  versions  of  the
operating systems covered in this book supportO_SEARCHyet.
One  and  only	one  of  the  previous	five  constants  must  be  specified. The  following
constants areoptional:
	 
O_DIRECTORYGenerate an error ifpathdoesn’t refer to a directory.
	
O_NOCTTY If pathrefers	to	a  terminal  device,  do  not  allocate  the  device  as  the
controlling  terminal  for	this  process.	Wetalk	about  controlling
terminals in Section 9.6.
O_NOFOLLOW Generate an error ifpathrefers to a symbolic link. We  discuss symbolic
links in Section 4.17.


In earlier releases of System V,theO_NDELAY(no delay) flag was introduced.	This
option	is	similar  to  theO_NONBLOCK(nonblocking)  option,  but  an  ambiguity  was
introduced in the return value from a read operation. The no-delay option causes a
read operation to return 0 if there is no data to be read from a pipe, FIFO, or device,
but  this  conflicts  with	a  return  value  of  0,  indicating  an  end  of  file. SVR4-based
systems  still	support  the  no-delay	option,  with  the	old  semantics,  but  new
applications should use the nonblocking option instead.

O_SYNC Have  eachwritewait	for  physical  I/O	to	complete,  including  I/O
necessary  to  update  file  attributes  modified  as  a  result  of  thewrite.
We	use this option in Section 3.14.


O_TTY_INIT When  opening  a  terminal  device  that  is  not  already  open,  set  the
nonstandardtermiosparameters to values that result in behavior that
conforms  to  the  Single  UNIX  Specification. We	discuss  the termios
structurewhen we discuss terminal I/O in Chapter 18.
The following two flags arealso optional. They arepart of the synchronized input and
output option of the Single UNIX Specification (and thus POSIX.1).
O_DSYNC Have eachwritewait for physical I/O to complete, but don’t wait for
file attributes to be updated if they don’t affect the ability to read the
data just written.
TheO_DSYNCandO_SYNCflags aresimilar,but subtly different.  TheO_DSYNCflag
affects a file’s attributes only when they need to be updated to reflect a change in the
file’s data (for example, update the file’s size to reflect moredata).  With theO_SYNC
flag, data and attributes arealways updated synchronously.When overwriting an
existing  part	of	a  file  opened  with  theO_DSYNCflag,	the  file  times  wouldn’t  be
updated synchronously.Incontrast, if we had opened the file with theO_SYNCflag,
everywriteto  the  file  would	update	the  file’s  times  beforethewritereturns,
regardless of whether we werewriting over existing bytes or appending to the file.
O_RSYNC Have eachreadoperation on the file descriptor wait until any pending
writes for the same portion of the file arecomplete.
Solaris 10 supports all three synchronization flags. Historically,FreeBSD (and thus
Mac OS X) have used theO_FSYNCflag, which has the same behavior asO_SYNC.
Because the two flags areequivalent, they define the flags to have the same value.
FreeBSD  8.0  doesn’t	support  theO_DSYNCorO_RSYNCflags.	Mac OS	X  doesn’t
support theO_RSYNCflag, but defines theO_DSYNCflag, treating it the same as the
O_SYNCflag.  Linux 3.2.0  supports	theO_DSYNCflag,  but  treats  theO_RSYNCflag
the same asO_SYNC
*/

/*---->文件描述符
A file descriptor is a non-negative integer. To the kernel, all open files are 
referred to by file descriptors. 
file descriptor 0 STDIN_FILENO  with the standard input of a process, 
file descriptor 1 STDOUT_FILENO with the standard output 
file descriptor 2 STDERR_FILENO with the standard error.*/
#define STDIN_FILENO   0
#define STDOUT_FILENO  1
#define STDERR_FILENO  2


#include <sys/epoll.h> 
/********************************* @epoll_create1 @flags ****************************
EPOLL_CLOEXEC
   Set the close-on-exec (FD_CLOEXEC) flag on the new file descrip-tor. See the desc-
   ription of the O_CLOEXEC flag in  open(2)  for reasons why this may be useful.
*/
#define EPOLL_CLOEXEC

/********************************* @epoll_ctl @op **********************************
EPOLL_CTL_ADD
    Add the file descriptor @fd to the interest list for @epfd. The set of events th-
    at we are interested in monitoring for @fd  is specified in the buffer pointed to
    by @ev, as described below.If we attempt to add a file descriptor that is already 
    in the interest list, epoll_ctl() fails with the error EEXIST.
EPOLL_CTL_MOD
    Modify the events setting for the file descriptor @fd, using the information spe-
    cified in the buffer pointed to by @ev. If we attempt to modify the settings of -
    a file descriptor that is not in the interest list for @epfd, epoll_ctl() fails -
    with the error ENOENT.
EPOLL_CTL_DEL
    Remove the file descriptor @fd from the interest list for @epfd. The @ev argument 
    is ignored for this operation. If  we attempt to remove a file descriptor that is 
    not in the interest list for @epfd, epoll_ctl() fails with the error ENOENT. Clo-
    sing a file descriptor automatically removes it from all of the epoll interest l-
    ists of which it is a member.
*/
#define EPOLL_CTL_ADD    //注册新的fd到epfd中；
#define EPOLL_CTL_MOD    //修改已经注册的fd的监听事件；
#define EPOLL_CTL_DEL    //从epfd中删除一个fd；

typedef union epoll_data
{
  void        *ptr;
  int          fd;
  __uint32_t   u32;
  __uint64_t   u64;
} epoll_data_t;

/*
@events
    The @events subfield is a bit mask specifying the set of events that we are inte-
    rested in monitoring for @fd.
    The bit values that can be specified in ev.events when we call epoll_ctl() and t-
    hat are placed in the evlist[].events fields returned by epoll_wait(). 
    
 EPOLLIN 
	表示对应的文件描述符可以读（包括对端SOCKET正常关闭）；当对方关闭连接(FIN), 
	EPOLLERR，都可以认为是一种EPOLLIN事件，在read的时候分别有0，-1两个返回值。
 EPOLLOUT	 
	表示对应的文件描述符可以写；
 EPOLLPRI	 
	表示对应的文件描述符有紧急的数据可读（这里应该表示有带外数据到来）；
 EPOLLERR	 
	表示对应的文件描述符发生错误；
 EPOLLHUP	 
	表示对应的文件描述符被挂断；
 EPOLLET	 
	将EPOLL设为边缘触发(Edge Triggered)模式，这是相对于水平触发(Level Triggered)来说的。
EPOLLONESHOT
    By default, once a file descriptor is added to an epoll interest list using the -
    epoll_ctl() EPOLL_CTL_ADD operation, it remains active (i.e., subsequent calls to 
    epoll_wait() will inform us whenever the file descriptor is ready) until we expl-
    icitly remove  it from the list using the epoll_ctl() EPOLL_CTL_DEL operation. If 
    we want to be notified only once about a particular file descriptor, then  we can 
    specify the EPOLLONESHOT flag(available since Linux 2.6.2) in the ev.events value 
    passed in epoll_ctl(). If this flag is specified, then, after the next epoll_wait() 
    call that informs us that the corresponding file descriptor is ready, the file d-
    escriptor is marked inactive in the interest list, and we won't be informed about 
    its state by future epoll_wait() calls. If  desired, we can subsequently reenable 
    monitoring of this file descriptor using the epoll_ctl() EPOLL_CTL_MOD operation. 
    ( We can't use the EPOLL_CTL_ADD operation for this purpose, because the inactive 
    file descriptor is still part of the epoll interest list.)
@data    
    The @data subfield is a union, one of whose members can be used to specify infor-
    mation that is passed back to the calling process (via epoll_wait()) if @fd later
    becomes ready.
*/
#define EPOLLIN
#define EPOLLOUT 
#define EPOLLPRI 
#define EPOLLERR
#define EPOLLHUP
#define EPOLLET 
#define EPOLLONESHOT

struct epoll_event {
    __uint32_t events; /* Epoll events */
    epoll_data_t data; /* User data variable */
};






/********************************* @ioctl @requst ***********************************
 ----> Socket operations
 SIOCATMARK (int)
    是否位于带外标记
 SIOCSPGRP  (int)
    设置套接口的进程ID 或进程组ID
 SIOCGPGRP  (int)
    获取套接口的进程ID 或进程组ID
 ----> File operations
 FIONBIO (int)
    设置/ 清除非阻塞I/O 标志
 FIOASYNC (int)
    设置/ 清除信号驱动异步I/O 标志
 FIONREAD (int)
    获取接收缓存区中的字节数
 FIOSETOWN (int)
    设置文件的进程ID 或进程组ID
 FIOGETOWN (int)
    获取文件的进程ID 或进程组ID

*/
#define SIOCATMARK
#define SIOCSPGRP
#define SIOCGPGRP

#define FIONBIO
#define FIOASYNC
#define FIONREAD
#define FIOSETOWN
#define FIOGETOWN

/*
接
口
SIOCGIFCONF
SIOCSIFADDR
SIOCGIFADDR
SIOCSIFFLAGS
SIOCGIFFLAGS
SIOCSIFDSTADDR
SIOCGIFDSTADDR
SIOCGIFBRDADDR
SIOCSIFBRDADDR
SIOCGIFNETMASK
SIOCSIFNETMASK
SIOCGIFMETRIC
SIOCSIFMETRIC
SIOCGIFMTU
SIOCxxx
获取所有接口的清单
设置接口地址
获取接口地址
设置接口标志
获取接口标志
设置点到点地址
获取点到点地址
获取广播地址
设置广播地址
获取子网掩码
设置子网掩码
获取接口的测度
设置接口的测度
获取接口MTU
（还有很多取决于系统的实现）
struct ifconf
struct ifreq
struct ifreq
struct ifreq
struct ifreq
struct ifreq
struct ifreq
struct ifreq
struct ifreq
struct ifreq
struct ifreq
struct ifreq
struct ifreq
struct ifreq
ARP
SIOCSARP
SIOCGARP
SIOCDARP
创建/ 修改ARP 表项
获取ARP 表项
删除ARP 表项
struct arpreq
struct arpreq
struct arpreq
路
由
SIOCADDRT
SIOCDELRT
增加路径
删除路径
struct rtentry
struct rtentry
流
I_xxx
　　	　　

*/




/*
---->不带缓冲I/O unbuffered I/O
与标准I/O相对照,术语不带缓冲指每个read和write都调用内核中的一个系统调用.
这些不带缓冲的I/O不是ISO C的组成部分,但它们是POSIX.1的组成部分.



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

