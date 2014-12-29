/*========================= 进程的启动 =========================
---->启动例程
内核用exec函数执行C程序时，在调用main前先调用一个特殊的启动例程。
启动例程取得命令行参数和环境变量值，然后调用main函数。从main函数返回后，启动例程立即调用exit函数。

*/


/*========================= 进程的退出 =========================
---->正常退出
1 调用return，等效于exit
2 调用exit
3 调用_exit或_Exit
---->异常退出
1 调用about函数 
2 进程收到某个信号，而该信号使程序终止。 


Returning an integer value from the main function is equivalent to calling exitwith the same value. Thus
exit(0);is the same as return(0);from the main function.

*/

/*
function:With ISO C,a process can register at least 32 functions that are automatically called by
         exit.These are called exit handlers and are registered by calling the atexit function.
Returns: 0 if OK, nonzero on error

1 The exit function calls these functions in reverse order of their registration. Each function is called as many times as it was registered.*/
#include <stdlib.h>
int atexit(void (*func)(void));


#include<stdlib.h>

/*******************************************************************************
 @status:不为0都表示异常退出,0表示正常退出
 function:用来终止进程(要先执行一些清除操作，然后将控制权交给内核)

 1 exit()函数在调用exit系统之前要检查文件的打开情况，把文件缓冲区的内容写回文件。
 2 exit函数会调用终止处理程序(通过atexit注册),然后关闭所有标准I/O流等。
 3 exit函数是在_exit函数之上的一个封装，其会调用_exit，并在调用之前先刷新流。
 ******************************************************************************/
void exit(int status);

/*不清洗标准I/O流*/
void _Exit(int status);


/*******************************************************************************
1 _exit()执行后立即返回给内核，而exit()要先执行一些清除操作，然后将控制权交给内核。
2 调用_exit函数时，其会关闭进程所有的文件描述符，清理内存以及其他一些内核清理函数，
  但不会刷新流(stdin, stdout, stderr ...).    
3 如有一些数据，认为已经写入了文件，实际上因为没有满足特定的条件，它们还只是保存
  在缓冲区内，这时用_exit()函数直接将进程关闭，缓冲区的数据就会丢失。
*******************************************************************************/
 
#include <unistd.h>    /* POSIX */ 
void _exit(int status); 


#include <unistd.h>

/*
@fork时，子进程会进程父进程的
 打开的文件:共享文件表(file table entry)
?Real user ID, real group ID, effective user ID, and effective group ID
?Supplementary group IDs
?Process group ID
?Session ID
?Controlling terminal
?The set-user-ID and set-group-ID flags
?Current working directory
?Root directory
?File mode creation mask
?Signal mask and dispositions
?The close-on-exec flag for any open file descriptors
?Environment
?Attached shared memory segments
?Memory mappings
?Resource limits

 The differences between the parent and child are:
 The return values from fork are different.
 The process IDs are different.
?The two processes have different parent process IDs: the parent process ID of the
child is the parent; the parent process ID of the parent doesn’t change.
?The  child’stms_utime, tms_stime, tms_cutime,andtms_cstimevalues
areset to 0 (these times arediscussed in Section 8.17).
?File locks set by the parent arenot inherited by the child.
?Pending alarms arecleared for the child.
?The set of pending signals for the child is set to the empty set*/
/*******************************************************************************
 Returns: 0 in child, process ID of child in parent,-1 on error
 1 The new process created by @fork is called the child process.This function is 
   called once but returns twice. 子进程返回0，父进程返回子进程的进程ID
 2 父子进程共享代码段，但各有自己的数据段、堆和栈空间。
 3 父子进程的执行顺序取决于调度算法
 4 Modern implementations don't perform a complete copy of the parent's data, stack,
   and heap, since a @fork is often followed by an @exec. Instead, a technique 
   called copy-on-write (COW) is used. These regions are shared by the parent and 
   the child and have their protection changed by the kernel to read-only. If 
   either process tries to modify these regions, the kernel then makes a copy 
   of that piece of memory only, typically a "page" in a virtual memory system. 
 ******************************************************************************/
pid_t fork(void);

/*******************************************************************************
 vfork用于创建一个新进程，而该新进程的目的是exec一个新进程。vfork保证子进程先运
 行，在调用exec或_exit之前与父进程数据是共享的,在它调用exec或_exit之后父进程才
 可能被调度运行。
 ******************************************************************************/
pid_t vfork(void);



#include <unistd.h>
pid_t getpid(void);/*Returns: process ID of calling process*/
pid_t getppid(void);/*Returns: parent process ID of calling process*/
uid_t getuid(void);/*Returns: real user ID of calling process*/
uid_t geteuid(void);/*Returns: effective user ID of calling process*/
gid_t getgid(void);/*Returns: real group ID of calling process*/
gid_t getegid(void);/*Returns: effective group ID of calling process*/


