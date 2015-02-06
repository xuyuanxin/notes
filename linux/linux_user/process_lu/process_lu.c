#include <stdlib.h>
/*-----------------------------------------------------------------------------------
 @function:
    With ISO C, a process can register at least 32 functions that are automatically -
    called by @exit. These are called exit handlers and are registered by calling the 
    @atexit function.
 @Returns: 
    0 if OK, nonzero on error

 The @exit function calls these functions in reverse order of their registration. Ea-
 ch function is called as many times as it was registered.
-----------------------------------------------------------------------------------*/
int atexit(void (*func)(void));

/*-----------------------------------------------------------------------------------
 Three functions terminate a program normally : _exit and _Exit , which return to the 
 kernel immediately, and exit, which performs certain cleanup processing and then re-
 turns to the kernel.

 All three exit functions expect a single integer argument, which we call the exit s-
 tatus. Most UNIX System shells provide a way to examine the exit status of a process.
 If (a) any of these functions is called without an exit status,(b)main does a return
 without a return value, or (c)the main function is not declared to return an integer,
 the exit status of the process is undefined.However,if the return type of main is an 
 integer and main "falls off the end"(an implicit return), the exit status of the pr-
 ocess is 0. (This behavior is new with the 1999 version of the ISO C standard. Hist-
 orically , the exit status was undefined if the end of the main function was reached 
 without an explicit return statement or a call to the exit function.)

 Returning an integer value from the main function is equivalent to calling exit with 
 the same value. Thus
            exit(0);
 is the same as
            return(0);
 from the main function.

 a process can terminate normally in five ways
 1 Executing a return from the @main function. this is equivalent to calling exit.
 2 Calling the @exit function. This function is defined by ISO C and includes the ca-
   lling of all exit handlers that have been registered by calling @atexit and closi-
   ng all standard I/O streams. Because ISO C does not deal with file descriptors, m-
   ultiple processes (parents and children ), and job control, the definition of this 
   function is incomplete for a UNIX system.
 3 Calling the _exit or _Exit function. ISO C defines _Exit to provide a way for a p-
   rocess to terminate without running exit handlers or signal handlers. Whether sta-
   ndard I/O streams are flushed depends on the implementation. On UNIX systems,_Exit 
   and _exit are synonymous and do not flush standard I/O streams. The _exit function 
   is called by exit and handles the UNIX system-specific details; _exit is specified 
   by POSIX.1.
 4 Executing a return from the start routine of the last thread in the process. The -
   return value of the thread is not used as the return value of the process, however. 
   When the last thread returns from its start routine, the process exits with a ter-
   mination status of 0.  
 5 Calling the pthread_exit function from the last thread in the process. As with the 
   previous case, the exit status of the process in this situation is always 0, rega-
   rdless of the argument passed to pthread_exit. 
   
 The three forms of abnormal termination are as follows: 
 1 Calling abort. This is a special case of the next item,as it generates the SIGABRT 
   signal.
 2 When the process receives certain signals.
 3 The last thread responds to a cancellation request. By default, cancellation occu-
   rs in a deferred manner: one thread requests that another be canceled, and someti-
   me later the target thread terminates. 
   
 Regardless of how a process terminates, the same code in the kernel is eventually e-
 xecuted. This kernel code closes all the open descriptors for the process , releases 
 the memory that it was using, and so on.   
-----------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------
 @status:不为0都表示异常退出,0表示正常退出
 function:用来终止进程(要先执行一些清除操作，然后将控制权交给内核)

 1 exit()函数在调用exit系统之前要检查文件的打开情况，把文件缓冲区的内容写回文件。
 2 exit函数会调用终止处理程序(通过atexit注册),然后关闭所有标准I/O流等。
 3 exit函数是在_exit函数之上的一个封装，其会调用_exit，并在调用之前先刷新流。

 Historically, the @exit function has always performed a clean shutdown of the stand-
 ard I/O library: the @fclose function is called for all open streams, this causes a-
 ll buffered output data to be flushed (written to the file).
-----------------------------------------------------------------------------------*/
void exit(int status);

