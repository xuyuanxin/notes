
#include <fcntl.h>
/*******************************************************************************
 @path: 
    Òª´ò¿ª»ò´´½¨ÎÄ¼þµÄÃû×Ö
 @oflag: O_RDWR
 @mode:  S_IEXEC
    ´´½¨Ê±²Å»áÓÃµ½£¬ÓÃÓÚÖ¸¶¨ÎÄ¼þµÄ·ÃÎÊÈ¨ÏÞÎ»£¨access permission bits£©
 @function:
    ´ò¿ªÒ»¸öÎÄ¼þ(Ò²¿ÉÓÃÓÚ´´½¨ÎÄ¼þ)
 @return: 
    file descriptor if OK,-1 on error

 1 open·µ»ØµÄÎÄ¼þÃèÊö·ûÒ»¶¨ÊÇ×îÐ¡µÄÎ´ÓÃÃèÊö·ûÊýÖµ¡£
 2 @pathÎÄ¼þÃû×î´ó×Ö·û¸öÊýÊÇ NAME_MAX
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
function: ´ò¿ªÒ»¸öÎÄ¼þ²¢ÉèÖÃÆäÆ«ÒÆÁ¿
returns : new file offset if OK,-1 on error
name    : lseekÖÐµÄl±íÊ¾³¤ÕûÐÍ

@lseek only records the current file offset within the kernel¡ªit does not cause
any I/O to take place. This offset is then used by the next read or write operation.
*******************************************************************************/
off_t lseek(int fd,off_t offset,int whence);

#include <unistd.h>
/******************************************************************************
@fd :¶ÁÄÄ¸öÎÄ¼þ(ÒÑ¾­´ò¿ªÁË)
@buf:°Ñ¶ÁµÄÊý¾Ý·ÅÈëÕâ¸öbufÖÐ
@nbytes:Ï£Íû¶ÁÈ¡Êý¾ÝµÄ³¤¶È

function:Data is read from an open file with the @read function.
Returns: number of bytes read, 0 if end of file,-1 on error

1 ²ÎÊýcountÊÇÇëÇó¶ÁÈ¡µÄ×Ö½ÚÊý£¬¶ÁÉÏÀ´µÄÊý¾Ý±£´æÔÚ»º³åÇøbufÖÐ£¬Í¬Ê±ÎÄ¼þµÄµ±Ç°¶Á
  Ð´Î»ÖÃÏòºóÒÆ¡£
2 ¶Á³£¹æÎÄ¼þÊ±£¬ÔÚ¶Áµ½count¸ö×Ö½ÚÖ®Ç°ÒÑµ½´ïÎÄ¼þÄ©Î²¡£ÀýÈç£¬¾àÎÄ¼þÄ©Î²»¹ÓÐ30¸ö×Ö
  ½Ú¶øÇëÇó¶Á100¸ö×Ö½Ú£¬Ôòread·µ»Ø30£¬ÏÂ´Îread½«·µ»Ø0¡£
3 ÃæÏòÎÄ±¾µÄÌ×½Ó×Ö¶Á²Ù×÷ÖÐ,Ò»´Îread²»ÄÜ±£Ö¤¶ÁÈëÍêÕûµÄÒ»ÐÐ»òÕûÐÐ,¶ÁÍêÕûµÄÒ»ÐÐ¿É
  ÄÜÐèÒª¶Ô´Ëµ÷ÓÃread,²¢¼ì²éÆäÖÐÊÇ·ñ³öÏÖÁË»»ÐÐ·û
4 ·þÎñÆ÷ÊÕµ½FINÊ±,µÝËÍÒ»¸öEOF¸ø½ø³Ì×èÈûÖÐµÄread,ÊÕµ½ºóread·µ»ØEOF
5 POSIX.1 requires that read return -1 with errno set to EAGAIN if there is no 
  data to read from a nonblocking descriptor. 
******************************************************************************/
ssize_t read(int fd,void *buf,size_t nbytes);

