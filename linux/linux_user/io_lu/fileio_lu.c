
#include <fcntl.h>
/*-----------------------------------------------------------------------------------
 @path: 
     the name of the file to open or create. NAME_MAX
 @oflag: 
     this function has a multitude of options, which are specified by the @oflag arg-
     ument. This argument is formed by ORing together one or more of the following c-
     onstants from the <fcntl.h> header. O_RDONLY
 @...: 
     the last argument is used only when a new file is being created. S_IEXEC
 @function: 
     A file is opened or created by calling either the @open function or the openat -
     function.
 @return: 
     file descriptor if OK, -1 on error. The file descriptor returned by @open and  -
     @openat is guaranteed to be the lowestnumbered unused descriptor.  
 ----------------------------------------------------------------------------------*/
int open(const char *path, int oflag, ... /* mode_t mode*/ );
int openat(int fd,const char *path,int oflag,... /* mode_tmode*/ );

/*-----------------------------------------------------------------------------------
 @func:
     A new file can also be created by calling the creat function.
 @returns: 
     file descriptor opened for write-only if OK, -1 on error.

 1 this function is equivalent to 
     open(path,O_WRONLY | O_CREAT | O_TRUNC, mode);
 2 One deficiency with creat is that the file is opened only for writing. Before  the
   new version of open was provided, if we were creating a temporary file that we wa-
   nted to write and then read back, we had to call creat, close, and then open. A b-
   etter way is to use the open function, as in
     open(path, O_RDWR | O_CREAT | O_TRUNC, mode);
 ----------------------------------------------------------------------------------*/
int creat(const char *path,mode_t mode);

#include <unistd.h>
/*-----------------------------------------------------------------------------------
 @function: 
     An open file is closed by calling the close function.
 @returns : 
     0 if OK, -1 on error.

 1 When a process terminates, all of its open files are closed automatically by the -
   kernel.  
 ----------------------------------------------------------------------------------*/
int close(int fd);

/*-----------------------------------------------------------------------------------
 @fd 
 @offset @whence
     The interpretation of the offset depends on the value of the whence argument. If 
     @whence is SEEK_SET,the file's offset is set to @offset bytes from the beginning 
     of the file. If @whence is SEEK_CUR, the file's @offset is set to its current v-
     alue plus the offset. The @offset can be positive or negative. If @whence is   -
     SEEK_END, the file's offset is set to the size of the file plus the @offset. The 
     offset can be positive or negative.
 @function: 
     An open file's offset can be set explicitly by calling lseek.
 @returns : 
     new file offset if OK,-1 on error
 name    : lseek中的l表示长整型

 @lseek only records the current file offset within the kernel, it does not cause an-
 y I/O to take place. This offset is then used by the next read or write operation. -
 Because a successful call to @lseek returns the new file offset, we can seek zero b-
 ytes from the current position to determine the current offset:
     off_t currpos;
     currpos = lseek(fd, 0, SEEK_CUR);
 This technique can also be used to determine if a file is capable of seeking. If th-
 e file descriptor refers to a pipe, FIFO, or socket, lseek sets errno to ESPIPE  and 
 returns -1.

 Every open file has an associated "current file offset", normally a non-negative in-
 teger that measures the number of bytes from the beginning of the file. Read and wr-
 ite operations normally start at the current file offset and cause the offset to  be 
 incremented by the number of bytes read or written. By default, this offset is init-
 ialized to 0 when a file is opened, unless the O_APPEND option is specified.
 -----------------------------------------------------------------------------------*/
off_t lseek(int fd,off_t offset,int whence);

