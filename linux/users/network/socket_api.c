#include <arpa/inet.h>

/*
function:converts the C character string pointed to by @strptr into its 32-bit binary network byte ordered value, 
         which is stored through the pointer @addrptr.
Returns: 1 if string was valid, 0 on error*/
int inet_aton(const char *strptr, struct in_addr *addrptr);
 

/*Returns: 32-bit binary network byte ordered IPv4 address; INADDR_NONE(0xffffffff) if error*/
in_addr_t inet_addr(const char *strptr);
 

/*Returns: pointer to dotted-decimal string
The inet_ntoa function converts a 32-bit binary network byte ordered IPv4 address into its corresponding dotted-decimal string. 
The string pointed to by the return value of the function resides in static memory. This means the function is not reentrant*/ 
char *inet_ntoa(struct in_addr inaddr);
 

/*
@family:AF_INET or AF_INET6
Returns: 1 if OK, 0 if input not a valid presentation format, -1 on error

1 If family is not supported, both functions return an error with errno set to EAFNOSUPPORT
2 The letters "p" and "n" stand for presentation and numeric. The presentation format for an address is often an ASCII string 
  and the numeric format is the binary value that goes into a socket address structure.

*/  
int inet_pton(int family, const char *strptr, void *addrptr);
  
 
/*
@family :地址类型 AF_INET or AF_INET6
@addrptr:这个地址指向的是一个地址的值,把这个值转换成字符串
@strptr :返回转换后的结果,不能是NULL.
@len    :缓存区strptr的大小，避免溢出，如果缓存区太小无法存储地址的值，则返回一个空指针，并将errno置为ENOSPC
  
Returns: pointer to result if OK, NULL on error

实例
struct sockaddr_in   addr;
inet_ntop(AF_INET, &addr.sin_addr, str, sizeof(str));

struct sockaddr_in6   addr6;
inet_ntop(AF_INET6, &addr6.sin6_addr, str, sizeof(str));*/ 
 const char *inet_ntop(int family, const void *addrptr, char *strptr, size_t len);
  
 
#define INET_ADDRSTRLEN       16       /* for IPv4 dotted-decimal */
#define INET6_ADDRSTRLEN      46       /* for IPv6 hex string */

/****************************** protocol family *******************************/
#define AF_INET   /* ipv4 protocols */
#define AF_INET6  /* ipv6 protocols */
#define AF_LOCAL  /* unix domain protocols */
#define AF_ROUTE  /* routing sockets */
#define AF_KEY	  /* It provides support for cryptographic security. Similar to 
the way that a routing socket (AF_ROUTE) is an interface to the kernel's routing 
table, the key socket is an interface into the kernel's key table. */

/******************************** socket type *********************************/
#define SOCK_STREAM /*stream socket TCP 协议,这样会提供按顺序的,可靠,双向,面向连
接的比特流. */
#define SOCK_DGRAM /*datagram socket UDP协议,这样只会提供定长的,不可靠,无连接的
通信.*/
#define SOCK_SEQPACKET /*sequenced packet socket*/
#define SOCK_RAW /*raw socket*/
#define SOCK_PACKET	/* Linux supports a new socket type, SOCK_PACKET, that provides 
access to the datalink */

/****************************** socket protocol *******************************/
#define IPPROTO_TCP   /* TCP transport protocol */
#define IPPROTO_UDP   /* UDP transport protocol */
#define IPPROTO_SCTP  /* SCTP transport protocol */

/*******************************************************************************
                | AF_INET  | AF_INET6 | AF_LOCAL | AF_ROUTE | AF_KEY |
 ---------------|----------|----------|----------|----------|--------|
 SOCK_STREAM    | tcp|sctp | tcp|sctp |    yes   |          |        |
 ---------------|----------|----------|----------|----------|--------|
 SOCK_DGRAM     |    udp   |   udp    |    yes   |          |        |
 ---------------|----------|----------|----------|----------|--------| 
 SOCK_SEQPACKET |   sctp   |   sctp   |    yes   |          |        |
 ---------------|----------|----------|----------|----------|--------| 
 SOCK_RAW       |   ipv4   |   ipv6   |          |    yes   |   yes  |
 ---------------|----------|----------|----------|----------|--------|
 Figure 4.5 Combinations of @family and @type for the @socket function
       
 Not all combinations of @socket @family and @type are valid.Figure 4.5 shows the 
 valid combinations, along with the actual protocols that are valid for each pair. 
 The boxes marked "Yes" are valid but do not have handy acronyms. The blank boxes 
 are not supported.    
 ******************************************************************************/

