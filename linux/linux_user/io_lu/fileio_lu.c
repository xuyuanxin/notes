
#include <fcntl.h>
/*******************************************************************************
@path: Ҫ�򿪻򴴽��ļ�������
@oflag:
@mode: ����ʱ�Ż��õ�
function:��һ���ļ�(Ҳ�����ڴ����ļ�)
return: file descriptor if OK,-1 on error

1 open���ص��ļ�������һ������С��δ����������ֵ��
2 @path�ļ�������ַ������� NAME_MAX
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
function: ��һ���ļ���������ƫ����
returns : new file offset if OK,-1 on error
name    : lseek�е�l��ʾ������

@lseek only records the current file offset within the kernel��it does not cause
any I/O to take place. This offset is then used by the next read or write operation.
*******************************************************************************/
off_t lseek(int fd,off_t offset,int whence);

#include <unistd.h>
/******************************************************************************
@fd :���ĸ��ļ�(�Ѿ�����)
@buf:�Ѷ������ݷ������buf��
@nbytes:ϣ����ȡ���ݵĳ���

function:Data is read from an open file with the @read function.
Returns: number of bytes read, 0 if end of file,-1 on error

1 ����count�������ȡ���ֽ����������������ݱ����ڻ�����buf�У�ͬʱ�ļ��ĵ�ǰ��
  дλ������ơ�
2 �������ļ�ʱ���ڶ���count���ֽ�֮ǰ�ѵ����ļ�ĩβ�����磬���ļ�ĩβ����30����
  �ڶ������100���ֽڣ���read����30���´�read������0��
3 �����ı����׽��ֶ�������,һ��read���ܱ�֤����������һ�л�����,��������һ�п�
  ����Ҫ�Դ˵���read,����������Ƿ�����˻��з�
4 �������յ�FINʱ,����һ��EOF�����������е�read,�յ���read����EOF
5 POSIX.1 requires that read return -1 with errno set to EAGAIN if there is no 
  data to read from a nonblocking descriptor. 
******************************************************************************/
ssize_t read(int fd,void *buf,size_t nbytes);

/******************************************************************************
 @fd    : д�ĸ��ļ�(�Ѿ�����)
 @buf   : buf����Ҫд������
 @nbytes: д�����ݵĳ���
 funtion: Data is written to an open file with the @write function.
 Returns: number of bytes written if OK,-1 on error

 For a regular file, the write operation starts at the file's current offset. If 
 the O_APPEND option was specified when the file was opened, the file's offset 
 is set to the current end of file before each write operation. After a successful
 write, the file's offset is incremented by the number of bytes actually written.

 It is okay to write to a socket that has received a FIN, but it is an error to 
 write to a socket that has received an RST.

 What happens if the client ignores the error return from read and writes more 
 data to the server? This can happen, for example, if the client needs to perform 
 two writes to the server before reading anything back, with the first write 
 eliciting the RST.
 
 When a process writes to a socket that has received an RST, the SIGPIPE signal 
 is sent to the process. The default action of this signal is to terminate the 
 process, so the process must catch the signal to avoid being involuntarily 
 terminated.If the process either catches the signal and returns from the signal 
 handler, or ignores the signal, the write operation returns EPIPE.
 *****************************************************************************/
ssize_t write(int fd,const void *buf,size_t nbytes);

#include <unistd.h>
/******************************************************************************
@fd    ��Ҫ��ȡ���ݵ��ļ�������
@buf   �����ݻ�����ָ�룬��Ŷ�ȡ����������
@count ����ȡ���ݵ��ֽ���
@offset����ȡ����ʼ��ַ��ƫ��������ȡ��ַ=�ļ���ʼ+offset��
����ֵ���ɹ������سɹ���ȡ���ݵ��ֽ�����ʧ�ܣ�����-1��

1 ִ�к��ļ�ƫ��ָ�벻��
2 �൱��˳�����lseek��read,���䶨λ�Ͷ�ȡ������ԭ�ӵġ�lseek��read֮��������ж�
  ����������⡣
******************************************************************************/
ssize_t pread(int fd, void *buf, size_t nbytes, off_t offset);