#include <sys/wait.h>

/*检查wait waitpid终止状态的宏 进程可能:正常终止 由某个信号杀死 由作业控制停止*/
#define WEXITSTATUS(status) /*WExitStatus to fetch the low-order 8 bits of the 
argument that the child passed to exit,_exit,or_Exit*/
#define WTERMSIG(status)  /*wtermsig to fetch the signal number that caused the 
termination.*/
#define WSTOPSIG(status)  /*Wstopsig to fetch the signal number that caused the 
child to stop*/
#define WIFEXITED(status)   /*WIFexited 正常终止则为真。正常终止时可以执行
WEXITSTATUS()*/
#define WIFSIGNALED(status) /*WIFsignaled 异常终止则为真(接收一个不捕获的信号)。
此时可以调用WTERMSIG()获取子进程终止的信号编号*/
#define WIFSTOPPED(status)  /*WIFstopped True if status was returned for a child 
that is currently stopped.此时可以调用WSTOPSIG()获取使子进程暂停的信号编号*/
#define WIFCONTINUED(status) /* True if status was returned for a child that has 
been continued after a job control stop (XSI option; waitpid only).*/



/*******************************************************************************
 @statloc:返回进程的退出状态(可以传NULL)，其中某些位表示退出状态(正常返回)，其他
          位则指示信号编号(异常返回)
 return: process ID(退出进程) if OK, 0 (see later), or -1 on error
 1 如果所有子进程都还在运行，则阻塞，有一个终止wait就返回。
 2 如果它没有任何子进程，则立即出错返回。这是唯一的出错原因
 ******************************************************************************/
pid_t wait(int *statloc);


#define WUNTRACED
/*******************************************************************************
 @pid: pid == -1 等待任意子进程
       pid > 0   等待其进程ID与pid相等的子进程
       pid == 0  等待其组ID等于进程组ID的任意子进程
       pid < -1  等待其组ID等于pid绝对值的任意子进程
 @statloc:返回进程的退出状态
 @options:可以为 0 或可以用"|"运算符把它们连接起来使用,如 WNOHANG | WUNTRACED
      0         等待
      WNOHANG   若pid指定的子进程没有结束，则waitpid()函数返回0，不予以等待。若结
                束，则返回该子进程的ID。
      WUNTRACED 若子进程进入暂停状态，则马上返回，但子进程的结束状态不予以理会。
                WIFSTOPPED(status)宏确定返回值是否对应与一个暂停子进程。
                
 return: process ID if OK, 0 (see later), or -1 on error

 1 如果指定的进程或进程组不存在，或者参数pid指定的进程不是调用进程的子进程则都将出错
 ******************************************************************************/
pid_t waitpid(pid_t pid,int *statloc,int options);


#include <sys/wait.h>
#define P_PID /*Wait for a particular process: id contains the process ID of the 
child to wait for.*/
#define P_PGID /*Wait for any child process in a particular process group: id 
contains the process group ID of the children to wait for.*/
#define P_ALL /*Wait for any child process: id is ignored*/

#define WCONTINUED /*Wait for a process that has previously stopped and has been 
continued, and whose status has not yet been reported.*/
#define WEXITED /*Wait for processes that have exited.*/

#define WNOHANG /* (WithNoHang) Return immediately instead of blocking if there 
is no child exit status available.*/

#define WNOWAIT /*Don't destroy the child exit status. The child's exit status 
can be retrieved by a subsequent call to wait, waitid, or waitpid.*/
#define WSTOPPED /*Wait for a process that has stopped and whose status has not 
yet been reported*/

/*******************************************************************************
 @idtype : 参数@id的类型，P_PID P_PGID P_ALL
 @id     :
 @infop  : 
 @options: WCONTINUED WEXITED WNOHANG  WNOWAIT WSTOPPED
 Returns: 0 if OK, -1 on error
 ******************************************************************************/
int waitid(idtype_t idtype, id_t id, siginfo_t *infop, int options);


#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/resource.h>
/*return: process ID if OK, 0, or -1 on error*/
pid_t wait3(int *statloc,int options,struct rusage *rusage);

/*return: process ID if OK, 0, or -1 on error*/
pid_t wait4(pid_t pid,int *statloc,int options,struct rusage *rusage);


