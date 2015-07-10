#include<sys/socket.h>
#include<netinet/in.h>
#include<errno.h>  /*errno*/
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"net_pub.h"
#include<limits.h>		/* for OPEN_MAX */

void sig_chld(int signo);


/*-----------------------------------------------------------------------------------
 binding the wildcard address(INADDR_ANY) tells the system that we will accept a con-
 nection destined for any local interface, in case the system is multihomed.

 ----> Normal Startup
 When the server starts, it calls socket, bind, listen, and accept, blocking in the -
 call to accept. (We have not started the client yet.) Before starting the client, w-
 e run the netstat program to verify the state of the server's listening socket.

 linux % netstat -a
 Active Internet connections (servers and established)
 Proto Recv-Q Send-Q  Local Address		 Foreign Address	  State
 tcp		0	   0      *:9877                  *:*          LISTEN

 A socket is in the LISTEN state with a wildcard for the local IP address and a loca-
 l port of 9877. netstat prints an asterisk for an IP address of 0 (INADDR_ANY, the -
 wildcard) or for a port of 0.

 We then start the client on the same host, specifying the server's IP address of   -
 127.0.0.1 (the loopback address). The client calls socket and connect, the latter c-
 ausing TCP's three-way handshake to take place. When the three-way handshake comple-
 tes, connect returns in the client and accept returns in the server. The  connection 
 is established. The following steps then take place:
 1 The client calls str_cli, which will block in the call to fgets, because we have -
   not typed a line of input yet.
 2 When accept returns in the server, it calls fork and the child calls str_echo. Th-
   is function calls readline, which calls read, which blocks while waiting for a li-
   ne to be sent from the client.
 3 The server parent, on the other hand, calls accept again, and blocks while waiting 
   for the next client connection.
 
 linux % netstat -a
 Active Internet connections (servers and established)
 Proto Recv-Q Send-Q  Local Address			 Foreign Address		  State
 tcp		0	   0    local host:9877          localhost:42758		  ESTABLISHED
 tcp		0	   0    local host:42758		 localhost:9877 		  ESTABLISHED
 tcp		0	   0        *:9877 				 *:*				  LISTEN

 ----> Normal Termination
 We type in two lines, each one is echoed, and then we type our terminal EOF charact-
 er (Control-D), which terminates the client. The client's side of the connection (s-
 ince the local port is 42758) enters the TIME_WAIT state, and the listening server -
 is still waiting for another client connection. We can follow through the steps inv-
 olved in the normal termination of our client and server:
 1 When we type our EOF character, fgets returns a null pointer and the function    -
   str_cli returns. 
 2 When str_cli returns to the client main function, the latter terminates by callin-
   g exit.
 3 Part of process termination is the closing of all open descriptors, so the  client 
   socket is closed by the kernel. This sends a FIN to the server, to which the serv-
   er TCP responds with an ACK. This is the first half of the TCP connection termina-
   tion sequence. At this point, the server socket is in the CLOSE_WAIT state and the 
   client socket is in the FIN_WAIT_2 state. 
 4 When the server TCP receives the FIN, the server child is blocked in a call to   -
   readline, and readline then returns 0. This causes the str_echo function to return 
   to the server child main.
 5 The server child terminates by calling exit .
 6 All open descriptors in the server child are closed. The closing of the  connected 
   socket by the child causes the final two segments of the TCP connection terminati-
   on to take place: a FIN from the server to the client, and an ACK from the  client 
   . At this point, the connection is completely terminated. The client socket enters 
   the TIME_WAIT state.
 7 Finally, the SIGCHLD signal is sent to the parent when the server child terminate-
   s. This occurs in this example, but we do not catch the signal in our code, and t-
   he default action of the signal is to be ignored. Thus, the child enters the zomb-
   ie state. We can verify this with the ps command.
 ----------------------------------------------------------------------------------*/
