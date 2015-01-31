#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include "ipc_pub.h"

ssize_t x_readline2(int fd, void *vptr, size_t maxlen)
{
    ssize_t n, rc;
    char    c, *ptr;

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
                return(0);    /* EOF, no data read */
            else
                break;        /* EOF, some data was read */
        } 
        else
            return(-1); /* error */
    }

    *ptr = 0;
    return(n);
}

/*-----------------------------------------------------------------------------------
 The server creates a FIFO with a well-known pathname,/tmp/fifo.serv in this example. 
 The server will read client requests from this FIFO. Each client creates its own FI-
 FO when it starts, with a pathname containing its process ID. Each client writes its
 request to the server's well-known FIFO, and the request contains the client process 
 ID along with the pathname of the file that the client wants the server to open  and 
 send to the client. 

 Create well-known FIFO and open for read-only and write-only 
    The server's well-known FIFO is created, and it is OK if it already exists. We t-
    hen open the FIFO twice, once read-only and once write-only. The @readfifo descr-
    iptor is used to read each client request that arrives at the FIFO, but the @dum-
    myfd descriptor is never used. If we do not open the FIFO for  writing, then each 
    time a client terminates, the FIFO becomes empty and the server's  read returns 0 
    to indicate an end-of-file. We would then have to close the FIFO and call open a-
    gain with the 0_RDONLY flag, and this will block until the next client request a-
    rrives. But if we always have a descriptor for the FIFO that was opened for writ-
    ing, read will never return 0 to indicate an end-of-file when no clients exist.I-
    nstead, our server will just block in the call to read, waiting for the next cli-
    ent request. This trick therefore simplifies our server code and  reduces the nu-
    mber of calls to open  for its well-known FIFO. When the server starts, the first 
    open ( with the 0_RDONLY  flag ) blocks until the first client opens the server's  
    FIFO write-only. The second open ( with the 0_WRONLY flag) then returns immediat-
    ely, because the FIFO is already open  for reading. 
 Read client request 
    Each client request is a single line consisting of the process ID, one space, and 
    then the pathname. We read this line with our @readline function.
 Parse client's  request 
    The newline that is normally returned by @readline is deleted. This newline is m-
    issing only if the buffer was filled before the newline was encountered, or if t-
    he final line of input was not terminated by a newline. The @strchr function ret-
    urns a pointer to the first blank in the line , and @ptr  is incremented to point 
    to the first character of the pathname that follows. The pathname of the client's 
    FIFO is constructed from the process ID,and the FIFO is opened  for write-only by 
    the server.  
 Open file for client, send file to client's FlFO 
    The file is opened and if this  fails, an error message is returned to the client 
    across the FIFO . If the open succeeds , the file is copied to the client's FIFO. 
    When done, we must close the server's end of the client's FIFO , which causes the 
    client's read to return 0 (end-of-file ). The server does not delete the client's 
    FIFO; the client must do so after it reads the end-of-file from the server.     
-----------------------------------------------------------------------------------*/
int main(int argc, char **argv)
{
    int  readfifo, writefifo, dummyfd, fd;
    char *ptr, buff[MAXLINE_01], fifoname[MAXLINE_01];
    pid_t pid;
    ssize_t n;

    /* create server's well-known FIFO; OK if already exists */
    if ((mkfifo(SERV_FIFO, S_IFIFO|FILE_MODE) < 0) && (errno != EEXIST)) {    
        printf("can't create %s \r\n", SERV_FIFO);
        return -1;
    }

    printf("server mkfifo %s ok! open... \r\n",SERV_FIFO);

/*----------------------------------------------------------------------------------- 
 open server's well-known FIFO for reading and writing 
 When the server starts, the first open ( with the 0_RDONLY  flag ) blocks  until the 
 first client opens the server's FIFO write-only. The second open ( with the 0_WRONLY 
 flag) then returns immediately, because the FIFO is already open for reading.  
-----------------------------------------------------------------------------------*/
    readfifo = open(SERV_FIFO, O_RDONLY, 0); /* */
    dummyfd = open(SERV_FIFO, O_WRONLY, 0);  /* never used */

    if( ( readfifo < 0) || (dummyfd < 0) ) {
        printf("open fail! %d %d \r\n",readfifo,dummyfd);
        return -1;
    }
    printf("open success,a clien come, reading... \r\n");
    while ( (n = x_readline2(readfifo, buff, MAXLINE_01)) > 0) {
        if (buff[n-1] == '\n') {
            n--;            /* delete newline from readline() */
        }
        buff[n] = '\0';        /* null terminate pathname */
        if ( (ptr = strchr(buff, ' ')) == NULL) {
            printf("bogus request: %s \r\n", buff);
            continue;
        }
        *ptr++ = 0;            /* null terminate PID, ptr = pathname */
        pid = atol(buff);
        snprintf(fifoname, sizeof(fifoname), "/tmp/fifo.%ld", (long) pid);
        if ( (writefifo = open(fifoname, O_WRONLY, 0)) < 0) {
            printf("cannot open: %s \r\n", fifoname);
            continue;
        }
        if ( (fd = open(ptr, O_RDONLY)) < 0) {
            snprintf(buff + n, sizeof(buff) - n, "[from serv]: can't open, %s\n",strerror(errno));
            n = strlen(ptr);
            write(writefifo, ptr, n); /*  error: must tell client */
            close(writefifo);
        } else {
            while ( (n = read(fd, buff, MAXLINE_01)) > 0) {
                write(writefifo, buff, n); /* open succeeded: copy file to FIFO */
            }
            close(fd);
            close(writefifo);
        }
    }
}