/*不清洗标准I/O流*/
void _Exit(int status);

 
#include <unistd.h>    
/*******************************************************************************
1 _exit()执行后立即返回给内核，而exit()要先执行一些清除操作，然后将控制权交给内核。
2 调用_exit函数时，其会关闭进程所有的文件描述符，清理内存以及其他一些内核清理函数，
  但不会刷新流(stdin, stdout, stderr ...).    
3 如有一些数据，认为已经写入了文件，实际上因为没有满足特定的条件，它们还只是保存
  在缓冲区内，这时用_exit()函数直接将进程关闭，缓冲区的数据就会丢失。
*******************************************************************************/
void _exit(int status); /* POSIX */ 



#include <stdlib.h>
/*-----------------------------------------------------------------------------------
 It is interesting to examine how these functions must operate when modifying the en-
 vironment list. the environment list( the array of pointers to the actual name=value 
 strings ) and the environment strings are typically stored at the top of a process's 
 memory space, above the stack. Deleting a string is simple; we just find the pointer 
 in the environment list and move all subsequent pointers down one. But adding a str-
 ing or modifying an existing string is more difficult. 

 1 If we're modifying an existing name:
   If the size of the new value is less than or equal to the size of the existing va-
   lue, we can just copy the new string over the old string.

   If the size of the new value is larger than the old one, however, we must malloc -
   to obtain room for the new string, copy the new string to this area, and then rep-
   lace the old pointer in the environment list for name with the pointer to this al-
   located area.
  
 2 If we're adding a new name,it's more complicated. First, we have to call malloc to 
   allocate room for the name=value string and copy the string to this area.
  
   Then, if it's the first time we've added a new name, we have to call malloc to ob-
   tain room for a new list of pointers. We copy the old environment list to this new 
   area and storea pointer to the name=value string at the end of this list of point-
   ers. We also storea null pointer at the end of this list, of course. Finally, we -
   set @environ to point to this new list of pointers. if the original environment l-
   ist was contained above the top of the stack, as is common, then we have moved th-
   is list of pointers to the heap. But most of the pointers in this list still point 
   to name=value strings above the top of the stack.

   If this isn't the first time we've added new strings to the environment list, then 
   we know that we've already allocated room for the list on the heap,so we just call 
   @realloc to allocate room for one more pointer . The pointer to the new name=value 
   string is stored at the end of the list (on top of the previous null pointer), fo-
   llowed by a null pointer.
-----------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------
 @Returns: 
     pointer to value associated with name, NULL if not found

 the environment strings are usually of the form: name=value. The UNIX kernel never -
 looks at these strings; their interpretation  is up to the various applications. The 
 shells, for example, use numerous environment variables. Some, such as HOME and USER,
 are set automatically at login; others are left for us to set. We normally set envi-
 ronment variables in a shell start-up file to control the shell's actions. If we set 
 the environment variable MAILPATH, for example,it tells the Bourne shell,GNU Bourne-
 again shell, and Korn shell where to look for mail. ISO C defines a function that w-
 e can use to fetch values from the environment, but this standard says that the con-
 tents of the environment areimplementation defined.

 Note that this function returns a pointer to the value of a name=value string. We s-
 hould always use  @getenv to fetch a specific value from the environment, instead of 
 accessing @environ directly.
-----------------------------------------------------------------------------------*/
char *getenv(const char *name);


/*-----------------------------------------------------------------------------------
 @Returns: 
    0 if OK, nonzero on error

 The @putenv function takes a string of the form name=value and places it in the env-
 ironment list. If name already exists, its old definition is first removed.

 Note the difference between @putenv and @setenv. Whereas @setenv must allocate memo-
 ry to create the name=value string from its arguments , @putenv is free to place the 
 string passed to idirectly into the environment. Indeed, many implementations do ex-
 actly this, so it would be an error to pass @putenv a string allocated on the stack, 
 since the memory would be reused after we return from the current function.
-----------------------------------------------------------------------------------*/
int putenv(char *str);

