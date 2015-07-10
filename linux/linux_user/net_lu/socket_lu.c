#include <netinet/in.h>
/*-----------------------------------------------------------------------------------
 host byte order: 
     We refer to the byte ordering used by a given system as the host byte order. 
 network byte order
     The Internet protocols use big-endian byte ordering for these multibyte integers
 
 htons htonl Both return: value in network byte order
 ntohs ntohl Both return: value in host byte order

 In the names of these functions, h stands for host, n stands for network, s stands -
 for short, and l stands for long. The terms "short" and "long" are historical artif-
 acts from the Digital VAX implementation of 4.2BSD. We should instead think of s  as 
 a 16-bit value (such as a TCP or UDP port number) and l as a 32-bit value (such as -
 an IPv4 address). Indeed, on the 64-bit Digital Alpha, a long integer occupies 64 b-
 its, yet the htonl and ntohl functions operate on 32-bit values.
 
 When using these functions, we do not care about the actual values (big-endian or  -
 little-endian) for the host byte order and the network byte order. What we must do -
 is call the appropriate function to convert a given value between the host and netw-
 ork byte order. On those systems that have the same byte ordering as the Internet p-
 rotocols (big-endian), these four functions are usually defined as null macros.

 We have not yet defined the term "byte." We use the term to mean an 8-bit quantity -
 since almost all current computer systems use 8-bit bytes. Most Internet standards -
 use the term octet instead of byte to mean an 8-bit quantity. This started in the e-
 arly days of TCP/IP because much of the early work was done on systems such as the -
 DEC-10, which did not use 8-bit bytes.

 
 Another important convention in Internet standards is bit ordering. In many Internet 
 standards, you will see "pictures" of packets that look similar to the following (t-
 his is the first 32 bits of the IPv4 header from RFC 791):
  0 				  1 				  2 				  3   
  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 |Version|	IHL  |Type of Service|			Total Length		 |
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 This represents four bytes in the order in which they appear on the wire; the leftm-
 ost bit is the most significant. However, the numbering starts with zero assigned to 
 the most significant bit. This is a notation that you should become familiar with to 
 make it easier to read protocol definitions in RFCs.
 ----------------------------------------------------------------------------------*/
uint16_t htons(uint16_t host16bitvalue);
uint32_t htonl(uint32_t host32bitvalue); 
uint16_t ntohs(uint16_t net16bitvalue);
uint32_t ntohl(uint32_t net32bitvalue);

#include <arpa/inet.h>

/*----------------------------------------------------------------------------------
 converts the C character string pointed to by @strptr into its 32-bit binary networ-
 k byte ordered value, which is stored through the pointer @addrptr. Returns: 1 if s-
 tring was valid, 0 on error. An undocumented feature of inet_aton is that if addrptr 
 is a null pointer, the function still performs its validation of the input string b-
 ut does not store any result.
 ----------------------------------------------------------------------------------*/
int inet_aton(const char *strptr, struct in_addr *addrptr);
 
/*-----------------------------------------------------------------------------------
 Today, inet_addr is deprecated and any new code should use inet_aton instead. Better 
 still is to use the newer functions(inet_pton and inet_ntop), which handle both IPv4 
 and IPv6.

 returning the 32-bit binary network byte ordered value as the return value. The pro-
 blem with this function is that all 2^32 possible binary values are valid IP addres-
 ses (0.0.0.0 through 255.255.255.255), but the function returns the constant       -
 INADDR_NONE (typically 32 one-bits) on an error. This means the dotted-decimal stri-
 ng 255.255.255.255 (the IPv4 limited broadcast address) cannot be handled by this f-
 unction since its binary value appears to indicate failure of the function.
 ----------------------------------------------------------------------------------*/
in_addr_t inet_addr(const char *strptr);
 
/*-----------------------------------------------------------------------------------
 The inet_ntoa function converts a 32-bit binary network byte ordered IPv4 address i-
 nto its corresponding dotted-decimal string. The string pointed to by the return va-
 lue of the function resides in static memory. This means the function is not reentr-
 ant
 ----------------------------------------------------------------------------------*/
char *inet_ntoa(struct in_addr inaddr);
 

