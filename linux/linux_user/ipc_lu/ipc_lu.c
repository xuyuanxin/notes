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



#include <sys/types.h>
#include <sys/stat.h>
/*-----------------------------------------------------------------------------------
 @path
    The pathname is a normal Unix pathname, and this is the name of the FIFO
 @mode
    The mode argument specifies the file permissionbits, similar to the second argum-
    ent to @open. 
 @func
 @return: 
    0 if OK,-1 on error

 The @mkfifo function implies 0_CREAT|0_EXCL. That is, it creates a new FIFO or retu-
 rns an error of EEXIST if the named FIFO already exists.

 To open an existing FIFO or create a new FIFO if it does not already exist, call @m-
 kfifo, check for an error of EEXIST, and if this occurs, call @open instead.

 Once a FIFO is created, it must  be opened  for reading or writing, using either the 
 @open function, or one of the standard I/O open functions such as @fopen.A FIFO must
 be opened either read-only or write-only. It must not be opened for read-write, bec-
 ause a FIFO is half-duplex.
 
 A write to a pipe or FIFO always appends the data, and a read always returns what'is 
 at the beginning of the pipe or FIFO. If @lseek is called for a pipe or FIFO, the e-
 rror ESPIPE is returned.

 example: fifo_writer.c 
-----------------------------------------------------------------------------------*/
int mkfifo(const char *path,mode_t mode);

/*return: 0 if OK,-1 on error*/
int mkfifoat(int fd,const char *path,mode_t mode);

