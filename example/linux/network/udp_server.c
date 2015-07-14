#include<sys/socket.h>
#include<netinet/in.h>
#include<errno.h>  /*errno*/
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"net_pub.h"


/*-----------------------------------------------------------------------------------
 Despite the simplicity of this function, there are numerous details to consider. 
 1 this function never terminates. Since UDP is a connectionless protocol, there 
   is nothing like an EOF as we have with TCP.
 2 this function provides an iterative server, not a concurrent server as we had with 
   TCP.There is no call to fork,so a single server process handles any and all clients. 
   In general, most TCP servers are concurrent and most UDP servers are iterative. 
   
 Each UDP socket has a receive buffer and each datagram that arrives for this  socket 
 is placed in that socket receive buffer. When the process calls recvfrom, the next -
 datagram from the buffer is returned to the process in a first-in, first-out  (FIFO) 
 order. This way, if multiple datagrams arrive for the socket before the process  can 
 read what's already queued for the socket, the arriving datagrams are just added  to 
 the socket receive buffer. But, this buffer has a limited size. We discussed this s-
 ize and how to increase it with the SO_RCVBUF socket option in Section 7.5.
 ----------------------------------------------------------------------------------*/
void dg_echo(int sockfd, struct sockaddr  *pcliaddr, socklen_t clilen)
{
	int			n;
	socklen_t	len;
	char		mesg[MAXLINE];

	for ( ; ; ) 
	{
		len = clilen;
		n = recvfrom(sockfd, mesg, MAXLINE, 0, pcliaddr, &len);

		if(n < 0)
		{
			printf("\r\nudp server error recvfrom fail!");
			continue;
		}

		if(n != sendto(sockfd, mesg, n, 0, pcliaddr, len))
			printf("\r\nudp server error sendto fail!");
	}
}


int main(int argc, char **argv)
{
	int					sockfd;
	int temp;
	struct sockaddr_in	servaddr, cliaddr;

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd < 0)
	{
	    printf("udp server error socket fail %d",sockfd);
		return 1;
	}

	//bzero(&servaddr, sizeof(servaddr));
	
	memset(&servaddr,0, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(SERV_PORT);

	temp = bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
	if(temp < 0)
	{
	    printf("udp server error bind fail %d",temp);
		return 1;
	}

	dg_echo(sockfd, (struct sockaddr *) &cliaddr, sizeof(cliaddr));
}

