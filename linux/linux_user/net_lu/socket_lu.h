/*-----------------------------------------------------------------------------------
                   Datatypes required by the POSIX specification
 -----------------------------------------------------------------------------------
 Datatype    |                 Description                           |    Header   
 ------------|-------------------------------------------------------|------
 int8_t      | Signed 8-bit interger                                 | <sys/types.h>
 uint8_t     | Unsigned 8-bit interger                               | <sys/types.h>
 int16_t     | Signed 16-bit interger                                | <sys/types.h>
 uint16_t    | Unsigned 16-bit interger                              | <sys/types.h>
 int32_t     | Signed 32-bit interger                                | <sys/types.h>
 uint32_t    | Unsigned 32-bit interger                              | <sys/types.h>
 ------------|-------------------------------------------------------|--------------
 sa_family_t | Address family of socket address structure            | <sys/socket.h>
 socklet_t   | Length of socket address structure, normally uint32_t | <sys/socket.h>
 ------------|-------------------------------------------------------|----------------
 in_addr_t   | IPv4 address, normally uint32_t                       | <netinet/in.h>
 in_port_t   | TCP or UDP port, normally uint16_t                    | <netinet/in.h>
 ------------------------------------------------------------------------------------
 ----------------------------------------------------------------------------------*/

/* socklent_t   uint32_t */

#include<netinet/in.h>
typedef uint32_t in_addr_t;  /*  IPv4 address, normally uint32_t */


/*-----------------------------------------------------------------------------------
 Socket Address Structures
 Most socket functions require a pointer to a socket address structure as an argumen-
 t. Each supported protocol suite defines its own socket address structure. The names 
 of these structures begin with sockaddr_ and end with a unique suffix for each prot-
 ocol suite.
 ----------------------------------------------------------------------------------*/
 
#define INET_ADDRSTRLEN   16 /* for IPv4 dotted-decimal  <netinet/in.h>*/
#define INET6_ADDRSTRLEN  46 /* for IPv6 hex string  <netinet/in.h>*/

/*-----------------------------------------------------------------------------------
 An IPv4 socket address structure, commonly called an "Internet socket address struc-
 ture," is named sockaddr_in and is defined by including the <netinet/in.h> header.
 ------------------------------------------------------------------------------------
 @sin_len
     The length member, sin_len, was added with 4.3BSD-Reno, when support for the OSI 
     protocols was added (Figure 1.15). Before this release, the first member was   -
     sin_family, which was historically an unsigned short. Not all vendors support  a 
     length field for socket address structures and the POSIX specification does  not 
     require this member.
 @sin_family
 @sin_port
 @sin_addr
     The POSIX specification requires only three members in the structure:sin_family, 
     sin_addr, and sin_port. It is acceptable for a POSIX-compliant implementation to 
     define additional structure members, and this is normal for an Internet socket -
     address structure. Almost all implementations add the sin_zero member so that a-
     ll socket address structures are at least 16 bytes in size.
 @sin_zero
     The sin_zero member is unused, but we always set it to 0 when filling in one  of 
     these structures. Although most uses of the structure do not require that this -
     member be 0, when binding a non-wildcard IPv4 address, this member must be 0   -
     (pp. 731–732 of TCPv2).

 Socket address structures are used only on a given host: The structure itself is not 
 communicated between different hosts, although certain fields (e.g., the IP  address 
 and port) are used for communication.    
 ----------------------------------------------------------------------------------*/
struct in_addr 
{
  in_addr_t   s_addr;           /* 32-bit IPv4 address network byte ordered */
};

struct sockaddr_in /* POSIX definition */
{
  uint8_t         sin_len;      /* length of structure (16) */
  sa_family_t     sin_family;   /* AF_INET */
  in_port_t       sin_port;     /* 16-bit TCP or UDP port number network byte ordered */
  struct in_addr  sin_addr;     /* 32-bit IPv4 address  network byte ordered */
  char            sin_zero[8];  /* unused */
};


#include <sys/socket.h>

