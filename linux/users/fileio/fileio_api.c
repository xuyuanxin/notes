
/*
@path: 要打开或创建文件的名字
@oflag:
@mode: 创建时才会用到
function:打开一个文件(也可用于创建文件)
return: file descriptor if OK,-1 on error

1 open返回的文件描述符一定是最小的未用描述符数值。
2 @path文件名最大字符个数是NAME_MAX
*/

/*If the file exists and if it is successfully opened for either write-only or read–write, truncate its length to 0.*/
#define	O_TRUNC   

/*	---->
	O_RDONLY Open for reading only.
	O_WRONLY Open for writing only.
	O_RDWR	 Open for reading and writing.
			 Most implementations define O_RDONLY as 0,O_WRONLY as 1, and O_RDWR as 2, for compatibility with older programs.
	O_EXEC	 Open for execute only.
	O_SEARCH Open for search only (applies to directories).
	
	The purpose of theO_SEARCHconstant is to evaluate search permissions at the time
	adirectory	is	opened. Further  operations  using	the  directory’s  file  descriptor  will
	not  reevaluate  permission  to  search  the  directory.None  of  the  versions  of  the
	operating systems covered in this book supportO_SEARCHyet.
	One  and  only	one  of  the  previous	five  constants  must  be  specified. The  following
	constants areoptional:
		
	O_APPEND  Append to the end of file on each write.
	
	O_CLOEXEC Set  theFD_CLOEXECfile  descriptor  flag. We	discuss  file  descriptor
	flags in Section 3.14.
	
	O_CREAT  Create the file if it doesn’t exist. This option requires a third argument to the open function (a fourth argument 
			 to the openat function) — the mode,which specifies the access permission bits of the new file.
			 
	O_DIRECTORYGenerate an error ifpathdoesn’t refer to a directory.
	
	O_EXCL	 Generate an error if O_CREAT is also specified and the file already exists. This test for whether the file already 
			 exists and the creation of the file if it doesn’t exist is an atomic operation. 
		
	O_NOCTTY If pathrefers	to	a  terminal  device,  do  not  allocate  the  device  as  the
	controlling  terminal  for	this  process.	Wetalk	about  controlling
	terminals in Section 9.6.
	O_NOFOLLOW Generate an error ifpathrefers to a symbolic link. We  discuss symbolic
	links in Section 4.17.
	
	O_NONBLOCK	If path refers to a FIFO, a block special file, or a character special file,this option sets the nonblocking mode 
				for both the opening of the file and subsequent I/O.
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
int open(const char *path,int oflag,... /* mode_t mode*/ );
int openat(intfd,const char *path,intoflag,... /* mode_tmode*/ );

/*
Returns: file descriptor opened for write-only if OK,?1 on error

1 Note that this function is equivalent to open(path,O_WRONLY | O_CREAT | O_TRUNC,mode);
2 One deficiency with creat is that the file is opened only for writing. 
*/
#include <fcntl.h>
int creat(const char *path,mode_t mode);

/*
function: An open file is closed by calling the close function.
Returns: 0 if OK,?1 on error

1 When a process terminates, all of its open files are closed automatically by the kernel.  
*/
#include <unistd.h>
int close(int fd);


/*
@fd
@offset:
@whence:
function:打开一个文件并设置其偏移量
returns: new file offset if OK,-1 on error
name: lseek中的l表示长整型

If whence is SEEK_SET(0),the file's offset is set to offset bytes from the beginning of the file.
If whence is SEEK_CUR(1),the file's offset is set to its current value plus the offset. The offset can be positive or negative.
If whence is SEEK_END(2),the file's offset is set to the size of the file plus the offset. The offset can be positive or negative.

lseek only records the current file offset within the kernel—it does not cause any I/O to take place.  This offset is then used 
by the next read or write operation.
*/
#include <unistd.h>
off_t lseek(int fd,off_t offset,int whence);

#include <unistd.h>
/*
@fd:读哪个文件(已经打开了)
@buf:把读的数据放入这个buf中
@nbytes:希望读取数据的长度

function:Data is read from an open file with the @read function.
Returns: number of bytes read, 0 if end of file,-1 on error

1 参数count是请求读取的字节数，读上来的数据保存在缓冲区buf中，同时文件的当前读写位置向后移。
2 读常规文件时，在读到count个字节之前已到达文件末尾。例如，距文件末尾还有30个字节而请求读100个字节，则read返回30，下次read将返回0。
3 面向文本的套接字读操作中,一次read不能保证读入完整的一行或整行,读完整的一行可能需要对此调用read,并检查其中是否出现了换行符*/
ssize_t read(int fd,void *buf,size_t nbytes);

