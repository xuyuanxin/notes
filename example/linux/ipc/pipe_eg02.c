#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

/*-----------------------------------------------------------------------------------
 Create pipes, fork 
    Two pipes are created. The parent calls the client function  and the  child calls 
    the server function. 
 waitpid  for child 
-----------------------------------------------------------------------------------*/
int main(int argc, char **argv)
{
	int		pipe1[2], pipe2[2];
	pid_t	childpid;

	pipe(pipe1);	/* create two pipes */
	pipe(pipe2);

	if ( (childpid = fork()) == 0) { /* child */
		close(pipe1[1]);
		close(pipe2[0]);
		server(pipe1[0], pipe2[1]);
		exit(0);
	}
	
	/* parent */
	close(pipe1[0]);
	close(pipe2[1]);
	client(pipe2[0], pipe1[1]);
	waitpid(childpid, NULL, 0);		/* wait for child to terminate */
	exit(0);
}

/*
solaris %  mainpipe 
/etc/inet/ntp.conf                <---- a file consisting of  two  lines 
multicastclient 224.0.1.1 
driftfile /etc/inet/ntp.drift 
solaris %  mainpipe 
/etc/shadow                       <---- a  file we cannot read 
/etc/shadow:  can't  open, Permission denied 
solaris %  mainpipe 
/no/such/file                     <---- a nonexistent file 
/no/such/file:  can't  open, No such file or directory 
*/