/*-----------------------------------------------------------------------------------
 http://www.cnblogs.com/youxin/p/3965962.html

 windows平台下:
 头文件：#include<ws2tcpip.h>

 linux平台下：
 下面两个头文件都有定义：
 1）#include <sys/socket.h>
 2）#include <unistd.h>


 详细定义：typedef int socklen_t;

 翻译：

 任何完整的库必须定义socklen_t和int相同的尺寸大小。别的事情打破了BSD套接字层的填充。
 POSIX起初确实将其定义为size_t。我已经向他们大声诉说这件事情。定义其为size_t类型是非
 常糟糕的，特别是size_t在64位操作系统上，很少和int保持同样的尺寸大小。例如，BSD套接
 字接口只接受和int尺寸大小的值，不管如何，POSIX组织最终想出一个办法，创建socklen_t的
 类型，他们本不该插手这个类型。但是曾经他们确实认为为它定义一个类型是必须的，为了某些
 令人费解的理由。
 ----------------------------------------------------------------------------------*/
typedef int socklen_t;


/*-----------------------------------------------------------------------------------
	  The generic socket address structure: sockaddr.  <sys/socket.h>
 ----------------------------------------------------------------------------------*/
struct sockaddr 
{
  uint8_t      sa_len;
  sa_family_t  sa_family;    /* address family: AF_xxx value */
  char         sa_data[14];  /* protocol-specific address */
};


/*
 Unix domain socket address structure, which is defined by including the <sys/un.h> 
 header.
 
 POSIX renames the Unix domain protocols as "local IPC," to remove the dependence on 
 the Unix OS. The historical constant AF_UNIX becomes AF_LOCAL.Nevertheless,we still 
 use the term "Unix domain" as that has become its de facto name, regardless of the 
 underlying OS. Also, even with POSIX  attempting to make these OS-independent, the 
 socket address structure still retains the _un suffix!
 
 @sun_path
    The pathname stored in the sun_path array must be null-terminated.The unspecified 
    address is indicated by a null string as the pathname, that is, a structure with 
    sun_path[0] equal to 0. This is the Unix domain equivalent of the IPv4 INADDR_ANY 
    constant and the IPv6 IN6ADDR_ANY_INIT constant.
*/
#include <sys/un.h>
struct sockaddr_un {
  sa_family_t sun_family;     /* AF_LOCAL */
  char        sun_path[104];  /* null-terminated pathname */
};

#define SUN_LEN /* is provided and it takes a pointer to a sockaddr_un structure and 
returns the length of the structure,including the number of non-null bytes in the pathname.*/ 

/************************************************************************************
 @msg_name @msg_namelen
    The @msg_name and @msg_namelen members are used when the socket is not connected 
    (e.g., an unconnected UDP socket).They are similar to the fifth and sixth arguments 
    to @recvfrom and @sendto: @msg_name points to a socket address structure in which 
    the caller stores the destination's protocol address for @sendmsg, or in which 
    @recvmsg stores the sender's protocol address. If a protocol address does not need 
    to be specified (e.g., a TCP socket or a connected UDP socket), @msg_name should 
    be set to a null pointer. @msg_namelen is a value for @sendmsg, but a value-result 
    for @recvmsg.
 @msg_iov  @msg_iovlen
    The @msg_iov and @msg_iovlen members specify the array of input or output buffers 
    (the array of iovec structures),similar to the second and third arguments for @readv 
    or @writev. 
 @msg_control  @msg_controllen
    The @msg_control and @msg_controllen members specify the location and size of the 
    optional ancillary data. msg_controllen is a value-result argument for @recvmsg. 
************************************************************************************/
struct msghdr {
void		 *msg_name; 	   /* protocol address */
socklen_t	  msg_namelen;	   /* size of protocol address */
struct iovec *msg_iov;		   /* scatter/gather array */
int 		  msg_iovlen;	   /* # elements in msg_iov */
void		 *msg_control;	   /* ancillary data (cmsghdr struct) */
socklen_t	  msg_controllen;  /* length of ancillary data */
int 		  msg_flags;	   /* flags returned by recvmsg() */
};

/*----------------------------------- @getsockopt @level --------------------------*/
#define SOL_SOCKET /* 基本套接口 */
#define IPPROTO_IP
#define IPPRO_TCP
/*----------------------------------- @getsockopt @optname ------------------------*/