/*******************************************************************************
@fd    ��Ҫд�����ݵ��ļ�������
@buf   �����ݻ�����ָ�룬���Ҫд���ļ��е�����
@count ��д���ļ��е����ݵ��ֽ���
@offset��д���ַ=�ļ���ʼ+offset
����ֵ ���ɹ�������д�뵽�ļ��е��ֽ�����ʧ�ܣ�����-1��

1 ִ�к��ļ�ƫ��ָ�벻��
2 �൱��˳�����lseek��write,���䶨λ�Ͷ�ȡ������ԭ�ӵġ�lseek��read֮�������
  �жϿ���������⡣
******************************************************************************/
ssize_t pwrite(int fd, const void *buf, size_t nbytes, off_t offset);



#include <unistd.h>
/*******************************************************************************
 ����ֵ:�ɹ������µ�������,ʧ�ܷ���-1
 ����:�����ļ�������@fd

 1 @dup���ص���������һ���ǵ�ǰ�����ļ��������е���С��ֵ
 2 ����������@fd����һ���ļ�����(file table entry)
 3 ����������ִ��ʱ�ر�(close-on-exec)��־������@dup�������
******************************************************************************/
int dup(int fd);

/*******************************************************************************
 ����ֵ:�ɹ������µ�������,ʧ�ܷ���-1
 ����:�����ļ�������@fd,@fd2��ָ������������

 1 ���@fd2�Ѿ��򿪣����ȹرա�
 2 ���@fd==@fd2�����ر�@fd2��ֱ�ӷ���@fd2
 3 ����������@fd����һ���ļ�����(file table entry)
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

/*********************************************************************************
 @cmd: F_SETFL
 
 @fun:
   The @fcntl function can change the properties of a file that is already open.
   The @fcntl function is used for five different purposes.
   1 Duplicate an existing descriptor (cmd=F_DUPFD or F_DUPFD_CLOEXEC)
   2 Get/set file descriptor flags (cmd=F_GETFD or F_SETFD)
   3 Get/set file status flags (cmd=F_GETFL or F_SETFL)
   4 Get/set asynchronous I/O ownership (cmd=F_GETOWNorF_SETOWN)
   5 Get/setrecordlocks (cmd=F_GETLK,F_SETLK,orF_SETLKW)
@ret: 
   depends on @cmd if OK (see following),-1 on error
   The return value from @fcntl depends on the command. All commands return -1 on 
   an error or some other value if OK. The following four commands have special
   return values: F_DUPFD, F_GETFD, F_GETFL, and F_GETOWN. The first command returns 
   the new file descriptor, the next two return the corresponding flags, and the 
   final command returns a positive process ID or a negative process group ID.
**********************************************************************************/
#include <fcntl.h>
int fcntl(int fd,int cmd,... /* int arg */ );

/******************************************************************************\
                                 ��¼��
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

 ---->ʹ�ù���
  We previously mentioned two types of locks: a shared read lock (l_type of
F_RDLCK) and an exclusive write lock (F_WRLCK). The basic rule is that any number 
of processes can have a shared read lock on a given byte, but only one process 
can have an exclusive write lock on a given byte. Furthermore, if there are one 
or more read locks on a byte, there can't be any write locks on that byte; if 
there is an exclusive write lock on a byte, there can��t be any read locks on 
that byte. 

---->����������ǿ������ Advisory versus Mandatory Locking
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
���ļ̳����ͷ�
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

#define FD_SETSIZE  /*@select�ĵ�һ������������������������ͨ����1024*/

struct timeval	
{
  long	 tv_sec;  /* seconds */
  long	 tv_usec; /* microseconds */
};

