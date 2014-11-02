#include <unistd.h>
#include<stdio.h>
#include<stdlib.h>


int  globvar=6;/*external variable in initialized data */
char  buf[] = "a write to stdout\n";

int main(void)
{
    int  var; /* automatic variable on the stack */
    pid_t  pid;
    var = 88;
	
    if (write(STDOUT_FILENO, buf, sizeof(buf)-1) != sizeof(buf)-1)
        printf("write error");
	
    printf("before fork "); 

    //printf("before fork \n");
	
    if ((pid = fork()) < 0) 
	{
        printf("fork error");
    }
	else if (pid == 0) 
	{ /* child */
        globvar++;  /* modify variables */
        var++;
    }
	else 
    {
        sleep(2);  /* parent */
    }
	
    printf("pid = %ld, glob = %d, var = %d\n", (long)getpid(), globvar,var);
    exit(0);
}

/*******************************************************************************
write:不带缓冲
printf:标准I/O库带缓冲，如果标准输出连接到终端设备，则它是行缓冲的，否则它是全缓冲的。

printf("before fork\n");
1 输出到终端时(此时printf是行缓冲的)
  调用前已经刷新缓冲区，所以子进程不会输出"before fork"
2 输出到文件(此时printf是全缓冲的)
  虽然有\n，由于此时是全缓冲的，所以子进程也会输出。




*/

/*
printf("before fork\n");的输出情况

$ ./a.exe
a write to stdout
before fork
pid = 5928, glob = 7, var = 89
pid = 6832, glob = 6, var = 88


$ ./a.exe >out.txt
$ cat out.txt
a write to stdout
before fork
pid = 2160, glob = 7, var = 89
before fork
pid = 840, glob = 6, var = 88

*/