/******************************************************************************
 @fd    : Ð´ÄÄ¸öÎÄ¼þ(ÒÑ¾­´ò¿ªÁË)
 @buf   : bufÖÐÊÇÒªÐ´µÄÊý¾Ý
 @nbytes: Ð´ÈëÊý¾ÝµÄ³¤¶È
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
@fd    £ºÒª¶ÁÈ¡Êý¾ÝµÄÎÄ¼þÃèÊö·û
@buf   £ºÊý¾Ý»º´æÇøÖ¸Õë£¬´æ·Å¶ÁÈ¡³öÀ´µÄÊý¾Ý
@count £º¶ÁÈ¡Êý¾ÝµÄ×Ö½ÚÊý
@offset£º¶ÁÈ¡µÄÆðÊ¼µØÖ·µÄÆ«ÒÆÁ¿£¬¶ÁÈ¡µØÖ·=ÎÄ¼þ¿ªÊ¼+offset¡£
·µ»ØÖµ£º³É¹¦£¬·µ»Ø³É¹¦¶ÁÈ¡Êý¾ÝµÄ×Ö½ÚÊý£»Ê§°Ü£¬·µ»Ø-1£»

1 Ö´ÐÐºó£¬ÎÄ¼þÆ«ÒÆÖ¸Õë²»±ä
2 Ïàµ±ÓÚË³Ðòµ÷ÓÃlseekºÍread,µ«Æä¶¨Î»ºÍ¶ÁÈ¡²Ù×÷ÊÇÔ­×ÓµÄ¡£lseekºÍreadÖ®¼äÈç¹û±»ÖÐ¶Ï
  ¿ÉÄÜÔì³ÉÎÊÌâ¡£
******************************************************************************/
ssize_t pread(int fd, void *buf, size_t nbytes, off_t offset);

/*******************************************************************************
@fd    £ºÒªÐ´ÈëÊý¾ÝµÄÎÄ¼þÃèÊö·û
@buf   £ºÊý¾Ý»º´æÇøÖ¸Õë£¬´æ·ÅÒªÐ´ÈëÎÄ¼þÖÐµÄÊý¾Ý
@count £ºÐ´ÈëÎÄ¼þÖÐµÄÊý¾ÝµÄ×Ö½ÚÊý
@offset£ºÐ´ÈëµØÖ·=ÎÄ¼þ¿ªÊ¼+offset
·µ»ØÖµ £º³É¹¦£¬·µ»ØÐ´Èëµ½ÎÄ¼þÖÐµÄ×Ö½ÚÊý£»Ê§°Ü£¬·µ»Ø-1£»

1 Ö´ÐÐºó£¬ÎÄ¼þÆ«ÒÆÖ¸Õë²»±ä
2 Ïàµ±ÓÚË³Ðòµ÷ÓÃlseekºÍwrite,µ«Æä¶¨Î»ºÍ¶ÁÈ¡²Ù×÷ÊÇÔ­×ÓµÄ¡£lseekºÍreadÖ®¼äÈç¹û±»
  ÖÐ¶Ï¿ÉÄÜÔì³ÉÎÊÌâ¡£
******************************************************************************/
ssize_t pwrite(int fd, const void *buf, size_t nbytes, off_t offset);



#include <unistd.h>
/*
 dupºÍdup2Ò²ÊÇÁ½¸ö·Ç³£ÓÐÓÃµÄµ÷ÓÃ£¬ËüÃÇµÄ×÷ÓÃ¶¼ÊÇÓÃÀ´¸´ÖÆÒ»¸öÎÄ¼þµÄÃèÊö·û¡£ËüÃÇ¾­³£ÓÃÀ´
 ÖØ¶¨Ïò½ø³ÌµÄstdin¡¢stdoutºÍstderr¡£

*/
/************************************************************************************
 ·µ»ØÖµ:
    ³É¹¦·µ»ØÐÂµÄÃèÊö·û,Ê§°Ü·µ»Ø-1
 ¹¦ÄÜ:
    ¸´ÖÆÎÄ¼þÃèÊö·û@fd¡£¸ø¸Ãº¯ÊýÒ»¸ö¼ÈÓÐµÄÃèÊö·û£¬Ëü¾Í»á·µ»ØÒ»¸öÐÂµÄÃèÊö·û£¬Õâ¸öÐÂµÄÃè
    Êö·ûÊÇ´«¸øËüµÄÃèÊö·ûµÄ¿½±´¡£ÕâÒâÎ¶×Å£¬ÕâÁ½¸öÃèÊö·û¹²ÏíÍ¬Ò»¸ö"ÎÄ¼þ±í"¡£

 1 @dup·µ»ØµÄÐÂÃèÊö·ûÒ»¶¨ÊÇµ±Ç°¿ÉÓÃÎÄ¼þÃèÊö·ûÖÐµÄ×îÐ¡ÊýÖµ
 2 ÐÂÃèÊö·ûÓë@fd¹²ÏíÒ»¸öÎÄ¼þ±íÏî(file table entry)
 3 ÐÂÃèÊö·ûµÄÖ´ÐÐÊ±¹Ø±Õ(close-on-exec)±êÖ¾×ÜÊÇÓÉ@dupº¯ÊýÇå³ý
************************************************************************************/
int dup(int fd);