/*-----------------------------------------------------------------------------------
 @return: 0 if OK, -1 on error

 The @setenv function sets @name to @value.If name already exists in the environment, 
 then (a) if @rewrite is nonzero, the existing definition for name  is first removed; 
 or (b)if @rewrite is 0,an existing definition for @name is not removed, @name is not 
 set to the new @value, and no error occurs.
-----------------------------------------------------------------------------------*/
int setenv(const char *name,const char *value,int rewrite);

/*-----------------------------------------------------------------------------------
 @return: 0 if OK, -1 on error
 The  @unsetenv function removes any definition of name. It is not an error if such a 
 definition does not exist.
-----------------------------------------------------------------------------------*/
int unsetenv(const char *name);


#include <unistd.h>

/*-----------------------------------------------------------------------------------
 Besides the open files , numerous other properties of the parent areinherited by the
 child:
 > Real user ID, real group ID, effective user ID, and effective group ID
 > Supplementary group IDs
 > Process group ID
 > Session ID
 > Controlling terminal
 > The set-user-ID and set-group-ID flags
 > Current working directory
 > Root directory
 > File mode creation mask
 > Signal mask and dispositions
 > The close-on-exec flag for any open file descriptors
 > Environment
 > Attached shared memory segments
 > Memory mappings
 > Resource limits

 The differences between the parent and child are:
 > The return values from fork are different.
 > The process IDs are different.
 > The two processes have different parent process IDs : the parent process ID of the
   child is the parent; the parent process ID of the parent doesn't change.
 > The  child's tms_utime, tms_stime, tms_cutime,andtms_cstimevalues are set to 0.
 > File locks set by the parent arenot inherited by the child.
 > Pending alarms arecleared for the child.
 > The set of pending signals for the child is set to the empty set
-----------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------
 @Returns: 
     0 in child, process ID of child in parent, -1 on error
 @function:
     An existing process can create a new one by calling the @fork function . The new 
     process created by @fork  is called the child process . The two main reasons for 
     @fork to fail are (a) if too many processes are already in the system, which us-
     ually means that something else is wrong, or (b) if the total number of process-
     es for this real user ID exceeds the system's limit. CHILD_MAX specifies the ma-
     ximum number of simultaneous processes per real user ID.
 
 The reason the child's process ID is returned to the parent is that a process can h-
 ave more than one child, and there is no function that allows a process to obtain t-
 he process IDs of its children. The reason @fork returns 0 to the child is that a p-
 rocess can have only a single parent, and the child can always call @getppid to obt-
 ain the process ID of its parent. (Process ID 0 is reserved for use by the kernel,so 
 it's not possible for 0 to be the process ID of a child.)

 In general, we never know whether the child starts executing beforethe parent, or v-
 ice versa. The order depends on the scheduling algorithm used by the kernel.
 
 Both the child and the parent continue executing with the instruction that follows -
 the call to @fork. The child is a copy of the parent. For example , the child gets a 
 copy of the parent's data space, heap, and stack. Note that this is a copy for the -
 child; the parent and the child do not share these portions of memory. The parent a-
 nd the child do share the text segment, however.
 
 Modern implementations don't perform a complete copy of the parent's data, stack, a-
 nd heap, since a @fork is often followed by an @exec. Instead, a technique called
 copy-on-write (COW) is used. These regions are shared by the parent and the child a-
 nd have their protection changed by the kernel to read-only. If either process tries 
 to modify these regions, the kernel then makes a copy of that piece of memory only ,
 typically a "page" in a virtual memory system. 

 one characteristic of @fork is that all file descriptors that are open in the parent 
 are duplicated in the child. We say duplicated because it's as if the  @dup function 
 had been called for each descriptor.The parent and the child sharea file table entry 
 for every open descriptor. It is important that the parent and the child share the -
 same file offset. 


 Thereare two uses for fork:
 1 When a process wants to duplicate itself so that the parent and the child can each 
   execute different sections of code at the same time.
 2 When a process wants to execute a different program. This is common for shells. In 
   this case, the child does an exec right after it returns from the fork.
-----------------------------------------------------------------------------------*/
pid_t fork(void);