/*-----------------------------------------------------------------------------------
 @fd :
     The read() reads data from the open file referred to by the descriptor @fd.
 @buf:
     The @buf argument supplies the address of the memory buffer into which the input 
     data is to be placed. This buffer must be at least @nbytes bytes long.
 @nbytes:
     The @nbytes argument specifies the maximum number of bytes to read.
 @func
     Data is read from an open file with the read function.
 @returns: 
    If the read is successful, the number of bytes read is returned. If the end of f-
    ile is encountered, 0 is returned, -1 on error.

 The read operation starts at the file's current offset. Before a successful  return, 
 the offset is incremented by the number of bytes actually read.

 There are several cases in which the number of bytes actually read is less than  the
 amount requested:
 1 When reading from a regular file, if the end of file is reached before the reques-
   ted number of bytes has been read. For example, if 30 bytes remain until the end -
   of file and we try to read 100 bytes, read returns 30. The next time we call read, 
   it will return 0 (end of file).
 2 When reading from a terminal device. Normally, up to one line is read at a time.
 3 When reading from a network. Buffering within the network may cause less than  the 
   requested amount to be returned.
 4 When reading from a pipe or FIFO. If the pipe contains fewer bytes than requested, 
   read will return only what is available. 
 5 When reading from a record-oriented device. Some record-oriented devices, such  as 
   magnetic tape, can return up to a single record at a time.  
 6 When interrupted by a signal and a partial amount of data has already been read.
   
 a 服务器收到FIN时,递送一个EOF给进程阻塞中的read,收到后read返回EOF
 b POSIX.1 requires that read return -1 with errno set to EAGAIN if there is no 
   data to read from a nonblocking descriptor. 
 ----------------------------------------------------------------------------------*/
ssize_t read(int fd,void *buf,size_t nbytes);

/*----------------------------------------------------------------------------------
 @fd:
     @fd is a file descriptor referring to the file to which data is to be written.
 @buf   : 
     @buf is the address of the data to be written; 
 @nbytes: 
     @nbytes is the number of bytes to write from @buf;
 @funtion: 
     Data is written to an open file with the @write function.
 @returns: 
     On success, write() returns the number of bytes actually written; this may be l-
     ess than @nbytes. The return value is usually equal to the @nbytes argument; ot-
     herwise, an error has occurred. A common cause for a write error is either fill-
     ing up a disk or exceeding the file size limit for a given process.

 For a regular file, the write operation starts at the file's current offset. If  the 
 O_APPEND option was specified when the file was opened, the file's offset is set  to 
 the current end of file before each write operation. After a successful write, the -
 file's offset is incremented by the number of bytes actually written.

 It is okay to write to a socket that has received a FIN, but it is an error to write 
 to a socket that has received an RST.

 What happens if the client ignores the error return from read and writes more data -
 to the server? This can happen, for example, if the client needs to perform two wri-
 tes to the server before reading anything back, with the first write eliciting the -
 RST.
 
 When a process writes to a socket that has received an RST, the SIGPIPE signal is s-
 ent to the process. The default action of this signal is to terminate the process, -
 so the process must catch the signal to avoid being involuntarily terminated. If the 
 process either catches the signal and returns from the signal handler, or ignores t-
 he signal, the write operation returns EPIPE.
 ----------------------------------------------------------------------------------*/
ssize_t write(int fd, const void *buf, size_t nbytes);

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

/*
 dup和dup2也是两个非常有用的调用，它们的作用都是用来复制一个文件的描述符。它们经常用来
 重定向进程的stdin、stdout和stderr。

*/
/************************************************************************************
 返回值:
    成功返回新的描述符,失败返回-1
 功能:
    复制文件描述符@fd。给该函数一个既有的描述符，它就会返回一个新的描述符，这个新的描
    述符是传给它的描述符的拷贝。这意味着，这两个描述符共享同一个"文件表"。

 1 @dup返回的新描述符一定是当前可用文件描述符中的最小数值
 2 新描述符与@fd共享一个文件表项(file table entry)
 3 新描述符的执行时关闭(close-on-exec)标志总是由@dup函数清除
************************************************************************************/
int dup(int fd);

/************************************************************************************
 返回值:
    成功返回新的描述符,失败返回-1
 功能:
    复制文件描述符@fd,@fd2是指定的新描述符.dup2函数跟dup函数相似，但dup2函数允许调用
    者规定一个有效描述符和目标描述符的id。dup2函数成功返回时，目标描述符（dup2函数的
    第二个参数）将变成源描述符（dup2函数的第一个参数）的复制品，换句话说，两个文件描
    述符现在都指向同一个文件，并且是函数第一个参数指向的文件。

 1 如果@fd2已经打开，则先关闭。
 2 如果@fd==@fd2，不关闭@fd2，直接返回@fd2
 3 新描述符与@fd共享一个文件表项(file table entry)
************************************************************************************/
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
int fsync(int fd);
int fdatasync(int fd);
void sync(void);

