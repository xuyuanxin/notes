/*If the file exists and if it is successfully opened for either write-only or
read–write, truncate its length to 0.*/

#define O_APPEND /*Append to the end of file on each write.By default, 
"current file offset" is initialized to 0 when a file is opened, unless the 
O_APPEND option is specified.*/
#define O_CLOEXEC /*Set the FD_CLOEXEC file descriptor flag.*/
#define	O_CREAT  /*Create the file if it doesn’t exist. This option requires a
third argument to the open function (a fourth argument to the openat function)—
the mode,which specifies the access permission bits of the new file.*/
#define O_EXEC	  /* Open for execute only.*/
#define O_EXCL	/*Generate an error if O_CREAT is also specified and the file 
already exists. This test for whether the file already exists and the creation 
of the file if it doesn’t exist is an atomic operation. */
#define	O_NONBLOCK /*If path refers to a FIFO, a block special file, or a character
special file,this option sets the nonblocking mode for both the opening of the file 
and subsequent I/O.*/

#define O_RDONLY  /*Open for reading only.*/
#define O_WRONLY  /*Open for writing only.*/
#define O_RDWR /*Open for reading and writing.Most implementations define 
O_RDONLY as 0,O_WRONLY as 1, and O_RDWR as 2, for compatibility with older programs.*/
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
#include <fcntl.h>
/*******************************************************************************
@path: 要打开或创建文件的名字
@oflag:
@mode: 创建时才会用到
function:打开一个文件(也可用于创建文件)
return: file descriptor if OK,-1 on error

1 open返回的文件描述符一定是最小的未用描述符数值。
2 @path文件名最大字符个数是 NAME_MAX
*******************************************************************************/
int open(const char *path,int oflag,... /* mode_t mode*/ );
int openat(int fd,const char *path,int oflag,... /* mode_tmode*/ );

/*******************************************************************************
Returns: file descriptor opened for write-only if OK,-1 on error

1 Note that this function is equivalent to open(path,O_WRONLY | O_CREAT | O_TRUNC,mode);
2 One deficiency with creat is that the file is opened only for writing. 
*******************************************************************************/
int creat(const char *path,mode_t mode);

#include <unistd.h>
/*******************************************************************************
function: An open file is closed by calling the close function.
Returns : 0 if OK,-1 on error

1 When a process terminates, all of its open files are closed automatically by 
  the kernel.  
*******************************************************************************/
int close(int fd);

#include <unistd.h>
#define SEEK_SET (0)
#define SEEK_CUR (1)
#define SEEK_END (2)
/******************************************************************************
@fd    :
@offset:
@whence:
SEEK_SET(0),the file's offset is set to @offset bytes from the beginning of the file.
SEEK_CUR(1),the file's offset is set to its current value plus the @offset. The @offset can be positive or negative.
SEEK_END(2),the file's offset is set to the size of the file plus the @offset. The @offset can be positive or negative.
function: 打开一个文件并设置其偏移量
returns : new file offset if OK,-1 on error
name    : lseek中的l表示长整型

@lseek only records the current file offset within the kernel—it does not cause
any I/O to take place. This offset is then used by the next read or write operation.
*******************************************************************************/
off_t lseek(int fd,off_t offset,int whence);

#include <unistd.h>
/******************************************************************************
@fd :读哪个文件(已经打开了)
@buf:把读的数据放入这个buf中
@nbytes:希望读取数据的长度

function:Data is read from an open file with the @read function.
Returns: number of bytes read, 0 if end of file,-1 on error

1 参数count是请求读取的字节数，读上来的数据保存在缓冲区buf中，同时文件的当前读
  写位置向后移。
2 读常规文件时，在读到count个字节之前已到达文件末尾。例如，距文件末尾还有30个字
  节而请求读100个字节，则read返回30，下次read将返回0。
3 面向文本的套接字读操作中,一次read不能保证读入完整的一行或整行,读完整的一行可
  能需要对此调用read,并检查其中是否出现了换行符
******************************************************************************/
ssize_t read(int fd,void *buf,size_t nbytes);

/******************************************************************************
@fd    : 写哪个文件(已经打开了)
@buf   : buf中是要写的数据
@nbytes: 写入数据的长度
funtion: Data is written to an open file with the @write function.
Returns: number of bytes written if OK,-1 on error

For a regular file, the write operation starts at the file's current offset. If 
the O_APPEND option was specified when the file was opened, the file's offset 
is set to the current end of file before each write operation. After a successful
write, the file's offset is incremented by the number of bytes actually written.
******************************************************************************/
ssize_t write(int fd,const void *buf,size_t nbytes);