/*-----------------------------------------------------------------------------------
 The letters "p" and "n" stand for presentation and numeric. The presentation  format 
 for an address is often an ASCII string and the numeric format is the binary value -
 that goes into a socket address structure.

 @family  AF_INET or AF_INET6
     The @family argument for both functions is either AF_INET or AF_INET6. If      -
     @family is not supported, both functions return an error with errno set to     -
     EAFNOSUPPORT.
 @strptr
     The @strptr argument to inet_ntop cannot be a null pointer. The caller must all-
     ocate memory for the destination and specify its size. On success, this  pointer 
     is the return value of the function.
 @len
     The @len argument is the size of the destination, to prevent the  function  from 
     overflowing the caller's buffer. To help specify this size, the following two d-
     efinitions are defined by including the <netinet/in.h> header: INET_ADDRSTRLEN -
     INET6_ADDRSTRLEN. If @len is too small to hold the resulting presentation forma-
     t, including the terminating null, a null pointer is returned and errno is set -
     to ENOSPC.
 @functon 
     inet_pton tries to convert the string pointed to by @strptr, storing the  binary 
     result through the pointer @addrptr. inet_ntop does the reverse conversion, from 
     numeric (addrptr) to presentation (strptr). 
 @Returns
     1 if OK, 0 if input not a valid presentation format, -1 on error

 Example
 Even if your system does not yet include support for IPv6, you can start using these 
 newer functions by replacing calls of the form 
     foo.sin_addr.s_addr = inet_addr(cp);
 with
     inet_pton(AF_INET, cp, &foo.sin_addr);
 and replacing calls of the form
     ptr = inet_ntoa(foo.sin_addr);
 with
     char str[INET_ADDRSTRLEN];
     ptr = inet_ntop(AF_INET, &foo.sin_addr, str, sizeof(str));
 ----------------------------------------------------------------------------------*/
int inet_pton(int family, const char *strptr, void *addrptr);
const char *inet_ntop(int family, const void *addrptr, char *strptr, size_t len);
  
#include <sys/socket.h>
/*-----------------------------------------------------------------------------------
 @domain: AF_INET
     specifies the protocol family 
 @type: SOCK_STREAM 
 @protocol: IPPROTO_TCP
     specific protocol type. 0 to select the system's default for the given combinat-
     ion of @domain and @type.
 return:
	non-negative descriptor if OK, -1 on error.

 AF_xxx Versus PF_xxx
    The "AF_" prefix stands for "address family" and the "PF_" prefix stands for 
    "protocol family." Historically, the intent was that a single protocol family 
    might support multiple address families and that the PF_ value was used to 
    create the socket and the AF_ value was used in socket address structures. 
    But in actuality, a protocol family supporting multiple address families has 
    never been supported and the <sys/socket.h> header defines the PF_ value for 
    a given protocol to be equal to the AF_ value for that protocol. While there 
    is no guarantee that this equality between the two will always be true, should 
    anyone change this for existing protocols, lots of existing code would break. 
    To conform to existing coding practice, we use only the AF_ constants in this 
    text, although you may encounter the PF_ value, mainly in calls to socket.

  --------------------------------------------------------------------+
                 | AF_INET  | AF_INET6 | AF_LOCAL | AF_ROUTE | AF_KEY |
  ---------------|----------|----------|----------|----------|--------|
  SOCK_STREAM    | tcp|sctp | tcp|sctp |    yes   |          |        |
  ---------------|----------|----------|----------|----------|--------|
  SOCK_DGRAM     |    udp   |   udp    |    yes   |          |        |
  ---------------|----------|----------|----------|----------|--------| 
  SOCK_SEQPACKET |   sctp   |   sctp   |    yes   |          |        |
  ---------------|----------|----------|----------|----------|--------| 
  SOCK_RAW       |   ipv4   |   ipv6   |          |    yes   |   yes  |
  ---------------+----------+----------+----------+----------+--------+
  Figure 4.5 Combinations of @family and @type for the @socket function
       
 Not all combinations of @socket @family and @type are valid. Figure 4.5 shows the v-
 alid combinations, along with the actual protocols that are valid for each pair. Th-
 e boxes marked "Yes" are valid but do not have handy acronyms. The blank boxes are -
 not supported.   
 ----------------------------------------------------------------------------------*/
