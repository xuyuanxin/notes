#include<sys/socket.h>	 
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>  /*errno*/
#include"net_pub.h"


/* Write "n" bytes to a descriptor. */
ssize_t x_writen(int fd, const void *vptr, size_t n)
{
	size_t		nleft;
	ssize_t		nwritten;
	const char	*ptr;

	ptr = vptr;
	nleft = n;
	
	while (nleft > 0) 
	{
		if ( (nwritten = write(fd, ptr, nleft)) <= 0) 
		{
			if (nwritten < 0 && errno == EINTR)
				nwritten = 0;		/* and call write() again */
			else
				return(-1);			/* error */
		}

		nleft -= nwritten;
		ptr   += nwritten;
	}
	return(n);
}



/*
maxlen:最多读取maxlen-1个字符,最后一个写0
function:读取一行

1 Note that our readline function calls the system's read function once for every byte of data. This is very inefficient, 
  and why we've commented the code to state it is "PAINFULLY SLOW." 
*/
ssize_t x_readline(int fd, void *vptr, size_t maxlen)
{
	ssize_t n, rc;
	char	c, *ptr;

	ptr = vptr;
	
	for (n = 1; n < maxlen; n++) 
	{
		if ( (rc = read(fd, &c, 1)) == 1) 
		{
			*ptr++ = c;
			if (c == '\n')
				break;
		} 
		else if (rc == 0) 
		{
			if (n == 1)
				return(0);	/* EOF, no data read */
			else
				break;		/* EOF, some data was read */
		} 
		else
			return(-1); /* error */
	}

	*ptr = 0;
	return(n);
}



/*@read reads data from the socket and the line is echoed back to the client by writen. 
  If the client closes the connection (the normal scenario), the receipt of the client's 
  FIN causes the child's read to return 0. This causes the @str_echo function to return, 
  which terminates the child in @main*/
void str_echo(int sockfd)
{
	ssize_t		n;
	char		buf[MAXLINE];

again:
	/*cli_close_normal 3:服务器收到FIN时,递送一个EOF给子进程阻塞中的read,收到后
	  read返回EOF,从而子进程终止*/
	while ( (n = read(sockfd, buf, MAXLINE)) > 0)
	{
		if(n != x_writen(sockfd, buf, n))
			printf("\r\nstr_echo:x_writen error");
	}

	if (n < 0 && errno == EINTR)
		goto again;
	else if (n < 0)
		printf("str_echo: read error");
}


/*******************************************************************************
 如果多个客户端同时关闭，服务器会同时收到多个SIGCHLD信号，由于UNIX信号一般不排队
 有可能服务器只处理1次SIGCHLD信号，这会在系统中留下僵尸进程。

 The correct solution is to call @waitpid instead of wait.we call @waitpid within 
 a loop, fetching the status of any of our children that have terminated. We must 
 specify the WNOHANG option: This tells @waitpid not to block if there are running 
 children that have not yet terminated.we cannot call @wait in a loop, because 
 there is no way to prevent @wait from blocking if there are running children 
 that have not yet terminated.
 
 不要用wait,防止多个信号但只处理一次

 Warning: Calling standard I/O functions such as printf in a signal handler is 
 not recommended, for reasons that we will discuss in Section 11.18. We call 
 printf here as a diagnostic tool to see when the child terminates.
 ******************************************************************************/
void sig_chld(int signo)
{
    pid_t    pid;
    int      stat;

    while ( (pid = waitpid(-1, &stat, WNOHANG)) > 0)
        printf("child %d terminated\n", pid);
	
    return;
}

