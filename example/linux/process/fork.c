#include <unistd.h>
#include<stdio.h>


int  globvar=6;/*external variable in initialized data */
char  buf[] = "a write to stdout\n";

int main(void)
{
    int  var; /* automatic variable on the stack */
    pid_t  pid;
    var = 88;
	
    if (write(STDOUT_FILENO, buf, sizeof(buf)-1) != sizeof(buf)-1)
        printf("write error");
	
    printf("before fork\n"); /* we don’t flush stdout */
	
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
/*
write:不带缓冲
printf:标准I/O库带缓冲，如果标准输出连接到终端设备，则它是行缓冲的，否则它是全缓冲的。

When we run the program interactively, we get only a single copy of the first printf line, because the standard output buffer 
is flushed by the newline. When we redirect standard output to a file, however, we get two copies of the printf line. In this 
second case, the printf before the fork is called once, but the line remains in the buffer when fork is called. This buffer is 
then copied into the child when the parent’s data space is copied to the child. Both the parent and the child now have a 
standard I/O buffer with this line in it.The second printf,right before the exit,just appends its data to the existing buffer.
When each process terminates, its copy of the buffer is finally flushed.

*/

/*
yuanxin@xw /cygdrive/g/notes/myproject/linux/process
$ ./a.exe
a write to stdout
before fork
pid = 5928, glob = 7, var = 89
pid = 6832, glob = 6, var = 88

yuanxin@xw /cygdrive/g/notes/myproject/linux/process
$ ./a.ext out.txt
-bash: ./a.ext: No such file or directory

yuanxin@xw /cygdrive/g/notes/myproject/linux/process
$ ./a.exe >out.txt

yuanxin@xw /cygdrive/g/notes/myproject/linux/process
$ cat out.txt
a write to stdout
before fork
pid = 2160, glob = 7, var = 89
before fork
pid = 840, glob = 6, var = 88

*/