#include <sys/socket.h>
/*
 @l_onoff @l_linger
    If @l_onoff is 0, the option is turned off. The value of @l_linger is ignored and 
    the previously discussed TCP default applies: @close returns immediately.
    If @l_onoff is nonzero and @l_linger is zero, TCP aborts the connection when it is 
    closed.That is,TCP discards any data still remaining in the socket send buffer and 
    sends an RST to the peer,not the normal four-packet connection termination sequence.

    If @l_onoff is nonzero and @l_linger is nonzero, then the kernel will linger when 
    the socket is closed . That is, if there is any data still remaining in the socket 
    send buffer,the process is put to sleep until either: (i) all the data is sent and 
    acknowledged by the peer TCP,or (ii) the linger time expires.If the socket has been 
    set to nonblocking, it will not wait for the close to complete, even if the linger 
    time is nonzero. 
    When using this feature of the SO_LINGER option,it is important for the application 
    to check the return value from close, because if the linger time expires before the 
    remaining data is sent and acknowledged,close returns EWOULDBLOCK and any remaining 
    data in the send buffer is discarded.
*/
struct linger {      
    int l_onoff;  //0=off, nonzero=on(开关)      
    int l_linger; //linger time(延迟时间)
};

/*-----------------------------------------------------------------------------------
                               Socket Options
 -----------------------------------------------------------------------------------
 SO_RCVTIMEO SO_SNDTIMEO 
     These two socket options allow us to place a timeout on socket receives and sen-
     ds. Notice that the argument to the two sockopt functions is a pointer to a tim-
     eval structure. This lets us specify the timeouts in seconds and microseconds. -
     We disable a timeout by setting its value to 0 seconds and 0 microseconds.  Both 
     timeouts are disabled by default. The receive timeout affects the five input fu-
     nctions: read, readv, recdv, recvfrom, and recvmsg. The send timeout affects the 
     five output functions: write, writev, send, sendto, and sendmsg. 
 SO_ERROR
    When an error occurs on a socket, the protocol module in a Berkeley-derived kernel 
    sets a variable named @so_error for that socket to one of the standard Unix Exxx 
    values. This is called the pending error for the socket.The process can then obtain 
    the value of so_error by fetching the SO_ERROR socket option. The integer value 
    returned by getsockopt is the pending error for the socket. The value of so_error 
    is then reset to 0 by the kernel
 SO_LINGER    struct linger
 ----------------------------------------------------------------------------------*/
#define SO_RCVTIMEO  /* struct timeval */
#define SO_SNDTIMEO 
#define SO_REUSEADDR /* 允许重用本地地址 tcp_udp_serv*/
#define SO_LINGER
#define SO_ERROR  /* eg:connect_nonb */