/*******************************************************************************
 @maxfdp1: ����������+1
 @readset: ����������������ΪNULL
 @readset: д��������������ΪNULL
 @readset: �쳣��������������ΪNULL
 @timeout: �ȴ�ʱ��
 function: 
    �����ں�
    1 ���ĵ�������
    2 ��������������Щ״̬�������Ƿ�ɶ����Ƿ��д�����������쳣״̬
    3 �ȴ�ʱ��
    ��select�����ں˸�������
    1 �Ѿ�׼���õ�����������
    2 ���ڶ���д���쳣������״̬�е�ÿһ������Щ�������Ѿ�׼���á�
      ʹ����Щ������Ϣ�Ϳ��Ե�����Ӧ��I/O��������ȷ��֪��������������
 Returns: 
    positive count of ready descriptors, 0 on timeout, �C1 on error
    
 There are three possible return values from @select.
 1 return -1 means that an error occurred. This can happen, for example, if a 
   signal is caught before any of the specified descriptors are ready.In this 
   case, none of the descriptor sets will be modified.
 2 return 0 means that no descriptors are ready.This happens if the time limit 
   expires before any of the descriptors are ready.When this happens,all the 
   descriptor sets will be zeroed out.
 3 A positive return value specifies the number of descriptors that are ready.
   This value is the sum of the descriptors ready in all three sets, so if the 
   same descriptor is ready to be read and written, it will be counted twice in 
   the return value. The only bits left on in the three descriptor sets are the 
   bits corresponding to the descriptors that are ready.
 ---->�ȴ���ʱ��
 1 ��Զ�ȴ�  timeout == NULL
 2 �ȴ�ָ����ʱ�� �����ʱ����timeoutָ��
 3 ���ȴ�  timeout�е�ʱ��Ϊ0
 The wait in the first two scenarios is normally interrupted if the process 
 catches a signal and returns from the signal handler.

 If we encounter the end of file on a descriptor, that descriptor is considered 
 readable by @select. We then call read and it returns 0��the way to signify end 
 of file on UNIX systems. 
 ---->׼����
 1 ���ڶ����������е�һ����������read���������������������������׼���õ�
 2 ����д���������е�һ����������write���������������������������׼���õ�
 3 ���쳣���������е�һ����������һ��δ���쳣״̬�������������׼���õġ�
   �쳣״̬����
   a �����������ϵ���Ĵ�������
   b �������ݰ�ģʽ��α�ն��Ϸ�����ĳЩ״̬��
 4 File descriptors for regular files always return ready for reading, writing, 
   and exception conditions.
 *******************************************************************************/
int select(int maxfdp1, fd_set *readset, fd_set *writeset, fd_set *exceptset, 
const struct timeval *timeout);

#include <sys/select.h>
/*******************************************************************************
 @select uses descriptor sets, typically an array of integers, with each bit in 
 each integer corresponding to a descriptor. For example, using 32-bit integers, 
 the first element of the array corresponds to descriptors 0 through 31, the 
 second element of the array corresponds to descriptors 32 through 63, and so on. 
 All the implementation details are irrelevant to the application and are hidden 
 in the fd_set datatype and the following four macros:
 ******************************************************************************/
int  FD_ISSET(int fd,fd_set *fdset);
void FD_CLR(int fd,fd_set *fdset);
void FD_SET(int fd,fd_set *fdset);
void FD_ZERO(fd_set *fdset); 

/*******************************************************************************
 After declaring a descriptor set, we must zero the set using FD_ZERO.Wethen set
 bits in the set for each descriptor that we��reinterested in, as in
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
  long   tv_nsec;      /* nanoseconds ���� */
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

/********** Input events and returned revents for poll ***********/
#define POLLIN       /*��ͨ�����ȼ������ݿɶ� */
#define POLLRDNORM   /*��ͨ���ݿɶ�*/
#define POLLRDBAND   /*���ȼ������ݿɶ�*/
#define POLLPRI      /*�����ȼ����ݿɶ�*/

#define POLLOUT      /*��ͨ���ݿ�д*/
#define POLLWRNORM   /*��ͨ���ݿ�д*/
#define POLLWRBAND   /*���ȼ������ݿ�д*/

#define POLLERR      /*�������󣬲�����Ϊ@events*/
#define POLLHUP      /*�������𣬲�����Ϊ@events*/
#define POLLNVAL     /*�����ֲ���һ���򿪵��ļ���������Ϊ@events*/