/************************************************************************************
 ·µ»ØÖµ:
    ³É¹¦·µ»ØÐÂµÄÃèÊö·û,Ê§°Ü·µ»Ø-1
 ¹¦ÄÜ:
    ¸´ÖÆÎÄ¼þÃèÊö·û@fd,@fd2ÊÇÖ¸¶¨µÄÐÂÃèÊö·û.dup2º¯Êý¸údupº¯ÊýÏàËÆ£¬µ«dup2º¯ÊýÔÊÐíµ÷ÓÃ
    Õß¹æ¶¨Ò»¸öÓÐÐ§ÃèÊö·ûºÍÄ¿±êÃèÊö·ûµÄid¡£dup2º¯Êý³É¹¦·µ»ØÊ±£¬Ä¿±êÃèÊö·û£¨dup2º¯ÊýµÄ
    µÚ¶þ¸ö²ÎÊý£©½«±ä³ÉÔ´ÃèÊö·û£¨dup2º¯ÊýµÄµÚÒ»¸ö²ÎÊý£©µÄ¸´ÖÆÆ·£¬»»¾ä»°Ëµ£¬Á½¸öÎÄ¼þÃè
    Êö·ûÏÖÔÚ¶¼Ö¸ÏòÍ¬Ò»¸öÎÄ¼þ£¬²¢ÇÒÊÇº¯ÊýµÚÒ»¸ö²ÎÊýÖ¸ÏòµÄÎÄ¼þ¡£

 1 Èç¹û@fd2ÒÑ¾­´ò¿ª£¬ÔòÏÈ¹Ø±Õ¡£
 2 Èç¹û@fd==@fd2£¬²»¹Ø±Õ@fd2£¬Ö±½Ó·µ»Ø@fd2
 3 ÐÂÃèÊö·ûÓë@fd¹²ÏíÒ»¸öÎÄ¼þ±íÏî(file table entry)
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
                                 ¼ÇÂ¼Ëø
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

 ---->Ê¹ÓÃ¹æÔò
  We previously mentioned two types of locks: a shared read lock (l_type of
F_RDLCK) and an exclusive write lock (F_WRLCK). The basic rule is that any number 
of processes can have a shared read lock on a given byte, but only one process 
can have an exclusive write lock on a given byte. Furthermore, if there are one 
or more read locks on a byte, there can't be any write locks on that byte; if 
there is an exclusive write lock on a byte, there can¡¯t be any read locks on 
that byte. 

---->½¨ÒéÐÔËøºÍÇ¿ÖÆÐÔËø Advisory versus Mandatory Locking
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
ËøµÄ¼Ì³ÐÓëÊÍ·Å
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

#define FD_SETSIZE  /*@selectµÄµÚÒ»¸ö²ÎÊý£¬×î´óµÄÃèÊö·û¸öÊý£¬Í¨³£ÊÇ1024*/

struct timeval	
{
  long	 tv_sec;  /* seconds */
  long	 tv_usec; /* microseconds */
};

