#include<sys/socket.h>
#include<netinet/in.h>
#include<errno.h>  /*errno*/
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"net_pub.h"

void sig_chld(int signo);

int main(int argc, char **argv)
{
	int					listenfd, connfd;
	int                 temp;
	pid_t				childpid;
	socklen_t			clilen;
	struct sockaddr_in	cliaddr, servaddr;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	
	if(listenfd < 0)
	{
	    printf("tcp server error socket fail %d",listenfd);
		return 1;
	}

	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(SERV_PORT);

    /*The local port (the server's well-known port) is specified by @bind. 
       Normally, the server also specifies the wildcard IP address in this call. 
       If the server binds the wildcard IP address on a multihomed host, it can 
       determine the local IP address by calling @getsockname after the connection 
       is established. The two foreign values are returned to the server by @accept*/
	temp = bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

	if(temp < 0)
	{
	    printf("tcp server error bind fail %d",temp);
		return 1;
	}	


	temp = listen(listenfd,1024);

	if(temp < 0)
	{
	    printf("tcp server error listen fail %d",temp);
		return 1;
	}	

	signal(SIGCHLD, sig_chld); /* must call waitpid() */

	for ( ; ; ) 
	{
		clilen = sizeof(cliaddr);
		
		/*客户端connect发起三次握手,connect收到ack后返回(第二次握手),而服务器accept要第三个握手才返回*/

		/*signal was caught by the parent(例如子进程终止) while the parent was 
		  blocked in a slow system call (accept), the kernel causes the accept 
		  to return an error of EINTR (interrupted system call). 

		  What we are doing in this piece of code is restarting the interrupted 
		  system call. This is fine for accept, along with functions such as read, 
		  write, select, and open. But there is one function that we cannot restart: connect. 
		  If this function returns EINTR, we cannot call it again, as doing so will 
		  return an immediate error. When connect is interrupted by a caught signal 
		  and is not automatically restarted, we must call select to wait for the 
		  connection to complete, as we will describe in Section 16.3.*/
		if ( (connfd = accept (listenfd, (struct sockaddr *) &cliaddr, &clilen)) < 0) 
		{
			   if (errno == EINTR){
				   continue;		  /* back to for() */
			   }else {
				   printf("tcp server error accept fail %d",connfd);
				   return 1;
			   }
		}

        childpid = fork();
		
		if ( childpid == 0) /* child process */
		{	
			close(listenfd);	/* close listening socket */
			str_echo(connfd);	/* process the request */
			
           /*cli_close_normal 4:All open descriptors in the server child are closed. 
              The closing of the connected socket by the child causes the final two 
              segments of the TCP connection termination to take place: a FIN from the 
              server to the client, and an ACK from the client. At this point, the 
              connection is completely terminated. The client socket enters the TIME_WAIT 
              state. 给父进程发送SIGCHLD信号，如果父进程不处理这个信号，默认处理是父进程
              忽略这个信号，这样的话子进程进入僵死状态*/
			exit(0);/* */
		}
		else if(childpid > 0)
		{
		    
		}
		
		close(connfd);			/* parent closes connected socket */
	}
}

