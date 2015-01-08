#include<sys/socket.h>
#include<netinet/in.h>
#include<errno.h>  /*errno*/
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"net_pub.h"


/************************************************************************************
 an asynchronous error is not returned on a UDP socket unless the socket has been connected.
 we are able to call @connect for a UDP socket. But this does not result in anything 
 like a TCP connection:There is no three-way handshake.Instead,the kernel just checks 
 for any immediate errors (e.g., an obviously unreachable destination), records the IP 
 address and port number of the peer(from the socket address structure passed to connect), 
 and returns immediately to the calling process.

 With a connected UDP socket, three things change, compared to the default unconnected 
 UDP socket:
 1 We can no longer specify the destination IP address and port for an output operation. 
   That is, we do not use @sendto, but @write or @send instead. Anything written to a 
   connected UDP socket is automatically sent to the protocol address (e.g., IP address 
   and port) specified by connect.
   Similar to TCP, we can call @sendto for a connected UDP socket, but we cannot specify 
   a destination address.The fifth argument to @sendto(the pointer to the socket address 
   structure) must be a null pointer, and the sixth argument (the size of the socket 
   address structure) should be 0. The POSIX specification states that when the fifth 
   argument is a null pointer, the sixth argument is ignored.
 2 We do not need to use @recvfrom to learn the sender of a datagram, but @read, @recv, 
   or @recvmsg instead. The only datagrams returned by the kernel for an input operation 
   on a connected UDP socket are those arriving from the protocol address specified in 
   connect. Datagrams destined to the connected UDP socket's local protocol address 
   (e.g., IP address and port) but arriving from a protocol address other than the one 
   to which the socket was connected are not passed to the connected socket. This limits 
   a connected UDP socket to exchanging datagrams with one and only one peer.
   Technically, a connected UDP socket exchanges datagrams with only one IP address, 
   because it is possible to connect to a multicast or broadcast address.
 3 Asynchronous errors are returned to the process for connected UDP sockets. The 
   corollary, as we previously described, is that unconnected UDP sockets do not receive 
   asynchronous errors.

 A process with a connected UDP socket can call connect again for that socket for one 
 of two reasons:
 1 To specify a new IP address and port
 2 To unconnect the socket
 The first case, specifying a new peer for a connected UDP socket, differs from the 
 use of connect with a TCP socket: connect can be called only one time for a TCP socket.
 To unconnect a UDP socket, we call connect but set the family member of the socket 
 address structure (sin_family for IPv4 or sin6_family for IPv6) to AF_UNSPEC. This 
 might return an error of EAFNOSUPPORT (p. 736 of TCPv2), but that is acceptable. It 
 is the process of calling connect on an already connected UDP socket that causes the 
 socket to become unconnected (pp. 787�C788 of TCPv2).
************************************************************************************/ 
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

static void sig_alrm(int signo)
{
	return;			/* just interrupt the recvfrom() */
}

/*with a call to alarm to interrupt the recvfrom if a reply is not received within five seconds.*/
void dg_cli_timeout1(FILE *fp, int sockfd, const struct sockaddr *pservaddr, socklen_t servlen)
{
	int	n;
	char	sendline[MAXLINE], recvline[MAXLINE + 1];

	signal(SIGALRM, sig_alrm);

	while (fgets(sendline, MAXLINE, fp) != NULL) {

		sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);

		alarm(5);
		if ( (n = recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL)) < 0) {
			if (errno == EINTR)
				fprintf(stderr, "socket timeout\n");
			else
				printf("recvfrom error");
		} else {
			alarm(0);
			recvline[n] = 0;	/* null terminate */
			fputs(recvline, stdout);
		}
	}
}

/************************************************************************************
 The bit corresponding to the descriptor is turned on in the read descriptor set. A 
 timeval structure is set to the number of seconds that the caller wants to wait.
 select waits for the descriptor to become readable, or for the timeout to expire. The 
 return value of this function is the return value of select: �C1 on an error, 0 if a 
 timeout occurs, or a positive value specifying the number of ready descriptors.

 This function does not perform the read operation; it just waits for the descriptor 
 to be ready for reading.Therefore,this function can be used with any type of socket, 
 TCP or UDP.It is trivial to create a similar function named writable_timeo that waits 
 for a descriptor to become writable.
************************************************************************************/
int readable_timeo(int fd, int sec)
{
	fd_set			rset;
	struct timeval	tv;

	FD_ZERO(&rset);
	FD_SET(fd, &rset);

	tv.tv_sec = sec;
	tv.tv_usec = 0;

	return(select(fd+1, &rset, NULL, NULL, &tv));
}

int Readable_timeo(int fd, int sec)
{
	int		n;

	if ( (n = readable_timeo(fd, sec)) < 0)
		printf("readable_timeo error");
	return(n);
}

/**
 * We do not call recvfrom until the function readable_timeo tells us that the descriptor 
 * is readable. This guarantees that recvfrom will not block.
**/
void dg_cli_timeout2(FILE *fp, int sockfd, const struct sockaddr *pservaddr, socklen_t servlen)
{
	int	n;
	char	sendline[MAXLINE], recvline[MAXLINE + 1];

	while (fgets(sendline, MAXLINE, fp) != NULL) {

		sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);

		if (Readable_timeo(sockfd, 5) == 0) {
			fprintf(stderr, "socket timeout\n");
		} else {
			n = recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);
			recvline[n] = 0;	/* null terminate */
			fputs(recvline, stdout);
		}
	}
}

/************************************************************************************
 We set this option once for a descriptor,specifying the timeout value, and this timeout 
 then applies to all read operations on that descriptor.The nice thing about this method 
 is that we set the option only once,compared to the previous two methods,which required 
 doing something before every operation on which we wanted to place a time limit.But this 
 socket option applies only to read operations,and the similar option SO_SNDTIMEO applies 
 only to write operations;neither socket option can be used to set a timeout for a connect.
************************************************************************************/
void dg_cli_timeout3(FILE *fp, int sockfd, const struct sockaddr *pservaddr, socklen_t servlen)
{
	int				n;
	char			sendline[MAXLINE], recvline[MAXLINE + 1];
	struct timeval	tv;

	tv.tv_sec = 5;
	tv.tv_usec = 0;
	setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

	while (fgets(sendline, MAXLINE, fp) != NULL) {

		sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);

		n = recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);
		if (n < 0) {
			if (errno == EWOULDBLOCK) {
				fprintf(stderr, "socket timeout\n");
				continue;
			} else
				printf("recvfrom error");
		}

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