/*-----------------------------------------------------------------------------------
 @cmd: F_SETFL
    The @fcntl function is used for five different purposes.
    1 Duplicate an existing descriptor (cmd=F_DUPFD or F_DUPFD_CLOEXEC)
    2 Get/set file descriptor flags (cmd=F_GETFD or F_SETFD)
    3 Get/set file status flags (cmd=F_GETFL or F_SETFL)
    4 Get/set asynchronous I/O ownership (cmd=F_GETOWN or F_SETOWN)
    5 Get/setrecordlocks (cmd=F_GETLK,F_SETLK,or F_SETLKW)
 @fun:
   The @fcntl function can change the properties of a file that is already open.
@ret: 
   depends on @cmd if OK (see following),-1 on error
   The return value from @fcntl depends on the command. All commands return -1 on 
   an error or some other value if OK. The following four commands have special
   return values: F_DUPFD, F_GETFD, F_GETFL, and F_GETOWN. The first command returns 
   the new file descriptor, the next two return the corresponding flags, and the 
   final command returns a positive process ID or a negative process group ID.
-----------------------------------------------------------------------------------*/
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

/*-----------------------------------------------------------------------------------
 @maxfdp1: FD_SETSIZE
     The @maxfdp1 argument specifies the number of descriptors to be tested. Its val-
     ue is the maximum descriptor to be tested plus one (hence our name of maxfdp1).
 @readset @readset @exceptset
     The three arguments, readset, writeset, and exceptset, specify the descriptors -
     that we want the kernel to test for reading, writing, and exception  conditions.
     three arguments can be specified as a null pointer if we are not interested in -
     that condition. Indeed, if all three pointers are null, then we have a higher p-
     recision timer than the normal Unix @sleep function ( which sleeps for multiples 
     of a second). 
 @timeout: 
     tells the kernel how long to wait for one of the specified descriptors to becom-
     e ready. There are three possibilities: 1 Wait forever--Return only when one  of 
     the specified descriptors is ready for I/O. For this, we specify the timeout ar-
     gument as a null pointer. 2 Wait up to a fixed amount of time--Return when one -
     of the specified descriptors is ready for I/O, but do not wait beyond the number 
     of seconds and microseconds specified in the timeval structure pointed to by the 
     timeout argument. 3 Do not wait at all--Return immediately after checking the d-
     escriptors. This is called polling. To specify this, the timeout argument must -
     point to a timeval structure and the timer value (the number of seconds and mic-
     roseconds specified by the structure) must be 0. The wait in the first two scen-
     arios is normally interrupted if the process catches a signal and returns from -
     the signal handler.
 function: 
    告诉内核
    1 关心的描述符
    2 关心描述符的哪些状态，比如是否可读、是否可写、描述符的异常状态
    3 等待时间
    从select返回内核告诉我们
    1 已经准备好的描述符数量
    2 对于读、写或异常这三个状态中的每一个，哪些描述符已经准备好。
      使用这些返回信息就可以调用相应的I/O函数，并确切知道函数不会阻塞
 Returns: 
     There are three possible return values from @select. 1 return -1 means that an -
     error occurred. This can happen, for example, if a signal is caught before any -
     of the specified descriptors are ready.In this case, none of the descriptor sets 
     will be modified. 2 return 0 means that no descriptors are ready. This happens -
     if the time limit expires before any of the descriptors are ready. When this ha-
     ppens, all the descriptor sets will be zeroed out. 3 A positive return value sp-
     ecifies the number of descriptors that are ready. This value is the sum of the -
     descriptors ready in all three sets, so if the same descriptor is ready to be r-
     ead and written, it will be counted twice in the return value. The only bits le-
     ft on in the three descriptor sets are the bits corresponding to the descriptors 
     that are ready.

 If we encounter the end of file on a descriptor, that descriptor is considered 
 readable by @select. We then call read and it returns 0—the way to signify end 
 of file on UNIX systems. 
 ----> Under What Conditions Is a Descriptor Ready?
 1 对于读描述符集中的一个描述符的read操作将不会阻塞，则此描述符是准备好的
 2 对于写描述符集中的一个描述符的write操作将不会阻塞，则此描述符是准备好的
 3 若异常描述符集中的一个描述符有一个未决异常状态，则此描述符是准备好的。
   异常状态包括
   a 在网络连接上到达的带外数据
   b 处于数据包模式的伪终端上发生了某些状态。
 4 File descriptors for regular files always return ready for reading, writing, 
   and exception conditions.

 example: tcp_serv_select()
 ----------------------------------------------------------------------------------*/