/*******************************************************************************
 @maxfdp1: ÃèÊö·û¸öÊý+1
 @readset: ¶ÁÃèÊö·û¼¯£¬¿ÉÒÔÎªNULL
 @readset: Ð´ÃèÊö·û¼¯£¬¿ÉÒÔÎªNULL
 @readset: Òì³£ÃèÊö·û¼¯£¬¿ÉÒÔÎªNULL
 @timeout: µÈ´ýÊ±¼ä
 function: 
    ¸æËßÄÚºË
    1 ¹ØÐÄµÄÃèÊö·û
    2 ¹ØÐÄÃèÊö·ûµÄÄÄÐ©×´Ì¬£¬±ÈÈçÊÇ·ñ¿É¶Á¡¢ÊÇ·ñ¿ÉÐ´¡¢ÃèÊö·ûµÄÒì³£×´Ì¬
    3 µÈ´ýÊ±¼ä
    ´Óselect·µ»ØÄÚºË¸æËßÎÒÃÇ
    1 ÒÑ¾­×¼±¸ºÃµÄÃèÊö·ûÊýÁ¿
    2 ¶ÔÓÚ¶Á¡¢Ð´»òÒì³£ÕâÈý¸ö×´Ì¬ÖÐµÄÃ¿Ò»¸ö£¬ÄÄÐ©ÃèÊö·ûÒÑ¾­×¼±¸ºÃ¡£
      Ê¹ÓÃÕâÐ©·µ»ØÐÅÏ¢¾Í¿ÉÒÔµ÷ÓÃÏàÓ¦µÄI/Oº¯Êý£¬²¢È·ÇÐÖªµÀº¯Êý²»»á×èÈû
 Returns: 
    positive count of ready descriptors, 0 on timeout, ¨C1 on error
    
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
 ---->µÈ´ýµÄÊ±¼ä
 1 ÓÀÔ¶µÈ´ý  timeout == NULL
 2 µÈ´ýÖ¸¶¨µÄÊ±¼ä ¾ßÌåµÄÊ±¼äÓÉtimeoutÖ¸¶¨
 3 ²»µÈ´ý  timeoutÖÐµÄÊ±¼äÎª0
 The wait in the first two scenarios is normally interrupted if the process 
 catches a signal and returns from the signal handler.

 If we encounter the end of file on a descriptor, that descriptor is considered 
 readable by @select. We then call read and it returns 0¡ªthe way to signify end 
 of file on UNIX systems. 
 ---->×¼±¸ºÃ
 1 ¶ÔÓÚ¶ÁÃèÊö·û¼¯ÖÐµÄÒ»¸öÃèÊö·ûµÄread²Ù×÷½«²»»á×èÈû£¬Ôò´ËÃèÊö·ûÊÇ×¼±¸ºÃµÄ
 2 ¶ÔÓÚÐ´ÃèÊö·û¼¯ÖÐµÄÒ»¸öÃèÊö·ûµÄwrite²Ù×÷½«²»»á×èÈû£¬Ôò´ËÃèÊö·ûÊÇ×¼±¸ºÃµÄ
 3 ÈôÒì³£ÃèÊö·û¼¯ÖÐµÄÒ»¸öÃèÊö·ûÓÐÒ»¸öÎ´¾öÒì³£×´Ì¬£¬Ôò´ËÃèÊö·ûÊÇ×¼±¸ºÃµÄ¡£
   Òì³£×´Ì¬°üÀ¨
   a ÔÚÍøÂçÁ¬½ÓÉÏµ½´ïµÄ´øÍâÊý¾Ý
   b ´¦ÓÚÊý¾Ý°üÄ£Ê½µÄÎ±ÖÕ¶ËÉÏ·¢ÉúÁËÄ³Ð©×´Ì¬¡£
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
 bits in the set for each descriptor that we¡¯reinterested in, as in
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
  long   tv_nsec;      /* nanoseconds ÄÉÃë */
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
#define POLLIN       /*ÆÕÍ¨»òÓÅÏÈ¼¶´øÊý¾Ý¿É¶Á */
#define POLLRDNORM   /*ÆÕÍ¨Êý¾Ý¿É¶Á*/
#define POLLRDBAND   /*ÓÅÏÈ¼¶´øÊý¾Ý¿É¶Á*/
#define POLLPRI      /*¸ßÓÅÏÈ¼¶Êý¾Ý¿É¶Á*/