#include <unistd.h>
/******************************************************************************
@fd    ：要读取数据的文件描述符
@buf   ：数据缓存区指针，存放读取出来的数据
@count ：读取数据的字节数
@offset：读取的起始地址的偏移量，读取地址=文件开始+offset。
返回值：成功，返回成功读取数据的字节数；失败，返回-1；

1 执行后，文件偏移指针不变
2 相当于顺序调用lseek和read,但其定位和读取操作是原子的。lseek和read之间如果被中断
  可能造成问题。
******************************************************************************/
ssize_t pread(int fd, void *buf, size_t nbytes, off_t offset);

/*******************************************************************************
@fd    ：要写入数据的文件描述符
@buf   ：数据缓存区指针，存放要写入文件中的数据
@count ：写入文件中的数据的字节数
@offset：写入地址=文件开始+offset
返回值 ：成功，返回写入到文件中的字节数；失败，返回-1；

1 执行后，文件偏移指针不变
2 相当于顺序调用lseek和write,但其定位和读取操作是原子的。lseek和read之间如果被
  中断可能造成问题。
******************************************************************************/
ssize_t pwrite(int fd, const void *buf, size_t nbytes, off_t offset);



#include <unistd.h>
/*******************************************************************************
 返回值:成功返回新的描述符,失败返回-1
 功能:复制文件描述符@fd

 1 @dup返回的新描述符一定是当前可用文件描述符中的最小数值
 2 新描述符与@fd共享一个文件表项(file table entry)
 3 新描述符的执行时关闭(close-on-exec)标志总是由@dup函数清除
******************************************************************************/
int dup(int fd);

/*******************************************************************************
 返回值:成功返回新的描述符,失败返回-1
 功能:复制文件描述符@fd,@fd2是指定的新描述符

 1 如果@fd2已经打开，则先关闭。
 2 如果@fd==@fd2，不关闭@fd2，直接返回@fd2
 3 新描述符与@fd共享一个文件表项(file table entry)
******************************************************************************/
int dup2(int fd,int fd2);
/*
Indeed, the call
dup(fd);
is equivalent to
fcntl(fd, F_DUPFD, 0);
Similarly, the call
dup2(fd, fd2);
is equivalent to
close(fd2);
fcntl(fd, F_DUPFD, fd2);
In this last case, the dup2 is not exactly the same as a close followed by an fcntl.
The differences are as follows:
1. dup2 is an atomic operation, whereas the alternate form involves two function
calls. It is possible in the latter case to have a signal catcher called between the
close and the fcntl that could modify the file descriptors. The same problem could 
occur if a different thread changes the file descriptors. 
2. There are some errno differences between dup2 and fcntl.*/

/******************************************************************************** 
  Traditional implementations of the UNIX System have a buffer cache or page 
cache in the kernel through which most disk I/O passes. When we write data to 
a file, the data is normally copied by the kernel into one of its buffers and 
queued for writing to disk at some later time. This is called delayed write. 
  The kernel eventually writes all the delayed-write blocks to disk, normally 
when it needs to reuse the buffer for some other disk block. To ensure consistency 
of the file system on disk with the contents of the buffer cache, the sync, 
fsync, and fdatasync functions are provided.

  The @sync function simply queues all the modified block buffers for writing and 
returns; it does not wait for the disk writes to take place.
  The function @sync is normally called periodically (usually every 30 seconds) 
from a system daemon, often called update.This guarantees regular flushing of 
the kernel's block buffers. The command sync(1) also calls the sync function.
  The function @fsync refers only to a single file, specified by the file descriptor
@fd, and waits for the disk writes to complete before returning. This function 
is used when an application, such as a database, needs to be sure that the modified 
blocks have been written to the disk.
  The @fdatasync function is similar to @fsync,but it affects only the data portions 
of a file. With @fsync,the file's attributes are also updated synchronously.

  Returns: 0 if OK,-1 on errors
*********************************************************************************/
#include <unistd.h>
int fsync(int fd);
int fdatasync(int fd);
void sync(void);