int tcp_serv_fork_v1(int argc, char **argv)
{
	int					listenfd, connfd;
	pid_t				childpid;
	socklen_t			clilen;
	struct sockaddr_in	cliaddr, servaddr;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY); /* */
	servaddr.sin_port        = htons(SERV_PORT);

	Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

	Listen(listenfd, LISTENQ);

	for ( ; ; ) {
		clilen = sizeof(cliaddr);
		connfd = Accept(listenfd, (SA *) &cliaddr, &clilen);

		if ( (childpid = Fork()) == 0) {	/* child process */
			Close(listenfd);	/* close listening socket */
			str_echo(connfd);	/* process the request */
			exit(0);
		}
		Close(connfd);			/* parent closes connected socket */
	}
}


int tcp_serv_fork(int argc, char **argv)
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

/************************************************************************************
 when the parent process in our concurrent server closes the connected socket, this 
 just decrements the reference count for the descriptor.Since the reference count was 
 still greater than 0,this call to close did not initiate TCP's four-packet connection 
 termination sequence.This is the behavior we want with our concurrent server with the 
 connected socket that is shared between the parent and child.If we really want to send 
 a FIN on a TCP connection, the @shutdown function can be used instead of close.
************************************************************************************/		
		close(connfd);			/* parent closes connected socket */
	}
}



int tcp_serv_select(int argc, char **argv)
{
	int					i, maxi, maxfd, listenfd, connfd, sockfd,ret;
	int					nready, client[FD_SETSIZE];
	ssize_t				n;
	fd_set				rset, allset;
	char				buf[MAXLINE];
	socklen_t			clilen;
	struct sockaddr_in	cliaddr, servaddr;

	listenfd = socket(AF_INET, SOCK_STREAM,0);
	
	if(listenfd < 0){
	    printf("tcp server(select) error! socket fail %d",listenfd);
		return 1;
	}

	//bzero(&servaddr, sizeof(servaddr));
	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(SERV_PORT);

	ret = bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
	
	if(ret < 0){
	    printf("tcp server(select) error! bind fail %d",ret);
		return 1;
	}

	ret = listen(listenfd, 1024);

	if(ret < 0){
	    printf("tcp server(select) error! listen fail %d",ret);
		return 1;
	}

	maxfd = listenfd;			/* initialize */
	maxi = -1;					/* index into client[] array */
	
	for (i = 0; i < FD_SETSIZE; i++) {
		client[i] = -1;			/* -1 indicates available entry */
	}
	
	FD_ZERO(&allset);
	FD_SET(listenfd,&allset);

    for ( ; ; ) {
		rset = allset;		/* structure assignment */
		nready = select(maxfd+1, &rset, NULL, NULL, NULL);

		if (FD_ISSET(listenfd, &rset)) {	/* new client connection */
			clilen = sizeof(cliaddr);
			connfd = accept(listenfd,(struct sockaddr *)&cliaddr, &clilen);

			for (i = 0; i < FD_SETSIZE; i++) {
				if (client[i] < 0) {
					client[i] = connfd;	/* save descriptor */
					break;
				}
			}	
				
			if (i == FD_SETSIZE){
				printf("too many clients\r\n");
				return -1;
			}	

			FD_SET(connfd, &allset);	/* add new descriptor to set */
			
			if (connfd > maxfd)
				maxfd = connfd;			/* for select */
			
			if (i > maxi)
				maxi = i;				/* max index in client[] array */

			if (--nready <= 0)
				continue;				/* no more readable descriptors */
		}

		for (i = 0; i <= maxi; i++) {	/* check all clients for data */
			if ( (sockfd = client[i]) < 0)
				continue;
			
			if (FD_ISSET(sockfd, &rset)) {
				if ( (n = read(sockfd, buf, MAXLINE)) == 0) {
					close(sockfd);/*4connection closed by client */
					FD_CLR(sockfd, &allset);
					client[i] = -1;
				} else {
					writen(sockfd, buf, n);
				}	

				if (--nready <= 0)
					break;				/* no more readable descriptors */
			}
		}
	}
}



