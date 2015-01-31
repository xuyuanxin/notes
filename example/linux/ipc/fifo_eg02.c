
/*-----------------------------------------------------------------------------------
 Create two FlFOs 
    TWO FIFOs are created in the /tmp filesystem. If the FIFOs already exist, that is 
    OK.
 fork 
    We call @fork, the child calls our @server function, and the parent calls our @c-
    1ient function. Before executing these calls, the parent opens the first FIFO for 
    writing and the second FIFO for reading,and the child opens the first FIFO for r-
    eading and the second FIFO for writing. This is similar to our pipe example.

 The changes from our pipe example to this FIFO example are as follows: 
 1 To create and open a pipe requires one call to @pipe. To create and open a FIFO r-
   equires one call to @mkfifo followed by a call to @open. 
 2 A pipe automatically disappears  on its last close. A FIFO's  name is deleted from 
   the  filesystem only by calling @unlink. 
   
 The benefit in the extra calls required for the FIFO is that a FIFO has a name in t-
 he file-system allowing one process to create a  FIFO and another  unrelated process 
 to open the FIFO. This  is not possible with a pipe. 

 Subtle problems can occur with programs  that do not use FIFOs correctly. if we swap 
 the order of the two calls to @open in the parent, the program does not work. The r-
 eason is that the @open of a FIFO for reading blocks if no process currently has the 
 FIFO open for writing. If we  swap the order of these two  opens in the parent, both 
 the parent and the child are opening a FIFO for reading when no process has the FIFO 
 open for writing, so both block. This is called a deadlock.
-----------------------------------------------------------------------------------*/
int main(int argc, char **argv)
{
	int		readfd, writefd;
	pid_t	childpid;

	/* create two FIFOs; OK if they already exist */
	if ((mkfifo(FIFO1, FILE_MODE) < 0) && (errno != EEXIST)) {
		printf("can't create %s \r\n", FIFO1);
		return -1;
	}
	if ((mkfifo(FIFO2, FILE_MODE) < 0) && (errno != EEXIST)) {
		unlink(FIFO1);
		printf("can't create %s \r\n", FIFO2);
		return -1;
	}

	if ( (childpid = fork()) == 0) { /* child */
		readfd = open(FIFO1, O_RDONLY, 0);
		writefd = open(FIFO2, O_WRONLY, 0);

		server(readfd, writefd);
		exit(0);
	}

	/* parent */
	writefd = open(FIFO1, O_WRONLY, 0);
	readfd = open(FIFO2, O_RDONLY, 0);

	client(readfd, writefd);

	waitpid(childpid, NULL, 0);		/* wait for child to terminate */

	close(readfd);
	close(writefd);

	unlink(FIFO1);
	unlink(FIFO2);
	exit(0);
}

