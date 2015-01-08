/*
 By default, sockets are blocking. This means that when we issue a socket call that 
 cannot be completed immediately,our process is put to sleep,waiting for the condition 
 to be true. We can divide the socket calls that may block into four categories:
 1 Input operations
   These include the read, readv, recv, recvfrom, and recvmsg functions. If we call 
   one of these input functions for a blocking TCP socket (the default),and there is 
   no data available in the socket receive buffer,we are put to sleep until some data 
   arrives. Since TCP is a byte stream, we will be awakened when "some" data arrives: 
   It could be a single byte of data, or it could be a full TCP segment of data. If 
   we want to wait until some fixed amount of data is available, we can call our own 
   function readn (Figure 3.15) or specify the MSG_WAITALL flag (Figure 14.6).

   Since UDP is a datagram protocol,if the socket receive buffer is empty for a blocking 
   UDP socket, we are put to sleep until a UDP datagram arrives.With a nonblocking socket, 
   if the input operation cannot be satisfied (at least one byte of data for a TCP socket 
   or a complete datagram for a UDP socket), we see an immediate return with an error of 
   EWOULDBLOCK.
   
 2 Output operations
   These include the write,writev,send,sendto,and sendmsg functions.For a TCP socket, 
   the kernel copies data from the application's buffer into the socket send buffer. 
   If there is no room in the socket send buffer for a blocking socket, the process 
   is put to sleep until there is room.

   With a nonblocking TCP socket, if there is no room at all in the socket send buffer, 
   we return immediately with an error of EWOULDBLOCK. If there is some room in the 
   socket send buffer,the return value will be the number of bytes the kernel was able 
   to copy into the buffer. (This is called a short count.)

   We also said in Section 2.11 that there is no actual UDP socket send buffer. The 
   kernel just copies the application data and moves it down the stack, prepending the 
   UDP and IP headers. Therefore, an output operation on a blocking UDP socket (the 
   default) will not block for the same reason as a TCP socket, but it is possible for 
   output operations to block on some systems due to the buffering and flow control 
   that happens within the networking code in the kernel.

 3 Accepting incoming connections
   This is the accept function. If accept is called for a blocking socket and a new 
   connection is not available, the process is put to sleep.If accept is called for 
   a nonblocking socket and a new connection is not available, the error EWOULDBLOCK 
   is returned instead.

 4 Initiating outgoing connections
   This is the connect function for TCP. (Recall that connect can be used with UDP, 
   but it does not cause a "real" connection to be established; it just causes the 
   kernel to store the peer's IP address and port number.) The establishment of a TCP 
   connection involves a three-way handshake and the connect function does not return 
   until the client receives the ACK of its SYN. This means that a TCP connect always 
   blocks the calling process for at least the RTT to the server.

   If connect is called for a nonblocking TCP socket and the connection cannot be 
   established immediately, the connection establishment is initiated (e.g., the first 
   packet of TCP's three-way handshake is sent), but the error EINPROGRESS is returned. 
   Notice that this error differs from the error returned in the previous three scenarios. 
   Also notice that some connections can be established immediately, normally when the 
   server is on the same host as the client. So, even with a nonblocking connect, we 
   must be prepared for connect to return successfully. We will show an example of a 
   nonblocking connect in Section 16.3.


 Traditionally, System V has returned the error EAGAIN for a nonblocking I/O operation 
 that cannot be satisfied, while Berkeley-derived implementations have returned the 
 error EWOULDBLOCK. Because of this history, the POSIX specification says either may 
 be returned for this case. Fortunately, most current systems define these two error 
 codes to be the same (check your system's <sys/errno.h> header), so it doesn't matter 
 which one we use. In this text, we use EWOULDBLOCK.
