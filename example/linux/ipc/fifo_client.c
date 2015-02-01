#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include "ipc_pub.h"

/*-----------------------------------------------------------------------------------
 Create FlFO 
    The client's FIFO is created with the process ID as the final part of the pathname. 
 Build client request line 
    The client's request consists of its process ID, one blank, the pathname for  the 
    server to send to the client, and a newline. This line is built in the array buff, 
    reading the pathname from the standard input. 
 Open server's FlFO and write request 
    The server's FIFO is opened and the request is written to the FIFO.If this client 
    is the first to open this FIFO since the server was started, then this open unbl-
    ocks the server from its call to open (with  the 0_RDONLY  flag). 
 Read file contents or error message from server 
    The server's reply is read from the FIFO and written to standard output. The cli-
    ent's FIFO is then closed and deleted. 
-----------------------------------------------------------------------------------*/
int main(int argc, char **argv)
{
    int        readfifo, writefifo;
    size_t    len;
    ssize_t    n;
    char    *ptr, fifoname[MAXLINE_01]={0}, buff[MAXLINE_01]={0};
    pid_t    pid;
  
    pid = getpid(); /* create FIFO with our PID as part of name */
    snprintf(fifoname, sizeof(fifoname), "/tmp/fifo.%ld", (long) pid);
    if ((mkfifo(fifoname, S_IFIFO|0777) < 0) && (errno != EEXIST)) {
        printf("can't create %s  %d %s \r\n", fifoname,errno,strerror(errno));
        return -1;
    }
    printf("mkfifo %s ok. now input request filename: \r\n",fifoname);
    snprintf(buff, sizeof(buff), "%ld ", (long) pid);
    len = strlen(buff); /* start buffer with pid and a blank */
    ptr = buff + len;
    fgets(ptr, MAXLINE_01 - len, stdin); /* read pathname */
    len = strlen(buff);        /* fgets() guarantees null byte at end */
    printf("sending len:%d | %s  \r\n",len,buff);
    writefifo = open(SERV_FIFO, O_WRONLY, 0);
    if(writefifo < 0) {
        printf("open %s fail \r\n",SERV_FIFO);
    }
    write(writefifo, buff, len); /* open FIFO to server and write PID and pathname to FIFO */        
    readfifo = open(fifoname, O_RDONLY, 0); /* now open our FIFO; blocks until server opens for writing */
    while ( (n = read(readfifo, buff, MAXLINE_01)) > 0) {
        write(STDOUT_FILENO, buff, n); /* read from IPC, write to standard output */
    }
    close(readfifo);
    unlink(fifoname);
    exit(0);
}


int main1(int argc, char **argv)
{
    int        readfd, writefd;

    writefd = open(FIFO1, O_WRONLY, 0);
    readfd = open(FIFO2, O_RDONLY, 0);

    client(readfd, writefd);

    close(readfd);
    close(writefd);

    unlink(FIFO1);
    unlink(FIFO2);
    exit(0);
}