/*******************************************************************************
 @domain: AF_INET等
    协议族,也叫协议域，用来确定通信的特性，包括地址格式.We note that you may 
    encounter AF_UNIX (the historical Unix name)instead of AF_LOCAL (the POSIX 
    name).You may also encounter the corresponding PF_xxx constant as the first 
    argument to socket.
 @type: SOCK_STREAM等 
    套接字类型 
 @protocol: IPPROTO_TCP等
    协议类型 0表示选择domain和type组合的系统默认值。When multiple protocols are 
    supported for the same @domain and socket @type,we can use the @protocol 
    argument to select a particular protocol.The default protocol for a SOCK_STREAM 
    socket in the AF_INET communication domain is TCP(Transmission Control Protocol).
    The default protocol for a SOCK_DGRAM socket in the AF_INET communication domain  
    is UDP(User Datagram  Protocol).
 return:
    成功时返回文件描述符(有的也称为套接字描述符),失败时返回-1,看errno可知道出错
    的详细情况.On success, the socket function returns a small non-negative 
    integer value, similar to a file descriptor. We call this a socket descriptor, 
    or a sockfd.
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
 ******************************************************************************/
int socket(int domain, int type,int protocol);

/**************************** @connect error type ****************************/
#define ETIMEDOUT
#define ECONNREFUSED
#define EHOSTUNREACH
#define ENETUNREACH 

/*******************************************************************************
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
 4 客户端connect发起三次握手,收到ack后返回(第二次握手),而服务器要第三个握手才返回
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
*******************************************************************************/
#include <sys/socket.h>	 
int connect(int sockfd, const struct sockaddr *servaddr, socklen_t addrlen);
	 
	
/*******************************************************************************
 @sockfd:
 @myaddr:要与@sockfd绑定的地址
 @addrlen:地址长度
 function:The @bind function assigns a local protocol address to a socket.
 returns: 0 if OK,-1 on error

1 With TCP, calling @bind lets us specify a port number, an IP address, both, or neither.
  A process can bind a specific IP address to its socket. The IP address must belong to an interface on the host.
2 If a TCP client or server does not do this, the kernel chooses an ephemeral port for the socket when either @connect or @listen is called. 
  It is normal for a TCP client to let the kernel choose an ephemeral port, unless the application requires a reserved port , but it is rare 
  for a TCP server to let the kernel choose an ephemeral port, since servers are known by their well-known port.
3 For a TCP client, this assigns the source IP address that will be used for IP datagrams sent on the socket. 
  For a TCP server, this restricts the socket to receive incoming client connections destined only to that IP address.
4 Normally, a TCP client does not bind an IP address to its socket. The kernel chooses the source IP address when the socket is connected,
  based on the outgoing interface that is used, which in turn is based on the route required to reach the server .
  If a TCP server does not bind an IP address to its socket, the kernel uses the destination IP address of the client's SYN as the server's source IP address .
5 If we specify a port number of 0, the kernel chooses an ephemeral port when bind is called. But if we specify a wildcard IP address, 
  the kernel does not choose the local IP address until either the socket is connected (TCP) or a datagram is sent on the socket (UDP).
6 With IPv4, the wildcard address is specified by the constant INADDR_ANY, whose value is normally 0. 
  The system allocates and initializes the in6addr_any variable to the constant IN6ADDR_ANY_INIT. 
*/	 
#include <sys/socket.h>
int bind (int sockfd, const struct sockaddr *myaddr, socklen_t addrlen);
	  
	 
/*
@sockfd:
@backlog:maximum number of connections the kernel should queue for this socket
function:TCP服务器调用
Returns: 0 if OK, -1 on error

When a socket is created by the socket function, it is assumed to be an active socket, that is, a client socket that will issue 
a connect. The listen function converts an unconnected socket into a passive socket, indicating that the kernel should accept 
incoming connection requests directed to this socket. In terms of the TCP state transition diagram , the call to listen moves 
the socket from the CLOSED state to the LISTEN state.

for a given listening socket, the kernel maintains two queues:
a) An incomplete connection queue, which contains an entry for each SYN that has arrived from a client for which the server is 
   awaiting completion of the TCP three-way handshake. These sockets are in the SYN_RCVD state .
b) A completed connection queue, which contains an entry for each client with whom the TCP three-way handshake has completed. 
   These sockets are in the ESTABLISHED state .
   当服务器收到SYN后，在未完成队列建立条目，并方发送SYN+ACK，当收到ACK后，该条目转移到完成队列，accept能够返回。

*/	  
#include <sys/socket.h>
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

 1 If accept is successful, its return value is a brand-new descriptor automatically 
   created by the kernel.This new descriptor refers to the TCP connection with 
   the client.
 2 When discussing @accept, we call the first argument to @accept the listening 
   socket (the descriptor created by socket and then used as the first argument 
   to both @bind and @listen), and we call the return value from accept the 
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
*******************************************************************************/
#include <sys/socket.h>
int accept (int sockfd, struct sockaddr *cliaddr, socklen_t *addrlen);
 