#define F_DUPFD  /*Duplicate the file descriptor @fd.The new file descriptor is 
returned as the value of the function. It is the lowest-numbered descriptor that 
is not already open, and that is greater than or equal to the third argument. 
The new descriptor shares the same file table entry as @fd. But the new descriptor 
has its own set of file descriptor flags, and its FD_CLOEXEC file descriptor 
flag is cleared. (This means that the descriptor is left open across an exec)*/
#define F_DUPFD_CLOEXEC /*Duplicate the file descriptor and set the FD_CLOEXEC 
file descriptor flag associated with the new descriptor.Returns the new file descriptor.*/
#define F_GETFD  /*Return the file descriptor flags for @fd as the value of the 
function. Currently,only one file descriptor flag is defined: the FD_CLOEXEC flag.*/
#define F_SETFD  /*Set the file descriptor flags for @fd.The new flag value is 
set from the third argument (taken as an integer).*/
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

Unfortunately, the five access-mode flags—O_RDONLY, O_WRONLY,O_RDWR, O_EXEC, 
and O_SEARCH —are not separate bits that can be tested. (As we mentioned 
earlier, the first three often have the values 0, 1,and 2, respectively, for 
historical reasons. Also, these five values are mutually exclusive; a file can 
have only one of them enabled.) Therefore, we must first use the O_ACCMODE mask 
to obtain the access-mode bits and then compare the result against any of the 
five values.*/
#define	O_ACCMODE /*<0003>：读写文件操作时，用于取出flag的低2位*/

#define F_SETFL /*Set the file status flags to the value of the third argument 
(taken as an integer). The only flags that can be changed are O_APPEND, O_NONBLOCK,
O_SYNC, O_DSYNC, O_RSYNC, O_FSYNC, and O_ASYNC.*/
#define F_GETOWN /*Get the process ID or process group ID currently receiving
the SIGIO and SIGURG signals.*/
#define F_SETOWN /*Set the process ID or process group ID to receive the SIGIO 
and SIGURG signals. A positive arg specifies a process ID. A negative arg implies 
a process group ID equal to the absolute value of arg.*/

/*********************************************************************************
function:The @fcntl function can change the properties of a file that is already open.
The @fcntl function is used for five different purposes.
1 Duplicate an existing descriptor (cmd=F_DUPFD or F_DUPFD_CLOEXEC)
2 Get/set file descriptor flags (cmd=F_GETFD or F_SETFD)
3 Get/set file status flags (cmd=F_GETFL or F_SETFL)
4 Get/set asynchronous I/O ownership (cmd=F_GETOWNorF_SETOWN)
5 Get/setrecordlocks (cmd=F_GETLK,F_SETLK,orF_SETLKW)
Returns: depends on cmd if OK (see following),-1 on error

The return value from @fcntl depends on the command. All commands return -1 on 
an error or some other value if OK. The following four commands have special
return values: F_DUPFD, F_GETFD, F_GETFL, and F_GETOWN. The first command returns 
the new file descriptor, the next two return the corresponding flags, and the 
final command returns a positive process ID or a negative process group ID.
**********************************************************************************/
#include <fcntl.h>
int fcntl(int fd,int cmd,... /* int arg */ );

/******************************************************************************\
                                 记录锁
\******************************************************************************/

#define F_RDLCK /*a shared read lock*/
#define F_WRLCK /*an exclusive write lock*/
#define F_UNLCK /*unlocking a region*/


/*******************************************************************************
 The type of lock desired:F_RDLCK(a shared read lock),F_WRLCK(an exclusive write 
 lock), or F_UNLCK(unlocking a region)
 The starting byte offset of the region being locked or unlocked (l_start and
 l_whence)
 The size of the region in bytes (l_len)
 The ID (l_pid) of the  process	holding the lock that can block the current 
 process (returned by F_GETLK only)

 l_start:The two elements that specify the starting offset of the region aresimilar 
         to the last two arguments of the @lseek function.Locks can start and 
         extend beyond the current end of file, but cannot start or extend before 
         the beginning of the file.
 l_len  :If @l_len is 0, it means that the lock extends to the largest possible 
         offset of the file. This allows us to lock a region starting anywhere 
         in the file, up through and including any data that is appended to the 
         file. (We don't have to try to guess how many bytes might be appended 
         to the file.)
 To lock the entire file, we set @l_start and @l_whence to point to the beginning
 of the file and specify a length (l_len) of 0.(There are several ways to specify
 the beginning of the file, but most applications specify @l_start as 0 and
 @l_whence as SEEK_SET.)

 ---->使用规则
  We previously mentioned two types of locks: a shared read lock (l_type of
F_RDLCK) and an exclusive write lock (F_WRLCK). The basic rule is that any number 
of processes can have a shared read lock on a given byte, but only one process 
can have an exclusive write lock on a given byte. Furthermore, if there are one 
or more read locks on a byte, there can't be any write locks on that byte; if 
there is an exclusive write lock on a byte, there can’t be any read locks on 
that byte. 

---->建议性锁和强制性锁 Advisory versus Mandatory Locking
 ******************************************************************************/