int select(int maxfdp1, fd_set *readset, fd_set *writeset, fd_set *exceptset, 
            const struct timeval *timeout);

/*-----------------------------------------------------------------------------------
 @select uses descriptor sets, typically an array of integers, with each bit in 
 each integer corresponding to a descriptor. For example, using 32-bit integers, 
 the first element of the array corresponds to descriptors 0 through 31, the 
 second element of the array corresponds to descriptors 32 through 63, and so on. 
 All the implementation details are irrelevant to the application and are hidden 
 in the fd_set datatype and the following four macros:

 example: fd_set_example()
 -----------------------------------------------------------------------------------*/
int  FD_ISSET(int fd,fd_set *fdset);
void FD_CLR(int fd,fd_set *fdset);
void FD_SET(int fd,fd_set *fdset);
void FD_ZERO(fd_set *fdset); 

/*******************************************************************************
 After declaring a descriptor set, we must zero the set using FD_ZERO.Wethen set
 bits in the set for each descriptor that we’reinterested in, as in
 ******************************************************************************/
void fd_set_example()
{
	fd_set	rset;
	int  fd;
	
	FD_ZERO(&rset); 		 /* initialize the set: all bits off */
	FD_SET(1, &rset);		 /* turn on bit for fd 1 */
	FD_SET(4, &rset);		 /* turn on bit for fd 4 */
	FD_SET(5, &rset);		 /* turn on bit for fd 5 */
	FD_SET(STDIN_FILENO, &rset);

	if (FD_ISSET(fd, &rset)) {
	}
}

#include <sys/select.h>
#include <signal.h>
#include <time.h>
 
struct timespec {
  time_t tv_sec;       /* seconds */
  long   tv_nsec;      /* nanoseconds 纳秒 */
};

/*******************************************************************************
 When @pselect is called, it replaces the signal mask of the process with an 
 @sigmask set (i.e., zeromask) and then checks the descriptors, possibly going 
 to sleep. But when @pselect returns, the signal mask of the process is reset 
 to its value before @pselect was called (i.e., SIGINT is blocked).

 Returns: count of ready descriptors, 0 on timeout,-1 on error
 ******************************************************************************/
int pselect(int maxfdp1,fd_set *restrict readfds,fd_set *restrict writefds,fd_set *restrict exceptfds,
const struct timespec *restrict tsptr,const sigset_t *restrict sigmask);



#include <poll.h>

/********** Input events and returned revents for @poll ***********/
#define POLLIN       /* Data other than high-priority data can be read */
#define POLLRDNORM   /* Equivalent to POLLIN */
#define POLLRDBAND   /* Priority data can be read (unused on Linux) */
#define POLLPRI      /* High-priority data can be read */
#define POLLRDHUP    /* Shutdown on peer socket */

#define POLLOUT      /* Normal data can be written */
#define POLLWRNORM   /* Equivalent to POLLOUT */
#define POLLWRBAND   /* Priority data can be written */

#define POLLERR      /* An error has occurred */
#define POLLHUP      /* A hangup has occurred */
#define POLLNVAL     /* File descriptor is not open */

#define POLLMSG      /* Unused on Linux (and unspecified in SUSv3) */

#define INFTIM       /*是一个负值 @poll的第三个参数,表示永远等待*/

/*-----------------------------------------------------------------------------------
@events @revents
   The @events and @revents fields of the pollfd structure are bit masks . The caller 
   initializes  @events to specify the events to be monitored for the file descriptor 
   @fd. Upon return from poll(), @revents is set to indicate which of those events a-
   ctually occurred for this file descriptor. 

   The first group of bits in this table (POLLIN, POLLRDNORM, POLLRDBAND, POLLPRI,and 
   POLLRDHUP) are concerned with input events. The next group of bits (POLLOUT, POLLWRNORM, 
   and POLLWRBAND) are concerned with output events. The third group of bits(POLLERR,
   POLLHUP, and POLLNVAL) are set in the @revents field to return additional informa-
   tion about the file descriptor.If specified in the @events field, these three bits 
   are ignored. The final bit (POLLMSG) is unused by poll() on Linux.
-----------------------------------------------------------------------------------*/
struct pollfd 
{
    int  fd;        /* file descriptor to check, or <0 to ignore */
    short  events;  /* events of interest on fd. POLLIN etc*/
    short  revents; /* events that occurred on fd */
};