int main1(int argc, char **argv)
{
    int    readfd, writefd;

    if ((mkfifo(FIFO1, FILE_MODE) < 0) && (errno != EEXIST)) {
        printf("can't create %s \r\n", FIFO1);
        return -1;
    }
    if ((mkfifo(FIFO2, FILE_MODE) < 0) && (errno != EEXIST)) {
        unlink(FIFO1); 
        printf("can't create %s \r\n", FIFO2);
        return -1;
    }

    readfd = open(FIFO1, O_RDONLY, 0);
    writefd = open(FIFO2, O_WRONLY, 0);

    server(readfd, writefd);
    exit(0);
}


/*
+=====================================================================================+
| Current operation     | Existing  opens  | Blocking(default)    |  O_NONBLOCK set   |
|                       | of pipe or FIFO  |                      |                   |
|-----------------------|----------------- |----------------------|-------------------|
| open FIFO read-only   | FIFO open        | return ok            |  return ok        |
|                       | for writing      |                      |                   |
|-----------------------|----------------- |----------------------|-------------------|
| open FIFO read-only   | FIFO not open    | blocks until FIFO is |  returns OK       |
|                       | for writing      | opened for writing   |                   |
|-----------------------|----------------- |----------------------|-------------------|
| open FIFO write-only  | FIFO open for    | return ok            |  return ok        |
|                       | reading          |                      |                   |
|-----------------------|----------------- |----------------------|-------------------|
| open FIFO write-only  | FIFO not open    | blocks until FIFO is | return an error   |
|                       | for reading      | opened for reading   | of ENXIO          |
|=======================|==================|======================|===================|
| read empty pipe       | pipe or FIFO     |        *1            |  returns an error |
| or empty FIFO         | open for writing |                      |  of  EAGAIN       |
|-----------------------|------------------|----------------------|-------------------|
| read empty pipe       | pipe or FIFO not | read  returns 0      | read  returns 0   | 
| or empty FIFO         | open for writing | (end-of-file)        | (end-of-file)     |
|-----------------------|------------------|----------------------|-------------------|
| write to pipe or FIFO | pipe or FIFO open| (see text)           |  (see text)       |
|                       | for reading      |                      |                   |
|-----------------------|------------------|----------------------|-------------------|
| write to pipe or FIFO | pipe or FIFO not | SIGPIPE  generated   | SIGPIPE generated |
|                       | open for reading |  for thread          | for thread        |
|=======================|==================|======================|===================+

*1 blocks until data is in the pipe or FIFO,or until the pipe or FIFO is no longer open 
   for writing


Note a few additional rules regarding the reading and writing of a pipe or FIFO. 
If we ask to read more data than is currently available  in the pipe or FIFO, only 
the available data  is  returned. We  must be prepared to handle a  return value 
from read  that is  less than the requested amount. 
If  the number of  bytes to write  is less than or equal  to PIPE-BUF (a Posix limit 
that we say more about in Section 4.11), the write is guaranteed to be atomic. 
This means that if  two processes each write to the same pipe or FIFO at about 
the same time, either all the data from the  first process  is written, followed by all 
the data from  the second process, or vice versa.  The system does not intermix 
the data from the two processes.  If,  however, the number of  bytes to write  is 
greater  than  PIPE-BUF, there  is  no  guarantee  that  the write operation  is 
atomic. 
Posix.1  requires that  PIPE-BUF  be at  least 512  bytes.  Commonly encountered values 
range  from  1024 for  BSD/OS  3.1  to  5120 for  Solaris 2.6.  We  show  a program  in Sec- 
tion 4.11 that prints this value. 
The  setting of  the 0-NONBLOCK flag has no effect on the atomicity of writes  to a 
pipe or FIFO-atomicity is determined  solely by whether the requested number 
of  bytes is less than or equal to PIPE-BUF. But when a pipe or FIFO is set non- 
blocking, the return value from write  depends on the number of  bytes to write 

and the amount of  space currently available  in the pipe or FIFO.  If  the number 
of  bytes to write  is less than or equal to PIPE-BUF: 
a.  If  there  is room in the pipe or FIFO for the requested number of  bytes, all the 
bytes are  transferred. 
b.  If  there is not enough room in the pipe or FIFO for the requested number of 
bytes,  return  is  made  immediately with  an  error  of  EAGAIN.  Since  the 
0-NONBLOCK  flag is set, the process does not want to be put to sleep. But the 
kernel cannot accept part of  the data and still guarantee  an atomic write,  so 
the kernel must return an error and tell  the process  to try again  later. 
If  the number of  bytes to write  is greater than PIPE-BUF: 
a.  If  there is  room for at least 1 byte in the pipe or FIFO,  the kernel transfers 
whatever  the pipe  or  FIFO  can  hold,  and  that  is  the  return value  from 
write. 
b.  If  the  pipe  or  FIFO  is  full,  return  is made  immediately with  an  error of 
EAGAIN. 
If  we write  to a pipe or FIFO  that is not open for reading, the SIGPIPE signal 
is generated: 
a.  If  the process does not catch or ignore SIGPIPE, the default action of  termi- 
nating the process  is taken. 
b.  If  the process  ignores  the  SIGPIPE signal,  or  if  it  catches  the signal and 
returns  from its signal handler, then write  returns  an error of  EPIPE. 
SIGPIPE  is considered a synchronous signal, that is, a signal attributable to one 
specific thread, the one  that called write.  But  the easiest way to handle this 
signal is to ignore it  (set its disposition to  SIG-IGN)  and let write  return an 
error  of  EPIPE.  An  application  should always  detect  an error  return  from 
write,  but detecting  the termination of  a process by SIGPIPE is harder.  If  the 
signal is not caught, we must look at  the termination status of  the process from 
the shell to determine that the process was killed by a signal, and which signal. 
Section 5.13 of UNPvl talks more about SIGPIPE. 
*/
