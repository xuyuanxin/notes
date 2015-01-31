#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include "ipc_pub.h"


/*-----------------------------------------------------------------------------------
 The pathname is read from standard input and written to the pipe, after deleting th-
 e newline that is stored by fgets. 
 The @client then reads everything that the @server writes to the pipe, writing it to 
 standard output. Normally this is the contents of the file, but if the specified pa-
 thname cannot be opened, what the server returns is an error message. 
-----------------------------------------------------------------------------------*/
void client(int readfd, int writefd)
{
	size_t	len;
	ssize_t	n;
	char	buff[MAXLINE_01];
	
	fgets(buff, MAXLINE_01, stdin); /* read pathname */
	len = strlen(buff);		        /* fgets() guarantees null byte at end */
	if (buff[len-1] == '\n') {
		len--;				        /* delete newline from fgets() */
	}
	write(writefd, buff, len);      /* write pathname to IPC channel */
	while ( (n = read(readfd, buff, MAXLINE_01)) > 0) {
		write(STDOUT_FILENO, buff, n); /* read from IPC, write to standard output */
	}
}

/*-----------------------------------------------------------------------------------
 Read pathname from pipe 
    The pathname written by the @client is read from the pipe and null terminated. N-
    ote that a read on a pipe returns as soon as some data is present; it need not w-
    ait for the requested number of bytes (MAXLINE_01 in this example). 
 Open file, handle error 
    The file is opened for reading,and if an error occurs, an error message string is 
    returned to the @client across the pipe. We call the @strerror function to return 
    the error message string corresponding to errno.  
 Copy file to pipe 
    If the open succeeds, the contents of the file are copied to the pipe.
-----------------------------------------------------------------------------------*/
void server(int readfd, int writefd)
{
	int		fd;
	ssize_t	n;
	char	buff[MAXLINE_01+1];

	if ( (n = read(readfd, buff, MAXLINE_01)) == 0) {
		printf("end-of-file while reading pathname");
		return;
	}
	buff[n] = '\0';		             /* null terminate pathname */
	if ( (fd = open(buff, O_RDONLY)) < 0) {
		snprintf(buff + n, sizeof(buff) - n, ": can't open, %s\n",strerror(errno));
		n = strlen(buff);
		write(writefd, buff, n);     /* error: must tell client */

	} else {
		while ( (n = read(fd, buff, MAXLINE_01)) > 0) {
			write(writefd, buff, n); /* open succeeded: copy file to IPC channel */
		}
		close(fd);
	}
}