/*-----------------------------------------------------------------------------------
 @fds: 
    a pointer to the first element of an array of structures.Each element of the arr-
    ay is a  @pollfd structure that specifies the conditions to be tested for a given 
    descriptor, fd.
 @nfds
    The number of elements in the array of structures is specified by the nfds argum-
    ent. The nfds_t data type used to type the  @nfds argument is an unsigned integer 
    type.
 @timeout: INFTIM
    If @timeout equals –1,block until one of the file descriptors listed in the @fds 
    array is ready (as defined by the corresponding events field) or a signal is cau-
    ght. If @timeout equals 0, do not block—just perform a check to see which file -
    descriptors are ready. If @timeout is greater than 0, block for up to @timeout m-
    illiseconds, until one of the file descriptors in @fds is ready, or until a sign-
    al is caught.
 @returns: 
    The return value from @poll is –1 if an error occurred , 0 if no descriptors are 
    ready before the timer expires, otherwise it is the number of descriptors that h-
    ave a nonzero @revents member.

 With regard to TCP and UDP sockets, the following conditions cause @poll to return 
 the specified revent. Unfortunately, POSIX leaves many holes (i.e., optional ways 
 to return the same condition) in its definition of poll.
 1 All regular TCP data and all UDP data is considered normal.
 2 TCP's out-of-band data is considered priority band.
 3 When the read half of a TCP connection is closed (e.g., a FIN is received), this 
   is also considered normal data and a subsequent read operation will return 0.
 4 The presence of an error for a TCP connection can be considered either normal data 
   or an error (POLLERR). In either case, a subsequent read will return –1 with errno 
   set to the appropriate value. This handles conditions such as the receipt of an RST 
   or a timeout.
 5 The availability of a new connection on a listening socket can be considered either 
   normal data or priority data. Most implementations consider this normal data.
 6 The completion of a nonblocking connect is considered to make a socket writable.
-----------------------------------------------------------------------------------*/
int poll(struct pollfd fds[], nfds_t nfds,int timeout);



#include <sys/epoll.h> 


/*-----------------------------------------------------------------------------------
 epoll is a Linux kernel system call,a scalable I/O event notification mechanism,first 
 introduced in Linux kernel 2.5.44. It is meant to replace the older POSIX select(2) 
 and poll(2) system calls,to achieve better performance in more demanding applications, 
 where the number of watched file descriptors is large (unlike the older system calls, 
 which operate in O(n) time, epoll operates in O(1) time).epoll is similar to FreeBSD's 
 kqueue, in that it operates on a configurable kernel object, exposed to user space as 
 a file descriptor of its own.

 EPOLL事件有两种模型 Level Triggered (LT) 和 Edge Triggered (ET)：

 LT(level triggered，水平触发模式)
    是缺省的工作方式，并且同时支持 block 和 non-block socket。在这种做法中，内核告诉你
    一个文件描述符是否就绪了，然后你可以对这个就绪的fd进行IO操作。如果你不作任何操作，
    内核还是会继续通知你的，所以，这种模式编程出错误可能性要小一点。

 ET(edge-triggered，边缘触发模式)
    是高速工作方式，只支持no-block socket。在这种模式下，当描述符从未就绪变为就绪时，
    内核通过epoll告诉你。然后它会假设你知道文件描述符已经就绪，并且不会再为那个文件
    描述符发送更多的就绪通知，等到下次有新的数据进来的时候才会再次出发就绪事件。 
-----------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------
 @size:
    The @size argument specifies the number of file descriptors that we expect to mo-
    nitor via the epoll instance. This argument is not an upper limit, but rather a -
    hint to the kernel about how to initially dimension internal data structures. Si-
    nce  Linux 2.6.8, the size argument is unused.
 @flags: 0 or EPOLL_CLOEXEC
    If flags is 0,then,other than the fact that the obsolete size argument is dropped, 
    epoll_create1() is the same as epoll_create().The following value can be included 
    in flags to obtain different behavior:EPOLL_CLOEXEC
 @func
    The epoll_create() system call creates a new epoll instance whose interest list -
    is initially empty.
 @ret
    Returns file descriptor on success, or –1 on error

 As its function result,epoll_create() returns a file descriptor referring to the new
 epoll instance. This file descriptor is used to refer to the epoll instance in other 
 epoll system calls. When the file descriptor is no longer required, it should be cl-
 osed in the usual way, using close(). When all file descriptors referring to an epo-
 ll instance are closed, the instance is destroyed and its associated resources are -
 released back to the system. ( Multiple file descriptors may refer to the same epoll 
 instance as a consequence of calls to fork() or descriptor duplication using dup() -
 or similar.)

 Starting with kernel 2.6.27, Linux supports a new system call, epoll_create1(). Thi-
 s system call performs the same task as epoll_create(), but drops the obsolete @size 
 argument and adds a @flags argument that can be used to modify the behavior of the -
 system call. One flag is currently supported: EPOLL_CLOEXEC, which causes the kernel 
 to enable the close-on-exec flag (FD_CLOEXEC) for the new file descriptor. This flag 
 is useful for the same reasons as the open() O_CLOEXEC flag. 
-----------------------------------------------------------------------------------*/
int epoll_create(int size);
int epoll_create1(int flags);