/*-----------------------------------------------------------------------------------
 @func
    The function @vfork has the same calling sequence and same return values as @fork

 The @vfork function was intended to create a new process for the purpose of executi-
 ng a new program. The @vfork function creates the new process, just like @fork, wit-
 hout copying the address space of the parent into the child, as the child won't ref-
 erence that address space; the child simply calls @exec ( or exit ) right after the 
 @vfork. Instead, the child runs in the address space of the parent until it calls e-
 ither @exec or @exit. This optimization is more efficient on some implementations of 
 the UNIX System, but leads to undefined results if the child modifies any data (exc-
 ept the variable used to hold the return value from @vfork), makes function calls,or 
 returns without calling @exec or @exit.

 Another difference between the two functions is that @vfork guarantees that the chi-
 ld runs first, until the child calls @exec or @exit.  When the child calls either of 
 these functions, the parent resumes. 

 example: vfork_eg01()
-----------------------------------------------------------------------------------*/
pid_t vfork(void);



/*-----------------------------------------------------------------------------------
 In addition to the process ID, thereare other identifiers for every process. The fo-
 llowing functions return these identifiers.
-----------------------------------------------------------------------------------*/
pid_t getpid(void);/*Returns: process ID of calling process*/
pid_t getppid(void);/*Returns: parent process ID of calling process*/
uid_t getuid(void);/*Returns: real user ID of calling process*/
uid_t geteuid(void);/*Returns: effective user ID of calling process*/
gid_t getgid(void);/*Returns: real group ID of calling process*/
gid_t getegid(void);/*Returns: effective group ID of calling process*/


#include <sys/wait.h>
/*----------------------------------------------------------------------------------- 
 Macros to examine the termination status returned by @wait and @waitpid
 进程可能:正常终止 由某个信号杀死 由作业控制停止

WIFEXITED 
    True if status was returned for a child that terminated normally.In this case, we 
    can execute WEXITSTATUS( status) to fetch the low-order 8 bits of the argument t-
    hat the child passed to exit, _exit, or _Exit.

WIFSIGNALED
    True if status was returned for a child that terminated abnormally, by receipt of 
    a signal that it didn't catch. In this case, we can execute WTERMSIG( status ) to 
    fetch the signal number that caused the termination. Additionally, some implemen-
    tations (but not the Single UNIX Specification) define the macro WCOREDUMP(status)
    that returns true if a core file of the terminated process was generated.
    
WIFSTOPPED
    True if status was returned for a child that is currently stopped. In this case, 
    we can execute WSTOPSIG( status) to fetch the signal number that caused the chil-
    d to stop

WIFCONTINUED
    True if status was returned for a child that has been continued after a job cont-
    rol stop (XSI option; waitpid only).
-----------------------------------------------------------------------------------*/
#define WIFEXITED(status)
#define WIFSIGNALED(status)
#define WIFSTOPPED(status)
#define WIFCONTINUED(status)

#define WEXITSTATUS(status)
#define WTERMSIG(status)
#define WSTOPSIG(status)
#define WCOREDUMP(status)
/*----------------------------------------------------------------------------------- 
 @statloc:
    @statloc is a pointer to an integer. If this argument is not a null pointer , the 
    termination status of the terminated process is stored in the location pointed to 
    by the argument. If we don't care about the termination status, we simply pass a 
    null pointer as this argument.
    
    Traditionally, the integer status return has been defined by  the implementation, 
    with certain bits indicating the exit status (for a normal return), other bits i-
    ndicating the signal number (for an abnormal return ), one bit indicating whether 
    a core file was generated, and so on. POSIX.1 specifies that the termination sta-
    tus is to be looked at using various macros that are defined in <sys/wait.h>.Four
    mutually exclusive macros tell us how the process terminated , and they all begin 
    with WIF. Based on which of these four macros is true, other macros are used to -
    obtain the exit status, signal number, and the like.
 @return: 
    process ID if OK, 0 (see later), or -1 on error. With @wait , the only real error 
    is if the calling process has no children. ( Another error return is possible, in 
    case the function call is interrupted by a signal.)
    
 When a process terminates, either normally or abnormally, the kernel notifies the p-
 arent by sending the SIGCHLD signal to the parent. The parent can choose to ignore -
 this signal, or it can provide a function that is called when the signal occurs: a -
 signal handler. The default action for this signal is to be ignored.For now, we need 
 to be aware that a process that calls @wait or @waitpid can
 1 Block, if all of its children are still running
 2 Return immediately with the termination status of a child, if a child has termina-
   ted and is waiting for its termination status to be fetched
 3 Return immediately with an error, if it doesn't have any child processes

 1 If the process is calling wait because it received the SIGCHLD signal, we expect - 
   @wait to return immediately. But if we call it at any random point in time, it ca-
   n block
 2 If a child has already terminated and is a zombie , @wait returns immediately with 
   that child's status. Otherwise, it blocks the caller until a child terminates . If 
   the caller blocks and has multiple children, @wait returns when one terminates. We 
   can always tell which child terminated , because the process ID is returned by the 
   function.  
----------------------------------------------------------------------------------- */
pid_t wait(int *statloc);