int socket(int domain, int type,int protocol);

/*-----------------------------------------------------------------------------------
 @sockfd: 
   is a socket descriptor returned by the @socket function. 
 @servaddr: 
   The socket address structure must contain the IP address and port number of 
   the server. 
 @servlen: 
   The second and third arguments are a pointer to a socket address structure 
   and its size 
 function:
   The connect function is used by a TCP client to establish a connection with 
   a TCP server.
 returns:
   0 if OK, -1 on error

 1 The client does not have to call @bind before calling connect: the kernel 
   will choose both an ephemeral port and the source IP address if necessary.
 2 In the case of a TCP socket, the @connect function initiates TCP's three-way 
   handshake.The function returns only when the connection is established or an 
   error occurs
 3 each time connect fails, we must close the socket descriptor and call socket 
   again.
 4 @connect returns when the second segment of the handshake(tcp) is received by  the 
   client, but @accept does not return until the third segment of the handshake is r-
   eceived by the server, one-half of the RTT after @connect returns.
 5 When @connect is interrupted by a caught signal and is not automatically 
   restarted.If this function returns EINTR, we cannot call it again, as doing 
   so will return an immediate error.

There are several different error returns possible.
1 If the client TCP receives no response to its SYN segment, ETIMEDOUT is returned. 
  4.4BSD, for example, sends one SYN when connect is called, another 6 seconds 
  later, and another 24 seconds later. If no response is received after a total 
  of 75 seconds, the error is returned.Some systems provide administrative control 
  over this timeout;
2 If the server's response to the client's SYN is a reset (RST), this indicates 
  that no process is waiting for connections on the server host at the port 
  specified (i.e., the server process is probably not running). This is a hard 
  error and the error ECONNREFUSED is returned to the client as soon as the RST 
  is received.An RST is a type of TCP segment that is sent by TCP when something 
  is wrong. Three conditions that generate an RST are: when a SYN arrives for a 
  port that has no listening server (what we just described), when TCP wants to 
  abort an existing connection, and when TCP receives a segment for a connection 
  that does not exist. (TCPv1 [pp. 246–250] contains additional information.)
3 If the client's SYN elicits an ICMP "destination unreachable" from some 
  intermediate router, this is considered a soft error. The client kernel saves 
  the message but keeps sending SYNs with the same time between each SYN as in 
  the first scenario. If no response is received after some fixed amount of time 
  (75 seconds for 4.4BSD), the saved ICMP error is returned to the process as 
  either EHOSTUNREACH or ENETUNREACH. It is also possible that the remote system 
  is not reachable by any route in the local system's forwarding table, or that 
  the connect call returns without waiting at all.
 ----------------------------------------------------------------------------------*/
