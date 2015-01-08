#include<sys/socket.h>
#include<netinet/in.h>
#include<errno.h>  /*errno*/
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"net_pub.h"


int tcp_udp_serv(int argc, char **argv)
{
}

int main(int argc, char **argv)
{
	int					listenfd, connfd, udpfd, nready, maxfdp1,tmp;
	char				mesg[MAXLINE];
	pid_t				childpid;
	fd_set				rset;
	ssize_t				n;
	socklen_t			len;
	const int			on = 1;
	struct sockaddr_in	cliaddr, servaddr;
	void				sig_chld(int);

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if(listenfd < 0)
	{
	    printf("tcpudp server error socket fail %d",listenfd);
		return 1;
	}

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(SERV_PORT);

	tmp = setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
	if(tmp < 0)
	{
	    printf("\r\ntcpudp server error setsockopt fail %d",tmp);
		return 1;
	}
	
	tmp = bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
	if(tmp < 0)
	{
	    printf("tcpudp server error bind fail %d\r\n",tmp);
		return 1;
	}

	tmp = listen(listenfd, 1024);
	if(tmp < 0)
	{
	    printf("tcpudp server error listen fail %d\r\n",tmp);
		return 1;
	}
	
	udpfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(udpfd < 0)
	{
	    printf("tcpudp server error setsockopt fail %d\r\n",udpfd);
		return 1;
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(SERV_PORT);

	tmp = bind(udpfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
	if(tmp < 0)
	{
	    printf("tcpudp server error bind2 fail %d\r\n",tmp);
		return 1;
	}
	
	if(SIG_ERR == signal(SIGCHLD, sig_chld) )	/* must call waitpid() */
	{
	    return 1;
	}

	FD_ZERO(&rset);
	maxfdp1 = max(listenfd, udpfd) + 1;
	
	for ( ; ; ) 
	{
		FD_SET(listenfd, &rset);
		FD_SET(udpfd, &rset);
		if ( (nready = select(maxfdp1, &rset, NULL, NULL, NULL)) < 0) 
		{
			if (errno == EINTR)
				continue;		/* back to for() */
			else
				printf("select error");
		}

		if (FD_ISSET(listenfd, &rset)) {
			len = sizeof(cliaddr);
			connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &len);
	
			if ( (childpid = fork()) == 0) {	/* child process */
				close(listenfd);	/* close listening socket */
				str_echo(connfd);	/* process the request */
				exit(0);
			}
			close(connfd);			/* parent closes connected socket */
		}

		if (FD_ISSET(udpfd, &rset)) {
			len = sizeof(cliaddr);
			n = recvfrom(udpfd, mesg, MAXLINE, 0, (struct sockaddr *) &cliaddr, &len);

			sendto(udpfd, mesg, n, 0, (struct sockaddr *) &cliaddr, len);
		}
	}
}