/*----------------------- @waitpid @options -----------------------------------------
WUNTRACED
    If the implementation supports job control , the status of any child specified by 
    @pid that has been continued after being stopped, but whose status has not yet b-
    een reported, is returned (XSI option).
WNOHANG
    The @waitpid function will not block if a child specified by @pid is not immedia-
    tely available. In this case, the return value is 0.
WUNTRACED
    If the implementation supports job control , the status of any child specified by 
    @pid that has stopped,and whose status has not been reported since it has stopped, 
    is returned. The WIFSTOPPED macro determines whether the return value corresponds 
    to a stopped child process.
-----------------------------------------------------------------------------------*/
#define WUNTRACED
#define WNOHANG
#define WUNTRACED

/*-----------------------------------------------------------------------------------
 @pid:
    pid == -1 Waits for any child process. In this respect, @waitpid is equivalent t-
              o @wait.
    pid > 0   Waits for the child whose process ID equals pid.
    pid == 0  Waits for any child whose process group ID equals that of the calling -
              process. 
    pid < -1  Waits for any child whose process group ID equals the absolute value of 
              @pid.
 @statloc:
    the same as @wait
 @options: WCONTINUED
    The @options argument lets us further control the operation of @waitpid. This ar-
    gument either is 0 or is constructed from the bitwise OR of the constants in Fig-
    ure 8.7.
 @return: 
    process ID if OK, 0 (see later), or -1 on error. it's also possible to get an er-
    ror if the specified process or process group does not exist or is not a child of 
    the calling process.

 1 The @wait function can block the caller until  a child process terminates, whereas
   @waitpid has an option that prevents it from blocking.

 example: waitpid_eg01()
-----------------------------------------------------------------------------------*/
pid_t waitpid(pid_t pid,int *statloc,int options);


#include <sys/wait.h>
/*-----------------------------------------------------------------------------------
P_PID 
    Wait for a particular process: @id contains the process ID of the child to wait 
    for.
P_PGID 
    Wait for any child process in a particular process group: @id contains the proce-
    ss group ID of the children to wait for.
P_ALL 
    Wait for any child process: @id is ignored.
-----------------------------------------------------------------------------------*/
#define P_PID 
#define P_PGID
#define P_ALL 
/*-----------------------------------------------------------------------------------
WCONTINUED 
    Wait for a process that has previously stopped and has been  continued, and whose 
    status has not yet been reported.
WEXITED 
    Wait for processes that have exited.
WNOHANG  (WithNoHang) 
    Return immediately instead of blocking if there  is no child exit status available.
WNOWAIT 
    Don't destroy the child exit status. The child's exit status  can be retrieved by 
    a subsequent call to wait, waitid, or waitpid.
WSTOPPED 
    Wait for a process that has stopped and whose status has not  yet been reported
-----------------------------------------------------------------------------------*/
#define WCONTINUED 
#define WEXITED
#define WNOHANG
#define WNOWAIT 
#define WSTOPPED 