int connect(int sockfd, const struct sockaddr *servaddr, socklen_t addrlen);
	 
	
/*******************************************************************************
 @sockfd:
 @myaddr:要与@sockfd绑定的地址
 @addrlen:地址长度
 function:The @bind function assigns a local protocol address to a socket.
 returns: 0 if OK,-1 on error

1 With TCP, calling @bind lets us specify a port number, an IP address, both, or 
  neither.A process can bind a specific IP address to its socket.The IP address 
  must belong to an interface on the host.
2 If a TCP client or server does not do this,the kernel chooses an ephemeral port 
  for the socket when either @connect or @listen is called.It is normal for a TCP 
  client to let the kernel choose an ephemeral port,unless the application requires 
  a reserved port , but it is rare for a TCP server to let the kernel choose an 
  ephemeral port, since servers are known by their well-known port.
3 For a TCP client, this assigns the source IP address that will be used for IP 
  datagrams sent on the socket.For a TCP server, this restricts the socket to 
  receive incoming client connections destined only to that IP address.
4 Normally, a TCP client does not bind an IP address to its socket. The kernel 
  chooses the source IP address when the socket is connected,based on the outgoing 
  interface that is used, which in turn is based on the route required to reach 
  the server.If a TCP server does not bind an IP address to its socket, the kernel 
  uses the destination IP address of the client's SYN as the server's source IP 
  address .
5 If we specify a port number of 0, the kernel chooses an ephemeral port when bind 
  is called. But if we specify a wildcard IP address,the kernel does not choose the 
  local IP address until either the socket is connected (TCP) or a datagram is sent 
  on the socket (UDP).
6 With IPv4, the wildcard address is specified by the constant INADDR_ANY, whose 
  value is normally 0.The system allocates and initializes the in6addr_any variable 
  to the constant IN6ADDR_ANY_INIT. 
*******************************************************************************/
int bind (int sockfd, const struct sockaddr *myaddr, socklen_t addrlen);
	  
	 
/*-----------------------------------------------------------------------------------
 @sockfd:
 @backlog: SOMAXCONN
    maximum number of connections the kernel should queue for this socket.
 @function
 @returns: 
    0 if OK, -1 on error
 
 This function is normally called after both the @socket and @bind functions and must 
 be called before calling the @accept function.

 When a socket is created by the @socket function, it is assumed to be an active soc-
 ket, that is, a client socket that will issue a connect. The @listen function conve-
 rts an unconnected socket into a passive socket, indicating that the kernel should -
 accept incoming connection requests directed to this socket. In terms of the TCP st-
 ate transition diagram,the call to @listen moves the socket from the CLOSED state to 
 the LISTEN state.

 for a given listening socket, the kernel maintains two queues:
 1 An incomplete connection queue, which contains an entry for each SYN that has arr-
   ived from a client for which the server is awaiting completion of the TCP three w-
   ay handshake. These sockets are in the SYN_RCVD state.
 2 A completed connection queue, which contains an entry for each client with whom t-
   he TCP three-way handshake has completed. These sockets are in the ESTABLISHED st-
   ate. When a SYN arrives from a client, TCP creates a new entry on the incomplete -
   queue and then responds with the second segment of the three-way handshake:the se-
   rver's SYN with an ACK of the client's SYN . This entry will remain on the incomp-
   lete queue until the third segment of the three-way handshake arrives(the client's 
   ACK of the server's SYN), or until the entry times out. If the three-way handshake 
   completes normally, the entry moves from the incomplete queue to the end of the c-
   ompleted queue. When the process calls @accept, the first entry on the completed -
   queue is returned to the process, or if the queue is empty , the process is put to 
   sleep until an entry is placed onto the completed queue.

 If the queues are full when a client SYN arrives, TCP ignores the arriving SYN; it -
 does not send an RST. This is because the condition is considered temporary, and the 
 client TCP will retransmit its SYN , hopefully finding room on the queue in the near 
 future.
-----------------------------------------------------------------------------------*/	  
int listen (int sockfd, int backlog);

	      
/*******************************************************************************
 @cliaddr:
   The @cliaddr and @addrlen arguments are used to return the protocol address 
   of the connected peer process (the client). 
 @addrlen:
   Before the call, we set the integer value referenced by *@addrlen to the size 
   of the socket address structure pointed to by cliaddr;on return, this integer 
   value contains the actual number of bytes stored by the kernel in the socket 
   address structure.
 function:
   @accept is called by a TCP server to return the next completed connection from 
   the front of the completed connection queue. If the completed connection queue 
   is empty, the process is put to sleep (assuming the default of a blocking socket).
 returns: 
   non-negative descriptor if OK, -1 on error

 1 If accept is successful,its return value is a brand-new descriptor automatically 
   created by the kernel. This new descriptor refers to the TCP connection with 
   the client.
 2 When discussing @accept, we call the first argument to accept the listening 
   socket (the descriptor created by socket and then used as the first argument 
   to both @bind and @listen ) , and we call the return value from accept the 
   connected socket.
 3 A given server normally creates only one listening socket, which then exists 
   for the lifetime of the server.The kernel creates one connected socket for 
   each client connection that is accepted (i.e., for which the TCP three-way 
   handshake completes). When the server is finished serving a given client, the 
   connected socket is closed.
 4 服务器accept要第三个握手完成才返回。
 5 signal was caught by the parent(例如子进程终止) while the parent was blocked 
   in a slow system call (accept), the kernel causes the accept to return an error 
   of EINTR (interrupted system call). 
 ******************************************************************************/