/*-----------------------------------------------------------------------------------
There are two basic types of options: binary options that enable or disable a certain 
feature (flags), and options that fetch and return specific values that we can either 
set or examine (values). The column labeled "Flag" specifies if the option is a flag 
option. When calling getsockopt for these flag options, *optval is an integer. The 
value returned in *optval is zero if the option is disabled, or nonzero if the option 
is enabled. Similarly,setsockopt requires a nonzero *optval to turn the option on,and 
a zero value to turn the option off. If the "Flag" column does not contain a "?," then 
the option is used to pass a value of the specified datatype between the user process 
and the system.

选项名称　　　　　　　　说明　　　　　　　　　　　　　　　　　　数据类型 
======================================================================== 
　　　　　　　　　　　　SOL_SOCKET 
------------------------------------------------------------------------ 
SO_BROADCAST　　　　　　允许发送广播数据　　　　　　　　　　　　int 
SO_DEBUG　　　　　　　　允许调试　　　　　　　　　　　　　　　　int 
SO_DONTROUTE　　　　　　不查找路由　　　　　　　　　　　　　　　int 
SO_ERROR　　　　　　　　获得套接字错误　　　　　　　　　　　　　int 
SO_KEEPALIVE　　　　　　保持连接　　　　　　　　　　　　　　　　int 
SO_LINGER　　　　　　　 延迟关闭连接　　　　　　　　　　　　　　struct linger 
SO_OOBINLINE　　　　　　带外数据放入正常数据流　　　　　　　　　int 
SO_RCVBUF　　　　　　　 接收缓冲区大小　　　　　　　　　　　　　int 
SO_SNDBUF　　　　　　　 发送缓冲区大小　　　　　　　　　　　　　int 
SO_RCVLOWAT　　　　　　 接收缓冲区下限　　　　　　　　　　　　　int 
SO_SNDLOWAT　　　　　　 发送缓冲区下限　　　　　　　　　　　　　int 
SO_RCVTIMEO　　　　　　 接收超时　　　　　　　　　　　　　　　　struct timeval 
SO_SNDTIMEO　　　　　　 发送超时　　　　　　　　　　　　　　　　struct timeval 
SO_REUSERADDR　　　　　 允许重用本地地址和端口　　　　　　　　　int 
SO_TYPE　　　　　　　　 获得套接字类型　　　　　　　　　　　　　int 
SO_BSDCOMPAT　　　　　　与BSD系统兼容　　　　　　　　　　　　　 int 
========================================================================
　　　　　　　　　　　　IPPROTO_IP 
------------------------------------------------------------------------
IP_HDRINCL　　　　　　　在数据包中包含IP首部　　　　　　　　　　int 
IP_OPTINOS　　　　　　　IP首部选项　　　　　　　　　　　　　　　int 
IP_TOS　　　　　　　　　服务类型 
IP_TTL　　　　　　　　　生存时间　　　　　　　　　　　　　　　　int 
========================================================================
　　　　　　　　　　　　IPPRO_TCP 
------------------------------------------------------------------------
TCP_MAXSEG　　　　　　　TCP最大数据段的大小　　　　　　　　　　 int 
TCP_NODELAY　　　　　　 不使用Nagle算法　　　　　　　　　　　　 int 
========================================================================


 ----------------------------------------------------------------------------------*/









/*-----------------------------------------------------------------------------------
                     @send @recv @flags
-------------------------------------------------------------------------------------
 MSG_DONTROUTE:
    是send函数使用的标志.这个标志告诉IP协议.目的主机在本地网络上面,没有必要查找路由表。
    这个标志一般用网络诊断和路由程序里面.
 MSG_OOB:
    表示可以接收和发送带外的数据.关于带外数据我们以后会解释的.
MSG_PEEK:
    是recv函数的使用标志,表示只是从系统缓冲区中读取内容,而不清除系统缓冲区的内容.这样
    下次读的时候,仍然是一样的内容.一般在有多个进程读写数据时可以使用这个标志.
MSG_WAITALL
    是recv函数的使用标志,表示等到所有的信息到达时才返回.使用这个标志的时候recv回一直阻
    塞,直到指定的条件满足,或者是发生了错误. 
    1)当读到了指定的字节时,函数正常返回.返回值等于len 
    2)当读到了文件的结尾时,函数正常返回.返回值小于len 
    3) 当操作发生错误时,返回-1,且设置错误为相应的错误号(errno)
*/
#define MSG_DONTROUTE
#define MSG_DONTWAIT
#define MSG_PEEK
#define MSG_WAITALL

/*
---->套接字地址
每个协议族都定义它自己的套接字地址结构。

ipv4套接字地址结构,也称为网际套接字地址结构 struct sockaddr_in
通用套接字地址结构 

套接字是通信端点的抽象，访问套接字需要使用套接字描述符(与文件描述符类似)。 
套接字描述符在UNIX系统是用文件描述符实现的。


---->原始套接字
原始套接字可以读写内核没有处理的IP数据包，而流套接字（就是TCP流）只能读取TCP协议的数
据，数据包套接字只能读取UDP协议的数据。因此，如果要访问其他协议发送数据必须使用原始
套接字。

原始套接字提供tcp和udp套接字不提供的以下三种能力
1 读写icmpv4、igmpv4、icmpv6等分组
2 读写内核不处理其协议字段的ipv4数据报
3 控制ipv4头部

原始套接字的使用场合
1 特殊用途的探测应用
2 基于数据包捕获的应用
3 特殊用途的传输应用

*************************************************************************************
                            Unix Domain Protocols
*************************************************************************************
The Unix domain protocols are not an actual protocol suite, but a way of performing 
client/server communication on a single host using the same API that is used for clients 
and servers on different hosts. The Unix domain protocols are an alternative to the 
interprocess communication (IPC) methods described in Volume 2 of this series, when 
the client and server are on the same host. Details on the actual implementation of 
Unix domain sockets in a Berkeley-derived kernel are provided in part 3 of TCPv3.

Two types of sockets are provided in the Unix domain: stream sockets (similar to TCP) 
and datagram sockets (similar to UDP). Even though a raw socket is also provided, its 
semantics have never been documented, it is not used by any  program that the authors 
are aware of, and it is not defined by POSIX.

The protocol addresses used to identify clients and servers in the Unix domain are 
pathnames within the normal filesystem. Recall that IPv4 uses a combination of 32-bit 
addresses and 16-bit port numbers for its protocol addresses, and IPv6 uses a combination 
of 128-bit addresses and 16-bit port numbers for its protocol addresses. These pathnames 
are not normal Unix files: We cannot read from or write to these files except from a 
program that has associated the pathname with a Unix domain socket.

*/