#define POLLOUT      /*ÆÕÍ¨Êý¾Ý¿ÉÐ´*/
#define POLLWRNORM   /*ÆÕÍ¨Êý¾Ý¿ÉÐ´*/
#define POLLWRBAND   /*ÓÅÏÈ¼¶´øÊý¾Ý¿ÉÐ´*/

#define POLLERR      /*·¢Éú´íÎó£¬²»¿É×÷Îª@events*/
#define POLLHUP      /*·¢Éú¹ÒÆð£¬²»¿É×÷Îª@events*/
#define POLLNVAL     /*ÃèÊö×Ö²»ÊÇÒ»¸ö´ò¿ªµÄÎÄ¼þ£¬²»¿É×÷Îª@events*/

#define INFTIM       /*ÊÇÒ»¸ö¸ºÖµ @pollµÄµÚÈý¸ö²ÎÊý,±íÊ¾ÓÀÔ¶µÈ´ý*/

/*******************************************************************************
 To tell the kernel which events we're interested in for each descriptor, we have
 to set the @events member of each array element to one or more of the values in 
 Figure 14.17. On return, the @revents member is set by the kernel, thereby 
 specifying which events have occurred for each descriptor. 
 ******************************************************************************/
struct pollfd 
{
    int  fd; /* file descriptor to check, or <0 to ignore */
    short  events; /* events of interest on fd POLLINµÈÖµ*/
    short  revents;  /* events that occurred on fd */
};

/************************************************************************************
 @fdarray: 
    a pointer to the first element of an array of structures.Each element of the array 
    is a pollfd structure that specifies the conditions to be tested for a given 
    descriptor, fd.
 @nfds   : 
    The number of elements in the array of structures is specified by the nfds argument.
 
 @timeout: INFTIMÓÀÔ¶µÈ´ý 0²»µÈ´ý ´óÓÚ0µÈ´ýÖ¸¶¨µÄÊ±¼ä
 @returns: 
    The return value from @poll is ¨C1 if an error occurred, 0 if no descriptors are 
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
   or an error (POLLERR). In either case, a subsequent read will return ¨C1 with errno 
   set to the appropriate value. This handles conditions such as the receipt of an RST 
   or a timeout.
 5 The availability of a new connection on a listening socket can be considered either 
   normal data or priority data. Most implementations consider this normal data.
 6 The completion of a nonblocking connect is considered to make a socket writable.
************************************************************************************/
int poll(struct pollfd fdarray[], nfds_t nfds,int timeout);



