#include <netdb.h>

struct hostent {
   char  *h_name;       /* official (canonical) name of host .表示的是主机的规范名。例如www.google.com的规范名其实是www.l.google.com。*/
   char **h_aliases;    /* pointer to array of pointers to alias names.
                              表示的是主机的别名.www.google.com就是google他自己的别名。有的时候，有的主机可能有好几个别名，
                              这些，其实都是为了易于用户记忆而为自己的网站多取的名字。*/
   int    h_addrtype;   /* host address type: AF_INET .表示的是主机ip地址的类型，到底是ipv4(AF_INET)，还是pv6(AF_INET6)*/
   int    h_length;     /* length of address: 4. 表示的是主机ip地址的长度*/
   char **h_addr_list;  /* ptr to array of ptrs with IPv4 addrs . 表示的是主机的ip地址，注意，这个是以网络字节序存储的。*/
};

#define HOST_NOT_FOUND
#define TRY_AGAIN
#define NO_RECOVERY
#define NO_DATA    /* specified name is valid, but it does not have an A record*/

/* 
  Returns: non-null pointer if OK,NULL on error with h_errno set
  
  1 it returns a pointer to a hostent structure that contains all the IPv4 addresses for the host. */
struct hostent *gethostbyname (const char *hostname);
	 
	 
#include <netdb.h>
/*@addr：指向网络字节顺序地址的指针。
  @len： 地址的长度，在AF_INET类型地址中为4。
  @type：地址类型，应为AF_INET。
  @Returns: non-null pointer if OK, NULL on error with h_errno set */	  
struct hostent *gethostbyaddr (const char *addr, socklen_t len, int family);
	  
	  
#include <netdb.h>
struct servent {
  char   *s_name;      /* official service name */
  char  **s_aliases;   /* alias list */
  int     s_port;      /* port number, network-byte order */
  char   *s_proto;     /* protocol to use */
};
{
struct servent *sptr;

sptr = getservbyname("domain", "udp"); /* DNS using UDP */
sptr = getservbyname("ftp", "tcp");    /* FTP using TCP */
sptr = getservbyname("ftp", NULL);     /* FTP using TCP */
sptr = getservbyname("ftp", "udp");    /* this call will fail */
}
/*Returns: non-null pointer if OK, NULL on error */	   
struct servent *getservbyname (const char *servname, const char *protoname);
	   
	   
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

/*-----------------------------------------------------------------------------------
 Given @node and @service,which identify an Internet host and a service,@getaddrinfo 
 returns one or more addrinfo structures, each of which contains an Internet address 
 that can be specified in a call to @bind or @connect. The @getaddrinfo function co-
 mbines the functionality provided by the @gethostbyname and @getservbyname functions 
 into a single interface,but unlike the latter functions, @getaddrinfo() is reentrant 
 and allows programs to eliminate IPv4-versus-IPv6 dependencies.
 @node
     specifies either a numerical network address (for IPv4,numbers-and-dots notation 
     as supported by @inet_aton; for  IPv6, hexadecimal string format as supported by
     @inet_pton), or a network hostname, whose network addresses are looked up and r-
     esolved. If @hints.ai_flags contains the AI_NUMERICHOST flag,then node must be a 
     numerical network address. The AI_NUMERICHOST flag suppresses any potentially l-
     engthy network host address lookups.
 @service
    sets the port in each returned address structure. If this argument is a service 
    name, it is translated to the corresponding port number.This argument can also be 
    specified as a decimal number, which is simply converted to binary. If service is
    NULL, then the port number of the returned socket addresses will be left uniniti-
    alized. If AI_NUMERICSERV is specified in hints.ai_flags and service is not NULL, 
    then service must point to a string containing a numeric port number. This flag is 
    used to inhibit the invocation of a name resolution service in cases where it is 
    known not to be required.
    Either @node or @service, but not both, may be NULL.
 @hints
    Specifying @hints as NULL is equivalent to setting @ai_socktype and @ai_protocol 
    to 0; @ai_family to AF_UNSPEC; and ai_flags to (AI_V4MAPPED | AI_ADDRCONFIG).
    (POSIX specifies different defaults for ai_flags; see NOTES.)
 @res
    The @getaddrinfo function allocates and initializes a linked list of addrinfo st-
    ructures, one for each network address that matches @node and @service,subject to 
    any restrictions imposed by hints, and returns a pointer to the start of the list 
    in @res.  The items in the linked list are linked by the @ai_next field.

 1 通常服务器端在调用@getaddrinfo之前，ai_flags设置AI_PASSIVE，用于bind；主机名nodename
   通常会设置为NULL，返回通配地址[::]。
 2 客户端调用getaddrinfo时，ai_flags一般不设置AI_PASSIVE，但是主机名nodename和服务名servname
  （更愿意称之为端口）则应该不为空。
 3 当然，即使不设置AI_PASSIVE，取出的地址也并非不可以被bind，很多程序中ai_flags直接设置为0，
   即3个标志位都不设置，这种情况下只要hostname和servname设置的没有问题就可以正确bind。   
-----------------------------------------------------------------------------------*/	   
int getaddrinfo(const char *node, const char *service,const struct addrinfo *hints,
                   struct addrinfo **res);	   
