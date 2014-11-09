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

		/*处理系统调用被信号中断的情况*/
		if ( (connfd = accept (listenfd, (struct sockaddr *) &cliaddr, &clilen)) < 0) 
		{
			   if (errno == EINTR)
				   continue;		  /* back to for() */
			   else
			   {
				   printf("tcp server error accept fail %d",connfd);
				   return 1;
			   }
		}

        childpid = fork();
		
		if ( childpid == 0) /* child process */
		{	
			close(listenfd);	/* close listening socket */
			str_echo(connfd);	/* process the request */

			
			/*正常终止 4:给父进程发送SIGCHLD信号*/
			exit(0);
		}
		else if(childpid > 0)
		{
		    
		}
		
		close(connfd);			/* parent closes connected socket */
	}
}