#include <sys/epoll.h> 
/*-----------------------------------------------------------------------------------
 epoll is a Linux kernel system call,a scalable I/O event notification mechanism,first 
 introduced in Linux kernel 2.5.44. It is meant to replace the older POSIX select(2) 
 and poll(2) system calls,to achieve better performance in more demanding applications, 
 where the number of watched file descriptors is large (unlike the older system calls, 
 which operate in O(n) time, epoll operates in O(1) time).epoll is similar to FreeBSD's 
 kqueue, in that it operates on a configurable kernel object, exposed to user space as 
 a file descriptor of its own.

 EPOLLÊÂ¼þÓÐÁ½ÖÖÄ£ÐÍ Level Triggered (LT) ºÍ Edge Triggered (ET)£º

 LT(level triggered£¬Ë®Æ½´¥·¢Ä£Ê½)
    ÊÇÈ±Ê¡µÄ¹¤×÷·½Ê½£¬²¢ÇÒÍ¬Ê±Ö§³Ö block ºÍ non-block socket¡£ÔÚÕâÖÖ×ö·¨ÖÐ£¬ÄÚºË¸æËßÄã
    Ò»¸öÎÄ¼þÃèÊö·ûÊÇ·ñ¾ÍÐ÷ÁË£¬È»ºóÄã¿ÉÒÔ¶ÔÕâ¸ö¾ÍÐ÷µÄfd½øÐÐIO²Ù×÷¡£Èç¹ûÄã²»×÷ÈÎºÎ²Ù×÷£¬
    ÄÚºË»¹ÊÇ»á¼ÌÐøÍ¨ÖªÄãµÄ£¬ËùÒÔ£¬ÕâÖÖÄ£Ê½±à³Ì³ö´íÎó¿ÉÄÜÐÔÒªÐ¡Ò»µã¡£

 ET(edge-triggered£¬±ßÔµ´¥·¢Ä£Ê½)
    ÊÇ¸ßËÙ¹¤×÷·½Ê½£¬Ö»Ö§³Öno-block socket¡£ÔÚÕâÖÖÄ£Ê½ÏÂ£¬µ±ÃèÊö·û´ÓÎ´¾ÍÐ÷±äÎª¾ÍÐ÷Ê±£¬
    ÄÚºËÍ¨¹ýepoll¸æËßÄã¡£È»ºóËü»á¼ÙÉèÄãÖªµÀÎÄ¼þÃèÊö·ûÒÑ¾­¾ÍÐ÷£¬²¢ÇÒ²»»áÔÙÎªÄÇ¸öÎÄ¼þ
    ÃèÊö·û·¢ËÍ¸ü¶àµÄ¾ÍÐ÷Í¨Öª£¬µÈµ½ÏÂ´ÎÓÐÐÂµÄÊý¾Ý½øÀ´µÄÊ±ºò²Å»áÔÙ´Î³ö·¢¾ÍÐ÷ÊÂ¼þ¡£ 
-----------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------
 ´´½¨Ò»¸öepollµÄ¾ä±ú£¬sizeÓÃÀ´¸æËßÄÚºËÐèÒª¼àÌýµÄÊýÄ¿Ò»¹²ÓÐ¶à´ó¡£µ±´´½¨ºÃepoll¾ä±úºó£¬
 Ëü¾ÍÊÇ»áÕ¼ÓÃÒ»¸öfdÖµ£¬ÔÚlinuxÏÂÈç¹û²é¿´/proc/½ø³Ìid/fd/£¬ÊÇÄÜ¹»¿´µ½Õâ¸öfdµÄ£¬ËùÒÔÔÚ
 Ê¹ÓÃÍêepollºó£¬±ØÐëµ÷ÓÃclose() ¹Ø±Õ£¬·ñÔò¿ÉÄÜµ¼ÖÂfd±»ºÄ¾¡¡£
 @size:
    The size is not the maximum size of the backing store but just a hint to the ker-
    nel about how to dimension internal structures. Since  Linux 2.6.8, the size arg-
    ument is unused.
 @flags: 0 or EPOLL_CLOEXEC
    If flags is 0,then,other than the fact that the obsolete size argument is dropped, 
    epoll_create1() is the same as epoll_create().The following value can be included 
    in flags to obtain different behavior:EPOLL_CLOEXEC
-----------------------------------------------------------------------------------*/
int epoll_create(int size);
int epoll_create1(int flags);


/*-----------------------------------------------------------------------------------
 @epfd: epoll_create() µÄ·µ»ØÖµ¡£
 @op    EPOLL_CTL_ADD
 @fd    ÐèÒª¼àÌýµÄfd
 @event ¸æËßÄÚºËÐèÒª¼àÌýÊ²Ã´ÊÂ
-----------------------------------------------------------------------------------*/
int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);

/*-----------------------------------------------------------------------------------
 ÊÕ¼¯ÔÚepoll¼à¿ØµÄÊÂ¼þÖÐÒÑ¾­·¢ËÍµÄÊÂ¼þ¡£ ²ÎÊýeventsÊÇ·ÖÅäºÃµÄepoll_event½á¹¹ÌåÊý×é£¬
 epoll½«»á°Ñ·¢ÉúµÄÊÂ¼þ¸³Öµµ½eventsÊý×éÖÐ£¨events²»¿ÉÒÔÊÇ¿ÕÖ¸Õë£¬ÄÚºËÖ»¸ºÔð°ÑÊý¾Ý¸´ÖÆ
 µ½Õâ¸öeventsÊý×éÖÐ£¬²»»áÈ¥°ïÖúÎÒÃÇÔÚÓÃ»§Ì¬ÖÐ·ÖÅäÄÚ´æ£©¡£maxevents¸æÖ®ÄÚºËÕâ¸öevents
 ÓÐ¶à´ó£¬Õâ¸ö maxeventsµÄÖµ²»ÄÜ´óÓÚ´´½¨epoll_create()Ê±µÄsize£¬²ÎÊýtimeoutÊÇ³¬Ê±Ê±¼ä
 £¨ºÁÃë£¬0»áÁ¢¼´·µ»Ø£¬-1½«²»È·¶¨£¬Ò²ÓÐËµ·¨ËµÊÇÓÀ¾Ã×èÈû£©¡£Èç¹ûº¯Êýµ÷ÓÃ³É¹¦£¬·µ»Ø¶ÔÓ¦
 I/OÉÏÒÑ×¼±¸ºÃµÄÎÄ¼þÃèÊö·ûÊýÄ¿£¬Èç·µ»Ø0±íÊ¾ÒÑ³¬Ê±¡£
-----------------------------------------------------------------------------------*/
int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout);