#define INFTIM       /*��һ����ֵ @poll�ĵ���������,��ʾ��Զ�ȴ�*/

/*******************************************************************************
 To tell the kernel which events we're interested in for each descriptor, we have
 to set the @events member of each array element to one or more of the values in 
 Figure 14.17. On return, the @revents member is set by the kernel, thereby 
 specifying which events have occurred for each descriptor. 
 ******************************************************************************/
struct pollfd 
{
    int  fd; /* file descriptor to check, or <0 to ignore */
    short  events; /* events of interest on fd POLLIN��ֵ*/
    short  revents;  /* events that occurred on fd */
};

/************************************************************************************
 @fdarray: 
    a pointer to the first element of an array of structures.Each element of the array 
    is a pollfd structure that specifies the conditions to be tested for a given 
    descriptor, fd.
 @nfds   : 
    The number of elements in the array of structures is specified by the nfds argument.
 
 @timeout: INFTIM��Զ�ȴ� 0���ȴ� ����0�ȴ�ָ����ʱ��
 @returns: 
    The return value from @poll is �C1 if an error occurred, 0 if no descriptors are 
    ready before the timer expires,otherwise it is the number of descriptors that have 
    a nonzero @revents member.

 With regard to TCP and UDP sockets, the following conditions cause @poll to return 
 the specified revent. Unfortunately, POSIX leaves many holes (i.e., optional ways 
 to return the same condition) in its definition of poll.
 1 All regular TCP data and all UDP data is considered normal.
 2 TCP's out-of-band data is considered priority band.
 3 When the read half of a TCP connection is closed (e.g., a FIN is received), this 
   is also considered normal data and a subsequent read operation will return 0.
 4 The presence of an error for a TCP connection can be considered either normal data 
   or an error (POLLERR). In either case, a subsequent read will return �C1 with errno 
   set to the appropriate value. This handles conditions such as the receipt of an RST 
   or a timeout.
 5 The availability of a new connection on a listening socket can be considered either 
   normal data or priority data. Most implementations consider this normal data.
 6 The completion of a nonblocking connect is considered to make a socket writable.
************************************************************************************/
int poll(struct pollfd fdarray[], nfds_t nfds,int timeout);


#include <sys/mman.h>
#define PROT_READ   /*Region can be read.*/
#define PROT_WRITE  /*Region can be written.*/
#define PROT_EXEC   /*Region can be executed.*/
#define PROT_NONE   /*Region cannot be accessed.*/
#define MAP_FIXED   /*����ֵ�������@addr*/
#define MAP_SHARED	/*�洢�����൱�ڶԸ��ļ���write.MAP_SHARED��MAP_PRIVATE����ָ��һ����������ͬʱָ����*/
#define MAP_PRIVATE /*��ӳ�����Ĵ洢�������´�����ӳ���ļ���һ��˽�и�����*/

/*
@addr:ӳ��洢������ʼ��ַ,0��ʾ��ϵͳ�Զ�ѡ��ҳ�߽����
@len: ӳ����ֽ���
@prot:ӳ�����ı���Ҫ��(��λ��)
      PROT_READ Region can be read.
      PROT_WRITE Region can be written.
      PROT_EXEC Region can be executed.
      PROT_NONE Region cannot be accessed.
@flag:ӳ��洢��������
      MAP_FIXED   ����ֵ�������@addr
      MAP_SHARED  �洢�����൱�ڶԸ��ļ���write.MAP_SHARED��MAP_PRIVATE����ָ��һ����������ͬʱָ����
      MAP_PRIVATE ��ӳ�����Ĵ洢�������´�����ӳ���ļ���һ��˽�и�����
@fd:  ��ӳ���ļ���������,ӳ���ļ�ǰҪ�򿪸��ļ�
@off: Ҫӳ���ֽ����ļ��е���ʼƫ����
Returns: starting address of mapped region if OK,MAP_FAILED on error*/
void *mmap(void *addr,size_t len,int prot,int flag,int fd,off_t off);