/*
function:The normal Unix close function is also used to close a socket and terminate a TCP connection.
Returns: 0 if OK, -1 on error

The default action of close with a TCP socket is to mark the socket as closed and return to the process immediately. 
The socket descriptor is no longer usable by the process: It cannot be used as an argument to read or write. 
But, TCP will try to send any data that is already queued to be sent to the other end, and after this occurs, 
the normal TCP connection termination sequence takes place .*/
#include <unistd.h>  
int close (int sockfd);
  
/*Both return: 0 if OK, -1 on error
1 These two functions return either the local protocol address associated with a socket (getsockname) or 
  the foreign protocol address associated with a socket (getpeername).
2 the final argument for both functions is a value-result argument. That is, both functions fill in the 
  socket address structure pointed to by localaddr or peeraddr.
*/
#include <sys/socket.h>
int getsockname(int sockfd, struct sockaddr *localaddr, socklen_t *addrlen);
int getpeername(int sockfd, struct sockaddr *peeraddr, socklen_t *addrlen);
  
 
  
  




/*
If how is SHUT_RD,then reading from the socket is disabled. If how is SHUT_WR,then we can’t use the socket for transmitting data. 
We  can use SHUT_RDWR to disable both data transmission and reception.*/
#include <sys/socket.h>
int shutdown(int sockfd,int how);


/*
在这四个转换函数中,h 代表host, n 代表 network.s 代表short l 代表long 
第一个函数的意义是将本机器上的long数据转化为网络上的long. 其他几个函数的意义也差不多.
*/
unsigned long  int htonl(unsigned long  int hostlong);
unsigned short int htons(unisgned short int hostshort);
unsigned long  int ntohl(unsigned long  int netlong);
unsigned short int ntohs(unsigned short int netshort);

#include <sys/socket.h>

/*
@sockfd:
@buff  :接收的数据存放在这个缓冲区里
@nbytes:希望接收的字节数
@flag:
@from:数据是谁发来的,可以为NULL,表示不关心来源,此时addrlen也是NULL.
@addrlen:目的地地址长度

return: number of bytes read if OK, –1 on error

1 可以返回0,并不表示对端关闭。*/
ssize_t recvfrom(int sockfd, void *buff, size_t nbytes, int flags, struct sockaddr *from, socklen_t *addrlen);

 
/*
@sockfd:
@buff  :发送的数据都在这个缓冲区里
@nbytes:发送的字节数，可以为0,此时发送的只有报文头没有数据区.
@flag:
@to:目的地
@addrlen:目的地地址长度
return: number of bytes written if OK, –1 on error

1 一般用于UDP,也可以用于TCP(一般不用)
2 The client must specify the server's IP address and port number for the call to @sendto.*/
ssize_t sendto(int sockfd, const void *buff, size_t nbytes, int flags, const struct sockaddr *to, socklen_t addrlen);
 

 


#include <sys/socket.h>

#define SHUT_RD
#define SHUT_WR
#define SHUT_RDWR
/*
@howto:SHUT_RD   关闭读半部,套接字缓冲区中的数都被丢弃,来自对端的数据都被确认,然后悄然丢弃。
       SHUT_WR   关闭写半部(即使引用计数不为0),套接字缓冲区的数据将被发送,后跟tcp连接终止序列,
       SHUT_RDWR The read half and the write half of the connection are both closed— 
                 This is equivalent to calling shutdown twice: first with SHUT_RD and then with SHUT_WR. 
Returns: 0 if OK, –1 on error


The three SHUT_xxx names are defined by the POSIX specification. Typical values for the @howto argument that you will encounter 
will be 0 (close the read half), 1 (close the write half), and 2 (close the read half and the write half).
*/
int shutdown(int sockfd, int howto);
 

 
#include <poll.h>
struct pollfd {
  int     fd;       /* descriptor to check */
  short   events;   /* events of interest on fd */
  short   revents;  /* events that occurred on fd */
};

int poll (struct pollfd *fdarray, unsigned long nfds, int timeout);
  

#include <sys/socket.h>
#define SOL_SOCKET /*基本套接口*/
  #define SO_REUSEADDR /*允许重用本地地址*/
  #define SO_RCVTIMEO  /*接收超时 struct timeval */
  
/*@sockfd:打开的套接字描述符
  @level : 指定选项代码的类型
           SOL_SOCKET: 基本套接口
           IPPROTO_IP: IPv4套接口
           IPPROTO_IPV6: IPv6套接口
           IPPROTO_TCP: TCP套接口
  @iptname:
  @optval:返回套接字当前的选项值
  @iptlen:
  return: 0 if OK,–1 on error*/ 
int getsockopt(int sockfd, int level, int optname, void *optval, socklen_t *optlen);
 
/*@sockfd:打开的套接字描述符
  @level
  @iptname:
  @optval:存放套接字待设置的新值
  @iptlen:
return: 0 if OK,–1 on error*/ 
int setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen);
 

 