struct flock 
{
    short l_type; /* F_RDLCK, F_WRLCK, or F_UNLCK */
    short l_whence; /* SEEK_SET, SEEK_CUR, or SEEK_END */
    off_t l_start; /* offset in bytes, relative to l_whence */
    off_t l_len; /* length, in bytes; 0 means lock to EOF */
    pid_t l_pid; /* returned with F_GETLK */
};

#define F_GETLK /*Determine whether the lock described by @flockptr is blocked
by some other lock. If a lock exists that would prevent ours from being created, 
the information on that existing lock overwrites the information pointed to by
@flockptr.If no lock exists that would prevent ours from being created, the
structure pointed to by @flockptr is left unchanged except for the l_type member,
which is set to F_UNLCK.*/
#define F_SETLK /*Set the lock described by @flockptr.If we are trying to obtain
a read lock(l_typeof F_RDLCK) or a write lock (l_typeof F_WRLCK) and the 
compatibility rule prevents the system from giving us the lock , @fcntl returns 
immediately with errno set to either EACCES or EAGAIN. This command is also used 
to clear the lock described by @flockptr(l_typeof F_UNLCK).*/
#define F_SETLKW /*This command is a blocking version of F_SETLK.(The W in the 
command name means wait.) If the requested read lock or write lock cannot be 
granted because another process currently has some part of the requested region  
locked, the calling process is put to sleep.The process wakes up either when the 
lock becomes available or when interrupted by a signal.*/

/*******************************************************************************
 @cmd: F_GETLK, F_SETLK,or F_SETLKW.
 ******************************************************************************/
int fcntl(int fd,int cmd,struct flock *flockptr);

/*******************************************************************************
锁的继承与释放
1 when a process terminates, all its locks are released. whenever a descriptor is 
  closed, any locks on the file referenced by that descriptor for that process are 
  released. This means that if we make the calls
		fd1 = open(pathname, ...);
		read_lock(fd1, ...);
		fd2 = dup(fd1);
		close(fd2);
  after the close(fd2),the lock that was obtained on fd1 is released. The same 
  thing would happen if we replaced the dup with open, as in
		fd1 = open(pathname, ...);
		read_lock(fd1, ...);
		fd2 = open(pathname, ...)
		close(fd2);
  to open the same file on another descriptor.
 
2 Locks are never inherited by the child across a fork.This means that if a process
  obtains a lock and then calls fork,the child is considered another process with
  regard to the lock that was obtained by the parent. The child has to call @fcntl 
  to obtain its own locks on any descriptors that were inherited across the fork.
  This constraint makes sense because locks are meant to prevent multiple processes 
  from writing to the same file at the same time. If the child inherited locks 
  across a fork, both the parent and the child could write to the same file at 
  the same time.
3 Locks are inherited by a new program across an exec.Note, however,that if the
  close-on-exec flag is set for a file descriptor,all locks for the underlying 
  file are released when the descriptor is closed as part of an exec.
 ******************************************************************************/



#include <sys/select.h>
#include <sys/time.h>

struct timeval	
{
  long	 tv_sec;  /* seconds */
  long	 tv_usec; /* microseconds */
};