#include <sys/mman.h>
/*
function:We can change the permissions on an existing mapping by calling @mprotect
Returns: 0 if OK,-1 on error*/
int mprotect(void *addr,size_t len,int prot);



#include <sys/mman.h>
/*
flags: MS_ASYNC       MS_ASYNC��MS_SYNC����ָ��һ��
       MS_SYNC        �ȴ���ϴ���
       MS_INVALIDATE
function:�޸ĳ�ϴ���ļ��С�
Returns: 0 if OK,-1 on error*/
int msync(void *addr,size_t len,int flags);


#include <sys/mman.h>
/*
function:���ӳ��
Returns: 0 if OK,-1 on error

Amemory-mapped region is automatically unmapped when the process terminates
or  we  can  unmap  a  region  directly  by  calling  themunmapfunction.  Closing the  file
descriptor used when we mapped the region does not unmap the region.
Themunmapfunction  does  not  affect  the  object  that  was  mapped��that  is,  the  call  to
munmapdoes not cause the contents of the mapped region to be written to the disk file.
The updating of the disk file for aMAP_SHAREDregion happens automatically by the
kernel��s virtual memory algorithm sometime after we storeinto the memory-mapped
region.  Modifications to  memory  in  aMAP_PRIVATEregion  arediscarded  when  the
region is unmapped.*/
int munmap(void *addr,size_t len);

 

#include <sys/uio.h>

/************************************************************************************
 read()��write()ϵͳ����ÿ�����ļ��ͽ��̵ĵ�ַ�ռ�֮�䴫��һ�����������ݡ����ǣ�Ӧ����
 ʱҲ��Ҫ����ɢ���ڴ�ദ�ط�����������д���ļ��У����߷�֮������������£����Ҫ����
 ���ж�һƬ���������������̵Ĳ�ͬ����ʹ��read()��Ҫôһ�ν����Ƕ���һ���ϴ�Ļ�����
 �У�Ȼ�����Ƿֳ����ɲ��ָ��Ƶ���ͬ������Ҫô����read()���ɴη��������Ƕ�����ͬ��
 ��ͬ��������뽫�����в�ͬ��������ݿ�������д���ļ���Ҳ����������ƵĴ�����

 UNIX�ṩ����������������readv()��writev()������ֻ��һ��ϵͳ���þͿ���ʵ�����ļ��ͽ���
 �Ķ��������֮�䴫�����ݣ�����˶��ϵͳ���û������ݵĿ�����readv()��Ϊɢ����������
 �ļ����������������ݿ�����ڴ��ɢ�Ļ������С�writev()��Ϊ�ۼ�д�����ռ��ڴ��з�ɢ��
 ���ɻ������е�����д���ļ������������С�

 ����@fildes���ļ������֡�@iov��һ���ṹ���飬����ÿ��Ԫ��ָ���洢���е�һ����������
 ����@iovcntָ������@iov��Ԫ�ظ�����Ԫ�ظ������಻����IOV_MAX��Linux�ж���IOV_MAX��ֵ
 Ϊ1024��

 readv()��fildesָ���ļ��е����ݰ�iov[0]��iov[1]��...��iov[iovcnt�C1]�涨��˳��ͳ�
 �ȣ���ɢ�ض�������ָ���Ĵ洢��ַ�С�readv()�ķ���ֵ�Ƕ�������ֽ��������û�����ݿ�
 �����������ļ�β���䷵��ֵΪ0��

 ��������������������Ҫ����д��ĳ������ʱ��ֻ����iov����ĸ���Ԫ�ذ��������и�������
 �ĵ�ַ���䳤�ȣ�Ȼ��iov������Ԫ�ظ�����Ϊ�������ݸ�writev()����Щ���ݱ��һ��д����
************************************************************************************/

/* return: number of bytes read or written, �C1 on error */ 
ssize_t readv(int filedes, const struct iovec *iov, int iovcnt);

/*@iov:�ṹ������ָ��
  return: number of bytes read or written, �C1 on error */
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
	