int accept (int sockfd, struct sockaddr *cliaddr, socklen_t *addrlen);
 
/******************************************************************************
 Both return: 0 if OK, -1 on error
  
 These two functions return either the local protocol address associated with a 
 socket (getsockname) or the foreign protocol address associated with a socket 
 (getpeername).the final argument for both functions is a value-result argument. 
 That is, both functions fill in the socket address structure pointed to by 
 localaddr or peeraddr.

 These two functions are required for the following reasons:
 1 After connect successfully returns in a TCP client that does not call bind, 
   @getsockname returns the local IP address and local port number assigned to 
   the connection by the kernel.
 2 After calling @bind with a port number of 0 (telling the kernel to choose the 
   local port number), @getsockname returns the local port number that was assigned.
 3 @getsockname can be called to obtain the address family of a socket 
 4 In a TCP server that binds the wildcard IP address , once a connection is 
   established with a client (accept returns successfully), the server can call 
   @getsockname to obtain the local IP address assigned to the connection. The 
   socket descriptor argument in this call must be that of the connected socket, 
   and not the listening socket.
 ******************************************************************************/
int getsockname(int sockfd, struct sockaddr *localaddr, socklen_t *addrlen);
int getpeername(int sockfd, struct sockaddr *peeraddr, socklen_t *addrlen);
   
  
/************************************************************************************
 @howto:SHUT_RD
Returns: 0 if OK, –1 on error

 The normal way to terminate a network connection is to call the @close function.But,
 there are two limitations with @close that can be avoided with @shutdown:
 1 close decrements the descriptor's reference count and closes the socket only if the 
   count reaches 0. With shutdown, we can initiate TCP's normal connection termination 
   sequence(the four segments beginning with a FIN ),regardless of the reference count.
 2 close terminates both directions of data transfer, reading and writing. Since a TCP 
   connection is full-duplex, there are times when we want to tell the other end that 
   we have finished sending,even though that end might have more data to send us.
   
The three SHUT_xxx names are defined by the POSIX specification. Typical values for the @howto argument that you will encounter 
will be 0 (close the read half), 1 (close the write half), and 2 (close the read half and the write half).
************************************************************************************/
int shutdown(int sockfd, int howto);

/************************************************************************************
 @sockfd:
 @buff  :接收的数据存放在这个缓冲区里
 @nbytes:希望接收的字节数
 @flag:
 @from:
   数据是谁发来的,可以为NULL,表示不关心来源,此时addrlen也是NULL.
   the protocol address of who sent the datagram. The number of bytes stored in this 
   socket address structure is also returned to the caller in the integer pointed to 
   by @addrlen. 
 @addrlen:
    If the from argument to @recvfrom is a null pointer, then the corresponding length 
    argument (addrlen) must also be a null pointer, and this indicates that we are not 
    interested in knowing the protocol address of who sent us data. 
 @return: number of bytes read if OK, –1 on error

 Both @recvfrom and @sendto can be used with TCP, although there is normally no reason 
 to do so.

 1 可以返回0,并不表示对端关闭。
************************************************************************************/
ssize_t recvfrom(int sockfd, void *buff, size_t nbytes, int flags, 
struct sockaddr *from, socklen_t *addrlen);

 
/************************************************************************************
 @sockfd:
 @buff  :发送的数据都在这个缓冲区里
 @nbytes:发送的字节数，可以为0,此时发送的只有报文头没有数据区.
 @flag:
 @to:
    The @to argument for @sendto is a socket address structure containing the protocol 
    address (e.g., IP address and port number) of where the data is to be sent. The 
    size of this socket address structure is specified by @addrlen.
 @addrlen:
 @return: number of bytes written if OK, –1 on error

 Writing a datagram of length 0 is acceptable. In the case of UDP, this results in an 
 IP datagram containing an IP header(normally 20 bytes for IPv4 and 40 bytes for IPv6), 
 an 8-byte UDP header, and no data. This also means that a return value of 0 from 
 @recvfrom is acceptable for a datagram protocol: It does not mean that the peer has 
 closed the connection, as does a return value of 0 from read on a TCP socket. Since 
 UDP is connectionless, there is no such thing as closing a UDP connection.
 
 1 一般用于UDP,也可以用于TCP(一般不用)
 2 The client must specify the server's IP address and port number for the call to @sendto.
 3 a successful return from a UDP output operation only means there was room for the 
   resulting IP datagram on the interface output queue. 
************************************************************************************/
ssize_t sendto(int sockfd, const void *buff, size_t nbytes, int flags, 
const struct sockaddr *to, socklen_t addrlen);
 