/*
@maxfdp1: 描述符个数+1
@readset: 读描述符集，可以为NULL
@readset: 写描述符集，可以为NULL
@readset: 异常描述符集，可以为NULL
@timeout: 等待时间
function: 
告诉内核
1 关心的描述符
2 关心描述符的哪些状态，比如是否可读、是否可写、描述符的异常状态
3 等待时间
从select返回内核告诉我们
1 已经准备好的描述符数量
2 对于读、写或异常这三个状态中的每一个，哪些描述符已经准备好。
  使用这些返回信息就可以调用相应的I/O函数，并确切知道函数不会阻塞
Returns: positive count of ready descriptors, 0 on timeout, –1 on error
Ther eare three possible return values from @select.
1 return -1 means that an error occurred. This can happen, for example, if a signal is caught before any of the specified descriptors are ready.
  In this case, none of the descriptor sets will be modified.
2 return 0 means that no descriptors are ready.This happens if the time limit expires before any of the descriptors are ready.When this happens,
  all the descriptor sets will be zeroed out.
3 A positive return value specifies the number of descriptors that are ready.This value is the sum of the descriptors ready in all three sets, so 
  if the same descriptor is ready to be read and written, it will be counted twice in the return value. The only bits left on in the three descriptor  
  sets are the bits corresponding to the descriptors that are ready.
---->等待的时间
1 永远等待  timeout == NULL
2 等待指定的时间 具体的时间由timeout指定
3 不等待  timeout中的时间为0
The wait in the first two scenarios is normally interrupted if the process catches a signal and returns from the signal handler.
---->准备好
1 对于读描述符集中的一个描述符的read操作将不会阻塞，则此描述符是准备好的
2 对于写描述符集中的一个描述符的write操作将不会阻塞，则此描述符是准备好的
3 若异常描述符集中的一个描述符有一个未决异常状态，则此描述符是准备好的。异常状态包括
  a 在网络连接上到达的带外数据
  b 处于数据包模式的伪终端上发生了某些状态。
4 File descriptors for regular files always return ready for reading, writing, and exception conditions.
*/
int select(int maxfdp1, fd_set *readset, fd_set *writeset, fd_set *exceptset, const struct timeval *timeout);

 
#include <sys/select.h>
int FD_ISSET(int fd,fd_set *fdset);
void FD_CLR(int fd,fd_set *fdset);
void FD_SET(int fd,fd_set *fdset);
void FD_ZERO(fd_set *fdset); 
/*
After declaring a descriptor set, we must zerothe set usingFD_ZERO.Wethen set
bits in the set for each descriptor that we’reinterested in, as in
fd_set  rset;
int  fd;
FD_ZERO(&rset);
FD_SET(fd, &rset);
FD_SET(STDIN_FILENO, &rset);
On return from @select, we can test whether a given bit in the set is still on using @FD_ISSET:
if (FD_ISSET(fd, &rset)) {
.
}

*/

#include <sys/select.h>
#include <signal.h>
#include <time.h>
 
struct timespec {
  time_t tv_sec;       /* seconds */
  long   tv_nsec;      /* nanoseconds */
};


/*
When @pselect is called, it replaces the signal mask of the process with an @sigmask set (i.e., zeromask) and then checks 
the descriptors, possibly going to sleep. But when @pselect returns, the signal mask of the process is reset to its value 
before pselect was called (i.e., SIGINT is blocked).

Returns: count of ready descriptors, 0 on timeout,-1 on error*/
int pselect(int maxfdp1,fd_set *restrict readfds,fd_set *restrict writefds,fd_set *restrict exceptfds,
             const struct timespec *restrict tsptr,const sigset_t *restrict sigmask);




#include <poll.h>
#define POLLIN       /*普通或优先级带数据可读*/
#define POLLRDNORM   /*普通数据可读*/
#define POLLRDBAND   /*优先级带数据可读*/
#define POLLPRI      /*高优先级数据可读*/
#define POLLOUT      /*普通数据可写*/
#define POLLWRNORM   /*普通数据可写*/
#define POLLWRBAND   /*优先级带数据可写*/
#define POLLERR      /*发生错误*/
#define POLLHUP      /*发生挂起*/
#define POLLNVAL     /*描述字不是一个打开的文件*/

#define INFTIM       /*是一个负值 poll的第三个参数,表示永远等待*/

struct pollfd 
{
    int  fd; /* file descriptor to check, or <0 to ignore */
    short  events; /* events of interest on fd */
    short  revents;  /* events that occurred on fd */
};

/*
@fdarray: 每个数组元素指定一个描述符编号以及对其所关心的状态。
@nfds:数组元素的个数
@timeout: INFTIM永远等待 0不等待 大于0等待指定的时间
Returns: count of ready descriptors, 0 on timeout,-1 on error*/
int poll(struct pollfd fdarray[], nfds_t nfds,int timeout);


