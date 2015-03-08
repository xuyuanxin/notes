#include <time.h>
#include <poll.h>
#include <stdlib.h>
#include <stdio.h>

/*-----------------------------------------------------------------------------------
 Example of the use of poll() to monitor multiple file descriptors.

 Usage: poll_pipes num-pipes [num-writes]
                               def = 1

 Create 'num-pipes' pipes, and perform 'num-writes' writes to randomly selected pipes. 
 Then use @poll to inspect the read ends of the pipes to see which pipes are readable.

notes01
    Build the file descriptor list to be supplied to poll(). This list is set to con-
    tain the file descriptors for the read ends of all of the pipes.
-----------------------------------------------------------------------------------*/
int poll_eg(int argc, char *argv[])
{
    int numPipes, j, ready, randPipe, numWrites;
    int (*pfds)[2]; /* File descriptors for all pipes */
    struct pollfd *pollFd;

    if (argc < 2 || strcmp(argv[1], "--help") == 0) {
        printf("%s num-pipes [num-writes]\n", argv[0]);
		return -1; 
    }

    numPipes = atoi(argv[1]); /* strtol */
    pfds = calloc(numPipes, sizeof(int [2])); /* Allocate the arrays that we use.*/
    if (pfds == NULL) {
        printf("calloc error\n");
		return -1;
    }
    pollFd = calloc(numPipes, sizeof(struct pollfd));
    if (pollFd == NULL) {
        printf("calloc error2 \n");
		return -1;
    }

    for (j = 0; j < numPipes; j++) { /* Create the number of pipes specified on command line */
        if (pipe(pfds[j]) == -1) {
            printf("pipe %d error \n", j);
			return -1;
        }
    }

    /* Perform specified number of writes to random pipes */

    numWrites = (argc > 2) ? atoi(argv[2]):1;

    srandom((int) time(NULL));
    for (j = 0; j < numWrites; j++) {
        randPipe = random() % numPipes;
        printf("Writing to fd: %3d (read fd: %3d)\n",pfds[randPipe][1], pfds[randPipe][0]);
        if (write(pfds[randPipe][1], "a", 1) == -1) {
            printf("write %d error \n", pfds[randPipe][1]);
			return -1;
        }
    }

    for (j = 0; j < numPipes; j++) { /* notes01 */
        pollFd[j].fd = pfds[j][0];
        pollFd[j].events = POLLIN;
    }

    ready = poll(pollFd, numPipes, 0);
    if (ready == -1) {
        printf("poll error \n");
		return -1;
    }

    printf("poll() returned: %d\n", ready);

    /* Check which pipes have data available for reading */

    for (j = 0; j < numPipes; j++) {
        if (pollFd[j].revents & POLLIN) {
            printf("Readable: %3d\n", pollFd[j].fd);
	    }
    }

    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
	return poll_eg(argc,argv);
}

