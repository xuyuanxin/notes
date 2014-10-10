/* include fig01 */
#include<poll.h>
#include<limits.h>		/* for OPEN_MAX */
#include<sys/socket.h>
#include<netinet/in.h>
#include<errno.h>  /*errno*/
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"net_pub.h"

int main(int argc, char **argv)
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

