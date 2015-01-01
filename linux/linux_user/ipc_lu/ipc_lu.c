#include<unistd.h>

/*
@filedes:建立管道,并将文件描述符由参数 filedes 数组返回
returns: 0 if OK,-1 on error

错误代码: 
EMFILE 进程已用完文件描述符最大量
ENFILE 系统已无文件描述符可用。
EFAULT 参数 filedes 数组地址不合法。

1 管道只能由相关进程使用,这些相关进程的共同的祖先进程创建了管道
2 filedes[0]为管道里的读取端,filedes[1]则为管道的写入端*/
int pipe(int filedes[2]);


#include <stdio.h>
/*
@cmd:要执行的命令,如 ps
@type:打开方式
      "r":文件指针链接到@cmd的标准输出
      "w":文件指针连接到@cmd的标准输入
function:创建一个管道,调用fork产生一个子进程,关闭管道的不使用端,执行一个shell运行命令@cmd,然后等待命令终止.
returns: file pointer if OK,NULL on error

1 使用popen()创建的管道必须使用pclose()关闭
2 管道中数据流的方向是由第二个参数type控制的。此参数可以是r或者w，分别代表读或写。但不能同时为读和写。
3 在Linux 系统下，管道将会以参数type中第一个字符代表的方式打开。所以，如果你在参数type中写入rw，管道将会以读的方式打开。
*/
FILE *popen(const char *cmd,const char *type);

/*Returns: termination status of @cmd,or -1 on error*/
int pclose(FILE *fp);




#include <sys/stat.h>
/*return: 0 if OK,-1 on error*/
int mkfifo(const char *path,mode_t mode);

/*return: 0 if OK,-1 on error*/
int mkfifoat(int fd,const char *path,mode_t mode);