#include <sys/mman.h>
#define PROT_READ   /*Region can be read.*/
#define PROT_WRITE  /*Region can be written.*/
#define PROT_EXEC   /*Region can be executed.*/
#define PROT_NONE   /*Region cannot be accessed.*/
#define MAP_FIXED   /*返回值必须等于@addr*/
#define MAP_SHARED	/*存储操作相当于对该文件的write.MAP_SHARED和MAP_PRIVATE必须指定一个，但不能同时指定。*/
#define MAP_PRIVATE /*对映射区的存储操作导致创建该映射文件的一个私有副本。*/

/*
@addr:映射存储区的起始地址,0表示让系统自动选择。页边界对齐
@len: 映射的字节数
@prot:映射区的保护要求(按位或)
      PROT_READ Region can be read.
      PROT_WRITE Region can be written.
      PROT_EXEC Region can be executed.
      PROT_NONE Region cannot be accessed.
@flag:映射存储区的属性
      MAP_FIXED   返回值必须等于@addr
      MAP_SHARED  存储操作相当于对该文件的write.MAP_SHARED和MAP_PRIVATE必须指定一个，但不能同时指定。
      MAP_PRIVATE 对映射区的存储操作导致创建该映射文件的一个私有副本。
@fd:  被映射文件的描述符,映射文件前要打开该文件
@off: 要映射字节在文件中的起始偏移量
Returns: starting address of mapped region if OK,MAP_FAILED on error*/
void *mmap(void *addr,size_t len,int prot,int flag,int fd,off_t off);





#include <sys/mman.h>
/*
function:We can change the permissions on an existing mapping by calling @mprotect
Returns: 0 if OK,-1 on error*/
int mprotect(void *addr,size_t len,int prot);



#include <sys/mman.h>
/*
flags: MS_ASYNC       MS_ASYNC和MS_SYNC必须指定一个
       MS_SYNC        等待冲洗完成
       MS_INVALIDATE
function:修改冲洗到文件中。
Returns: 0 if OK,-1 on error*/
int msync(void *addr,size_t len,int flags);


#include <sys/mman.h>
/*
function:解除映射
Returns: 0 if OK,-1 on error

Amemory-mapped region is automatically unmapped when the process terminates
or  we  can  unmap  a  region  directly  by  calling  themunmapfunction.  Closing the  file
descriptor used when we mapped the region does not unmap the region.
Themunmapfunction  does  not  affect  the  object  that  was  mapped—that  is,  the  call  to
munmapdoes not cause the contents of the mapped region to be written to the disk file.
The updating of the disk file for aMAP_SHAREDregion happens automatically by the
kernel’s virtual memory algorithm sometime after we storeinto the memory-mapped
region.  Modifications to  memory  in  aMAP_PRIVATEregion  arediscarded  when  the
region is unmapped.*/
int munmap(void *addr,size_t len);



include <sys/socket.h>
	/*return: number of bytes read or written if OK, –1 on error */
 
ssize_t recv(int sockfd, void *buff, size_t nbytes, int flags);
 
/*return: number of bytes read or written if OK, –1 on error */
ssize_t send(int sockfd, const void *buff, size_t nbytes, int flags);
 

#include <sys/uio.h>
struct iovec {
  void   *iov_base;   /* starting address of buffer */
  size_t  iov_len;    /* size of buffer */
};

/* return: number of bytes read or written, –1 on error */ 
ssize_t readv(int filedes, const struct iovec *iov, int iovcnt);

/*@iov:结构体数组指针
  return: number of bytes read or written, –1 on error */
ssize_t writev(int filedes, const struct iovec *iov, int iovcnt);
 
 
#include <sys/socket.h>
struct msghdr {
void		 *msg_name; 	   /* protocol address */
socklen_t	  msg_namelen;	   /* size of protocol address */
struct iovec *msg_iov;		   /* scatter/gather array */
int 		  msg_iovlen;	   /* # elements in msg_iov */
void		 *msg_control;	   /* ancillary data (cmsghdr struct) */
socklen_t	  msg_controllen;  /* length of ancillary data */
int 		  msg_flags;	   /* flags returned by recvmsg() */
};

  /*Both return: number of bytes read or written if OK, –1 on error */
 ssize_t recvmsg(int sockfd, struct msghdr *msg, int flags);

/*return: number of bytes read or written if OK, –1 on error */  
ssize_t sendmsg(int sockfd, struct msghdr *msg, int flags);
 

/*




*/