/*-----------------------------------------------------------------------------------
 @idtype :  P_PID  P_PGID 
 @id     :
    The @id parameter is interpreted based on the value of @idtype. 
 @infop  : 
    The @infop argument is a pointer to a @siginfo structure. This structure contains
    detailed information about the signal generated that caused the state change in -
    the child process. 
 @options: WCONTINUED WEXITED WNOHANG  WNOWAIT WSTOPPED
    The @options argument is a bitwise OR of the flags shown in Figure 8.10. These f-
    lags indicate which state changes the caller is interested in. At least one of 
    WCONTINUED, WEXITED, or WSTOPPED must be specified in the @options argument.
 @Returns: 
     0 if OK, -1 on error
-----------------------------------------------------------------------------------*/
int waitid(idtype_t idtype, id_t id, siginfo_t *infop, int options);


#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/resource.h>
/*-----------------------------------------------------------------------------------
 @return: 
    process ID if OK, 0, or -1 on error
    
 Most UNIX system implementations provide two additional functions: wait3 and wait4. 
 Historically, these two variants descend from the BSD branch of the UNIX System. Th-
 e only feature provided by these two functions that isn't provided by the wait,waitid, 
 and waitpid functions is an additional argument that allows the kernel to return a -
 summary of the resources used by the terminated process and all its child processes. 
 The resource information includes such statistics as the amount of user CPU time, a-
 mount of system CPU time, number of page faults, number of signals received, and the
 like.
-----------------------------------------------------------------------------------*/
pid_t wait3(int *statloc,int options,struct rusage *rusage);
pid_t wait4(pid_t pid,int *statloc,int options,struct rusage *rusage);


#include <unistd.h>
/************************************************************************************
 We've mentioned that the process ID does not change after an exec,but the new program 
 inherits additional properties from the calling process:
 Process ID and parent process ID
 Real user ID and real group ID
 Supplementary group IDs
 Process group ID
 Session ID
 Controlling terminal
 Time left until alarm clock
 Current working directory
 Root directory
 File mode creation mask
 File locks
 Process signal mask
 Pending signals
 Resource limits
 Nice value (on XSI-conformant systems; see Section 8.16)
 Values fortms_utime,tms_stime,tms_cutime,andtms_cstime

 l: list  
 v: vector  
 p: means that the function takes a filename argument and uses the PATH environment 
    variable to find the executable file.
 l: means that the function takes a list of arguments and is mutually exclusive with 
    the letter v, 
 v: means that it takes an argv[] vector.
 e: means that the function takes an envp[] array instead of using the current environment.

 use of the @fork function is to create a new process(the child) that then causes another 
 program to be executed by calling one of the @exec functions.When a process calls one of 
 the @exec functions, that process is completely replaced by the new program, and the new 
 program starts executing at its main  function. The process ID does not change across an 
 @exec, because a new process is not created; @exec merely replaces the current process ?a 
 its text, data, heap, and stack segments ?a with a brand-new program from disk.
 There are seven different @exec functions, but we'll often simply refer to " the exec 
 function",which means that we could use any of the seven functions.These seven functions 
 round out the UNIX System process control primitives. With @fork, we can create new 
 processes; and with the @exec functions,we can initiate new programs. The @exit function 
 and the @wait functions handle termination and waiting for termination.These are the only 
 process control primitives we need. 

 @filename:
    If filename contains a slash /, it is taken as a @pathname. Otherwise, the executable 
    file is searched for in the directories specified by the PATH environment variable.
 @return:
    All seven return -1 on error, no return on success

 If either @execlp or @execvp finds an executable file using one of the path prefixes,but 
 the file isn't a machine executable  that was generated by the link editor, the function 
 assumes that the  file is a shell script and tries to invoke /bin/sh with the filenameas 
 input to the shell.

    execlp                         execl                              execle
      |                              |                                  |
      |build argv                    |build argv                        |build argv
      |                              |                                  |
     \|/    try each PATH prefix    \|/          use environ           \|/
    execvp -----------------------> execv --------------------------> execve (system call)
                                                                       /|\
                                                                        |build path from
                                                                        |/proc/self/fd
                                                                        |alias
                                                                      fexecve
************************************************************************************/
int execl(const char *pathname,const char *arg0,... /* (char *)0 */ );
int execv(const char *pathname,char *const argv[]);
int execle(const char *pathname,const char *arg0,.../* (char *)0, char *const envp[] */ );
int execve(const char *pathname,char *const argv[], char *const envp[]);
int execlp(const char *filename,const char *arg0,... /* (char *)0 */ );
int execvp(const char *filename,char *const argv[]);
int fexecve(int fd,char *const argv[], char *const envp[]);