/************************************************************************************
    flags              说明           recv      send
 MSG_DONTROUTE     绕过路由表查找      n         y
 MSG_DONTWAIT	     仅本操作非阻塞      y         y
 MSG_OOB           发送或接收带外数据  y         y
 MSG_PEEK          窥看外来消息        y         n
 MSG_WAITALL       等待所有数据        y	        n 

 @flags
    如果flags为0,则和read,write一样的操作.
 return: 
    number of bytes read or written if OK, –1 on error 
************************************************************************************/
ssize_t recv(int sockfd, void *buff, size_t nbytes, int flags);
ssize_t send(int sockfd, const void *buff, size_t nbytes, int flags);


/*Both return: number of bytes read or written if OK, –1 on error */
ssize_t recvmsg(int sockfd, struct msghdr *msg, int flags);

/*return: number of bytes read or written if OK, –1 on error */  
ssize_t sendmsg(int sockfd, struct msghdr *msg, int flags);





  





/*
If how is SHUT_RD,then reading from the socket is disabled. If how is SHUT_WR,then we can’t use the socket for transmitting data. 
We  can use SHUT_RDWR to disable both data transmission and reception.*/
#include <sys/socket.h>
int shutdown(int sockfd,int how);

/*-----------------------------------------------------------------------------------
 The socket mechanism provides two socket-option interfaces for us to control the be-
 havior of sockets. One interface is used to set an option, and another interface al-
 lows us to query the state of an option. We can get and set three kinds of options:
 1. Generic options that work with all socket types
 2. Options that are managed at the socket level, but depend on the underlying proto-
    cols for support
 3. Protocol-specific options unique to each individual protocol
 The Single UNIX Specification defines only the socket-layer options (the first two -
 option types in the preceding list).

 @sockfd 
     must refer to an open socket descriptor. 
 @level  SOL_SOCKET
	The @level argument identifies the protocol to which the option applies. If the - 
	option is a generic socket-level option, then level is set to SOL_SOCKET. Otherw-
	ise, @level is set to the number of the protocol that controls the option. Examp-
	les are IPPROTO_TCP for TCP options and IPPROTO_IP for IP options. 
 @optname  SO_LINGER
 @optval   
	The @optval argument points to a data structure or an integer, depending on the -
	option. Some options are on/off switches. If the integer is nonzero, then the op-
	tion is enabled. If the integer is zero, then the option is disabled. 
 @optlen2  
     specifies the size of the object to which val points.
 @optlen1
     The optlen2 argument is a pointer to an integer. Before calling getsockopt, we -
     set the integer to the size of the buffer where the option is to be copied. If -
     the actual size of the option is greater than this size, the option is  silently 
     truncated. If the actual size of the option is less than this size, then the in-
     teger is updated with the actual size on return.
 @return: 
     0 if OK,–1 on error 
 @example dg_cli_timeout3
 ----------------------------------------------------------------------------------*/
int getsockopt(int sockfd, int level, int optname, void *optval, socklen_t *optlen1);
int setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen2);
 