/* allocate an array of pollfd structures to maintain the client information */
int tcp_serv_poll(int argc, char **argv)
{
	int					i, maxi, listenfd, connfd, sockfd,temp;
	int					nready;
	ssize_t				n;
	char				buf[MAXLINE];
	socklen_t			clilen;
	struct pollfd		client[OPEN_MAX];
	struct sockaddr_in	cliaddr, servaddr;
	char strip[16] = {0};

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if(listenfd < 0)
	{
	    printf("tcp server error socket fail %d",sockfd);
		return 1;
	}

	//bzero(&servaddr, sizeof(servaddr));
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

/************************************************************************************
 We use the first entry in the @client array for the listening socket and set the 
 descriptor for the remaining entries to –1. We also set the POLLRDNORM event for this 
 descriptor, to be notified by @poll when a new connection is ready to be accepted . 
 The variable @maxi contains the largest index of the client array currently in use.
************************************************************************************/

	client[0].fd = listenfd;       /*这个作为监听套接字,监听所有连接*/
	client[0].events = POLLRDNORM;
	
	for (i = 1; i < OPEN_MAX; i++)
		client[i].fd = -1;		/* -1 indicates available entry */
	
	maxi = 0;					/* max index into client[] array */

	for ( ; ; ) 
	{
		nready = poll(client, maxi+1, -1/*INFTIM*/);

		if(nready < 0)
		{
		    printf("\r\ntcp server error poll");
			return;
		}

		if (client[0].revents & POLLRDNORM) /* new client connection */
		{	
			clilen = sizeof(cliaddr);
			
			connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen);

			if(connfd < 0)
			{			    
				printf("tcp server error accept fail %d",connfd);
				continue;
			}

			inet_ntop(AF_INET,&cliaddr.sin_addr, strip,16);
			printf("new client: %s:%d\n",strip,cliaddr.sin_port);

/************************************************************************************
 We call @poll to wait for either a new connection or data on existing connection.When 
 a new connection is accepted, we find the first available entry in the client array 
 by looking for the first one with a negative descriptor.Notice that we start the search 
 with the index of 1, since client[0] is used for the listening socket. When an available 
 entry is found, we save the descriptor and set the POLLRDNORM event.
************************************************************************************/

			for (i = 1; i < OPEN_MAX; i++)
			{
				if (client[i].fd < 0) 
				{
					client[i].fd = connfd;	/* save descriptor */
					break;
				}
			}
				
			if (i == OPEN_MAX)
				printf("too many clients");

			client[i].events = POLLRDNORM;
			
			if (i > maxi)
				maxi = i;				/* max index in client[] array */

			if (--nready <= 0)
				continue;				/* no more readable descriptors */
		}

/************************************************************************************
 The two return events that we check for are POLLRDNORM and POLLERR.The second of these 
 we did not set in the @events member because it is always returned when the condition 
 is true. The reason we check for POLLERR is because some implementations return this 
 event when an RST is received for a connection, while others just return POLLRDNORM. 
 In either case, we call read and if an error has occurred, it will return an error. 
 When an existing connection is terminated by the client, we just set the fd member to 
 –1.
************************************************************************************/


		for (i = 1; i <= maxi; i++) /* check all clients for data */
		{	
			if ( (sockfd = client[i].fd) < 0)
				continue;
			
			if (client[i].revents & (POLLRDNORM | POLLERR)) 
			{
				if ( (n = read(sockfd, buf, MAXLINE)) < 0) 
				{
					if (errno == ECONNRESET) 
					{
					    /*4connection reset by client */
						printf("client[%d] aborted connection\n", i);
						close(sockfd);
						client[i].fd = -1;
					} 
					else
					{
						printf("read error");
					}
				} 
				else if (n == 0) 
				{
						/*4connection closed by client */
					printf("client[%d] closed connection\n", i);
					close(sockfd);
					client[i].fd = -1;
				} 
				else
				{
					if(n != x_writen(sockfd, buf, n))
			            printf("\r\nstr_echo:x_writen error");
				}

				if (--nready <= 0)
					break;				/* no more readable descriptors */
			}
		}
	}
}




int main(int argc, char **argv)
{
    int ret ;

	ret = tcp_serv_select(argc,argv);

	return ret;
}
