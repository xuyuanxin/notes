#include<unistd.h>

/*-----------------------------------------------------------------------------------
 @fd:
    Two file descriptors are returned through the fd argument: fd[0] is open for re-
    ading, and fd[1] is open for writing.
 @returns: 
    0 if OK,-1 on error

 错误代码: 
 EMFILE 进程已用完文件描述符最大量
 ENFILE 系统已无文件描述符可用。
 EFAULT 参数 filedes 数组地址不合法。

1 Historically, they have been half duplex (i.e., data flows in only one direction). 
  Some systems now provide full-duplex pipes, but for maximum portability, we should 
  never assume that this is the case.
 2 Pipes can be used only between processes that have a common ancestor. Normally, a 
   pipe is created by a process, that process calls fork, and the pipe is used betw-
   een the parent and the child
-----------------------------------------------------------------------------------*/
int pipe(int fd[2]);


#include <stdio.h>
/*-----------------------------------------------------------------------------------
 @cmd:
    要执行的命令,如 ps ls
 @type:打开方式
    "r":文件指针链接到@cmd的标准输出
    "w":文件指针连接到@cmd的标准输入
 @function:
    creating a pipe, forking a child, closing the unused ends of the pipe, executing 
    a shell to run the command, and waiting for the command to terminate.
 @returns: 
    file pointer if OK, NULL on error

 The function @popen does a @fork and @exec to execute the @cmd and returns a stand-
 ard I/O file pointer. If @type is "r" , the file pointer is connected to the stand-
 ard output of @cmd. If @type is "w" , the file pointer is connected to the standar-
 d input of @cmd.

 1 使用popen()创建的管道必须使用pclose()关闭
 2 管道中数据流的方向是由第二个参数@type控制的。此参数可以是r或者w，分别代表读或写。
   但不能同时为读和写。
 3 在Linux 系统下，管道将会以参数@type中第一个字符代表的方式打开。所以，如果你在参数
   @type中写入rw，管道将会以读的方式打开。
-----------------------------------------------------------------------------------*/
FILE *popen(const char *cmd,const char *type);

/*-----------------------------------------------------------------------------------
 @func:
    closes the standard I/O stream, waits for  the command to terminate, and  returns 
    the termination status of the shell.
 @returns: 
    termination status of @cmd, or -1 on error. If the shell cannot be  executed, the 
    termination status returned by @pclose is as if the shell had executed exit(127).
-----------------------------------------------------------------------------------*/
int pclose(FILE *fp);




#include <sys/stat.h>
/*-----------------------------------------------------------------------------------
 @func
    该函数的第一个参数是一个普通的路径名，也就是创建后FIFO的名字。第二个参数与打开普
    通文件的open()函数中的mode 参数相同。 如果mkfifo的第一个参数是一个已经存在的路径
    名时，会返回EEXIST错误，所以一般典型的调用代码首先会检查是否返回该错误，如果确实
    返回该错误，那么只要调用打开FIFO的函数就可以了。一般文件的I/O函数都可以用于FIFO，
    如close、read、write等等。
 @return: 
    0 if OK,-1 on error

 mkfifo函数已经隐含指定O_CREAT | O_EXCL,也就是说,要么创建一个新的FIFO，要么返回EEXIST
 错误(文件已经存在)
-----------------------------------------------------------------------------------*/
int mkfifo(const char *path,mode_t mode);

/*return: 0 if OK,-1 on error*/
int mkfifoat(int fd,const char *path,mode_t mode);

