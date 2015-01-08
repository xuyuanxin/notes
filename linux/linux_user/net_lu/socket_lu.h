
/* socklent_t   uint32_t */

#include<netinet/in.h>

struct sockaddr {          /*通用套接字地址结构*/
  uint8_t      sa_len;
  sa_family_t  sa_family;    /* address family: AF_xxx value */
  char         sa_data[14];  /* protocol-specific address */
};


struct in_addr {
  in_addr_t   s_addr;           /* 32-bit IPv4 address network byte ordered */
};

struct sockaddr_in {         /*ipv4套接字地址结构*/
  uint8_t         sin_len;      /* length of structure (16) */
  sa_family_t     sin_family;   /* AF_INET */
  in_port_t       sin_port;     /* 16-bit TCP or UDP port number network byte ordered */
  struct in_addr  sin_addr;     /* 32-bit IPv4 address  network byte ordered */
  char            sin_zero[8];  /* unused */
};


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
#define SO_RCVTIMEO  /* 接收超时 struct timeval */
#define SO_REUSEADDR /* 允许重用本地地址 tcp_udp_serv*/
#define SO_LINGER

/*----------------------------------- @recv @flags ------------------------*/
#define MSG_DONTROUTE
#define MSG_DONTWAIT

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