#define INADDR_ANY

#define SOMAXCONN /* @listen @backlog*/

/*-----------------------------------------------------------------------------------
                 Protocol family constants for socket function
 ------------------------------------------------------------------------------------
 AF_KEY
    It provides support for cryptographic security. Similar to the way that a routing 
    socket (AF_ROUTE) is an interface to the kernel's routing table,the key socket is 
    an interface into the kernel's key table.
 PF_INET
    在Unix/Linux系统中，在不同的版本中这两者有微小差别.对于BSD,是AF,对于POSIX是PF.理论
    上建立socket时是指定协议，应该用PF_xxxx，设置地址时应该用AF_xxxx。当然AF_INET和
    PF_INET的值是相同的，混用也不会有太大的问题。
 ----------------------------------------------------------------------------------*/
#define AF_INET   /* ipv4 protocols */
#define PF_INET   /* */
#define AF_INET6  /* ipv6 protocols */
#define AF_LOCAL  /* unix domain protocols */
#define AF_ROUTE  /* routing sockets */
#define AF_KEY	  /* Key socket*/

/*-----------------------------------------------------------------------------------
				 type of socket for socket function
 ------------------------------------------------------------------------------------
 @SOCK_STREAM
     stream socket TCP 协议,这样会提供按顺序的,可靠,双向,面向连接的比特流. 
 @SOCK_DGRAM
     datagram socket UDP协议,这样只会提供定长的,不可靠,无连接的通信.
 @SOCK_PACKET
     Linux supports a new socket type, SOCK_PACKET, that provides access to the data-
     link.
 ----------------------------------------------------------------------------------*/
#define SOCK_STREAM    /* */
#define SOCK_DGRAM     /* */
#define SOCK_SEQPACKET /* sequenced packet socket */
#define SOCK_RAW       /* raw socket */
#define SOCK_PACKET	   /* */

/****************************** socket protocol *******************************/
#define IPPROTO_TCP   /* TCP transport protocol */
#define IPPROTO_UDP   /* UDP transport protocol */
#define IPPROTO_SCTP  /* SCTP transport protocol */

/**************************** @connect error type ****************************/
#define ETIMEDOUT
#define ECONNREFUSED
#define EHOSTUNREACH
#define ENETUNREACH 

/********************************* @shutdown @howto *********************************/
#define SHUT_RD /* The read half of the connection is closed— No more data can be 
received on the socket and any data currently in the socket receive buffer is discarded. 
The process can no longer issue any of the read functions on the socket.Any data received 
after this call for a TCP socket is acknowledged and then silently discarded.*/
#define SHUT_WR /* The write half of the connection is closed— In the case of TCP,
this is called a half-close.Any data currently in the socket send buffer will be sent, 
followed by TCP's normal connection termination sequence.As we mentioned earlier,this 
closing of the write half is done regardless of whether or not the socket descriptor's 
reference count is currently greater than 0. The process can no longer issue any of the 
write functions on the socket.*/
#define SHUT_RDWR /* The read half and the write half of the connection are both closed
This is equivalent to calling shutdown twice: first with SHUT_RD and then with SHUT_WR.*/


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

 
#include <sys/select.h>
 
#define FD_SETSIZE /* a constant in <sys/select.h> that specifies the maximum number 
 of descriptors (often 1,024) */