/*-----------------------------------------------------------------------------------
 @epfd: 
 @op    EPOLL_CTL_ADD
    The @op argument specifies the operation to be performed
 @fd    
    The @fd argument identifies which of the file descriptors in the interest list is 
    to have its settings modified.  This argument can be a file descriptor for a pipe, 
    FIFO, socket, POSIX message queue, inotify instance, terminal, device, or even a-
    nother epoll descriptor (i.e., we can build a kind of hierarchy of monitored des-
    criptors). However, @fd can't be a file descriptor for a regular file or a direc-
    tory (the error EPERM results).
 @event 
 @func
    The epoll_ctl() system call modifies the interest list of the epoll instance ref-
    erred to by the file descriptor @epfd.
 @ret
    Returns 0 on success, or –1 on error
-----------------------------------------------------------------------------------*/
int epoll_ctl(int epfd, int op, int fd, struct epoll_event *ev);

/* Using epoll_create() and epoll_ctl() */
void epoll_eg01(int fd)
{
    int epfd;
    struct epoll_event ev;
    epfd = epoll_create(5);
    if (epfd == -1)
        errExit("epoll_create");
    ev.data.fd = fd;
    ev.events = EPOLLIN;
    if (epoll_ctl(epfd, EPOLL_CTL_ADD, fd, ev) == -1)
        errExit("epoll_ctl");
}


/*-----------------------------------------------------------------------------------
 @evlist @maxevents
    The information about ready file descriptors is returned in the array of epoll_event
    structures pointed to by @evlist. The @evlist array is allocated by the caller, -
    and the number of elements it contains is specified in @maxevents.
    Each item in the array @evlist returns information about a single ready file des-
    criptor. The  @events subfield returns a mask of the events that have occurred on
    this descriptor. The @data subfield returns whatever value was specified in ev.data
    when we registered interest in this file descriptor using  epoll_ctl(). Note that 
    the @data field provides the only mechanism for finding out the number of the fi-
    le descriptor associated with this event. Thus, when we make the epoll_ctl() call 
    that places a file descriptor in the interest list, we should either set ev.data.fd 
    to the file descriptor number or set ev.data.ptr to point to a structure that co-
    ntains the file descriptor number.
 @timeout
    If @timeout equals –1, block until an event occurs for one of the file descript-
    ors in the interest list for @epfd or until a signal is caught.
    If @timeout equals 0, perform a nonblocking check to see which events are curren-
    tly available on the file descriptors in the interest list for @epfd.
    If timeout is greater than 0, block for up to @timeout milliseconds, until an ev-
    ent occurs on one of the file descriptors in the interest list for @epfd, or unt-
    il a signal is caught.
 @func
    The epoll_wait() system call returns information about ready file descriptors from
    the epoll instance referred to by the file descriptor @epfd. A single epoll_wait() 
    call can return information about multiple ready file descriptors.
 @ret
   	Returns number of ready file descriptors, 0 on timeout, or –1 on error
-----------------------------------------------------------------------------------*/
int epoll_wait(int epfd, struct epoll_event *evlist, int maxevents, int timeout);


