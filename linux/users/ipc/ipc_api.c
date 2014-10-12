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


#include <sys/stat.h>
/*return: 0 if OK,-1 on error*/
int mkfifo(const char *path,mode_t mode);

/*return: 0 if OK,-1 on error*/
int mkfifoat(int fd,const char *path,mode_t mode);