#include <unistd.h>
/*-----------------------------------------------------------------------------------
 @function
    We can set the real user ID and effective user ID with the @setuid function. Sim-
    ilarly, we can set the real group ID and the effective group ID with the  @setgid
    function
 @return: 
    0 if OK,-1 on error
    
 In the UNIX System, privileges, are based on user and group IDs. When our programs -
 need additional privileges or need to gain access to resources that they currently -
 aren't allowed to access, they need to change their user or group ID to an ID that -
 has the appropriate privilege or access. Similarly , when our programs need to lower 
 their privileges or prevent access to certain resources, they do so by changing eit-
 her their user ID or group ID to an ID without the privilege or ability access to t-
 he resource.

 There are rules for who can change the IDs. Let's consider only the user ID for now.
 (Everything we describe for the user ID also applies to the group ID.)  Here, we are 
 assuming that _POSIX_SAVED_IDS is true. If this feature isn't provided , then delete 
 all preceding references to the saved set-user-ID
 1 If the process has superuser privileges, the @setuid function sets the real user -
   ID, effective user ID, and saved set-user-ID to @uid.
 2 If the process does not have superuser privileges, but @uid equals either the real
   user ID or the saved set-user-ID, @setuid sets only the effective user ID to @uid.
   The real user ID and the saved set-user-ID are not changed.
 3 If neither of these two conditions is true, errno is set to EPERM and -1 is retur-
   ned.

 We can make a few statements about the three user IDs that the kernel maintains.
 1 Only a superuser process can change the real user ID. Normally, the real user ID -
   is set by the login(1) program when we log in and never changes . Because login is 
   a superuser process, it sets all three user IDs when it calls @setuid.
 2 The effective user ID is set by the @exec functions only if the set-user-ID bit is 
   set for the program file. If the set-user-ID bit is not set, the @exec functions -
   leave the effective user ID as its current value . We can call @setuid at any time 
   to set the effective user ID to either the real user  ID or the saved set-user-ID.  
 3 The saved set-user-ID is copied from the effective user ID by @exec. If the file's 
   set-user-ID bit is set,this copy is saved after @exec stores the effective user ID 
   from the file's user ID. 

 +---------------------------------------------------------------------------------------------------------+
 |                            various ways these three user IDs can be changed                             |
 +---------------------------------------------------------------------------------------------------------+
 |                   |                             exec                   |          setuid(uid)           |
 | ID                |----------------------------------------------------|--------------------------------|
 |                   |  set-user-ID bit off          | set-user-ID bit on | superuser  | upprivileged user |
 |---------------------------------------------------------------------------------------------------------|
 | real user ID      | unchanged                     | unchanged          | set to uid | unchanged         |
 |---------------------------------------------------------------------------------------------------------|
 | effective user ID | unchanged                     | set form user ID   | set to uid | set to uid        |
 |                   |                               | of program file    |            |                   |
 |---------------------------------------------------------------------------------------------------------|
 | saved set-user ID | copied from effective user ID | copied form        | set to uid | unchanged         |
 |                   |                               | effective user ID  |            |                   |    
 +---------------------------------------------------------------------------------------------------------+
-----------------------------------------------------------------------------------*/
int setuid(uid_t uid);
int setgid(gid_t gid);

/*-----------------------------------------------------------------------------------
 @func
    Historically, BSD supported the swapping of the real user ID and the effective u-
    ser ID with the @setreuid function.
 @return: 
    0 if OK, -1 on error. We can supply a value of -1 for any of the arguments to in-
    dicate that the corresponding ID should remain unchanged.
-----------------------------------------------------------------------------------*/
int setreuid(uid_t ruid, uid_t euid);
int setregid(gid_t rgid, gid_t egid);