#include <sys/mman.h>
/* @mmmap @prot */
#define PROT_READ   /* Region can be read. */
#define PROT_WRITE  /* Region can be written. */
#define PROT_EXEC   /* Region can be executed. */
#define PROT_NONE   /* Region cannot be accessed. */
/* @mmmap @flag */
#define MAP_FIXED   /* 返回值必须等于@addr MAP_SHARED和MAP_PRIVATE必须指定一个，但不能同时指定。*/
#define MAP_SHARED	/* 存储操作相当于对该文件的write.*/
#define MAP_PRIVATE /* 对映射区的存储操作导致创建该映射文件的一个私有副本。*/

/*-----------------------------------------------------------------------------------
 @addr:
    映射存储区的起始地址,0表示让系统自动选择。页边界对齐
 @len: 
    映射的字节数
 @prot:
    映射区的保护要求(按位或)
    PROT_READ Region can be read.
    PROT_WRITE Region can be written.
    PROT_EXEC Region can be executed.
    PROT_NONE Region cannot be accessed.
 @flag: MAP_FIXED
    Either the MAP_SHARED or the MAP_PRIVATE flag must be specified , optionally ORed 
    with  MAP_FIXED. If MAP_PRIVATE is specified, then modifications to the mapped d-
    ata by the calling process are visible only to that process and do not change the 
    underlying object (either a file object or a shared memory object). If MAP_SHARED 
    is specified, modifications to the mapped data by the calling process are visible  
    to all processes that are sharing the object, and these changes do modify the un-
    derlying object. 
 @fd:  
    被映射文件的描述符,映射文件前要打开该文件
 @off: 
    要映射字节在文件中的起始偏移量
 @Returns: 
    starting address of mapped region if OK,MAP_FAILED on error

 One way to share memory between a parent and child is	to call map with MAP_SHARED 
 before calling fork. Posix.1 then guarantees that memory mappings in the parent are 
 retained in the child. Furthermore, changes made by the parent are visible to the c-
 hild and vice versa.

 After map returns success, the @fd argument can be closed. This has no effect on the 
 mapping that was established by @mmap. 

 Trying to map a descriptor that refers to a terminal or a socket, for example, gene-
 rates an error return from map. These types of  descriptors must be accessed using -
 read and write (or variants thereof ). 
 
 Another use of map is to provide shared memory between unrelated processes . In this 
 case, the actual contents of the file become the initial contents of the memory that 
 is shared, and any changes made by the processes to this shared memory are then cop-
 ied back to the file (providing filesystem persistence).This assumes that MAP_SHARED 
 is specified, which is required to share the memory between processes. 

 low memory      return value of @mmap        
 |                   |
\|/                 \|/
 +-----------------------------------------------+
 |                   |                 |         |       address space of process
 +-----------------------------------------------+
                     |                 |
                     |                 |
                    \|/               \|/
 +-------------------------------------------+
 |   @offset         |      @len       |     |      file referenced by descriptor @fd
 +-------------------------------------------+

 example: mmap_eg_sharemem()
-----------------------------------------------------------------------------------*/
void *mmap(void *addr,size_t len,int prot,int flag,int fd,off_t off);

/*-----------------------------------------------------------------------------------
 @function:
    To remove a mapping from the address space of the process, we call @munmap. 
 @Returns: 
    0 if OK,-1 on error

 A memory-mapped region is automatically unmapped when the process terminates or we -
 can unmap a region directly by calling the @munmap function. The @munmap function d-
 oes not affect the object that was mapped, that is, the call to @munmap does not ca-
 use the contents of the mapped region to be written to the disk file.The updating of 
 the disk file for a  MAP_SHARED region happens automatically by the kernel's virtual 
 memory algorithm sometime after we store into the memory-mapped region.Modifications 
 to memory in a MAP_PRIVATE region are discarded when the region is unmapped.
-----------------------------------------------------------------------------------*/
int munmap(void *addr,size_t len);