#include <sys/mman.h>
/* @mmmap @prot */
#define PROT_READ   /* Region can be read. */
#define PROT_WRITE  /* Region can be written. */
#define PROT_EXEC   /* Region can be executed. */
#define PROT_NONE   /* Region cannot be accessed. */
/* @mmmap @flag */
#define MAP_FIXED   /* ·µ»ØÖµ±ØÐëµÈÓÚ@addr MAP_SHAREDºÍMAP_PRIVATE±ØÐëÖ¸¶¨Ò»¸ö£¬µ«²»ÄÜÍ¬Ê±Ö¸¶¨¡£*/
#define MAP_SHARED	/* ´æ´¢²Ù×÷Ïàµ±ÓÚ¶Ô¸ÃÎÄ¼þµÄwrite.*/
#define MAP_PRIVATE /* ¶ÔÓ³ÉäÇøµÄ´æ´¢²Ù×÷µ¼ÖÂ´´½¨¸ÃÓ³ÉäÎÄ¼þµÄÒ»¸öË½ÓÐ¸±±¾¡£*/

/*-----------------------------------------------------------------------------------
 @addr:
    Ó³Éä´æ´¢ÇøµÄÆðÊ¼µØÖ·,0±íÊ¾ÈÃÏµÍ³×Ô¶¯Ñ¡Ôñ¡£Ò³±ß½ç¶ÔÆë
 @len: 
    Ó³ÉäµÄ×Ö½ÚÊý
 @prot:
    Ó³ÉäÇøµÄ±£»¤ÒªÇó(°´Î»»ò)
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
    ±»Ó³ÉäÎÄ¼þµÄÃèÊö·û,Ó³ÉäÎÄ¼þÇ°Òª´ò¿ª¸ÃÎÄ¼þ
 @off: 
    ÒªÓ³Éä×Ö½ÚÔÚÎÄ¼þÖÐµÄÆðÊ¼Æ«ÒÆÁ¿
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
 read()ºÍwrite()ÏµÍ³µ÷ÓÃÃ¿´ÎÔÚÎÄ¼þºÍ½ø³ÌµÄµØÖ·¿Õ¼äÖ®¼ä´«ËÍÒ»¿éÁ¬ÐøµÄÊý¾Ý¡£µ«ÊÇ£¬Ó¦ÓÃÓÐ
 Ê±Ò²ÐèÒª½«·ÖÉ¢ÔÚÄÚ´æ¶à´¦µØ·½µÄÊý¾ÝÁ¬ÐøÐ´µ½ÎÄ¼þÖÐ£¬»òÕß·´Ö®¡£ÔÚÕâÖÖÇé¿öÏÂ£¬Èç¹ûÒª´ÓÎÄ
 ¼þÖÐ¶ÁÒ»Æ¬Á¬ÐøµÄÊý¾ÝÖÁ½ø³ÌµÄ²»Í¬ÇøÓò£¬Ê¹ÓÃread()ÔòÒªÃ´Ò»´Î½«ËüÃÇ¶ÁÖÁÒ»¸ö½Ï´óµÄ»º³åÇø
 ÖÐ£¬È»ºó½«ËüÃÇ·Ö³ÉÈô¸É²¿·Ö¸´ÖÆµ½²»Í¬µÄÇøÓò£¬ÒªÃ´µ÷ÓÃread()Èô¸É´Î·ÖÅú½«ËüÃÇ¶ÁÖÁ²»Í¬Çø
 Óò¡£Í¬Ñù£¬Èç¹ûÏë½«³ÌÐòÖÐ²»Í¬ÇøÓòµÄÊý¾Ý¿éÁ¬ÐøµØÐ´ÖÁÎÄ¼þ£¬Ò²±ØÐë½øÐÐÀàËÆµÄ´¦Àí¡£

 UNIXÌá¹©ÁËÁíÍâÁ½¸öº¯Êý¡ªreadv()ºÍwritev()£¬ËüÃÇÖ»ÐèÒ»´ÎÏµÍ³µ÷ÓÃ¾Í¿ÉÒÔÊµÏÖÔÚÎÄ¼þºÍ½ø³Ì
 µÄ¶à¸ö»º³åÇøÖ®¼ä´«ËÍÊý¾Ý£¬Ãâ³ýÁË¶à´ÎÏµÍ³µ÷ÓÃ»ò¸´ÖÆÊý¾ÝµÄ¿ªÏú¡£readv()³ÆÎªÉ¢²¼¶Á£¬¼´½«
 ÎÄ¼þÖÐÈô¸ÉÁ¬ÐøµÄÊý¾Ý¿é¶ÁÈëÄÚ´æ·ÖÉ¢µÄ»º³åÇøÖÐ¡£writev()³ÆÎª¾Û¼¯Ð´£¬¼´ÊÕ¼¯ÄÚ´æÖÐ·ÖÉ¢µÄ
 Èô¸É»º³åÇøÖÐµÄÊý¾ÝÐ´ÖÁÎÄ¼þµÄÁ¬ÐøÇøÓòÖÐ¡£

 ²ÎÊý@fildesÊÇÎÄ¼þÃèÊö×Ö¡£@iovÊÇÒ»¸ö½á¹¹Êý×é£¬ËüµÄÃ¿¸öÔªËØÖ¸Ã÷´æ´¢Æ÷ÖÐµÄÒ»¸ö»º³åÇø¡£
 ²ÎÊý@iovcntÖ¸³öÊý×é@iovµÄÔªËØ¸öÊý£¬ÔªËØ¸öÊýÖÁ¶à²»³¬¹ýIOV_MAX¡£LinuxÖÐ¶¨ÒåIOV_MAXµÄÖµ
 Îª1024¡£

 readv()Ôò½«fildesÖ¸¶¨ÎÄ¼þÖÐµÄÊý¾Ý°´iov[0]¡¢iov[1]¡¢...¡¢iov[iovcnt¨C1]¹æ¶¨µÄË³ÐòºÍ³¤
 ¶È£¬·ÖÉ¢µØ¶Áµ½ËüÃÇÖ¸¶¨µÄ´æ´¢µØÖ·ÖÐ¡£readv()µÄ·µ»ØÖµÊÇ¶ÁÈëµÄ×Ü×Ö½ÚÊý¡£Èç¹ûÃ»ÓÐÊý¾Ý¿É
 ¶ÁºÍÓöµ½ÁËÎÄ¼þÎ²£¬Æä·µ»ØÖµÎª0¡£

 ÓÐÁËÕâÁ½¸öº¯Êý£¬µ±ÏëÒª¼¯ÖÐÐ´³öÄ³ÕÅÁ´±íÊ±£¬Ö»ÐèÈÃiovÊý×éµÄ¸÷¸öÔªËØ°üº¬Á´±íÖÐ¸÷¸ö±íÏî
 µÄµØÖ·ºÍÆä³¤¶È£¬È»ºó½«iovºÍËüµÄÔªËØ¸öÊý×÷Îª²ÎÊý´«µÝ¸øwritev()£¬ÕâÐ©Êý¾Ý±ã¿ÉÒ»´ÎÐ´³ö¡£
************************************************************************************/

/* return: number of bytes read or written, ¨C1 on error */ 
ssize_t readv(int filedes, const struct iovec *iov, int iovcnt);

/*@iov:½á¹¹ÌåÊý×éÖ¸Õë
  return: number of bytes read or written, ¨C1 on error */
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
