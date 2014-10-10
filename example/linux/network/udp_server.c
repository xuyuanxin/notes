#include<sys/socket.h>
#include<netinet/in.h>
#include<errno.h>  /*errno*/
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"net_pub.h"


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