#define MS_ASYNC	   
#define MS_SYNC 
#define MS_INVALIDATE

/*-----------------------------------------------------------------------------------
 @addr @len
    The @addr and @len arguments normally refer to the entire memory-mapped region of  
    memory, although subsets of this region can also be specified. 
 @flags: MS_ASYNC	MS_SYNC 	MS_INVALIDATE
    One of the two constants MS_ASYNC and MS_SYNC must be specified, but not both.The 
    difference in these two is that MS_ASYNC returns once the write operations are q-
    ueued by the kernel , whereas MS_SYNC returns only after the write operations are 
    complete. If MS_INVALIDATE is also specified, all in-memory copies of the file d-
    ata that are inconsistent with the file data are invalidated. Subsequent referen-
    ces will obtain data from the file. 
 @Returns: 
    0 if OK,-1 on error		

 the kernel's virtual memory algorithm keeps the memory-mapped file (typically on di-
 sk) synchronized with the memory-mapped region in memory, assuming a MAP_SHARED seg-
 ment. That is, if we modify a location in memory that is memory-mapped to a file, t-
 hen at some time later the kernel will update the file accordingly. But sometimes, -
 we want to make certain  that the file on disk corresponds to what is in the memory-
 mapped region, and we call @msync to perform this synchronization. 
-----------------------------------------------------------------------------------*/
int msync(void *addr,size_t len,int flags);


/*-----------------------------------------------------------------------------------
function:We can change the permissions on an existing mapping by calling @mprotect
Returns: 0 if OK,-1 on error
-----------------------------------------------------------------------------------*/
int mprotect(void *addr,size_t len,int prot);




 

#include <sys/uio.h>

/************************************************************************************
 read()和write()系统调用每次在文件和进程的地址空间之间传送一块连续的数据。但是，应用有
 时也需要将分散在内存多处地方的数据连续写到文件中，或者反之。在这种情况下，如果要从文
 件中读一片连续的数据至进程的不同区域，使用read()则要么一次将它们读至一个较大的缓冲区
 中，然后将它们分成若干部分复制到不同的区域，要么调用read()若干次分批将它们读至不同区
 域。同样，如果想将程序中不同区域的数据块连续地写至文件，也必须进行类似的处理。

 UNIX提供了另外两个函数—readv()和writev()，它们只需一次系统调用就可以实现在文件和进程
 的多个缓冲区之间传送数据，免除了多次系统调用或复制数据的开销。readv()称为散布读，即将
 文件中若干连续的数据块读入内存分散的缓冲区中。writev()称为聚集写，即收集内存中分散的
 若干缓冲区中的数据写至文件的连续区域中。

 参数@fildes是文件描述字。@iov是一个结构数组，它的每个元素指明存储器中的一个缓冲区。
 参数@iovcnt指出数组@iov的元素个数，元素个数至多不超过IOV_MAX。Linux中定义IOV_MAX的值
 为1024。

 readv()则将fildes指定文件中的数据按iov[0]、iov[1]、...、iov[iovcnt–1]规定的顺序和长
 度，分散地读到它们指定的存储地址中。readv()的返回值是读入的总字节数。如果没有数据可
 读和遇到了文件尾，其返回值为0。

 有了这两个函数，当想要集中写出某张链表时，只需让iov数组的各个元素包含链表中各个表项
 的地址和其长度，然后将iov和它的元素个数作为参数传递给writev()，这些数据便可一次写出。
************************************************************************************/

/* return: number of bytes read or written, –1 on error */ 
ssize_t readv(int filedes, const struct iovec *iov, int iovcnt);

/*@iov:结构体数组指针
  return: number of bytes read or written, –1 on error */
ssize_t writev(int filedes, const struct iovec *iov, int iovcnt);
 

/************************************************************************************
 @request
    We can divide the  requests  related to  networking  into six categories: Socket 
    operations; File operations; Interface operations; ARP cache operations; Routing 
    table operations; STREAMS system
 @third argument
    The  third argument is always  a pointer, but the type of pointer depends on the 
    request.
 
 @returns: -1 on error, something else if OK
 
************************************************************************************/
#include <unistd.h> /* System V */
#include <sys/ioctl.h> /* BSD and Linux */
int ioctl(int fd, int request, ...);
	