void freeaddrinfo(struct addrinfo *res);
const char *gai_strerror(int errcode);



#define AF_UNSPEC

/*---------------- struct addrinfo @ai_flags 
AI_PASSIVE
   当此标志置位时，表示调用者将在bind()函数调用中使用返回的地址结构。当此标志不置位时
   ，表示将在connect()函数调用中使用。当@node为NULL，且此标志置位，则返回的地址将是通
   配地址。如果@node为NULL，且此标志不置位，则返回的地址将是回环地址。
AI_CANONNAME   
   当此标志置位时，在函数所返回的第一个addrinfo结构中的@ai_cannoname成员中，应该包含一
   个以空字符结尾的字符串，字符串的内容是节点名的正规名。
AI_NUMERICHOST   
   当此标志置位时，此标志表示调用中的节点名必须是一个数字地址字符串。
*/
#define AI_PASSIVE 
#define AI_CANONNAME 
#define AI_NUMERICHOST


/*-----------------------------------------------------------------------------------
 http://man7.org/linux/man-pages/man3/getaddrinfo.3.html

 @ai_family: AF_INET AF_INET6 AF_UNSPEC
    This field specifies the desired address family for the returned addresses. Valid 
    values for this field include AF_INET and AF_INET6. The value AF_UNSPEC indicates 
    that @getaddrinfo() should return socket addresses for any address family (either 
    IPv4 or IPv6, for example) that can be used with node and service.
 @ai_socktype: SOCK_STREAM SOCK_DGRAM 
    This field specifies the preferred socket type,for example SOCK_STREAM or SOCK_DGRAM. 
    Specifying 0 in this field indicates that socket addresses of any type can be ret-
    urned by @getaddrinfo().
 @ai_protocol: IPPROTO_IP IPPROTO_IPV4 IPPROTO_IPV6 IPPROTO_UDP IPPROTO_TCP
    This field specifies the protocol for the returned socket addresses. Specifying 0 
    in this field indicates that socket addresses with any protocol can be returned by
    @getaddrinfo().
 @ai_flags: AI_PASSIVE AI_CANONNAME AI_NUMERICHOST
    This field specifies additional options, described below. Multiple flags are spec-
    ified by bitwise OR-ing them together.
*/
struct addrinfo {
    int ai_flags;
    int ai_family;
    int ai_socktype;
    int ai_protocol;
    size_t ai_addrlen;        //must be zero or a null pointer
    char* ai_canonname;       //must be zero or a null pointer
    struct sockaddr* ai_addr; //must be zero or a null pointer
    struct addrinfo* ai_next; //must be zero or a null pointer
};