/*-----------------------------------------------------------------------------------
 @return: 
    0 if OK, -1 on error

 POSIX.1 includes the two functions @seteuid and @setegid.These functions are similar 
 to @setuid and @setgid, but only the effective user ID or effective group ID is cha-
 nged. An unprivileged user can set  its effective user ID to either its real user ID 
 or its saved set-user-ID. For a privileged user, only the effective user ID is set -
 to @uid. (This behavior differs from that of the @setuid function, which changes all 
 three user IDs.)    
-----------------------------------------------------------------------------------*/
int seteuid(uid_t uid);
int setegid(gid_t gid);

/*-----------------------------------------------------------------------------------
 @func 
    The function @getpgrp returns the process group ID of the calling process.
 @Returns: 
    process group ID of calling process

 In addition to having a process ID, each process belongs to a process group. A proc-
 ess group is a collection of one or more processes, usually associated with the same 
 job, that can receive signals from the same terminal. Each process group has a uniq-
 ue process group ID. Process group IDs are similar to process IDs: they are positive 
 integers and can be stored in a pid_t data type. 
-----------------------------------------------------------------------------------*/
pid_t getpgrp(void);

/*-----------------------------------------------------------------------------------
 @pid
    If @pid is 0, the process group ID of the calling process is returned. 
 @returns: 
    process group ID if OK,-1 on error.
 @func
    the @getpgrp function took a @pid argument and returned the process group for th-
    at process.
-----------------------------------------------------------------------------------*/
pid_t getpgid(pid_t pid);




/*-----------------------------------------------------------------------------------
  @pid @pgid
     This function sets the process group ID to @pgid in the process whose process ID 
     equals @pid. If the two arguments are equal, the process specified by @pid beco-
     mes a process group leader. If @pid is 0, the process ID of the caller  is used. 
     Also, if pgid is 0, the process ID specified by @pid is used as the process gro-
     up ID.
  @function:
     A process joins an existing process group or creates a new process group by cal-
     ling @setpgid. 
  @Returns: 
     0 if OK,-1 on error

  Each process group can have a process group leader. The leader is identified by its 
  process group ID being equal to its process ID. It is possible  for a process group 
  leader to create a process group, create processes in the group, and then terminate. 
  The process group still exists, as long as at least one process is in the group, r-
  egardless of whether the group leader terminates . This is called the process group 
  lifetime—the period of time that begins when the group is created and ends when t-
  he last remaining process leaves the group. The last remaining process in the proc-
  ess group can either terminate or enter some other process group.

 A process can set the process group ID of only itself or any of its children. Furth-
 ermore, it can't change the process group ID of one of its children after that child
 has called one of the @exec functions.
-----------------------------------------------------------------------------------*/
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
/*-----------------------------------------------------------------------------------
 @env: 
    @env is of the special type jmp_buf. This data type is some form of array that is 
    capable of holding all the information required to restore the status of the sta-
    ck to the state when we call @longjmp. Normally, the @env variable is a global v-
    ariable, since we'll need to reference it from another function.
 @Returns: 
    0 if called directly, nonzero if returning from a call to @longjmp

 In C,we can't goto a label that's in another function.Instead,we must use the @setjmp
 and @longjmp functions to perform this type of branching. As we'll see, these two f-
 unctions are useful for handling error conditions that occur in a deeply nested fun-
 ction call. we're not doing a normal C goto statement within a function; instead, we
 are branching back through the call frames to a function that is in the call path of 
 the current function.

 We call setjmp from the location that we want to return to.

 example:longjmp_eg01
-----------------------------------------------------------------------------------*/
int setjmp(jmp_buf env);

/*******************************************************************************
 @env:调用@setjmp时使用的@env
 @val:从@setjmp返回的值，入参必须大于0
 ******************************************************************************/
void longjmp(jmp_buf env,int val);

#include <sys/resource.h>
struct rlimit {
    rlim_t rlim_cur; /* soft limit: current limit */
    rlim_t rlim_max; /* hard limit: maximum value for rlim_cur */
};

/*
 @return: 0 if OK, -1 on error
*/
int getrlimit(int resource,struct rlimit *rlptr);
int setrlimit(int resource,const struct rlimit *rlptr);