/*
具体使用如下： 
1.closesocket（一般不会立即关闭而经历TIME_WAIT的过程）后想继续重用该socket： 
BOOL bReuseaddr=TRUE; 
setsockopt(s,SOL_SOCKET ,SO_REUSEADDR,(const char*)&bReuseaddr,sizeof(BOOL));

2. 如果要已经处于连接状态的soket在调用closesocket后强制关闭，不经历 TIME_WAIT的过程： 
BOOL bDontLinger = FALSE; 
setsockopt(s,SOL_SOCKET,SO_DONTLINGER,(const char*)&bDontLinger,sizeof(BOOL));

3.在send(),recv()过程中有时由于网络状况等原因，发收不能预期进行,而设置收发时限： 
int nNetTimeout=1000;//1秒 
//发送时限 
setsockopt(socket，SOL_S0CKET,SO_SNDTIMEO，(char *)&nNetTimeout,sizeof(int)); 
//接收时限 setsockopt(socket，SOL_S0CKET,SO_RCVTIMEO，(char *)&nNetTimeout,sizeof(int)); 

 
4.在send()的时候，返回的是实际发送出去的字节(同步)或发送到socket缓冲区的字节 (异步);系统默认的状态发送和接收一次为8688字节(约为8.5K)； 
在实际的过程中发送数据和接收数据量比较大，可以设置socket缓冲区，而避免了send(),recv()不断的循环收发： 
// 接收缓冲区 
int nRecvBuf=32*1024; 
//设置为32K 
setsockopt(s,SOL_SOCKET,SO_RCVBUF,(const char*)&nRecvBuf,sizeof(int)); 
//发送缓冲区 int nSendBuf=32*1024;//设置为32K 
setsockopt(s,SOL_SOCKET,SO_SNDBUF,(const char*)&nSendBuf,sizeof(int));
 
5. 如果在发送数据的时，希望不经历由系统缓冲区到socket缓冲区的拷贝而影响程序的性能： 
int nZero=0; 
setsockopt(socket，SOL_S0CKET,SO_SNDBUF，(char *)&nZero,sizeof(nZero));
 
6.同上在recv()完成上述功能(默认情况是将socket缓冲区的内容拷贝到系统缓冲区)： 
int nZero=0; 
setsockopt(socket，SOL_S0CKET,SO_RCVBUF，(char *)&nZero,sizeof(int));
 
7.一般在发送UDP数据报的时候，希望该socket发送的数据具有广播特性： 
BOOL bBroadcast=TRUE; 
setsockopt(s,SOL_SOCKET,SO_BROADCAST,(const char*)&bBroadcast,sizeof(BOOL));
 
8.在client连接服务器过程中，如果处于非阻塞模式下的socket在connect()的过程中可以设置connect()延时,直到accpet()被呼叫(本函数设置只有在非阻塞的过程中有显著的作用，在阻塞的函数调用中作用不大) 
BOOL bConditionalAccept=TRUE; 
setsockopt(s,SOL_SOCKET,SO_CONDITIONAL_ACCEPT,(const char*)&bConditionalAccept,sizeof(BOOL));
 
9.如果在发送数据的过程中(send()没有完成，还有数据没发送)而调用了closesocket(),以前我们一般采取的措施是"从容关闭"shutdown(s,SD_BOTH),但是数据是肯定丢失了，如何设置让程序满足具体应用的要求(即让没发完的数据发送出去后在关闭socket)？ 
struct linger 
{ 
u_short l_onoff; 
u_short l_linger; 
}; 
linger m_sLinger; 
m_sLinger.l_onoff=1;//(在closesocket()调用,但是还有数据没发送完毕的时候容许逗留) 如果m_sLinger.l_onoff=0;则功能和2.)作用相同; 
m_sLinger.l_linger=5; //(容许逗留的时间为5秒) 
setsockopt(s,SOL_SOCKET,SO_LINGER,(const char*)&m_sLinger,sizeof(linger));

*/
 
#include <unistd.h>  
/************************************************************************************
 @function:
    The normal Unix close function is also used to close a socket and terminate a TCP 
    connection.
 @returns: 
    0 if OK, -1 on error

 The default action of close with a TCP socket is to mark the socket as closed and 
 return to the process immediately.The socket descriptor is no longer usable by the 
 process:It cannot be used as an argument to read or write.But,TCP will try to send 
 any data that is already queued to be sent to the other end, and after this occurs, 
 the normal TCP connection termination sequence takes place . we will describe the 
 SO_LINGER socket option, which lets us change this default action with a TCP socket.
 ***********************************************************************************/
int close (int sockfd);