#include <unistd.h>
/*
We’ve mentioned that the process ID does not change after an exec,but the new
program inherits additional properties from the calling process:
?Process ID and parent process ID
?Real user ID and real group ID
?Supplementary group IDs
?Process group ID
?Session ID
?Controlling terminal
?Time left until alarm clock
?Current working directory
?Root directory
?File mode creation mask
?File locks
?Process signal mask
?Pending signals
?Resource limits
?Nice value (on XSI-conformant systems; see Section 8.16)
?Values fortms_utime,tms_stime,tms_cutime,andtms_cstime

l:list  v:vector  
p: means that the function takes a filename argument and uses the PATH environment variable to find the executable file.
l: means that the function takes a list of arguments and is mutually exclusive with the letter v, 
v: means that it takes an argv[] vector.
e: means that the function takes an envp[] array instead of using the current environment.

@filename:If filename contains a slash /, it is taken as a pathname.Otherwise, the executable file is searched for 
          in the directories specified by the PATH environment variable

All seven return:-1 on error, no return on success


The process ID does not change across an exec,because a new process is not created; exec merely replaces the current process
—its text, data, heap,  and  stack segments — with a brand-new program from disk.*/
int execl(const char *pathname,const char *arg0,... /* (char *)0 */ );
int execv(const char *pathname,char *const argv[]);
int execle(const char *pathname,const char *arg0,.../* (char *)0, char *const envp[] */ );
int execve(const char *pathname,char *const argv[], char *const envp[]);

/*If either execlp or execvp finds an executable file using one of the path prefixes,but the file isn't a machine executable 
  that was generated by the link editor,the function assumes that the file is a shell script and tries to invoke /bin/sh with 
  the filenameas input to the shell.*/
int execlp(const char *filename,const char *arg0,... /* (char *)0 */ );
int execvp(const char *filename,char *const argv[]);
int fexecve(int fd,char *const argv[], char *const envp[]);

#include <unistd.h>
/*
function:
return: 0 if OK,-1 on error

---->修改规则
1 若进程具有超级用户权限，则setuid函数将实际用户ID、有效用户ID,以及保存的设置用户ID设置为uid
2 If the process does not have superuser privileges, but uid equals either the real user ID or the saved set-user-ID,
  setuid sets only the effective user ID to uid. The real user ID and the saved set-user-ID are not changed.
3 If neither of these two conditions is true,errno is set to EPERM and -1 is returned.

We can make a few statements about the three user IDs that the kernel maintains.
1 Only a superuser process can change the real user ID. Normally,the real user ID is set by the login(1) program when we log in and never changes. 
  Because login is a superuser process, it sets all three user IDs when it call ssetuid.
2 The effective user ID is set by the exec functions only if the set-user-ID bit is set for the program file. 
  If the set-user-ID bit is not set, the exec functions leave the effective user ID as its current value. 
  We can call setuid at any time to set the effective user ID to either the real user ID or the saved set-user-ID.  
  Naturally, we can’t set the effective user ID to any random value.
3 The saved set-user-ID is copied from the effective user ID by exec.If the file’s set-user-ID bit is set, this copy is saved after exec stores 
  the effective user ID from the file's user ID.*/
int setuid(uid_t uid);
int setgid(gid_t gid);



#include <unistd.h>
/*Returns: process group ID of calling process*/
pid_t getpgrp(void);

/*
  returns: process group ID if OK,-1 on error

  1 getpgid(0)==getpgrp()*/
pid_t getpgid(pid_t pid);

/*
  function:A process joins an existing process group or creates a new process group by calling @setpgid
  Returns: 0 if OK,-1 on error

  1 把进程@pid的进程组ID设置成@pgid,如果@pid==@pgid,则进程@pid变成进程组组长.
  2 if @pid==0  使用调用者的进程ID
  3 if @pgid==0 则进程@pid的进程ID作为进程组ID
  4 一个进程只能为自己或它的子进程设置进程组ID
  5 子进程调用exec系列函数后,进程组不能改变*/
int setpgid(pid_t pid,pid_t pgid);

/*
function:A process establishes a new session by calling the @setsid function.
returns: process group ID if OK,-1 on error

1 如果调用该函数的进程是组长进程,则函数返回出错.
2 如果不是组长进程,则@setsid创建一个新会话.
2.1 The process becomes the session leader of this new session. (A session leader is
    the process that creates a session.) The process is the only process in this new session.
2.2 The process becomes the process group leader of a new process group. The new
    process group ID is the process ID of the calling process.
2.3 The process has no controlling terminal. If the process had a controlling terminal before calling
    @setsid,that association is broken.*/
pid_t setsid(void);

/*
returns: session leader's process group ID if OK,-1 on error
1 If @pid is 0, @getsid returns the process group ID of the calling process's session leader.
2 For security reasons, some implementations may restrict the calling process from obtaining the 
  process group ID of the session leader if @pid doesn't belong to the same session as the caller.*/
pid_t getsid(pid_t pid);





#include <setjmp.h>
/*******************************************************************************
 @env: 一般是个全局变量，存储栈信息。将来调用@longjmp时用来恢复栈。
 Returns: 0 if called directly,nonzero if returning from a call to @longjmp
 ******************************************************************************/
int setjmp(jmp_buf env);

/*******************************************************************************
 @env:调用@setjmp时使用的@env
 @val:从@setjmp返回的值，入参必须大于0
 ******************************************************************************/
void longjmp(jmp_buf env,int val);

