
/*
 The first three arguments are the normal arguments to @connect,and the fourth argument 
 is the number of seconds to wait for the connection to complete.A value of 0 implies no 
 timeout on the select;hence,the kernel will use its normal TCP connection establishment 
 timeout.

 
 Berkeley-derived implementations (and POSIX) have the following two rules regarding 
 @select and nonblocking @connects:
 1 When the connection completes successfully, the descriptor becomes writable.
 2 When the connection establishment encounters an error, the descriptor becomes both 
   readable and writable.
 These two rules regarding select fall out from our rules in Section 6.3 about the 
 conditions that make a descriptor ready.A TCP socket is writable if there is available 
 space in the send buffer (which will always be the case for a connecting socket since 
 we have not yet written anything to the socket) and the socket is connected (which 
 occurs only when the three-way handshake completes). A pending error causes a socket 
 to be both readable and writable.
*/
int connect_nonb(int sockfd, const struct sockaddr *saptr, socklen_t salen, int nsec)
{
	int				flags, n, error;
	socklen_t		len;
	fd_set			rset, wset;
	struct timeval	tval;

	flags = fcntl(sockfd, F_GETFL, 0);
	fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);

	error = 0;

/*
 When a TCP socket is set to nonblocking and then @connect is called, connect returns 
 immediately with an error of EINPROGRESS but the TCP three-way handshake continues. 
*/	
	if ( (n = connect(sockfd, saptr, salen)) < 0)
		if (errno != EINPROGRESS)
			return(-1);
/* 
 Do whatever we want while the connect is taking place.At this point, we can do whatever 
 we want while we wait for the connection to complete.

 If the nonblocking connect returns 0, the connection is complete. As we have said, 
 this can occur when the server is on the same host as the client.
*/
	if (n == 0)
		goto done;	/* connect completed immediately */

	FD_ZERO(&rset);
	FD_SET(sockfd, &rset);
	wset = rset;
	tval.tv_sec = nsec;
	tval.tv_usec = 0;

/*
 If select returns 0, the timer expired, and we return ETIMEDOUT to the caller.We also 
 close the socket, to prevent the three-way handshake from proceeding any further.
*/
	if ( (n = select(sockfd+1, &rset, &wset, NULL,nsec ? &tval : NULL)) == 0) {
		close(sockfd);		/* timeout */
		errno = ETIMEDOUT;
		return(-1);
	}

/*
 If the descriptor is readable or writable, we call getsockopt to fetch the socket's 
 pending error (SO_ERROR). If the connection completed successfully, this value will 
 be 0.If the connection encountered an error,this value is the errno value corresponding 
 to the connection error (e.g., ECONNREFUSED, ETIMEDOUT, etc.). 
 We also encounter our first portability problem.If an error occurred,Berkeley-derived 
 implementations of getsockopt return 0 with the pending error returned in our variable 
 error. But Solaris causes getsockopt itself to return ¨C1 with errno set to the pending 
 error. Our code handles both scenarios.

 it is possible for a connection to complete and for data to arrive from a peer before 
 select is called.In this case,the socket will be both readable and writable on success, 
 the same as if the connection had failed. Our code handles this scenario by calling 
 getsockopt and checking the pending error for the socket.
*/

	if (FD_ISSET(sockfd, &rset) || FD_ISSET(sockfd, &wset)) {
		len = sizeof(error);
		if (getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &error, &len) < 0)
			return(-1);			/* Solaris pending error */
	} else
		printf("select error: sockfd not set");

done:
	fcntl(sockfd, F_SETFL, flags);	/* restore file status flags */

	if (error) {
		close(sockfd);		/* just in case */
		errno = error;
		return(-1);
	}
	return(0);
}

