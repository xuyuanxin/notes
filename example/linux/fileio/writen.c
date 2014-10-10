/*
Stream sockets (e.g., TCP sockets) exhibit a behavior with the read and write functions that differs from normal file I/O. 
A read or write on a stream socket might input or output fewer bytes than requested, but this is not an error condition. 
The reason is that buffer limits might be reached for the socket in the kernel. All that is required to input or output the 
remaining bytes is for the caller to invoke the read or write function again. Some versions of Unix also exhibit this behavior 
when writing more than 4,096 bytes to a pipe. This scenario is always a possibility on a stream socket with read, but is normally 
seen with write only if the socket is nonblocking. Nevertheless, we always call our writen function instead of write, in case the 
implementation returns a short count.*/

/* include writen */
#include	"unp.h"


/* Write "n" bytes to a descriptor. */
ssize_t x_writen(int fd, const void *vptr, size_t n)
{
	size_t		nleft;
	ssize_t		nwritten;
	const char	*ptr;

	ptr = vptr;
	nleft = n;
	
	while (nleft > 0) 
	{
		if ( (nwritten = write(fd, ptr, nleft)) <= 0) 
		{
			if (nwritten < 0 && errno == EINTR)
				nwritten = 0; /* and call write() again */
			else
				return(-1);	  /* error */
		}

		nleft -= nwritten;
		ptr   += nwritten;
	}
	
	return(n);
}

/* Read "n" bytes from a descriptor. */
ssize_t	x_readn(int fd, void *vptr, size_t n)
{
	size_t	nleft;
	ssize_t	nread;
	char	*ptr;

	ptr = vptr;
	nleft = n;
	
	while (nleft > 0) 
	{
		if ( (nread = read(fd, ptr, nleft)) < 0) 
		{
			if (errno == EINTR)
				nread = 0;		/* and call read() again */
			else
				return(-1);
		} else if (nread == 0)
			break;				/* EOF */

		nleft -= nread;
		ptr   += nread;
	}
	
	return(n - nleft);		/* return >= 0 */
}


/*
maxlen:最多读取maxlen-1个字符,最后一个写0
function:读取一行

1 Note that our readline function calls the system's read function once for every byte of data. This is very inefficient, 
  and why we've commented the code to state it is "PAINFULLY SLOW." 
*/
ssize_t x_readline(int fd, void *vptr, size_t maxlen)
{
	ssize_t n, rc;
	char	c, *ptr;

	ptr = vptr;
	
	for (n = 1; n < maxlen; n++) 
	{
		if ( (rc = read(fd, &c, 1)) == 1) 
		{
			*ptr++ = c;
			if (c == '\n')
				break;
		} 
		else if (rc == 0) 
		{
			if (n == 1)
				return(0);	/* EOF, no data read */
			else
				break;		/* EOF, some data was read */
		} 
		else
			return(-1); /* error */
	}

	*ptr = 0;
	return(n);
}