/*
@fd:写哪个文件(已经打开了)
@buf:buf中是要写的数据
@nbytes:写入数据的长度
funtion:Data is written to an open file with the @write function.
Returns: number of bytes written if OK,-1 on error

For a regular file, the write operation starts at the file’s current offset. If the O_APPEND option was specified when the file 
was opened, the file’s offset is set to the current end of file before each write operation. After a successful write, the file’s 
offset is incremented by the number of bytes actually written.
*/
#include <unistd.h>
ssize_t write(int fd,const void *buf,size_t nbytes);


/*
@fd
@fd2
function:An existing file descriptor is duplicated by dup dup2
return: new file descriptor if OK,-1 on error 

1 The new file descriptor returned by dup is guaranteed to be the lowest-numbered available file descriptor.With dup2, we specify 
the value of the new descriptor with the fd2 argument. If fd2 is already open, it is first closed. If fd equals fd2,then dup2 
returns fd2 without closing it. Otherwise, the FD_CLOEXEC file descriptor flag is cleared for fd2,so that fd2 is left open if the
process calls exec.
2 The new file descriptor that is returned as the value of the functions shares the same file table entry as the fd argument. 
they share the same file status flags—read, write, append, and so on—and the same current file offset.
3 Each descriptor has its own set of file descriptor flags. As we describe in Section  3.14, the close-on-exec file descriptor 
flag for the new  descriptor  is  always cleared by the dup functions.
*/

#include <unistd.h>
int dup(int fd);
int dup2(int fd,int fd2);


/*
The @sync function simply queues all the modified block buffers for writing and returns; it does not wait for the disk writes to take place.
The function @sync is normally called periodically (usually every 30 seconds) from a system daemon, often called update.This 
guarantees regular flushing of the kernel’s block buffers.  The command sync(1) also calls the sync function.
The function fsync refers only to a single file, specified by the file descriptor fd, and waits for the disk writes to complete 
before returning. This function is used when an application, such as a database, needs to be sure that the modified blocks have been
written to the disk.
The fdatasync function is similar to fsync,but it affects only the data portions of a file. With fsync,the file’s attributes 
are also updated synchronously.

Returns: 0 if OK,?1 on errors*/
#include <unistd.h>
int fsync(int fd);
int fdatasync(int fd);

void sync(void);

/*
function:The fcntl function can change the properties of a file that is already open.
The fcntl function is used for five different purposes.
1.  Duplicate an existing descriptor (cmd=F_DUPFD or F_DUPFD_CLOEXEC)
2.  Get/set file descriptor flags (cmd=F_GETFD or F_SETFD)
3.  Get/set file status flags (cmd=F_GETFL or F_SETFL)
4.  Get/set asynchronous I/O ownership (cmd=F_GETOWNorF_SETOWN)
5.  Get/setrecordlocks (cmd=F_GETLK,F_SETLK,orF_SETLKW)
Returns: depends on cmd if OK (see following),-1 on error

---->fcntl中的第二个参数
F_DUPFD  Duplicate the file descriptor @fd.The new file descriptor is returned as the value of the function. It is the lowest-numbered
         descriptor that is not already open, and that is greater than or equal to the third argument (taken as an integer). The new
         descriptor shares the same file table entry as @fd. But the new descriptor has its own set of file descriptor flags, and its 
		FD_CLOEXEC file descriptor flag is cleared. (This means that the descriptor is left open across an exec)
F_DUPFD_CLOEXEC Duplicate the file descriptor and set the FD_CLOEXEC file descriptor flag associated with the new descriptor.Returns the
                new file descriptor.
F_GETFD  Return the file descriptor flags for @fd as the value of the function. Currently,only one file descriptor flag is defined: the FD_CLOEXEC flag.
F_SETFD  Set the file descriptor flags for @fd.The new flag value is set from the third argument (taken as an integer).*/
#include <fcntl.h>
int fcntl(int fd,int cmd,... /* intarg */ );




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
