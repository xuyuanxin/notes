#include<sys/socket.h>
#include<netinet/in.h>
#include<errno.h>  /*errno*/
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"net_pub.h"
 
void dg_cli_v2(FILE *fp, int sockfd, const SA *pservaddr, socklen_t servlen)
{
	int		n;
	char	sendline[MAXLINE], recvline[MAXLINE + 1];

	connect(sockfd, (struct sockaddr *) pservaddr, servlen);

	while (fgets(sendline, MAXLINE, fp) != NULL) 
	{
		write(sockfd, sendline, strlen(sendline));

		n = read(sockfd, recvline, MAXLINE);

		recvline[n] = 0;	/* null terminate */
		fputs(recvline, stdout);
	}
}

/************************************************************************************
 the first time the process calls sendto, if the socket has not yet had a local port 
 bound to it, that is when an ephemeral port is chosen by the kernel for the socket. 
 As with TCP, the client can call bind explicitly, but this is rarely done.

 Notice that the call to @recvfrom specifies a null pointer as the fifth and sixth 
 arguments. This tells the kernel that we are not interested in knowing who sent the 
 reply. There is a risk that any process, on either the same host or some other host, 
 can send a datagram to the client's IP address and port, and that datagram will be 
 read by the client, who will think it is the server's reply. 

 If a client datagram is lost (say it is discarded by some router between the client 
 and server), the client will block forever in its call to recvfrom in the function 
 @g_cli, waiting for a server reply that will never arrive. Similarly, if the client 
 datagram arrives at the server but the server's reply is lost, the client will again 
 block forever in its call to recvfrom. A typical way to prevent this is to place a 
 timeout on the client's call to recvfrom. 
************************************************************************************/
void dg_cli(FILE *fp, int sockfd, const struct sockaddr *pservaddr, socklen_t servlen)
{
	int	n;
	char	sendline[MAXLINE], recvline[MAXLINE + 1];

	while (fgets(sendline, MAXLINE, fp) != NULL) 
	{
		sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);

		n = recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);

		recvline[n] = 0;	/* null terminate */
		fputs(recvline, stdout);
	}
}

int main(int argc, char **argv)
{
	int					sockfd;
	struct sockaddr_in	servaddr;

	if (argc != 2)
	{
		printf("usage: udpcli <IPaddress>");
		return 0;
	}

	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	
	inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	
	if(socket < 0)
	{
	    printf("\r\nudp client error socket %d",socket);
		return 0;
	}

	dg_cli(stdin, sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

	exit(0);
}

